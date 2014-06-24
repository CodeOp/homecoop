<?php

function homecoop_page_orders() {
  homecoop_authenticated_page();
  global $g_oMemberSession;
  
  drupal_set_title(t('My Orders'));
  $view = views_get_view('homecoop_my_orders');
  $view->preview=TRUE;
  $view->is_cacheable = FALSE;
  $view->init_display('default');
  $view->exposed_input['MemberID'] = $g_oMemberSession->MemberID;
  
  $view->pre_execute();
  $output = $view->display_handler->preview();
  $view->post_execute();

  return $output;
}