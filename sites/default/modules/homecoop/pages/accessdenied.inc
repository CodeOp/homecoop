<?php

function homecoop_page_accessdenied() {
  drupal_set_title(t('Access Denied'));
  drupal_set_message(t('Access Denied'), 'error', false);
  
  homecoop_include_app_file('settings');

  if (homecoop_check_if_authenticated()) {
    homecoop_add_js_file('authenticated.js');
    homecoop_include_app_file('authenticate');
  }
  return array();
}