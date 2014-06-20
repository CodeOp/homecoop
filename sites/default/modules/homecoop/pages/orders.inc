<?php

function homecoop_page_orders() {
  homecoop_authenticated_page();
  
  drupal_set_title(t('My Orders'));
  
  return views_embed_view('homecoop_my_orders');
}