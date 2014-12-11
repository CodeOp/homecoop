<?php

function homecoop_page_profile() {
  homecoop_authenticated_page();
  
  global $g_oMemberSession;
  $oRecord = new Member;
  
  $oRecord->ID = $g_oMemberSession->MemberID;
  if (!$oRecord->CheckAccess())
  {
       drupal_goto(Consts::URL_ACCESS_DENIED);
       return;
  }
  
  drupal_set_title(t('My Profile'));
  
  $entity = homecoop_member_load($g_oMemberSession->MemberID);
  
  return drupal_get_form('homecoop_profile_form', $entity);
  
  /*if(!$oRecord->LoadRecord( $g_oMemberSession->MemberID ))
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
  }*/
  
  
}

function homecoop_profile_form($form, &$form_state, $entity) {
  
  $form['#id'] = 'homecoop_profile-form';
  $form['#attributes']['name'] = 'homecoop_profile_form';
  // Save the entity for later, in case we need it.
  $form_state['homecoop_member'] = $entity;
  
  $form['hidOriginalData'] = array('#type' => 'value', '#value' => $entity->OriginalData, 
    '#attributes' => array('id' => 'hidOriginalData'));
  
  $form['maintable'] = array(
    '#weight' => 10,
    'buttons' => array(
      'btn_save' => array(
        '#type' => 'submit',
        '#name' => 'btn_save',
        '#id' => 'btn_save',
        '#submit' => array('homecoop_profile_form_save'),
        '#executes_submit_callback' => true,
        '#validate' => array('homecoop_profile_form_validate'),
        '#value' => t('Save'),
        '#suffix' => '&nbsp;',
        '#weight' => 10, 
      ),
    ),
    'controlstable' => array(
      '#weight' => 50,
    ),
  );
  
  $form['maintable']['controlstable']['txtName'] = array(
      '#weight' => 10, 
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#maxlength' => 100,
      '#size' => 25,
      '#default_value' => check_plain($entity->Name),
      '#required' => TRUE,
  );

  //login name is read only for existing members 
  //in order to allow coordinators to identify the member
  //throughout hir name changes
  $form['maintable']['controlstable']['txtLoginName'] = array(
      '#weight' => 20, 
      '#markup' => check_plain($entity->LoginName),
      '#type' => 'item',
      '#title' => t('User name'),
  );
  
  $form['maintable']['controlstable']['txtNewPassword'] = array(
      '#weight' => 30, 
      '#size' => 25,
      '#type' => 'password_confirm',
      '#title' => t('New Password'),
      //no default value for better security
      '#required' => FALSE,
  );
  
  $form['maintable']['controlstable']['txtBalance'] = array(
      '#weight' => 35, 
      '#markup' => $entity->Balance,
      '#type' => 'item',
      '#title' => t('Balance'),
  );
  
  if ($entity->Balance != $entity->BalanceHeld) {
    $form['maintable']['controlstable']['txtBalanceHeld'] = array(
      '#weight' => 40, 
      '#markup' => $entity->BalanceHeld,
      '#type' => 'item',
      '#title' => t('Balance for withdrawal'),
    );
  }
  
  $form['maintable']['controlstable']['txtPaymentMethodName'] = array(
      '#weight' => 35, 
      '#markup' => $entity->PaymentMethodName,
      '#type' => 'item',
      '#title' => t('Payment Method'),
  );
  
  $form['maintable']['controlstable']['txtPercentOverBalance'] = array(
      '#weight' => 35,
      '#markup' => $entity->PercentOverBalance,
      '#type' => 'item',
      '#title' => t('% Over Balance'),
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
    '#rules' => array('email'),
  );
  
  $form['maintable']['controlstable']['txtEMail2'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address 2'),
    '#default_value' => check_plain($entity->EMail2),
    '#weight' => 110,
    '#maxlength' => 254,
    '#size' => 25,
    '#rules' => array('email'),
  );
  
  $form['maintable']['controlstable']['txtEMail3'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address 3'),
    '#default_value' => check_plain($entity->EMail3),
    '#weight' => 110,
    '#maxlength' => 254,
    '#size' => 25,
    '#rules' => array('email'),
  );
  
  $form['maintable']['controlstable']['txtEMail4'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address 4'),
    '#default_value' => check_plain($entity->EMail4),
    '#weight' => 110,
    '#maxlength' => 254,
    '#size' => 25,
    '#rules' => array('email'),
  );
  
  $form['maintable']['controlstable']['JoinedOn'] = array(
    '#markup' => $entity->JoinedOn,
    '#type' => 'item',
    '#title' => t('Joined On'),
    '#weight' => 130,
  );
  
  $form['maintable']['controlstable']['FileFormat'] = array(
        '#type' => 'select',
        '#key_type' => 'associative',
        '#title' => t('File Format'),
        '#default_value' => $entity->ExportFormat,
        '#options' => array(Consts::EXPORT_FORMAT_MS_EXCEL_XML => 'MS Excel xml',
                                      Consts::EXPORT_FORMAT_LIBRE_OFFICE_FLAT_ODS => 'Libre Office flat ods'),
        '#weight' => 140,
        '#description' => t('The preferred file format for data exports.'),
  );

  
  return $form;
  
}