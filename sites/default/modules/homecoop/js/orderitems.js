function Save()
{
  /*document.getElementById("hidPostAction").value = <?php echo SQLBase::POST_ACTION_SAVE; ?>;*/
}
function SwitchViewMode()
{
  var bConfirm = true;
  if (document.getElementById("hidDirty").value == 1)
    bConfirm = confirm(Drupal.settings.homecoop.ConfirmChanges);
  
  if (bConfirm)
  {
    /*document.getElementById("hidPostAction").value = <?php echo OrderItems::POST_ACTION_SWITCH_VIEW_MODE; ?>;
    document.frmMain.submit();*/
  }
  else
  {
    /*if (document.getElementById("selProductsView").selectedIndex == <?php echo OrderItems::PRODUCTS_VIEW_MODE_SHOW_ALL; ?>)
      document.getElementById("selProductsView").selectedIndex = <?php echo OrderItems::PRODUCTS_VIEW_MODE_ITEMS_ONLY; ?>;
    else
      document.getElementById("selProductsView").selectedIndex = <?php echo OrderItems::PRODUCTS_VIEW_MODE_SHOW_ALL; ?>;*/
  }
}
function SetDirty()
{
  document.getElementById("hidDirty").value = 1;
}