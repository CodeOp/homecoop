<?php

function homecoop_page_coord_orders() {
  homecoop_authenticated_page();
  
  $oData = new Orders;
  
  if (isset($_GET['coid'])) {
    $oData->CoopOrderID = intval($_GET['coid']);
  }
  
  $oData->LoadDataByCoopOrder();
  $oTabInfo = new CoopOrderTabInfo;
  $oTabInfo->Page = CoopOrderTabInfo::PAGE_ORDERS;
  
  switch($oData->LastOperationStatus)
  {
    case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
    case SQLBase::OPERATION_STATUS_NO_PERMISSION:
    case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
    case SQLBase::OPERATION_STATUS_COORDINATION_GROUP_VERIFY_FAILED:
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }

  drupal_set_title(t('@ordername - Member Orders', array('@ordername' => $oData->Name)));
  
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
  
  $bReadOnly = ($oData->Status != CoopOrder::STATUS_ACTIVE 
          && $oData->Status != CoopOrder::STATUS_DRAFT
          && $oData->Status != CoopOrder::STATUS_LOCKED );
  
  $oExtraData = homecoop_get_tabs_info($oTabInfo, NULL, NULL, TRUE);
  
  $view = views_get_view('homecoop_cooporder_orders');
  
  $view->preview=TRUE;
  $view->is_cacheable = FALSE;
  $view->init_display('default');  
  $view->pre_execute(array($oData->CoopOrderID, $bReadOnly));
  
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