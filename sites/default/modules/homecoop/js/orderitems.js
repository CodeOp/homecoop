function SwitchViewMode() {
  var bConfirm = true;
  if (document.getElementById("hidDirty").value == 1)
    bConfirm = confirm(Drupal.settings.homecoop.ConfirmChanges);
  
  if (bConfirm)
  {
    document.getElementById("hidPostAction").value = Drupal.settings.homecoop.PostActionViewChange;
    document.homecoop_page_orderitems_form.submit();
  }
  else
  {
    if (document.getElementById("selProductsView").selectedIndex == Drupal.settings.homecoop.PostActionShowAll)
      document.getElementById("selProductsView").selectedIndex = Drupal.settings.homecoop.PostActionItemOnly;
    else
      document.getElementById("selProductsView").selectedIndex = Drupal.settings.homecoop.PostActionShowAll;
  }
}
function Save() {
  document.getElementById("hidPostAction").value = 0;
}
function SetDirty() {
  document.getElementById("hidDirty").value = 1;
}