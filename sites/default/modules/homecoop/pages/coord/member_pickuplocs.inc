<?php

function homecoop_page_member_pickuplocs() {
  homecoop_authenticated_page();
  
  $oTable = new MemberPickupLocations();
  $oMemberTabInfo = NULL;
  $arrPageData = array();
  
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
  
  $arrPageData['fulledit'] = $oTable->HasPermission(MemberPickupLocations::PERMISSION_EDIT);
  
  $oMemberTabInfo = new MemberTabInfo($oTable->ID, MemberTabInfo::PAGE_PICKUP_LOCATIONS);
  $oMemberTabInfo->MainTabName = check_plain($oTable->Name);
  drupal_set_title(t('@name - Pickup Locations', array('@name' => $oMemberTabInfo->MainTabName)));
  
  return drupal_get_form('homecoop_page_member_pickuplocs_form', (object)
      ($arrPageData + homecoop_member_tab_info($oMemberTabInfo)));
}

function homecoop_page_member_pickuplocs_form($form, &$form_state, $pageobj) {
  global $g_oMemberSession;
  
  //ajax
  if(!isset($g_oMemberSession)) {
    homecoop_authenticated_page();
  }
  
  homecoop_add_js_file('member_pickuplocs.js');
  
  $form['#id'] = 'homecoop_page_member_pickuplocs-form';
  $form['#attributes']['name'] = 'homecoop_page_member_pickuplocs_form';
    
  $form['hidPostValue'] = array('#type' => 'value', '#value' => $pageobj->ID, 
    '#attributes' => array('id' => 'hidPostValue'));
  
  $form['hidPickupLocation'] = array('#type' => 'hidden', '#default_value' => 0,
    '#attributes' => array('id' => 'hidPickupLocation'));
    
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
      '#prefix' => '<table cellspacing="0" cellpadding="2" width="100%"><tr><td class="columntitlelong">' .
                  t('Location Name') . '</td><td class="columntitleshort">' . t('Removed') . 
                  '</td><td class="columntitlenowidth">' . t('Blocked') . '</td></tr>',
      '#suffix' => '</table>',
      '#weight' => 50,
    ),
  );
  
  foreach($pageobj->table as $row) {
    $plid = $row['PickupLocationKeyID'];
    $form['maintable']['controlstable']["row$plid"] = array(
      '#prefix' => '<tr>',
      'name' => array(
        '#prefix' => '<td>',
        '#suffix' => '</td>',
        '#markup' => check_plain($row['sPickupLocation']),
        
      ),
      '#suffix' => '</tr>',
    );
    
    $removed = $row['bRemoved'] ? 1 : 0;
    $blocked = $row['bBlocked'] ? 1 : 0;
    $existing = $row['MPLID'] != NULL? 1 : 0;
    $form['maintable']['controlstable']["row$plid"]["chkRemove_$plid"] = array(
      '#prefix' => '<td>',
      '#suffix' => '</td>',
      '#type' => 'checkbox',
      '#title' => '',
      '#default_value' => $removed,
      '#disabled' => !$pageobj->fulledit,
    );
    
    $form['maintable']['controlstable']["row$plid"]["chkBlock_$plid"] = array(
      '#prefix' => '<td>',
      '#suffix' => '</td>',
      '#type' => 'checkbox',
      '#title' => '',
      '#default_value' => $blocked,
      '#disabled' => !$pageobj->fulledit,
    );
    
    $form['maintable']['controlstable']["row$plid"]["existing_$plid"] = array(
      '#type' => 'hidden',
      '#default_value' => $existing,
      '#attributes' => array('id' => "existing_$plid")
    );
    
    if ($pageobj->fulledit) {
      $form['maintable']['controlstable']["row$plid"]["chkRemove_$plid"]['#ajax'] = array(
        'callback' => 'homecoop_member_pickuplocs_filter_ajax_callback',
        'wrapper' => 'div_ajax_result',
        'method' => 'replace',
      );
      $form['maintable']['controlstable']["row$plid"]["chkRemove_$plid"]['#attributes'] = array(
        'onchange' => "SetActionParams($plid)",
      );
      
      $form['maintable']['controlstable']["row$plid"]["chkBlock_$plid"]['#ajax'] = array(
        'callback' => 'homecoop_member_pickuplocs_block_ajax_callback',
        'wrapper' => 'div_ajax_result',
        'method' => 'replace',
      );
      $form['maintable']['controlstable']["row$plid"]["chkBlock_$plid"]['#attributes'] = array(
        'onchange' => "SetActionParams($plid)",
      );
    } 
  }

  return $form;
}

function homecoop_member_pickuplocs_filter_ajax_callback($form, &$form_state) {
 
  global $g_oMemberSession;
  
  //ajax
  if(!isset($g_oMemberSession)) {
    homecoop_authenticated_page();
  }
  $plid = intval($form_state['values']['hidPickupLocation']);
  
  if ($plid == 0) {
    drupal_set_message(t('Record was not saved. No pickup location was identified.'), 'error');
  }
  else {
  
    $oTable = new MemberPickupLocations();
    $oTable->ID = intval($form_state['values']['hidPostValue']);
    
    $bSuccess = $oTable->RemoveFromFacet($plid, $form_state['values']["chkRemove_$plid"], empty($form_state['values']["existing_$plid"]));

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

  //message display command
  $commands[] = ajax_command_html('#div_ajax_result' , render($element));
  
  //post script command
  $commands[] = array (
    'command' => 'SetExisting',
      'plid' => $plid,
      'success' => $bSuccess,
  );

  return array('#type' => 'ajax', '#commands' => $commands);
}

function homecoop_member_pickuplocs_block_ajax_callback($form, &$form_state) {
 
  global $g_oMemberSession;
  
  //ajax
  if(!isset($g_oMemberSession)) {
    homecoop_authenticated_page();
  }
  $plid = intval($form_state['values']['hidPickupLocation']);
  
  if ($plid == 0) {
    drupal_set_message(t('Record was not saved. No pickup location was identified.'), 'error');
  }
  else {
  
    $oTable = new MemberPickupLocations();
    $oTable->ID = intval($form_state['values']['hidPostValue']);

    $bSuccess = $oTable->BlockFromFacet($plid, $form_state['values']["chkBlock_$plid"], empty($form_state['values']["existing_$plid"]));

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

  //message display command
  $commands[] = ajax_command_html('#div_ajax_result' , render($element));
  
  //post script command
  $commands[] = array (
    'command' => 'SetExisting',
      'plid' => $plid,
      'success' => $bSuccess,
  );

  return array('#type' => 'ajax', '#commands' => $commands);
}