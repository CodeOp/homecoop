<?php

class codeop_util_handler_list_field extends views_handler_field {
    
  function render($values) {    
    $value = $this->get_value($values);
    if (isset($this->definition['list']) && isset($this->definition['list'][$value])) {
      return $this->definition['list'][$value];
    }
    return $value;
  }
}