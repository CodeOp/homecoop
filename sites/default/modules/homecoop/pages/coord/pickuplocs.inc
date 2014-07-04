<?php

function homecoop_page_pickuplocs() {
  global $language, $g_oMemberSession;
  homecoop_authenticated_page();
  
  $oAccess = new PickupLocations;

  $oAccess->GetAccess();

  if ($oAccess->LastOperationStatus == SQLBase::OPERATION_STATUS_NO_PERMISSION)
  {
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  drupal_set_title(t('Pickup Locations'));
    
  $bCanSetCoord = $oAccess->HasPermission(SQLBase::PERMISSION_COORD_SET);
  $bCanAdd = $oAccess->HasPermission(SQLBase::PERMISSION_ADD);
  
  $view = views_get_view('homecoop_pickup_locations');  
  $view->preview=TRUE;
  $view->is_cacheable = FALSE;
  $view->init_display('default'); 
  
  //args: allow add, allow coord, language, language, coordinating groups
  $arrParams = array(
    $bCanAdd? 'yes' : 'no',
    $bCanSetCoord? 'yes' : 'no',
    $language->language,
    $language->language,
  );
  
  if ( $oAccess->GetPermissionScope(PickupLocations::PERMISSION_COORD) == Consts::PERMISSION_SCOPE_GROUP_CODE ) {
    $arrParams[] = implode("+", $g_oMemberSession->Groups);
  }
  
  $view->pre_execute($arrParams);
  
  $content = $view->display_handler->preview();
  
  $view->post_execute();
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $content;
}