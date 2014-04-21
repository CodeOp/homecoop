<?php

function homecoop_page_login() { 
  drupal_set_title(t('Login'), PASS_THROUGH);
  
  homecoop_include_app_file('settings');
  
  return drupal_get_form('homecoop_page_login_form');
}

function homecoop_page_login_form($form, &$form_state) {
  // Set the id to identify this as a record edit form.
  $form['#id'] = 'homecoop_page_login_form';
    
  $sLoginName = '';
  if (isset($form_state['values']['login'])) {
    $sLoginName = trim($form_state['values']['login']);
  }
  
  // Set fields
  $form['login'] = array(
    '#type' => 'textfield',
    '#title' => t('Login Name'),
    '#default_value' => $sLoginName,
    '#weight' => 0,
    '#maxlength' => 128,
    '#required' => TRUE,
    '#attributes' => array(
      'class' => array(
        'dataentrysmall',
      ),
    ),
  );
  
  $form['pass'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#weight' => 1,
    '#maxlength' => 128,
    '#required' => TRUE,
    '#attributes' => array(
      'class' => array(
        'dataentrysmall',
      ),
    ),
  );
  
  //Add the buttons
  $form['buttons'] = array();
  $form['buttons']['#weight'] = 100;
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Login'),
    '#weight' => 100,
    '#submit' => array('homecoop_page_login_form_submit'),
  );
  
  $form['#validate'][] = 'homecoop_page_login_form_validate';
    
  return $form;
}

function homecoop_page_login_form_validate($form, &$form_state) { 
  global $g_oError;
  //skip iterations invoked by ajax
  if (!isset($form_state['submitted']) || !$form_state['submitted'])  {
    return;
  }
  
  $oLogin = new Login;
  
  //encrypt password
  if (isset($form_state['values']['pass'])) {
    $oLogin->Password = trim($form_state['values']['pass']);
    //do not store plain password from now on
    unset($form_state['values']['pass']);
  }
     
  if (isset($form_state['values']['login'])) {
    $oLogin->LoginName = trim($form_state['values']['login']);
  }
  
  $nLoginFlags = $oLogin->DoLogin ();
  
  $oLogin->Password = '';
  
  if (!is_object($g_oError))
    $g_oError = new ErrorHandler();
  
  if ( $nLoginFlags != 0 )
  {
    switch(  $nLoginFlags )
    {
        case Login::ERR_LOGIN_INCORRECT_NAME_PASSWORD:
            $g_oError->AddError(t('Incorrect User name or password.'));
            break;
        case Login::ERR_LOGIN_NAME_EMPTY:
            form_set_error('login', t('User name is required.'));
            break;
        case Login::ERR_LOGIN_PASSWORD_EMPTY:
            form_set_error('pass', t('User name is required.'));
            break;
        case Login::ERR_NO_PERMISSIONS:
            $g_oError->AddError(
                t('Your account has no permissions at all. If this is a mistake, please contact us at @adminemail to correct the problem', 
                 array('@adminemail' => COOP_ADDRESS_MEMBER_PERMISSIONS)));
            break;
        case Login::ERR_MEMBER_DISABLED:
            $g_oError->AddError(t('Your account is inactive. If this is a mistake, please contact us at @adminemail to correct the problem', 
                array('@adminemail' => COOP_ADDRESS_MEMBER_PERMISSIONS)));
            break;
        default:
          $g_oError->AddError(t('Login failed due to unknown error.'));
          break;
   }
  }
}

function homecoop_page_login_form_submit($form, &$form_state) {
  $form_state['redirect'] = 'hcfront';
}