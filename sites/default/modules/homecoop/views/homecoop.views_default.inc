<?php

/*
 * Implements hook_views_default_views
 */
function homecoop_views_default_views() {
  $views = array();
  
  //view
  $view = new view();
  $view->name = 'homecoop_my_orders';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_Order';
  $view->human_name = 'HomeCoop My Orders';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = HOMECOOP_PAGER_PAGES;
  
  $handler->display->display_options['style_plugin'] = 'table';
 // $handler->display->display_options['style_options']['row_class'] = 'resgridrow';
  $handler->display->display_options['style_options']['columns'] = array(
    'OrderID' => 'OrderID',
    'mCoopTotalIncFee' => 'mCoopTotalIncFee',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'OrderID' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mCoopTotalIncFee' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Order: Coop Order */
  $handler->display->display_options['relationships']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['relationships']['CoopOrderKeyID']['table'] = 'T_Order';
  $handler->display->display_options['relationships']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['relationships']['CoopOrderKeyID']['label'] = 'Order - CoopOrder';
  $handler->display->display_options['relationships']['CoopOrderKeyID']['required'] = TRUE;
  /* Relationship: Order: Pickup Location */
  $handler->display->display_options['relationships']['PickupLocationKeyID']['id'] = 'PickupLocationKeyID';
  $handler->display->display_options['relationships']['PickupLocationKeyID']['table'] = 'T_Order';
  $handler->display->display_options['relationships']['PickupLocationKeyID']['field'] = 'PickupLocationKeyID';
  $handler->display->display_options['relationships']['PickupLocationKeyID']['label'] = 'Order - PickupLocation';
  $handler->display->display_options['relationships']['PickupLocationKeyID']['required'] = TRUE;
  /* Relationship: Cooperative Order: Coop Order Name */
  $handler->display->display_options['relationships']['CoopOrderKeyID_1']['id'] = 'CoopOrderKeyID_1';
  $handler->display->display_options['relationships']['CoopOrderKeyID_1']['table'] = 'T_CoopOrder';
  $handler->display->display_options['relationships']['CoopOrderKeyID_1']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['relationships']['CoopOrderKeyID_1']['relationship'] = 'CoopOrderKeyID';
  $handler->display->display_options['relationships']['CoopOrderKeyID_1']['label'] = 'Coop Order Name';
  $handler->display->display_options['relationships']['CoopOrderKeyID_1']['required'] = TRUE;
  /* Relationship: Pickup Location: Pickup Location Name */
  $handler->display->display_options['relationships']['PickupLocationKeyID_1']['id'] = 'PickupLocationKeyID_1';
  $handler->display->display_options['relationships']['PickupLocationKeyID_1']['table'] = 'T_PickupLocation';
  $handler->display->display_options['relationships']['PickupLocationKeyID_1']['field'] = 'PickupLocationKeyID';
  $handler->display->display_options['relationships']['PickupLocationKeyID_1']['relationship'] = 'PickupLocationKeyID';
  $handler->display->display_options['relationships']['PickupLocationKeyID_1']['label'] = 'Pickup Location Name';
  $handler->display->display_options['relationships']['PickupLocationKeyID_1']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID']['id'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['relationship'] = 'CoopOrderKeyID_1';
  $handler->display->display_options['relationships']['LangID']['label'] = 'Coop Order Name Language';
  $handler->display->display_options['relationships']['LangID']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID_1']['id'] = 'LangID_1';
  $handler->display->display_options['relationships']['LangID_1']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID_1']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID_1']['relationship'] = 'PickupLocationKeyID_1';
  $handler->display->display_options['relationships']['LangID_1']['label'] = 'Pickup Location Name Language';
  $handler->display->display_options['relationships']['LangID_1']['required'] = TRUE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString']['id'] = 'sString';
  $handler->display->display_options['fields']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString']['field'] = 'sString';
  $handler->display->display_options['fields']['sString']['relationship'] = 'CoopOrderKeyID_1';
  $handler->display->display_options['fields']['sString']['label'] = 'Order Title';
  $handler->display->display_options['fields']['sString']['element_label_colon'] = FALSE;
  /* Field: Cooperative Order: Delivery */
  $handler->display->display_options['fields']['dDelivery']['id'] = 'dDelivery';
  $handler->display->display_options['fields']['dDelivery']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['dDelivery']['field'] = 'dDelivery';
  $handler->display->display_options['fields']['dDelivery']['relationship'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['dDelivery']['label'] = 'Delivery';
  $handler->display->display_options['fields']['dDelivery']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['dDelivery']['date_format'] = 'custom';
  $handler->display->display_options['fields']['dDelivery']['custom_date_format'] = HOMECOOP_DATE_FORMAT;
  $handler->display->display_options['fields']['dDelivery']['second_date_format'] = 'long';
  
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Status';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php homecoop_views_php_cooporder_status_pre_render($view, $handler, $static, $row, $data, $value); ?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Cooperative Order: Status */
  $handler->display->display_options['fields']['nStatus']['id'] = 'nStatus';
  $handler->display->display_options['fields']['nStatus']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['nStatus']['field'] = 'nStatus';
  $handler->display->display_options['fields']['nStatus']['relationship'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['nStatus']['label'] = '';
  $handler->display->display_options['fields']['nStatus']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nStatus']['element_label_colon'] = FALSE;
  
  
  
  /* Field: Order: Created On */
  $handler->display->display_options['fields']['dCreated']['id'] = 'dCreated';
  $handler->display->display_options['fields']['dCreated']['table'] = 'T_Order';
  $handler->display->display_options['fields']['dCreated']['field'] = 'dCreated';
  $handler->display->display_options['fields']['dCreated']['label'] = 'Order Date';
  $handler->display->display_options['fields']['dCreated']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['dCreated']['date_format'] = 'custom';
  $handler->display->display_options['fields']['dCreated']['custom_date_format'] = HOMECOOP_DATE_FORMAT;
  $handler->display->display_options['fields']['dCreated']['second_date_format'] = 'long';
  /* Field: String: String */
  $handler->display->display_options['fields']['sString_1']['id'] = 'sString_1';
  $handler->display->display_options['fields']['sString_1']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString_1']['field'] = 'sString';
  $handler->display->display_options['fields']['sString_1']['relationship'] = 'PickupLocationKeyID_1';
  $handler->display->display_options['fields']['sString_1']['label'] = 'Location Name';
  $handler->display->display_options['fields']['sString_1']['element_label_colon'] = FALSE;
  /* Field: Order: Total Amount */
  $handler->display->display_options['fields']['mCoopTotalIncFee']['id'] = 'mCoopTotalIncFee';
  $handler->display->display_options['fields']['mCoopTotalIncFee']['table'] = 'T_Order';
  $handler->display->display_options['fields']['mCoopTotalIncFee']['field'] = 'mCoopTotalIncFee';
  $handler->display->display_options['fields']['mCoopTotalIncFee']['label'] = 'Total';
  $handler->display->display_options['fields']['mCoopTotalIncFee']['element_label_colon'] = FALSE;

  /* Field: Cooperative Order: Closing */
  $handler->display->display_options['fields']['dEnd']['id'] = 'dEnd';
  $handler->display->display_options['fields']['dEnd']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['dEnd']['field'] = 'dEnd';
  $handler->display->display_options['fields']['dEnd']['relationship'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['dEnd']['label'] = '';
  $handler->display->display_options['fields']['dEnd']['exclude'] = TRUE;
  $handler->display->display_options['fields']['dEnd']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['dEnd']['date_format'] = 'long';
  $handler->display->display_options['fields']['dEnd']['second_date_format'] = 'long';
  
  /* Sort criterion: Cooperative Order: Delivery */
  $handler->display->display_options['sorts']['dDelivery']['id'] = 'dDelivery';
  $handler->display->display_options['sorts']['dDelivery']['table'] = 'T_CoopOrder';
  $handler->display->display_options['sorts']['dDelivery']['field'] = 'dDelivery';
  $handler->display->display_options['sorts']['dDelivery']['relationship'] = 'CoopOrderKeyID';
  $handler->display->display_options['sorts']['dDelivery']['order'] = 'DESC';
  
  
  
  /* Contextual filter: Language: PHP Folder */
$handler->display->display_options['arguments']['sPhpFolder']['id'] = 'sPhpFolder';
$handler->display->display_options['arguments']['sPhpFolder']['table'] = 'Tlng_Language';
$handler->display->display_options['arguments']['sPhpFolder']['field'] = 'sPhpFolder';
$handler->display->display_options['arguments']['sPhpFolder']['relationship'] = 'LangID';
$handler->display->display_options['arguments']['sPhpFolder']['default_action'] = 'default';
$handler->display->display_options['arguments']['sPhpFolder']['default_argument_type'] = 'php';
$handler->display->display_options['arguments']['sPhpFolder']['default_argument_options']['code'] = 'global $language; return $language->language;';
$handler->display->display_options['arguments']['sPhpFolder']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['sPhpFolder']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['sPhpFolder']['summary_options']['items_per_page'] = '5';
$handler->display->display_options['arguments']['sPhpFolder']['limit'] = '0';
/* Contextual filter: Language: PHP Folder */
$handler->display->display_options['arguments']['sPhpFolder_1']['id'] = 'sPhpFolder_1';
$handler->display->display_options['arguments']['sPhpFolder_1']['table'] = 'Tlng_Language';
$handler->display->display_options['arguments']['sPhpFolder_1']['field'] = 'sPhpFolder';
$handler->display->display_options['arguments']['sPhpFolder_1']['relationship'] = 'LangID_1';
$handler->display->display_options['arguments']['sPhpFolder_1']['default_action'] = 'default';
$handler->display->display_options['arguments']['sPhpFolder_1']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['sPhpFolder_1']['default_argument_options']['argument'] = 'en';
$handler->display->display_options['arguments']['sPhpFolder_1']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['sPhpFolder_1']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['sPhpFolder_1']['summary_options']['items_per_page'] = '5';
$handler->display->display_options['arguments']['sPhpFolder_1']['limit'] = '0';
/* Contextual filter: Order: Member ID */
$handler->display->display_options['arguments']['MemberID']['id'] = 'MemberID';
$handler->display->display_options['arguments']['MemberID']['table'] = 'T_Order';
$handler->display->display_options['arguments']['MemberID']['field'] = 'MemberID';
$handler->display->display_options['arguments']['MemberID']['default_action'] = 'default';
$handler->display->display_options['arguments']['MemberID']['default_argument_type'] = 'php';
$handler->display->display_options['arguments']['MemberID']['default_argument_options']['code'] = 'global $g_oMemberSession; if (isset($g_oMemberSession)) { return $g_oMemberSession->MemberID; } return 0;';
$handler->display->display_options['arguments']['MemberID']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['MemberID']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['MemberID']['summary_options']['items_per_page'] = '5';
  
  
  /* Contextual filter: Language: PHP Folder */
  $handler->display->display_options['arguments']['sPhpFolder']['id'] = 'sPhpFolder';
  $handler->display->display_options['arguments']['sPhpFolder']['table'] = 'Tlng_Language';
  $handler->display->display_options['arguments']['sPhpFolder']['field'] = 'sPhpFolder';
  $handler->display->display_options['arguments']['sPhpFolder']['relationship'] = 'LangID';
  $handler->display->display_options['arguments']['sPhpFolder']['default_action'] = 'default';
  
  $handler->display->display_options['arguments']['sPhpFolder']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['sPhpFolder']['default_argument_options']['code'] = 'global $language; return $language->language;';
  $handler->display->display_options['arguments']['sPhpFolder']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['sPhpFolder']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['sPhpFolder']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  $handler->display->display_options['arguments']['sPhpFolder']['limit'] = '0';
  /* Contextual filter: Language: PHP Folder */
  $handler->display->display_options['arguments']['sPhpFolder_1']['id'] = 'sPhpFolder_1';
  $handler->display->display_options['arguments']['sPhpFolder_1']['table'] = 'Tlng_Language';
  $handler->display->display_options['arguments']['sPhpFolder_1']['field'] = 'sPhpFolder';
  $handler->display->display_options['arguments']['sPhpFolder_1']['relationship'] = 'LangID_1';
  $handler->display->display_options['arguments']['sPhpFolder_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['sPhpFolder_1']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['sPhpFolder_1']['default_argument_options']['code'] = 'global $language; return $language->language;';
  $handler->display->display_options['arguments']['sPhpFolder_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['sPhpFolder_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['sPhpFolder_1']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  $handler->display->display_options['arguments']['sPhpFolder_1']['limit'] = '0';
  /* Contextual filter: Order: Member ID */
  $handler->display->display_options['arguments']['MemberID']['id'] = 'MemberID';
  $handler->display->display_options['arguments']['MemberID']['table'] = 'T_Order';
  $handler->display->display_options['arguments']['MemberID']['field'] = 'MemberID';
  $handler->display->display_options['arguments']['MemberID']['default_action'] = 'default';
  $handler->display->display_options['arguments']['MemberID']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['MemberID']['default_argument_options']['code'] = 'global $g_oMemberSession; if (isset($g_oMemberSession)) { return $g_oMemberSession->MemberID; } return 0;';
  $handler->display->display_options['arguments']['MemberID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['MemberID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['MemberID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  $translatables['homecoop_my_orders_sample'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Order - CoopOrder'),
    t('Order - PickupLocation'),
    t('Coop Order Name'),
    t('Pickup Location Name'),
    t('Coop Order Name Language'),
    t('Pickup Location Name Language'),
    t('Order Title'),
    t('Delivery'),
    t('Order Date'),
    t('Location Name'),
    t('Total'),
    t('.'),
    t(','),
    t('Status'),
    t('All'),
  );
  
  $views[$view->name] = $view;
  
  return $views;
}
