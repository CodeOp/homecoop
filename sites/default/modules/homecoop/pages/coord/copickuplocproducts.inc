<?php

function homecoop_page_copickuploc_products() {
  global $g_oMemberSession, $language;
  
  homecoop_authenticated_page();
  
  $oData = new CoopOrderPickupLocationProducts;
  $oTabInfo = new CoopOrderTabInfo;
  $oPLTabInfo = NULL;
  $oTabInfo->Page = CoopOrderTabInfo::PAGE_PICKUP;
  $oTabInfo->IsSubPage = TRUE;
  $oCoopOrderCapacity = NULL;
    
  if (isset($_GET['coid'])) {
    $oData->CoopOrderID = intval($_GET['coid']);
  }
  
  if (isset($_GET['plid'])) {
    $oData->PickupLocationID = intval($_GET['plid']);
  }
  
  if ($oData->CoopOrderID <= 0 || $oData->PickupLocationID <= 0) {
     drupal_goto(Consts::URL_ACCESS_DENIED);
     return;
  }
  
  $oData->LoadData();
  
  switch($oData->LastOperationStatus) {
    case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
    case SQLBase::OPERATION_STATUS_NO_PERMISSION:
    case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
    case SQLBase::OPERATION_STATUS_COORDINATION_GROUP_VERIFY_FAILED:
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  drupal_set_title(t('Products by Pickup Location @name', array('@name' => $oData->PickupLocationName)));
  
  //for some reason the #default_value property of the hidden element hidCurrentMainTab, set in homecoop_tab_cooporder()
  //does not work and its value remains empty, so we set it on load
  drupal_add_js('jQuery(document).ready(function () { document.getElementById("hidCurrentMainTab").value = "tabPickupLocation"; });', 'inline');

  $oTabInfo->ID = $oData->CoopOrderID;
  $oTabInfo->Status = $oData->Status;
  $oTabInfo->CoopOrderTitle = $oData->Name;
  $oTabInfo->CoordinatingGroupID = $oData->CoordinatingGroupID;
  $oTabInfo->StatusObj = new ActiveCoopOrderStatus($oData->End, $oData->Delivery, $oData->Status);
  $oTabInfo->CoopTotal = $oData->CoopOrderCoopTotal; 
  $oPercent = new CoopOrderCapacity($oData->CoopOrderMaxBurden, $oData->CoopOrderBurden, $oData->CoopOrderMaxCoopTotal, $oData->CoopOrderCoopTotal,
      $oData->CoopOrderMaxStorageBurden, $oData->CoopOrderStorageBurden);
  if ($oPercent->SelectedType != CoopOrderCapacity::TypeNone)
    $oTabInfo->Capacity = $oPercent->PercentRounded . '%';
  unset($oPercent);

  $oPLTabInfo = new CoopOrderPickupLocationTabInfo($oData->CoopOrderID, $oData->PickupLocationID, $oData->PickupLocationName, 
          CoopOrderPickupLocationTabInfo::PAGE_PRODUCTS);
  $oPLTabInfo->CoordinatingGroupID = $oData->PickupLocationCoordGroupID;

  //args: id, read-write/read-only, languageX3, coordinating groups
  $arrParams = array(
    $oData->CoopOrderID,
    $oData->PickupLocationID,
    $language->language,
    $language->language,
    $language->language,
  );
  
  if ( $oData->GetPermissionScope(CoopOrderPickupLocationProducts::PERMISSION_COOP_ORDER_PRODUCT_VIEW) != Consts::PERMISSION_SCOPE_COOP_CODE 
      && $oData->GetPermissionScope(CoopOrderPickupLocationProducts::PERMISSION_COOP_ORDER_PRODUCT_MODIFY) != Consts::PERMISSION_SCOPE_COOP_CODE) {
    $arrParams[] = implode("+", $g_oMemberSession->Groups);
  }
  
  $oExtraData = homecoop_get_tabs_info($oTabInfo, NULL, $oPLTabInfo, TRUE);

  $view = views_get_view('homecoop_cooporder_pickuplocation_products');  
  $view->preview=TRUE;
  $view->is_cacheable = FALSE;
  $view->init_display('default');  
  $view->pre_execute($arrParams);
    
  $content = array(
    'coopordertab' => array(
      'tab' => homecoop_tab_cooporder($oExtraData),
      '#weight' => 10,
     ),
    'pickuploctab' => array(
      'tab' => homecoop_tab_copickuploc($oExtraData),
      '#weight' => 11,
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