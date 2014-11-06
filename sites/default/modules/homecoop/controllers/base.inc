<?php

/*
 * homecoop base entity controller
 * 
 */

class HomeCoopBaseController {
  
  /**
   * Overrides DrupalDefaultEntityController::resetCache().
   */
  public function resetCache(array $ids = NULL) {
    $this->cacheComplete = FALSE;
    if (isset($ids)) {
      foreach ($ids as $id) {
        unset($this->entityCache[$id]);
      }
    }
    else {
      $this->entityCache = array();
    }
    // Support the entitycache module.
    if (!empty($this->entityInfo['entity cache'])) {
      EntityCacheControllerHelper::resetEntityCache($this, $ids);
    }
  }
}