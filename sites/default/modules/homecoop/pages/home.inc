<?php

function homecoop_page_front() {
  
  homecoop_authenticated_page();

  global $HomeCoopThemePath;
  
   $hcsettings = array(
    'ThemePath' => $HomeCoopThemePath,
   );
  
  drupal_add_js(array('homecoop' => $hcsettings), 'setting');
  
  homecoop_add_js_file('activeorders.js');
  homecoop_add_js_file('facet.js');
  
  try
  {
    $oNotifications = new Notifications;
    $oNotifications->DisplayNotifications();
    unset($oNotifications);
  }
  catch(Exception $e)
  {
    $g_oError->HandleException($e);
  }
  
  $arrContent = homecoop_page_front_prepare_form();
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $arrContent;
}

function homecoop_page_front_prepare_form() {
  homecoop_prepare_facet();
  
  $arrContent = array(
    '#prefix' => '<table cellspacing="0" cellpadding="0" width="100%"><tr>',
    'tdFacet' => array(
        '#prefix' => '<td id="tdFacet">',
        'facetform' => drupal_get_form('homecoop_page_front_form'),
        '#suffix' => '</td>',
      ),
    'tdMain' => array(
      '#prefix' => '<td id="tdMain">',
      'activeorders' => homecoop_activeorders(),
      '#suffix' => '</td>',
    ),
    '#suffix' => '</tr></table>',
  );
  
  return $arrContent;
}

function homecoop_page_front_form($form, &$form_state) {
  
  global $HomeCoopThemePath, $g_aMemberPickupLocationIDs, $g_aMemberPickupLocations, $g_nMemberPickupLocationsRemoved;
  global $g_aMemberProducerIDs, $g_aMemberProducers, $g_nMemberProducersRemoved;
  
  $form['#id'] = 'homecoop_page_front-form';
    
  $form['hidfacetmblexpandstate'] = array('#type' => 'hidden', '#default_value' => 0, '#attributes' => array('id' => 'hidfacetmblexpandstate'));
  $form['hidplfacetgrpexpandstate'] = array('#type' => 'hidden', '#default_value' => 0, '#attributes' => array('id' =>  'hidplfacetgrpexpandstate'));
  $form['hidprfacetgrpexpandstate'] = array('#type' => 'hidden', '#default_value' => 0, '#attributes' => array('id' =>  'hidprfacetgrpexpandstate'));
  $form['hidSelectedPLs'] = array('#type' => 'hidden', '#default_value' => '', '#attributes' => array('id' => 'hidSelectedPLs'));
  $form['hidSelectedPRs'] = array('#type' => 'hidden', '#default_value' => '', '#attributes' => array('id' => 'hidSelectedPRs'));
  $form['facet'] = array(
    '#prefix' => '<div id="divPLFacet" class="facet mobilehide">',
    '#suffix' => '</div>',
    'pltitle' => array(
        '#prefix' => '<span class="facettitle">',
        '#markup' => t('Pickup Locations'),
        '#suffix' => '</span>',
    ),
    'plbody' => array(
      '#prefix' => '<ul id="plfacetgrp" class="facetgrp">',
      '#suffix' => '</ul>',
      'body' => homecoop_RenderFacetList($g_aMemberPickupLocationIDs, $g_aMemberPickupLocations, $g_nMemberPickupLocationsRemoved, 
          'sPickupLocation', 'lipl_', 'hidplfacetgrpexpandstate'),
    ),
    'plexpand' => array(
        '#prefix' => '<div id="plfacetgrp_expand" class="facetexpander" onclick="JavaScript:TogglePLExpand();">',
        '#markup' => '<img id="imgPLFacetExpandArrow" src="' . $HomeCoopThemePath . 'img/arrow_down.gif"/>',
        '#suffix' => '</div>',
    ),
    'facetsep' => array(
        '#markup' => '<div class="facetsep"></div>',
    ),
    'prtitle' => array(
        '#prefix' => '<span class="facettitle">',
        '#markup' => t('Producers'),
        '#suffix' => '</span>',
    ),
    'prbody' => array(
      '#prefix' => '<ul id="prfacetgrp" class="facetgrp">',
      '#suffix' => '</ul>',
      'body' => homecoop_RenderFacetList($g_aMemberProducerIDs, $g_aMemberProducers, $g_nMemberProducersRemoved, 
          'sProducer', 'lipr_', 'hidprfacetgrpexpandstate'),
    ),
    'prexpand' => array(
        '#prefix' => '<div id="prfacetgrp_expand" class="facetexpander" onclick="JavaScript:TogglePRExpand();">',
        '#markup' => '<img id="imgPRFacetExpandArrow" src="' . $HomeCoopThemePath . 'img/arrow_down.gif"/>',
        '#suffix' => '</div>',
    ),
    'applyfilter' => array(
      '#type' => 'submit',
      '#id' => 'btnFilter',
      '#prefix' => '<div id="divFacetFilter">',
      '#suffix' => '</div>',
      '#submit' => array('homecoop_page_front_form_submit'),
      '#value' => t('Apply filter'),
      '#attributes' => array('class' => array('facetapply'),
        'disabled' => array('true'), 'onclick' => array('JavaScript:ApplyFacetFilter();')),
    ),
  );
  
  $form['#submit'][] = 'homecoop_page_front_form_submit';
  
  return $form;
}

function homecoop_page_front_form_submit($form, &$form_state) {
  global $g_oMemberPickupLocations, $g_oMemberProducers;
  $sSelectedPLS = '';
  $sSelectedPRS = '';
  $bFacetLoad = FALSE;
  if ( isset( $form_state['values']['hidSelectedPLs'] ) )
  {
      $sSelectedPLS = $form_state['values']['hidSelectedPLs'];
  
      if ($g_oMemberPickupLocations->ApplyFilter($sSelectedPLS))
        $bFacetLoad = TRUE;
  }
  
  if ( isset( $form_state['values']['hidSelectedPRs'] ) )
  {
      $sSelectedPRS = $form_state['values']['hidSelectedPRs'];
  
      if ($g_oMemberProducers->ApplyFilter($sSelectedPRS))
        $bFacetLoad = TRUE;
  }
  
  if ($bFacetLoad) {
    return homecoop_page_front_prepare_form();
  }
}

/*
 * Active Orders
 */
function homecoop_activeorders() {
  global $g_oMemberSession, $g_sRootRelativePath, $g_oTimeZone;
  //get active, in date, cooperative orders
  $oTable = new ActiveOrders;
  $recTable = NULL;
  $oPickUpLocs = NULL;
  $recPickupLoc = NULL;
  $oProducers = NULL;
  $recProducer = NULL;
  $nCountPickups = 0;
  $fBurden = 0;
  $dStart = NULL;
  $dEnd = NULL;
  $dDelivery = NULL;
  $oActiveOrderStatus = NULL;
  $sActiveOrderStatus = NULL;
  $sOrderCssClass = NULL;
  $sOrderBoxCssClass = NULL;
  $sHistoryButtonCssClass = '';
  $oCoopOrderCapacity = NULL;
  $oCoopOrderProducerCapacity = NULL;
  $oCoopOrderPickupCapacity = NULL;
  $oPermissions = NULL;
  $bCanCoord = FALSE;
  $sProducerSeparator = '';
  $bHasOrdersPermission = FALSE;
  $bHasProductsPermission = FALSE;
  $bHasExportPermission = FALSE;
  define('ORDER_DETAILS_ROWS', 2);
  
  $arrContent = array(
  );

  try {
    $recTable = $oTable->GetTable();

    if (!$oTable->HasPermission( SQLBase::PERMISSION_PAGE_ACCESS )) {
      return; //no permission to make orders
    }
      
    //this must be set here in order to pass parameter by reference and create it once before the while loop
    $arrCoordPermissions = array(ActiveOrders::PERMISSION_EDIT,  ActiveOrders::PERMISSION_VIEW);

    $arrContent['#prefix'] = '<table class="centerregion" cellspacing="0" ><tr><td><div id="activeOrdersCnt">';
    $arrContent['#suffix'] = '</div></td></tr></table>';

    //go through the active cooperative orders to output a "box" (html table with border) for each one
    while ( $recTable ) {
        $oPickUpLocs = new CoopOrderPickupLocations;
        $oProducers = new CoopOrderProducers;
        $recPickupLoc = $oPickUpLocs->LoadFacet($recTable["CoopOrderKeyID"], $g_oMemberSession->MemberID);
        $recProducer = $oProducers->LoadFacet($recTable["CoopOrderKeyID"], $g_oMemberSession->MemberID);
        //if this order is filtered out/blocked
        if (!$recPickupLoc || !$recProducer) {
          $recTable = $oTable->fetch();
          continue;
        }

        if (!$g_oMemberSession->IsOnlyMember) {
          $oPermissions = $oTable->GetCoordPermissions($recTable["CoordinatingGroupID"]);
          $bCanCoord = $oPermissions->HasPermissions( $arrCoordPermissions );
          $bHasOrdersPermission = $oPermissions->HasPermission(ActiveOrders::PERMISSION_ORDERS);
          $bHasProductsPermission = $oPermissions->HasPermission(ActiveOrders::PERMISSION_PRODUCTS);
          $bHasExportPermission = $oPermissions->HasPermission(ActiveOrders::PERMISSION_EXPORT);
        }

        $dDelivery = new DateTime($recTable["dDelivery"], $g_oTimeZone);
        $dStart = new DateTime($recTable["dStart"], $g_oTimeZone);
        $dEnd = new DateTime($recTable["dEnd"], $g_oTimeZone);
        $oActiveOrderStatus = new ActiveCoopOrderStatus($dEnd, $dDelivery, $recTable["nStatus"] );
        $sActiveOrderStatus = $oActiveOrderStatus->StatusName;

        $sHistoryButtonCssClass = '';

        $oCoopOrderCapacity = new CoopOrderCapacity($recTable["fMaxBurden"], $recTable["fBurden"], 
                $recTable["mMaxCoopTotal"], $recTable["mCoopTotal"],
                $recTable["fMaxStorageBurden"], $recTable["fStorageBurden"]);

        if ($recTable["nStatus"] == CoopOrder::STATUS_LOCKED) {
          $sOrderCssClass = ' class="closedorder" ';
          $sOrderBoxCssClass = ' class="orderbox closedorder" ';
        }
        else {
          switch($oActiveOrderStatus->Status) {
            case ActiveCoopOrderStatus::Open:
              $sOrderCssClass = ' class="openorder" ';
              $sOrderBoxCssClass = ' class="orderbox openorder" ';
              if ($oCoopOrderCapacity->Percent >= 100) //show order as open only if capacity is less then 100%
                $sActiveOrderStatus = '';
              break;
            case ActiveCoopOrderStatus::Closed:
              $sOrderCssClass = ' class="closedorder" ';
              $sOrderBoxCssClass = ' class="orderbox closedorder" ';
              $sHistoryButtonCssClass = ' HistoryButton';
              break;
            case ActiveCoopOrderStatus::Arrived:
              $sOrderCssClass = ' class="arrivedorder" ';
              $sOrderBoxCssClass = ' class="orderbox arrivedorder" ';
              $sHistoryButtonCssClass = ' HistoryButton';
             break;
            case ActiveCoopOrderStatus::ArrivingToday:
              $sOrderCssClass = ' class="arrivedorder" ';
              $sOrderBoxCssClass = ' class="orderbox arrivedorder" ';
              $sHistoryButtonCssClass = ' HistoryButton';
              break;
            default:
              $sOrderCssClass = '';
              $sOrderBoxCssClass = ' class="orderbox" ';
              $sHistoryButtonCssClass = ' HistoryButton';
              break;
          }
        }

        $arrOrderBox = array(
          '#prefix' => '<div '. $sOrderBoxCssClass. ' ><table cellpadding="0" cellspacing="0" width="100%">',
          '#suffix' => '</table></div>',
        );

        $arrOrderBox['ordertitle'] = array(
          '#prefix' => '<tr><td width="100%">',
          '#suffix' => '</td></tr>',
        );

        if ($bCanCoord) {
          if ($bHasOrdersPermission) {
            $arrOrderBox['ordertitle']['#markup'] = '<a class="LinkButton headdata' . $sHistoryButtonCssClass . '" href="' . 
                url('hccoord/orders', array('query' => array('coid' => $recTable["CoopOrderKeyID"]))) . '" >' . htmlspecialchars($recTable["sCoopOrder"]) . '</a>&nbsp;';
          }
          else {
            $arrOrderBox['ordertitle']['#markup'] = '<a class="LinkButton headdata' . $sHistoryButtonCssClass . '" href="' . 
                url('hccoord/cooporder', array('query' => array('coid' => $recTable["CoopOrderKeyID"])))  . '" >' . htmlspecialchars($recTable["sCoopOrder"]) . '</a>&nbsp;';
          }
        }
        else {
          $arrOrderBox['ordertitle']['#markup'] = htmlspecialchars($recTable["sCoopOrder"]);
        }

        $arrOrderBox['closingdate'] = array(
          '#prefix' => '<tr><td><div class="normalcolor" >',
          '#markup' => t('Closing‏:‏‎&nbsp;') . '</span><span '.
                 $sOrderCssClass . ' >&nbsp;' . $dEnd->format('n.j.Y') . '</div><div ' . $sOrderCssClass . ' >&nbsp;' .
              t('at&nbsp;') . $dEnd->format('g:i A'),
          '#suffix' => '</div></td></tr>',
        );

        $arrOrderBox['deliverydate'] = array(
          '#prefix' => '<tr><td><span class="normalcolor" >',
          '#markup' => t('Delivery‏: @date', array('@date' => LanguageSupport::LANGUAGE_DIRECTION_MARK . $dDelivery->format('n.j.Y'))),
          '#suffix' => '</span></td></tr>',
        );

        //row: order status, button + capacity
        $arrOrderStatusButtonCapacity = array(
          '#prefix' => '<tr><td ' . $sOrderCssClass . ' height="100%" ><div>',
          '#suffix' => '</div></td></tr>',
          'orderstatusandbutton' => array(
            '#prefix' => '<div>',
            '#suffix' => '</div>',
            'orderstatus' => array(
              '#prefix' => '<div>',
              '#markup' => $sActiveOrderStatus,
              '#suffix' => '</div>',
            ),
          ),
        );

        //existing order button
        if ($recTable["OrderID"] != NULL) {
          $arrOrderStatusButtonCapacity['orderstatusandbutton']['button'] = array(
            '#markup' => '<input type="button" id="btnOrder" class="order" value="' . t('My Order') . '" name="btnOrder" onclick="JavaScript:OpenOrder(\'' .
            $g_sRootRelativePath . '\',' . $recTable["OrderID"] . ');" />',
          );
        }
        //new order button
        else if ($oActiveOrderStatus->Status == ActiveCoopOrderStatus::Open && $oCoopOrderCapacity->Percent < 100) {
          $arrOrderStatusButtonCapacity['orderstatusandbutton']['button'] = array(
            '#markup' => '<input type="button" id="btnOrder" class="order" value="' . t('Order Now') . '" name="btnOrder" onclick="JavaScript:NewOrder(\'' .
            $g_sRootRelativePath . '\',' . $recTable["CoopOrderKeyID"] . ');" />',
          );
        }

        $arrOrderStatusButtonCapacity['capacity'] = array(
          '#prefix' => '<div class="capacitypercentcnt">',
          '#suffix' => '</div>',
        );

        if ($oCoopOrderCapacity->SelectedType != CoopOrderCapacity::TypeNone) { 
          $arrOrderStatusButtonCapacity['capacity'] = array(
            '#prefix' => '<span class="capacitypercent">' . $oCoopOrderCapacity->PercentRounded . 
                 '%</span><br/><span class="listareatitle">',
            '#markup' => t('Full'),
            '#suffix' => '</span>',
          );
        }
        
        $arrOrderBox['StatusButtonCapacity'] = $arrOrderStatusButtonCapacity;

        //row: pickup locations
        $arrPickupLocations = array(
          '#prefix' => '<tr><td><span class="listareatitle">' . t('Pickup:‎') . '</span><span class="normalcolor" >',
          '#suffix' => '</span></td></tr>',
        );

        $nCountRecs = 0;

        while($recPickupLoc) {
          $sPL = '';
          if ($nCountRecs > 0) {
            $sPL .= ',‎&nbsp';
          }

          $nCountRecs++;

           if ($bCanCoord && $oTable->CheckPickupLocationCoordPermissions($recPickupLoc["CoordinatingGroupID"])) {
             $sPL .= '<a class="LinkButton' . $sHistoryButtonCssClass . '" href="' .
                 url('hccoord/copickuplocorders', array('query' => array('coid' => $recTable["CoopOrderKeyID"],
                                                                          'plid' => $recPickupLoc["PickupLocationKeyID"]))) . '" >' . 
                 htmlspecialchars($recPickupLoc["sPickupLocation"]) . '</a>';
           }
           else {
            $sPL .= htmlspecialchars($recPickupLoc["sPickupLocation"]);
           }

           $oCoopOrderPickupCapacity = new CoopOrderCapacity($recPickupLoc["fMaxBurden"], $recPickupLoc["fBurden"], 
                                $recPickupLoc["mMaxCoopTotal"], $recPickupLoc["mCoopTotal"],
                                $recPickupLoc["fMaxStorageBurden"], $recPickupLoc["fStorageBurden"]);

           //% full
           if (HOME_PAGE_SHOW_PICKUP_LOCATION_CAPACITIES && $oCoopOrderPickupCapacity->SelectedType != CoopOrderCapacity::TypeNone) {
              $sPL .= LanguageSupport::AppendInFixedOrder('&nbsp;', '(' . $oCoopOrderPickupCapacity->PercentRounded . '%)');
           }

           $recPickupLoc = $oPickUpLocs->fetch();
           $arrPickupLocations['pl' . $recPickupLoc["PickupLocationKeyID"]] = array('#markup' => $sPL);
        }
        
        $arrOrderBox['pickuplocs'] = $arrPickupLocations;

        $nCountRecs = 0;

        //row: producers
        $arrProducers = array(
          '#prefix' => '<tr><td><span class="listareatitle">' . t('Producer:‎') . '</span><span class="normalcolor" >',
          '#suffix' => '</span></td></tr>',
        );

        while ( $recProducer )
        {        
          $sProducer = '';
          if ($nCountRecs > 0)
            $sProducer .= ',‎&nbsp';

          $nCountRecs++;

          if ($bCanCoord && $oTable->CheckProducerCoordPermissions($recPickupLoc["CoordinatingGroupID"]))
            $sProducer .= '<a class="LinkButton' . $sHistoryButtonCssClass . '" href="' .
              url('hccoord/coproducer', array('query' => array('coid' => $recTable["CoopOrderKeyID"],
                                                                'pid' => $recProducer["ProducerKeyID"]))) . '" >' . htmlspecialchars($recProducer["sProducer"]) . '</a>';
          else
            $sProducer .= htmlspecialchars($recProducer["sProducer"]);

          $oCoopOrderProducerCapacity = new CoopOrderCapacity(
                                $recProducer["fMaxBurden"], $recProducer["fBurden"], 
                                $recProducer["mMaxProducerOrder"], $recProducer["mProducerTotal"] );

          //% full
          if (HOME_PAGE_SHOW_PRODUCER_CAPACITIES && $oCoopOrderProducerCapacity->SelectedType != CoopOrderCapacity::TypeNone)
            $sProducer .= LanguageSupport::AppendInFixedOrder('&nbsp;', '(' . $oCoopOrderProducerCapacity->PercentRounded . '%)');

          $recProducer = $oProducers->fetch();
          $arrProducers['pr' . $recProducer["ProducerKeyID"]] = array('#markup' => $sProducer);
        }

        $arrOrderBox['producers'] = $arrProducers;

        //row: Coordinator extra links
        if ($bCanCoord)
        {
          $arrOrderBox['coordextra'] = array(
            '#prefix' => '<tr><td>',
            '#suffix' => '</td></tr>',
          );
          if ($bHasProductsPermission)
            $arrOrderBox['coordextra']['products']['#markup'] = '<a class="LinkButton headdata' . $sHistoryButtonCssClass .
              '" href="hccoord/coproducts?id=' . $recTable["CoopOrderKeyID"] . '" >' . t('Products') . '</a>&nbsp;';

          if ($bHasExportPermission)
            $arrOrderBox['coordextra']['export']['#markup'] = '<a class="LinkButton headdata' . $sHistoryButtonCssClass . 
              '" href="' . 
              url('hccoord/cooporderexport', array('query' => array('coid' => $recTable["CoopOrderKeyID"]))) . '" >' . t('Export') . '</a>';
        }
        
        $arrContent['orderbox' . $recTable["CoopOrderKeyID"]] = $arrOrderBox;

        $recTable = $oTable->fetch();
    }
  }
  catch(Exception $eao)
  {
    $g_oError->HandleException($eao);
  }
  
  return $arrContent;
}

/* 
 * facet filter
 */
function homecoop_prepare_facet() {
  //prepare facet data
  homecoop_prepare_pickup_facet();
  homecoop_prepare_producer_facet();
}



function homecoop_RenderFacetList(&$aFacetIDs, &$aFacet, &$nFacetRemoved, $sNameField, $sListItemIDPrefix, $sStateID)
{
  $arrContent = array();
  $nIndex = 0;
  $nRemoved = 0;
  $nLenSelected = count($aFacetIDs);
  foreach($aFacet as $ID => $Data)
  {
    if ($Data['bBlocked'] || $Data['bDisabled'])     
      continue;
    
    $sPrefix = '<li id="' .  $sListItemIDPrefix . $ID . '" onclick="JavaScript:ToggleItemSelect(\''
        . $sListItemIDPrefix . $ID . '\' , \'' . $sStateID . '\');" class="facetitm';
    
    if ($Data['bRemoved'])
    {
      $nRemoved++;
      
      if ($nRemoved == 1)
        $sPrefix .= ' firstfacet';
      if ($nRemoved == $nFacetRemoved)
        $sPrefix .= ' lastfacet';
      
      $sPrefix .= ' unselectedfacet';
    }
    else
    {
      $nIndex++;
      if ($nIndex == 1)
        $sPrefix .= ' firstfacet';
      if ($nIndex == $nLenSelected)
        $sPrefix .= ' lastfacet';
    }
    
    $sPrefix .= '">';
    
    $arrContent[$sListItemIDPrefix . $ID] = array(
      '#prefix' => $sPrefix,
      '#markup' => htmlspecialchars($Data[$sNameField]),
      '#suffix' => '</li>' );
  }
  
  return $arrContent;
}