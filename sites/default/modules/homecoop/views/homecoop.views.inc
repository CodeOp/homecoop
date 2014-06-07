<?php

/*
 * Implements hook_views_data
 */
function homecoop_views_data() {
  $data = array();  
  
  $data['T_CoopOrder'] = 
      array(   
        'table' => array(     
          'base' => array(       
            'field' => 'CoopOrderKeyID',       
            'title' => t('Cooperative Order'),  
            'database' => 'homecoop',
            'help' => t('HomeCoop Cooperative Order'),    
          ),
          'group' => t('Cooperative Order'),
        ),
        'CoopOrderKeyID' => array(     
          'title' => t('Cooperative Order ID'),     
          'help' => t('The primary identifier for an HomeCoop Cooperative Order.'),     
          'field' => array(       
            'handler' => 'views_handler_field_numeric',       
            'click sortable' => FALSE,     
           ),   
        ),   
        'dStart' => array(     
              'title' => t('Opening'),     
              'help' => t('Opening date from which members orders can be added.'),    
              'field' => array(       
                'handler' => 'views_handler_field_date',       
                'click sortable' => TRUE,     
              ),     
              'sort' => array(       
                  'handler' => 'views_handler_sort_date',     
              ),     
              'filter' => array(         
                    'handler' => 'views_handler_filter_date',       
              ),   
         ),   
        'dEnd' => array(     
          'title' => t('Closing'),    
          'help' => t('Closing date until which members orders can be added.'),    
          'field' => array(       
            'handler' => 'views_handler_field_date',       
            'click sortable' => TRUE,     
          ),     
          'sort' => array(       
            'handler' => 'views_handler_sort_date',     
          ),     
          'filter' => array(         
            'handler' => 'views_handler_filter_date',       
          ),   
        ),   
        'dDelivery' => array(     
          'title' => t('Delivery'),     
          'help' => t('Delivery date'),    
          'field' => array(       
            'handler' => 'views_handler_field_date',       
            'click sortable' => TRUE,     
          ),     
          'sort' => array(       
            'handler' => 'views_handler_sort_date',     
          ),     
          'filter' => array(         
            'handler' => 'views_handler_filter_date',       
          ),   
        ),   
        'mCoopFee' => array(     
          'title' => t('Cooperative Fee'),     
          'help' => t('A fixed amount that is paid by each member per order, in addition to the sum cost of the products, to cover expenses'),     
          'field' => array(       
          'handler' => 'views_handler_field_numeric',       
            'click sortable' => FALSE,     
          ),   
        ),   
        'mSmallOrder' => array(     
          'title' => t('Small Order'),   
          'help' => t('Defines a small member\'s order, that has a reduced cooperative fee attached to it'),    
          'field' => array(       
          'handler' => 'views_handler_field_numeric',       
            'click sortable' => FALSE,     
          ),   
        ),   
        'mSmallOrderCoopFee' => array(     
          'title' => t('Small Order Coop Fee'), 
          'help' => t('A reduced cooperative fee, for a small order'),
          'field' => array(       'handler' => 'views_handler_field_numeric',
            'click sortable' => FALSE,
          ),
        ),
        'fCoopFee' => array(     
          'title' => t('% Cooperative Fee'), 
          'help' => t('Defines a cooperative fee by percents from the total amount paid for ordered products'),
          'field' => array(       
            'handler' => 'views_handler_field',
            'click sortable' => FALSE,
          ),
        ),
        'ModifiedByMemberID' => array(     
          'title' => t('Last Updated By'), 
          'help' => t('Modified by (member id)'), 
          'field' => array(       
            'handler' => 'views_handler_field_numeric',
            'click sortable' => FALSE,
          ),
        ),
        'nStatus' => array(     
          'title' => t('Status'), 
          'help' => t('Coop. order status'), 
          'field' => array(       
            'handler' => 'views_handler_field_numeric',
            'click sortable' => FALSE,
          ),
        ),
        'CoordinatingGroupID' => array(     
          'title' => t('Coordinating Group'), 
          'help' => t('Coordinating group that has permissions to manage this coop. order'), 
          'field' => array(       
            'handler' => 'views_handler_field_numeric',
            'click sortable' => FALSE,
          ),
        ),
        'mMaxCoopTotal' => array(     
          'title' => t('Max. Coop Total'), 
          'help' => t('Limits the total amount of the cooperative order. Members will not be able to place an order that exceeds the limitation set here.'),
          'field' => array(       
            'handler' => 'views_handler_field_numeric',
            'click sortable' => FALSE,
          ),
        ),
        'fMaxBurden' => array(     
          'title' => t('Delivery Capacity'), 
          'help' => t('Limits the size of this cooperative order to the overall order\'s capacity, 
            comapring it to the sum of the "burden" field of each product multiplied by the quantity ordered. 
            A limitation can also be set for a specific pickup location. 
            Members will not be able to place an order that exceeds the limitation set here.'),
          'field' => array(       
            'handler' => 'views_handler_field',
            'click sortable' => FALSE,
          ),
        ),
        'fBurden' => array(     
          'title' => t('Total Burden'),
          'help' => t('The sum total of each ordered product "Burden" multiplied by the times it was ordered (calculated)'),
          'field' => array(       
            'handler' => 'views_handler_field',
            'click sortable' => FALSE,
          ),
        ),
        'mCoopTotal' => array(     
          'title' => t('Total Coop'),
          'help' => t('Total amount of the cooperative order (calculated)'),
          'field' => array(       
            'handler' => 'views_handler_field_numeric',
            'click sortable' => FALSE,
          ),
        ),
        'mProducerTotal' => array(     
          'title' => t('Total Producers'),
          'help' => t('Total amount for the producers (calculated)'),
          'field' => array(       
            'handler' => 'views_handler_field_numeric',
            'click sortable' => FALSE,
          ),
        ),
        'mTotalDelivery' => array(     
          'title' => t('Total Delivery'),
          'help' => t('Total amount for delivery (calculated)'),
          'field' => array(       
            'handler' => 'views_handler_field_numeric',
            'click sortable' => FALSE,
          ),
        ),
        'bHasJoinedProducts' => array(     
          'title' => t('Has Joined Products'),
          'help' => t('Internal field: whether products were "joined" by the join operation'),
          'field' => array(   
            'handler' => 'views_handler_field_numeric',
            'click sortable' => FALSE,
          ),
        ),
        'fMaxStorageBurden' => array(     
          'title' => t('Total max. storage'),
          'help' => t('Total maximum storage areas capacity (calculated)'),
          'field' => array(       
            'handler' => 'views_handler_field',
            'click sortable' => FALSE,
          ),
        ),
        'fStorageBurden' => array(     
          'title' => t('Total storage full'),
          'help' => t('Total storage areas used space - percentage (calculated).'),
          'field' => array(       
            'handler' => 'views_handler_field',
            'click sortable' => FALSE,
          ),
        ),
    );

     $data['T_CoopOrderPickupLocation'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'CoopOrderKeyID',
          'title' => t('Coop Order Pickup Location'),
          'database' => 'homecoop',
          'help' => t('Coop Order Pickup Location'),
        ),
       'group' => t('Coop Order Pickup Location'),
      ),
      'CoopOrderKeyID' => array(     
        'title' => t('Coop Order ID'),
        'help' => t('Cooperative order id'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'PickupLocationKeyID' => array(     
        'title' => t('Pickup Location ID'),
        'help' => t('Pickup location id'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'fMaxBurden' => array(     
        'title' => t('Delivery Capacity'), 
        'help' => t('Limits the size of this cooperative order\'s pickup location to the overall capacity, 
          comapring it to the sum of the "burden" field of each product multiplied by the quantity ordered. 
          Members will not be able to place an order that exceeds the limitation set here.'),
          'field' => array(       
            'handler' => 'views_handler_field',
            'click sortable' => FALSE,
          ),
      ),
      'fBurden' => array(     
        'title' => t('Total Burden'),
        'help' => t('The sum total of each ordered product "Burden" multiplied by the times it was ordered, per pickup location'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
      'mMaxCoopTotal' => array(     
        'title' => t('Max. Coop Total'),
        'help' => t('Max. coop total for this pickup location'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'mCoopTotal' => array(     
        'title' => t('Total Coop'),
        'help' => t('Total coop amount for this pickup location (calculated)'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'fMaxStorageBurden' => array(     
        'title' => t('Total max. storage'),
        'help' => t('Total maximum storage areas capacity. (calculated)'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
      'fStorageBurden' => array(     
        'title' => t('Total storage full'),
        'help' => t('Total storage areas used space. (calculated)'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
    );

     $data['T_CoopOrderPickupLocationProducer'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'CoopOrderKeyID',
          'title' => t('Coop Order Pickup Location Producer'),
          'database' => 'homecoop',
          'help' => t('Coop Order Pickup Location Producer - a table that helps in calculations'),
        ),
        'group' => t('Coop Order Pickup Location Producer'),
      ),

      'CoopOrderKeyID' => array(     
        'title' => t('Coop Order ID'),
        'help' => t('Coop Order ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'ProducerKeyID' => array(     
        'title' => t('Producer ID'),
        'help' => t('Producer ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'PickupLocationKeyID' => array(     
        'title' => t('Pickup Location ID'),
        'help' => t('Pickup Location ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mProducerTotal' => array(     
        'title' => t('Total Producers (calculated)'),
        'help' => t('Total Producers (calculated)'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mCoopTotal' => array(     
        'title' => t('Total Coop (calculated)'),
        'help' => t('Total Coop (calculated)'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

     $data['T_CoopOrderPickupLocationProduct'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'CoopOrderKeyID',
          'title' => t('Coop Order Pickup Location Product'),
          'database' => 'homecoop',
          'help' => t('Coop Order Pickup Location Product - for calculations'),
        ),
        'group' => t('Coop Order Pickup Location Product'),
      ),
      'CoopOrderKeyID' => array(     
        'title' => t('Coop Order ID'),
        'help' => t('Coop Order ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'ProductKeyID' => array(     
        'title' => t('Product ID'),
        'help' => t('Product ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'PickupLocationKeyID' => array(     
        'title' => t('Pickup Location ID'),
        'help' => t('Pickup Location ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'mProducerTotal' => array(     
        'title' => t('Total Producers'),
        'help' => t('Total Producers'),
        'field' => array(     
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'mCoopTotal' => array(     
        'title' => t('Total Coop'),
        'help' => t('Total Coop'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'fTotalCoopOrder' => array(     
        'title' => t('Total Quantity Ordered'),
        'help' => t('Ordered product quantity'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_CoopOrderProducer'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'CoopOrderKeyID',
          'title' => t('Coop Order Producer'),
          'database' => 'homecoop',
          'help' => t('Coop Order Producer'),
        ),
        'group' => t('Coop Order Producer'),
      ),
      'CoopOrderKeyID' => array(     
        'title' => t('Coop Order ID'),
        'help' => t('Coop Order ID'),
        'field' => array(     
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'ProducerKeyID' => array(     
        'title' => t('Producer ID'),
        'help' => t('Producer ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'mMaxProducerOrder' => array(     
        'title' => t('Max. Producer Order'),
        'help' => t('Max. Producer Order'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'mProducerTotal' => array(     
        'title' => t('Producer Total'),
        'help' => t('Producer Total (calculated)'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'fDelivery' => array(     
        'title' => t('% Delivery Fee'),
        'help' => t('% Delivery Fee'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
      'mDelivery' => array(     
        'title' => t('Fixed Delivery Fee'),
        'help' => t('Fixed Delivery Fee'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'mMinDelivery' => array(     
        'title' => t('Min. Delivery Fee'),
        'help' => t('Min. Delivery Fee'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'mMaxDelivery' => array(     
        'title' => t('Max. Delivery Fee'),
        'help' => t('Max. Delivery Fee'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'mTotalDelivery' => array(     
        'title' => t('Total Delivery'),
        'help' => t('Total Delivery'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'fBurden' => array(     
        'title' => t('Total Burden'),
        'help' => t('Total Burden'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
      'fMaxBurden' => array(     
        'title' => t('Delivery Capacity'),
        'help' => t('Limits the size of this cooperative order\'s producer to the overall capacity, 
          comapring it to the sum of the "burden" field of each product multiplied by the quantity ordered. 
          Members will not be able to place an order that exceeds the limitation set here.'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
      'mCoopTotal' => array(     
        'title' => t('Total Coop'),
        'help' => t('Total Coop'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

     $data['T_CoopOrderProduct'] = array(   
      'table' => array(     
        'base' => array(       
        'field' => 'CoopOrderKeyID',
          'title' => t('Coop Order Product'),
          'database' => 'homecoop',
          'help' => t('Coop Order Product'),
        ),
        'group' => t('Coop Order Product'),
      ),

      'CoopOrderKeyID' => array(     
        'title' => t('Coop Order ID'),
        'help' => t('Coop Order ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'ProductKeyID' => array(     
        'title' => t('Product ID'),
        'help' => t('Product ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mProducerPrice' => array(     
        'title' => t('Producer Price'),
        'help' => t('Producer Price'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mCoopPrice' => array(     
        'title' => t('Coop. Price'),
        'help' => t('Coop. Price'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'fMaxUserOrder' => array(     
        'title' => t('Max. Member Order'),
        'help' => t('Max. product quantity per member'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'fMaxCoopOrder' => array(     
        'title' => t('Max. Coop Order'),
        'help' => t('Max. product quantity for the entire coop order'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'fBurden' => array(     
        'title' => t('Burden'),
        'help' => t('Burden'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'fTotalCoopOrder' => array(     
        'title' => t('Total Quantity Ordered'),
        'help' => t('Ordered product quantity'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'nJoinedStatus' => array(     
        'title' => t('Joined Status'),
        'help' => t('Joined Status (internal)'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mProducerTotal' => array(     
        'title' => t('Producer Total'),
        'help' => t('Producer Total (calculated)'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mCoopTotal' => array(     
        'title' => t('Total Coop'),
        'help' => t('Total Coop (calculated)'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'bDisabled' => array(     
        'title' => t('Status'),
        'help' => t('Is Disabled?'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

     $data['T_CoopOrderProductStorage'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'CoopOrderKeyID',
          'title' => t('Coop Order Product Storage'),
          'database' => 'homecoop',
          'help' => t('Coop Order Product Storage'),
        ),
        'group' => t('Coop Order Product Storage'),
      ),
      'CoopOrderKeyID' => array(     
        'title' => t('Coop Order ID'),
        'help' => t('Coop Order ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'ProductKeyID' => array(     
        'title' => t('Product ID'),
        'help' => t('Product ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'PickupLocationKeyID' => array(     
        'title' => t('Pickup Location ID'),
        'help' => t('Pickup Location ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'StorageAreaKeyID' => array(     
        'title' => t('Storage Area ID'),
        'help' => t('Storage Area ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_CoopOrderStorageArea'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'CoopOrderKeyID',
          'title' => t('Coop Order Storage Area'),
          'database' => 'homecoop',
          'help' => t('Coop Order Storage Area'),
        ),
        'group' => t('Coop Order Storage Area'),
      ),
      'CoopOrderKeyID' => array(     
        'title' => t('Coop Order ID'),
        'help' => t('Coop Order ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'StorageAreaKeyID' => array(     
        'title' => t('Storage Area ID'),
        'help' => t('Storage Area ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'fMaxBurden' => array(     
        'title' => t('Max. storage'),
        'help' => t('Limits the size of this cooperative order\'s pickup location to the overall capacity, 
          comapring it to the sum of the "burden" field of each product multiplied by the quantity ordered. 
          Members will not be able to place an order that exceeds the limitation set here.'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
      'fBurden' => array(     
        'title' => t('Total Burden'),
        'help' => t('The sum total of each ordered product "Burden" multiplied by the times it was ordered'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_CoordinatingGroup'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'CoordinatingGroupID',
          'title' => t('Coordinating Group'),
          'database' => 'homecoop',
          'help' => t('Access group that sets permissions on specific records'),
        ),
        'group' => t('Coordinating Group'),
      ),
      'CoordinatingGroupID' => array(     
        'title' => t('Coordinating Group ID'),
        'help' => t('Coordinating Group ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'sCoordinatingGroup' => array(     
        'title' => t('Coordinating Group'),
        'help' => t('Coordinating group name'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
    );

    $data['T_CoordinatingGroupMember'] = array(   
      'table' => array(     
        'base' => array(       
        'field' => 'CoordinatingGroupID',
        'title' => t('Coordinating Group Member'),
        'database' => 'homecoop',
        'help' => t('Defines membership in a coordinating (access) group, for permissions to specific records'),
       ),
       'group' => t('Coordinating Group Member'),
      ),

      'CoordinatingGroupID' => array(     
        'title' => t('Coordinating Group ID'),
        'help' => t('Coordinating Group ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'MemberID' => array(     
        'title' => t('Member ID'),
        'help' => t('Member ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'bContactPerson' => array(     
        'title' => t('Is Contact Person?'),
        'help' => t('Is a contact person in this group?'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_Key'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'KeyID',
          'title' => t('Key'),
          'database' => 'homecoop',
          'help' => t('Holds cross-language keys for translated strings'),
        ),
        'group' => 'T Key',
      ),
      
      'KeyID' => array(     
        'title' => t('Key ID'),
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'sStringKey' => array(     
        'title' => t('Key Name'),
        'help' => t('Name of the key, for built-in constants'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_Measure'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'MeasureKeyID',
          'title' => t('Measure'),
          'database' => 'homecoop',
          'help' => t('Measure'),
        ),
      'group' => t('Measure'),
      ),
      'MeasureKeyID' => array(     
        'title' => t('Measure ID'),
        'help' => t('Measure ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_Member'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'MemberID',
          'title' => t('Member'),
          'database' => 'homecoop',
          'help' => t('HomeCoop Members'),
        ),
        'group' => t('Member'),
      ),
      'MemberID' => array(     
         'title' => t('Member ID'),
         'help' => t('Member ID'),
         'field' => array(       
           'handler' => 'views_handler_field_numeric',
           'click sortable' => FALSE,
         ),
         'argument' => array(
           'handler' => 'views_handler_argument_numeric',
           'name field' => 'sName',
           'numeric' => TRUE,
           'validate type' => 'MemberID',
         ),
        ),
      'sLoginName' => array(     
        'title' => t('Login name'),
        'help' => t('Login name'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
      'sPassword' => array(     
        'title' => t('Password'),
        'help' => t('Password'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'sEMail' => array(     
        'title' => t('Email address'),
        'help' => t('Email address'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
      
      'PaymentMethodKeyID' => array(     
        'title' => t('Payment Method ID'),
        'help' => t('Payment Method ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      
      'dJoined' => array(     
        'title' => t('Joined On'),
        'help' => t('Joined On'),
        'field' => array(       
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        'sort' => array(       
          'handler' => 'views_handler_sort_date',
        ),
        'filter' => array(         
          'handler' => 'views_handler_filter_date',
        ),
      ),
      
      'mBalance' => array(     
        'title' => t('Balance'),
        'help' => t('Effective balance for orders limits'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'sName' => array(     
        'title' => t('Name'),
        'help' => t('Name'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'fPercentOverBalance' => array(     
        'title' => t('% Over Balance'),
        'help' => t('The percentage in which a member\'s order can exceed hir balance. 
          This rule is being applied only when the member\'s payment method allows a percentage over balance.'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'sEMail2' => array(     
        'title' => t('Email address 2'),
        'help' => t('Email address 2'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'sEMail3' => array(     
        'title' => t('Email address 3'),
        'help' => t('Email address 3'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'sEMail4' => array(     
        'title' => t('Email address 4'),
        'help' => t('Email address 4'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
      
      'bDisabled' => array(     
        'title' => t('Status'),
        'help' => t('Is disabled?'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'sComments' => array(     
        'title' => t('Comments'),
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'mBalanceInvested' => array(     
        'title' => t('Balance Invested'),
        'help' => t('Describes a sum of balance that cannot be withdrawn. Descriptive field only'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mBalanceHeld' => array(     
        'title' => t('Balance Held'),
        'help' => t('Actual balance deposited'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'nExportFormat' => array(     
        'title' => t('Export Format'),
        'help' => t('Export Format - to save as default'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'sPasswordForMigration' => array(     
        'title' => t('Password For Migration'),
        'help' => t('Clear password for migration'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
    );

    $data['T_MemberPickupLocation'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'MemberID',
          'title' => t('Member Pickup Location'),
          'database' => 'homecoop',
          'help' => t('Member Pickup Location - for blocking members and facet search'),
        ),
        'group' => t('Member Pickup Location'),
      ),
      'MemberID' => array(     
        'title' => t('Member ID'),
        'help' => t('Member ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'PickupLocationKeyID' => array(     
        'title' => t('Pickup Location ID'),
        'help' => t('Pickup Location ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'bBlocked' => array(     
        'title' => t('Blocked'),
        'help' => t('Member is blocked from ordering from this pickup location'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'bRemoved' => array(     
        'title' => t('Removed'),
        'help' => t('Member has filtered out this pickup location in the main facet search'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_MemberProducer'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'MemberID',
          'title' => t('Member Producer'),
          'database' => 'homecoop',
          'help' => t('Member Producer - for blocking members and facet search'),
        ),
        'group' => t('Member Producer'),
      ),
      'MemberID' => array(     
        'title' => t('Member ID'),
        'help' => t('Member ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'ProducerKeyID' => array(     
        'title' => t('Producer ID'),
        'help' => t('Producer ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'bBlocked' => array(     
        'title' => t('Blocked'),
        'help' => t('Member is blocked from ordering from this producer'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'bRemoved' => array(     
        'title' => t('Removed'),
        'help' => t('Member has filtered out this producer in the main facet search'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_MemberRole'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'MemberID',
          'title' => t('Member Role'),
          'database' => 'homecoop',
          'help' => t('Provides permissions to members through roles (permission sets)'),
        ),
        'group' => t('Member Role'),
      ),
      'MemberID' => array(     
        'title' => t('Member ID'),
        'help' => t('Member ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'RoleKeyID' => array(     
        'title' => t('Role ID'),
        'help' => t('Role ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_Order'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'OrderID',
          'title' => t('Order'),
          'database' => 'homecoop',
          'help' => t('Member\'s order header'),
        ),
        'group' => t('Order'),
      ),
      'OrderID' => array(     
        'title' => t('Order ID'),
        'help' => t('Order ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'CoopOrderKeyID' => array(     
        'title' => t('Coop Order ID'),
        'help' => t('Coop Order ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'MemberID' => array(     
         'title' => t('Member ID'),
         'help' => t('Member ID'),
         'field' => array(       
           'handler' => 'views_handler_field_numeric',
           'click sortable' => FALSE,
         ),
         'relationship' => array(
             'title' => t('Member'),
             'lable' => t('Member'),
             'base' => 'T_Member',
             'base field' => 'MemberID',
         ),
         'argument' => array(
           'handler' => 'views_handler_argument_many_to_one',
           'numeric' => TRUE,
         ),
       ),

      'PickupLocationKeyID' => array(     
        'title' => t('Pickup Location ID'),
        'help' => t('Pickup Location ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'dCreated' => array(     
        'title' => t('Created On'),
        'help' => t('Created On'),
        'field' => array(       
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        'sort' => array(       
           'handler' => 'views_handler_sort_date',
        ),
        'filter' => array(         
          'handler' => 'views_handler_filter_date',
        ),
      ),

      'dModified' => array(     
        'title' => t('Last Updated On'),
        'help' => t('Last Updated On'),
        'field' => array(       
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        'sort' => array(       
           'handler' => 'views_handler_sort_date',
        ),
        'filter' => array(         
          'handler' => 'views_handler_filter_date',
        ),
      ),

      'mCoopTotal' => array(     
        'title' => t('Coop Total'),
        'help' => t('Total amount for the coop, excluding fee'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'CreatedByMemberID' => array(     
        'title' => t('Created By'),
        'help' => t('member id'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'ModifiedByMemberID' => array(     
        'title' => t('Last Updated By'),
        'help' => t('member id'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mProducerTotal' => array(     
        'title' => t('Producer Total'),
        'help' => t('for calculations'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'sMemberComments' => array(     
        'title' => t('Comments'),
        'help' => t('Member comments'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'mCoopFee' => array(     
        'title' => t('Coop Fee'),
        'help' => t('calculated'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'bHasItemComments' => array(     
        'title' => t('Has Item Comments'),
        'help' => t('internal'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'fBurden' => array(     
        'title' => t('Burden'),
        'help' => t('calculated'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'mCoopTotalIncFee' => array(     
        'title' => t('Total Amount'),
        'help' => t('Total amount for the coop, including fee'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'PaymentMethodKeyID' => array(     
        'title' => t('Payment Method ID'),
        'help' => t('Payment Method ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'fPercentOverBalance' => array(     
        'title' => t('% Over Balance'),
        'help' => ('The percentage in which a member\'s order can exceed hir balance. This rule is being applied only when the member\'s payment method allows a percentage over balance.'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_OrderItem'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'OrderItemID',
          'title' => t('Order Item'),
          'database' => 'homecoop',
          'help' => t('Order Item'),
        ),
        'group' => t('Order Item'),
      ),

      'OrderItemID' => array(     
        'title' => t('Order Item ID'),
        'help' => t('Order Item ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'OrderID' => array(     
        'title' => t('Order ID'),
        'help' => t('Order ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'ProductKeyID' => array(     
        'title' => t('Product ID'),
        'help' => t('Product ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'fQuantity' => array(     
        'title' => t('Order'),
        'help' => t('Product quantity'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'mCoopPrice' => array(     
        'title' => t('Price'),
        'help' => t('Coop Price'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mProducerPrice' => array(     
        'title' => t('Producer Price'),
        'help' => t('Producer Price'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'fOriginalQuantity' => array(     
        'title' => t('Original Quantity'),
        'help' => t('Original Quantity'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'fMaxFixQuantityAddition' => array(     
        'title' => t('Add'),
        'help' => t('The maximum quantity the cooperative order coordinator will be allowed to *add* to your order for completing partial orders to the package size. For instance, if a package size is 2lb, and you wish to order only 0.5lb, by entering 0.5lb in this field you may specify that you are ready to go up to 1lb.'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'sMemberComments' => array(     
        'title' => t('Comments'),
        'help' => t('Member Comments'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'fUnjoinedQuantity' => array(     
        'title' => t('Unjoined Quantity'),
        'help' => t('internal'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'nJoinedItems' => array(     
        'title' => t('Joined Items'),
        'help' => t('internal'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_OrderItem_Deleted'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'OrderItemID',
          'title' => t('Deleted Order Item'),
          'database' => 'homecoop',
          'help' => t('Deleted Order Item'),
         ),
        'group' => t('Deleted Order Item'),
      ),
      
      'OrderItemID' => array(     
        'title' => t('Order Item ID'),
        'help' => t('Order Item ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'OrderID' => array(     
        'title' => t('Order ID'),
        'help' => t('Order ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'ProductKeyID' => array(     
        'title' => t('Product ID'),
        'help' => t('Product ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'fQuantity' => array(     
        'title' => t('Order'),
        'help' => t('Product quantity'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'mCoopPrice' => array(     
        'title' => t('Price'),
        'help' => t('Coop Price'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mProducerPrice' => array(     
        'title' => t('Producer Price'),
        'help' => t('Producer Price'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'fOriginalQuantity' => array(     
        'title' => t('Original Quantity'),
        'help' => t('Original Quantity'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'fMaxFixQuantityAddition' => array(     
        'title' => t('Add'),
        'help' => t('The maximum quantity the cooperative order coordinator will be allowed to *add* to your order for completing partial orders to the package size. For instance, if a package size is 2lb, and you wish to order only 0.5lb, by entering 0.5lb in this field you may specify that you are ready to go up to 1lb.'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'sMemberComments' => array(     
        'title' => t('Comments'),
        'help' => t('Member Comments'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'fUnjoinedQuantity' => array(     
        'title' => t('Unjoined Quantity'),
        'help' => t('internal'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'nJoinedItems' => array(     
        'title' => t('Joined Items'),
        'help' => t('internal'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'DeletedBy' => array(     
        'title' => t('Deleted By'),
        'help' => t('member id'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_PaymentMethod'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'PaymentMethodKeyID',
          'title' => t('Payment Method'),
          'database' => 'homecoop',
          'help' => t('Payment Method'),
        ),
        'group' => t('Payment Method'),
      ),

      'PaymentMethodKeyID' => array(     
        'title' => t('Payment Method ID'),
        'help' => t('Payment Method ID'),
        'field' => array(       'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_Permission'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'PermissionAreaKeyID',
          'title' => t('Permission'),
          'help' => t('Permissions defined by the system'),
        ),
       'group' => t('Permission'),
      ),

      'PermissionAreaKeyID' => array(     
        'title' => t('Permission Area ID'),
        'help' => t('Entity/relationship this permission is ascribed to'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'PermissionTypeKeyID' => array(     
        'title' => t('Permission Type ID'),
        'help' => t('Type of operation this permission is ascribed to'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'nAllowedScopeCodes' => array(     
        'title' => t('Allowed Scope Codes'),
        'help' => t('Record access bitwise flags'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_PermissionArea'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'PermissionAreaKeyID',
          'title' => t('Permission Area'),
          'database' => 'homecoop',
          'help' => t('Permission Area'),
        ),
        'group' => t('Permission Area'),
      ),
      'PermissionAreaKeyID' => array(     
        'title' => t('Permission Area ID'),
        'help' => t('Permission Area ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_PermissionScope'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'PermissionScopeKeyID',
          'title' => t('Permission Scope'),
          'database' => 'homecoop',
          'help' => t('Permission Scope'),
        ),
        'group' => t('Permission Scope'),
      ),
      'PermissionScopeKeyID' => array(     
        'title' => t('Permission Scope ID'),
        'help' => t('Permission Scope ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'nScopeCode' => array(     
        'title' => t('Scope Code'),
        'help' => t('Bitwise flag'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_PermissionType'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'PermissionTypeKeyID',
          'title' => t('Permission Type'),
          'database' => 'homecoop',
          'help' => t('Permission Type'),
        ),
        'group' => t('Permission Type'),
      ),

      'PermissionTypeKeyID' => array(     
        'title' => t('Permission Type ID'),
        'help' => t('Permission Type ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_PickupLocation'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'PickupLocationKeyID',
          'title' => t('Pickup Location'),
          'database' => 'homecoop',
          'help' => t('Pickup Location'),
        ),
        'group' => t('Pickup Location'),
      ),

      'PickupLocationKeyID' => array(     
        'title' => t('Pickup Location ID'),
        'help' => t('Pickup Location ID'),
        'field' => array(       'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'AddressStringKeyID' => array(     
        'title' => t('Address String ID'),
        'help' => t('multilingual field'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'PublishedCommentsStringKeyID' => array(     
        'title' => t('Published Comments String ID'),
        'help' => t('multilingual field'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'AdminCommentsStringKeyID' => array(     
        'title' => t('Admin Comments String ID'),
        'help' => t('multilingual field'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'bDisabled' => array(     
        'title' => t('Disabled'),
        'help' => t('Disabled'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'CoordinatingGroupID' => array(     
        'title' => t('Coordinating Group ID'),
        'help' => t('Coordinating Group ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'fMaxBurden' => array(     
        'title' => t('Delivery Capacity'),
        'help' => t('The maximum capacity of the pickup location in terms of the product field "Burden". 
          the sum for all products of "Burden" times product quantity will be compared to this value for all the members\' orders 
          that have this pickup location selected. 
          This is only a default value and can be overwritten in the cooperative order\'s pickup location settings. 
          If not overridden in the coop order, members will not be able to place an order that exceeds the limitation set here.'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'nRotationOrder' => array(     
        'title' => t('Rotation Order'),
        'help' => t('Rotation Order'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'sExportFileName' => array(     
        'title' => t('Export File Name'),
        'help' => t('Export File Name'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'mCachier' => array(     
        'title' => t('Cachier'),
        'help' => t('Cachier total'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mPrevCachier' => array(     
        'title' => t('Prev. Cachier'),
        'help' => t('Prev. cachier amount'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'dCachierUpdate' => array(     
        'title' => t('Cachier Update'),
        'help' => t('Cachier Update'),
        'field' => array(       
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        'sort' => array(       
           'handler' => 'views_handler_sort_date',
        ),
        'filter' => array(         
          'handler' => 'views_handler_filter_date',
        ),
      ),
    ); 

    $data['T_PickupLocationStorageArea'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'StorageAreaKeyID',
          'title' => t('Pickup Location Storage Area'),
          'database' => 'homecoop',
          'help' => t('Pickup Location Storage Area'),
        ),
        'group' => t('Pickup Location Storage Area'),
      ),
      'PickupLocationKeyID' => array(     
        'title' => t('Pickup Location ID'),
        'help' => t('Pickup Location ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
      'StorageAreaKeyID' => array(     
        'title' => t('Storage Area ID'),
        'help' => t('Storage Area ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'fMaxBurden' => array(     
        'title' => t('Max Burden'),
        'help' => t('Max Burden'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'bDisabled' => array(     
        'title' => t('Disabled'),
        'help' => t('Disabled'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'bDefault' => array(     
        'title' => t('Default'),
        'help' => t('Default'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_Producer'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'ProducerKeyID',
          'title' => t('Producer'),
          'database' => 'homecoop',
          'help' => t('Producer'),
        ),
        'group' => t('Producer'),
      ),

      'ProducerKeyID' => array(     
        'title' => t('Producer ID'),
        'help' => t('Producer ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'bDisabled' => array(     
        'title' => t('Disabled'),
        'help' => t('Disabled'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'CoordinatingGroupID' => array(     
        'title' => t('Coordinating Group ID'),
        'help' => t('Coordinating Group ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'sExportFileName' => array(     
        'title' => t('Export File Name'),
        'help' => t('Export File Name'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_Product'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'ProductKeyID',
          'title' => t('Product'),
          'database' => 'homecoop',
          'help' => t('Product'),
        ),
        'group' => t('Product'),
      ),
      'ProductKeyID' => array(     
        'title' => t('Product ID'),
        'help' => t('Product ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'ProducerKeyID' => array(     
        'title' => t('Producer ID'),
        'help' => t('Producer ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'SpecStringKeyID' => array(     
        'title' => t('Details String ID'),
        'help' => t('multilingual field'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'UnitKeyID' => array(     
        'title' => t('Unit ID'),
        'help' => t('Unit ID'),
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'fQuantity' => array(     
        'title' => t('Quantity'),
        'help' => t('Quantity'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'fPackageSize' => array(     
        'title' => t('Package Size'),
        'help' => t('Package size for a large package that the cooperative allows ordering portions/slices of.'),
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'fUnitInterval' => array(     
        'title' => 'FUnitInterval',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'fMaxUserOrder' => array(     
        'title' => 'FMaxUserOrder',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'bDisabled' => array(     
        'title' => 'BDisabled',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mProducerPrice' => array(     
        'title' => 'MProducerPrice',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mCoopPrice' => array(     
        'title' => 'MCoopPrice',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'fBurden' => array(     
        'title' => 'FBurden',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'sImage1FileName' => array(     
        'title' => 'SImage1FileName',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'nItems' => array(     
        'title' => 'NItems',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'ItemUnitKeyID' => array(     
        'title' => 'ItemUnitKeyID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'fItemQuantity' => array(     
        'title' => 'FItemQuantity',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'nSortOrder' => array(     
        'title' => 'NSortOrder',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'JoinToProductKeyID' => array(     
        'title' => 'JoinToProductKeyID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'sImage2FileName' => array(     
        'title' => 'SImage2FileName',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_Role'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'RoleKeyID',
          'title' => 'T Role',
          'database' => 'homecoop',
          'help' => 'TODO: please describe the items in this table!',
        ),
        'group' => 'T Role',
      ),

     'RoleKeyID' => array(     
       'title' => 'RoleKeyID',
       'help' => 'TODO: please describe this field!',
       'field' => array(       
         'handler' => 'views_handler_field_numeric',
         'click sortable' => FALSE,
        ),
      ),
    ); 

     $data['T_RolePermission'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'RoleKeyID',
          'title' => 'T RolePermission',
          'database' => 'homecoop',
          'help' => 'TODO: please describe the items in this table!',
        ),
        'group' => 'T RolePermission',
      ),

      'RoleKeyID' => array(     
        'title' => 'RoleKeyID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'PermissionAreaKeyID' => array(     
        'title' => 'PermissionAreaKeyID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'PermissionTypeKeyID' => array(     
        'title' => 'PermissionTypeKeyID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'PermissionScopeKeyID' => array(     
        'title' => 'PermissionScopeKeyID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_Transaction'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'TransactionID',
          'title' => 'T Transaction',
          'database' => 'homecoop',
          'help' => 'TODO: please describe the items in this table!',
        ),
        'group' => 'T Transaction',
      ),

      'TransactionID' => array(     
        'title' => 'TransactionID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'PickupLocationKeyID' => array(     
        'title' => 'PickupLocationKeyID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'MemberID' => array(     
        'title' => 'MemberID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'ModifiedByMemberID' => array(     
        'title' => 'ModifiedByMemberID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'mAmount' => array(     
        'title' => 'MAmount',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'dDate' => array(     
        'title' => 'DDate',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        'sort' => array(       
           'handler' => 'views_handler_sort_date',
        ),
        'filter' => array(         
          'handler' => 'views_handler_filter_date',
        ),
      ),

      'sTransaction' => array(     
        'title' => 'STransaction',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['T_Unit'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'UnitKeyID',
          'title' => 'T Unit',
          'database' => 'homecoop',
          'help' => 'TODO: please describe the items in this table!',
        ),
        'group' => 'T Unit',
      ),

      'UnitKeyID' => array(     
        'title' => 'UnitKeyID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'MeasureKeyID' => array(     
        'title' => 'MeasureKeyID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'nFloatingPoint' => array(     
        'title' => 'NFloatingPoint',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'UnitAbbreviationStringKeyID' => array(     
        'title' => 'UnitAbbreviationStringKeyID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['Tlng_Language'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'LangID',
          'title' => 'Tlng Language',
          'database' => 'homecoop',
          'help' => 'TODO: please describe the items in this table!',
        ),
        'group' => 'Tlng Language',
      ),
      'LangID' => array(     
        'title' => 'LangID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'sLanguage' => array(     
        'title' => 'SLanguage',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),

      'bActive' => array(     
        'title' => 'BActive',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'bRequired' => array(     
        'title' => 'BRequired',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'FallingLangID' => array(     
        'title' => 'FallingLangID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'sPhpFolder' => array(     
        'title' => 'SPhpFolder',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
    ); 

    $data['Tlng_String'] = array(   
      'table' => array(     
        'base' => array(       
          'field' => 'KeyID',
          'title' => 'Tlng String',
          'database' => 'homecoop',
          'help' => 'TODO: please describe the items in this table!',
        ),
        'group' => 'Tlng String',
      ),

      'KeyID' => array(     
        'title' => 'KeyID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'LangID' => array(     
        'title' => 'LangID',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field_numeric',
          'click sortable' => FALSE,
        ),
      ),

      'sString' => array(     
        'title' => 'SString',
        'help' => 'TODO: please describe this field!',
        'field' => array(       
          'handler' => 'views_handler_field',
          'click sortable' => FALSE,
        ),
      ),
    ); 
  
  return $data;
}