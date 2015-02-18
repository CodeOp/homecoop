function ClickDefaultRadio(id) {
  alert('event click. value before:' + id + ':' + document.getElementById(id).value);
  document.getElementById(id).value = (document.getElementById(id).value == 1? 0 : 1);
  alert('event click. value after:' + document.getElementById(id).value);
}
