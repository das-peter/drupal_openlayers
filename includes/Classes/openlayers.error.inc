<?php

class openlayers_error extends openlayers_object implements openlayers_object_interface {

  var $error_message;

  function __construct() {
    foreach ($this->defauts_properties() as $property => $value) {
      $this->{$property} = $value;
    }
  }

  function defauts_properties() {
    $properties = parent::defauts_properties();
    $properties['error_message'] = 'Error while loading object @machine_name having class @class.';
    return $properties;
  }

  function init(array $data) {
    foreach ($this->defauts_properties() as $property => $value) {
      if (isset($data[$property])) {
        $this->{$property} = $data[$property];
      }
    }

    if (isset($data['options'])) {
      $this->options = array_replace_recursive((array) $this->options, (array) $data['options']);
    }

    watchdog(openlayers_config::WATCHDOG_TYPE, $this->getMessage(), array(), WATCHDOG_ERROR);
    drupal_set_message($this->getMessage(), 'error', FALSE);
  }

  function getMessage() {
    $machine_name = isset($this->machine_name) ? $this->machine_name : 'undefined';
    $class = isset($this->class) ? $this->class : 'undefined';
    $type = isset($this->type) ? $this->type : 'undefined';

    return t($this->error_message, array('@machine_name' => $machine_name, '@class' => $class, '@type' => $type));
  }

  function getSource() {
    return array();
  }

  function getSources() {
    return array();
  }

  function getLayers() {
    return array();
  }

  function getControls() {
    return array();
  }

  function getInteractions() {
    return array();
  }

  function getComponents() {
    return array();
  }

}
