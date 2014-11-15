<?php

function homecoop_page_member_transactions() {
  homecoop_authenticated_page();
  
  $oTable = new TransactionTable();
  $oMember = new Member();
  
  if (isset($_GET['id'])) {
    $oTable->MemberID = intval($_GET['id']);
  }
  
  if (!$oTable->CheckAccess()) {
    drupal_goto(Consts::URL_ACCESS_DENIED);
    return;
  }
  
  switch($oTable->LastOperationStatus)
  {
    case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
    case SQLBase::OPERATION_STATUS_NO_PERMISSION:
    case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
    case SQLBase::OPERATION_STATUS_COORDINATION_GROUP_VERIFY_FAILED:
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }

  if (!$oMember->CheckAccess() || !$oMember->IsCoordinator || !$oMember->HasPermission(Member::PERMISSION_VIEW)) {
     drupal_goto(Consts::URL_ACCESS_DENIED);
     return;
  }
  
  $entity = homecoop_member_load($oTable->MemberID);
  
  if(!$entity) {
     drupal_goto(Consts::URL_ACCESS_DENIED);
     return;
  }
  
  $oMemberTabInfo = new MemberTabInfo($oTable->MemberID, MemberTabInfo::PAGE_TRANSACTIONS);

  $oMemberTabInfo->MainTabName = check_plain($entity->Name);
  drupal_set_title(t('@name - Transactions', array('@name' => $oMemberTabInfo->MainTabName)));
    
  $view = views_get_view('homecoop_member_transactions');
  $view->preview=TRUE;
  $view->is_cacheable = FALSE;
  $view->init_display('default');  
  $view->pre_execute(array($oTable->MemberID,));
  
  $content = array(
    'membertab' => array(
      'tab' => homecoop_member_tab_content((object)homecoop_member_tab_info($oMemberTabInfo)),
      '#weight' => 10,
     ),
    'spacer' => array(
      '#markup' => '<div class="spacer4">&nbsp;</div>',
      '#weight' => 15,
    ),
    'view' => array(
      '#markup' => $view->display_handler->preview(),
      '#weight' => 20,
    ),
  );
    
  $view->post_execute();
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $content;
}