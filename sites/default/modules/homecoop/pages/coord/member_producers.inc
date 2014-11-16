<?php

function homecoop_page_member_producers() {
  homecoop_authenticated_page();
  
  $oTable = new MemberProducers();
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
  
  $arrPageData['fulledit'] = $oTable->HasPermission(MemberProducers::PERMISSION_EDIT);
  
  $oMemberTabInfo = new MemberTabInfo($oTable->ID, MemberTabInfo::PAGE_PRODUCERS);
  $oMemberTabInfo->MainTabName = check_plain($oTable->Name);
  drupal_set_title(t('@name - Producers', array('@name' => $oMemberTabInfo->MainTabName)));
  
  return drupal_get_form('homecoop_page_member_producers_form', (object)
      ($arrPageData + homecoop_member_tab_info($oMemberTabInfo)));
}

function homecoop_page_member_producers_form($form, &$form_state, $pageobj) {
  global $g_oMemberSession;
  
  //ajax
  if(!isset($g_oMemberSession)) {
    homecoop_authenticated_page();
  }
  
  homecoop_add_js_file('member_producers.js');
  
  $form['#id'] = 'homecoop_page_member_producers-form';
  $form['#attributes']['name'] = 'homecoop_page_member_producers_form';
    
  $form['hidPostValue'] = array('#type' => 'value', '#value' => $pageobj->ID, 
    '#attributes' => array('id' => 'hidPostValue'));
  
  $form['hidProducer'] = array('#type' => 'hidden', '#default_value' => 0,
    '#attributes' => array('id' => 'hidProducer'));
    
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
                  t('Producer Name') . '</td><td class="columntitleshort">' . t('Removed') . 
                  '</td><td class="columntitlenowidth">' . t('Blocked') . '</td></tr>',
      '#suffix' => '</table>',
      '#weight' => 50,
    ),
  );
  
  foreach($pageobj->table as $row) {
    $prid = $row['ProducerKeyID'];
    $form['maintable']['controlstable']["row$prid"] = array(
      '#prefix' => '<tr>',
      'name' => array(
        '#prefix' => '<td>',
        '#suffix' => '</td>',
        '#markup' => check_plain($row['sProducer']),
        
      ),
      '#suffix' => '</tr>',
    );
    
    $removed = $row['bRemoved'] ? 1 : 0;
    $blocked = $row['bBlocked'] ? 1 : 0;
    $existing = $row['MPRID'] != NULL? 1 : 0;
    $form['maintable']['controlstable']["row$prid"]["chkRemove_$prid"] = array(
      '#prefix' => '<td>',
      '#suffix' => '</td>',
      '#type' => 'checkbox',
      '#title' => '',
      '#default_value' => $removed,
      '#disabled' => !$pageobj->fulledit,
    );
    
    $form['maintable']['controlstable']["row$prid"]["chkBlock_$prid"] = array(
      '#prefix' => '<td>',
      '#suffix' => '</td>',
      '#type' => 'checkbox',
      '#title' => '',
      '#default_value' => $blocked,
      '#disabled' => !$pageobj->fulledit,
    );
    
    $form['maintable']['controlstable']["row$prid"]["existing_$prid"] = array(
      '#type' => 'hidden',
      '#default_value' => $existing,
      '#attributes' => array('id' => "existing_$prid")
    );
    
    if ($pageobj->fulledit) {
      $form['maintable']['controlstable']["row$prid"]["chkRemove_$prid"]['#ajax'] = array(
        'callback' => 'homecoop_member_producers_filter_ajax_callback',
        'wrapper' => 'div_ajax_result',
        'method' => 'replace',
      );
      $form['maintable']['controlstable']["row$prid"]["chkRemove_$prid"]['#attributes'] = array(
        'onchange' => "SetActionParams($prid)",
      );
      
      $form['maintable']['controlstable']["row$prid"]["chkBlock_$prid"]['#ajax'] = array(
        'callback' => 'homecoop_member_producers_block_ajax_callback',
        'wrapper' => 'div_ajax_result',
        'method' => 'replace',
      );
      $form['maintable']['controlstable']["row$prid"]["chkBlock_$prid"]['#attributes'] = array(
        'onchange' => "SetActionParams($prid)",
      );
    } 
  }

  return $form;
}

function homecoop_member_producers_filter_ajax_callback($form, &$form_state) {
 
  global $g_oMemberSession;
  
  //ajax
  if(!isset($g_oMemberSession)) {
    homecoop_authenticated_page();
  }
  $prid = intval($form_state['values']['hidProducer']);
  
  if ($prid == 0) {
    drupal_set_message(t('Record was not saved. No pickup location was identified.'), 'error');
  }
  else {
  
    $oTable = new MemberProducers();
    $oTable->ID = intval($form_state['values']['hidPostValue']);
    
    $bSuccess = $oTable->RemoveFromFacet($prid, $form_state['values']["chkRemove_$prid"], empty($form_state['values']["existing_$prid"]));

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
      'prid' => $prid,
      'success' => $bSuccess,
  );

  return array('#type' => 'ajax', '#commands' => $commands);
}

function homecoop_member_producers_block_ajax_callback($form, &$form_state) {
 
  global $g_oMemberSession;
  
  //ajax
  if(!isset($g_oMemberSession)) {
    homecoop_authenticated_page();
  }
  $prid = intval($form_state['values']['hidProducer']);
  
  if ($prid == 0) {
    drupal_set_message(t('Record was not saved. No pickup location was identified.'), 'error');
  }
  else {
  
    $oTable = new MemberProducers();
    $oTable->ID = intval($form_state['values']['hidPostValue']);

    $bSuccess = $oTable->BlockFromFacet($prid, $form_state['values']["chkBlock_$prid"], empty($form_state['values']["existing_$prid"]));

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
      'prid' => $prid,
      'success' => $bSuccess,
  );

  return array('#type' => 'ajax', '#commands' => $commands);
}