<?php
/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Zoom Box Behavior
 */
class openlayers_behavior_zoombox extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'zoombox' => '',
    );
  }

  function attached() {
    return array(
      'js' => array(
        drupal_get_path('module', 'openlayers') . '/plugins/behaviors/openlayers_behavior_zoombox.js'
      )
    );
  }
}
