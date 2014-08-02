<?php

function homecoop_page_copickuplocs() {
  global $g_oMemberSession, $language;
  
  homecoop_authenticated_page();
     
  $oData = new CoopOrderPickupLocations;

  $oTabInfo = new CoopOrderTabInfo;
  $bReadOnly = FALSE;
  $oTabInfo->Page = CoopOrderTabInfo::PAGE_PICKUP;
  
  $bShowSums = FALSE;
   
  if (isset($_GET['id']))
    $oData->CoopOrderID = intval($_GET['id']);
  
  if ($oData->CoopOrderID <= 0)
  {
     drupal_goto(Consts::URL_ACCESS_DENIED);
     return;
  }
  
  $oData->LoadData();
  
  switch($oData->LastOperationStatus)
  {
    case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
    case SQLBase::OPERATION_STATUS_NO_PERMISSION:
    case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
    case SQLBase::OPERATION_STATUS_COORDINATION_GROUP_VERIFY_FAILED:
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  drupal_set_title(t('@name - Pickup Locations', array('@name' => $oData->Name)));

  $oTabInfo->ID = $oData->CoopOrderID;
  $oTabInfo->CoopOrderTitle = $oData->Name;
  $oTabInfo->Status = $oData->Status;
  $oTabInfo->CoordinatingGroupID = $oData->CoordinatingGroupID;
  $oTabInfo->StatusObj = new ActiveCoopOrderStatus($oData->End, $oData->Delivery, $oData->Status);
  $oTabInfo->CoopTotal = $oData->CoopOrderCoopTotal; 
  
  if (!$oData->HasPermission(CoopOrderPickupLocations::PERMISSION_COOP_ORDER_PICKUP_LOCATION_EDIT)) {
      $bReadOnly = TRUE;
  }
  else if ($oData->Status != CoopOrder::STATUS_ACTIVE 
          && $oData->Status != CoopOrder::STATUS_DRAFT
          && $oData->Status != CoopOrder::STATUS_LOCKED )
  {
    $bReadOnly = TRUE;
    drupal_set_message(t('Cooperative order cannot be updated at its current status'), 'warning', FALSE);
  }
  
  //args: allow add, allow coord, language, language, coordinating groups
  $arrParams = array(
    $oData->CoopOrderID,
    $bReadOnly? 'ro' : 'rw',
    $language->language,
    $language->language,
  );
  
  if ( $oData->GetPermissionScope(CoopOrderPickupLocations::PERMISSION_COOP_ORDER_PICKUP_LOCATION_EDIT) == Consts::PERMISSION_SCOPE_GROUP_CODE ) {
    $arrParams[] = implode("+", $g_oMemberSession->Groups);
  }
  
  $oExtraData = homecoop_get_tabs_info($oTabInfo, NULL, NULL, TRUE);
  
  if ($oData->HasPermission(CoopOrderPickupLocations::PERMISSION_SUMS)) {
    $view = views_get_view('homecoop_cooporder_pickup_locations');  
  }
  else {
    $view = views_get_view('homecoop_cooporder_pickup_locations_nosums');  
  }
  
  $view->preview=TRUE;
  $view->is_cacheable = FALSE;
  $view->init_display('default'); 
  $view->pre_execute($arrParams);
  
  $content = array(
    'coopordertab' => array(
      'tab' => homecoop_tab_cooporder($oExtraData),
      '#weight' => 10,
     ),
    'spacer' => array(
      '#markup' => '<div class="spacer4">&nbsp;</div>',
      '#weight' => 15,
    ),
    'view' => array(
      '#markup' => $view->display_handler->preview(),
      '#weight' => 20,
    ),
  );
  
  $view->post_execute();
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $content;
}
