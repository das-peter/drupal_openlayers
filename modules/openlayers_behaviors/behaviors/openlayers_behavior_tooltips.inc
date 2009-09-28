<?php
// $Id$

/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Tooltip Behavior
 */
class openlayers_behavior_tooltips extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'tooltips' => '',
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers_behaviors') .'/behaviors/js/openlayers_behavior_tooltips.js');
    return $this->options;
  }
}
