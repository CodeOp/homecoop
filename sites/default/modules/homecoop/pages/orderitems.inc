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
  $form['hidOriginalData'] = array('#type' => 'hidden', '#default_value' => $oFormExtraData['OriginalData'], 
    '#attributes' => array('id' => 'hidOriginalData'));
  $form['hidPostAction'] = array('#type' => 'hidden', '#default_value' => '', 
    '#attributes' => array('id' => 'hidPostAction'));
  $form['hidDirty'] = array('#type' => 'hidden', '#default_value' => '0', 
    '#attributes' => array('id' => 'hidDirty'));
  $form['hidPostValue'] = array('#type' => 'hidden', '#default_value' => $oFormExtraData['order']['ID'], 
    '#attributes' => array('id' => 'hidPostValue'));
  
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
  
  if ($oRecord->CanModify) {
    $form['maintable']['buttons'] = array(
      '#weight' => 40,
      'btn_save' => array(
        '#type' => 'submit',
        '#name' => 'btn_save',
        '#id' => 'btn_save',
        '#submit' => array('homecoop_page_orderitems_form_submit'),
        '#value' => t('Save Ordered Products'),
        '#attributes' => array('class' => array('order'),
          ),
        '#prefix' => '<div class="inlineblock">',
        '#suffix' => '</div>',
        '#weight' => 10, 
      ),
      'selProductsView' => array(
        '#type' => 'select',
        '#name' => 'selProductsView',
        '#id' => 'selProductsView',
        '#key_type' => 'associative',
        '#options' => $oFormExtraData['arrProductsView'],
        '#default_value' => $oFormExtraData['ProductsViewMode'],
        '#prefix' => '<div class="inlineblock">',
        '#suffix' => '</div>',
        '#weight' => 20,
        '#required' => TRUE,
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
  }
  
  $bPrintedHeaders = false;
  $sJoinedItemsTooltipID = '';
  $bItemReadOnly = FALSE;
  
  
  /*
  foreach($arrItems as $oItem)
  {
      if (!$oItem->Visible)
        continue;

      $bItemReadOnly = $oItem->DisabledProduct || !$oRecord->CanModify;

      if ($oItem->InvalidEntry)
      {
        //show validation message
        echo '<div class="resgridrow"><span class="message">' , $oItem->ValidationMessage  , '</span></div>',
         '<div class="resgridrow orderiteminvalidrow">';
      }
      else if ($oItem->ChangedByCoordinator)
      {
        echo '<div class="resgridrow ';
        if ($oItem->DisabledProduct)
          echo 'orderitemcancelledrow" ';
        else
          echo 'changedrow" ';
        echo '>';
      }
      else if ($oItem->DisabledProduct)
        continue;
      else
        echo '<div class="resgridrow">';

      $oProductPackage = new ProductPackage($oItem->ProductItems, $oItem->ProductItemQuantity, 
                $oItem->ItemUnitAbbrev, $oItem->UnitInterval, $oItem->UnitAbbrev, $oItem->PackageSize, 
                $oItem->ProductQuantity, $oItem->ProductMaxCoopOrder, $oItem->ProductTotalCoopOrderQuantity,
           'tooltiphelp', 'ProductPackage' . $oItem->ProductID);

      //1. ProductName + link to product screen + hidden order item id to identify existing records
      echo '<div class="resgridcell">';
      HtmlDivTable::EchoTitle($bPrintedHeaders, 'Product');
      echo '<div class="resgriddatalong">';

      if ($oProductPackage->HasTooltip)
      {
        echo '<a class="tooltiphelprel" href="#" onclick="JavaScript:OpenProductOverview(\'' , $g_sRootRelativePath, '\', ',
              $oRecord->CoopOrderID, ',', $oItem->ProductID, ');" >', htmlspecialchars($oItem->ProductName), 
              '<span>';
        $oProductPackage->EchoTooltip();
        echo       '</span></a>';
      }
      else
        echo '<span class="link" onclick="JavaScript:OpenProductOverview(\'' , $g_sRootRelativePath, '\', ',
              $oRecord->CoopOrderID, ',', $oItem->ProductID, ');" >', htmlspecialchars($oItem->ProductName), '</span>';

      echo  '<input type="hidden" id="' , OrderItems::CTL_PREFIX_ID , $oItem->ProductID , '" name="' ,
                OrderItems::CTL_PREFIX_ID , $oItem->ProductID , '" value="' , $oItem->OrderItemID , '" />';

      echo  '</div></div>';

      //2. Producer
      $cellProducer = new HtmlGridCellText($oItem->ProducerName, HtmlGridCellText::CELL_TYPE_NORMAL);
      echo '<div class="resgridcell">';
      HtmlDivTable::EchoTitle($bPrintedHeaders, 'Producer');
      echo '<div class="resgriddatahlong">';
      echo $cellProducer->EchoHtml();
      echo "</div></div>";
      unset($cellProducer);

      //3. Product Package
      echo '<div class="resgridcell">';
      HtmlDivTable::EchoTitle($bPrintedHeaders, 'Quantity');
      echo '<div class="resgriddatashort">';
      $oProductPackage->SuppressTooltip = TRUE;
      $oProductPackage->EchoHtml();
      echo '</div></div>';

      //4. Coop Price
      echo '<div class="resgridcell">';
      HtmlDivTable::EchoTitle($bPrintedHeaders, 'Price');
      echo '<div class="resgriddatatiny">';
      echo $oItem->ProductCoopPrice , '</div>';
      echo '</div>';

      //5. Member Order
      $txtMemberOrder = new HtmlTextEditNumericRange(OrderItems::CTL_PREFIX_QUANTITY . $oItem->ProductID,
          'ltr', HtmlTextEdit::TEXTBOX, $oItem->Quantity, $oItem->GetAllowedInterval() );
      $txtMemberOrder->ReadOnly = $bItemReadOnly;
      $txtMemberOrder->MaxLength = HtmlTextEditNumeric::NUMBER_DEFAULT_MAX_LENGTH;
      $txtMemberOrder->CssClass = "orderitemqentry";
      $txtMemberOrder->OnChange = "JavaScript:SetDirty();";
      if ($oItem->ChangedByCoordinator)
      {
        $txtMemberOrder->SubsequentText = sprintf('&nbsp;(%.2F)', $oItem->MemberLastQuantity);
      }
      if ($oItem->ProductMaxUserOrder != NULL)
        $txtMemberOrder->MaxValue = $oItem->ProductMaxUserOrder;

      echo '<div class="resgridcell">';
      HtmlDivTable::EchoTitle($bPrintedHeaders, 'Order');
      echo '<div class="resgriddatatiny">';
      $txtMemberOrder->EchoHtml();
      echo '</div></div>';

      //6. Max Fix Addition
      echo '<div class="resgridcell">';
      echo '<div class="resgridtitle'; 
      if ($bPrintedHeaders)
        echo ' mobiledisplay';
      echo '"><a id="additionhlp_' , $oItem->ProductID ,'" name="additionhlp_' , 
        $oItem->ProductID ,'" class="tooltiphelp" href="#additionhlp_' , $oItem->ProductID ,
        '" >Add<span>The maximum quantity the cooperative order coordinator will be allowed to *add* to your order for completing partial orders to the package size. For instance, if a package size is 2lb, and you wish to order only 0.5lb, by entering 0.5lb in this field you may specify that you are ready to go up to 1lb.</span></a></div>';


      echo '<div class="resgriddatatiny">';

      if (  ($oItem->MemberMaxFixQuantityAddition != NULL && $oItem->MemberMaxFixQuantityAddition != 0)
        || Product::AllowsPartialOrders($oItem->ProductUnitID, $oItem->ProductQuantity, $oItem->UnitInterval, $oItem->PackageSize))
      {
        $txtMemberMaxFixQuantityAddition = new HtmlTextEditNumericRange(OrderItems::CTL_PREFIX_MAX_FIX_QUANTITY_ADDITION . $oItem->ProductID,
            'ltr', HtmlTextEdit::TEXTBOX, $oItem->MemberMaxFixQuantityAddition, $oItem->GetAllowedInterval() );
        $txtMemberMaxFixQuantityAddition->ReadOnly = $bItemReadOnly;
        $txtMemberMaxFixQuantityAddition->MaxLength = HtmlTextEditNumeric::NUMBER_DEFAULT_MAX_LENGTH;
        if ($oItem->PackageSize != NULL)
          $txtMemberMaxFixQuantityAddition->MaxValue = $oItem->PackageSize;
        else
          $txtMemberMaxFixQuantityAddition->MaxValue = $oItem->ProductQuantity;
        $txtMemberMaxFixQuantityAddition->CssClass = "orderitemqentry";
        $txtMemberMaxFixQuantityAddition->OnChange = "JavaScript:SetDirty();";

        $txtMemberMaxFixQuantityAddition->EchoHtml();
      }
      echo '</div></div>';

      //7. Total Price
      echo '<div class="resgridcell">';
      HtmlDivTable::EchoTitle($bPrintedHeaders, 'Total');
      echo '<div class="resgriddatatiny">';
      if ($oItem->JoinedItems > 0)
      {
        $fOriginalAmount = ($oItem->Quantity/$oItem->ProductQuantity) * $oItem->ProductCoopPrice;
        $fAmountSaved = $fOriginalAmount - $oItem->CoopTotal;

        $sJoinedItemsTooltipID = 'joinitemhlp_' . $oItem->OrderItemID;

        echo '<a id="', $sJoinedItemsTooltipID, '" name="', $sJoinedItemsTooltipID, '" class="tooltiphelprel" href="#', 
            $sJoinedItemsTooltipID, '" >',$oItem->CoopTotal,'<span>', 
              sprintf('%1$d items were joined to the product %2$s. As a result a sum of %3$s was saved.',$oItem->JoinedItems,
                   $oItem->JoinToProductName, $fAmountSaved),'</span></a>';
      }
      else
        echo $oItem->CoopTotal;

      echo '</div></div>';

      //8. Member Comments

      echo '<div class="resgridcell">';
      HtmlDivTable::EchoTitle($bPrintedHeaders, 'Comments');
      if ($oItem->DisabledProduct)
      {
        echo '<div class="resgriddatalong">This product is cancelled</div>';
      }
      else
      {
        echo '<div class="resgriddatalong">';
        $txtOrderItemComments = new HtmlTextEdit(OrderItems::CTL_PREFIX_COMMENTS . $oItem->ProductID,
          NULL, HtmlTextEdit::TEXTAREA, $oItem->MemberComments);
        $txtOrderItemComments->ReadOnly = $bItemReadOnly;
        $txtOrderItemComments->MaxLength = OrderItems::MAX_LENGTH_MEMBER_COMMENTS;
        $txtOrderItemComments->CssClass = "orderitemcentry";
        $txtOrderItemComments->Rows = 1;
        $txtOrderItemComments->OnChange = "JavaScript:SetDirty();";
        $txtOrderItemComments->EncloseInHtmlCell = FALSE;
        $txtOrderItemComments->EchoEditPartHtml();
        echo '</div>';
      }
      echo '</div>';

      echo '</div>';

      $bPrintedHeaders = true;
  }*/
  
  return $form;
}