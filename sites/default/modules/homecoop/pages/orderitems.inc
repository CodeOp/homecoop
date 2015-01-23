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
  
  $hcsettings = array(
    'ConfirmChanges' => t('It seems you have made changes and did not save them. If you proceed in changing the products view mode, these changes will be lost. Proceed?'),
    'PostActionViewChange' => OrderItems::POST_ACTION_SWITCH_VIEW_MODE,
    'PostActionShowAll' => OrderItems::PRODUCTS_VIEW_MODE_SHOW_ALL,
    'PostActionItemOnly' => OrderItems::PRODUCTS_VIEW_MODE_ITEMS_ONLY,
  );
  
  drupal_add_js(array('homecoop' => $hcsettings), 'setting');
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
  $oTabInfo = new CoopOrderTabInfo;
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
  
  $arrProductsView = array(
    OrderItems::PRODUCTS_VIEW_MODE_SHOW_ALL => t('All Products'),
    OrderItems::PRODUCTS_VIEW_MODE_ITEMS_ONLY => t('Ordered Products'),
  );
  
  return array(
    'order' => $oRecord->GetAllProperties(),
    'hascoordpermission' => $bHasCoordPermission,
    'arrProductsView' => $arrProductsView,
    'OriginalData' => $oTable->GetSerializedOriginalData(),
  ) + $oTable->GetAllProperties() 
    + homecoop_get_tabs_info($oTabInfo, $oOrderTabInfo, $oPLTabInfo, $bHasCoordPermission);
}

function homecoop_page_orderitems_form($form, &$form_state, $oFormExtraData) {
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
  //internal values
  $form['hidOriginalData'] = array('#type' => 'value', '#value' => $oFormExtraData['OriginalData'], 
    '#attributes' => array('id' => 'hidOriginalData'));
  $form['hidPostValue'] = array('#type' => 'value', '#value' => $oFormExtraData['order']['ID'], 
    '#attributes' => array('id' => 'hidPostValue'));
  //exposed values
  $form['hidPostAction'] = array('#type' => 'hidden', '#default_value' => '', 
    '#attributes' => array('id' => 'hidPostAction'));
  $form['hidDirty'] = array('#type' => 'hidden', '#default_value' => '0', 
    '#attributes' => array('id' => 'hidDirty'));
  
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
    'controlstable' => array(
      '#weight' => 50,
      '#prefix' => '<div class="resgridparent">',
      '#suffix' => '</div>',
    ),
  );
  
  if ($oFormExtraData['order']['CanModify']) {
    $form['maintable']['buttons'] = array(
      '#weight' => 40,
      'btn_save' => array(
        '#type' => 'submit',
        '#name' => 'btn_save',
        '#id' => 'btn_save',
        '#submit' => array('homecoop_page_orderitems_form_submit'),
        '#value' => t('Save Ordered Products'),
        '#attributes' => array('onclick' => 'Save();',  'class' => array('order'),
          ),
        '#prefix' => '<div class="inlineblock">',
        '#suffix' => '&nbsp;</div>',
        '#weight' => 10, 
      ),
      'selProductsView' => array(
        '#type' => 'select',
        '#name' => 'selProductsView',
        '#id' => 'selProductsView',
        '#key_type' => 'associative',
        '#options' => $oFormExtraData['arrProductsView'],
        '#default_value' => $oFormExtraData['ProductsViewMode'], //re-setting the actual value of this control
        '#prefix' => '<div class="inlineblock">',
        '#suffix' => '</div>',
        '#weight' => 20,
        '#required' => TRUE,
        '#attributes' => array(
          'onchange' => 'SwitchViewMode();',
          'id' => 'selProductsView',
        ),
      ),
    );
  }
  
  if (!isset($oFormExtraData['OrderItems']) || !is_array($oFormExtraData['OrderItems']) || count($oFormExtraData['OrderItems']) == 0) {
    $form['maintable']['controlstable']['norecords'] = array(
      '#prefix' => '<div class="norecords">',
      '#markup' => t('No records.'),
      '#suffix' => '</div>',
      '#weight' => 10,
    );
    
    return $form;
  }
  
  $bPrintedHeaders = false;
  $sJoinedItemsTooltipID = '';
  $bItemReadOnly = FALSE;  
  $nRowWeight = 20;
  $sRow = '';
  $sClass = '';
  $sName = '';
  $sUrl = '';
  
  foreach($oFormExtraData['OrderItems'] as $oItem)
  {
      if (!$oItem['Visible'])
        continue;
      
      $sRow = 'row' . $oItem['ProductID'];

      $bItemReadOnly = $oItem['DisabledProduct'] || !$oFormExtraData['order']['CanModify'];

      if ($oItem['InvalidEntry'])
      {
        //show validation message
        $form['maintable']['controlstable']['validationmessage'] = array(
          '#prefix' => '<div class="resgridrow"><span class="message">',
          '#markup' => $oItem['ValidationMessage'],
          '#suffix' => '</span></div>',
          '#weight' => 10,
        );
        //set row class
        $form['maintable']['controlstable'][$sRow] = array(
          '#prefix' => '<div class="resgridrow orderiteminvalidrow">',
          '#suffix' => '</div>',
          '#weight' => $nRowWeight,
        );
      }
      else if ($oItem['ChangedByCoordinator'])
      {
        $sClass = 'resgridrow ';
        if ($oItem['DisabledProduct']) {
          $sClass .= 'orderitemcancelledrow';
        }
        else {
          $sClass .= 'changedrow';
        }
        $form['maintable']['controlstable'][$sRow] = array(
          '#prefix' => '<div class="' . $sClass . '">',
          '#suffix' => '</div>',
          '#weight' => $nRowWeight,
        );
      }
      else if ($oItem['DisabledProduct']) {
        continue;
      }
      else {
        $form['maintable']['controlstable'][$sRow] = array(
          '#prefix' => '<div class="resgridrow">',
          '#suffix' => '</div>',
          '#weight' => $nRowWeight,
        );
      }

      $oProductPackage = new ProductPackage($oItem['ProductItems'], $oItem['ProductItemQuantity'], 
                $oItem['ItemUnitAbbrev'], $oItem['UnitInterval'], $oItem['UnitAbbrev'], $oItem['PackageSize'], 
                $oItem['ProductQuantity'], $oItem['ProductMaxCoopOrder'], $oItem['ProductTotalCoopOrderQuantity'],
           'tooltiphelp', 'ProductPackage' . $oItem['ProductID']);

      //1. ProductName + link to product screen + hidden order item id to identify existing records
      $form['maintable']['controlstable'][$sRow]['product'] = array(
        '#prefix' => '<div class="resgridfirstcell">',
        '#suffix' => '</div>',
        '#weight' => 10,
      );
      
      $sClass = 'resgridtitle';
      if ($bPrintedHeaders)
        $sClass .= ' mobiledisplay';
      
      $form['maintable']['controlstable'][$sRow]['product']['title'] = array(
        '#prefix' => '<div class="' . $sClass . '">',
        '#markup' => t('Product'),
        '#suffix' => '</div>',
        '#weight' => 10,
      );
      
      $form['maintable']['controlstable'][$sRow]['product']['data'] = array(
        '#prefix' => '<div class="resgriddatalong">',
        '#suffix' => '</div>',
        '#weight' => 20,
      );
      
      $sUrl = url('hcproduct', array('query' => array(
              'prd' => $oItem['ProductID'], 'coid' => $oFormExtraData['order']['CoopOrderID'],
            )));
      if ($oProductPackage->HasTooltip) {
        $form['maintable']['controlstable'][$sRow]['product']['data']['link'] = array(
          '#prefix' => '<a class="tooltiphelprel" href="#" onclick="JavaScript:OpenProductOverview(\'' . $sUrl . '\');" >',
          '#markup' => check_plain($oItem['ProductName']) . '<span>' . $oProductPackage->Tooltip . '</span>',
          '#suffix' => '</a>',
        );
      }
      else {
        $form['maintable']['controlstable'][$sRow]['product']['data']['link'] = array(
          '#prefix' => '<span class="link" onclick="JavaScript:OpenProductOverview(\'' . $sUrl . '\');" >',
          '#markup' => check_plain($oItem['ProductName']),
          '#suffix' => '</span>',
        );
      }
       
      //internal orderitem id
      $sName = OrderItems::CTL_PREFIX_ID . $oItem['ProductID'];
      $form['maintable']['controlstable'][$sRow][$sName] = array('#type' => 'value', '#value' => $oItem['OrderItemID'], 
       '#attributes' => array('id' => $sName));
      
      
      //2. Producer
      $cellProducer = new HtmlGridCellText($oItem['ProducerName'], HtmlGridCellText::CELL_TYPE_NORMAL);      
      $form['maintable']['controlstable'][$sRow]['producer'] = array(
        '#prefix' => '<div class="resgridcell">',
        'title' => array(
          '#prefix' => '<div class="' . $sClass . '">',
          '#markup' => t('Producer'),
          '#suffix' => '</div>',
        ),
        'data' => array(
          '#prefix' => '<div class="resgriddatahlong">',
          'producermarkup' => $cellProducer->GetHtml(),
          '#suffix' => '</div>',
        ),
        '#suffix' => '</div>',
        '#weight' => 20,
      );
      unset($cellProducer);

      //3. Product Package
      $oProductPackage->SuppressTooltip = TRUE;
      $form['maintable']['controlstable'][$sRow]['productpackage'] = array(
        '#prefix' => '<div class="resgridcell">',
        'title' => array(
          '#prefix' => '<div class="' . $sClass . '">',
          '#markup' => t('Quantity'),
          '#suffix' => '</div>',
        ),
        'data' => array(
          '#prefix' => '<div class="resgriddatashort">',
          '#markup' => $oProductPackage->Html,
          '#suffix' => '</div>',
        ),
        '#suffix' => '</div>',
        '#weight' => 30,
      );
      
      //4. Coop Price
      $form['maintable']['controlstable'][$sRow]['price'] = array(
        '#prefix' => '<div class="resgridcell">',
        'title' => array(
          '#prefix' => '<div class="' . $sClass . '">',
          '#markup' => t('Price'),
          '#suffix' => '</div>',
        ),
        'data' => array(
          '#prefix' => '<div class="resgriddatatiny">',
          '#markup' => $oItem['ProductCoopPrice'],
          '#suffix' => '</div>',
        ),
        '#suffix' => '</div>',
        '#weight' => 40,
      );
      
      //5. Member Order
      $txtMemberOrder = new HtmlTextEditNumericRange(OrderItems::CTL_PREFIX_QUANTITY . $oItem['ProductID'],
          'ltr', HtmlTextEdit::TEXTBOX, $oItem['Quantity'], $oItem['allowedinterval'] );
      $txtMemberOrder->ReadOnly = $bItemReadOnly;
      $txtMemberOrder->MaxLength = HtmlTextEditNumeric::NUMBER_DEFAULT_MAX_LENGTH;
      $txtMemberOrder->CssClass = "orderitemqentry";
      $txtMemberOrder->OnChange = "JavaScript:SetDirty();";
      if ($oItem['ChangedByCoordinator']) {
        $txtMemberOrder->SubsequentText = sprintf('&nbsp;(%.2F)', $oItem['MemberLastQuantity']);
      }
      if ($oItem['ProductMaxUserOrder'] != NULL) {
        $txtMemberOrder->MaxValue = $oItem['ProductMaxUserOrder'];
      }
      
      $form['maintable']['controlstable'][$sRow]['memberorder'] = array(
        '#prefix' => '<div class="resgridcell">',
        'title' => array(
          '#prefix' => '<div class="' . $sClass . '">',
          '#markup' => t('Order'),
          '#suffix' => '</div>',
        ),
        'data' => array(
          '#prefix' => '<div class="resgriddatatiny">',
          'orderbox' => $txtMemberOrder->GetHtml(),
          '#suffix' => '</div>',
        ),
        '#suffix' => '</div>',
        '#weight' => 50,
      );

      //6. Max Fix Addition
      $form['maintable']['controlstable'][$sRow]['addition'] = array(
        '#prefix' => '<div class="resgridcell">',
        'title' => array(
          '#prefix' => '<div class="' . $sClass . '">',
          'tooltip' => array(
            '#prefix' => '<a id="additionhlp_' . $oItem['ProductID'] . '" name="additionhlp_' .
              $oItem['ProductID'] . '" class="tooltiphelp" href="#additionhlp_' . $oItem['ProductID'] . '" >',
            '#markup' => t('Add') . '<span>' . 
              t('The maximum quantity the cooperative order coordinator will be allowed to *add* 
                to your order for completing partial orders to the package size. For instance, 
                if a package size is 2lb, and you wish to order only 0.5lb, 
                by entering 0.5lb in this field you may specify that you are ready to go up to 1lb.') . '</span>',
            '#suffix' => '</a>',
          ),
          '#suffix' => '</div>',
        ),
        'data' => array(
          '#prefix' => '<div class="resgriddatatiny">',
          '#suffix' => '</div>',
        ),
        '#suffix' => '</div>',
        '#weight' => 60,
      );
      
      if (  ($oItem['MemberMaxFixQuantityAddition'] != NULL && $oItem['MemberMaxFixQuantityAddition'] != 0)
        || Product::AllowsPartialOrders($oItem['ProductUnitID'], $oItem['ProductQuantity'], $oItem['UnitInterval'], $oItem['PackageSize'])) {
        $txtMemberMaxFixQuantityAddition = new HtmlTextEditNumericRange(OrderItems::CTL_PREFIX_MAX_FIX_QUANTITY_ADDITION . $oItem['ProductID'],
            'ltr', HtmlTextEdit::TEXTBOX, $oItem['MemberMaxFixQuantityAddition'], $oItem['allowedinterval'] );
        $txtMemberMaxFixQuantityAddition->ReadOnly = $bItemReadOnly;
        $txtMemberMaxFixQuantityAddition->MaxLength = HtmlTextEditNumeric::NUMBER_DEFAULT_MAX_LENGTH;
        if ($oItem['PackageSize'] != NULL)
          $txtMemberMaxFixQuantityAddition->MaxValue = $oItem['PackageSize'];
        else
          $txtMemberMaxFixQuantityAddition->MaxValue = $oItem['ProductQuantity'];
        $txtMemberMaxFixQuantityAddition->CssClass = "orderitemqentry";
        $txtMemberMaxFixQuantityAddition->OnChange = "JavaScript:SetDirty();";
        
        $form['maintable']['controlstable'][$sRow]['addition']['data']['additionbox'] = 
            $txtMemberMaxFixQuantityAddition->GetHtml();
      }
      
      //7. Total Price
      $form['maintable']['controlstable'][$sRow]['totalprice'] = array(
        '#prefix' => '<div class="resgridcell">',
        'title' => array(
          '#prefix' => '<div class="' . $sClass . '">',
          '#markup' => t('Total'),
          '#suffix' => '</div>',
        ),
        'data' => array(
          '#prefix' => '<div class="resgriddatatiny">',
          '#suffix' => '</div>',
        ),
        '#suffix' => '</div>',
        '#weight' => 70,
      );
      
      if ($oItem['JoinedItems'] > 0) {
        $fOriginalAmount = ($oItem['Quantity']/$oItem['ProductQuantity']) * $oItem['ProductCoopPrice'];
        $fAmountSaved = $fOriginalAmount - $oItem['CoopTotal'];

        $sJoinedItemsTooltipID = 'joinitemhlp_' . $oItem['OrderItemID'];

        $form['maintable']['controlstable'][$sRow]['totalprice']['data']['totallink'] = array(
          '#prefix' => '<a id="' . $sJoinedItemsTooltipID . '" name="'. $sJoinedItemsTooltipID . '" class="tooltiphelprel" href="#' .
          $sJoinedItemsTooltipID . '" >',
          '#markup' => $oItem['CoopTotal'] . '<span>' . 
          t('@itemsjoined items were joined to the product @product. As a result a sum of @sum was saved.', 
              array('@itemsjoined' => $oItem['JoinedItems'], '@product' => $oItem['JoinToProductName'], '@sum' => $fAmountSaved)) . '</span>',
          '#suffix' => '</a>',
        );
      }
      else {
        $form['maintable']['controlstable'][$sRow]['totalprice']['data']['#markup'] = $oItem['CoopTotal'];
      }
      
      //8. Member Comments
      $form['maintable']['controlstable'][$sRow]['comments'] = array(
        '#prefix' => '<div class="resgridcell">',
        'title' => array(
          '#prefix' => '<div class="' . $sClass . '">',
          '#markup' => t('Comments'),
          '#suffix' => '</div>',
        ),
        'data' => array(
          '#prefix' => '<div class="resgriddatalong">',
          '#suffix' => '</div>',
        ),
        '#suffix' => '</div>',
        '#weight' => 80,
      );
      
      
      if ($oItem['DisabledProduct']) {
        $form['maintable']['controlstable'][$sRow]['comments']['data']['#markup'] = t('This product is cancelled');
      }
      else {
        $sName = OrderItems::CTL_PREFIX_COMMENTS . $oItem['ProductID'];
        $form['maintable']['controlstable'][$sRow]['comments']['data'][$sName] = array(
          '#type' => 'textarea',
          '#max_length' => OrderItems::MAX_LENGTH_MEMBER_COMMENTS,
          '#rows' => 1,
          '#name' => $sName,
          '#id' => $sName,
          '#default_value' => check_plain($oItem['MemberComments']),
          '#disabled' => $bItemReadOnly,
          '#weight' => 80,
          '#attributes' => array('placeholder' => t('Any comments?'),
            'onchange' => 'JavaScript:SetDirty();',
            'class' => array('orderitemcentry')),
        );        
      }

      $bPrintedHeaders = true;
      $nRowWeight += 10;
  }
  
  return $form;
}

function homecoop_page_orderitems_form_submit($form, &$form_state) {
  $oRecord = new Order;
  $oTable = new OrderItems;
  
  if ( isset( $form_state['values']['hidPostValue'] ) && !empty($form_state['values']['hidPostValue']) )
    $oRecord->ID = intval($form_state['values']['hidPostValue']);

  if ( isset( $form_state['values']['hidOriginalData'] ) )
    $oTable->SetSerializedOriginalData( $form_state['values']["hidOriginalData"] );

  $oRecord->SuppressMessages = TRUE; //so messages won't displayed twice
  //get order for permissions check
  if (!$oRecord->LoadRecord( $oRecord->ID ) )
  {
    drupal_goto(Consts::URL_ACCESS_DENIED );
    return;
  }

  $oTable->SetOrder($oRecord);

  if ( isset( $form_state['values']['selProductsView'] ) ) {
    $oTable->ProductsViewMode = intval($form_state['values']['selProductsView']);
  }
  $nMode = $oTable->ProductsViewMode;

  if (!$oRecord->CanModify)
    $oTable->ProductsViewMode = OrderItems::PRODUCTS_VIEW_MODE_ITEMS_ONLY;
  
  if ($form_state['values']['hidPostAction'] == OrderItems::POST_ACTION_SWITCH_VIEW_MODE) {
    homecoop_page_orderitems_post_submit_reload($form_state, $oRecord, $oTable);
    return;
  }
  
  $bSuccess = $oTable->Save($form_state);  
  
  //if mode has changed regardless of user's choice, set its value on load
  if ($nMode != $oTable->ProductsViewMode) {
    drupal_add_js('jQuery(document).ready(function () { document.getElementById("selProductsView").selectedIndex = ' . 
        $oTable->ProductsViewMode . '; });', 'inline');
  }

  //always reload order record after save (but suppress messages)
  $oRecord->LoadRecord( $oRecord->ID );

  if ($bSuccess) {
    drupal_set_message('Ordered products were saved successfully.', 'status', FALSE);
    homecoop_page_orderitems_post_submit_reload($form_state, $oRecord, $oTable);
  }
  else {
    $form_state['homecoop_orderitems'] = homecoop_page_orderitems_prepareform($oRecord, $oTable);
    $form_state['rebuild'] = true;    
  }
}

function homecoop_page_orderitems_post_submit_reload(&$form_state, &$oRecord, &$oTable) {
  //always reload table to get latest storage areas values
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
  
  $form_state['homecoop_orderitems'] = homecoop_page_orderitems_prepareform($oRecord, $oTable);
  $form_state['rebuild'] = true;
}