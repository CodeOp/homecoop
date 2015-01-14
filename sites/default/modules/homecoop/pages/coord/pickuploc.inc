<?php

function homecoop_page_pickuploc_add() {
  homecoop_page_pickuploc_common_start();
  
}

function homecoop_page_pickuploc_edit($entity) {
  homecoop_page_pickuploc_common_start();
  
}

function homecoop_page_pickuploc_common_start()
{
  homecoop_authenticated_page();
  
  $oRecord = new PickupLocation;
  
  if (!$oRecord->CheckAccess())
  {
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
}