<?php

/*
 * homecoop_member entity controller
 * 
 */
class HomeCoopMemberController extends HomeCoopBaseController implements DrupalEntityControllerInterface {
  
  const ENTNAME = 'homecoop_member';
  
  public function create(array $values = array()) {
    if (!empty($values))
       return (object)$values;
    $oRecord = new Member();
    return (object)($oRecord->GetAllProperties()
        + array(
          'HasAccessToRoles' => $oRecord->HasAccessToRoles(),
          'hasdeletepermission' => $oRecord->HasPermission(SQLBase::PERMISSION_DELETE),
          'OriginalData' => $oRecord->GetSerializedOriginalData(),
        )
      );
  }
  
  public function save($entity) {
    try {
      global $user;
      
      // Determine if we will be inserting a new record
      $bIsNew = empty($entity->ID);
                  
      // Give modules the opportunity to prepare field data for
      // saving.
      field_attach_presave(ENTNAME, $entity);
      
      //convert entity back to array to set all the class properties
      $oMember = new Member();
      $arrProps = (array)$entity;
      foreach($arrProps as $key => $value) {
        $oMember->$key = $value;
      }

      // If this is a new record...
      if ($bIsNew) {
        if (!$oMember->Add())
          return FALSE;
                
        $op = 'insert';
      }
      else {
        if (!$oMember->Edit())
          return FALSE;
        
        $op = 'update';
      }
      
      unset($oMember);
            
      // Save fields.
      $function = 'field_attach_' . $op;
      $function(ENTNAME, $entity);
      
      module_invoke_all('entity_' . $op, $entity, ENTNAME);
          
      return $entity;
    }
    catch (Exception $e) {
      watchdog_exception(ENTNAME, $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
  }
  
  public function delete($ids) {
    if (empty($ids)) {
      return TRUE;
    }
      
    $entities = $this->load($ids, array());
        
    try
    {
      foreach($ids as $id) {
        $oMember = new Member();
        $oMember->ID = $id;
        $oMember->Delete();
        unset($oMember);
      }
      
      //delete fields
      foreach($entities as $entity) {        
        field_attach_delete(ENTNAME, $entity);

        module_invoke_all('entity_delete', $entity, ENTNAME);
      }
    }
    catch(Exception $e) {
      watchdog_exception(ENTNAME, $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
    
    return TRUE;
  }
    
  public function load($ids = array(), $conditions = array())
  {
    $entities = array();
    
    foreach($ids as $id) {
      $oRecord = new Member();
      if (!$oRecord->LoadRecord($id)) {
        throw new Exception(t('Access denied. Member entity load failed.'));
      }
      
      switch($oRecord->LastOperationStatus)
      {
        case SQLBase::OPERATION_STATUS_NO_SUFFICIENT_DATA_PROVIDED:
        case SQLBase::OPERATION_STATUS_NO_PERMISSION:
        case SQLBase::OPERATION_STATUS_LOAD_RECORD_FAILED:
        case SQLBase::OPERATION_STATUS_COORDINATION_GROUP_VERIFY_FAILED:
          throw new Exception(t('Access denied. Member entity load operation is not allowed.'));
      }
      $oRecord->RevokeModifyPermission();
      
      $oMemberTabInfo = new MemberTabInfo($oRecord->ID, MemberTabInfo::PAGE_ENTRY);
      $oMemberTabInfo->MainTabName = $oRecord->Name;
      $entities[$id] = $this->create($oRecord->GetAllProperties() +
          array(
          'HasAccessToRoles' => $oRecord->HasAccessToRoles(),
          'hasdeletepermission' => $oRecord->HasPermission(SQLBase::PERMISSION_DELETE),
          'OriginalData' => $oRecord->GetSerializedOriginalData(),
        ) + homecoop_member_tab_info($oMemberTabInfo) );
    }
    
    return $entities;
  }
}