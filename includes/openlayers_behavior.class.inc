<?php

Interface openlayers_behavior_interface {
  public function __construct($options = array(), $map = array());
  public function js_dependency();
  public function options_init();
  public function options_form($defaults = array());
  public function render(&$map);
}

/**
 * We define base classes in the core module.
 * All other parent classes can be autoloaded through ctools.
 */
class openlayers_behavior implements openlayers_behavior_interface {
  var $options, $map;

  function __construct($options = array(), $map = array()) {
    $this->options = $options + $this->options_init();
    $this->map = $map;
  }

  /*
  * @return array of JavaScript functions required to be defined
  * in order for this function to work
  */
  function js_dependency() {
    return array();
  }

  function options_init() {
    return array();
  }

  /*
  * @param $defaults default values for the form as an array
  * @return a FormAPI form
  */
  function options_form($defaults = array()) {
    return array();
  }

  function render(&$map) {}
}
