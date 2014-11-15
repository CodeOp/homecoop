(function($) {
  Drupal.ajax.prototype.commands.SetExisting = function(ajax, response, status) {
    if (response.success) {
      document.getElementById('existing_' + response.plid).value = 1;
    }    
  };
  
}(jQuery));

function SetActionParams(nPickupLoc) {
  document.getElementById('hidPickupLocation').value = nPickupLoc;
}