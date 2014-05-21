function ConfirmDelete()
{
  return confirm(Drupal.settings.homecoop.ConfirmDelete);
}

function MemberChange()
{
  if (Drupal.settings.homecoop.MemberID > 0) {
    if (!confirm(Drupal.settings.homecoop.ConfirmMemberChange)) {
      document.getElementById("selMemberID").value = Drupal.settings.homecoop.MemberID;
      return false;
    }
  }
  document.getElementById("hidPostAction").value = Drupal.settings.homecoop.PostActionMemberChange;
  document.homecoop_page_order_form.submit();
  return true;
}