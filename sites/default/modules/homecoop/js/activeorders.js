function OpenOrder(sRoot, nOrderID)
{
  document.location = sRoot + 'hcorderitems?id=' + nOrderID;
}

function NewOrder(sRoot, nCoopOrderID)
{
  document.location = sRoot + 'hcorder?coid=' + nCoopOrderID;
}
