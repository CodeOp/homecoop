<?php

if(realpath(__FILE__) == realpath($_SERVER['SCRIPT_FILENAME']))
   return;

//this class currently displays only balance validation notice
//in the future may display other notices as well
class Notifications {

  public function DisplayNotifications()
  {
    global $g_oMemberSession, $g_dNow;
    
    //dynamic notification for new member's 0 balance
    if (    $g_oMemberSession->Balance == 0 
            && $g_oMemberSession->PaymentMethod != Consts::PAYMENT_METHOD_AT_PICKUP )
    {
        drupal_set_message('<!$MSG_ZERO_BALNACE_LINE1$!>', 'warning');
        drupal_set_message('<!$MSG_ZERO_BALNACE_LINE2$!>', 'warning');
        drupal_set_message(sprintf('<!$MSG_ZERO_BALNACE_LINE4$!>', COOP_ADDRESS_MEMBER_BALANCE ), 'warning');
    }    
  }
}

?>
