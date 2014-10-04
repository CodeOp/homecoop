<?php

function homecoop_page_members() {
  global $language, $g_oMemberSession;
  homecoop_authenticated_page();
  
  $oAccess = new Members;
  
  $oAccess->GetAccess();

  if ($oAccess->LastOperationStatus == SQLBase::OPERATION_STATUS_NO_PERMISSION)
  {
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  drupal_set_title(t('Members'));
  
  $bCanAdd = $oAccess->HasPermission(Members::PERMISSION_COORD);
  
  $view = views_get_view('homecoop_members');  
  $view->preview=TRUE;
  $view->is_cacheable = FALSE;
  $view->init_display('default'); 
  
  //args: allow add, allow coord, language, language, coordinating groups
  $arrParams = array(
    $language->language,
    $bCanAdd? 'rw' : 'ro',
  );
  
  $view->pre_execute($arrParams);
  
  $content = $view->display_handler->preview();
  
  $view->post_execute();
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $content;
}