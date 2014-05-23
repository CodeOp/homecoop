<?php

function homecoop_header_block() {
  $HelloMessage = '';
  $sBalance = '';
  $sBalanceLink = '';

  homecoop_include_app_file('settings');
  
  global $HomeCoopThemePath;
  global $g_oMemberSession;
  
  $bIsAuthenticated = homecoop_check_if_authenticated();

  if ($bIsAuthenticated) {
    //display balance if different than zero or payment method is not at pickup
    if ($g_oMemberSession->Balance != 0 || $g_oMemberSession->PaymentMethod != Consts::PAYMENT_METHOD_AT_PICKUP) {
      $sBalance = $g_oMemberSession->Balance;
      $HelloMessage .= t('Your balance: @balance', array('@balance' => $g_oMemberSession->Balance));

      if ($g_oMemberSession->Balance != $g_oMemberSession->BalanceHeld) {
        $HelloMessage .= ' ' . t('‎(in cachier: @balanceheld)‎', array('@balanceheld' => $g_oMemberSession->BalanceHeld));
      }

      $mMaxOrder = $g_oMemberSession->GetMaxOrder();
      if ($mMaxOrder != NULL && $mMaxOrder != $g_oMemberSession->Balance) { //if not payment at pickup
        $HelloMessage .= ' ' . t('Max. Order: @maxorder', array('@maxorder' => $mMaxOrder));
      }
    }

    if ($sBalance != '') {
        $sBalanceLink = '<a class="tooltiphelp mobilemenu balancelink" href="#"><img border="0" src="' . 
            $HomeCoopThemePath . 'img/emblem-money.png" class="homecoop-emblem-money"/>‎' . $sBalance;
    }

    $sBalanceLink .= '<span>' . $HelloMessage . '</span>';
    if ($sBalance != '') {
      $sBalanceLink .=  '</a>';
    }
  }
  
  $arrContent = array(
    '#prefix' => '<table cellspacing="0" cellpadding="0" class="fullwidth">',
    'markup' => array ('#markup' => '<form class="homecoop_header_form" name="frmhcheader" id="frmhcheader" target="_self" method="post" accept-charset="UTF-8">' . 
      '<input type="hidden" id="hidLogout" name="hidLogout" /></form>'),
    '#suffix' => '</table>',
  );
  
  $hc_mobile_menu = array(
        '#prefix' => '<tr class="mobiledisplay"><td><a id="tglUser" class="nav-toggle"></a></td>',
        '#suffix' => '</tr>',
      );
  
  if ($bIsAuthenticated) { 
    $hc_mobile_menu['markup']['#prefix'] = '<td>';
    if (!$g_oMemberSession->IsOnlyMember ) {
      $hc_mobile_menu['markup']['#markup'] = '<a id="tglCoord" class="nav-toggle"></a>';
    }
    $hc_mobile_menu['markup']['#suffix'] = '</td>';

    $hc_header_addition = array(
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    if (current_path() == 'hcfront') {
      $hc_header_addition['markup']['#prefix'] = '<a href="#" class="facetmobileexpander mobiledisplay" onclick="JavaScript:ToggleMobileExpand();">';
      $hc_header_addition['markup']['#markup'] = '<img alt="' . t('Pickup Locations') . 
          '" id="imgFacetMobileExpandArrow" src="' . $HomeCoopThemePath . 'img/filter.png"/>';
      $hc_header_addition['markup']['#suffix'] = '</a>';
    }
    
    $hc_mobile_menu['hc_header_addition'] = $hc_header_addition;
    
    $hc_mobile_menu['hc_balance_link'] = array(
      '#prefix' => '<td>',
      'markup' => array ('#markup' => $sBalanceLink),
      '#suffix' => '</td>',
    );
  }
 
  $arrContent['hc_mobile_menu'] = $hc_mobile_menu;

  if ($bIsAuthenticated && !$g_oMemberSession->IsOnlyMember )
  {
    $arrContent['hc_coord_menu'] = homecoop_coord_menu();
  }

  $hc_user_menu = array(
    '#prefix' => '<tr class="usermenu"><td ',
    '#suffix' => '</ul></nav></td></tr>',
  );

  if ($bIsAuthenticated) {
    $hc_user_menu['#prefix'] .= ' colspan="4" class="usermenucell" ';
    $hc_user_menu['hc_my_profile'] = array(
      '#prefix' => '<li>',
      'markup' => array ('#markup' => '<span class="usermenulabel" title="My Profile"><a href="' . url('hcprofile') . 
       '">' . t('Hello, @name', array('@name' => $g_oMemberSession->Name)) . '</a></span>'),
      '#suffix' => '</li>',
    );

    $hc_user_menu['hc_balance_link'] = array(
      '#prefix' => '<li class="mobilehide">',
      'markup' => array ('#markup' => $sBalanceLink),
      '#suffix' => '</li>',
    );
    
    if ( $g_oMemberSession->CanOrder) 
    {
      define('hcprmidMyOrder', 10);
      $oPermissionBridgeSet = new PermissionBridgeSet();

      if ($oPermissionBridgeSet->DefinePermissionBridge(hcprmidMyOrder, Consts::PERMISSION_AREA_ORDERS, Consts::PERMISSION_TYPE_MODIFY, 
               Consts::PERMISSION_SCOPE_BOTH, 0, TRUE)) {
        $hc_user_menu['hc_my_orders'] = array(
          '#prefix' => '<li>',
          'markup' => array ('#markup' => '<span class="usermenulabel"><a href="' . url('hcorders') . '">' . t('My Orders') . '</a></span>'),
          '#suffix' => '</li>',
        );
      }
    }
    
    $hc_user_menu['hc_catalog'] = array(
      '#prefix' => '<li>',
      'markup' => array ('#markup' => '<span class="usermenulabel"><a href="' . url('hccatalog') . '">' . t('Products Catalog') . '</a></span>'),
      '#suffix' => '</li>',
    );
  }
  $hc_user_menu['#prefix'] .= ' ><nav id="navUser" class="nav-collapse"><ul>';
  
  $hc_user_menu['langauge'] = homecoop_language_links();

  if ($bIsAuthenticated) {
    $hc_user_menu['hc_logout'] = array(
      '#prefix' => '<li>',
      'markup' => array ('#markup' => '<span class="usermenulabel"><a href="#" onclick="JavaScript:Logout()" >' . t('Logout') . '</a></span>'),
      '#suffix' => '</li>',
    );
  }
  
  $arrContent['hc_user_menu'] = $hc_user_menu;
  
  return array('hc_header' => $arrContent);
}

function homecoop_language_links() {
  $langs = language_list();
  
  $content = array(
    '#prefix' => '<li>',
    '#suffix' => '</li>',
  );

  if (count($langs) > 1) {
    global $language, $base_url;
    
    $sUrl = current_path();
    
    $arrParams = drupal_get_query_parameters();
    $sQuery = '';
    $bFirst = true;
    if (count($arrParams) > 0) {
      foreach($arrParams as $key => $value) {
        if (!$bFirst) {
          $sQuery .= '&';
          $bFirst = false;
        }
        $sQuery .= $key . '=' . urlencode($value);
      }
      $sQuery = '?' . $sQuery;
    }
  
    foreach($langs as $lkey => $oLang) {
      if ($language->language == $lkey) { //skip link to current language
        continue;
      }
      $content['links'][$lkey]['#prefix'] = '<span class="usermenulabel">';
      $content['links'][$lkey]['#markup'] = '<a href="#" class="subtlelink" onclick="JavaScript: ChangeLanguage(\'' .
          $base_url . '/' . $lkey . '/' . $sUrl . $sQuery . '\');" >' . $oLang->native . '</a>';

      $content['links'][$lkey]['#suffix'] = '</span>';
    } 
  }
  
  return $content;
}

function homecoop_coord_menu() {
  $arrContent = array(
    '#prefix' => '<tr class="coordmenu"><td colspan="4" class="coordmenucell"><nav id="navCoord" class="nav-collapse"><ul>',
    '#suffix' => '</ul></nav></td></tr>',
  );
  
  define('prmidCoopOrdersModify', 10);
  define('prmidCoopOrdersView', 11);
  define('prmidProducersModify', 30);
  define('prmidProducersView', 31);
  define('prmidProductsModify', 40);
  define('prmidProductsView', 41);
  define('prmidPickupLocationsModify', 50);
  define('prmidCachierTotals', 60);
  define('prmidMembersModify', 70);
  define('prmidMembersView', 80);
  
  $oPermissionBridgeSet = new PermissionBridgeSet();
  
  if ($oPermissionBridgeSet->DefinePermissionBridge(prmidCoopOrdersView, Consts::PERMISSION_AREA_COOP_ORDERS, Consts::PERMISSION_TYPE_VIEW, 
     Consts::PERMISSION_SCOPE_BOTH, 0, TRUE) ||
    $oPermissionBridgeSet->DefinePermissionBridge(prmidCoopOrdersModify, Consts::PERMISSION_AREA_COOP_ORDERS, Consts::PERMISSION_TYPE_MODIFY, 
     Consts::PERMISSION_SCOPE_BOTH, 0, TRUE))
  {
    $arrContent['cooporders'] = array(
      '#prefix' => '<li><span class="coordmenulabel">',
      '#markup' => '<a href="' . url('hccooporders') . '">' . t('Cooperative Orders') . '</a>',
      '#suffix' => '</span></li>',
    );
  }   

  if ($oPermissionBridgeSet->DefinePermissionBridge(prmidProducersView, Consts::PERMISSION_AREA_PRODUCERS, Consts::PERMISSION_TYPE_VIEW, 
       Consts::PERMISSION_SCOPE_BOTH, 0, TRUE) ||
     $oPermissionBridgeSet->DefinePermissionBridge(prmidProducersModify, Consts::PERMISSION_AREA_PRODUCERS, Consts::PERMISSION_TYPE_MODIFY, 
       Consts::PERMISSION_SCOPE_BOTH, 0, TRUE))
  {
    $arrContent['producers'] = array(
      '#prefix' => '<li><span class="coordmenulabel">',
      '#markup' => '<a href="' . url('hccoord/producers') . '">' . t('Producers') . '</a>',
      '#suffix' => '</span></li>',
    );
  }

  if ($oPermissionBridgeSet->DefinePermissionBridge(prmidProductsView, Consts::PERMISSION_AREA_PRODUCTS, Consts::PERMISSION_TYPE_VIEW, 
       Consts::PERMISSION_SCOPE_BOTH, 0, TRUE) || 
      $oPermissionBridgeSet->DefinePermissionBridge(prmidProductsModify, Consts::PERMISSION_AREA_PRODUCTS, Consts::PERMISSION_TYPE_MODIFY, 
       Consts::PERMISSION_SCOPE_BOTH, 0, TRUE))
  {
    $arrContent['products'] = array(
        '#prefix' => '<li><span class="coordmenulabel">',
        '#markup' => '<a href="' . url('hccoord/products') . '">' . t('Products') . '</a>',
        '#suffix' => '</span></li>',
      );  
  }

  if ($oPermissionBridgeSet->DefinePermissionBridge(prmidPickupLocationsModify, Consts::PERMISSION_AREA_PICKUP_LOCATIONS, Consts::PERMISSION_TYPE_MODIFY, 
       Consts::PERMISSION_SCOPE_BOTH, 0, TRUE))
  {
    $arrContent['pickuplocs'] = array(
        '#prefix' => '<li><span class="coordmenulabel">',
        '#markup' => '<a href="' . url('hccoord/pickuplocs') . '">' . t('Pickup Locations') . '</a>',
        '#suffix' => '</span></li>',
      );
  }

  if ($oPermissionBridgeSet->DefinePermissionBridge(prmidCachierTotals, Consts::PERMISSION_AREA_CACHIER_TOTALS, 
             Consts::PERMISSION_TYPE_VIEW, Consts::PERMISSION_SCOPE_COOP_CODE, 0, TRUE))
  {
    $arrContent['cachier'] = array(
        '#prefix' => '<li><span class="coordmenulabel">',
        '#markup' => '<a href="' . url('hccoord/cachier') . '">' . t('Cashier Totals') . '</a>',
        '#suffix' => '</span></li>',
      );
  }

  if ($oPermissionBridgeSet->DefinePermissionBridge(prmidMembersView, Consts::PERMISSION_AREA_MEMBERS, Consts::PERMISSION_TYPE_VIEW, 
       Consts::PERMISSION_SCOPE_COOP_CODE, 0, TRUE) ||    
      $oPermissionBridgeSet->DefinePermissionBridge(prmidMembersModify, Consts::PERMISSION_AREA_MEMBERS, Consts::PERMISSION_TYPE_MODIFY, 
       Consts::PERMISSION_SCOPE_COOP_CODE, 0, TRUE))
  {
    $arrContent['members'] = array(
        '#prefix' => '<li><span class="coordmenulabel">',
        '#markup' => '<a href="' . url('hccoord/members') . '">' . t('Members') . '</a>',
        '#suffix' => '</span></li>',
      );
  }
  
  return $arrContent;
}