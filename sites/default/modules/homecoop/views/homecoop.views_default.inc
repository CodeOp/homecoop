<?php

/*
 * Implements hook_views_default_views
 */
function homecoop_views_default_views() {
  $views = array();
  
  //-------------------------------------------------------------------------------------------------------------------
  // My Orders
  //-------------------------------------------------------------------------------------------------------------------
  $view = homecoop_my_orders_get_view('homecoop_my_orders', false);
  $views[$view->name] = $view;
  
  $view = homecoop_my_orders_get_view('homecoop_my_orders_coord', true);
  $views[$view->name] = $view;
  
  //--------------
  // Translations
  //--------------
  $translatables['homecoop_my_orders'] = array(
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
    t('Status'),
    t('.'),
    t(','),
    t('Order Date'),
    t('Location Name'),
    t('Total'),
    t('Order ID'),
    t('All'),
    t('Member'),
  );
  
  //-------------------------------------------------------------------------------------------------------------------
  // Cooperative Orders
  //-------------------------------------------------------------------------------------------------------------------
  
  $view = new view();
  $view->name = 'homecoop_cooporders';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_CoopOrder';
  $view->human_name = 'HomeCoop CoopOrders';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Cooperative Orders';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Cooperative Order: Coop Order Name */
  $handler->display->display_options['relationships']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['relationships']['CoopOrderKeyID']['table'] = 'T_CoopOrder';
  $handler->display->display_options['relationships']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['relationships']['CoopOrderKeyID']['label'] = 'CoopOrderName';
  $handler->display->display_options['relationships']['CoopOrderKeyID']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID']['id'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['relationship'] = 'CoopOrderKeyID';
  $handler->display->display_options['relationships']['LangID']['label'] = 'CoopOrderNameLang';
  $handler->display->display_options['relationships']['LangID']['required'] = TRUE;
  /* Field: Cooperative Order: Cooperative Order ID */
  $handler->display->display_options['fields']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['CoopOrderKeyID']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['CoopOrderKeyID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['CoopOrderKeyID']['element_label_colon'] = FALSE;
  /* Field: Cooperative Order: Total storage full */
  $handler->display->display_options['fields']['fStorageBurden']['id'] = 'fStorageBurden';
  $handler->display->display_options['fields']['fStorageBurden']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['fStorageBurden']['field'] = 'fStorageBurden';
  $handler->display->display_options['fields']['fStorageBurden']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fStorageBurden']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fStorageBurden']['precision'] = '0';
  /* Field: Cooperative Order: Total max. storage */
  $handler->display->display_options['fields']['fMaxStorageBurden']['id'] = 'fMaxStorageBurden';
  $handler->display->display_options['fields']['fMaxStorageBurden']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['fMaxStorageBurden']['field'] = 'fMaxStorageBurden';
  $handler->display->display_options['fields']['fMaxStorageBurden']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fMaxStorageBurden']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fMaxStorageBurden']['precision'] = '0';
  /* Field: Cooperative Order: Delivery Capacity */
  $handler->display->display_options['fields']['fMaxBurden']['id'] = 'fMaxBurden';
  $handler->display->display_options['fields']['fMaxBurden']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['fMaxBurden']['field'] = 'fMaxBurden';
  $handler->display->display_options['fields']['fMaxBurden']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fMaxBurden']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fMaxBurden']['precision'] = '0';
  /* Field: Cooperative Order: Total Burden */
  $handler->display->display_options['fields']['fBurden']['id'] = 'fBurden';
  $handler->display->display_options['fields']['fBurden']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['fBurden']['field'] = 'fBurden';
  $handler->display->display_options['fields']['fBurden']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fBurden']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fBurden']['precision'] = '0';
  /* Field: Cooperative Order: Max. Coop Total */
  $handler->display->display_options['fields']['mMaxCoopTotal']['id'] = 'mMaxCoopTotal';
  $handler->display->display_options['fields']['mMaxCoopTotal']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['mMaxCoopTotal']['field'] = 'mMaxCoopTotal';
  $handler->display->display_options['fields']['mMaxCoopTotal']['exclude'] = TRUE;
  $handler->display->display_options['fields']['mMaxCoopTotal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mMaxCoopTotal']['precision'] = '0';
  /* Field: Cooperative Order: Status */
  $handler->display->display_options['fields']['nStatus']['id'] = 'nStatus';
  $handler->display->display_options['fields']['nStatus']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['nStatus']['field'] = 'nStatus';
  $handler->display->display_options['fields']['nStatus']['label'] = '';
  $handler->display->display_options['fields']['nStatus']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nStatus']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString']['id'] = 'sString';
  $handler->display->display_options['fields']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString']['field'] = 'sString';
  $handler->display->display_options['fields']['sString']['relationship'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['sString']['label'] = 'Order Title';
  $handler->display->display_options['fields']['sString']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['sString']['alter']['path'] = 'hccoord/cooporder?id=[CoopOrderKeyID]';
  $handler->display->display_options['fields']['sString']['element_label_colon'] = FALSE;
  /* Field: Cooperative Order: Opening */
  $handler->display->display_options['fields']['dStart']['id'] = 'dStart';
  $handler->display->display_options['fields']['dStart']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['dStart']['field'] = 'dStart';
  $handler->display->display_options['fields']['dStart']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['dStart']['date_format'] = 'custom';
  $handler->display->display_options['fields']['dStart']['custom_date_format'] = HOMECOOP_DATE_FORMAT;
  $handler->display->display_options['fields']['dStart']['second_date_format'] = 'long';
  /* Field: Cooperative Order: Closing */
  $handler->display->display_options['fields']['dEnd']['id'] = 'dEnd';
  $handler->display->display_options['fields']['dEnd']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['dEnd']['field'] = 'dEnd';
  $handler->display->display_options['fields']['dEnd']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['dEnd']['date_format'] = 'custom';
  $handler->display->display_options['fields']['dEnd']['custom_date_format'] = HOMECOOP_DATE_FORMAT;
  $handler->display->display_options['fields']['dEnd']['second_date_format'] = 'long';
  /* Field: Cooperative Order: Delivery */
  $handler->display->display_options['fields']['dDelivery']['id'] = 'dDelivery';
  $handler->display->display_options['fields']['dDelivery']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['dDelivery']['field'] = 'dDelivery';
  $handler->display->display_options['fields']['dDelivery']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['dDelivery']['date_format'] = 'custom';
  $handler->display->display_options['fields']['dDelivery']['custom_date_format'] = HOMECOOP_DATE_FORMAT;
  $handler->display->display_options['fields']['dDelivery']['second_date_format'] = 'long';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['StatusName']['id'] = 'StatusName';
  $handler->display->display_options['fields']['StatusName']['table'] = 'views';
  $handler->display->display_options['fields']['StatusName']['field'] = 'php';
  $handler->display->display_options['fields']['StatusName']['label'] = 'Status';
  $handler->display->display_options['fields']['StatusName']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['StatusName']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['StatusName']['php_output'] = '<?php print CoopOrder::StatusName($row->nStatus); ?>';
  $handler->display->display_options['fields']['StatusName']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['StatusName']['php_click_sortable'] = '';
  /* Field: Cooperative Order: Total Coop */
  $handler->display->display_options['fields']['mCoopTotal']['id'] = 'mCoopTotal';
  $handler->display->display_options['fields']['mCoopTotal']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['mCoopTotal']['field'] = 'mCoopTotal';
  $handler->display->display_options['fields']['mCoopTotal']['label'] = 'Coop';
  $handler->display->display_options['fields']['mCoopTotal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mCoopTotal']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['mCoopTotal']['precision'] = '2';
  /* Field: Cooperative Order: Total Producers */
  $handler->display->display_options['fields']['mProducerTotal']['id'] = 'mProducerTotal';
  $handler->display->display_options['fields']['mProducerTotal']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['mProducerTotal']['field'] = 'mProducerTotal';
  $handler->display->display_options['fields']['mProducerTotal']['label'] = 'Producers';
  $handler->display->display_options['fields']['mProducerTotal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mProducerTotal']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['mProducerTotal']['precision'] = '2';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['PercentFull']['id'] = 'PercentFull';
  $handler->display->display_options['fields']['PercentFull']['table'] = 'views';
  $handler->display->display_options['fields']['PercentFull']['field'] = 'php';
  $handler->display->display_options['fields']['PercentFull']['label'] = 'Full';
  $handler->display->display_options['fields']['PercentFull']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['PercentFull']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['PercentFull']['php_output'] = '<?php 
  $oCoopOrderCapacity = new CoopOrderCapacity(
                                $row->fMaxBurden, $row->fBurden,
                                $row->mMaxCoopTotal, $row->mCoopTotal,
                           $row->fMaxStorageBurden, $row->fStorageBurden);
  if ($oCoopOrderCapacity->SelectedType != CoopOrderCapacity::TypeNone) {
                          echo $oCoopOrderCapacity->PercentRounded , \'%\';
  }
  ?>';
  $handler->display->display_options['fields']['PercentFull']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['PercentFull']['php_click_sortable'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['CopyLink']['id'] = 'CopyLink';
  $handler->display->display_options['fields']['CopyLink']['table'] = 'views';
  $handler->display->display_options['fields']['CopyLink']['field'] = 'php';
  $handler->display->display_options['fields']['CopyLink']['label'] = '';
  $handler->display->display_options['fields']['CopyLink']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['CopyLink']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['CopyLink']['php_output'] = '<?php print \'<a href="\' . url(\'hccoord/coopordercopy\', array(\'query\' => array(\'id\' => $row->CoopOrderKeyID))) . \'" >\' . t(\'Copy\') . \'</a>\'; ?>';
  $handler->display->display_options['fields']['CopyLink']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['CopyLink']['php_click_sortable'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['CoordLink']['id'] = 'CoordLink';
  $handler->display->display_options['fields']['CoordLink']['table'] = 'views';
  $handler->display->display_options['fields']['CoordLink']['field'] = 'php';
  $handler->display->display_options['fields']['CoordLink']['label'] = '';
  $handler->display->display_options['fields']['CoordLink']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['CoordLink']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['CoordLink']['php_output'] = '<?php print \'<a href="\' . url(\'hccoord/coordinate\', array(\'query\' => array(\'pa\' => \'' . 
      Consts::PERMISSION_AREA_COOP_ORDERS .'\', \'rid\' => $row->CoopOrderKeyID))) . \'" >\' . t(\'Coordination\') . \'</a>\'; ?>';
  $handler->display->display_options['fields']['CoordLink']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['CoordLink']['php_click_sortable'] = '';
  /* Sort criterion: Cooperative Order: Delivery */
  $handler->display->display_options['sorts']['dDelivery']['id'] = 'dDelivery';
  $handler->display->display_options['sorts']['dDelivery']['table'] = 'T_CoopOrder';
  $handler->display->display_options['sorts']['dDelivery']['field'] = 'dDelivery';
  $handler->display->display_options['sorts']['dDelivery']['order'] = 'DESC';
  
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['AllowEdit']['id'] = 'AllowEdit';
  $handler->display->display_options['arguments']['AllowEdit']['table'] = 'views';
  $handler->display->display_options['arguments']['AllowEdit']['field'] = 'null';
  $handler->display->display_options['arguments']['AllowEdit']['default_action'] = 'default';
  $handler->display->display_options['arguments']['AllowEdit']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['AllowEdit']['default_argument_options']['argument'] = 'yes';
  $handler->display->display_options['arguments']['AllowEdit']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['AllowEdit']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['AllowEdit']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['ViewSums']['id'] = 'ViewSums';
  $handler->display->display_options['arguments']['ViewSums']['table'] = 'views';
  $handler->display->display_options['arguments']['ViewSums']['field'] = 'null';
  $handler->display->display_options['arguments']['ViewSums']['default_action'] = 'default';
  $handler->display->display_options['arguments']['ViewSums']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ViewSums']['default_argument_options']['argument'] = 'yes';
  $handler->display->display_options['arguments']['ViewSums']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ViewSums']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ViewSums']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['CanCopy']['id'] = 'CanCopy';
  $handler->display->display_options['arguments']['CanCopy']['table'] = 'views';
  $handler->display->display_options['arguments']['CanCopy']['field'] = 'null';
  $handler->display->display_options['arguments']['CanCopy']['default_action'] = 'default';
  $handler->display->display_options['arguments']['CanCopy']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CanCopy']['default_argument_options']['argument'] = 'yes';
  $handler->display->display_options['arguments']['CanCopy']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CanCopy']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CanCopy']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['CanSetCoord']['id'] = 'CanSetCoord';
  $handler->display->display_options['arguments']['CanSetCoord']['table'] = 'views';
  $handler->display->display_options['arguments']['CanSetCoord']['field'] = 'null';
  $handler->display->display_options['arguments']['CanSetCoord']['default_action'] = 'default';
  $handler->display->display_options['arguments']['CanSetCoord']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CanSetCoord']['default_argument_options']['argument'] = 'yes';
  $handler->display->display_options['arguments']['CanSetCoord']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CanSetCoord']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CanSetCoord']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  
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
  $translatables['homecoop_cooporders_sample'] = array(
    t('Cooperative Orders'),
    t('CoopOrderName'),
    t('CoopOrderNameLang'),
    t('Order Title'),
    t('Opening'),
    t('Closing'),
    t('Delivery'),
    t('Status'),
    t('Coop'),
    t('Producers'),
    t('Full'),
    t('All'),
  );
  $views[$view->name] = $view;
  
  //-------------------------------------------------------------------------------------------------------------------
  // CoopOrder Orders
  //-------------------------------------------------------------------------------------------------------------------
  $view = new view();
  $view->name = 'homecoop_cooporder_orders';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_Order';
  $view->human_name = 'HomeCoop CoopOrder Orders';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
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
  /* Header: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['empty'] = TRUE;
  $handler->display->display_options['header']['php']['php_output'] = '<?php if (!isset($view->args[1]) || $view->args[1] == \'rw\') { ?><div><a href="<?php echo url(\'hcorder\', array(\'query\' => array(\'coid\' => $view->args[0]))); ?>"><img border="0" title="<?php echo t(\'Add\'); ?>" src="<?php echo homecoop_getthemepath() . \'img/edit-add-2.png\'  ?>" /></a></div><?php } ?>';  
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
  /* Relationship: Order: Member */
  $handler->display->display_options['relationships']['MemberID']['id'] = 'MemberID';
  $handler->display->display_options['relationships']['MemberID']['table'] = 'T_Order';
  $handler->display->display_options['relationships']['MemberID']['field'] = 'MemberID';
  $handler->display->display_options['relationships']['MemberID']['label'] = 'OrderMember';
  $handler->display->display_options['relationships']['MemberID']['required'] = TRUE;
  /* Field: Order: Order ID */
  $handler->display->display_options['fields']['OrderID']['id'] = 'OrderID';
  $handler->display->display_options['fields']['OrderID']['table'] = 'T_Order';
  $handler->display->display_options['fields']['OrderID']['field'] = 'OrderID';
  $handler->display->display_options['fields']['OrderID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['OrderID']['element_label_colon'] = FALSE;
  /* Field: Member: Name */
  $handler->display->display_options['fields']['sName']['id'] = 'sName';
  $handler->display->display_options['fields']['sName']['table'] = 'T_Member';
  $handler->display->display_options['fields']['sName']['field'] = 'sName';
  $handler->display->display_options['fields']['sName']['label'] = 'Member';
  $handler->display->display_options['fields']['sName']['relationship'] = 'MemberID';
  $handler->display->display_options['fields']['sName']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sName']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['sName']['alter']['path'] = 'hcorderitems?id=[OrderID]';
  
  /* Field: Member: Email address */
  $handler->display->display_options['fields']['sEMail']['id'] = 'sEMail';
  $handler->display->display_options['fields']['sEMail']['table'] = 'T_Member';
  $handler->display->display_options['fields']['sEMail']['field'] = 'sEMail';
  $handler->display->display_options['fields']['sEMail']['label'] = 'Email address';
  $handler->display->display_options['fields']['sEMail']['relationship'] = 'MemberID';
  $handler->display->display_options['fields']['sEMail']['element_label_colon'] = FALSE;
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
  $handler->display->display_options['fields']['mCoopTotalIncFee']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['mCoopTotalIncFee']['precision'] = 2;
  /* Field: Member: Balance */
  $handler->display->display_options['fields']['mBalance']['id'] = 'mBalance';
  $handler->display->display_options['fields']['mBalance']['table'] = 'T_Member';
  $handler->display->display_options['fields']['mBalance']['field'] = 'mBalance';
  $handler->display->display_options['fields']['mBalance']['label'] = 'Balance';
  $handler->display->display_options['fields']['mBalance']['relationship'] = 'MemberID';
  $handler->display->display_options['fields']['mBalance']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mBalance']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['mBalance']['precision'] = 2;
  /* Field: Order: Created On */
  $handler->display->display_options['fields']['dCreated']['id'] = 'dCreated';
  $handler->display->display_options['fields']['dCreated']['table'] = 'T_Order';
  $handler->display->display_options['fields']['dCreated']['field'] = 'dCreated';
  $handler->display->display_options['fields']['dCreated']['label'] = 'Order Date';
  $handler->display->display_options['fields']['dCreated']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['dCreated']['date_format'] = 'custom';
  $handler->display->display_options['fields']['dCreated']['custom_date_format'] = 'j.n.Y';
  $handler->display->display_options['fields']['dCreated']['second_date_format'] = 'long';
  /* Field: Order: Comments */
  $handler->display->display_options['fields']['sMemberComments']['id'] = 'sMemberComments';
  $handler->display->display_options['fields']['sMemberComments']['table'] = 'T_Order';
  $handler->display->display_options['fields']['sMemberComments']['field'] = 'sMemberComments';
  $handler->display->display_options['fields']['sMemberComments']['label'] = 'Comments';
  $handler->display->display_options['fields']['sMemberComments']['element_label_colon'] = FALSE;
  /* Sort criterion: Order: Created On */
  $handler->display->display_options['sorts']['dCreated']['id'] = 'dCreated';
  $handler->display->display_options['sorts']['dCreated']['table'] = 'T_Order';
  $handler->display->display_options['sorts']['dCreated']['field'] = 'dCreated';
  $handler->display->display_options['sorts']['dCreated']['order'] = 'DESC';
  $handler->display->display_options['sorts']['dCreated']['expose']['label'] = 'Created On';
  /* Sort criterion: Member: Name */
  $handler->display->display_options['sorts']['sName']['id'] = 'sName';
  $handler->display->display_options['sorts']['sName']['table'] = 'T_Member';
  $handler->display->display_options['sorts']['sName']['field'] = 'sName';
  $handler->display->display_options['sorts']['sName']['relationship'] = 'MemberID';
  /* Contextual filter: Order: Coop Order ID */
  $handler->display->display_options['arguments']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['table'] = 'T_Order';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['Access']['id'] = 'Access';
  $handler->display->display_options['arguments']['Access']['table'] = 'views';
  $handler->display->display_options['arguments']['Access']['field'] = 'null';
  $handler->display->display_options['arguments']['Access']['default_action'] = 'default';
  $handler->display->display_options['arguments']['Access']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['Access']['default_argument_options']['argument'] = 'rw';
  $handler->display->display_options['arguments']['Access']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['Access']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['Access']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
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

  $translatables['homecoop_cooporder_orders'] = array(
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
    t('OrderMember'),
    t('Order ID'),
    t('.'),
    t(','),
    t('Name'),
    t('Email address'),
    t('Location Name'),
    t('Total'),
    t('Balance'),
    t('Order Date'),
    t('Comments'),
    t('Created On'),
    t('All'),
    t('Member'),
  );
  $views[$view->name] = $view;
  
  return $views;
}

function homecoop_my_orders_get_view($view_name, $is_coord) {
  //-------------------------------------------------------------------------------------------------------------------
  // My Orders
  //-------------------------------------------------------------------------------------------------------------------
  $view = new view();
  $view->name = $view_name;
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_Order';
  $view->human_name = 'HomeCoop My Orders' . ($is_coord? ' (coord)' : '');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
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
  
  //--------------
  // Relationships
  //--------------
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
  
  //--------------
  // Fields
  //--------------
  /* Field: Order: Order ID - must be first, to be used by the following name link */
  $handler->display->display_options['fields']['OrderID']['id'] = 'OrderID';
  $handler->display->display_options['fields']['OrderID']['table'] = 'T_Order';
  $handler->display->display_options['fields']['OrderID']['field'] = 'OrderID';
  $handler->display->display_options['fields']['OrderID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['OrderID']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString']['id'] = 'sString';
  $handler->display->display_options['fields']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString']['field'] = 'sString';
  $handler->display->display_options['fields']['sString']['relationship'] = 'CoopOrderKeyID_1';
  $handler->display->display_options['fields']['sString']['label'] = 'Order Title';
  $handler->display->display_options['fields']['sString']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['sString']['alter']['path'] = 'hcorderitems?id=[OrderID]';
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
  $handler->display->display_options['fields']['mCoopTotalIncFee']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['mCoopTotalIncFee']['precision'] = 2;
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
  
  
  //--------------
  // Sort
  //--------------
  $handler->display->display_options['sorts']['dDelivery']['id'] = 'dDelivery';
  $handler->display->display_options['sorts']['dDelivery']['table'] = 'T_CoopOrder';
  $handler->display->display_options['sorts']['dDelivery']['field'] = 'dDelivery';
  $handler->display->display_options['sorts']['dDelivery']['relationship'] = 'CoopOrderKeyID';
  $handler->display->display_options['sorts']['dDelivery']['order'] = 'DESC';
    
  //--------------
  // Contextual filters
  //--------------
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
  if (!$is_coord) {
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
  }
  else {
    //--------------
    // Filters
    //--------------
    /* Filter criterion: Order: Member ID */
    $handler->display->display_options['filters']['MemberID']['id'] = 'MemberID';
    $handler->display->display_options['filters']['MemberID']['table'] = 'T_Order';
    $handler->display->display_options['filters']['MemberID']['field'] = 'MemberID';
    $handler->display->display_options['filters']['MemberID']['exposed'] = TRUE;
    $handler->display->display_options['filters']['MemberID']['expose']['operator_id'] = 'MemberID_op';
    $handler->display->display_options['filters']['MemberID']['expose']['label'] = 'Member';
    $handler->display->display_options['filters']['MemberID']['expose']['operator'] = 'MemberID_op';
    $handler->display->display_options['filters']['MemberID']['expose']['identifier'] = 'MemberID';
    $handler->display->display_options['filters']['MemberID']['expose']['required'] = TRUE;
    /*$handler->display->display_options['filters']['MemberID']['expose']['remember_roles'] = array(
      2 => '2',
      1 => 0,
      3 => 0,
    );*/
  }
  
  
  
  return $view;
}