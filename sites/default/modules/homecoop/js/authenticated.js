function Logout()
{
    document.getElementById('hidLogout').value = '1';
    document.forms['frmhcheader'].submit();
}

function OpenProductOverview(sUrl)
{
  //var sUrl = sPathToRoot + 'product.php?prd=' + ProductID + "&coid=" + CoopOrderID;
  var nLeft = screen.availWidth/2 - screen.availWidth/4;
  if (nLeft < 0) nLeft = 0;

  var sParams = 'status=0,toolbar=0,menubar=0,height=' + (screen.availHeight*2/3) + ', width=' + (screen.availWidth/2) + ',top=100,left=' + nLeft;
  window.open(sUrl, '_blank', sParams );
}

function ToggleTabDisplay(sTabNameToShow) {
  var sTabToHide = document.getElementById('hidCurrentMainTab').value;
  
  if (sTabNameToShow == sTabToHide) return;
  
  var ctlTabToHide = document.getElementById(sTabToHide);
  
  if (ctlTabToHide != null) {
    ctlTabToHide.style.display = "none";
  }
  
  var ctlTabToShow = document.getElementById(sTabNameToShow);
  
  if (ctlTabToShow != null) {
    ctlTabToShow.style.display = "block";
  }
  
  var ctlTabItemToHide = document.getElementById(sTabToHide + "Item");
  
  if (ctlTabItemToHide != null) {
    ctlTabItemToHide.style.backgroundColor = "#D8D8D8";
  }
  
  var ctlTabItemToShow = document.getElementById(sTabNameToShow + "Item");
  
  if (ctlTabItemToShow != null) {
    document.getElementById(sTabNameToShow + "Item").style.backgroundColor = "#FFF";
  }
  
  document.getElementById('hidCurrentMainTab').value = sTabNameToShow;
}

