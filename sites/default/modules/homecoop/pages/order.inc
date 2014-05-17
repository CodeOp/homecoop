<?php

function homecoop_page_order() {
  homecoop_authenticated_page();
  
  global $HomeCoopThemePath, $g_sRootRelativePath, $g_oError, $g_oMemberSession;
  
  $hcsettings = array(
    'ThemePath' => $HomeCoopThemePath,
    'ConfirmDelete' => t('Please confirm or cancel the delete operation'),
  );
  
  drupal_add_js(array('homecoop' => $hcsettings), 'setting');
  homecoop_add_js_file('order.js');
  
  $oRecord = new Order;
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
  
  $GLOBALS['g_oFormExtraData'] = array(
    'record' => $oRecord,
    'ordertab' => $oOrderTabInfo,
    'pltab' => $oPLTabInfo,
    'cooptab' => $oTabInfo,
    'pickuplocs' => $arrPickupLocs,
    'members' => $arrMembers,
    'hascoordpermission' => $bHasCoordPermission,
  );
  
  $arrContent = array(
    'orderform' => drupal_get_form('homecoop_page_order_form'),
  );
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $arrContent;
}

function homecoop_page_order_form($form, &$form_state) {
  global $g_oError, $g_oFormExtraData;
  if (!isset($g_oFormExtraData)) {
    return array();
  }
  
  $oRecord = $g_oFormExtraData['record'];
  
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
        '#value' => $oRecord->ID > 0 ? t('Save Order Header') : t('Create Order'),
        '#disabled' => $oRecord->CanModify ? FALSE: TRUE,
        '#attributes' => array('class' => array('order')),
        '#suffix' => '&nbsp;',
        '#weight' => 10, 
      ),
    ),
    'controlstable' => array(
      '#weight' => 50,
    ),
  );

  if ($oRecord->CanModify && $oRecord->ID > 0 && $oRecord->HasPermission(SQLBase::PERMISSION_DELETE)) {
    $form['maintable']['buttons']['delete'] = array(
      'type' => 'submit',
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
  
  if ($oRecord->CanModify)
  {
    $form['maintable']['controlstable']['pickuploc'] = array(
       '#type' => 'select',
        '#key_type' => 'associative',
        '#title' => t('Location Name'),
        '#options' => $g_oFormExtraData['pickuplocs'],
        '#default_value' => $oRecord->PickupLocationID,
        '#weight' => 10,
        '#required' => TRUE,
     );
  }
  else
  {
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
  }
  
  return $form;
                
 /*               
                
                  if ($oRecord->CanModify && $bHasCoordPermission && 
                      $oRecord->HasPermission(Order::PERMISSION_SET_MAX_ORDER) )
                  {
                    echo '<tr>';
                   
                    $txtBalance = new HtmlTextLabel('Balance', 'txtBalance', $oRecord->Balance);
                    $txtBalance->EchoHtml();
                    unset($txtBalance);
                 
                    echo '<td></td>';
                    echo '</tr>';
                
                    echo '<tr>';
                
                    $selPaymentMethod = new HtmlSelectArray('PaymentMethodKeyID', 'Payment Method', $arrPaymentMethods,
                          $oRecord->PaymentMethodID);
                    $selPaymentMethod->Required = TRUE;
                    $selPaymentMethod->ReadOnly = !$oRecord->CanModify;
                    $selPaymentMethod->EchoHtml();
                    unset($selPaymentMethod);

                    echo '<td></td>';
                    echo '</tr>';

                    echo '<tr>';
                    $txtPOBalance = new HtmlTextEditNumeric('% Over Balance', 'txtPercentOverBalance', 
                            $oRecord->PercentOverBalance);
                    $txtPOBalance->ReadOnly = !$oRecord->CanModify;
                    $txtPOBalance->EchoHtml();
                    unset($txtPOBalance);
                  
                    echo '<td><a id="percentoverhlp" name="percentoverhlp" class="tooltiphelp" href="#percentoverhlp" >‏?‏<span class="helpspan">The percentage in which a member&#x27;s order can exceed hir balance. This rule is being applied only when the member&#x27;s payment method allows a percentage over balance.</span></a></td>';
                    echo '</tr>';

                  }
                ?>
                <tr>
                  <?php
                    $lblMaxOrder = new HtmlTextLabel('Max. Order', 'lblMaxOrder',$oRecord->MaxOrder);
                    $lblMaxOrder->EchoHtml();
                    unset($lblMaxOrder);
                  ?>
                  <td></td>
                </tr>

                <tr>
                  <td><label for="txtMemberComments">Comments‏:‏</label></td>
                  <?php 
                    $txtMemberComments = new HtmlTextEdit('txtMemberComments', NULL , 
                            HtmlTextEdit::TEXTAREA, $oRecord->MemberComments);
                    $txtMemberComments->ReadOnly = !$oRecord->CanModify;
                    $txtMemberComments->MaxLength = Order::MAX_LENGTH_MEMBER_COMMENTS;
                    $txtMemberComments->EchoEditPartHtml();
                  ?>
                  <td></td>
                </tr>
                <?php 
                  if ($bHasCoordPermission && $oRecord->CanModify)
                  {
                    echo '<tr>';
                    
                    $sMemberFieldLabel = NULL;
                    
                    //change the label of the member field, according to whether a new order or existing one
                    if ($oRecord->ID > 0)
                      $sMemberFieldLabel = 'Move order to';
                    else
                      $sMemberFieldLabel = 'Member';
                    
                    //select member
                    $selMember = new HtmlSelectArray('MemberID', $sMemberFieldLabel, $arrMembers, $oRecord->MemberID);
                    $selMember->OnChange = "JavaScript:MemberChange();";
                    $selMember->Required = TRUE;
                    $selMember->EmptyText = NULL; //remove empty row
                    $selMember->EchoHtml();
                    
                    echo '<td><span id="spLoginName" name="spLoginName">';
                    if ($selMember->ValueFound) //if member not found, don't show incorrect data
                        echo sprintf('Login name: %s', htmlspecialchars( $oRecord->LoginName ));
                    echo '</span></td>';
                    
                    echo '</tr>';
                    
                    echo '<tr>',
                          '<td><label>Email address‏:‏</label></td>';
                    
                    echo '<td>';
                    
                    if ($selMember->ValueFound) //if member not found, don't show incorrect data
                    {
                      echo htmlspecialchars($oRecord->EMail);
                      if ( $oRecord->EMail2 != NULL )
                        echo ', ', htmlspecialchars($oRecord->EMail2);
                      if ( $oRecord->EMail3 != NULL )
                        echo ', ', htmlspecialchars($oRecord->EMail3);
                      if ( $oRecord->EMail4 != NULL )
                        echo ', ', htmlspecialchars($oRecord->EMail4);
                    }
                     
                    echo '</td>';
                   
                    echo '<td></td>';
                    
                    echo '</tr>';
                  }
                ?>
                <?php if ($oRecord->ID > 0) { 
                  
                  $sContacts = '';
                  
                  if ($arrCOContacts != NULL)
                  {
                    
                    foreach($arrCOContacts as $arrCOValues)
                    {
                      $sContacts .= sprintf('%1$s, %2$s ', $arrCOValues["sName"], $arrCOValues["sEMail"]);
                    }
                    
                    if ($sContacts != '')
                    {
                      $lblCOContacts = new HtmlTextLabel('Order Coordinator(s)','lblCOContacts', $sContacts);
                      echo '<tr>';
                      $lblCOContacts->EchoHtml(); 
                      echo '<td></td></tr>';
                    }
                  }
                  
                  
                  if ($arrPLContacts != NULL)
                  {
                    $sContacts = '';
                    foreach($arrPLContacts as $arrPLValues)
                    {
                      $sContacts .= sprintf('%1$s, %2$s ', $arrPLValues["sName"], $arrPLValues["sEMail"]);
                      
                    }
                    if ($sContacts != '')
                    {
                      $lblPLContacts = new HtmlTextLabel('Pickup Location Coordinator(s)','lblPLContacts', $sContacts);
                      echo '<tr>';
                      $lblPLContacts->EchoHtml();
                      echo '<td></td></tr>';
                    }
                  }
                  
                  ?>
                <tr><td colspan="3">&nbsp;</td></tr>
                <tr>
                  <td colspan="3">
                    <?php
                        echo(sprintf('Last update by %1$s on %2$s at %3$s',$oRecord->ModifiedByMemberName,
                                $oRecord->DateModified->format('n.j.Y'),
                                $oRecord->DateModified->format('g:i A')
                                ));
                    ?>
                  </td>
                </tr>
                <tr>
                  <td colspan="3">
                    <?php
                        echo(sprintf('Created by %1$s on %2$s at %3$s',$oRecord->CreatedByMemberName,
                                $oRecord->DateCreated->format('n.j.Y'),
                                $oRecord->DateCreated->format('g:i A')
                                ));
                    ?>
                  </td>
                </tr>
                <?php } ?>*/
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

function homecoop_page_order_form_save($form, &$form_state) {
}