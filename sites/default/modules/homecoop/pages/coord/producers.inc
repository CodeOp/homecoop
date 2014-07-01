<?php

function homecoop_page_producers() {
  global $language, $g_oMemberSession;
  
  homecoop_authenticated_page();
   
  
  $oProducers = new Producers;
  
  $oProducers->GetAccess();
  
  if ($oProducers->LastOperationStatus == SQLBase::OPERATION_STATUS_NO_PERMISSION)
  {
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  drupal_set_title(t('Producers'));
  
  $bCanSetCoord = $oProducers->HasPermission(SQLBase::PERMISSION_COORD_SET);
  $bCanAdd = $oProducers->HasPermission(SQLBase::PERMISSION_ADD);
  
  $view = views_get_view('homecoop_producers');  
  $view->preview=TRUE;
  $view->is_cacheable = FALSE;
  $view->init_display('default');  
  
  $arrParams = array($bCanAdd? 'rw' : 'ro', $bCanSetCoord? 'yes' : 'no', $language->language);
  if ( ($oProducers->GetPermissionScope(Producers::PERMISSION_COORD) != Consts::PERMISSION_SCOPE_COOP_CODE) &&
            ($oProducers->GetPermissionScope(Producers::PERMISSION_VIEW) != Consts::PERMISSION_SCOPE_COOP_CODE) ) {
    $arrParams[] = implode("+", $g_oMemberSession->Groups);
  }
  
  //args: has add permissions, has coord permissions
  $view->pre_execute($arrParams);
  
  $content = $view->display_handler->preview();
  
  $view->post_execute();
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $content;
}