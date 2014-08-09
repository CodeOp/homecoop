<?php

function homecoop_page_coproducts() {
  global $g_oMemberSession, $language;
  
  homecoop_authenticated_page();
   
  $oData = new CoopOrderProducts;
  $oTabInfo = new CoopOrderTabInfo;
  $bReadOnly = FALSE;
  $oTabInfo->Page = CoopOrderTabInfo::PAGE_PRODUCTS;
  
  if (isset($_GET['id']))
    $oData->CoopOrderID = intval($_GET['id']);
  
  if ($oData->CoopOrderID <= 0)
  {
     drupal_goto(Consts::URL_ACCESS_DENIED);
     return;
  }
  
  if (!$oData->LoadData()) {
    drupal_goto(Consts::URL_ACCESS_DENIED);
    return;
  }
  
  switch($oData->LastOperationStatus)
  {
    case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
    case SQLBase::OPERATION_STATUS_NO_PERMISSION:
    case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
    case SQLBase::OPERATION_STATUS_COORDINATION_GROUP_VERIFY_FAILED:
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  drupal_set_title(t('@name - Products', array('@name' => $oData->Name)));
  
  $oTabInfo->ID = $oData->CoopOrderID;
  $oTabInfo->CoopOrderTitle = $oData->Name;
  $oTabInfo->Status = $oData->Status;
  $oTabInfo->CoordinatingGroupID = $oData->CoordinatingGroupID;
  $oTabInfo->StatusObj = new ActiveCoopOrderStatus($oData->End, $oData->Delivery, $oData->Status);
  $oTabInfo->CoopTotal = $oData->CoopOrderCoopTotal; 
  $oPercent = new CoopOrderCapacity($oData->CoopOrderMaxBurden, $oData->CoopOrderBurden, $oData->CoopOrderMaxCoopTotal, $oData->CoopOrderCoopTotal,
      $oData->CoopOrderMaxStorageBurden, $oData->CoopOrderStorageBurden);
  if ($oPercent->SelectedType != CoopOrderCapacity::TypeNone)
    $oTabInfo->Capacity = $oPercent->PercentRounded . '%';
  unset($oPercent);

  if (!$oData->HasPermission(CoopOrderProducts::PERMISSION_COOP_ORDER_PRODUCT_EDIT)) {
    $bReadOnly = TRUE;
  }
  else if ($oData->Status != CoopOrder::STATUS_ACTIVE 
          && $oData->Status != CoopOrder::STATUS_DRAFT
          && $oData->Status != CoopOrder::STATUS_LOCKED )
  {
    $bReadOnly = TRUE;
    drupal_set_message(t('Cooperative order cannot be updated at its current status'), 'warning');
  }
  
  //args: id, read-write/read-only, languageX3, coordinating groups
  $arrParams = array(
    $oData->CoopOrderID,
    $bReadOnly? 'ro' : 'rw',
    $language->language,
    $language->language,
    $language->language,
  );
  
  if ( $oData->GetPermissionScope(CoopOrderProducts::PERMISSION_COOP_ORDER_PRODUCT_EDIT) != Consts::PERMISSION_SCOPE_COOP_CODE 
      && $oData->GetPermissionScope(CoopOrderProducts::PERMISSION_COOP_ORDER_PRODUCT_VIEW) != Consts::PERMISSION_SCOPE_COOP_CODE) {
    $arrParams[] = implode("+", $g_oMemberSession->Groups);
  }
  
  $oExtraData = homecoop_get_tabs_info($oTabInfo, NULL, NULL, TRUE);

  $view = views_get_view('homecoop_cooporder_products');
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