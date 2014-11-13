(function($) {
  Drupal.ajax.prototype.commands.Activate = function(ajax, response, status) {
    var ctlAction = document.getElementById('select_action');
    if (response.success && ctlAction.options.length == 3) {
      ctlAction.remove(1);
    }
    ctlAction.selectedIndex = 0;
  };
  
  
  Drupal.ajax.prototype.commands.Deactivate = function(ajax, response, status) {
    var ctlAction = document.getElementById('select_action');
    if (response.success && ctlAction.options.length == 2) {
      var optDeactivate = new Option(ctlAction.options[1].text, ctlAction.options[1].value);
      ctlAction.options[1] = new Option(Drupal.settings.homecoop.ActivateDesc,
                                          Drupal.settings.homecoop.ActivateCode);
      ctlAction.options[2] = optDeactivate;
    }
    ctlAction.selectedIndex = 0;
  };
}(jQuery));