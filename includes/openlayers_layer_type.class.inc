<?php
/**
 * We define base classes in the core module.
 * All other parent classes can be autoloaded through ctools.
 */
class openlayers_layer_type {
  var $options, $map;

  function __construct($layer = array(), $map = array()) {
    foreach (array('name', 'title', 'description', 'data', 'export_type', 'export_module', 'in_code_only', 'type') as $k) {
      if (isset($layer->{$k})) {
        $this->{$k} = $layer->{$k};
      }
    }
    if (isset($this->data) && is_array($this->data)) {
      $this->data += $this->options_init();
    }
    $this->map = $map;
  }

  function options_init() {
    return array();
  }

  function options_form($defaults = array()) {
    return array();
  }

  /**
   * @return
   *   A version of this layer_type which can be saved,
   *   when attempting to save a modified layer
   */
  function to_record() {
    return array(
      'name' => $this->name,
      'description' => $this->description,
      'title' => $this->title,
      'data' => $this->data
    );
  }

  /**
   * @return
   *   Success value on saving this layer
   */
  function save() {
    if (!empty($this->name)) {
      return (db_select('openlayers_layers')
        ->fields('openlayers_layers', array('name'))
        ->condition('name', $this->name)
        ->execute()
        ->fetchCol()) ?
        drupal_write_record('openlayers_layers', $this->to_record(), 'name') :
        drupal_write_record('openlayers_layers', $this->to_record());
    }
  }

  function render(&$map) {}
}
