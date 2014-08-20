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
  
  
  //-------------------------------------------------------------------------------------------------------------------
  // Cooperative Orders
  //-------------------------------------------------------------------------------------------------------------------
  $view = homecoop_cooporders_get_view('homecoop_cooporders', true);
  $views[$view->name] = $view;
  
  $view = homecoop_cooporders_get_view('homecoop_cooporders_nosums', false);
  $views[$view->name] = $view;
  
  //-------------------------------------------------------------------------------------------------------------------
  // Pickup Locations
  //-------------------------------------------------------------------------------------------------------------------
  
  $view = new view();
  $view->name = 'homecoop_pickup_locations';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_PickupLocation';
  $view->human_name = 'HomeCoop Pickup Locations';
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
    'PickupLocationKeyID' => 'PickupLocationKeyID',
    'CoordinatingGroupID' => 'CoordinatingGroupID',
    'bDisabled' => 'bDisabled',
    'sString' => 'sString',
    'sString_1' => 'sString_1',
    'mCachier' => 'mCachier',
    'dCachierUpdate' => 'dCachierUpdate',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'PickupLocationKeyID' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'CoordinatingGroupID' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'bDisabled' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sString' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sString_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mCachier' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'dCachierUpdate' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['php_output'] = '<?php if (!isset($view->args[0]) || $view->args[0] == \'yes\') { ?><div><a href="<?php echo url(\'hccoord/pickuploc\'); ?>"><img border="0" title="<?php echo t(\'Add\'); ?>" src="<?php echo homecoop_getthemepath() . \'img/edit-add-2.png\'  ?>" /></a></div><?php } ?>';
  /* Relationship: Pickup Location: Pickup Location Address */
  $handler->display->display_options['relationships']['AddressStringKeyID']['id'] = 'AddressStringKeyID';
  $handler->display->display_options['relationships']['AddressStringKeyID']['table'] = 'T_PickupLocation';
  $handler->display->display_options['relationships']['AddressStringKeyID']['field'] = 'AddressStringKeyID';
  $handler->display->display_options['relationships']['AddressStringKeyID']['label'] = 'PickupLocationAddress';
  $handler->display->display_options['relationships']['AddressStringKeyID']['required'] = TRUE;
  /* Relationship: Pickup Location: Pickup Location Name */
  $handler->display->display_options['relationships']['PickupLocationKeyID']['id'] = 'PickupLocationKeyID';
  $handler->display->display_options['relationships']['PickupLocationKeyID']['table'] = 'T_PickupLocation';
  $handler->display->display_options['relationships']['PickupLocationKeyID']['field'] = 'PickupLocationKeyID';
  $handler->display->display_options['relationships']['PickupLocationKeyID']['label'] = 'PickupLocationName';
  $handler->display->display_options['relationships']['PickupLocationKeyID']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID']['id'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['relationship'] = 'AddressStringKeyID';
  $handler->display->display_options['relationships']['LangID']['label'] = 'AddressLang';
  $handler->display->display_options['relationships']['LangID']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID_1']['id'] = 'LangID_1';
  $handler->display->display_options['relationships']['LangID_1']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID_1']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID_1']['relationship'] = 'PickupLocationKeyID';
  $handler->display->display_options['relationships']['LangID_1']['label'] = 'NameLang';
  $handler->display->display_options['relationships']['LangID_1']['required'] = TRUE;
  /* Field: Pickup Location: Pickup Location ID */
  $handler->display->display_options['fields']['PickupLocationKeyID']['id'] = 'PickupLocationKeyID';
  $handler->display->display_options['fields']['PickupLocationKeyID']['table'] = 'T_PickupLocation';
  $handler->display->display_options['fields']['PickupLocationKeyID']['field'] = 'PickupLocationKeyID';
  $handler->display->display_options['fields']['PickupLocationKeyID']['label'] = '';
  $handler->display->display_options['fields']['PickupLocationKeyID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['PickupLocationKeyID']['element_label_colon'] = FALSE;
  /* Field: Pickup Location: Coordinating Group ID */
  $handler->display->display_options['fields']['CoordinatingGroupID']['id'] = 'CoordinatingGroupID';
  $handler->display->display_options['fields']['CoordinatingGroupID']['table'] = 'T_PickupLocation';
  $handler->display->display_options['fields']['CoordinatingGroupID']['field'] = 'CoordinatingGroupID';
  $handler->display->display_options['fields']['CoordinatingGroupID']['label'] = '';
  $handler->display->display_options['fields']['CoordinatingGroupID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['CoordinatingGroupID']['element_label_colon'] = FALSE;
  /* Field: Pickup Location: Disabled */
  $handler->display->display_options['fields']['bDisabled']['id'] = 'bDisabled';
  $handler->display->display_options['fields']['bDisabled']['table'] = 'T_PickupLocation';
  $handler->display->display_options['fields']['bDisabled']['field'] = 'bDisabled';
  $handler->display->display_options['fields']['bDisabled']['label'] = '';
  $handler->display->display_options['fields']['bDisabled']['exclude'] = TRUE;
  $handler->display->display_options['fields']['bDisabled']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString']['id'] = 'sString';
  $handler->display->display_options['fields']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString']['field'] = 'sString';
  $handler->display->display_options['fields']['sString']['relationship'] = 'PickupLocationKeyID';
  $handler->display->display_options['fields']['sString']['label'] = 'Location Name';
  $handler->display->display_options['fields']['sString']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['sString']['alter']['path'] = 'hccoord/pickuploc?id=[PickupLocationKeyID]';
  $handler->display->display_options['fields']['sString']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString_1']['id'] = 'sString_1';
  $handler->display->display_options['fields']['sString_1']['table'] = 'Tlng_String';
  $handler->display->display_oOrptions['fields']['sString_1']['field'] = 'sString';
  $handler->display->display_options['fields']['sString_1']['relationship'] = 'AddressStringKeyID';
  $handler->display->display_options['fields']['sString_1']['label'] = 'Address';
  $handler->display->display_options['fields']['sString_1']['element_label_colon'] = FALSE;
  /* Field: Pickup Location: Cachier */
  $handler->display->display_options['fields']['mCachier']['id'] = 'mCachier';
  $handler->display->display_options['fields']['mCachier']['table'] = 'T_PickupLocation';
  $handler->display->display_options['fields']['mCachier']['field'] = 'mCachier';
  $handler->display->display_options['fields']['mCachier']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mCachier']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['mCachier']['precision'] = '0';
  /* Field: Pickup Location: Cachier Update */
  $handler->display->display_options['fields']['dCachierUpdate']['id'] = 'dCachierUpdate';
  $handler->display->display_options['fields']['dCachierUpdate']['table'] = 'T_PickupLocation';
  $handler->display->display_options['fields']['dCachierUpdate']['field'] = 'dCachierUpdate';
  $handler->display->display_options['fields']['dCachierUpdate']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['dCachierUpdate']['date_format'] = 'custom';
  $handler->display->display_options['fields']['dCachierUpdate']['custom_date_format'] = HOMECOOP_DATE_FORMAT;
  $handler->display->display_options['fields']['dCachierUpdate']['second_date_format'] = 'long';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Status';
  $handler->display->display_options['fields']['php']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php']['alter']['path'] = 'hccoord/pickuploc?id=[PickupLocationKeyID]';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php print $row->bDisabled? t(\'Inactive\') : t(\'Active\'); ?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['label'] = '';
  $handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = '<?php 

    if (!isset($view->args[1]) || $view->args[1] == \'yes\') { 
    $arrParams = array(\'pa\' => \'' . Consts::PERMISSION_AREA_PICKUP_LOCATIONS  .  '\', \'rid\' => $row->PickupLocationKeyID);
    if (!empty($row->CoordinatingGroupID)) { 
    $arrParams[\'id\'] = $row->CoordinatingGroupID;
    }
    print \'<a href="\' . url(\'hccoord/coordinate\', array(\'query\' => $arrParams)) . \'" >\' . t(\'Coordination\') . \'</a>\'; 
    } ?>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* Sort criterion: String: String */
  $handler->display->display_options['sorts']['sString']['id'] = 'sString';
  $handler->display->display_options['sorts']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['sorts']['sString']['field'] = 'sString';
  $handler->display->display_options['sorts']['sString']['relationship'] = 'PickupLocationKeyID';
  /* Contextual filter: Global: Can Add */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['default_argument_options']['argument'] = 'yes';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  /* Contextual filter: Global: Can Coord */
  $handler->display->display_options['arguments']['null_1']['id'] = 'null_1';
  $handler->display->display_options['arguments']['null_1']['table'] = 'views';
  $handler->display->display_options['arguments']['null_1']['field'] = 'null';
  $handler->display->display_options['arguments']['null_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null_1']['default_argument_options']['argument'] = 'yes';
  $handler->display->display_options['arguments']['null_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null_1']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
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
  /* Contextual filter: Pickup Location: Coordinating Group ID */
  $handler->display->display_options['arguments']['CoordinatingGroupID']['id'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['table'] = 'T_PickupLocation';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['field'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  $handler->display->display_options['arguments']['CoordinatingGroupID']['break_phrase'] = TRUE;
  
  $views[$view->name] = $view;
  
  //-------------------------------------------------------------------------------------------------------------------
  // Products
  //-------------------------------------------------------------------------------------------------------------------
  
  $view = new view();
  $view->name = 'homecoop_products';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_Product';
  $view->human_name = 'HomeCoop Products';
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
    'ProductKeyID' => 'ProductKeyID',
    'ProducerKeyID' => 'ProducerKeyID',
    'bDisabled' => 'bDisabled',
    'nSortOrder' => 'nSortOrder',
    'fBurden' => 'fBurden',
    'mCoopPrice' => 'mCoopPrice',
    'mProducerPrice' => 'mProducerPrice',
    'fQuantity' => 'fQuantity',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'ProductKeyID' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ProducerKeyID' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'bDisabled' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nSortOrder' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'fBurden' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mCoopPrice' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mProducerPrice' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'fQuantity' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['php_output'] = '<?php if (!isset($view->args[0]) || $view->args[0] == \'yes\') { ?><div><a href="<?php echo url(\'hccoord/product\'); ?>"><img border="0" title="<?php echo t(\'Add\'); ?>" src="<?php echo homecoop_getthemepath() . \'img/edit-add-2.png\'  ?>" /></a></div><?php } ?>';
  /* Relationship: Product: Producer */
  $handler->display->display_options['relationships']['ProducerKeyID']['id'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['table'] = 'T_Product';
  $handler->display->display_options['relationships']['ProducerKeyID']['field'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['label'] = 'ProductProducer';
  $handler->display->display_options['relationships']['ProducerKeyID']['required'] = TRUE;
  /* Relationship: Product: Product Name */
  $handler->display->display_options['relationships']['ProductKeyID']['id'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['ProductKeyID']['table'] = 'T_Product';
  $handler->display->display_options['relationships']['ProductKeyID']['field'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['ProductKeyID']['label'] = 'ProductName';
  $handler->display->display_options['relationships']['ProductKeyID']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID']['id'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['relationship'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['LangID']['label'] = 'ProductNameLang';
  $handler->display->display_options['relationships']['LangID']['required'] = TRUE;
  /* Relationship: Producer: Producer Name */
  $handler->display->display_options['relationships']['ProducerKeyID_1']['id'] = 'ProducerKeyID_1';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['table'] = 'T_Producer';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['field'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['relationship'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['label'] = 'ProducerName';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID_1']['id'] = 'LangID_1';
  $handler->display->display_options['relationships']['LangID_1']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID_1']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID_1']['relationship'] = 'ProducerKeyID_1';
  $handler->display->display_options['relationships']['LangID_1']['label'] = 'ProducerNameLang';
  $handler->display->display_options['relationships']['LangID_1']['required'] = TRUE;
  /* Relationship: Product: Unit */
  $handler->display->display_options['relationships']['UnitKeyID']['id'] = 'UnitKeyID';
  $handler->display->display_options['relationships']['UnitKeyID']['table'] = 'T_Product';
  $handler->display->display_options['relationships']['UnitKeyID']['field'] = 'UnitKeyID';
  $handler->display->display_options['relationships']['UnitKeyID']['label'] = 'ProductUnit';
  $handler->display->display_options['relationships']['UnitKeyID']['required'] = TRUE;
  /* Relationship: Unit: Unit Abbreviation */
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['id'] = 'UnitAbbreviationStringKeyID';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['table'] = 'T_Unit';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['field'] = 'UnitAbbreviationStringKeyID';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['relationship'] = 'UnitKeyID';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['label'] = 'ProductUnitAbrevName';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID_2']['id'] = 'LangID_2';
  $handler->display->display_options['relationships']['LangID_2']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID_2']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID_2']['relationship'] = 'UnitAbbreviationStringKeyID';
  $handler->display->display_options['relationships']['LangID_2']['label'] = 'ProductUnitAbrevNameLang';
  $handler->display->display_options['relationships']['LangID_2']['required'] = TRUE;
  /* Field: Product: Product ID */
  $handler->display->display_options['fields']['ProductKeyID']['id'] = 'ProductKeyID';
  $handler->display->display_options['fields']['ProductKeyID']['table'] = 'T_Product';
  $handler->display->display_options['fields']['ProductKeyID']['field'] = 'ProductKeyID';
  $handler->display->display_options['fields']['ProductKeyID']['label'] = '';
  $handler->display->display_options['fields']['ProductKeyID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ProductKeyID']['element_label_colon'] = FALSE;
  /* Field: Product: Producer ID */
  $handler->display->display_options['fields']['ProducerKeyID']['id'] = 'ProducerKeyID';
  $handler->display->display_options['fields']['ProducerKeyID']['table'] = 'T_Product';
  $handler->display->display_options['fields']['ProducerKeyID']['field'] = 'ProducerKeyID';
  $handler->display->display_options['fields']['ProducerKeyID']['label'] = '';
  $handler->display->display_options['fields']['ProducerKeyID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ProducerKeyID']['element_label_colon'] = FALSE;
  /* Field: Product: Quantity */
  $handler->display->display_options['fields']['fQuantity']['id'] = 'fQuantity';
  $handler->display->display_options['fields']['fQuantity']['table'] = 'T_Product';
  $handler->display->display_options['fields']['fQuantity']['field'] = 'fQuantity';
  $handler->display->display_options['fields']['fQuantity']['label'] = '';
  $handler->display->display_options['fields']['fQuantity']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fQuantity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fQuantity']['precision'] = '0';
  /* Field: Product: Status */
  $handler->display->display_options['fields']['bDisabled']['id'] = 'bDisabled';
  $handler->display->display_options['fields']['bDisabled']['table'] = 'T_Product';
  $handler->display->display_options['fields']['bDisabled']['field'] = 'bDisabled';
  $handler->display->display_options['fields']['bDisabled']['label'] = '';
  $handler->display->display_options['fields']['bDisabled']['exclude'] = TRUE;
  $handler->display->display_options['fields']['bDisabled']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString_2']['id'] = 'sString_2';
  $handler->display->display_options['fields']['sString_2']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString_2']['field'] = 'sString';
  $handler->display->display_options['fields']['sString_2']['relationship'] = 'UnitAbbreviationStringKeyID';
  $handler->display->display_options['fields']['sString_2']['label'] = '';
  $handler->display->display_options['fields']['sString_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['sString_2']['element_label_colon'] = FALSE;
  /* Field: Product: Sorting Order */
  $handler->display->display_options['fields']['nSortOrder']['id'] = 'nSortOrder';
  $handler->display->display_options['fields']['nSortOrder']['table'] = 'T_Product';
  $handler->display->display_options['fields']['nSortOrder']['field'] = 'nSortOrder';
  $handler->display->display_options['fields']['nSortOrder']['label'] = '#';
  $handler->display->display_options['fields']['nSortOrder']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString']['id'] = 'sString';
  $handler->display->display_options['fields']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString']['field'] = 'sString';
  $handler->display->display_options['fields']['sString']['relationship'] = 'ProductKeyID';
  $handler->display->display_options['fields']['sString']['label'] = 'Product';
  $handler->display->display_options['fields']['sString']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['sString']['alter']['path'] = 'hccoord/product?id=[ProductKeyID]';
  $handler->display->display_options['fields']['sString']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString_1']['id'] = 'sString_1';
  $handler->display->display_options['fields']['sString_1']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString_1']['field'] = 'sString';
  $handler->display->display_options['fields']['sString_1']['relationship'] = 'ProducerKeyID_1';
  $handler->display->display_options['fields']['sString_1']['label'] = 'Producer';
  $handler->display->display_options['fields']['sString_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['sString_1']['alter']['path'] = 'hccoord/producer?id=[ProducerKeyID]';
  $handler->display->display_options['fields']['sString_1']['element_label_colon'] = FALSE;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Quantity';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php echo $row->fQuantity, \' \', $row->sString_2; ?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Product: Coop. Price */
  $handler->display->display_options['fields']['mCoopPrice']['id'] = 'mCoopPrice';
  $handler->display->display_options['fields']['mCoopPrice']['table'] = 'T_Product';
  $handler->display->display_options['fields']['mCoopPrice']['field'] = 'mCoopPrice';
  $handler->display->display_options['fields']['mCoopPrice']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mCoopPrice']['precision'] = '0';
  /* Field: Product: Producer Price */
  $handler->display->display_options['fields']['mProducerPrice']['id'] = 'mProducerPrice';
  $handler->display->display_options['fields']['mProducerPrice']['table'] = 'T_Product';
  $handler->display->display_options['fields']['mProducerPrice']['field'] = 'mProducerPrice';
  $handler->display->display_options['fields']['mProducerPrice']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mProducerPrice']['precision'] = '0';
  /* Field: Product: Burden */
  $handler->display->display_options['fields']['fBurden']['id'] = 'fBurden';
  $handler->display->display_options['fields']['fBurden']['table'] = 'T_Product';
  $handler->display->display_options['fields']['fBurden']['field'] = 'fBurden';
  $handler->display->display_options['fields']['fBurden']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fBurden']['precision'] = '0';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['label'] = 'Status';
  $handler->display->display_options['fields']['php_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_1']['alter']['path'] = 'hccoord/product?id=[ProductKeyID]';
  $handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = '<?php print $row->bDisabled? t(\'Inactive\') : t(\'Active\'); ?>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* Sort criterion: Product: Sorting Order */
  $handler->display->display_options['sorts']['nSortOrder']['id'] = 'nSortOrder';
  $handler->display->display_options['sorts']['nSortOrder']['table'] = 'T_Product';
  $handler->display->display_options['sorts']['nSortOrder']['field'] = 'nSortOrder';
  /* Sort criterion: String: String */
  $handler->display->display_options['sorts']['sString']['id'] = 'sString';
  $handler->display->display_options['sorts']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['sorts']['sString']['field'] = 'sString';
  $handler->display->display_options['sorts']['sString']['relationship'] = 'ProductKeyID';
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['default_argument_options']['argument'] = 'yes';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
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
  /* Contextual filter: Language: PHP Folder */
  $handler->display->display_options['arguments']['sPhpFolder_2']['id'] = 'sPhpFolder_2';
  $handler->display->display_options['arguments']['sPhpFolder_2']['table'] = 'Tlng_Language';
  $handler->display->display_options['arguments']['sPhpFolder_2']['field'] = 'sPhpFolder';
  $handler->display->display_options['arguments']['sPhpFolder_2']['relationship'] = 'LangID_2';
  $handler->display->display_options['arguments']['sPhpFolder_2']['default_action'] = 'default';
  $handler->display->display_options['arguments']['sPhpFolder_2']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['sPhpFolder_2']['default_argument_options']['code'] = 'global $language; return $language->language;';
  $handler->display->display_options['arguments']['sPhpFolder_2']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['sPhpFolder_2']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['sPhpFolder_2']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  $handler->display->display_options['arguments']['sPhpFolder_2']['limit'] = '0';
  /* Contextual filter: Producer: Coordinating Group ID */
  $handler->display->display_options['arguments']['CoordinatingGroupID']['id'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['table'] = 'T_Producer';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['field'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['relationship'] = 'ProducerKeyID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['exception']['value'] = '0';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  $handler->display->display_options['arguments']['CoordinatingGroupID']['break_phrase'] = TRUE;
  $views[$view->name] = $view;

  //-------------------------------------------------------------------------------------------------------------------
  // Producers
  //-------------------------------------------------------------------------------------------------------------------
  $view = new view();
  $view->name = 'homecoop_producers';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_Producer';
  $view->human_name = 'HomeCoop Producers';
  $view->core = 7;
  $view->api_version = '3.0';

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
    'ProducerKeyID' => 'ProducerKeyID',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'ProducerKeyID' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['php_output'] = '<?php if (!isset($view->args[0]) || $view->args[0] == \'rw\') { ?><div><a href="<?php echo url(\'hccoord/producer\'); ?>"><img border="0" title="<?php echo t(\'Add\'); ?>" src="<?php echo homecoop_getthemepath() . \'img/edit-add-2.png\'  ?>" /></a></div><?php } ?>
  ';
  /* Relationship: Producer: Producer Name */
  $handler->display->display_options['relationships']['ProducerKeyID']['id'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['table'] = 'T_Producer';
  $handler->display->display_options['relationships']['ProducerKeyID']['field'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['label'] = 'ProducerName';
  $handler->display->display_options['relationships']['ProducerKeyID']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID']['id'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['relationship'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['LangID']['label'] = 'ProducerNameLang';
  $handler->display->display_options['relationships']['LangID']['required'] = TRUE;
  /* Field: Producer: Producer ID */
  $handler->display->display_options['fields']['ProducerKeyID']['id'] = 'ProducerKeyID';
  $handler->display->display_options['fields']['ProducerKeyID']['table'] = 'T_Producer';
  $handler->display->display_options['fields']['ProducerKeyID']['field'] = 'ProducerKeyID';
  $handler->display->display_options['fields']['ProducerKeyID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ProducerKeyID']['element_label_colon'] = FALSE;
  /* Field: Producer: Coordinating Group ID */
  $handler->display->display_options['fields']['CoordinatingGroupID']['id'] = 'CoordinatingGroupID';
  $handler->display->display_options['fields']['CoordinatingGroupID']['table'] = 'T_Producer';
  $handler->display->display_options['fields']['CoordinatingGroupID']['field'] = 'CoordinatingGroupID';
  $handler->display->display_options['fields']['CoordinatingGroupID']['label'] = '';
  $handler->display->display_options['fields']['CoordinatingGroupID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['CoordinatingGroupID']['element_label_colon'] = FALSE;
  /* Field: Producer: Disabled */
  $handler->display->display_options['fields']['bDisabled']['id'] = 'bDisabled';
  $handler->display->display_options['fields']['bDisabled']['table'] = 'T_Producer';
  $handler->display->display_options['fields']['bDisabled']['field'] = 'bDisabled';
  $handler->display->display_options['fields']['bDisabled']['label'] = '';
  $handler->display->display_options['fields']['bDisabled']['exclude'] = TRUE;
  $handler->display->display_options['fields']['bDisabled']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString']['id'] = 'sString';
  $handler->display->display_options['fields']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString']['field'] = 'sString';
  $handler->display->display_options['fields']['sString']['relationship'] = 'ProducerKeyID';
  $handler->display->display_options['fields']['sString']['label'] = 'Producer Name';
  $handler->display->display_options['fields']['sString']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['sString']['alter']['path'] = 'hccoord/producer?id=[ProducerKeyID]';
  $handler->display->display_options['fields']['sString']['element_label_colon'] = FALSE;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Status';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php print $row->bDisabled ? t(\'Inactive\') : t(\'Active\'); ?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['label'] = '';
  $handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = '<?php 

  if (!isset($view->args[1]) || $view->args[1] == \'yes\') { 
  $arrParams = array(\'pa\' => \'' . Consts::PERMISSION_AREA_PRODUCERS  .  '\', \'rid\' => $row->ProducerKeyID);
  if (!empty($row->CoordinatingGroupID)) { 
  $arrParams[\'id\'] = $row->CoordinatingGroupID;
  }
  print \'<a href="\' . url(\'hccoord/coordinate\', array(\'query\' => $arrParams)) . \'" >\' . t(\'Coordination\') . \'</a>\'; 
  } ?>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* Sort criterion: String: String */
  $handler->display->display_options['sorts']['sString']['id'] = 'sString';
  $handler->display->display_options['sorts']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['sorts']['sString']['field'] = 'sString';
  $handler->display->display_options['sorts']['sString']['relationship'] = 'ProducerKeyID';
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['default_argument_options']['argument'] = 'rw';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null_1']['id'] = 'null_1';
  $handler->display->display_options['arguments']['null_1']['table'] = 'views';
  $handler->display->display_options['arguments']['null_1']['field'] = 'null';
  $handler->display->display_options['arguments']['null_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null_1']['default_argument_options']['argument'] = 'yes';
  $handler->display->display_options['arguments']['null_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null_1']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
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
  /* Contextual filter: Producer: Coordinating Group ID */
  $handler->display->display_options['arguments']['CoordinatingGroupID']['id'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['table'] = 'T_Producer';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['field'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  $handler->display->display_options['arguments']['CoordinatingGroupID']['break_phrase'] = TRUE;

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
  /* Field: Order: Has Item Comments */
  $handler->display->display_options['fields']['bHasItemComments']['id'] = 'bHasItemComments';
  $handler->display->display_options['fields']['bHasItemComments']['table'] = 'T_Order';
  $handler->display->display_options['fields']['bHasItemComments']['field'] = 'bHasItemComments';
  $handler->display->display_options['fields']['bHasItemComments']['label'] = '';
  $handler->display->display_options['fields']['bHasItemComments']['exclude'] = TRUE;
  $handler->display->display_options['fields']['bHasItemComments']['element_label_colon'] = FALSE;
  /* Field: Order: Comments */
  $handler->display->display_options['fields']['sMemberComments']['id'] = 'sMemberComments';
  $handler->display->display_options['fields']['sMemberComments']['table'] = 'T_Order';
  $handler->display->display_options['fields']['sMemberComments']['field'] = 'sMemberComments';
  $handler->display->display_options['fields']['sMemberComments']['label'] = '';
  $handler->display->display_options['fields']['sMemberComments']['exclude'] = TRUE;
  $handler->display->display_options['fields']['sMemberComments']['element_label_colon'] = FALSE;
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
  $handler->display->display_options['fields']['dCreated']['custom_date_format'] = HOMECOOP_DATE_FORMAT;
  $handler->display->display_options['fields']['dCreated']['second_date_format'] = 'long';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Comments';
  $handler->display->display_options['fields']['php']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php']['alter']['path'] = 'hcorderitems?id=[OrderID]';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_value'] = 'if ($row->bHasItemComments) {
   return check_plain($row->sMemberComments) . t(\'+ More..\');
  }
  return check_plain($row->sMemberComments);';
  $handler->display->display_options['fields']['php']['php_output'] = '<?php print $value; ?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
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
  
  $views[$view->name] = $view;
  
  //----------------------------
  // Coop Order Pickup Locations
  //----------------------------
  
  $view = homecoop_cooporder_pickuplocs_get_view('homecoop_cooporder_pickup_locations', true);
  $views[$view->name] = $view;
  
  $view = homecoop_cooporder_pickuplocs_get_view('homecoop_cooporder_pickup_locations_nosums', false);
  $views[$view->name] = $view;
  
  //----------------------------
  // Coop Order Producers
  //----------------------------
  
  $view = new view();
  $view->name = 'homecoop_cooporder_producers';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_CoopOrderProducer';
  $view->human_name = 'HomeCoop CoopOrder Producers';
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
    'CoopOrderKeyID' => 'CoopOrderKeyID',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'CoopOrderKeyID' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['php_output'] = '<?php if (!isset($view->args[1]) || $view->args[1] == \'rw\') { ?><div><a href="<?php echo url(\'hccoord/coproducer\', array(\'query\' => array(\'coid\' => $view->args[0]))); ?>"><img border="0" title="<?php echo t(\'Add\'); ?>" src="<?php echo homecoop_getthemepath() . \'img/edit-add-2.png\'  ?>" /></a></div><?php } ?>';
  /* Relationship: Coop Order Producer: Producer */
  $handler->display->display_options['relationships']['ProducerKeyID']['id'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['table'] = 'T_CoopOrderProducer';
  $handler->display->display_options['relationships']['ProducerKeyID']['field'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['label'] = 'Producer';
  $handler->display->display_options['relationships']['ProducerKeyID']['required'] = TRUE;
  /* Relationship: Producer: Producer Name */
  $handler->display->display_options['relationships']['ProducerKeyID_1']['id'] = 'ProducerKeyID_1';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['table'] = 'T_Producer';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['field'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['relationship'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['label'] = 'ProducerName';
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID']['id'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['relationship'] = 'ProducerKeyID_1';
  $handler->display->display_options['relationships']['LangID']['label'] = 'ProducerNameLang';
  $handler->display->display_options['relationships']['LangID']['required'] = TRUE;
  /* Field: Coop Order Producer: Coop Order ID */
  $handler->display->display_options['fields']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['CoopOrderKeyID']['table'] = 'T_CoopOrderProducer';
  $handler->display->display_options['fields']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['CoopOrderKeyID']['label'] = '';
  $handler->display->display_options['fields']['CoopOrderKeyID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['CoopOrderKeyID']['element_label_colon'] = FALSE;
  /* Field: Coop Order Producer: Producer ID */
  $handler->display->display_options['fields']['ProducerKeyID']['id'] = 'ProducerKeyID';
  $handler->display->display_options['fields']['ProducerKeyID']['table'] = 'T_CoopOrderProducer';
  $handler->display->display_options['fields']['ProducerKeyID']['field'] = 'ProducerKeyID';
  $handler->display->display_options['fields']['ProducerKeyID']['label'] = '';
  $handler->display->display_options['fields']['ProducerKeyID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ProducerKeyID']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString']['id'] = 'sString';
  $handler->display->display_options['fields']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString']['field'] = 'sString';
  $handler->display->display_options['fields']['sString']['relationship'] = 'ProducerKeyID_1';
  $handler->display->display_options['fields']['sString']['label'] = 'Producer';
  $handler->display->display_options['fields']['sString']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['sString']['alter']['path'] = 'hccoord/coproducer?coid=[CoopOrderKeyID]&pid=[ProducerKeyID]';
  $handler->display->display_options['fields']['sString']['element_label_colon'] = FALSE;
  /* Field: Coop Order Producer: Delivery Capacity */
  $handler->display->display_options['fields']['fMaxBurden']['id'] = 'fMaxBurden';
  $handler->display->display_options['fields']['fMaxBurden']['table'] = 'T_CoopOrderProducer';
  $handler->display->display_options['fields']['fMaxBurden']['field'] = 'fMaxBurden';
  $handler->display->display_options['fields']['fMaxBurden']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fMaxBurden']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['fMaxBurden']['precision'] = '0';
  /* Field: Coop Order Producer: Producer Total */
  $handler->display->display_options['fields']['mProducerTotal']['id'] = 'mProducerTotal';
  $handler->display->display_options['fields']['mProducerTotal']['table'] = 'T_CoopOrderProducer';
  $handler->display->display_options['fields']['mProducerTotal']['field'] = 'mProducerTotal';
  $handler->display->display_options['fields']['mProducerTotal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mProducerTotal']['precision'] = '0';
  /* Field: Coop Order Producer: Total Coop */
  $handler->display->display_options['fields']['mCoopTotal']['id'] = 'mCoopTotal';
  $handler->display->display_options['fields']['mCoopTotal']['table'] = 'T_CoopOrderProducer';
  $handler->display->display_options['fields']['mCoopTotal']['field'] = 'mCoopTotal';
  $handler->display->display_options['fields']['mCoopTotal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mCoopTotal']['precision'] = '0';
  /* Field: Coop Order Producer: Total Delivery */
  $handler->display->display_options['fields']['mTotalDelivery']['id'] = 'mTotalDelivery';
  $handler->display->display_options['fields']['mTotalDelivery']['table'] = 'T_CoopOrderProducer';
  $handler->display->display_options['fields']['mTotalDelivery']['field'] = 'mTotalDelivery';
  $handler->display->display_options['fields']['mTotalDelivery']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mTotalDelivery']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['mTotalDelivery']['precision'] = '0';
  /* Contextual filter: Coop Order Producer: Coop Order ID */
  $handler->display->display_options['arguments']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['table'] = 'T_CoopOrderProducer';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
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
  /* Contextual filter: Producer: Coordinating Group ID */
  $handler->display->display_options['arguments']['CoordinatingGroupID']['id'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['table'] = 'T_Producer';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['field'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['relationship'] = 'ProducerKeyID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;

  $views[$view->name] = $view;
  
  //-------------------
  // CoopOrder Products
  //-------------------
  
  $view = new view();
  $view->name = 'homecoop_cooporder_products';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_CoopOrderProduct';
  $view->human_name = 'HomeCoop CoopOrder Products';
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
    'CoopOrderKeyID' => 'CoopOrderKeyID',
    'ProductKeyID' => 'ProductKeyID',
    'sString' => 'sString',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'CoopOrderKeyID' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ProductKeyID' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sString' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['php_output'] = '<?php if (!isset($view->args[1]) || $view->args[1] == \'rw\') { ?><div><a href="<?php echo url(\'hccoord/coproduct\', array(\'query\' => array(\'coid\' => $view->args[0]))); ?>"><img border="0" title="<?php echo t(\'Add\'); ?>" src="<?php echo homecoop_getthemepath() . \'img/edit-add-2.png\'  ?>" /></a></div><?php } ?>';
  /* Relationship: Coop Order Product: Product */
  $handler->display->display_options['relationships']['ProductKeyID']['id'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['ProductKeyID']['table'] = 'T_CoopOrderProduct';
  $handler->display->display_options['relationships']['ProductKeyID']['field'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['ProductKeyID']['label'] = 'Product';
  $handler->display->display_options['relationships']['ProductKeyID']['required'] = TRUE;
  /* Relationship: Product: Product Name */
  $handler->display->display_options['relationships']['ProductKeyID_1']['id'] = 'ProductKeyID_1';
  $handler->display->display_options['relationships']['ProductKeyID_1']['table'] = 'T_Product';
  $handler->display->display_options['relationships']['ProductKeyID_1']['field'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['ProductKeyID_1']['relationship'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['ProductKeyID_1']['label'] = 'ProductName';
  $handler->display->display_options['relationships']['ProductKeyID_1']['required'] = TRUE;
  /* Relationship: Product: Producer */
  $handler->display->display_options['relationships']['ProducerKeyID']['id'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['table'] = 'T_Product';
  $handler->display->display_options['relationships']['ProducerKeyID']['field'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['relationship'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID']['id'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['relationship'] = 'ProductKeyID_1';
  $handler->display->display_options['relationships']['LangID']['label'] = 'ProductNameLang';
  $handler->display->display_options['relationships']['LangID']['required'] = TRUE;
  /* Relationship: Producer: Producer Name */
  $handler->display->display_options['relationships']['ProducerKeyID_1']['id'] = 'ProducerKeyID_1';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['table'] = 'T_Producer';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['field'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['relationship'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['label'] = 'ProducerName';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID_1']['id'] = 'LangID_1';
  $handler->display->display_options['relationships']['LangID_1']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID_1']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID_1']['relationship'] = 'ProducerKeyID_1';
  $handler->display->display_options['relationships']['LangID_1']['label'] = 'ProducerNameLang';
  $handler->display->display_options['relationships']['LangID_1']['required'] = TRUE;
  /* Relationship: Product: Unit */
  $handler->display->display_options['relationships']['UnitKeyID']['id'] = 'UnitKeyID';
  $handler->display->display_options['relationships']['UnitKeyID']['table'] = 'T_Product';
  $handler->display->display_options['relationships']['UnitKeyID']['field'] = 'UnitKeyID';
  $handler->display->display_options['relationships']['UnitKeyID']['relationship'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['UnitKeyID']['label'] = 'ProductUnit';
  $handler->display->display_options['relationships']['UnitKeyID']['required'] = TRUE;
  /* Relationship: Unit: Unit Abbreviation */
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['id'] = 'UnitAbbreviationStringKeyID';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['table'] = 'T_Unit';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['field'] = 'UnitAbbreviationStringKeyID';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['relationship'] = 'UnitKeyID';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['label'] = 'ProductUnitAbrev';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID_2']['id'] = 'LangID_2';
  $handler->display->display_options['relationships']['LangID_2']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID_2']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID_2']['relationship'] = 'UnitAbbreviationStringKeyID';
  $handler->display->display_options['relationships']['LangID_2']['label'] = 'ProductUnitAbrevName';
  $handler->display->display_options['relationships']['LangID_2']['required'] = TRUE;
  /* Field: Coop Order Product: Coop Order ID */
  $handler->display->display_options['fields']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['CoopOrderKeyID']['table'] = 'T_CoopOrderProduct';
  $handler->display->display_options['fields']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['CoopOrderKeyID']['label'] = '';
  $handler->display->display_options['fields']['CoopOrderKeyID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['CoopOrderKeyID']['element_label_colon'] = FALSE;
  /* Field: Coop Order Product: Product ID */
  $handler->display->display_options['fields']['ProductKeyID']['id'] = 'ProductKeyID';
  $handler->display->display_options['fields']['ProductKeyID']['table'] = 'T_CoopOrderProduct';
  $handler->display->display_options['fields']['ProductKeyID']['field'] = 'ProductKeyID';
  $handler->display->display_options['fields']['ProductKeyID']['label'] = '';
  $handler->display->display_options['fields']['ProductKeyID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ProductKeyID']['element_label_colon'] = FALSE;
  /* Field: Coop Order Product: Status */
  $handler->display->display_options['fields']['bDisabled']['id'] = 'bDisabled';
  $handler->display->display_options['fields']['bDisabled']['table'] = 'T_CoopOrderProduct';
  $handler->display->display_options['fields']['bDisabled']['field'] = 'bDisabled';
  $handler->display->display_options['fields']['bDisabled']['label'] = '';
  $handler->display->display_options['fields']['bDisabled']['exclude'] = TRUE;
  $handler->display->display_options['fields']['bDisabled']['element_label_colon'] = FALSE;
  /* Field: Product: Quantity */
  $handler->display->display_options['fields']['fQuantity']['id'] = 'fQuantity';
  $handler->display->display_options['fields']['fQuantity']['table'] = 'T_Product';
  $handler->display->display_options['fields']['fQuantity']['field'] = 'fQuantity';
  $handler->display->display_options['fields']['fQuantity']['relationship'] = 'ProductKeyID';
  $handler->display->display_options['fields']['fQuantity']['label'] = '';
  $handler->display->display_options['fields']['fQuantity']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fQuantity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fQuantity']['precision'] = '0';
  /* Field: String: String */
  $handler->display->display_options['fields']['sString_2']['id'] = 'sString_2';
  $handler->display->display_options['fields']['sString_2']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString_2']['field'] = 'sString';
  $handler->display->display_options['fields']['sString_2']['relationship'] = 'UnitAbbreviationStringKeyID';
  $handler->display->display_options['fields']['sString_2']['label'] = '';
  $handler->display->display_options['fields']['sString_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['sString_2']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString']['id'] = 'sString';
  $handler->display->display_options['fields']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString']['field'] = 'sString';
  $handler->display->display_options['fields']['sString']['relationship'] = 'ProductKeyID_1';
  $handler->display->display_options['fields']['sString']['label'] = 'Product';
  $handler->display->display_options['fields']['sString']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['sString']['alter']['path'] = 'hccoord/coproduct?prdid=[ProductKeyID]&coid=[CoopOrderKeyID]';
  $handler->display->display_options['fields']['sString']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString_1']['id'] = 'sString_1';
  $handler->display->display_options['fields']['sString_1']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString_1']['field'] = 'sString';
  $handler->display->display_options['fields']['sString_1']['relationship'] = 'ProducerKeyID_1';
  $handler->display->display_options['fields']['sString_1']['label'] = 'Producer';
  $handler->display->display_options['fields']['sString_1']['element_label_colon'] = FALSE;
  /* Field: Coop Order Product: Total Quantity Ordered */
  $handler->display->display_options['fields']['fTotalCoopOrder']['id'] = 'fTotalCoopOrder';
  $handler->display->display_options['fields']['fTotalCoopOrder']['table'] = 'T_CoopOrderProduct';
  $handler->display->display_options['fields']['fTotalCoopOrder']['field'] = 'fTotalCoopOrder';
  $handler->display->display_options['fields']['fTotalCoopOrder']['label'] = 'Total';
  $handler->display->display_options['fields']['fTotalCoopOrder']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fTotalCoopOrder']['precision'] = '0';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Status';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php print $row->bDisabled? t(\'Inactive\') : t(\'Active\'); ?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Coop Order Product: Producer Total */
  $handler->display->display_options['fields']['mProducerTotal']['id'] = 'mProducerTotal';
  $handler->display->display_options['fields']['mProducerTotal']['table'] = 'T_CoopOrderProduct';
  $handler->display->display_options['fields']['mProducerTotal']['field'] = 'mProducerTotal';
  $handler->display->display_options['fields']['mProducerTotal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mProducerTotal']['precision'] = '0';
  /* Field: Coop Order Product: Coop. Price */
  $handler->display->display_options['fields']['mCoopPrice']['id'] = 'mCoopPrice';
  $handler->display->display_options['fields']['mCoopPrice']['table'] = 'T_CoopOrderProduct';
  $handler->display->display_options['fields']['mCoopPrice']['field'] = 'mCoopPrice';
  $handler->display->display_options['fields']['mCoopPrice']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mCoopPrice']['precision'] = '0';
  /* Field: Coop Order Product: Producer Price */
  $handler->display->display_options['fields']['mProducerPrice']['id'] = 'mProducerPrice';
  $handler->display->display_options['fields']['mProducerPrice']['table'] = 'T_CoopOrderProduct';
  $handler->display->display_options['fields']['mProducerPrice']['field'] = 'mProducerPrice';
  $handler->display->display_options['fields']['mProducerPrice']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mProducerPrice']['precision'] = '0';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['label'] = 'Quantity';
  $handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = '<?php echo $row->fQuantity, \' \', $row->sString_2; ?>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* Field: Coop Order Product: Burden */
  $handler->display->display_options['fields']['fBurden']['id'] = 'fBurden';
  $handler->display->display_options['fields']['fBurden']['table'] = 'T_CoopOrderProduct';
  $handler->display->display_options['fields']['fBurden']['field'] = 'fBurden';
  $handler->display->display_options['fields']['fBurden']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fBurden']['precision'] = '0';
  /* Sort criterion: Coop Order Product: Status */
  $handler->display->display_options['sorts']['bDisabled']['id'] = 'bDisabled';
  $handler->display->display_options['sorts']['bDisabled']['table'] = 'T_CoopOrderProduct';
  $handler->display->display_options['sorts']['bDisabled']['field'] = 'bDisabled';
  /* Sort criterion: Product: Sorting Order */
  $handler->display->display_options['sorts']['nSortOrder']['id'] = 'nSortOrder';
  $handler->display->display_options['sorts']['nSortOrder']['table'] = 'T_Product';
  $handler->display->display_options['sorts']['nSortOrder']['field'] = 'nSortOrder';
  $handler->display->display_options['sorts']['nSortOrder']['relationship'] = 'ProductKeyID';
  /* Contextual filter: Coop Order Product: Coop Order ID */
  $handler->display->display_options['arguments']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['table'] = 'T_CoopOrderProduct';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
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
  /* Contextual filter: Language: PHP Folder */
  $handler->display->display_options['arguments']['sPhpFolder_2']['id'] = 'sPhpFolder_2';
  $handler->display->display_options['arguments']['sPhpFolder_2']['table'] = 'Tlng_Language';
  $handler->display->display_options['arguments']['sPhpFolder_2']['field'] = 'sPhpFolder';
  $handler->display->display_options['arguments']['sPhpFolder_2']['relationship'] = 'LangID_2';
  $handler->display->display_options['arguments']['sPhpFolder_2']['default_action'] = 'default';
  $handler->display->display_options['arguments']['sPhpFolder_2']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['sPhpFolder_2']['default_argument_options']['code'] = 'global $language; return $language->language;';
  $handler->display->display_options['arguments']['sPhpFolder_2']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['sPhpFolder_2']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['sPhpFolder_2']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  $handler->display->display_options['arguments']['sPhpFolder_2']['limit'] = '0';
  /* Contextual filter: Producer: Coordinating Group ID */
  $handler->display->display_options['arguments']['CoordinatingGroupID']['id'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['table'] = 'T_Producer';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['field'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['relationship'] = 'ProducerKeyID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;

  $views[$view->name] = $view;
  
  $view = new view();
  $view->name = 'homecoop_cooporder_pickup_location_producers';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_CoopOrderPickupLocationProducer';
  $view->human_name = 'HomeCoop CoopOrder Pickup Location Producers';
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
    'sString' => 'sString',
    'mCoopTotal' => 'mCoopTotal',
    'mProducerTotal' => 'mProducerTotal',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'sString' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mCoopTotal' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mProducerTotal' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Coop Order Pickup Location Producer: Coop Order Pickup Location Producer - Producer */
  $handler->display->display_options['relationships']['ProducerKeyID']['id'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['table'] = 'T_CoopOrderPickupLocationProducer';
  $handler->display->display_options['relationships']['ProducerKeyID']['field'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['label'] = 'Producer';
  $handler->display->display_options['relationships']['ProducerKeyID']['required'] = TRUE;
  /* Relationship: Producer: Producer Name */
  $handler->display->display_options['relationships']['ProducerKeyID_1']['id'] = 'ProducerKeyID_1';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['table'] = 'T_Producer';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['field'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['relationship'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['label'] = 'ProducerName';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID']['id'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['relationship'] = 'ProducerKeyID_1';
  $handler->display->display_options['relationships']['LangID']['label'] = 'ProducerNameLang';
  $handler->display->display_options['relationships']['LangID']['required'] = TRUE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString']['id'] = 'sString';
  $handler->display->display_options['fields']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString']['field'] = 'sString';
  $handler->display->display_options['fields']['sString']['relationship'] = 'ProducerKeyID_1';
  $handler->display->display_options['fields']['sString']['label'] = 'Producer';
  $handler->display->display_options['fields']['sString']['element_label_colon'] = FALSE;
  /* Field: Coop Order Pickup Location Producer: Total Coop (calculated) */
  $handler->display->display_options['fields']['mCoopTotal']['id'] = 'mCoopTotal';
  $handler->display->display_options['fields']['mCoopTotal']['table'] = 'T_CoopOrderPickupLocationProducer';
  $handler->display->display_options['fields']['mCoopTotal']['field'] = 'mCoopTotal';
  $handler->display->display_options['fields']['mCoopTotal']['label'] = 'Total Coop';
  $handler->display->display_options['fields']['mCoopTotal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mCoopTotal']['precision'] = '0';
  /* Field: Coop Order Pickup Location Producer: Total Producers (calculated) */
  $handler->display->display_options['fields']['mProducerTotal']['id'] = 'mProducerTotal';
  $handler->display->display_options['fields']['mProducerTotal']['table'] = 'T_CoopOrderPickupLocationProducer';
  $handler->display->display_options['fields']['mProducerTotal']['field'] = 'mProducerTotal';
  $handler->display->display_options['fields']['mProducerTotal']['label'] = 'Total Producers';
  $handler->display->display_options['fields']['mProducerTotal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mProducerTotal']['precision'] = '0';
  /* Sort criterion: String: String */
  $handler->display->display_options['sorts']['sString']['id'] = 'sString';
  $handler->display->display_options['sorts']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['sorts']['sString']['field'] = 'sString';
  $handler->display->display_options['sorts']['sString']['relationship'] = 'ProducerKeyID_1';
  /* Contextual filter: Coop Order Pickup Location Producer: Coop Order ID */
  $handler->display->display_options['arguments']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['table'] = 'T_CoopOrderPickupLocationProducer';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  /* Contextual filter: Coop Order Pickup Location Producer: Pickup Location ID */
  $handler->display->display_options['arguments']['PickupLocationKeyID']['id'] = 'PickupLocationKeyID';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['table'] = 'T_CoopOrderPickupLocationProducer';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['field'] = 'PickupLocationKeyID';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
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
  /* Contextual filter: Producer: Coordinating Group ID */
  $handler->display->display_options['arguments']['CoordinatingGroupID']['id'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['table'] = 'T_Producer';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['field'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['relationship'] = 'ProducerKeyID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;

  $views[$view->name] = $view;
  
  $view = new view();
  $view->name = 'homecoop_cooporder_pickuplocation_products';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_CoopOrderPickupLocationProduct';
  $view->human_name = 'HomeCoop CoopOrder PickupLocation Products';
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
    'CoopOrderKeyID' => 'CoopOrderKeyID',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'CoopOrderKeyID' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Coop Order Pickup Location Product: Coop Order Pickup Location Product - Product */
  $handler->display->display_options['relationships']['ProductKeyID']['id'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['ProductKeyID']['table'] = 'T_CoopOrderPickupLocationProduct';
  $handler->display->display_options['relationships']['ProductKeyID']['field'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['ProductKeyID']['label'] = 'Product';
  $handler->display->display_options['relationships']['ProductKeyID']['required'] = TRUE;
  /* Relationship: Product: Producer */
  $handler->display->display_options['relationships']['ProducerKeyID']['id'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['table'] = 'T_Product';
  $handler->display->display_options['relationships']['ProducerKeyID']['field'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['relationship'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID']['label'] = 'Producer';
  $handler->display->display_options['relationships']['ProducerKeyID']['required'] = TRUE;
  /* Relationship: Product: Product Name */
  $handler->display->display_options['relationships']['ProductKeyID_1']['id'] = 'ProductKeyID_1';
  $handler->display->display_options['relationships']['ProductKeyID_1']['table'] = 'T_Product';
  $handler->display->display_options['relationships']['ProductKeyID_1']['field'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['ProductKeyID_1']['relationship'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['ProductKeyID_1']['label'] = 'ProductName';
  $handler->display->display_options['relationships']['ProductKeyID_1']['required'] = TRUE;
  /* Relationship: Product: Unit */
  $handler->display->display_options['relationships']['UnitKeyID']['id'] = 'UnitKeyID';
  $handler->display->display_options['relationships']['UnitKeyID']['table'] = 'T_Product';
  $handler->display->display_options['relationships']['UnitKeyID']['field'] = 'UnitKeyID';
  $handler->display->display_options['relationships']['UnitKeyID']['relationship'] = 'ProductKeyID';
  $handler->display->display_options['relationships']['UnitKeyID']['label'] = 'ProductUnit';
  $handler->display->display_options['relationships']['UnitKeyID']['required'] = TRUE;
  /* Relationship: Producer: Producer Name */
  $handler->display->display_options['relationships']['ProducerKeyID_1']['id'] = 'ProducerKeyID_1';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['table'] = 'T_Producer';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['field'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['relationship'] = 'ProducerKeyID';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['label'] = 'ProducerName';
  $handler->display->display_options['relationships']['ProducerKeyID_1']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID']['id'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['relationship'] = 'ProductKeyID_1';
  $handler->display->display_options['relationships']['LangID']['label'] = 'ProductNameLang';
  $handler->display->display_options['relationships']['LangID']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID_1']['id'] = 'LangID_1';
  $handler->display->display_options['relationships']['LangID_1']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID_1']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID_1']['relationship'] = 'ProducerKeyID_1';
  $handler->display->display_options['relationships']['LangID_1']['label'] = 'ProducerNameLang';
  $handler->display->display_options['relationships']['LangID_1']['required'] = TRUE;
  /* Relationship: Unit: Unit Abbreviation */
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['id'] = 'UnitAbbreviationStringKeyID';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['table'] = 'T_Unit';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['field'] = 'UnitAbbreviationStringKeyID';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['relationship'] = 'UnitKeyID';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['label'] = 'UnitAbbreviation';
  $handler->display->display_options['relationships']['UnitAbbreviationStringKeyID']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID_2']['id'] = 'LangID_2';
  $handler->display->display_options['relationships']['LangID_2']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID_2']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID_2']['relationship'] = 'UnitAbbreviationStringKeyID';
  $handler->display->display_options['relationships']['LangID_2']['label'] = 'UnitAbbrevLang';
  $handler->display->display_options['relationships']['LangID_2']['required'] = TRUE;
  /* Field: Coop Order Pickup Location Product: Coop Order ID */
  $handler->display->display_options['fields']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['CoopOrderKeyID']['table'] = 'T_CoopOrderPickupLocationProduct';
  $handler->display->display_options['fields']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['CoopOrderKeyID']['label'] = '';
  $handler->display->display_options['fields']['CoopOrderKeyID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['CoopOrderKeyID']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString']['id'] = 'sString';
  $handler->display->display_options['fields']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString']['field'] = 'sString';
  $handler->display->display_options['fields']['sString']['relationship'] = 'ProducerKeyID_1';
  $handler->display->display_options['fields']['sString']['label'] = 'Producer';
  $handler->display->display_options['fields']['sString']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString_1']['id'] = 'sString_1';
  $handler->display->display_options['fields']['sString_1']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString_1']['field'] = 'sString';
  $handler->display->display_options['fields']['sString_1']['relationship'] = 'ProductKeyID_1';
  $handler->display->display_options['fields']['sString_1']['label'] = 'Product';
  $handler->display->display_options['fields']['sString_1']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString_2']['id'] = 'sString_2';
  $handler->display->display_options['fields']['sString_2']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString_2']['field'] = 'sString';
  $handler->display->display_options['fields']['sString_2']['relationship'] = 'UnitAbbreviationStringKeyID';
  $handler->display->display_options['fields']['sString_2']['label'] = '';
  $handler->display->display_options['fields']['sString_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['sString_2']['element_label_colon'] = FALSE;
  /* Field: Product: Package Size */
  $handler->display->display_options['fields']['fPackageSize']['id'] = 'fPackageSize';
  $handler->display->display_options['fields']['fPackageSize']['table'] = 'T_Product';
  $handler->display->display_options['fields']['fPackageSize']['field'] = 'fPackageSize';
  $handler->display->display_options['fields']['fPackageSize']['relationship'] = 'ProductKeyID';
  $handler->display->display_options['fields']['fPackageSize']['label'] = '';
  $handler->display->display_options['fields']['fPackageSize']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fPackageSize']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fPackageSize']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['fPackageSize']['precision'] = '2';
  /* Field: Product: Quantity */
  $handler->display->display_options['fields']['fQuantity']['id'] = 'fQuantity';
  $handler->display->display_options['fields']['fQuantity']['table'] = 'T_Product';
  $handler->display->display_options['fields']['fQuantity']['field'] = 'fQuantity';
  $handler->display->display_options['fields']['fQuantity']['relationship'] = 'ProductKeyID';
  $handler->display->display_options['fields']['fQuantity']['label'] = '';
  $handler->display->display_options['fields']['fQuantity']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fQuantity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fQuantity']['precision'] = '0';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Package Size';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_value'] = 'if (!empty($row->fPackageSize)) {
    return $row->fPackageSize;
  }
  return $row->fQuantity;';
  $handler->display->display_options['fields']['php']['php_output'] = '<?php print $value . \' \' . $row->sString_2; ?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Coop Order Pickup Location Product: Total Quantity Ordered */
  $handler->display->display_options['fields']['fTotalCoopOrder']['id'] = 'fTotalCoopOrder';
  $handler->display->display_options['fields']['fTotalCoopOrder']['table'] = 'T_CoopOrderPickupLocationProduct';
  $handler->display->display_options['fields']['fTotalCoopOrder']['field'] = 'fTotalCoopOrder';
  $handler->display->display_options['fields']['fTotalCoopOrder']['label'] = 'Quantity';
  $handler->display->display_options['fields']['fTotalCoopOrder']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fTotalCoopOrder']['precision'] = '0';
  /* Field: Coop Order Pickup Location Product: Total Coop */
  $handler->display->display_options['fields']['mCoopTotal']['id'] = 'mCoopTotal';
  $handler->display->display_options['fields']['mCoopTotal']['table'] = 'T_CoopOrderPickupLocationProduct';
  $handler->display->display_options['fields']['mCoopTotal']['field'] = 'mCoopTotal';
  $handler->display->display_options['fields']['mCoopTotal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mCoopTotal']['precision'] = '0';
  /* Field: Coop Order Pickup Location Product: Total Producers */
  $handler->display->display_options['fields']['mProducerTotal']['id'] = 'mProducerTotal';
  $handler->display->display_options['fields']['mProducerTotal']['table'] = 'T_CoopOrderPickupLocationProduct';
  $handler->display->display_options['fields']['mProducerTotal']['field'] = 'mProducerTotal';
  $handler->display->display_options['fields']['mProducerTotal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mProducerTotal']['precision'] = '0';
  /* Contextual filter: Coop Order Pickup Location Product: Coop Order ID */
  $handler->display->display_options['arguments']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['table'] = 'T_CoopOrderPickupLocationProduct';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  /* Contextual filter: Coop Order Pickup Location Product: Pickup Location ID */
  $handler->display->display_options['arguments']['PickupLocationKeyID']['id'] = 'PickupLocationKeyID';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['table'] = 'T_CoopOrderPickupLocationProduct';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['field'] = 'PickupLocationKeyID';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
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
  /* Contextual filter: Language: PHP Folder */
  $handler->display->display_options['arguments']['sPhpFolder_2']['id'] = 'sPhpFolder_2';
  $handler->display->display_options['arguments']['sPhpFolder_2']['table'] = 'Tlng_Language';
  $handler->display->display_options['arguments']['sPhpFolder_2']['field'] = 'sPhpFolder';
  $handler->display->display_options['arguments']['sPhpFolder_2']['relationship'] = 'LangID_2';
  $handler->display->display_options['arguments']['sPhpFolder_2']['default_action'] = 'default';
  $handler->display->display_options['arguments']['sPhpFolder_2']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['sPhpFolder_2']['default_argument_options']['code'] = 'global $language; return $language->language;';
  $handler->display->display_options['arguments']['sPhpFolder_2']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['sPhpFolder_2']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['sPhpFolder_2']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  $handler->display->display_options['arguments']['sPhpFolder_2']['limit'] = '0';
  /* Contextual filter: Producer: Coordinating Group ID */
  $handler->display->display_options['arguments']['CoordinatingGroupID']['id'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['table'] = 'T_Producer';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['field'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['relationship'] = 'ProducerKeyID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  /* Filter criterion: Coop Order Pickup Location Product: Total Quantity Ordered */
  $handler->display->display_options['filters']['fTotalCoopOrder']['id'] = 'fTotalCoopOrder';
  $handler->display->display_options['filters']['fTotalCoopOrder']['table'] = 'T_CoopOrderPickupLocationProduct';
  $handler->display->display_options['filters']['fTotalCoopOrder']['field'] = 'fTotalCoopOrder';
  $handler->display->display_options['filters']['fTotalCoopOrder']['operator'] = '>';
  $handler->display->display_options['filters']['fTotalCoopOrder']['value']['value'] = '0';

  $views[$view->name] = $view;
  
  $view = new view();
  $view->name = 'homecoop_cooporder_pickuplocation_orders';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_Order';
  $view->human_name = 'HomeCoop CoopOrder PickupLocation Orders';
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
    'sName' => 'sName',
    'sEMail' => 'sEMail',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'OrderID' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sName' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sEMail' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Order: Member */
  $handler->display->display_options['relationships']['MemberID']['id'] = 'MemberID';
  $handler->display->display_options['relationships']['MemberID']['table'] = 'T_Order';
  $handler->display->display_options['relationships']['MemberID']['field'] = 'MemberID';
  $handler->display->display_options['relationships']['MemberID']['label'] = 'Member';
  $handler->display->display_options['relationships']['MemberID']['required'] = TRUE;
  /* Field: Order: Order ID */
  $handler->display->display_options['fields']['OrderID']['id'] = 'OrderID';
  $handler->display->display_options['fields']['OrderID']['table'] = 'T_Order';
  $handler->display->display_options['fields']['OrderID']['field'] = 'OrderID';
  $handler->display->display_options['fields']['OrderID']['label'] = '';
  $handler->display->display_options['fields']['OrderID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['OrderID']['element_label_colon'] = FALSE;
  /* Field: Order: Comments */
  $handler->display->display_options['fields']['sMemberComments']['id'] = 'sMemberComments';
  $handler->display->display_options['fields']['sMemberComments']['table'] = 'T_Order';
  $handler->display->display_options['fields']['sMemberComments']['field'] = 'sMemberComments';
  $handler->display->display_options['fields']['sMemberComments']['label'] = '';
  $handler->display->display_options['fields']['sMemberComments']['exclude'] = TRUE;
  $handler->display->display_options['fields']['sMemberComments']['element_label_colon'] = FALSE;
  /* Field: Order: Has Item Comments */
  $handler->display->display_options['fields']['bHasItemComments']['id'] = 'bHasItemComments';
  $handler->display->display_options['fields']['bHasItemComments']['table'] = 'T_Order';
  $handler->display->display_options['fields']['bHasItemComments']['field'] = 'bHasItemComments';
  $handler->display->display_options['fields']['bHasItemComments']['label'] = '';
  $handler->display->display_options['fields']['bHasItemComments']['exclude'] = TRUE;
  $handler->display->display_options['fields']['bHasItemComments']['element_label_colon'] = FALSE;
  /* Field: Member: Name */
  $handler->display->display_options['fields']['sName']['id'] = 'sName';
  $handler->display->display_options['fields']['sName']['table'] = 'T_Member';
  $handler->display->display_options['fields']['sName']['field'] = 'sName';
  $handler->display->display_options['fields']['sName']['relationship'] = 'MemberID';
  $handler->display->display_options['fields']['sName']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['sName']['alter']['path'] = 'hcorderitems?id=[OrderID]';
  $handler->display->display_options['fields']['sName']['element_label_colon'] = FALSE;
  /* Field: Member: Email address */
  $handler->display->display_options['fields']['sEMail']['id'] = 'sEMail';
  $handler->display->display_options['fields']['sEMail']['table'] = 'T_Member';
  $handler->display->display_options['fields']['sEMail']['field'] = 'sEMail';
  $handler->display->display_options['fields']['sEMail']['relationship'] = 'MemberID';
  /* Field: Order: Total Amount */
  $handler->display->display_options['fields']['mCoopTotalIncFee']['id'] = 'mCoopTotalIncFee';
  $handler->display->display_options['fields']['mCoopTotalIncFee']['table'] = 'T_Order';
  $handler->display->display_options['fields']['mCoopTotalIncFee']['field'] = 'mCoopTotalIncFee';
  $handler->display->display_options['fields']['mCoopTotalIncFee']['label'] = 'Total';
  $handler->display->display_options['fields']['mCoopTotalIncFee']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mCoopTotalIncFee']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['mCoopTotalIncFee']['precision'] = '2';
  /* Field: Member: Balance */
  $handler->display->display_options['fields']['mBalance']['id'] = 'mBalance';
  $handler->display->display_options['fields']['mBalance']['table'] = 'T_Member';
  $handler->display->display_options['fields']['mBalance']['field'] = 'mBalance';
  $handler->display->display_options['fields']['mBalance']['relationship'] = 'MemberID';
  $handler->display->display_options['fields']['mBalance']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mBalance']['precision'] = '0';
  /* Field: Order: Created On */
  $handler->display->display_options['fields']['dCreated']['id'] = 'dCreated';
  $handler->display->display_options['fields']['dCreated']['table'] = 'T_Order';
  $handler->display->display_options['fields']['dCreated']['field'] = 'dCreated';
  $handler->display->display_options['fields']['dCreated']['label'] = 'Order Date';
  $handler->display->display_options['fields']['dCreated']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['dCreated']['date_format'] = 'custom';
  $handler->display->display_options['fields']['dCreated']['custom_date_format'] = HOMECOOP_DATE_FORMAT;
  $handler->display->display_options['fields']['dCreated']['second_date_format'] = 'long';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Comments';
  $handler->display->display_options['fields']['php']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php']['alter']['path'] = 'hcorderitems?id=[OrderID]';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_value'] = 'if ($row->bHasItemComments) {
   return check_plain($row->sMemberComments) . t(\'+ More..\');
  }
  return check_plain($row->sMemberComments);';
  $handler->display->display_options['fields']['php']['php_output'] = '<?php print $value; ?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Sort criterion: Order: Created On */
  $handler->display->display_options['sorts']['dCreated']['id'] = 'dCreated';
  $handler->display->display_options['sorts']['dCreated']['table'] = 'T_Order';
  $handler->display->display_options['sorts']['dCreated']['field'] = 'dCreated';
  $handler->display->display_options['sorts']['dCreated']['order'] = 'DESC';
  /* Contextual filter: Order: Coop Order ID */
  $handler->display->display_options['arguments']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['table'] = 'T_Order';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  /* Contextual filter: Order: Pickup Location ID */
  $handler->display->display_options['arguments']['PickupLocationKeyID']['id'] = 'PickupLocationKeyID';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['table'] = 'T_Order';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['field'] = 'PickupLocationKeyID';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['PickupLocationKeyID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;

  $views[$view->name] = $view;

  return $views;
}

/*
 * Translations. moved to a separate not-running function
 */
function homecoop_views_translatables() {
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
  
  $translatables['homecoop_cooporder_pickuplocation_products'] = array(
    t('Package Size'),
    t('Total Producers'),
  );
  
  $translatables['homecoop_cooporder_producers'] = array(
    t('Producer'),
    t('ProducerName'),
    t('ProducerNameLang'),
    t('Delivery Capacity'),
    t('Producer Total'),
    t('Total Coop'),
    t('Total Delivery'),
  );

  
  $translatables['homecoop_cooporder_pickup_locations'] = array(
    t('COPickup-Pickup'),
    t('PickupAddress'),
    t('PickupName'),
    t('PickupNameLang'),
    t('PickupAddressLang'),
    t('Location Name'),
    t('Total Burden'),
    t('Total storage full'),
    t('Total Coop'),
  );
  
  $translatables['homecoop_pickup_locations'] = array(
    t('PickupLocationAddress'),
    t('PickupLocationName'),
    t('AddressLang'),
    t('NameLang'),
    t('Address'),
    t('Cachier'),
    t('Cachier Update'),
  );
  
  $translatables['homecoop_products'] = array(
    t('ProductProducer'),
    t('ProductName'),
    t('ProductNameLang'),
    t('ProducerName'),
    t('ProducerNameLang'),
    t('ProductUnit'),
    t('ProductUnitAbrevName'),
    t('ProductUnitAbrevNameLang'),
    t('Product'),
    t('Producer'),
    t('Quantity'),
    t('Coop. Price'),
    t('Producer Price'),
    t('Burden'),
  );
  
  $translatables['homecoop_producers_sample'] = array(
    t('Producer ID'),
    t('Producer Name'),
  );
  
  $translatables['homecoop_cooporder_orders'] = array(
    t('OrderMember'),
    t('Name'),
    t('Email address'),
    t('Balance'),
    t('Comments'),
    t('Created On'),
  );
  $translatables['homecoop_cooporders'] = array(
    t('Cooperative Orders'),
    t('CoopOrderName'),
    t('CoopOrderNameLang'),
    t('Opening'),
    t('Closing'),
    t('Coop'),
    t('Producers'),
    t('Full'),
  );
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

function homecoop_cooporders_get_view($view_name, $view_sums) {
  $view = new view();
  $view->name = $view_name;
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_CoopOrder';
  $view->human_name = 'HomeCoop CoopOrders' . ($view_sums? '' : ' (no sums)');
  $view->core = 7;
  $view->api_version = '3.0';

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
  /* Header: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['empty'] = TRUE;
  $handler->display->display_options['header']['php']['php_output'] = '<?php if (!isset($view->args[0]) || $view->args[0] == \'yes\') { ?><div><a href="<?php echo url(\'hccoord/cooporder\'); ?>"><img border="0" title="<?php echo t(\'Add\'); ?>" src="<?php echo homecoop_getthemepath() . \'img/edit-add-2.png\'  ?>" /></a></div><?php } ?>';  
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
  /* Field: Cooperative Order: Coordinating Group */
  $handler->display->display_options['fields']['CoordinatingGroupID']['id'] = 'CoordinatingGroupID';
  $handler->display->display_options['fields']['CoordinatingGroupID']['table'] = 'T_CoopOrder';
  $handler->display->display_options['fields']['CoordinatingGroupID']['field'] = 'CoordinatingGroupID';
  $handler->display->display_options['fields']['CoordinatingGroupID']['label'] = '';
  $handler->display->display_options['fields']['CoordinatingGroupID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['CoordinatingGroupID']['element_label_colon'] = FALSE;
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
  
  if ($view_sums) {
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
  }
  
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['PercentFull']['id'] = 'PercentFull';
  $handler->display->display_options['fields']['PercentFull']['table'] = 'views';
  $handler->display->display_options['fields']['PercentFull']['field'] = 'php';
  $handler->display->display_options['fields']['PercentFull']['label'] = 'Full';
  $handler->display->display_options['fields']['PercentFull']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['PercentFull']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['PercentFull']['php_value'] = ' 
  $oCoopOrderCapacity = new CoopOrderCapacity(
                                $row->fMaxBurden, $row->fBurden,
                                $row->mMaxCoopTotal, $row->mCoopTotal,
                           $row->fMaxStorageBurden, $row->fStorageBurden);
  if ($oCoopOrderCapacity->SelectedType != CoopOrderCapacity::TypeNone) {
                          return $oCoopOrderCapacity->PercentRounded , \'%\';
  }';
  $handler->display->display_options['fields']['PercentFull']['php_output'] = '<?php print $value; ?>';
  $handler->display->display_options['fields']['PercentFull']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['PercentFull']['php_click_sortable'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['CopyLink']['id'] = 'CopyLink';
  $handler->display->display_options['fields']['CopyLink']['table'] = 'views';
  $handler->display->display_options['fields']['CopyLink']['field'] = 'php';
  $handler->display->display_options['fields']['CopyLink']['label'] = '';
  $handler->display->display_options['fields']['CopyLink']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['CopyLink']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['CopyLink']['php_output'] = '<?php if (!isset($view->args[1]) || $view->args[1] == \'yes\') { print \'<a href="\' . url(\'hccoord/coopordercopy\', array(\'query\' => array(\'id\' => $row->CoopOrderKeyID))) . \'" >\' . t(\'Copy\') . \'</a>\'; } ?>';
  $handler->display->display_options['fields']['CopyLink']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['CopyLink']['php_click_sortable'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['CoordLink']['id'] = 'CoordLink';
  $handler->display->display_options['fields']['CoordLink']['table'] = 'views';
  $handler->display->display_options['fields']['CoordLink']['field'] = 'php';
  $handler->display->display_options['fields']['CoordLink']['label'] = '';
  $handler->display->display_options['fields']['CoordLink']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['CoordLink']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['CoordLink']['php_output'] = '<?php 

  if (!isset($view->args[2]) || $view->args[2] == \'yes\') { 
  $arrParams = array(\'pa\' => \''. Consts::PERMISSION_AREA_COOP_ORDERS .'\', \'rid\' => $row->CoopOrderKeyID);
  if (!empty($row->CoordinatingGroupID)) { 
  $arrParams[\'id\'] = $row->CoordinatingGroupID;
  }
  print \'<a href="\' . url(\'hccoord/coordinate\', array(\'query\' => $arrParams)) . \'" >\' . t(\'Coordination\') . \'</a>\'; 
  } ?>';
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
  
  /* Contextual filter: Cooperative Order: Coordinating Group */
  $handler->display->display_options['arguments']['CoordinatingGroupID']['id'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['table'] = 'T_CoopOrder';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['field'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  $handler->display->display_options['arguments']['CoordinatingGroupID']['break_phrase'] = TRUE;
  return $view;
}

function homecoop_cooporder_pickuplocs_get_view($name, $bViewSums) {
  $view = new view();
  $view->name = $name;
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'T_CoopOrderPickupLocation';
  $view->human_name = 'HomeCoop CoopOrder Pickup Locations' . $bViewSums? '' : ' (no sums)';
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
    'CoopOrderKeyID' => 'CoopOrderKeyID',
    'fBurden' => 'fBurden',
    'mCoopTotal' => 'mCoopTotal',
    'fMaxStorageBurden' => 'fMaxStorageBurden',
    'fStorageBurden' => 'fStorageBurden',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'CoopOrderKeyID' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'fBurden' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'fMaxStorageBurden' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'fStorageBurden' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: PHP */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['php_output'] = '<?php if (!isset($view->args[1]) || $view->args[1] == \'rw\') { ?><div><a href="<?php echo url(\'hccoord/copickuploc\', array(\'query\' => array(\'coid\' => $view->args[0]))); ?>"><img border="0" title="<?php echo t(\'Add\'); ?>" src="<?php echo homecoop_getthemepath() . \'img/edit-add-2.png\'  ?>" /></a></div><?php } ?>';
  /* Relationship: Coop Order Pickup Location: Coop Order Pickup Location - Pickup Location */
  $handler->display->display_options['relationships']['PickupLocationKeyID']['id'] = 'PickupLocationKeyID';
  $handler->display->display_options['relationships']['PickupLocationKeyID']['table'] = 'T_CoopOrderPickupLocation';
  $handler->display->display_options['relationships']['PickupLocationKeyID']['field'] = 'PickupLocationKeyID';
  $handler->display->display_options['relationships']['PickupLocationKeyID']['label'] = 'COPickup-Pickup';
  $handler->display->display_options['relationships']['PickupLocationKeyID']['required'] = TRUE;
  /* Relationship: Pickup Location: Pickup Location Address */
  $handler->display->display_options['relationships']['AddressStringKeyID']['id'] = 'AddressStringKeyID';
  $handler->display->display_options['relationships']['AddressStringKeyID']['table'] = 'T_PickupLocation';
  $handler->display->display_options['relationships']['AddressStringKeyID']['field'] = 'AddressStringKeyID';
  $handler->display->display_options['relationships']['AddressStringKeyID']['relationship'] = 'PickupLocationKeyID';
  $handler->display->display_options['relationships']['AddressStringKeyID']['label'] = 'PickupAddress';
  $handler->display->display_options['relationships']['AddressStringKeyID']['required'] = TRUE;
  /* Relationship: Pickup Location: Pickup Location Name */
  $handler->display->display_options['relationships']['PickupLocationKeyID_1']['id'] = 'PickupLocationKeyID_1';
  $handler->display->display_options['relationships']['PickupLocationKeyID_1']['table'] = 'T_PickupLocation';
  $handler->display->display_options['relationships']['PickupLocationKeyID_1']['field'] = 'PickupLocationKeyID';
  $handler->display->display_options['relationships']['PickupLocationKeyID_1']['relationship'] = 'PickupLocationKeyID';
  $handler->display->display_options['relationships']['PickupLocationKeyID_1']['label'] = 'PickupName';
  $handler->display->display_options['relationships']['PickupLocationKeyID_1']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID']['id'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID']['relationship'] = 'PickupLocationKeyID_1';
  $handler->display->display_options['relationships']['LangID']['label'] = 'PickupNameLang';
  $handler->display->display_options['relationships']['LangID']['required'] = TRUE;
  /* Relationship: String: Language */
  $handler->display->display_options['relationships']['LangID_1']['id'] = 'LangID_1';
  $handler->display->display_options['relationships']['LangID_1']['table'] = 'Tlng_String';
  $handler->display->display_options['relationships']['LangID_1']['field'] = 'LangID';
  $handler->display->display_options['relationships']['LangID_1']['relationship'] = 'AddressStringKeyID';
  $handler->display->display_options['relationships']['LangID_1']['label'] = 'PickupAddressLang';
  $handler->display->display_options['relationships']['LangID_1']['required'] = TRUE;
  /* Field: Coop Order Pickup Location: Coop Order ID */
  $handler->display->display_options['fields']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['CoopOrderKeyID']['table'] = 'T_CoopOrderPickupLocation';
  $handler->display->display_options['fields']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['fields']['CoopOrderKeyID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['CoopOrderKeyID']['element_label_colon'] = FALSE;
  /* Field: Coop Order Pickup Location: Pickup Location ID */
  $handler->display->display_options['fields']['PickupLocationKeyID']['id'] = 'PickupLocationKeyID';
  $handler->display->display_options['fields']['PickupLocationKeyID']['table'] = 'T_CoopOrderPickupLocation';
  $handler->display->display_options['fields']['PickupLocationKeyID']['field'] = 'PickupLocationKeyID';
  $handler->display->display_options['fields']['PickupLocationKeyID']['exclude'] = TRUE;
  $handler->display->display_options['fields']['PickupLocationKeyID']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString']['id'] = 'sString';
  $handler->display->display_options['fields']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString']['field'] = 'sString';
  $handler->display->display_options['fields']['sString']['relationship'] = 'PickupLocationKeyID_1';
  $handler->display->display_options['fields']['sString']['label'] = 'Location Name';
  $handler->display->display_options['fields']['sString']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['sString']['alter']['path'] = 'hccoord/copickuploc?coid=[CoopOrderKeyID]&plid=[PickupLocationKeyID]';
  $handler->display->display_options['fields']['sString']['element_label_colon'] = FALSE;
  /* Field: String: String */
  $handler->display->display_options['fields']['sString_1']['id'] = 'sString_1';
  $handler->display->display_options['fields']['sString_1']['table'] = 'Tlng_String';
  $handler->display->display_options['fields']['sString_1']['field'] = 'sString';
  $handler->display->display_options['fields']['sString_1']['relationship'] = 'AddressStringKeyID';
  $handler->display->display_options['fields']['sString_1']['label'] = 'Address';
  $handler->display->display_options['fields']['sString_1']['element_label_colon'] = FALSE;
  /* Field: Coop Order Pickup Location: Total Burden */
  $handler->display->display_options['fields']['fBurden']['id'] = 'fBurden';
  $handler->display->display_options['fields']['fBurden']['table'] = 'T_CoopOrderPickupLocation';
  $handler->display->display_options['fields']['fBurden']['field'] = 'fBurden';
  $handler->display->display_options['fields']['fBurden']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['fBurden']['precision'] = '2';
  /* Field: Coop Order Pickup Location: Total storage full */
  $handler->display->display_options['fields']['fStorageBurden']['id'] = 'fStorageBurden';
  $handler->display->display_options['fields']['fStorageBurden']['table'] = 'T_CoopOrderPickupLocation';
  $handler->display->display_options['fields']['fStorageBurden']['field'] = 'fStorageBurden';
  $handler->display->display_options['fields']['fStorageBurden']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fStorageBurden']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['fStorageBurden']['precision'] = '2';
  /* Field: Coop Order Pickup Location: Total Coop */
  if ($bViewSums) {
    $handler->display->display_options['fields']['mCoopTotal']['id'] = 'mCoopTotal';
    $handler->display->display_options['fields']['mCoopTotal']['table'] = 'T_CoopOrderPickupLocation';
    $handler->display->display_options['fields']['mCoopTotal']['field'] = 'mCoopTotal';
    $handler->display->display_options['fields']['mCoopTotal']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['mCoopTotal']['set_precision'] = TRUE;
    $handler->display->display_options['fields']['mCoopTotal']['precision'] = '2';
  }
  /* Field: Coop Order Pickup Location: Total max. storage */
  $handler->display->display_options['fields']['fMaxStorageBurden']['id'] = 'fMaxStorageBurden';
  $handler->display->display_options['fields']['fMaxStorageBurden']['table'] = 'T_CoopOrderPickupLocation';
  $handler->display->display_options['fields']['fMaxStorageBurden']['field'] = 'fMaxStorageBurden';
  $handler->display->display_options['fields']['fMaxStorageBurden']['label'] = '';
  $handler->display->display_options['fields']['fMaxStorageBurden']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fMaxStorageBurden']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fMaxStorageBurden']['precision'] = '0';
  
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['label'] = '';
  $handler->display->display_options['fields']['php_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_1']['alter']['path'] = 'hccoord/copickuplocproducers?coid=[CoopOrderKeyID]&plid=[PickupLocationKeyID]';
  $handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = '<?php print t(\'Producers\'); ?>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['label'] = '';
  $handler->display->display_options['fields']['php_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_2']['alter']['path'] = 'hccoord/copickuplocproducts?coid=[CoopOrderKeyID]&plid=[PickupLocationKeyID]';
  $handler->display->display_options['fields']['php_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php print t(\'Products\'); ?>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php_3']['id'] = 'php_3';
  $handler->display->display_options['fields']['php_3']['table'] = 'views';
  $handler->display->display_options['fields']['php_3']['field'] = 'php';
  $handler->display->display_options['fields']['php_3']['label'] = '';
  $handler->display->display_options['fields']['php_3']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_3']['alter']['path'] = 'hccoord/copickuplocorders?coid=[CoopOrderKeyID]&plid=[PickupLocationKeyID]';
  $handler->display->display_options['fields']['php_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_3']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_3']['php_output'] = '<?php print t(\'Member Orders\'); ?>';
  $handler->display->display_options['fields']['php_3']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_3']['php_click_sortable'] = '';
  
  /* Sort criterion: String: String */
  $handler->display->display_options['sorts']['sString']['id'] = 'sString';
  $handler->display->display_options['sorts']['sString']['table'] = 'Tlng_String';
  $handler->display->display_options['sorts']['sString']['field'] = 'sString';
  $handler->display->display_options['sorts']['sString']['relationship'] = 'PickupLocationKeyID_1';
  
  
  
  /* Contextual filter: Coop Order Pickup Location: Coop Order ID */
  $handler->display->display_options['arguments']['CoopOrderKeyID']['id'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['table'] = 'T_CoopOrderPickupLocation';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['field'] = 'CoopOrderKeyID';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoopOrderKeyID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['default_argument_options']['argument'] = 'rw';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;
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
  /* Contextual filter: Pickup Location: Coordinating Group ID */
  $handler->display->display_options['arguments']['CoordinatingGroupID']['id'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['table'] = 'T_PickupLocation';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['field'] = 'CoordinatingGroupID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['relationship'] = 'PickupLocationKeyID';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['CoordinatingGroupID']['summary_options']['items_per_page'] = HOMECOOP_RECORDS_PER_PAGE;

  return $view;
}