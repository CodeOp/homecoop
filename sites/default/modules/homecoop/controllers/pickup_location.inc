<?php

/*
 * homecoop_member entity controller
 * 
 */
class HomeCoopPickupLocationController extends HomeCoopBaseController implements DrupalEntityControllerInterface {
  
  const ENTNAME = 'homecoop_pickup_location';
  
  public function create(array $values = array()) {
    if (!empty($values))
       return (object)$values;
    $oRecord = new PickupLocation();
    return (object)($oRecord->GetAllProperties()
        + array(
          'OriginalData' => $oRecord->GetSerializedOriginalData(),
        )
      );
  }
  
  
   public function save($entity) {
    try {
      global $user;
      
      //use user_save
      
      // Determine if we will be inserting a new record
      $entity->IsNew = empty($entity->ID);
                  
      // Give modules the opportunity to prepare field data for
      // saving.
      //field_attach_presave(self::ENTNAME, $entity);
      
      //convert entity back to array to set all the class properties
      $oPickupLocation = $this->toClass($entity);
      
      // If this is a new record...
      if ($entity->IsNew) {
        if (!$oPickupLocation->Add())
          return FALSE;
        $entity->ID = $oPickupLocation->ID;        
        $op = 'insert';
      }
      else {
        if (!$oPickupLocation->Edit())
          return FALSE;
        $op = 'update';
      }
      
      unset($oPickupLocation);
            
      // Save fields.
      //$function = 'field_attach_' . $op;
      //$function(self::ENTNAME, $entity);
      
      //module_invoke_all('entity_' . $op, $entity, self::ENTNAME);
          
      return $entity;
    }
    catch (Exception $e) {
      watchdog_exception(self::ENTNAME, $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
  }
  
  public function load($ids = array(), $conditions = array())
  {
    $entities = array();
    
    foreach($ids as $id) {
      $oRecord = new PickupLocation();
      if (!$oRecord->LoadRecord($id)) {
        throw new Exception(t('Access denied. Pickup Location entity load failed.'));
      }
      
      switch($oRecord->LastOperationStatus)
      {
        case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
        case SQLBase::OPERATION_STATUS_NO_PERMISSION:
        case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
        case SQLBase::OPERATION_STATUS_COORDINATION_GROUP_VERIFY_FAILED:
          throw new Exception(t('Access denied. Pickup Location entity load operation is not allowed.'));
      }
      
      $oPickupLocationTabInfo = new PickupLocationTabInfo($oRecord->ID, $oRecord->CoordinatingGroupID, 
        PickupLocationTabInfo::PAGE_ENTRY);
      
      $oPickupLocationTabInfo->MainTabName = $oRecord->Name;
      
      $entities[$id] = $this->create($oRecord->GetAllProperties() +
          array('OriginalData' => $oRecord->GetSerializedOriginalData())
          + homecoop_pickup_location_tab_info($oPickupLocationTabInfo)
         );
    }
    
    return $entities;
  }
  
  public function delete($ids) {
    if (empty($ids)) {
      return TRUE;
    }
        
    try
    {
      //field code
      //$entities = $this->load($ids, array());
      
      foreach($ids as $id) {
        $oPickupLocation = new PickupLocation();
        $oPickupLocation->ID = $id;
        $oPickupLocation->Delete();
        unset($oPickupLocation);
      }

      //delete fields
      //foreach($entities as $entity) {        
      //  field_attach_delete(self::ENTNAME, $entity);

      //  module_invoke_all('entity_delete', $entity, self::ENTNAME);
      //}
    }
    catch(Exception $e) {
      watchdog_exception(self::ENTNAME, $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
    
    return TRUE;
  }
  
  public function toClass($entity) {
    $oMember = new Member();
    $arrProps = (array)$oMember->GetAllProperties();
    foreach($arrProps as $key => $value) {
      $oMember->$key = $entity->$key;
    }
    return $oMember;
  }
}