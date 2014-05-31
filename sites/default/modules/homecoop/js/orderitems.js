function Save()
{
  document.getElementById("hidPostAction").value = <?php echo SQLBase::POST_ACTION_SAVE; ?>;
}
function SwitchViewMode()
{
  var bConfirm = true;
  if (document.getElementById("hidDirty").value == 1)
    bConfirm = confirm(decodeXml('It seems you have made changes and did not save them. If you proceed in changing the products view mode, these changes will be lost. Proceed?'));
  
  if (bConfirm)
  {
    document.getElementById("hidPostAction").value = <?php echo OrderItems::POST_ACTION_SWITCH_VIEW_MODE; ?>;
    document.frmMain.submit();
  }
  else
  {
    if (document.getElementById("selProductsView").selectedIndex == <?php echo OrderItems::PRODUCTS_VIEW_MODE_SHOW_ALL; ?>)
      document.getElementById("selProductsView").selectedIndex = <?php echo OrderItems::PRODUCTS_VIEW_MODE_ITEMS_ONLY; ?>;
    else
      document.getElementById("selProductsView").selectedIndex = <?php echo OrderItems::PRODUCTS_VIEW_MODE_SHOW_ALL; ?>;
  }
}
function SetDirty()
{
  document.getElementById("hidDirty").value = 1;
}