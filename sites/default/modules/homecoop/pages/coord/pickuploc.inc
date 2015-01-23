<?php

function homecoop_page_pickuploc_add() {
  homecoop_page_pickuploc_common_start();
  
  $entity = entity_get_controller('homecoop_pickup_location')->create();
  
  drupal_set_title(t('New Pickup Location'));
  
  return drupal_get_form('homecoop_pickup_location_form', $entity);
}

function homecoop_page_pickuploc_edit($entity) {
  homecoop_page_pickuploc_common_start();
  
  drupal_set_title($entity->Name);
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return drupal_get_form('homecoop_pickup_location_form', $entity);
}

function homecoop_page_pickuploc_common_start()
{
  homecoop_authenticated_page();
  
  $oRecord = new PickupLocation;
  
  if (!$oRecord->CheckAccess())
  {
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
}

function homecoop_pickup_location_form($form, &$form_state, $entity) {
  
  $form['#id'] = 'homecoop_pickup_location-form';
  $form['#attributes']['name'] = 'homecoop_pickup_location_form';
  // Save the entity for later, in case we need it.
  $form_state['homecoop_pickup_location'] = $entity;
  
  //internal values
  $form['hidOriginalData'] = array('#type' => 'value', '#value' => $entity->OriginalData, 
    '#attributes' => array('id' => 'hidOriginalData'));
  
  $form['hidPostValue'] = array('#type' => 'value', '#value' => $entity->ID, 
    '#attributes' => array('id' => 'hidPostValue'));
  
  $form['maintable'] = array(
    '#weight' => 10,
    'controlstable' => array(
      '#weight' => 50,
    ),
  );
  
  if ($entity->ID > 0) {
    $form['maintable']['pickuploctab'] = array(
      'tab' => homecoop_pickup_location_tab_content($entity),
      '#weight' => 10,
    );
  }
  
  $form['maintable']['buttons'] = array(
      '#weight' => 20,
      'btn_save' => array(
        '#type' => 'submit',
        '#name' => 'btn_save',
        '#id' => 'btn_save',
        '#submit' => array('homecoop_pickup_location_form_save'),
        '#executes_submit_callback' => true,
        '#validate' => array('homecoop_pickup_location_form_validate'),
        '#value' => t('Save'),
        '#suffix' => '&nbsp;',
        '#weight' => 10, 
      ),
    );
  
  if ($entity->hasdeletepermission) {
    $form['maintable']['buttons']['lnk_delete'] = array(
        '#markup' => l(t('Delete'), "hccoord/pickuploc/$entity->ID/delete"),
        '#weight' => 20,
    );
  }
  
  $form['maintable']['controlstable'] = array(
    '#weight' => 30,
    '#prefix' => '<div class="resgridparent">',
    '#suffix' => '</div>',
  );
  
  $txtName = new HtmlTextEditMultiLang(t('Location Name'), 'txtName', HtmlTextEdit::TEXTBOX, $entity->Names);
  $txtName->Required = TRUE;
  $form['maintable']['controlstable']['pickuplocname'] = array(
    '#prefix' => '<div class="resgridrow">',
    'namerow' => $txtName->GetHtml(),
    '#suffix' => '</div>',
    '#weight' => 10,
  );
  unset($txtName);
  
  $txtAddress = new HtmlTextEditMultiLang(t('Address'), 'txtAddress', HtmlTextEdit::TEXTAREA, $entity->AddressStrings);
                $txtAddress->Required = TRUE;
  $form['maintable']['controlstable']['pickuplocaddress'] = array(
    '#prefix' => '<div class="resgridrow">',
    'namerow' => $txtAddress->GetHtml(),
    '#suffix' => '</div>',
    '#weight' => 20,
  );              
  unset($txtAddress);
  
  
  $txtPublishedComments = new HtmlTextEditMultiLang(t('Pickup Instructions'), 'txtPublishedComments', 
          HtmlTextEdit::TEXTAREA, $entity->PublishedComments);
  
  $form['maintable']['controlstable']['publishedcomments'] = array(
    '#prefix' => '<div class="resgridrow">',
    'namerow' => $txtPublishedComments->GetHtml(),
    '#suffix' => '</div>',
    '#weight' => 30,
  );   
  unset($txtPublishedComments);
  
  $txtAdminComments = new HtmlTextEditMultiLang(t('Coordination Comments'), 'txtAdminComments', HtmlTextEdit::TEXTAREA, 
          $entity->AdminComments);
  $form['maintable']['controlstable']['admincomments'] = array(
    '#prefix' => '<div class="resgridrow">',
    'namerow' => $txtAdminComments->GetHtml(),
    '#suffix' => '</div>',
    '#weight' => 30,
  ); 
  unset($txtAdminComments);
  
  $form['maintable']['controlstable']['ctlIsDisabled'] = array(
        '#type' => 'select',
        '#key_type' => 'associative',
        '#title' => t('Status'),
        '#default_value' => $entity->IsDisabled,
        '#options' => array(0 => t('Active'), 1 => t('Inactive')),
        '#weight' => 40,
        '#required' => TRUE,
  );
  
  $form['maintable']['controlstable']['txtRotationOrder'] = array(
      '#weight' => 50, 
      '#type' => 'textfield',
      '#title' => t('Rotation Order'),
      '#maxlength' => 10,
      '#size' => 25,
      '#default_value' => check_plain($entity->RotationOrder),
      '#rules' => array('numeric'),
      '#number_type' => 'integer',
  );
  
  $form['maintable']['controlstable']['txtMaxBurden'] = array(
      '#weight' => 60, 
      '#type' => 'textfield',
      '#title' => t('Delivery Capacity'),
      '#maxlength' => 10,
      '#size' => 25,
      '#default_value' => check_plain($entity->MaxBurden),
      '#rules' => array('numeric'),
      '#number_type' => 'decimal',
      '#description' => t('The maximum capacity of the pickup location in terms of the product field &quot;Burden&quot;. the sum for all products of &quot;Burden&quot; times product quantity will be compared to this value for all the members&#x27; orders that have this pickup location selected. This is only a default value and can be overwritten in the cooperative order&#x27;s pickup location settings. If not overridden in the coop order, members will not be able to place an order that exceeds the limitation set here.'),
  );
  
  $form['maintable']['controlstable']['txtCachier'] = array(
      '#weight' => 70, 
      '#type' => 'textfield',
      '#title' => t('Cashier'),
      '#maxlength' => 10,
      '#size' => 25,
      '#default_value' => check_plain($entity->Cachier),
      '#rules' => array('numeric'),
      '#number_type' => 'decimal',
  );
  
  $form['maintable']['controlstable']['txtTransaction'] = array(
      '#weight' => 80, 
      '#type' => 'textfield',
      '#title' => t('Transaction Desc.'),
      '#maxlength' => 100,
      '#default_value' => check_plain($entity->Transaction),
  );
  
  if ($entity->ID > 0) {
    if (!empty($entity->CachierDate)) {
      $form['maintable']['controlstable']['lblCachierDate'] = array(
          '#weight' => 90, 
          '#type' => 'item',
          '#title' => t('Cashier Update'),
          '#attributes' => array('dir' => 'ltr'),
          '#markup' => $entity->CachierDate->format(HOMECOOP_DATE_TIME_FORMAT),
      );
    }

    if (!empty($entity->PrevCachier)) {
      $form['maintable']['controlstable']['lblPrevCachier'] = array(
          '#weight' => 100, 
          '#type' => 'item',
          '#title' => t('Prev. Cashier'),
          '#markup' => check_plain($entity->PrevCachier),
          '#attributes' => array('dir' => 'ltr'),
      );
    }
  }
  
  $form['maintable']['controlstable']['txtExportFileName'] = array(
      '#weight' => 110, 
      '#type' => 'textfield',
      '#title' => t('Export File Name'),
      '#maxlength' => PickupLocation::MAX_LENGTH_EXPORT_FILE_NAME,
      '#default_value' => check_plain($entity->ExportFileName),
  );
  
  field_attach_form('homecoop_pickup_location', $entity, $form, $form_state);
  
  return $form;
}

function homecoop_pickup_location_form_validate($form, &$form_state) { 
    
  $entity = homecoop_page_pickup_location_get_submitted_entity($form_state);
  
  $oRecord = entity_get_controller('homecoop_pickup_location')->toClass($entity);
  if (!$oRecord->Validate()) {  
    return;
  }
  
  //Field API validation
  field_attach_form_validate('homecoop_pickup_location', $entity, $form, $form_state);
}




//todo: unfinished
function homecoop_page_pickup_location_get_submitted_entity(&$form_state) {
  $entity = $form_state['homecoop_pickup_location'];
  if ( isset($form_state['values']['hidPostValue'] ) && !empty($form_state['values']['hidPostValue'])) {
      $entity->ID = intval($form_state['values']['hidPostValue']);
    }
    
  if ( isset( $form_state['values']['hidOriginalData'] ) ) {
    $entity->OriginalData = $form_state['values']['hidOriginalData'];
  }
  
  //todo: get multilingual field value
  //if ( isset( $form_state['values']['txtName'] )) {
    //$entity->Name = codeop_util_null_or_trimmed_value($form_state['values']['txtName']);
  //}
  
    
  /*if ( isset( $form_state['values']['selPaymentMethodID'])) {
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
  }*/
  
  $form_state['homecoop_pickup_location'] = $entity;
  return $entity;
}

function homecoop_page_pickup_location_delete_confirm($form, &$form_state, $entity) {  
  
  $form['PickupLocationID'] = array('#type' => 'value', '#value' => $entity->ID);
  
  return confirm_form($form, 
    t('Please confirm the delete operation.'),
    'hccoord/pickuplocs',
    t('This action will succeed only when there are no records linked to %title. If it fails, deactivate the pickup location instead.',
        array('%title' => $entity->Name)),
    t('Delete'), 
    t('Cancel')
  );
}

function homecoop_page_pickup_location_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $id = $form_state['values']['PickupLocationID'];
    
    if (!entity_get_controller('homecoop_pickup_location')->delete(array($id))) {
      drupal_set_message(t('The record was not deleted.'), 'error', false);
      return;
    }
    
    drupal_set_message(t('Pickup location has been deleted.'));
    
    $form_state['redirect'] = 'hccoord/pickuplocs';
  }
}