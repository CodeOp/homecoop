<?php

function homecoop_page_order() {
  homecoop_authenticated_page();
  
  global $HomeCoopThemePath, $g_sRootRelativePath, $g_oError, $g_oMemberSession;
  
  
  
  $oRecord = new Order;
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
  
  
  if (isset($_GET['id']))
  {
    if(!$oRecord->LoadRecord( intval($_GET['id'])) )
    {
        RedirectPage::To( $g_sRootRelativePath . Consts::URL_ACCESS_DENIED );
        exit;
    }
  }
  else if (isset($_GET['coid']))
  {
    $oRecord->LoadCoopOrder(intval($_GET['coid']), $g_oMemberSession->MemberID);
  }
  
  switch($oRecord->LastOperationStatus)
  {
    case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
    case SQLBase::OPERATION_STATUS_NO_PERMISSION:
    case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
    case SQLBase::OPERATION_STATUS_COORDINATION_GROUP_VERIFY_FAILED:
      RedirectPage::To( $g_sRootRelativePath . Consts::URL_ACCESS_DENIED );
      exit;
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
        drupal_set_message(t('There are no members left to add to this cooperative order. All members are already ordering.'),'error');
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
  
  $oFormExtraData = array(
    'record' => $oRecord,
    'ordertab' => $oOrderTabInfo,
    'pltab' => $oPLTabInfo,
    'cooptab' => $oTabInfo,
    'pickuplocs' => $arrPickupLocs,
    'members' => $arrMembers,
    'hascoordpermission' => $bHasCoordPermission,
    'paymethods' => $arrPaymentMethods,
    'cocontacts' => $arrCOContacts,
    'plcontacts' => $arrPLContacts,
  );
  
  $arrContent = array(
    'orderform' => drupal_get_form('homecoop_page_order_form', $oFormExtraData),
  );
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $arrContent;
}

function homecoop_page_order_form($form, &$form_state, $oFormExtraData) {
  global $g_oError;
  if (!isset($oFormExtraData)) {
    return array();
  }
  $bHasCoordPermission = $oFormExtraData['hascoordpermission'];
  $oRecord = $oFormExtraData['record'];
  
  $form['#id'] = 'homecoop_page_order_form';
  $form['hidOriginalData'] = array('#type' => 'hidden', '#default_value' => $oRecord->GetSerializedOriginalData(), 
    '#attributes' => array('id' => 'hidOriginalData'));
  $form['hidPostAction'] = array('#type' => 'hidden', '#default_value' => '', 
    '#attributes' => array('id' => 'hidPostAction'));
  $form['hidPostValue'] = array('#type' => 'hidden', '#default_value' => $oRecord->ID, 
    '#attributes' => array('id' => 'hidPostValue'));
  $form['maintable'] = array(
    'coopordertab' => array(
      'tab' => homecoop_order_tab_cooporder(),
      '#weight' => 10,
    ),
    'copickuploctab' => array(
      'tab' => homecoop_order_tab_copickuploc(),
      '#weight' => 20,
    ),
    'ordertab' => array(
      'tab' => homecoop_order_tab_order(),
      '#weight' => 30,
    ),
    'buttons' => array(
      '#weight' => 40,   
      'btn_save' => array(
        '#type' => 'submit',
        '#id' => 'btn_save',
        '#submit' => array('homecoop_page_order_form_save'),
        '#value' => $oRecord->ID > 0 ? t('Save Order Header') : t('Open New Order'),
        '#disabled' => $oRecord->CanModify ? FALSE: TRUE,
        '#attributes' => array('class' => array('order')),
        '#suffix' => '&nbsp;',
        '#weight' => 10, 
      ),
    ),
    'controlstable' => array(
      '#weight' => 50,
      'maxorder' => array(
        '#prefix' => '<label>' . t('Max. Order') . '</label><span>',
        '#markup' => $oRecord->MaxOrder,
        '#suffix' => '</span>',
        '#weight' => 70,
      ),
      'membercomments' => array(
        '#type' => 'textarea',
        '#max_length' => Order::MAX_LENGTH_MEMBER_COMMENTS,
        '#rows' => 3,
        '#default_value' => check_plain($oRecord->MemberComments),
        '#disabled' => $oRecord->CanModify ? false: true,
        '#weight' => 80,
        '#attributes' => array('placeholder' => t('Any comments?')),
      )
    ),
  );

  if ($oRecord->CanModify && $oRecord->ID > 0 && $oRecord->HasPermission(SQLBase::PERMISSION_DELETE)) {
    $form['maintable']['buttons']['delete'] = array(
        '#type' => 'submit',
        '#id' => 'btnDelete',
        '#submit' => array('homecoop_page_front_form_delete'),
        '#value' => t('Delete @title', array('@title' => $oRecord->PageTitleSuffix)),
        '#disabled' => $oRecord->CanModify ? false: true,
        '#weight' => 20, 
        '#attributes' => array(
          'class' => array('order'),
          'onclick' => array('ConfirmDelete();'),
        ),
    );
  }
  
  if ($oRecord->CanModify) {
    $form['maintable']['controlstable']['pickuploc'] = array(
        '#type' => 'select',
        '#key_type' => 'associative',
        '#title' => t('Location Name'),
        '#options' => $oFormExtraData['pickuplocs'],
        '#default_value' => $oRecord->PickupLocationID,
        '#weight' => 10,
        '#required' => TRUE,
     );
    
    if ($bHasCoordPermission) {
      if ($oRecord->HasPermission(Order::PERMISSION_SET_MAX_ORDER)) {
        $form['maintable']['controlstable']['balance'] = array(
          '#prefix' => '<label>' . t('Balance') . '</label><span>',
          '#markup' => $oRecord->Balance,
          '#suffix' => '</span>',
          '#weight' => 40,
        );
        $form['maintable']['controlstable']['paymethod'] = array(
          '#type' => 'select',
          '#key_type' => 'associative',
          '#title' => t('Payment Method'),
          '#options' => $oFormExtraData['paymethods'],
          '#default_value' => $oRecord->PaymentMethodID,
          '#weight' => 50,
          '#required' => TRUE,
          '#disabled' => $oRecord->CanModify ? false: true,
       );

        $form['maintable']['controlstable']['percentoverbalance'] = array(
          '#type' => 'textfield',
          '#title' => t('% Over Balance'),
          '#description' => t('The percentage in which a member\'s order can exceed hir balance. This rule is being applied only when the member\'s payment method allows a percentage over balance.'),
          '#size' => 5,
          '#max_length' => 5,
          '#default_value' => $oRecord->PercentOverBalance,
          '#weight' => 60,
          '#disabled' => $oRecord->CanModify ? false: true,
          '#rules' => array('decimal'),
        );
      }
      
      $form['maintable']['controlstable']['selMemberID'] = array(
        '#type' => 'select',
        '#id' => 'selMemberID',
        '#key_type' => 'associative',
        '#title' => ($oRecord->ID > 0)? t('Move order to') : t('Member'),
        '#options' => $oFormExtraData['members'],
        '#default_value' => $oRecord->MemberID,
        '#weight' => 90,
        '#required' => TRUE,
        '#attributes' => array(
          'onchange' => 'MemberChange();',
          'id' => 'selMemberID',
        ),
      );
      
      //if member found in select list
      if (isset($oFormExtraData['members'][$oRecord->MemberID])) {
        $form['maintable']['controlstable']['loginname'] = array(
          '#prefix' => '<label>' . t('Login name') . '</label><span>',
          '#markup' => check_plain($oRecord->LoginName),
          '#suffix' => '</span>',
          '#weight' => 100,
        );
        
        $sEmail = $oRecord->EMail;
        if ( $oRecord->EMail2 != NULL )
          $sEmail .= ', ' . $oRecord->EMail2;
        if ( $oRecord->EMail3 != NULL )
          $sEmail .= ', ' . $oRecord->EMail3;
        if ( $oRecord->EMail4 != NULL )
          $sEmail .= ', ' . $oRecord->EMail4;
        
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
        '#markup' => check_plain($oRecord->PickupLocationName),
        '#suffix' => '</span>',
        '#weight' => 10,
     );
  }
  
  if ($oRecord->ID > 0) {
    $form['maintable']['controlstable']['pickupaddress'] = array(
       '#prefix' => '<label>' . t('Address') . '</label><span>',
       '#markup' => check_plain($oRecord->PickupLocationAddress),
       '#suffix' => '</span>',
       '#weight' => 20,
    );
    $form['maintable']['controlstable']['pickupinstruct'] = array(
       '#prefix' => '<label>' . t('Pickup Instructions') . '</label><span>',
       '#markup' => check_plain($oRecord->PublishedComments),
       '#suffix' => '</span>',
       '#weight' => 30,
    );
     
    homecoop_page_order_display_contacts('cocontacts', $oFormExtraData, $form, t('Order Coordinator(s)'), 120 );
    homecoop_page_order_display_contacts('plcontacts', $oFormExtraData, $form, t('Pickup Location Coordinator(s)'), 130 );
    
    $form['maintable']['controlstable']['lastupdate'] = array(
       '#markup' => '<label>' . t('Last update by @membername on @date at @time',
            array(
              '@membername' => $oRecord->ModifiedByMemberName,
              '@date' => $oRecord->DateModified->format('n.j.Y'),
              '@time' => $oRecord->DateModified->format('g:i A'),
            )
           ) . '</label>',
       '#weight' => 140,
    );
    
    $form['maintable']['controlstable']['created'] = array(
       '#markup' => '<label>' . t('Created by @membername on @date at @time',
            array(
              '@membername' => $oRecord->CreatedByMemberName,
              '@date' => $oRecord->DateCreated->format('n.j.Y'),
              '@time' => $oRecord->DateCreated->format('g:i A'),
            )
           ) . '</label>',
       '#weight' => 150,
    );
  }
  
  $form['#submit'][] = 'homecoop_page_order_form_submit';
  
  return $form;
}

function homecoop_order_tab_cooporder() {
  return array('#markup' => '');
}
function homecoop_order_tab_copickuploc() {
  return array('#markup' => '');
}
function homecoop_order_tab_order() {
  return array('#markup' => '');
}

/*
 * Submit function for the save operation
 */
function homecoop_page_order_form_save($form, &$form_state) {
  
}

/*
 * Submit function for the delete operation
 */
function homecoop_page_front_form_delete($form, &$form_state) {
  
}

/*
 * Other submits, according to action (change of member)
 */
function homecoop_page_order_form_submit($form, &$form_state) {
  if (!isset($form_state['values']['hidPostAction'])) {
    return;
  }
  $nAction = intval($form_state['values']['hidPostAction']);
  switch($nAction) {
    case Order::POST_ACTION_MEMBER_CHANGE:
      break;
  }
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

