<?php

function homecoop_page_cashier() {
  homecoop_authenticated_page();
  
  $oData = new CachierTotals;
  
  if (!$oData->GetAccess())
  {
      drupal_goto(Consts::URL_ACCESS_DENIED);
      return;
  }
  
  drupal_set_title(t('Cashier Totals'));
  
  $mCashiers = Rounding::Round(homecoop_cashier_cashiers(), Rounding::ROUND_TYPE_DEFAULT);
  $mMembers = Rounding::Round(homecoop_cashier_members(), Rounding::ROUND_TYPE_DEFAULT);
  $mBalance = intval($mCashiers - $mMembers);
  
  $content = array(
    'members' => array(
      '#prefix' => '<div class="resgridrow">',
      '#suffix' => '</div>',
      'memlabel' => array(
        '#prefix' => '<span>',
        '#markup' => t('Total Member Balances:'),
        '#suffix' => '</span>',
      ),
      'memsum' => array(
        '#prefix' => '<div class="headlabel" dir="ltr">',
        '#markup' => $mMembers,
        '#suffix' => '</div>',
      ),
    ),
    'cashiers' => array(
      '#prefix' => '<div class="resgridrow">',
      '#suffix' => '</div>',
      'cashierlabel' => array(
        '#prefix' => '<span>',
        '#markup' => t('Total Cashiers:'),
        '#suffix' => '</span>',
      ),
      'cashiersum' => array(
        '#prefix' => '<div class="headlabel" dir="ltr">',
        '#markup' => $mCashiers,
        '#suffix' => '</div>',
      ),
    ),
    'balance' => array(
      '#prefix' => '<div class="resgridrow">',
      '#suffix' => '</div>',
      'balancelabel' => array(
        '#prefix' => '<span>',
        '#markup' => t('Total Balance:'),
        '#suffix' => '</span>',
      ),
      'balancesum' => array(
        '#prefix' => '<div class="headlabel" dir="ltr">',
        '#markup' => $mBalance,
        '#suffix' => '</div>',
      ),
    ),
    'newline' => array('#markup' => '<br/>'),
  );
  
  //close session opened in 'authenticate.php' when not required anymore
  UserSessionBase::Close();
  
  return $content;
}

function homecoop_cashier_members() {
    $query = db_select('T_Member', 'm', array('target' => 'homecoop'));
    $query->addExpression('sum(mBalanceHeld)', 'mBalanceHeld');
    $results = $query->execute()->fetchAssoc();

    if (is_array($results)) {
      return $results['mBalanceHeld'];
    }
    
    return 0;
}

function homecoop_cashier_cashiers() {
    $query = db_select('T_PickupLocation', 'p', array('target' => 'homecoop'));
    $query->addExpression('sum(mCachier)', 'mCachier');
    $results = $query->execute()->fetchAssoc();

    if (is_array($results)) {
      return $results['mCachier'];
    }
    
    return 0;
}