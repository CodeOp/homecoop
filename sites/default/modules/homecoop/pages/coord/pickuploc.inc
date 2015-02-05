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
  homecoop_add_js_file('pickup_location.js');
  
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

  $txtName = array(
    'element' => array(
      '#type' => 'textfield',
      '#required' => TRUE,
    ),
    'title' => t('Location Name'),
    'ID' => 'txtName',
    'values' => $entity->Names,
  );
  
  $weight = 10;
  
  $form['maintable']['controlstable']['pickuplocname'] = array(
    'namerow' => codeop_util_multilang_element($txtName),
    '#weight' => $weight,
  );
  unset($txtName);
    
  $txtAddress = array(
    'element' => array(
      '#type' => 'textarea',
      '#required' => TRUE,
    ),
    'title' => t('Address'),
    'ID' => 'txtAddress',
    'values' => $entity->AddressStrings,
  );           
     
  $weight += 10;
  $form['maintable']['controlstable']['pickuplocaddress'] = array(
    'namerow' => codeop_util_multilang_element($txtAddress),
    '#weight' => $weight,
  );              
  unset($txtAddress);
  
  $txtPublishedComments = array(
    'element' => array(
      '#type' => 'textarea',
      '#required' => TRUE,
    ),
    'title' => t('Pickup Instructions'),
    'ID' => 'txtPublishedComments',
    'values' => $entity->PublishedComments,
  ); 
  
  $weight += 10;
  $form['maintable']['controlstable']['publishedcomments'] = array(
    'namerow' => codeop_util_multilang_element($txtPublishedComments),
    '#weight' => $weight,
  );   
  unset($txtPublishedComments);
    
  $txtAdminComments = array(
    'element' => array(
      '#type' => 'textarea',
    ),
    'title' => t('Coordination Comments'),
    'ID' => 'txtAdminComments',
    'values' => $entity->AdminComments,
  ); 
  
  $weight += 10;
  $form['maintable']['controlstable']['admincomments'] = array(
    'namerow' => codeop_util_multilang_element($txtAdminComments),
    '#weight' => $weight,
  ); 
  unset($txtAdminComments);
  
  $weight += 10;
  $form['maintable']['controlstable']['ctlIsDisabled'] = array(
        '#type' => 'select',
        '#key_type' => 'associative',
        '#title' => t('Status'),
        '#default_value' => $entity->IsDisabled,
        '#options' => array(0 => t('Active'), 1 => t('Inactive')),
        '#weight' => $weight,
        '#required' => TRUE,
  );
  
  $weight += 10;
  $form['maintable']['controlstable']['txtRotationOrder'] = array(
      '#weight' => $weight, 
      '#type' => 'textfield',
      '#title' => t('Rotation Order'),
      '#maxlength' => 10,
      '#size' => 25,
      '#default_value' => check_plain($entity->RotationOrder),
      '#rules' => array('numeric'),
      '#number_type' => 'integer',
  );
  
  $weight += 10;
  $form['maintable']['controlstable']['txtMaxBurden'] = array(
      '#weight' => $weight, 
      '#type' => 'textfield',
      '#title' => t('Delivery Capacity'),
      '#maxlength' => 10,
      '#size' => 25,
      '#default_value' => check_plain($entity->MaxBurden),
      '#rules' => array('numeric'),
      '#number_type' => 'decimal',
      '#description' => t('The maximum capacity of the pickup location in terms of the product field &quot;Burden&quot;. the sum for all products of &quot;Burden&quot; times product quantity will be compared to this value for all the members&#x27; orders that have this pickup location selected. This is only a default value and can be overwritten in the cooperative order&#x27;s pickup location settings. If not overridden in the coop order, members will not be able to place an order that exceeds the limitation set here.'),
  );
  
  $weight += 10;
  $form['maintable']['controlstable']['txtCachier'] = array(
      '#weight' => $weight, 
      '#type' => 'textfield',
      '#title' => t('Cashier'),
      '#maxlength' => 10,
      '#size' => 25,
      '#default_value' => check_plain($entity->Cachier),
      '#rules' => array('numeric'),
      '#number_type' => 'decimal',
  );
  
  $weight += 10;
  $form['maintable']['controlstable']['txtTransaction'] = array(
      '#weight' => $weight, 
      '#type' => 'textfield',
      '#title' => t('Transaction Desc.'),
      '#maxlength' => 100,
      '#default_value' => check_plain($entity->Transaction),
  );
  
  if ($entity->ID > 0) {
    if (!empty($entity->CachierDate)) {
      $weight += 10;
      $form['maintable']['controlstable']['lblCachierDate'] = array(
          '#weight' => $weight, 
          '#type' => 'item',
          '#title' => t('Cashier Update'),
          '#attributes' => array('dir' => 'ltr'),
          '#markup' => $entity->CachierDate->format(HOMECOOP_DATE_TIME_FORMAT),
      );
    }

    if (!empty($entity->PrevCachier)) {
      $weight += 10;
      $form['maintable']['controlstable']['lblPrevCachier'] = array(
          '#weight' => $weight, 
          '#type' => 'item',
          '#title' => t('Prev. Cashier'),
          '#markup' => check_plain($entity->PrevCachier),
          '#attributes' => array('dir' => 'ltr'),
      );
    }
  }
  
  $weight += 10;
  $form['maintable']['controlstable']['txtExportFileName'] = array(
      '#weight' => $weight, 
      '#type' => 'textfield',
      '#title' => t('Export File Name'),
      '#maxlength' => PickupLocation::MAX_LENGTH_EXPORT_FILE_NAME,
      '#default_value' => check_plain($entity->ExportFileName),
  );
  
  // Storage Areas
  $oStorageAreaRow = NULL;
  $nTotalCount = 0;
  $nStorageCount = 0;

  if ($entity->ID > 0) 
  {
    foreach($entity->StorageAreas as $sa)
    {
      $weight += 10;
      $form['maintable']['controlstable']['sep'] = array(
        '#prefix' => '<div class="sepline">',
        '#suffix' => '</div>',
        '#weight' => $weight,
      );

      $nStorageCount++;
      $oStorageAreaRow = new HtmlStorageArea($sa, $nStorageCount);
      $form['maintable']['controlstable'] += $oStorageAreaRow->GetHtml($weight);
    }
  }
  $nTotalCount += $nStorageCount;
  //restore unsaved new entries after validation errors
  if (count($entity->NewStorageAreas) > 0)
  {
    foreach($entity->NewStorageAreas as $sa)
    {
      $weight += 10;
      $form['maintable']['controlstable']['sep'] = array(
        '#prefix' => '<div class="sepline">',
        '#suffix' => '</div>',
        '#weight' => $weight,
      );

      $nStorageCount++;
      $nTotalCount++;

      $oStorageAreaRow = new HtmlStorageArea($sa, $nStorageCount);
      $oStorageAreaRow->IsNew = TRUE;
      $oStorageAreaRow->Required = ($nTotalCount == 1);
      $form['maintable']['controlstable'] += $oStorageAreaRow->GetHtml($weight);
    }
  }
  //default behaviour for new form with no unsaved new entries to restore
  elseif ($entity->ID == 0)
  {
    $nStorageCount = 1;
    //add default storage area if not added
    $oStorageAreaRow = new HtmlStorageArea();
    $oStorageAreaRow->IsNew = TRUE;
    $form['maintable']['controlstable'] += $oStorageAreaRow->GetHtml($weight);
  }
  unset($oStorageAreaRow);
  
  $weight += 10;
  $form['maintable']['controlstable']['trPlaceHolder'] = array(
    '#prefix' => '<div class="resgridrow" id="trPlaceHolder" name="trPlaceHolder">',
    '#suffix' => '</div>',
    '#weight' => $weight,
  );
  
  $weight += 10;
  $form['maintable']['controlstable']['sep_after'] = array(
    '#prefix' => '<div class="sepline">',
    '#suffix' => '</div>',
    '#weight' => $weight,
  );
  
  $weight += 10;
  $form['maintable']['controlstable']['btn_add_storage'] = array(
    '#prefix' => '<div class="resgridrow">',
    '#type' => 'button',
    '#name' => 'btn_add_storage',
    '#id' => 'btn_add_storage',
    '#weight' => $weight,
    '#ajax' => array(
         'callback' => 'homecoop_pickup_location_addstoragearea_ajax_callback',
         'wrapper' => 'trPlaceHolder',
       ),
    '#suffix' => '</div>',
    '#value' => t('Add storage area'),
  );
  
  $form['hidStorageAreaCount'] = array('#type' => 'hidden', '#default_value' => $nStorageCount, 
    '#attributes' => array('id' => 'hidStorageAreaCount'));
     
  //field_attach_form('homecoop_pickup_location', $entity, $form, $form_state);
  
  return $form;
}

function homecoop_pickup_location_form_validate($form, &$form_state) { 
    
  $entity = homecoop_page_pickup_location_get_submitted_entity($form_state);
  
  $oRecord = entity_get_controller('homecoop_pickup_location')->toClass($entity);
  if (!$oRecord->Validate()) {  
    return;
  }
  
  //Field API validation
  //field_attach_form_validate('homecoop_pickup_location', $entity, $form, $form_state);
}

function homecoop_pickup_location_form_save($form, &$form_state) {  
  
  $entity = $form_state['homecoop_pickup_location'];
  
  // Notify field widgets.
  //field_attach_submit('homecoop_pickup_location', $entity, $form, $form_state);
  
  $entity = entity_get_controller('homecoop_pickup_location')->save($entity); //calls field_attach_insert/update
  
  if (!$entity) {
    drupal_set_message(t('Record was not saved. You may not have sufficent permissions or an error has occured.'), 'error', false);
    return;
  }

  if ($entity->IsNew) {
    $form_state['redirect'] = 'hccoord/pickuploc/' . $entity->ID;
  }

  //won't work without rebuild while it should have (and rebuild vanishes the header...)
  drupal_set_message(t('Record saved successfully.'), 'status', true);
}

function homecoop_page_pickup_location_get_submitted_entity(&$form_state) {
  $entity = $form_state['homecoop_pickup_location'];
  if ( isset($form_state['values']['hidPostValue'] ) && !empty($form_state['values']['hidPostValue'])) {
      $entity->ID = intval($form_state['values']['hidPostValue']);
    }
    
  if ( isset( $form_state['values']['hidOriginalData'] ) ) {
    $entity->OriginalData = $form_state['values']['hidOriginalData'];
  }
  
  $entity->Names = codeop_util_multilang_get_names($form_state, 'txtName');
  
  $entity->AddressStrings = codeop_util_multilang_get_names($form_state, 'txtAddress');
  
  $entity->PublishedComments = codeop_util_multilang_get_names($form_state, 'txtPublishedComments');
  
  $entity->AdminComments = codeop_util_multilang_get_names($form_state, 'txtAdminComments');
    
  if ( isset( $form_state['values']['txtMaxBurden'] )) {
      $entity->MaxBurden = codeop_util_null_or_trimmed_number($form_state['values']['txtMaxBurden']);
  }
  
  if ( isset( $form_state['values']['txtTransaction'] )) {
    $entity->Transaction = codeop_util_null_or_trimmed_value($form_state['values']['txtTransaction']);
  }
  
  if ( isset( $form_state['values']['txtRotationOrder'] )) {
      $entity->RotationOrder = codeop_util_null_or_trimmed_number($form_state['values']['txtRotationOrder']);
  }
          
  if ( isset( $form_state['values']['txtExportFileName'] )) {
    $entity->ExportFileName = codeop_util_null_or_trimmed_value($form_state['values']['txtExportFileName']);
  }
  
  if ( isset( $form_state['values']['ctlIsDisabled'] )) {
    $entity->IsDisabled = (intval($form_state['values']['ctlIsDisabled']) == 1);
  }
                        
  if ( isset( $form_state['values']['txtCachier'] )) {
      $entity->Cachier = codeop_util_null_or_trimmed_number($form_state['values']['txtCachier']);
  }
  
  homecoop_page_pickup_location_get_storageareas($form_state, $entity);
  
  $form_state['homecoop_pickup_location'] = $entity;
  return $entity;
}

//process post data and return an unkeyed array with each element in this format
// StorageAreaKeyID => id
// Names => return value from ComplexPostData::GetNames
// Disabled => TRUE/FALSE
// Delete => TRUE/FALSE
function homecoop_page_pickup_location_get_storageareas(&$form_state, $entity)
{
  $nStorageAreaKeyID = 0;
  $nNamePrefixLen = strlen(HtmlStorageArea::CTL_NAME_PREFIX);
  $nDisabledPrefixLen = strlen(HtmlStorageArea::CTL_DISABLED_PREFIX);
  $nMaxBurdenPrefixLen = strlen(HtmlStorageArea::CTL_MAX_BURDEN_PREFIX);
  $nDeletePrefixLen = strlen(HtmlStorageArea::CTL_DELETE_PREFIX);
  $nNewNamePrefixLen = strlen(HtmlStorageArea::CTL_NEW_NAME_PREFIX);
  $nNewDisabledPrefixLen = strlen(HtmlStorageArea::CTL_NEW_DISABLED_PREFIX);
  $nNewMaxBurdenPrefixLen = strlen(HtmlStorageArea::CTL_NEW_MAX_BURDEN_PREFIX);
  $sBaseCtlName = NULL;


  foreach($form_state['values'] as $key => $value)
  {
    //if found in position 0
    if (strpos($key, HtmlStorageArea::CTL_NAME_PREFIX) === 0)
    {
      $nStorageAreaKeyID = homecoop_page_pickup_location_get_storagearea_names_id($key, $nNamePrefixLen, $sBaseCtlName,
          'StorageAreas', $entity);

      $entity->StorageAreas[$nStorageAreaKeyID]['Names'] = 
          codeop_util_multilang_get_names($form_state,$sBaseCtlName);
    }
    elseif (strpos($key, HtmlStorageArea::CTL_DISABLED_PREFIX) === 0)
    {
      $nStorageAreaKeyID = homecoop_page_pickup_location_init_storagearea($key, $nDisabledPrefixLen,
          'StorageAreas', $entity);

      $entity->StorageAreas[$nStorageAreaKeyID]['bDisabled'] = (intval($value) == 1);
    }
    elseif (strpos($key, HtmlStorageArea::CTL_MAX_BURDEN_PREFIX) === 0)
    {
      $nStorageAreaKeyID = homecoop_page_pickup_location_init_storagearea($key, $nMaxBurdenPrefixLen,
          'StorageAreas', $entity);

      if (!empty($value)) //allow null, do not allow 0
        $entity->StorageAreas[$nStorageAreaKeyID]['fMaxBurden'] = 0 + $value;
    }
    elseif (strpos($key, HtmlStorageArea::CTL_DELETE_PREFIX) === 0)
    {
      $nStorageAreaKeyID = homecoop_page_pickup_location_init_storagearea($key, $nDeletePrefixLen,
          'StorageAreas', $entity);

      $entity->StorageAreas[$nStorageAreaKeyID]['Delete'] = (intval($value) == 1);
    }
    elseif (strpos($key, HtmlStorageArea::CTL_NEW_NAME_PREFIX) === 0)
    {
      $nStorageAreaKeyID = homecoop_page_pickup_location_get_storagearea_names_id($key, $nNewNamePrefixLen, $sBaseCtlName,
          'NewStorageAreas', $entity);

      $entity->NewStorageAreas[$nStorageAreaKeyID]['Names'] = 
          codeop_util_multilang_get_names($form_state,$sBaseCtlName);
    }
    elseif (strpos($key, HtmlStorageArea::CTL_NEW_DISABLED_PREFIX) === 0)
    {
      $nStorageAreaKeyID = homecoop_page_pickup_location_init_storagearea($key, $nNewDisabledPrefixLen,
          'NewStorageAreas', $entity);

      $entity->NewStorageAreas[$nStorageAreaKeyID]['bDisabled'] = (intval($value) == 1);
    }
    elseif (strpos($key, HtmlStorageArea::CTL_NEW_MAX_BURDEN_PREFIX) === 0)
    {
      $nStorageAreaKeyID = homecoop_page_pickup_location_init_storagearea($key, $nNewMaxBurdenPrefixLen,
          'NewStorageAreas', $entity);

      if (!empty($value)) //allow null, do not allow 0
        $entity->NewStorageAreas[$nStorageAreaKeyID]['fMaxBurden'] = 0 + $value;
    }
  }

  //set the Default property
  //get default value
  if (isset($form_state['values'][HtmlStorageArea::CTL_DEFAULT_GROUP]))
  {
    $nDefaultStorageAreaID = intval($form_state['values'][HtmlStorageArea::CTL_DEFAULT_GROUP]);
    if ($nDefaultStorageAreaID >= HtmlStorageArea::MIN_NEW_CONTROLS_NUM)
    {
      $nDefaultStorageAreaID -= HtmlStorageArea::MIN_NEW_CONTROLS_NUM;
      if (isset($entity->NewStorageAreas[$nDefaultStorageAreaID]))
        $entity->NewStorageAreas[$nDefaultStorageAreaID]['bDefault'] = TRUE;
    }
    elseif (isset($entity->StorageAreas[$nDefaultStorageAreaID]))
      $entity->StorageAreas[$nDefaultStorageAreaID]['bDefault'] = TRUE;
  }

}

function homecoop_page_pickup_location_get_storagearea_names_id($key, $nPrefixLen, &$sBaseCtlName, $sStorageArrKey, $entity)
{
  $sIDPlusLang = substr($key, $nPrefixLen );

  $nPos = strpos($sIDPlusLang, '-');
  if ($nPos > 0)
  {
    $nStorageAreaKeyID = 0 + substr($sIDPlusLang, 0, $nPos );
    $sBaseCtlName = substr($key, 0, $nPrefixLen + $nPos );
  }

  return homecoop_page_pickup_location_init_storagearea_by_id($key, $nStorageAreaKeyID, $sStorageArrKey, $entity);
}

function homecoop_page_pickup_location_init_storagearea($key, $nPrefixLen, $sStorageArrKey, $entity)
{
  $nStorageAreaKeyID = 0 + substr($key, $nPrefixLen );;

  return homecoop_page_pickup_location_init_storagearea_by_id($key, $nStorageAreaKeyID, $sStorageArrKey, $entity);
}

function homecoop_page_pickup_location_init_storagearea_by_id($key, $nStorageAreaKeyID, $sStorageArrKey, $entity)
{
  if ($nStorageAreaKeyID == 0)
    throw new Exception('Error in homecoop_page_pickup_location_init_storagearea: StorageAreaKeyID 0 for key ' . $key);

  if (!array_key_exists($nStorageAreaKeyID, $entity->$sStorageArrKey))
  {
    $entity->$sStorageArrKey[$nStorageAreaKeyID] = array(
      'StorageAreaKeyID' => $nStorageAreaKeyID,
      'Names' => NULL,
      'fMaxBurden' => NULL,
      'bDisabled' => FALSE,
      'Delete' => FALSE,
      'bDefault' => FALSE,
    );
  }

  return $nStorageAreaKeyID;
}

function homecoop_pickup_location_addstoragearea_ajax_callback($form, &$form_state) {
  global $g_oMemberSession;
  
  //ajax
  if(!isset($g_oMemberSession)) {
    homecoop_authenticated_page();
  }
  
  $commands = array();
  
  $weight = 0;
  $element = array(
    'sep_before' => array(
      '#prefix' => '<div class="sepline">',
      '#suffix' => '</div>',
      '#weight' => $weight,
    )
  );
  
  $form['maintable']['controlstable']['sep'] = array(
        '#prefix' => '<div class="sepline">',
        '#suffix' => '</div>',
        '#weight' => $weight,
      );

  $nStorageCount = $form_state['values']['hidStorageAreaCount'];
  $nStorageCount++;
  
  $form['hidStorageAreaCount']['#value'] =  $nStorageCount;
  //add default storage area if not added
  $oStorageAreaRow = new HtmlStorageArea(NULL, $nStorageCount);
  $oStorageAreaRow->IsNew = TRUE;
  $weight += 10;
  $element += $oStorageAreaRow->GetHtml($weight);
    
  $weight += 10;
  $element['trPlaceHolder'] = array(
    '#prefix' => '<div class="resgridrow" id="trPlaceHolder" name="trPlaceHolder">',
    '#suffix' => '</div>',
    '#weight' => $weight,
  );

  //message display command
  $commands[] = ajax_command_html('#trPlaceHolder' , render($element));
  
  //post script command
  $commands[] = array (
    //'command' => 'AddStorageArea',
    'success' => TRUE,
  );

  return array('#type' => 'ajax', '#commands' => $commands);
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