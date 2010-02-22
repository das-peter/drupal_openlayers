<?php
// $Id$

/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Vector Layer Behavior
 */
class openlayers_cck_vector_layer extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'features' => '',
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers_cck') .'/includes/behaviors/openlayers_cck_vector_layer.js');
    return $this->options;
  }
}
