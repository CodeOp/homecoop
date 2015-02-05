<?php

function homecoop_page_member_edit($entity) {
  homecoop_page_member_common_start();
  
  drupal_set_title($entity->Name);
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  if (!$entity->HasNoPermissions) {
    drupal_add_js('jQuery(document).ready(function () { SetActivateOptionAsDisabled(); });', 'inline');
  }
  
  return drupal_get_form('homecoop_member_form', $entity);
}

function homecoop_page_member_add() {
  homecoop_page_member_common_start();
  
  $entity = entity_get_controller('homecoop_member')->create();
  
  drupal_set_title(t('New Member'));
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return drupal_get_form('homecoop_member_form', $entity);
}

function homecoop_member_form($form, &$form_state, $entity) {
  global $g_oMemberSession;
  
  //ajax
  if(!isset($g_oMemberSession)) {
    homecoop_authenticated_page();
  }
  
  homecoop_add_js_file('member.js');
  
  $form['#id'] = 'homecoop_member-form';
  $form['#attributes']['name'] = 'homecoop_member_form';
  // Save the entity for later, in case we need it.
  $form_state['homecoop_member'] = $entity;
  
  //internal values
  $form['hidOriginalData'] = array('#type' => 'value', '#value' => $entity->OriginalData, 
    '#attributes' => array('id' => 'hidOriginalData'));
  
  $form['hidPostValue'] = array('#type' => 'value', '#value' => $entity->ID, 
    '#attributes' => array('id' => 'hidPostValue'));
  
  //ajax injected drupal messages - on top of all controls
  $form['ajaxmessage'] = array(
    '#prefix' => '<div id="div_ajax_message">',
    '#suffix' => '</div>',
    '#weight' => 0, 
  );
  
  $form['maintable'] = array(
    '#weight' => 10,
    'controlstable' => array(
      '#weight' => 50,
      'maxorder' => array(
        '#markup' => $entity->MaxOrder,
        '#type' => 'item',
        '#title' => t('Max. Order'),
        '#weight' => 70,
      ),
    ),
  );
  
  if ($entity->ID > 0) {
    $form['maintable']['membertab'] = array(
      'tab' => homecoop_member_tab_content($entity),
      '#weight' => 10,
    );
  }
  
  if ($entity->CanModify) {
    $form['maintable']['buttons'] = array(
      '#weight' => 20,
      'btn_save' => array(
        '#type' => 'submit',
        '#name' => 'btn_save',
        '#id' => 'btn_save',
        '#submit' => array('homecoop_member_form_save'),
        '#executes_submit_callback' => true,
        '#validate' => array('homecoop_member_form_validate'),
        '#value' => t('Save'),
        '#suffix' => '&nbsp;',
        '#weight' => 10, 
      ),
    );
    
    if ($entity->ID > 0) {
      $form['maintable']['buttons']['addlink'] = array(
        '#prefix' => '<a href="' . url('hccoord/member') . '" >',
        '#markup' =>  '<img border="0" title="' . t('Add') . '" src="' . homecoop_getthemepath() . 'img/edit-add-2.png" />',
        '#suffix' => '</a>&nbsp;',
        '#weight' => 5, 
      );
      
      $arrActions = array(
        Member::POST_ACTION_ACTIVATE => t('Restore Permissions'),
        Member::POST_ACTION_DEACTIVATE => t('Remove Permissions'),
      );     
      
      $form['maintable']['buttons']['select_action'] = array(
        '#type' => 'select',
        '#name' => 'select_action',
        '#id' => 'select_action',
        '#key_type' => 'associative',
        '#title' => t('Select action'),
        '#title_display' => 'attribute',
        '#options' => $arrActions,
        '#empty_value' => 0,
        '#empty_option' => t('Select action'),
        '#default_value' => 0,
        '#weight' => 30,
        '#ajax' => array(
          'callback' => 'homecoop_member_form_ajax_callback',
          'wrapper' => 'div_ajax_message',
        ),
      );
      
      if ($entity->hasdeletepermission) {
        $form['maintable']['buttons']['lnk_delete'] = array(
            '#markup' => l(t('Delete'), "hccoord/member/$entity->ID/delete"),
            '#weight' => 45,
        );
      }
    }
    
  } //end can modify
  
  
  
  //form input controls
  $form['maintable']['controlstable']['txtName'] = array(
      '#weight' => 10, 
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#maxlength' => 100,
      '#size' => 25,
      '#default_value' => check_plain($entity->Name),
      '#required' => TRUE,
      '#disabled' => !$entity->CanModify,
  );
  
  $form['maintable']['controlstable']['txtLoginName'] = array(
      '#weight' => 20, 
      '#maxlength' => 30,
      '#size' => 25,
      '#type' => 'textfield',
      '#title' => t('User name'),
      '#default_value' => check_plain($entity->LoginName),
      '#required' => $entity->ID == 0,
      //read only for existing record 
      //in order to allow coordinators to identify the member
      //throughout hir name changes
      '#disabled' => $entity->ID > 0,
  );
  
  $form['maintable']['controlstable']['txtNewPassword'] = array(
      '#weight' => 30, 
      '#size' => 25,
      '#type' => 'password_confirm',
      '#title' => t('New Password'),
      //no default value for better security
      '#required' => ($entity->ID == 0),
      '#disabled' => !$entity->CanModify,
  );
  
  $form['maintable']['controlstable']['txtBalance'] = array(
      '#weight' => 40, 
      '#type' => 'textfield',
      '#title' => t('Balance'),
      '#maxlength' => 30,
      '#size' => 25,
      '#default_value' => check_plain($entity->Balance),
      '#disabled' => !$entity->CanModify,
      '#rules' => array('numeric'),
      '#number_type' => 'decimal',
  );
  
  $form['maintable']['controlstable']['txtBalanceHeld'] = array(
      '#weight' => 50, 
      '#type' => 'textfield',
      '#title' => t('Balance Held'),
      '#maxlength' => 30,
      '#size' => 25,
      '#default_value' => check_plain($entity->BalanceHeld),
      '#disabled' => !$entity->CanModify,
      '#rules' => array('numeric'),
      '#number_type' => 'decimal',
  );
  
  if ($entity->CanModify) {
    $form['maintable']['controlstable']['selPickupLocationID'] = array(
        '#type' => 'select',
        '#key_type' => 'associative',
        '#title' => t('Cashier'),
        '#options' => homecoop_list_cachiers(),
        '#weight' => 60,
        '#description' => t('Cashier of balance change'),
     );
  }
  
  $form['maintable']['controlstable']['selPaymentMethodID'] = array(
        '#type' => 'select',
        '#key_type' => 'associative',
        '#title' => t('Payment Method'),
        '#default_value' => $entity->PaymentMethodID,
        '#options' => homecoop_list_payment_methods(),
        '#weight' => 70,
        '#disabled' => !$entity->CanModify,
        '#required' => TRUE,
  );
  
  
  $form['maintable']['controlstable']['txtPercentOverBalance'] = array(
      '#weight' => 80, 
      '#type' => 'textfield',
      '#title' => t('% Over Balance'),
      '#maxlength' => 10,
      '#size' => 25,
      '#default_value' => check_plain($entity->PercentOverBalance),
      '#disabled' => !$entity->CanModify,
      '#rules' => array('numeric'),
      '#number_type' => 'float',
      '#description' => t('The percentage in which a member&#x27;s order can exceed hir balance. This rule is being applied only when the member&#x27;s payment method allows a percentage over balance.'),
  );
  
  $form['maintable']['controlstable']['txtEMail'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address'),
    '#default_value' => check_plain($entity->EMail),
    '#weight' => 100,
    '#maxlength' => 254,
    '#size' => 25,
    '#required' => TRUE,
    '#disabled' => !$entity->CanModify,
    '#rules' => array('email'),
  );
  
  $form['maintable']['controlstable']['txtEMail2'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address 2'),
    '#default_value' => check_plain($entity->EMail2),
    '#weight' => 110,
    '#maxlength' => 254,
    '#size' => 25,
    '#disabled' => !$entity->CanModify,
    '#rules' => array('email'),
  );
  
  $form['maintable']['controlstable']['txtEMail3'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address 3'),
    '#default_value' => check_plain($entity->EMail3),
    '#weight' => 110,
    '#maxlength' => 254,
    '#size' => 25,
    '#disabled' => !$entity->CanModify,
    '#rules' => array('email'),
  );
  
  $form['maintable']['controlstable']['txtEMail4'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address 4'),
    '#default_value' => check_plain($entity->EMail4),
    '#weight' => 110,
    '#maxlength' => 254,
    '#size' => 25,
    '#disabled' => !$entity->CanModify,
    '#rules' => array('email'),
  );
  
  $form['maintable']['controlstable']['ctlIsDisabled'] = array(
        '#type' => 'select',
        '#key_type' => 'associative',
        '#title' => t('Status'),
        '#default_value' => $entity->IsDisabled,
        '#options' => array(0 => t('Active'), 1 => t('Inactive')),
        '#weight' => 120,
        '#disabled' => !$entity->CanModify,
        '#required' => TRUE,
  );
  
  $form['maintable']['controlstable']['JoinedOn'] = array(
    '#markup' => $entity->JoinedOn,
    '#type' => 'item',
    '#title' => t('Joined On'),
    '#weight' => 130,
  );
  
  $form['maintable']['controlstable']['txtComments'] = array(
    '#type' => 'textarea',
    '#title' => t('Comments'),
    '#default_value' => check_plain($entity->Comments),
    '#weight' => 140,
    '#maxlength' => 300,
    '#size' => 25,
    '#disabled' => !$entity->CanModify,
  );
  
  //field_attach_form('homecoop_member', $entity, $form, $form_state);
  
  return $form;
}

function homecoop_page_member_common_start()
{
  homecoop_authenticated_page();
  
  $oRecord = new Member;
   
  //must be coordinator to enter this page
  if (!$oRecord->CheckAccess() || (!$oRecord->IsCoordinator && !$oRecord->HasPermission(Member::PERMISSION_VIEW)))
  {
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
}

function homecoop_member_form_validate($form, &$form_state) { 
    
  $entity = homecoop_page_member_get_submitted_entity($form_state);
  
  $oRecord = entity_get_controller('homecoop_member')->toClass($entity);
  if (!$oRecord->Validate()) {  
    return;
  }
  
  //Field API validation
  //field_attach_form_validate('homecoop_member', $entity, $form, $form_state);
}

function homecoop_member_form_save($form, &$form_state) {  
  
  $entity = $form_state['homecoop_member'];
  
  // Notify field widgets.
  //field_attach_submit('homecoop_member', $entity, $form, $form_state);

  $entity = entity_get_controller('homecoop_member')->save($entity);
  
  if (!$entity) {
    drupal_set_message(t('Record was not saved. You may not have sufficent permissions or an error has occured.'), 'error', false);
    return;
  }
    
  if ($entity->IsNew) {
    $form_state['redirect'] = 'hccoord/member/' . $entity->ID;
  }

  //won't work without rebuild while it should have (and rebuild vanishes the header...)
  drupal_set_message(t('Record saved successfully.'), 'status', true);
}

function homecoop_page_member_get_submitted_entity(&$form_state) {
  $entity = $form_state['homecoop_member'];
  if ( isset($form_state['values']['hidPostValue'] ) && !empty($form_state['values']['hidPostValue'])) {
      $entity->ID = intval($form_state['values']['hidPostValue']);
    }
    
  if ( isset( $form_state['values']['hidOriginalData'] ) ) {
    $entity->OriginalData = $form_state['values']['hidOriginalData'];
  }
  
  if ( isset( $form_state['values']['txtName'] )) {
    $entity->Name = codeop_util_null_or_trimmed_value($form_state['values']['txtName']);
  }
  
  if (($entity->ID == 0) && isset( $form_state['values']['txtLoginName'])) { //login name can be set only once for a new member 
    $entity->LoginName = codeop_util_null_or_trimmed_value($form_state['values']['txtLoginName']);
  }
  
  if ( isset( $form_state['values']['selPaymentMethodID'])) {
    $entity->PaymentMethodID = intval($form_state['values']['selPaymentMethodID']);
  }
  
  if ( isset( $form_state['values']['selPickupLocationID'])) {
    $entity->PickupLocationID = intval($form_state['values']['selPickupLocationID']);
  }
  
  if ( isset( $form_state['values']['txtBalance'] )) {
      $entity->Balance = codeop_util_null_or_trimmed_number($form_state['values']['txtBalance']);
  }
  
  if ( isset( $form_state['values']['txtBalanceHeld'] )) {
      $entity->BalanceHeld = codeop_util_null_or_trimmed_number($form_state['values']['txtBalanceHeld']);
  }
  
  if ( isset( $form_state['values']['txtPercentOverBalance'] )) {
      $entity->PercentOverBalance = codeop_util_null_or_trimmed_number($form_state['values']['txtPercentOverBalance']);
  }
  
  if ( isset( $form_state['values']['txtEMail'] )) {
    $entity->EMail = codeop_util_null_or_trimmed_value($form_state['values']['txtEMail']);
  }
  
  if ( isset( $form_state['values']['txtEMail2'] )) {
    $entity->EMail2 = codeop_util_null_or_trimmed_value($form_state['values']['txtEMail2']);
  }
  
  if ( isset( $form_state['values']['txtEMail3'] )) {
    $entity->EMail3 = codeop_util_null_or_trimmed_value($form_state['values']['txtEMail3']);
  }
  
  if ( isset( $form_state['values']['txtEMail4'] )) {
    $entity->EMail4 = codeop_util_null_or_trimmed_value($form_state['values']['txtEMail4']);
  }
  
  if ( isset( $form_state['values']['ctlIsDisabled'] )) {
    $entity->IsDisabled = (intval($form_state['values']['ctlIsDisabled']) == 1);
  }
    
  if ( isset( $form_state['values']['txtComments'] )) {
    $entity->Comments = codeop_util_null_or_trimmed_value($form_state['values']['txtComments']);
  }
  
  if ( isset( $form_state['values']['txtNewPassword'] )) {
    $entity->NewPassword = codeop_util_null_or_trimmed_value($form_state['values']['txtNewPassword']);
  }
  
  $form_state['homecoop_member'] = $entity;
  return $entity;
}

function homecoop_page_member_delete_confirm($form, &$form_state, $entity) {  
  
  $form['MemberID'] = array('#type' => 'value', '#value' => $entity->ID);
  
  return confirm_form($form, 
    t('Please confirm the delete operation.'),
    'hccoord/members',
    t('This action will succeed only when there are no orders linked to %title. To block a member from signing in, remove hir permissions instead.',
        array('%title' => $entity->Name)),
    t('Delete'), 
    t('Cancel')
  );
}

function homecoop_page_member_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $id = $form_state['values']['MemberID'];
    
    if (!entity_get_controller('homecoop_member')->delete(array($id))) {
      drupal_set_message(t('The record was not deleted.'), 'error', false);
      return;
    }
    
    drupal_set_message(t('Member has been deleted.'));
    
    $form_state['redirect'] = 'hccoord/members';
  }
}

/*
 * Action ajax callback
 */
function homecoop_member_form_ajax_callback($form, &$form_state) {
  global $g_oMemberSession;
  
  //ajax
  if(!isset($g_oMemberSession)) {
    homecoop_authenticated_page();
  }
  $id = $form_state['values']['hidPostValue'];
  $action = intval($form_state['values']['select_action']);
  
  $ret_val = FALSE;
  $command = NULL;
  //$arrScript = array();
  
  switch ($action) {
    case Member::POST_ACTION_ACTIVATE:
      $ret_val = entity_get_controller('homecoop_member')->activate(array($id));
      if ($ret_val) {
        drupal_set_message(t('Permissions restored successfully'), 'status', false);
      }
      else {
        drupal_set_message(t('Permissions restore failed'), 'error', false);
      }
      $command = 'Activate';
      break;
    case Member::POST_ACTION_DEACTIVATE:
      $ret_val = entity_get_controller('homecoop_member')->deactivate(array($id));
      if ($ret_val) {
        drupal_set_message(t('Permissions removed successfully'), 'status', false);
      }
      else {
        drupal_set_message(t('Permissions remove failed'), 'error', false);
      }
      $command = 'Deactivate';
      break;
    default:
      return array();
  }
  
  $commands = array();
  
  $element = array('messages' => array(
                      '#type' => 'markup',
                        '#markup' => theme('status_messages'))
        );

  //message display command
  $commands[] = ajax_command_html('#div_ajax_message' , render($element));
  
  //post script command
  $commands[] = array (
    'command' => $command,
    'success' => $ret_val,
  );

  return array('#type' => 'ajax', '#commands' => $commands);
}