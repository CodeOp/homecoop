<?php

function homecoop_page_orders() {
  homecoop_authenticated_page();
  
  $oData = new MemberOrders;
  $bCoord = $oData->CheckCoord();
  
  if ($bCoord) {
    drupal_set_title(t('Orders'));
    global $g_oMemberSession;
    $view = views_get_view('homecoop_my_orders_coord');
    $view->preview=TRUE;
    $view->is_cacheable = FALSE;
    $view->init_display('default');
    $view->exposed_input['MemberID'] = $g_oMemberSession->MemberID;
    $view->pre_execute();
    $output = $view->display_handler->preview();
    $view->post_execute();
    return $output;
  }
  else {
    drupal_set_title(t('My Orders'));
    return views_embed_view('homecoop_my_orders');
  }
}