<?php
// $Id$

/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Layer Switcher Behavior
 */
class openlayers_behavior_layerswitcher extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layerswitcher' => '',
      'descending' => FALSE,
    );
  }

  function js_dependency() {
    return array('OpenLayers.Control.LayerSwitcher');
  }

  function options_form($defaults) {
    return array(
      'descending' => array(
        '#type' => 'checkbox',
        '#title' => t('Show layers in descending order'),
        '#description' => t('From higher Z-index down'),
        '#default_value' => isset($defaults['descending']) ? $defaults['descending'] : FALSE 
      )
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') .'/includes/behaviors/js/openlayers_behavior_layerswitcher.js');
    return $this->options;
  }
}
