<?php
/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Ctools plugin definition.
 */
$plugin = array(
  'title' => t('Keyboard Defaults'),
  'description' => t('Provides keyboard shortcuts to pan and zoom the map.'),
  'type' => 'layer',
  'behavior' => array(
    'class' => 'openlayers_behavior_keyboarddefaults',
    'parent' => 'openlayers_behavior',
  ),
);

/**
 * Keyboard Defaults Behavior
 */
class openlayers_behavior_keyboarddefaults extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'keyboarddefaults' => '',
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') . 
      '/includes/behaviors/js/openlayers_behavior_keyboarddefaults.js');
    return $this->options;
  }
}
