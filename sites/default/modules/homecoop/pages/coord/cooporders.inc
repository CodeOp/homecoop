<?php

function homecoop_page_cooporders() {
  global $language, $g_oMemberSession;
  homecoop_authenticated_page();
  
  $oAccess = new CoopOrders;

  $oAccess->GetAccess();
  
  if ($oAccess->LastOperationStatus == CoopOrders::OPERATION_STATUS_NO_PERMISSION) //completely denied from page
  {
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  drupal_set_title(t('Cooperative Orders'));
  
  $bCanEdit = $oAccess->HasPermission(SQLBase::PERMISSION_COORD);
  $bCanViewSums = $oAccess->HasPermission(CoopOrders::PERMISSION_SUMS);
  $bCanCopy = $oAccess->HasPermission(SQLBase::PERMISSION_COPY);  
  $bCanSetCoord = $oAccess->HasPermission(SQLBase::PERMISSION_COORD_SET);
  
  if ($bCanViewSums) {
    $view = views_get_view('homecoop_cooporders');
  }
  else {
    $view = views_get_view('homecoop_cooporders_nosums');
  }
  
  $arrParams = array(
    $bCanEdit? 'yes' : 'no',
    $bCanCopy? 'yes' : 'no',
    $bCanSetCoord? 'yes' : 'no',
    $language->language,  
  );
  
  if ( $oAccess->GetPermissionScope(CoopOrders::PERMISSION_PAGE_ACCESS) != Consts::PERMISSION_SCOPE_COOP_CODE 
           && $oAccess->GetPermissionScope(CoopOrders::PERMISSION_COORD) != Consts::PERMISSION_SCOPE_COOP_CODE ) {
    $arrParams[] = implode("+", $g_oMemberSession->Groups);
  }
  
  $view->preview=TRUE;
  $view->is_cacheable = FALSE;
  $view->init_display('default');  
  $view->pre_execute($arrParams);
  
  $content = $view->display_handler->preview();
  
  $view->post_execute();
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $content;
}