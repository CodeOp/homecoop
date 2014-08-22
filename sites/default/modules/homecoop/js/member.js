function Delete()
{
  if (confirm(Drupal.settings.homecoop.ConfirmDelete))
  {
    document.getElementById("hidPostAction").value = Drupal.settings.homecoop.PostActionDelete;
    document.homecoop_page_member_form.submit();
  }
}
function Deactivate()
{
    document.getElementById("hidPostAction").value = Drupal.settings.homecoop.PostActionDeactivate;
    document.homecoop_page_member_form.submit();  
}
function Activate()
{
    document.getElementById("hidPostAction").value = Drupal.settings.homecoop.PostActionActivate;
    document.homecoop_page_member_form.submit();  
}
function Save()
{
  document.getElementById("hidPostAction").value = Drupal.settings.homecoop.PostActionSave;
}
function VerifyPassword()
{
  if (document.getElementById("txtNewPassword").value == document.getElementById("txtVerifyPassword").value)
  {
    if (document.getElementById("txtNewPassword").value == '')
      document.getElementById("spVerifyResult").innerHTML = '';
    else
    {
      document.getElementById("spVerifyResult").style.color = 'green';
      document.getElementById("spVerifyResult").innerHTML = 'Password verification succeeded';
    }
  }
  else
  {
    document.getElementById("spVerifyResult").style.color = 'red';
    document.getElementById("spVerifyResult").innerHTML = 'Password verification failed';
  }
}