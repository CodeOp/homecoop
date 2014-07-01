<?php
function homecoop_page_products() {
  homecoop_authenticated_page();
   
  //drupal_set_title(t('Cooperative Orders'));
  
  //$view = views_get_view('homecoop_cooporders');  
  $view->preview=TRUE;
  $view->is_cacheable = FALSE;
  $view->init_display('default');  
  
  //args: has add permission, language, language, coordinating group id
  $view->pre_execute();
  
  $content = $view->display_handler->preview();
  
  $view->post_execute();
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $content;
}