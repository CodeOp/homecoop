(function($) {
  Drupal.ajax.prototype.commands.AddStorageArea = function(ajax, response, status) {
    if (response.success) {
      var nCount = document.getElementById("hidStorageAreaCount").value;
      nCount++;
      document.getElementById("hidStorageAreaCount").value = nCount;
    }
  };
}(jQuery));
