(function($) {
  Drupal.ajax.prototype.commands.Activate = function(ajax, response, status) {
    var ctlAction = document.getElementById('select_action');
    if (response.success) {
      ctlAction.options[1].disabled = true;
    }
    ctlAction.selectedIndex = 0;
  };
  
  
  Drupal.ajax.prototype.commands.Deactivate = function(ajax, response, status) {
    var ctlAction = document.getElementById('select_action');
    if (response.success) {
      ctlAction.options[1].disabled = false;
    }
    ctlAction.selectedIndex = 0;
  };
}(jQuery));

function SetActivateOptionAsDisabled() {
  var ctlAction = document.getElementById('select_action');
  ctlAction.options[1].disabled = true;
}