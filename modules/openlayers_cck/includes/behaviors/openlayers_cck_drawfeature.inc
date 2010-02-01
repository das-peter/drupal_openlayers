<?php
// $Id$

/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Layer Switcher Behavior
 */
class openlayers_cck_drawfeature extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'wkt_field_id' => 'edit-field-loc-openlayers-wkt',
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers_cck') .'/includes/behaviors/openlayers_cck_drawfeature.js');
    return $this->options;
  }
}

