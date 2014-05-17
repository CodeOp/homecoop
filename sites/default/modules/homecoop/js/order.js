function ConfirmDelete()
{
  return confirm(Drupal.settings.homecoop.ConfirmDelete);
}
function MemberChange()
{
  <?php
  if ($oRecord->ID > 0) { ?>
    if (!confirm(decodeXml('Attention: you have chosen to move this order from one member to another. To complete the operation confirm this message box and save the order')))
    {
      document.getElementById("selMemberID").value = <?php echo $oRecord->MemberID; ?>;
      return;
    }
  <?php } ?>
  
  document.getElementById("hidPostAction").value = <?php echo Order::POST_ACTION_MEMBER_CHANGE; ?>;
  document.frmMain.submit();
}