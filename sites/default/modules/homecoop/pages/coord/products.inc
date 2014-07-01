<?php
function homecoop_page_products() {
  global $language, $g_oMemberSession;
  homecoop_authenticated_page();
  
  $oProducts = new Products;
  
  $oProducts->GetAccess();

  if ($oProducts->LastOperationStatus == SQLBase::OPERATION_STATUS_NO_PERMISSION)
  {
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  $bEdit = $oProducts->HasPermission(Products::PERMISSION_COORD);

  drupal_set_title(t('Products'));
  
  $view = views_get_view('homecoop_products');
  $view->preview=TRUE;
  $view->is_cacheable = FALSE;
  $view->init_display('default');  
  
  //args: has add permission, language, language, language, coordinating group id
  $arrParams = array($bEdit ? 'yes' : 'no', $language->language, $language->language, $language->language);
  
  if ( ($oProducts->GetPermissionScope(Products::PERMISSION_COORD) != Consts::PERMISSION_SCOPE_COOP_CODE)  &&
          ($oProducts->GetPermissionScope(Products::PERMISSION_VIEW) != Consts::PERMISSION_SCOPE_COOP_CODE) ) {
    $arrParams[] =  implode("+", $g_oMemberSession->Groups);
  }
  
  $view->pre_execute($arrParams);
  
  $content = $view->display_handler->preview();
  
  $view->post_execute();
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $content;
}