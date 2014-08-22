<?php

function homecoop_page_member() {
  
  homecoop_authenticated_page();
  
  $oRecord = new Member;
   
  //must be coordinator to enter this page
  if (!$oRecord->CheckAccess() || (!$oRecord->IsCoordinator && !$oRecord->HasPermission(Member::PERMISSION_VIEW)))
  {
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  //editing existing
  if(!$oRecord->LoadRecord(intval($_GET['id'])))
  {
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  switch($oRecord->LastOperationStatus)
  {
    case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
    case SQLBase::OPERATION_STATUS_NO_PERMISSION:
    case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
    case SQLBase::OPERATION_STATUS_COORDINATION_GROUP_VERIFY_FAILED:
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  $oRecord->RevokeModifyPermission();
  
  $hcsettings = array(
    'ConfirmDelete' => t('Please confirm the delete operation. Note that this action will succeed only when there are no orders linked to the member. To block a member from signing in, remove hir permissions instead.'),
    'MemberID' => $oRecord->MemberID,
    'PostActionDelete' => SQLBase::POST_ACTION_DELETE,
    'PostActionDeactivate' => MEMBER::POST_ACTION_DEACTIVATE,
    'PostActionActivate' => MEMBER::POST_ACTION_ACTIVATE,
    'PostActionSave' => SQLBase::POST_ACTION_SAVE,
  );
  
  drupal_add_js(array('homecoop' => $hcsettings), 'setting');
  homecoop_add_js_file('member.js');
  
  $sPageTitle = t('New Member');
  if ($oRecord->Name != NULL) {
    $sPageTitle = $oRecord->Name;
  }
  
  drupal_set_title($sPageTitle);
  
  $oFormExtraData = homecoop_page_member_prepareform($oRecord);
  
  $arrContent = array(
    '#prefix' => '<table cellspacing="0" cellpadding="0" width="100%"><tr>',
    'td' => array(
        '#prefix' => '<td>',
        'memberform' => drupal_get_form('homecoop_page_member_form', $oFormExtraData),
        '#suffix' => '</td>',
      ),
    '#suffix' => '</tr></table>',
  );
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $arrContent;
}

function homecoop_page_member_prepareform($oRecord) {

  $oMemberTabInfo = new MemberTabInfo($oRecord->ID, MemberTabInfo::PAGE_ENTRY);
  $oMemberTabInfo->MainTabName = $oRecord->Name;  
  
  return array(
    'paymentmethods' => $oRecord->GetPaymentMethods(),
    'pickuplocations' => $oRecord->GetCachiers(),
    'HasAccessToRoles' => $oRecord->HasAccessToRoles(),
    'hasdeletepermission' => $oRecord->HasPermission(SQLBase::PERMISSION_DELETE),
  ) + homecoop_member_tab_info($oMemberTabInfo) 
    + $oRecord->GetAllProperties();
}

function homecoop_page_member_form($form, &$form_state, $oFormExtraData) {
  global $HomeCoopThemePath;
  
  if (isset($form_state['homecoop_member'])) {
    $oFormExtraData = $form_state['homecoop_member'];
  }
  elseif (isset($oFormExtraData)) {
    $form_state['homecoop_member'] = $oFormExtraData;
  }
  else  {
    return array();
  }
  
  $form['#id'] = 'homecoop_page_member-form';
  $form['#attributes']['name'] = 'homecoop_page_member_form';
  //internal values
  $form['hidOriginalData'] = array('#type' => 'value', '#value' => $oFormExtraData['OriginalData'], 
    '#attributes' => array('id' => 'hidOriginalData'));
  $form['hidPostValue'] = array('#type' => 'value', '#value' => $oFormExtraData['ID'], 
    '#attributes' => array('id' => 'hidPostValue'));
  //exposed value
  $form['hidPostAction'] = array('#type' => 'hidden', '#default_value' => '', 
    '#attributes' => array('id' => 'hidPostAction'));
  
  $form['maintable'] = array(
    'membertab' => array(
      'tab' => homecoop_member_tab_content($oFormExtraData),
      '#weight' => 10,
    ),
    'controlstable' => array(
      '#weight' => 50,
      'maxorder' => array(
        '#prefix' => '<label>' . t('Max. Order') . '</label><span>',
        '#markup' => $oFormExtraData['MaxOrder'],
        '#suffix' => '</span>',
        '#weight' => 70,
      ),
    ),
  );
  
  if ($oFormExtraData['CanModify']) {
    $form['maintable']['buttons'] = array(
      '#weight' => 20,
      'btn_save' => array(
        '#type' => 'submit',
        '#name' => 'btn_save',
        '#id' => 'btn_save',
        '#submit' => array('homecoop_page_member_form_submit'),
        '#value' => t('Save'),
        '#disabled' => $oFormExtraData['CanModify'] ? FALSE: TRUE,
        '#attributes' => array(
          'onclick' => 'Save();',
          ),
        '#suffix' => '&nbsp;',
        '#weight' => 10, 
      ),
    );
    
    if ($oFormExtraData['ID'] > 0) {
      $form['maintable']['buttons']['addlink'] = array(
        '#prefix' => '<a href="' . url('hccoord/member') . '" >',
        '#markup' =>  '<img border="0" title="' . t('Add') . '" src="' . $HomeCoopThemePath . 'img/edit-add-2.png" />',
        '#suffix' => '</a>&nbsp;',
        '#weight' => 5, 
      );
      
      if ($oFormExtraData['hasdeletepermission']) {
        $form['maintable']['buttons']['btn_delete'] = array(
            '#type' => 'button',
            '#name' => 'btn_delete',
            '#id' => 'btn_delete',
            '#value' => t('Delete'),
            '#weight' => 20, 
            '#attributes' => array(
              'onclick' => 'Delete();',
            ),
        );
      }
      
      $form['maintable']['buttons']['btnDeactivate'] = array(
            '#type' => 'button',
            '#name' => 'btnDeactivate',
            '#id' => 'btnDeactivate',
            '#value' => t('Remove Permissions'),
            '#weight' => 30, 
            '#attributes' => array(
              'onclick' => 'Deactivate();',
            ),
        );
      
      if ($oFormExtraData['HasNoPermissions']) {
        $form['maintable']['buttons']['btnActivate'] = array(
            '#type' => 'button',
            '#name' => 'btnActivate',
            '#id' => 'btnActivate',
            '#value' => t('Restore Permissions'),
            '#weight' => 40, 
            '#attributes' => array(
              'onclick' => 'Activate();',
            ),
        );
      }
    }
    
  } //end can modify
  
  
  
  $form['#submit'][] = 'homecoop_page_member_form_submit';
  
  return $form;
}

function homecoop_page_member_form_submit($form, &$form_state) {
  
  
}