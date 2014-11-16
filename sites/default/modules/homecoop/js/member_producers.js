(function($) {
  Drupal.ajax.prototype.commands.SetExisting = function(ajax, response, status) {
    if (response.success) {
      document.getElementById('existing_' + response.prid).value = 1;
    }    
  };
  
}(jQuery));

function SetActionParams(nProducer) {
  document.getElementById('hidProducer').value = nProducer;
}