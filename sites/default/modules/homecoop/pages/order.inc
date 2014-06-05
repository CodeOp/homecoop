<?php

function homecoop_page_order() {
  homecoop_authenticated_page();
  
  global $HomeCoopThemePath, $g_oMemberSession;
    
  $oRecord = new Order;
  
  if (isset($_GET['id'])) {
    if(!$oRecord->LoadRecord( intval($_GET['id'])) ) {
        drupal_goto(Consts::URL_ACCESS_DENIED);
        return;
    }
  }
  else if (isset($_GET['coid'])) {
    $oRecord->LoadCoopOrder(intval($_GET['coid']), $g_oMemberSession->MemberID);
  }
  
  switch($oRecord->LastOperationStatus) {
    case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
    case SQLBase::OPERATION_STATUS_NO_PERMISSION:
    case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
    case SQLBase::OPERATION_STATUS_COORDINATION_GROUP_VERIFY_FAILED:
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  $hcsettings = array(
    'ConfirmDelete' => t('Please confirm or cancel the delete operation'),
    'ConfirmMemberChange' => t('Attention: you have chosen to move this order from one member to another. To complete the operation confirm this message box and save the order'),
    'MemberID' => $oRecord->MemberID,
    'PostActionMemberChange' => Order::POST_ACTION_MEMBER_CHANGE,
    'ThemePath' => $HomeCoopThemePath,
  );
  
  drupal_add_js(array('homecoop' => $hcsettings), 'setting');
  homecoop_add_js_file('order.js');
  
  $oFormExtraData = homecoop_page_order_prepareform($oRecord);
  
  $arrContent = array(
    'orderform' => drupal_get_form('homecoop_page_order_form', $oFormExtraData),
  );
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $arrContent;
}

function homecoop_page_order_prepareform(&$oRecord) {
  
  global $g_oMemberSession;
  
  $oPickupLocs = NULL;
  $oMembers = NULL;
  $arrPickupLocs = NULL;
  $arrMembers = NULL;
  $oTabInfo = NULL;
  $oOrderTabInfo = NULL;
  $oPLTabInfo = NULL;
  $arrCOContacts = NULL;
  $arrPLContacts = NULL;
  $arrPaymentMethods = NULL;
  $bHasCoordPermission = FALSE;
  

  $bHasCoordPermission = $oRecord->HasPermission(SQLBase::PERMISSION_COORD);
  if ( $oRecord->CanModify )
  {
    if ( $bHasCoordPermission )
    {
      $arrPaymentMethods = $oRecord->GetPaymentMethods();
      $oMembers = new Members;
      $arrMembers = $oMembers->GetMembersListForOrder($oRecord->CoopOrderID, $oRecord->ID);
      //if there are no members, can't modify
      if (!is_array($arrMembers) || count($arrMembers) == 0)
      {
        $oRecord->CanModify = FALSE;
        drupal_set_message(t('There are no members left to add to this cooperative order. All members are already ordering.'),'error', false);
      }
      //if the required member is not in the list - set member to first one
      elseif (!isset($arrMembers[$oRecord->MemberID]))
      {
        $oRecord->LoadCoopOrder($oRecord->CoopOrderID, key($arrMembers));
      }
    }
    
    $oPickupLocs = new CoopOrderPickupLocations;
    $arrPickupLocs = array();
    if ($bHasCoordPermission) {
      $arrPickupLocs = $oPickupLocs->GetListKeyPair($oRecord->CoopOrderID, $oRecord->MemberID);
    }
    else
    {
      //prepare to load facet-aware pickup location list
      homecoop_prepare_pickup_facet();
      global $g_aMemberPickupLocationIDs;
      //update facet on the fly to include current pickup location
      if ($oRecord->ID > 0 && $oRecord->PickupLocationID > 0 && !isset($g_aMemberPickupLocationIDs[$oRecord->PickupLocationID])) {
        $g_aMemberPickupLocationIDs[$oRecord->PickupLocationID] = $oRecord->PickupLocationID;
      }
      //load facet-aware pickup location list
      $arrPickupLocs = $oPickupLocs->GetFacetKeyPair($oRecord->CoopOrderID, $g_oMemberSession->MemberID);
    }
  }

  $oTabInfo = new CoopOrderTabInfo;
  $oTabInfo->CoordinatingGroupID = $oRecord->CoordinatingGroupID;
  $oTabInfo->ID = $oRecord->CoopOrderID;
  if ( $oTabInfo->CheckAccess() )
  {
    $oTabInfo->Page = CoopOrderTabInfo::PAGE_ORDERS;
    $oTabInfo->CoopOrderTitle = $oRecord->CoopOrderName;
    $oTabInfo->IsSubPage = TRUE;
    $oTabInfo->Status = $oRecord->Status;
    $oTabInfo->CoopTotal = $oRecord->CoopOrderCoopTotal; 
  }
  
  $oPLTabInfo = new CoopOrderPickupLocationTabInfo( $oRecord->CoopOrderID, $oRecord->PickupLocationID, $oRecord->PickupLocationName, 
        CoopOrderPickupLocationTabInfo::PAGE_ORDERS );
  $oPLTabInfo->CoordinatingGroupID = $oRecord->PickupLocationGroupID;
  $oPLTabInfo->IsSubPage = TRUE;

  $oOrderTabInfo = new OrderTabInfo($oRecord->ID, OrderTabInfo::PAGE_ENTRY, $oRecord->CoopTotal, $oRecord->OrderCoopFee);
  $oOrderTabInfo->StatusObj = $oRecord->StatusObj;
  $oPercent = new CoopOrderCapacity($oRecord->MaxBurden, $oRecord->TotalBurden, $oRecord->MaxCoopTotal, $oRecord->CoopOrderCoopTotal,
      $oRecord->CoopOrderMaxStorageBurden, $oRecord->CoopOrderStorageBurden);
  if ($oPercent->SelectedType != CoopOrderCapacity::TypeNone)
    $oOrderTabInfo->Capacity = $oPercent->PercentRounded . '%';
  unset($oPercent);

  $oRecord->BuildPageTitle();
  drupal_set_title($oRecord->PageTitle);
  $oOrderTabInfo->MainTabName = $oRecord->PageTitleSuffix;

  //get contacts
  $oRecord->GetContacts($arrCOContacts, $arrPLContacts);
  
  return array(
      'pickuplocs' => $arrPickupLocs,
      'members' => $arrMembers,
      'hascoordpermission' => $bHasCoordPermission,
      'hassetmaxpermission' => $oRecord->HasPermission(Order::PERMISSION_SET_MAX_ORDER),
      'hasdeletepermission' => $oRecord->HasPermission(SQLBase::PERMISSION_DELETE),
      'paymethods' => $arrPaymentMethods,
      'cocontacts' => $arrCOContacts,
      'plcontacts' => $arrPLContacts,
      'OriginalData' => $oRecord->GetSerializedOriginalData(),
    ) + homecoop_get_tabs_info($oTabInfo, $oOrderTabInfo, $oPLTabInfo, $bHasCoordPermission) 
      + $oRecord->GetAllProperties();
}

function homecoop_page_order_form($form, &$form_state, $oFormExtraData) {
  if (isset($form_state['homecoop_order'])) {
    $oFormExtraData = $form_state['homecoop_order'];
  }
  elseif (isset($oFormExtraData)) {
    $form_state['homecoop_order'] = $oFormExtraData;
  }
  else  {
    return array();
  }
  
  $bHasCoordPermission = $oFormExtraData['hascoordpermission'];
  
  $form['#id'] = 'homecoop_page_order_form';
  $form['#attributes']['name'] = 'homecoop_page_order_form';
  //internal values
  $form['hidOriginalData'] = array('#type' => 'value', '#value' => $oFormExtraData['OriginalData'], 
    '#attributes' => array('id' => 'hidOriginalData'));
  $form['hidPostValue'] = array('#type' => 'value', '#value' => $oFormExtraData['ID'], 
    '#attributes' => array('id' => 'hidPostValue'));
  //exposed value
  $form['hidPostAction'] = array('#type' => 'hidden', '#default_value' => '', 
    '#attributes' => array('id' => 'hidPostAction'));
  
  $form['maintable'] = array(
    'coopordertab' => array(
      'tab' => homecoop_tab_cooporder($oFormExtraData),
      '#weight' => 10,
    ),
    'copickuploctab' => array(
      'tab' => homecoop_tab_copickuploc($oFormExtraData),
      '#weight' => 20,
    ),
    'ordertab' => array(
      'tab' => homecoop_tab_order($oFormExtraData),
      '#weight' => 30,
    ),
    'buttons' => array(
      '#weight' => 40,   
      'btn_save' => array(
        '#type' => 'submit',
        '#name' => 'btn_save',
        '#id' => 'btn_save',
        '#submit' => array('homecoop_page_order_form_submit'),
        '#value' => $oFormExtraData['ID'] > 0 ? t('Save Order Header') : t('Open New Order'),
        '#disabled' => $oFormExtraData['CanModify'] ? FALSE: TRUE,
        '#attributes' => array('class' => array('order'),
          ),
        '#suffix' => '&nbsp;',
        '#weight' => 10, 
      ),
    ),
    'controlstable' => array(
      '#weight' => 50,
      'maxorder' => array(
        '#prefix' => '<label>' . t('Max. Order') . '</label><span>',
        '#markup' => $oFormExtraData['MaxOrder'],
        '#suffix' => '</span>',
        '#weight' => 70,
      ),
      'membercomments' => array(
        '#type' => 'textarea',
        '#max_length' => Order::MAX_LENGTH_MEMBER_COMMENTS,
        '#rows' => 3,
        '#default_value' => check_plain($oFormExtraData['MemberComments']),
        '#disabled' => $oFormExtraData['CanModify'] ? false: true,
        '#weight' => 80,
        '#attributes' => array('placeholder' => t('Any comments?')),
      )
    ),
  );

  if ($oFormExtraData['CanModify'] && $oFormExtraData['ID'] > 0 && $oFormExtraData['hasdeletepermission']) {
    $form['maintable']['buttons']['btn_delete'] = array(
        '#type' => 'submit',
        '#name' => 'btn_delete',
        '#id' => 'btn_delete',
        '#submit' => array('homecoop_page_order_form_delete'),
        '#value' => t('Delete @title', array('@title' => $oFormExtraData['PageTitleSuffix'])),
        '#weight' => 20, 
        '#attributes' => array(
          'class' => array('order'),
          'onclick' => 'return ConfirmDelete();',
        ),
    );
  }
  
  if ($oFormExtraData['CanModify']) {
    $form['maintable']['controlstable']['pickuploc'] = array(
        '#type' => 'select',
        '#key_type' => 'associative',
        '#title' => t('Location Name'),
        '#options' => $oFormExtraData['pickuplocs'],
        '#default_value' => $oFormExtraData['PickupLocationID'],
        '#weight' => 10,
        '#required' => TRUE,
     );
    
    if ($bHasCoordPermission) {
      if ($oFormExtraData['hassetmaxpermission']) {
        $form['maintable']['controlstable']['balance'] = array(
          '#prefix' => '<label>' . t('Balance') . '</label><span>',
          '#markup' => $oFormExtraData['Balance'],
          '#suffix' => '</span>',
          '#weight' => 40,
        );
        $form['maintable']['controlstable']['paymethod'] = array(
          '#type' => 'select',
          '#key_type' => 'associative',
          '#title' => t('Payment Method'),
          '#options' => $oFormExtraData['paymethods'],
          '#default_value' => $oFormExtraData['PaymentMethodID'],
          '#weight' => 50,
          '#required' => TRUE,
          '#disabled' => $oFormExtraData['CanModify'] ? false: true,
       );

        $form['maintable']['controlstable']['percentoverbalance'] = array(
          '#type' => 'textfield',
          '#title' => t('% Over Balance'),
          '#description' => t('The percentage in which a member\'s order can exceed hir balance. This rule is being applied only when the member\'s payment method allows a percentage over balance.'),
          '#size' => 5,
          '#max_length' => 5,
          '#default_value' => $oFormExtraData['PercentOverBalance'],
          '#weight' => 60,
          '#disabled' => $oFormExtraData['CanModify'] ? false: true,
          '#rules' => array('decimal'),
        );
      }
      
      $form['maintable']['controlstable']['selMemberID'] = array(
        '#type' => 'select',
        '#id' => 'selMemberID',
        '#key_type' => 'associative',
        '#title' => ($oFormExtraData['ID'] > 0)? t('Move order to') : t('Member'),
        '#options' => $oFormExtraData['members'],
        '#default_value' => $oFormExtraData['MemberID'],
        '#weight' => 90,
        '#required' => TRUE,
        '#attributes' => array(
          'onchange' => 'MemberChange();',
          'id' => 'selMemberID',
        ),
      );
      
      //if member found in select list
      if (isset($oFormExtraData['members'][$oFormExtraData['MemberID']])) {
        $form['maintable']['controlstable']['loginname'] = array(
          '#prefix' => '<label>' . t('Login name') . '</label><span>',
          '#markup' => check_plain($oFormExtraData['LoginName']),
          '#suffix' => '</span>',
          '#weight' => 100,
        );
        
        $sEmail = $oFormExtraData['EMail'];
        if ( $oFormExtraData['EMail2'] != NULL )
          $sEmail .= ', ' . $oFormExtraData['EMail2'];
        if ( $oFormExtraData['EMail3'] != NULL )
          $sEmail .= ', ' . $oFormExtraData['EMail3'];
        if ( $oFormExtraData['EMail4'] != NULL )
          $sEmail .= ', ' . $oFormExtraData['EMail4'];
        
        $form['maintable']['controlstable']['email'] = array(
          '#prefix' => '<label>' . t('Email address‏') . '</label><span>',
          '#markup' => check_plain($sEmail),
          '#suffix' => '</span>',
          '#weight' => 110,
        );
      }
    }
  }
  else {
    $form['maintable']['controlstable']['pickuploc'] = array(
        '#prefix' => '<label>' . t('Location Name') . '</label><span>',
        '#markup' => check_plain($oFormExtraData['PickupLocationName']),
        '#suffix' => '</span>',
        '#weight' => 10,
     );
  }
  
  if ($oFormExtraData['ID'] > 0) {
    $form['maintable']['controlstable']['pickupaddress'] = array(
       '#prefix' => '<label>' . t('Address') . '</label><span>',
       '#markup' => check_plain($oFormExtraData['PickupLocationAddress']),
       '#suffix' => '</span>',
       '#weight' => 20,
    );
    $form['maintable']['controlstable']['pickupinstruct'] = array(
       '#prefix' => '<label>' . t('Pickup Instructions') . '</label><span>',
       '#markup' => check_plain($oFormExtraData['PublishedComments']),
       '#suffix' => '</span>',
       '#weight' => 30,
    );
     
    homecoop_page_order_display_contacts('cocontacts', $oFormExtraData, $form, t('Order Coordinator(s)'), 120 );
    homecoop_page_order_display_contacts('plcontacts', $oFormExtraData, $form, t('Pickup Location Coordinator(s)'), 130 );
    
    $form['maintable']['controlstable']['lastupdate'] = array(
       '#markup' => '<label>' . t('Last update by @membername on @date at @time',
            array(
              '@membername' => $oFormExtraData['ModifiedByMemberName'],
              '@date' => $oFormExtraData['DateModified']->format('n.j.Y'),
              '@time' => $oFormExtraData['DateModified']->format('g:i A'),
            )
           ) . '</label>',
       '#weight' => 140,
    );
    
    $form['maintable']['controlstable']['created'] = array(
       '#markup' => '<label>' . t('Created by @membername on @date at @time',
            array(
              '@membername' => $oFormExtraData['CreatedByMemberName'],
              '@date' => $oFormExtraData['DateCreated']->format('n.j.Y'),
              '@time' => $oFormExtraData['DateCreated']->format('g:i A'),
            )
           ) . '</label>',
       '#weight' => 150,
    );
  }
  
  return $form;
}


/*
 * Submit function for the save operation
 */
function homecoop_page_order_form_submit($form, &$form_state) {
  global $g_oMemberSession, $g_oError;
    
  if (isset($form_state['values']['hidPostAction'])
    && intval($form_state['values']['hidPostAction']) == Order::POST_ACTION_MEMBER_CHANGE) {
    homecoop_page_order_change_member($form, $form_state);
    return;
  }

  $oRecord = new Order;

  homecoop_page_order_get_common_form_data($form_state, $oRecord);

  if ( isset( $form_state['values']['membercomments'] )) {
    $sMemberComments = trim($form_state['values']['membercomments']);
    if (!empty($sMemberComments))
      $oRecord->MemberComments = $sMemberComments;
  }

  if ($oRecord->ID > 0) {
    $bSuccess = $oRecord->Edit();
    if ( $bSuccess ) {
      $g_oError->AddError('Record saved successfully.', 'status');
      return;
    }
  }
  else {
    $bSuccess = $oRecord->Add();
    if ($bSuccess) {
      //when just entering order items - show all        
      $form_state['redirect'] = array(
        'hcorderitems',
        array(
          'query' => array(
            'mode' => OrderItems::PRODUCTS_VIEW_MODE_SHOW_ALL,
            'id' => $oRecord->ID,
          ),
        ),
      );
      return;
    }
  }

  if ($oRecord->LastOperationStatus != SQLBase::OPERATION_STATUS_VALIDATION_FAILED) {
      $g_oError->AddError('Record was not saved. You may not have sufficent permissions or an error has occured.');
  }
  else {
    $g_oError->AddError('Data was not saved.');
  }

  switch($oRecord->LastOperationStatus)
  {
    case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
    case SQLBase::OPERATION_STATUS_NO_PERMISSION:
    case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
    case SQLBase::OPERATION_STATUS_COORDINATION_GROUP_VERIFY_FAILED:
      $form_state['redirect'] = Consts::URL_ACCESS_DENIED ;
      return;
  }
}

/*
 * Submit function for the delete operation
 */
function homecoop_page_order_form_delete($form, &$form_state) {
  global $g_oError;
  $oRecord = new Order;

  homecoop_page_order_get_common_form_data($form_state, $oRecord);
  
  if ( $oRecord->Delete() ) {
      $g_oError->AddError('The record was deleted successfully.', 'status');
      
      $form_state['redirect'] = array(
        'hcorder',
        array(
          'query' => array(
            'coid' => $oRecord->CoopOrderID,
          ),
        ),
      );
      return;
  }
  else {
      $g_oError->AddError('The record was not deleted.');
  }
  
  switch($oRecord->LastOperationStatus)
  {
    case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
    case SQLBase::OPERATION_STATUS_NO_PERMISSION:
    case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
    case SQLBase::OPERATION_STATUS_COORDINATION_GROUP_VERIFY_FAILED:
      $form_state['redirect'] = Consts::URL_ACCESS_DENIED ;
      return;
  }
}

/*
 * Other submits, according to action: change of member by coordinator
 */
function homecoop_page_order_change_member(&$form, &$form_state) {  
  $oRecord = new Order;

  homecoop_page_order_get_common_form_data($form_state, $oRecord);
  
  //load new member and coop order data
  $oRecord->LoadCoopOrder($oRecord->CoopOrderID, $oRecord->MemberID);
  
  $form_state['homecoop_order'] = homecoop_page_order_prepareform($oRecord);
  
  $form_state['rebuild'] = true;
}

function homecoop_page_order_display_contacts($sContactsKey, &$oFormExtraData, &$form, $sLabel, $Weight) {
  if ($oFormExtraData[$sContactsKey] != NULL) {
      $sContacts = '';
      foreach($oFormExtraData[$sContactsKey] as $arrValues) {
        $sContacts .= sprintf('%1$s, %2$s ', $arrValues["sName"], $arrValues["sEMail"]);
      }

      if ($sContacts != '') {
        $form['maintable']['controlstable'][$sContactsKey] = array(
          '#prefix' => '<label>' . $sLabel . '</label><span>',
          '#markup' => check_plain($sContacts),
          '#suffix' => '</span>',
          '#weight' => $Weight,
        );
      }
    }
}

function homecoop_page_order_get_common_form_data(&$form_state, &$oRecord) {
    global $g_oMemberSession;
    if ( isset($form_state['values']['hidPostValue'] ) && !empty($form_state['values']['hidPostValue'])) {
      $oRecord->ID = intval($form_state['values']['hidPostValue']);
    }
    
    if ( isset( $form_state['values']['hidOriginalData'] ) ) {
      $oRecord->SetSerializedOriginalData( $form_state['values']['hidOriginalData'] );
    }
    
    $oRecord->CopyOriginalDataWhenUnsaved();
    
    //collect data
    if ( isset( $form_state['values']['pickuploc'] )) {
      $oRecord->PickupLocationID = intval($form_state['values']['pickuploc']);
    }

    if ( isset( $form_state['values']['selMemberID'] )) {
      $oRecord->MemberID = intval($form_state['values']['selMemberID']);
    }
    else if ($oRecord->ID == 0) {
      $oRecord->MemberID = $g_oMemberSession->MemberID;
    }

    if ( isset( $form_state['values']['percentoverbalance'] ) && !empty($form_state['values']['percentoverbalance'])) {
      $oRecord->PercentOverBalance = 0 + trim($form_state['values']['percentoverbalance']);
    }

    if ( isset( $form_state['values']['paymethod'] )) {
      $oRecord->PaymentMethodID = intval($form_state['values']['paymethod']);
    }
}

