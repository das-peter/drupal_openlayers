<?php

abstract class openlayers_object {

  public $machine_name;
  public $name;
  public $description;
  public $class;
  public $options = array();
  protected $attached = array(
    'js' => array(),
    'css' => array(),
    'library' => array(),
    'libraries_load' => array()
  );

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

  function options_form_validate() {}

  function init(array $data) {
    foreach ($this->defauts_properties() as $property => $value) {
      if (isset($data[$property])) {
        $this->{$property} = $data[$property];
      }
    }

    if (isset($data['options'])) {
      $this->options = array_replace_recursive((array) $this->options, (array) $data['options']);
    }

    $this->plugin = ctools_get_plugins('openlayers', $this->getType(), get_class($this));

    if (empty($this->machine_name)) {
      $this->machine_name = drupal_html_id($this->getType().'-'.time());
    }

  }

  public function getType() {
    list($module, $type) = explode('_', get_class($this));
    if (isset($type)) {
      return $type;
    }
    return FALSE;
  }

  public function develop() {}

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
    $options = $this->options;

    if (is_array($key)) {
      $notfound = FALSE;
      foreach($key as $item) {
        if (isset($options[$item])) {
          $options = $options[$item];
        } else {
          $notfound = TRUE;
          break;
        }
      }
      if (!$notfound) {
        return $options;
      }
    }

    if (is_string($key)) {
      if (isset($options[$key])) {
        return $options[$key];
      }
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
        $this->attached['js'][$file] = array('data' => $file, 'type' => 'file', 'group' => OPENLAYERS_JS_GROUP, 'weight' => OPENLAYERS_JS_WEIGHT);
        unset($this->plugin);
      }
    }

    return $this->attached;
  }

  public function dependencies() {
    return array();
  }

}
