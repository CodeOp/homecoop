<?php

/*
 * Implements hook_views_data
 */
function homecoop_views_data() {
  $data = array();
  $data['T_CoopOrder'] = 
      array(   'table' => array(     
        'base' => array(       
          'field' => 'CoopOrderKeyID',       
          'title' => 'T CoopOrder',  
          'database' => 'homecoop',
          'help' => 'TODO: please describe the items in this table!',     
        ),     'group' => 'T CoopOrder',   ),   
        'CoopOrderKeyID' => array(     
          'title' => 'CoopOrderKeyID',     
          'help' => 'TODO: please describe this field!',     
          'field' => array(       
            'handler' => 'views_handler_field_numeric',       
            'click sortable' => FALSE,     ),   ),   'dStart' => array(     
              'title' => 'DStart',     'help' => 'TODO: please describe this field!',     
              'field' => array(       'handler' => 'views_handler_field_date',       
                'click sortable' => TRUE,     ),     'sort' => array(       
                  'handler' => 'views_handler_sort_date',     ),     'filter' => array(         
                    'handler' => 'views_handler_filter_date',       ),   ),   
        'dEnd' => array(     'title' => 'DEnd',     'help' => 'TODO: please describe this field!',     'field' => array(       'handler' => 'views_handler_field_date',       'click sortable' => TRUE,     ),     'sort' => array(       'handler' => 'views_handler_sort_date',     ),     'filter' => array(         'handler' => 'views_handler_filter_date',       ),   ),   
        'dDelivery' => array(     'title' => 'DDelivery',     'help' => 'TODO: please describe this field!',     'field' => array(       'handler' => 'views_handler_field_date',       'click sortable' => TRUE,     ),     'sort' => array(       'handler' => 'views_handler_sort_date',     ),     'filter' => array(         'handler' => 'views_handler_filter_date',       ),   ),   
        'mCoopFee' => array(     'title' => 'MCoopFee',     'help' => 'TODO: please describe this field!',     'field' => array(       
          'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
        'mSmallOrder' => array(     'title' => 'MSmallOrder',     'help' => 'TODO: please describe this field!',     'field' => array(       
          'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
        'mSmallOrderCoopFee' => array(     'title' => 'MSmallOrderCoopFee',     'help' => 'TODO: please describe this field!',     
          'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
        'fCoopFee' => array(     'title' => 'FCoopFee',     'help' => 'TODO: please describe this field!',     'field' => array(       
          'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
        'ModifiedByMemberID' => array(     'title' => 'ModifiedByMemberID',     'help' => 'TODO: please describe this field!',     
          'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
        'nStatus' => array(     'title' => 'NStatus',     'help' => 'TODO: please describe this field!',     
          'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
        'CoordinatingGroupID' => array(     'title' => 'CoordinatingGroupID',     'help' => 'TODO: please describe this field!',     
          'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
        'mMaxCoopTotal' => array(     'title' => 'MMaxCoopTotal',     'help' => 'TODO: please describe this field!',     
          'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
        'fMaxBurden' => array(     'title' => 'FMaxBurden',     'help' => 'TODO: please describe this field!',     
          'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
        'fBurden' => array(     'title' => 'FBurden',     'help' => 'TODO: please describe this field!',     
          'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
        'mCoopTotal' => array(     'title' => 'MCoopTotal',     'help' => 'TODO: please describe this field!',     
          'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
        'mProducerTotal' => array(     'title' => 'MProducerTotal',     'help' => 'TODO: please describe this field!',     
          'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
        'mTotalDelivery' => array(     'title' => 'MTotalDelivery',     'help' => 'TODO: please describe this field!',     
          'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
        'bHasJoinedProducts' => array(     'title' => 'BHasJoinedProducts',     'help' => 'TODO: please describe this field!',     
          'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
        'fMaxStorageBurden' => array(     'title' => 'FMaxStorageBurden',     'help' => 'TODO: please describe this field!',     
          'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
        'fStorageBurden' => array(     'title' => 'FStorageBurden',     'help' => 'TODO: please describe this field!',     
          'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_CoopOrderPickupLocation'] = array(   'table' => array(     
    'base' => array(       'field' => 'CoopOrderKeyID',       
      'title' => 'T CoopOrderPickupLocation',       
      'database' => 'homecoop',
      'help' => 'TODO: please describe the items in this table!',     ),     
    'group' => 'T CoopOrderPickupLocation',   ),   
    'CoopOrderKeyID' => array(     'title' => 'CoopOrderKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'PickupLocationKeyID' => array(     'title' => 'PickupLocationKeyID',     'help' => 'TODO: please describe this field!',    
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fMaxBurden' => array(     'title' => 'FMaxBurden',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fBurden' => array(     'title' => 'FBurden',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'mMaxCoopTotal' => array(     'title' => 'MMaxCoopTotal',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mCoopTotal' => array(     'title' => 'MCoopTotal',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fMaxStorageBurden' => array(     'title' => 'FMaxStorageBurden',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fStorageBurden' => array(     'title' => 'FStorageBurden',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_CoopOrderPickupLocationProducer'] = array(   'table' => array(     'base' => array(       
    'field' => 'CoopOrderKeyID',       'title' => 'T CoopOrderPickupLocationProducer', 'database' => 'homecoop',      
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T CoopOrderPickupLocationProducer',   ),   
    'CoopOrderKeyID' => array(     'title' => 'CoopOrderKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'ProducerKeyID' => array(     'title' => 'ProducerKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'PickupLocationKeyID' => array(     'title' => 'PickupLocationKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mProducerTotal' => array(     'title' => 'MProducerTotal',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mCoopTotal' => array(     'title' => 'MCoopTotal',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_CoopOrderPickupLocationProduct'] = array(   'table' => array(     'base' => array(       
    'field' => 'CoopOrderKeyID',       'title' => 'T CoopOrderPickupLocationProduct',    'database' => 'homecoop',      
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T CoopOrderPickupLocationProduct',   ),   
    'CoopOrderKeyID' => array(     'title' => 'CoopOrderKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'ProductKeyID' => array(     'title' => 'ProductKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'PickupLocationKeyID' => array(     'title' => 'PickupLocationKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mProducerTotal' => array(     'title' => 'MProducerTotal',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mCoopTotal' => array(     'title' => 'MCoopTotal',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fTotalCoopOrder' => array(     'title' => 'FTotalCoopOrder',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_CoopOrderProducer'] = array(   'table' => array(     'base' => array(       
    'field' => 'CoopOrderKeyID',       'title' => 'T CoopOrderProducer',      'database' => 'homecoop',       
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T CoopOrderProducer',   ),   
    'CoopOrderKeyID' => array(     'title' => 'CoopOrderKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'ProducerKeyID' => array(     'title' => 'ProducerKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mMaxProducerOrder' => array(     'title' => 'MMaxProducerOrder',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mProducerTotal' => array(     'title' => 'MProducerTotal',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fDelivery' => array(     'title' => 'FDelivery',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'mDelivery' => array(     'title' => 'MDelivery',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mMinDelivery' => array(     'title' => 'MMinDelivery',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mMaxDelivery' => array(     'title' => 'MMaxDelivery',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mTotalDelivery' => array(     'title' => 'MTotalDelivery',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fBurden' => array(     'title' => 'FBurden',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fMaxBurden' => array(     'title' => 'FMaxBurden',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'mCoopTotal' => array(     'title' => 'MCoopTotal',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_CoopOrderProduct'] = array(   'table' => array(     'base' => array(       
    'field' => 'CoopOrderKeyID',       'title' => 'T CoopOrderProduct',    'database' => 'homecoop',       
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T CoopOrderProduct',   ),   
    'CoopOrderKeyID' => array(     'title' => 'CoopOrderKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'ProductKeyID' => array(     'title' => 'ProductKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mProducerPrice' => array(     'title' => 'MProducerPrice',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mCoopPrice' => array(     'title' => 'MCoopPrice',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fMaxUserOrder' => array(     'title' => 'FMaxUserOrder',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fMaxCoopOrder' => array(     'title' => 'FMaxCoopOrder',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fBurden' => array(     'title' => 'FBurden',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fTotalCoopOrder' => array(     'title' => 'FTotalCoopOrder',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'nJoinedStatus' => array(     'title' => 'NJoinedStatus',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mProducerTotal' => array(     'title' => 'MProducerTotal',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mCoopTotal' => array(     'title' => 'MCoopTotal',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'bDisabled' => array(     'title' => 'BDisabled',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_CoopOrderProductStorage'] = array(   'table' => array(     'base' => array(       
    'field' => 'CoopOrderKeyID',       'title' => 'T CoopOrderProductStorage',   'database' => 'homecoop',       
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T CoopOrderProductStorage',   ),   
    'CoopOrderKeyID' => array(     'title' => 'CoopOrderKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'ProductKeyID' => array(     'title' => 'ProductKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'PickupLocationKeyID' => array(     'title' => 'PickupLocationKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'StorageAreaKeyID' => array(     'title' => 'StorageAreaKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_CoopOrderStorageArea'] = array(   'table' => array(     'base' => array(       
    'field' => 'CoopOrderKeyID',       'title' => 'T CoopOrderStorageArea',    'database' => 'homecoop',    
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T CoopOrderStorageArea',   ),   
    'CoopOrderKeyID' => array(     'title' => 'CoopOrderKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'StorageAreaKeyID' => array(     'title' => 'StorageAreaKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fMaxBurden' => array(     'title' => 'FMaxBurden',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fBurden' => array(     'title' => 'FBurden',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_CoordinatingGroup'] = array(   'table' => array(     'base' => array(       
    'field' => 'CoordinatingGroupID',       'title' => 'T CoordinatingGroup',     'database' => 'homecoop',  
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T CoordinatingGroup',   ),   
    'CoordinatingGroupID' => array(     'title' => 'CoordinatingGroupID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'sCoordinatingGroup' => array(     'title' => 'SCoordinatingGroup',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_CoordinatingGroupMember'] = array(   'table' => array(     'base' => array(       
    'field' => 'CoordinatingGroupID',       'title' => 'T CoordinatingGroupMember',       'database' => 'homecoop', 
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T CoordinatingGroupMember',   ),   
    'CoordinatingGroupID' => array(     'title' => 'CoordinatingGroupID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'MemberID' => array(     'title' => 'MemberID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'bContactPerson' => array(     'title' => 'BContactPerson',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_Key'] = array(   'table' => array(     'base' => array(       'field' => 'KeyID',       'title' => 'T Key',   'database' => 'homecoop',      
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T Key',   ),   
    'KeyID' => array(     
      'title' => 'KeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'sStringKey' => array(     'title' => 'SStringKey',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_Measure'] = array(   'table' => array(     'base' => array(       
    'field' => 'MeasureKeyID',       'title' => 'T Measure',    'database' => 'homecoop',      
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T Measure',   ),   
    'MeasureKeyID' => array(     'title' => 'MeasureKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_Member'] = array(   'table' => array(     'base' => array(       
    'field' => 'MemberID',       'title' => 'T Member',      'database' => 'homecoop',  
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T Member',   ),   
    'MemberID' => array(     'title' => 'MemberID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'sLoginName' => array(     'title' => 'SLoginName',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'sPassword' => array(     'title' => 'SPassword',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'sEMail' => array(     'title' => 'SEMail',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'PaymentMethodKeyID' => array(     'title' => 'PaymentMethodKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'dJoined' => array(     'title' => 'DJoined',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_date',       'click sortable' => TRUE,     ),     
      'sort' => array(       'handler' => 'views_handler_sort_date',     ),     'filter' => array(         'handler' => 'views_handler_filter_date',       ),   ),   
    'mBalance' => array(     'title' => 'MBalance',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'sName' => array(     'title' => 'SName',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fPercentOverBalance' => array(     'title' => 'FPercentOverBalance',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'sEMail2' => array(     'title' => 'SEMail2',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'sEMail3' => array(     'title' => 'SEMail3',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'sEMail4' => array(     'title' => 'SEMail4',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'bDisabled' => array(     'title' => 'BDisabled',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'sComments' => array(     'title' => 'SComments',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'mBalanceInvested' => array(     'title' => 'MBalanceInvested',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mBalanceHeld' => array(     'title' => 'MBalanceHeld',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'nExportFormat' => array(     'title' => 'NExportFormat',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'sPasswordForMigration' => array(     'title' => 'SPasswordForMigration',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_MemberPickupLocation'] = array(   'table' => array(     'base' => array(       
    'field' => 'MemberID',       'title' => 'T MemberPickupLocation',   'database' => 'homecoop',      
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T MemberPickupLocation',   ),   
    'MemberID' => array(     'title' => 'MemberID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'PickupLocationKeyID' => array(     'title' => 'PickupLocationKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'bBlocked' => array(     'title' => 'BBlocked',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'bRemoved' => array(     'title' => 'BRemoved',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_MemberProducer'] = array(   'table' => array(     'base' => array(       'field' => 'MemberID',       
    'title' => 'T MemberProducer',       'database' => 'homecoop', 
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T MemberProducer',   ),   
    'MemberID' => array(     'title' => 'MemberID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'ProducerKeyID' => array(     'title' => 'ProducerKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'bBlocked' => array(     'title' => 'BBlocked',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'bRemoved' => array(     'title' => 'BRemoved',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_MemberRole'] = array(   'table' => array(     'base' => array(       
    'field' => 'MemberID',       'title' => 'T MemberRole',   'database' => 'homecoop',     
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T MemberRole',   ),   
    'MemberID' => array(     'title' => 'MemberID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'RoleKeyID' => array(     'title' => 'RoleKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_Order'] = array(   'table' => array(     'base' => array(       
    'field' => 'OrderID',       'title' => 'T Order',       'database' => 'homecoop',     
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T Order',   ),   
    'OrderID' => array(     'title' => 'OrderID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'CoopOrderKeyID' => array(     'title' => 'CoopOrderKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'MemberID' => array(     'title' => 'MemberID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'PickupLocationKeyID' => array(     'title' => 'PickupLocationKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'dCreated' => array(     'title' => 'DCreated',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_date',       'click sortable' => TRUE,     ),     'sort' => array(       
        'handler' => 'views_handler_sort_date',     ),     'filter' => array(         'handler' => 'views_handler_filter_date',       ),   ),   
    'dModified' => array(     'title' => 'DModified',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_date',       'click sortable' => TRUE,     ),     'sort' => array(       
        'handler' => 'views_handler_sort_date',     ),     'filter' => array(         'handler' => 'views_handler_filter_date',       ),   ),   
    'mCoopTotal' => array(     'title' => 'MCoopTotal',     'help' => 'TODO: please describe this field!',     'field' => array(       
      'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'CreatedByMemberID' => array(     'title' => 'CreatedByMemberID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'ModifiedByMemberID' => array(     'title' => 'ModifiedByMemberID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mProducerTotal' => array(     'title' => 'MProducerTotal',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'sMemberComments' => array(     'title' => 'SMemberComments',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'mCoopFee' => array(     'title' => 'MCoopFee',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'bHasItemComments' => array(     'title' => 'BHasItemComments',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fBurden' => array(     'title' => 'FBurden',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'mCoopTotalIncFee' => array(     'title' => 'MCoopTotalIncFee',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'PaymentMethodKeyID' => array(     'title' => 'PaymentMethodKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fPercentOverBalance' => array(     'title' => 'FPercentOverBalance',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_OrderItem'] = array(   'table' => array(     'base' => array(       
    'field' => 'OrderItemID',       'title' => 'T OrderItem',    'database' => 'homecoop',     
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T OrderItem',   ),   
    'OrderItemID' => array(     'title' => 'OrderItemID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'OrderID' => array(     'title' => 'OrderID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'ProductKeyID' => array(     'title' => 'ProductKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fQuantity' => array(     'title' => 'FQuantity',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'mCoopPrice' => array(     'title' => 'MCoopPrice',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mProducerPrice' => array(     'title' => 'MProducerPrice',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fOriginalQuantity' => array(     'title' => 'FOriginalQuantity',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fMaxFixQuantityAddition' => array(     'title' => 'FMaxFixQuantityAddition',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'sMemberComments' => array(     'title' => 'SMemberComments',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fUnjoinedQuantity' => array(     'title' => 'FUnjoinedQuantity',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'nJoinedItems' => array(     'title' => 'NJoinedItems',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_OrderItem_Deleted'] = array(   'table' => array(     'base' => array(       
    'field' => 'OrderItemID',       'title' => 'T OrderItem Deleted',    'database' => 'homecoop',     
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T OrderItem Deleted',   ),   
    'OrderItemID' => array(     'title' => 'OrderItemID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'OrderID' => array(     'title' => 'OrderID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'ProductKeyID' => array(     'title' => 'ProductKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fQuantity' => array(     'title' => 'FQuantity',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'mCoopPrice' => array(     'title' => 'MCoopPrice',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mProducerPrice' => array(     'title' => 'MProducerPrice',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fOriginalQuantity' => array(     'title' => 'FOriginalQuantity',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fMaxFixQuantityAddition' => array(     'title' => 'FMaxFixQuantityAddition',     
      'help' => 'TODO: please describe this field!',     'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'sMemberComments' => array(     'title' => 'SMemberComments',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fUnjoinedQuantity' => array(     'title' => 'FUnjoinedQuantity',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'nJoinedItems' => array(     'title' => 'NJoinedItems',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'DeletedBy' => array(     'title' => 'DeletedBy',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_PaymentMethod'] = array(   'table' => array(     'base' => array(       
    'field' => 'PaymentMethodKeyID',       'title' => 'T PaymentMethod',   'database' => 'homecoop',     
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T PaymentMethod',   ),   
    'PaymentMethodKeyID' => array(     'title' => 'PaymentMethodKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_Permission'] = array(   'table' => array(     'base' => array(       
    'field' => 'PermissionAreaKeyID',       'title' => 'T Permission',       'help' => 'TODO: please describe the items in this table!',     ),     
    'group' => 'T Permission',   ),   
    'PermissionAreaKeyID' => array(     'title' => 'PermissionAreaKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'PermissionTypeKeyID' => array(     'title' => 'PermissionTypeKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'nAllowedScopeCodes' => array(     'title' => 'NAllowedScopeCodes',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_PermissionArea'] = array(   'table' => array(     'base' => array(       
    'field' => 'PermissionAreaKeyID',       'title' => 'T PermissionArea',     'database' => 'homecoop',       
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T PermissionArea',   ),   
    'PermissionAreaKeyID' => array(     'title' => 'PermissionAreaKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_PermissionScope'] = array(   'table' => array(     'base' => array(       
    'field' => 'PermissionScopeKeyID',       'title' => 'T PermissionScope',      'database' => 'homecoop',       
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T PermissionScope',   ),   
    'PermissionScopeKeyID' => array(     'title' => 'PermissionScopeKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'nScopeCode' => array(     'title' => 'NScopeCode',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_PermissionType'] = array(   'table' => array(     'base' => array(       'field' => 'PermissionTypeKeyID',       
    'title' => 'T PermissionType',       'database' => 'homecoop',    
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T PermissionType',   ),   
    'PermissionTypeKeyID' => array(     'title' => 'PermissionTypeKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_PickupLocation'] = array(   'table' => array(     'base' => array(       
    'field' => 'PickupLocationKeyID',       'title' => 'T PickupLocation',   'database' => 'homecoop',       
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T PickupLocation',   ),   
    'PickupLocationKeyID' => array(     'title' => 'PickupLocationKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'AddressStringKeyID' => array(     'title' => 'AddressStringKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'PublishedCommentsStringKeyID' => array(     'title' => 'PublishedCommentsStringKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'AdminCommentsStringKeyID' => array(     'title' => 'AdminCommentsStringKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'bDisabled' => array(     'title' => 'BDisabled',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'CoordinatingGroupID' => array(     'title' => 'CoordinatingGroupID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fMaxBurden' => array(     'title' => 'FMaxBurden',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'nRotationOrder' => array(     'title' => 'NRotationOrder',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'sExportFileName' => array(     'title' => 'SExportFileName',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'mCachier' => array(     'title' => 'MCachier',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mPrevCachier' => array(     'title' => 'MPrevCachier',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'dCachierUpdate' => array(     'title' => 'DCachierUpdate',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_date',       'click sortable' => TRUE,     ),     'sort' => array(       
        'handler' => 'views_handler_sort_date',     ),     'filter' => array(         'handler' => 'views_handler_filter_date',       ),   ), ); 
  
  $data['T_PickupLocationStorageArea'] = array(   'table' => array(     'base' => array(       
    'field' => 'StorageAreaKeyID',       'title' => 'T PickupLocationStorageArea',  'database' => 'homecoop',      
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T PickupLocationStorageArea',   ),   
    'PickupLocationKeyID' => array(     'title' => 'PickupLocationKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'StorageAreaKeyID' => array(     'title' => 'StorageAreaKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fMaxBurden' => array(     'title' => 'FMaxBurden',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'bDisabled' => array(     'title' => 'BDisabled',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'bDefault' => array(     'title' => 'BDefault',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_Producer'] = array(   'table' => array(     'base' => array(       
    'field' => 'ProducerKeyID',       'title' => 'T Producer',      'database' => 'homecoop',    
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T Producer',   ),   
    'ProducerKeyID' => array(     'title' => 'ProducerKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'bDisabled' => array(     'title' => 'BDisabled',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'CoordinatingGroupID' => array(     'title' => 'CoordinatingGroupID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'sExportFileName' => array(     'title' => 'SExportFileName',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_Product'] = array(   'table' => array(     'base' => array(       
    'field' => 'ProductKeyID',       'title' => 'T Product',      'database' => 'homecoop',       
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T Product',   ),   
    'ProductKeyID' => array(     'title' => 'ProductKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'ProducerKeyID' => array(     'title' => 'ProducerKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'SpecStringKeyID' => array(     'title' => 'SpecStringKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'UnitKeyID' => array(     'title' => 'UnitKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fQuantity' => array(     'title' => 'FQuantity',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fPackageSize' => array(     'title' => 'FPackageSize',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fUnitInterval' => array(     'title' => 'FUnitInterval',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'fMaxUserOrder' => array(     'title' => 'FMaxUserOrder',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'bDisabled' => array(     'title' => 'BDisabled',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mProducerPrice' => array(     'title' => 'MProducerPrice',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mCoopPrice' => array(     'title' => 'MCoopPrice',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fBurden' => array(     'title' => 'FBurden',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'sImage1FileName' => array(     'title' => 'SImage1FileName',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'nItems' => array(     'title' => 'NItems',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'ItemUnitKeyID' => array(     'title' => 'ItemUnitKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'fItemQuantity' => array(     'title' => 'FItemQuantity',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'nSortOrder' => array(     'title' => 'NSortOrder',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'JoinToProductKeyID' => array(     'title' => 'JoinToProductKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'sImage2FileName' => array(     'title' => 'SImage2FileName',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_Role'] = array(   'table' => array(     'base' => array(       
    'field' => 'RoleKeyID',       'title' => 'T Role',        'database' => 'homecoop',     
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T Role',   ),   
  'RoleKeyID' => array(     'title' => 'RoleKeyID',     'help' => 'TODO: please describe this field!',     
    'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_RolePermission'] = array(   'table' => array(     'base' => array(       
    'field' => 'RoleKeyID',       'title' => 'T RolePermission',   'database' => 'homecoop',         
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T RolePermission',   ),   
    'RoleKeyID' => array(     'title' => 'RoleKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'PermissionAreaKeyID' => array(     'title' => 'PermissionAreaKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'PermissionTypeKeyID' => array(     'title' => 'PermissionTypeKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'PermissionScopeKeyID' => array(     'title' => 'PermissionScopeKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_Transaction'] = array(   'table' => array(     'base' => array(       
    'field' => 'TransactionID',       'title' => 'T Transaction',  'database' => 'homecoop',        
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T Transaction',   ),   
    'TransactionID' => array(     'title' => 'TransactionID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'PickupLocationKeyID' => array(     'title' => 'PickupLocationKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'MemberID' => array(     'title' => 'MemberID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'ModifiedByMemberID' => array(     'title' => 'ModifiedByMemberID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'mAmount' => array(     'title' => 'MAmount',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'dDate' => array(     'title' => 'DDate',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_date',       'click sortable' => TRUE,     ),     'sort' => array(       
        'handler' => 'views_handler_sort_date',     ),     'filter' => array(         'handler' => 'views_handler_filter_date',       ),   ),   
    'sTransaction' => array(     'title' => 'STransaction',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['T_Unit'] = array(   'table' => array(     'base' => array(       
    'field' => 'UnitKeyID',       'title' => 'T Unit',   'database' => 'homecoop',           
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'T Unit',   ),   
    'UnitKeyID' => array(     'title' => 'UnitKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'MeasureKeyID' => array(     'title' => 'MeasureKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'nFloatingPoint' => array(     'title' => 'NFloatingPoint',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'UnitAbbreviationStringKeyID' => array(     'title' => 'UnitAbbreviationStringKeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['Tlng_Language'] = array(   'table' => array(     'base' => array(       'field' => 'LangID',       
    'title' => 'Tlng Language',     'database' => 'homecoop',    
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'Tlng Language',   ),   
    'LangID' => array(     'title' => 'LangID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'sLanguage' => array(     'title' => 'SLanguage',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ),   
    'bActive' => array(     'title' => 'BActive',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'bRequired' => array(     'title' => 'BRequired',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'FallingLangID' => array(     'title' => 'FallingLangID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'sPhpFolder' => array(     'title' => 'SPhpFolder',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ), ); 
  
  $data['Tlng_String'] = array(   'table' => array(     'base' => array(       
    'field' => 'KeyID',       'title' => 'Tlng String',    'database' => 'homecoop',        
    'help' => 'TODO: please describe the items in this table!',     ),     'group' => 'Tlng String',   ),   
    'KeyID' => array(     'title' => 'KeyID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'LangID' => array(     'title' => 'LangID',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field_numeric',       'click sortable' => FALSE,     ),   ),   
    'sString' => array(     'title' => 'SString',     'help' => 'TODO: please describe this field!',     
      'field' => array(       'handler' => 'views_handler_field',       'click sortable' => FALSE,     ),   ), ); 
  
  return $data;
}