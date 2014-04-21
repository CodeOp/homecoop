<?php

function homecoop_page_front() {
  homecoop_include_app_file('settings');
  homecoop_include_app_file('authenticate');
  
  drupal_add_css(drupal_get_path('module', 'homecoop') . 'css/facet.css');
  
  global $g_oMemberSession;
  
  $hcsettings = array(
    'IsCoordUser' => (isset($g_oMemberSession) && !$g_oMemberSession->IsOnlyMember),
   );
  
  drupal_add_js(array('homecoop' => $hcsettings), 'setting');
  
  homecoop_add_js_file('authenticated.js');
  homecoop_add_js_file('activeorders.js');
  homecoop_add_js_file('facet.js');
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
    
  return array();
}