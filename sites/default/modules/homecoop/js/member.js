function Delete()
{
  if (confirm(Drupal.settings.homecoop.ConfirmDelete))
  {
    document.homecoop_page_member_form.submit();
  }
}