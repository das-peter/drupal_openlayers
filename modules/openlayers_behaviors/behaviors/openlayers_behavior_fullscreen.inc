<?php
// $Id$

/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Fullscreen Behavior
 */
class openlayers_behavior_fullscreen extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'fullscreen' => '',
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_css(drupal_get_path('module', 'openlayers_behaviors') .'/openlayers_behaviors.css', 'module');
    drupal_add_js(drupal_get_path('module', 'openlayers_behaviors') .'/behaviors/js/openlayers_behavior_fullscreen.js');
    return $this->options;
  }
}
