<?php

abstract class openlayers_object implements openlayers_object_interface {

  public $machine_name;
  private $name;
  private $description;
  public $class;
  public $options = array();
  private $plugin = NULL;
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
      'options' => array()
    );
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

    $this->class = get_class($this);
    $this->plugin = ctools_get_plugins('openlayers', $this->getType(), get_class($this));

    if (empty($this->machine_name)) {
      $this->machine_name = drupal_html_id($this->getType().'-'.time());
    }
  }

  public function options_form(&$form, &$form_state) {return array();}

  public function options_form_validate($form, &$form_state) {}

  public function options_form_submit($form, &$form_state) {}

  public function alterBuild(&$build, $map) {}

  public function getType() {
    list($module, $type) = explode('__', get_class($this));
    if (isset($type)) {
      return $type;
    }
    return FALSE;
  }

  public function develop() {}

  public function clearOption($parents) {
    $ref = &$this->options;

    if (is_string($parents)) {
      $parents = array($parents);
    }

    $last = end($parents);
    reset($parents);
    foreach ($parents as $parent) {
      if (isset($ref) && !is_array($ref)) {
        $ref = array();
      }
      if ($last == $parent) {
        unset($ref[$parent]);
      } else {
        if (isset($ref[$parent])) {
          $ref = &$ref[$parent];
        } else {
          break;
        }
      }
    }
  }

  public function setOption($parents, $value = NULL) {
    $ref = &$this->options;

    if (is_string($parents)) {
      $parents = array($parents);
    }

    foreach ($parents as $parent) {
      if (isset($ref) && !is_array($ref)) {
        $ref = array();
      }
      $ref = &$ref[$parent];
    }
    $ref = $value;
  }

  public function get($prop) {
    return $this->$prop;
  }

  public function getOption($parents, $default_value = NULL) {
    $options = $this->options;

    if (is_string($parents)) {
      $parents = array($parents);
    }

    if (is_array($parents)) {
      $notfound = FALSE;
      foreach($parents as $parent) {
        if (isset($options[$parent])) {
          $options = $options[$parent];
        } else {
          $notfound = TRUE;
          break;
        }
      }
      if (!$notfound) {
        return $options;
      }
    }

    if (is_null($default_value)) {
      return FALSE;
    }

    return $default_value;
  }

  public function attached() {
    if ($plugin = $this->getPlugin()) {
      $file = $plugin['path'] . '/' . get_class($this) . '.js';
      if (file_exists($file)) {
        $this->attached['js'][$file] = array('data' => $file, 'type' => 'file', 'group' => openlayers_config::JS_GROUP, 'weight' => openlayers_config::JS_WEIGHT);
      }
      $file = $plugin['path'] . '/' . get_class($this) . '.css';
      if (file_exists($file)) {
        $this->attached['css'][$file] = array('data' => $file, 'type' => 'file', 'group' => openlayers_config::JS_GROUP, 'weight' => openlayers_config::JS_WEIGHT);
      }
    }

    return $this->attached;
  }

  public function dependencies() {
    return array();
  }

  public function getPlugin() {
    return $this->plugin;
  }

  public function toJSArray() {
    // TODO: find a better solution here.
    return json_decode(json_encode($this), TRUE);
  }

}
