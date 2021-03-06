<?php

function homecoop_page_member_roles() {
  homecoop_authenticated_page();

  $arrPageData = array();

  $oTable = new MemberRoles;
  $oMemberTabInfo = NULL;
  $arrPageData['view_only'] = TRUE;
  $sPageTitle = '';

  if (isset($_GET['id']))
      $oTable->ID = intval($_GET['id']);

  $arrPageData['table'] = $oTable->GetTable();

  switch($oTable->LastOperationStatus)
  {
    case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
    case SQLBase::OPERATION_STATUS_NO_PERMISSION:
    case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }

  $oMemberTabInfo = new MemberTabInfo($oTable->ID, MemberTabInfo::PAGE_ROLES);

  drupal_set_title(t('@name - Roles', array('@name' => check_plain($oTable->Name))));

  $oMemberTabInfo->MainTabName = $oTable->Name;

  if ($oTable->HasPermission(SQLBase::PERMISSION_COORD))
  {
    $arrPageData['table_to_add'] = $oTable->GetOtherRoles();
    $arrPageData['view_only'] = FALSE;
  }

  return drupal_get_form('homecoop_page_member_roles_form', (object)
      ($arrPageData + homecoop_member_tab_info($oMemberTabInfo)));
}

function homecoop_page_member_roles_form($form, &$form_state, $pageobj) {
  global $g_oMemberSession;
  
  //ajax
  if(!isset($g_oMemberSession)) {
    homecoop_authenticated_page();
  }
  
  homecoop_add_js_file('member_roles.js');
  
  $form['#id'] = 'homecoop_member_roles-form';
  $form['#attributes']['name'] = 'homecoop_member_roles_form';
    
  $form['hidPostValue'] = array('#type' => 'value', '#value' => $pageobj->ID, 
    '#attributes' => array('id' => 'hidPostValue'));
  
  $form['hidRole'] = array('#type' => 'hidden', '#default_value' => 0,
    '#attributes' => array('id' => 'hidRole'));
  
  //ajax injected result - on top of all controls
  $form['ajaxresult'] = array(
    '#prefix' => '<div id="div_ajax_result">',
    '#suffix' => '</div>',
    '#weight' => 0, 
  );
   
  $form['maintable'] = array(
    'membertab' => array(
      'tab' => homecoop_member_tab_content($pageobj),
      '#weight' => 10,
    ),
    '#weight' => 10,
    'controlstable' => array(
      '#type' => 'fieldset',
      '#weight' => 50,
    ),
  );
  
  if (!$pageobj->view_only) {
    $weight = 10;
    foreach ( $pageobj->table as $roleid => $rolename )
    {
        $form['maintable']['controlstable']["chkRole_$roleid"] = array(
              '#weight' => $weight, 
              '#type' => 'checkbox',
              '#title' => $rolename,
              '#default_value' => 1,
              '#ajax' => array(
                'callback' => 'homecoop_member_roles_ajax_callback',
                'wrapper' => 'div_ajax_result',
                'method' => 'replace',
              ),
              '#attributes' => array(
                'onchange' => "SetRole($roleid)",
              ),
          );      
        $weight += 10;
    }

    if (isset($pageobj->table_to_add)) {
      foreach ( $pageobj->table_to_add as $roleid => $rolename )
      {
          $form['maintable']['controlstable']["chkRole_$roleid"] = array(
              '#weight' => $weight, 
              '#type' => 'checkbox',
              '#title' => $rolename,
              '#default_value' => 0,
              '#ajax' => array(
                'callback' => 'homecoop_member_roles_ajax_callback',
                'wrapper' => 'div_ajax_result',
                'method' => 'replace',
              ),
              '#attributes' => array(
                'onchange' => "SetRole($roleid)",
              ),
          );

          $weight += 10;
      }
    } 
  }
  
  return $form;
}

function homecoop_member_roles_ajax_callback($form, &$form_state) {
  
  global $g_oMemberSession;
  
  //ajax
  if(!isset($g_oMemberSession)) {
    homecoop_authenticated_page();
  }
  $roleid = intval($form_state['values']['hidRole']);
  
  if ($roleid == 0) {
    drupal_set_message(t('Record was not saved. No role was identified.'), 'error');
  }
  else {
  
    $oTable = new MemberRoles();
    $oTable->ID = intval($form_state['values']['hidPostValue']);

    $bSuccess = false;
    if ($form_state['values']["chkRole_$roleid"]) {
      $bSuccess = $oTable->AddRole($roleid);
    }
    else {
      $bSuccess = $oTable->RemoveRole($roleid);
    }

    if ($bSuccess) {
      drupal_set_message(t('Record saved successfully.'), 'status');
    }
    else if ($oTable->LastOperationStatus != SQLBase::OPERATION_STATUS_VALIDATION_FAILED) {
      drupal_set_message(t('Record was not saved. You may not have sufficent permissions or an error has occured.'), 'error');
    }
  }
  
  $commands = array();
  
  $element = array('messages' => array(
                      '#type' => 'markup',
                        '#markup' => theme('status_messages'))
        );

  $commands[] = ajax_command_html('#div_ajax_result' , render($element));

  return array('#type' => 'ajax', '#commands' => $commands);
}