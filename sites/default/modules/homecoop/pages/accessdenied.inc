<?php

function homecoop_page_accessdenied() {
  drupal_set_title(t('Access Denied'));
  drupal_set_message(t('Access Denied'), 'error');
  return array();
}