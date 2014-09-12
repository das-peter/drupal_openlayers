<?php

abstract class openlayers_object {

  public $machine_name;
  public $name;
  public $description;
  public $class;
  public $options = array();
  protected $attached = array();

  function defauts_properties() {
    return array(
      'machine_name' => '',
      'name' => '',
      'description' => '',
      'class' => '',
      'options' => array()
    );
  }

  function options_form() {
    return array();
  }

  function init(stdClass $data) {
    foreach ($this->defauts_properties() as $property => $value) {
      if (isset($data->{$property})) {
        $this->{$property} = $data->$property;
      }
    }

    $this->options = array_replace_recursive((array) $this->options, (array) $data->options);
  }

  public function setOption($key, $value = NULL) {
    if (is_string($key) && !empty($value)) {
      $this->options = array_replace_recursive($this->options, array($key => $value));
    }
    if (is_array($key)) {
      $this->options = array_replace_recursive($this->options, $key);
    }
    return $this;
  }

  public function getOption($key, $default_value = NULL) {
    if (isset($this->options[$key])) {
      return $this->options[$key];
    }
    if (is_null($default_value)) {
      return FALSE;
    }
    return $default_value;
  }

  public function toArray() {
    return json_decode(json_encode($this), TRUE);
  }

  public function attached() {
    if (isset($this->plugin)) {
      $file = $this->plugin['path'] . '/' . $this->class . '.js';
      if (file_exists($file)) {
        $this->attached['js'][$file] = $file;
        unset($this->plugin);
      }
    }

    return $this->attached;
  }

}
