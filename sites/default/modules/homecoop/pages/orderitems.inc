<?php

function homecoop_page_orderitems() {
  homecoop_authenticated_page();
  
//  global $HomeCoopThemePath, $g_oMemberSession;
  
  $oRecord = new Order;
  $oTable = new OrderItems;

  if ( isset( $_GET['id'] ) ) {
    $oRecord->ID = intval($_GET['id']);
  }

  if (!$oRecord->LoadRecord( $oRecord->ID ) ) {
    drupal_goto(Consts::URL_ACCESS_DENIED);
    return;
  }
  
  if ( isset( $_GET['mode'] ) ) {
    $oTable->ProductsViewMode = intval($_GET['mode']);
    if ($oTable->ProductsViewMode != OrderItems::PRODUCTS_VIEW_MODE_ITEMS_ONLY &&
            $oTable->ProductsViewMode != OrderItems::PRODUCTS_VIEW_MODE_SHOW_ALL)
      $oTable->ProductsViewMode = OrderItems::PRODUCTS_VIEW_MODE_SHOW_ALL;
  }
    
  //even if mode is pre-set, if no products - set mode to all
  if ($oRecord->CoopTotal == 0) {
    $oTable->ProductsViewMode = OrderItems::PRODUCTS_VIEW_MODE_SHOW_ALL;
  }

  $oTable->SetOrder($oRecord);
  $oTable->LoadTable();
  
  switch($oTable->LastOperationStatus)
  {
    case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
    case SQLBase::OPERATION_STATUS_NO_PERMISSION:
    case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
    case SQLBase::OPERATION_STATUS_COORDINATION_GROUP_VERIFY_FAILED:
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  homecoop_add_js_file('orderitems.js');
  
  $oFormExtraData = homecoop_page_orderitems_prepareform($oRecord, $oTable);
  
  $arrContent = array(
    'orderitemsform' => drupal_get_form('homecoop_page_orderitems_form', $oFormExtraData),
  );
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $arrContent;
}

function homecoop_page_orderitems_prepareform(&$oRecord, &$oTable) {
  $bHasCoordPermission = $oRecord->HasPermission(SQLBase::PERMISSION_COORD);  
  $oPLTabInfo = new CoopOrderPickupLocationTabInfo( $oRecord->CoopOrderID, $oRecord->PickupLocationID, $oRecord->PickupLocationName, 
        CoopOrderPickupLocationTabInfo::PAGE_ORDERS );
  $oPLTabInfo->CoordinatingGroupID = $oRecord->PickupLocationGroupID;
  $oPLTabInfo->IsSubPage = TRUE;
  
  $oOrderTabInfo = new OrderTabInfo($oRecord->ID, OrderTabInfo::PAGE_ITEMS, $oRecord->CoopTotal, $oRecord->OrderCoopFee);
  $oOrderTabInfo->StatusObj = $oRecord->StatusObj;
  $oPercent = new CoopOrderCapacity($oRecord->MaxBurden, $oRecord->TotalBurden, $oRecord->MaxCoopTotal, $oRecord->CoopOrderCoopTotal,
      $oRecord->CoopOrderMaxStorageBurden, $oRecord->CoopOrderStorageBurden);
  if ($oPercent->SelectedType != CoopOrderCapacity::TypeNone)
    $oOrderTabInfo->Capacity = $oPercent->PercentRounded . '%';
  unset($oPercent);
  
  $oRecord->BuildPageTitle();
  drupal_set_title($oRecord->PageTitle);
  $oOrderTabInfo->MainTabName = $oRecord->PageTitleSuffix;
  $oTabInfo->CoordinatingGroupID = $oRecord->CoordinatingGroupID;
  $oTabInfo->ID = $oRecord->CoopOrderID;
  if ( $oTabInfo->CheckAccess() ) {
    $oTabInfo->Page = CoopOrderTabInfo::PAGE_ORDERS;
    $oTabInfo->IsSubPage = TRUE;
    $oTabInfo->Status = $oRecord->Status;
    $oTabInfo->CoopOrderTitle = $oRecord->CoopOrderName;
    $oTabInfo->CoopTotal = $oRecord->CoopOrderCoopTotal; 
  }
  
  if ( $oRecord->ItemsChangedByCoordinator ) {
    drupal_set_message(t('Some order items&#x27; quantities have been modified by a coordinator. The modified rows are marked in color and the original quantities are displayed in parenthesis'), 
            'warning', FALSE);
  }
  
  return array(
    'order' => $oRecord->GetAllProperties(),
    'hascoordpermission' => $bHasCoordPermission,

    'OriginalData' => $oTable->GetSerializedOriginalData(),
  ) + $oTable->GetAllProperties() 
    + homecoop_get_tabs_info($oTabInfo, $oOrderTabInfo, $oPLTabInfo, $bHasCoordPermission);
}

function homecoop_page_orderitems_form($form, &$form_state, $oFormExtraData) {
  global $g_oError;

  if (isset($form_state['homecoop_orderitems'])) {
    $oFormExtraData = $form_state['homecoop_orderitems'];
  }
  elseif (isset($oFormExtraData)) {
    $form_state['homecoop_orderitems'] = $oFormExtraData;
  }
  else  {
    return array();
  }
  
  $bHasCoordPermission = $oFormExtraData['hascoordpermission'];
  
  $form['#id'] = 'homecoop_page_orderitems_form';
  $form['#attributes']['name'] = 'homecoop_page_orderitems_form';
  $form['hidOriginalData'] = array('#type' => 'hidden', '#default_value' => $oFormExtraData['OriginalData'], 
    '#attributes' => array('id' => 'hidOriginalData'));
  $form['hidPostAction'] = array('#type' => 'hidden', '#default_value' => '', 
    '#attributes' => array('id' => 'hidPostAction'));
  /*$form['hidPostValue'] = array('#type' => 'hidden', '#default_value' => $oFormExtraData['ID'], 
    '#attributes' => array('id' => 'hidPostValue'));*/
}