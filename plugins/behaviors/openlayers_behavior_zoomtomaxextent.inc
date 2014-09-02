<?php
/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Zoom to Max Extent Behavior
 */
class openlayers_behavior_zoomtomaxextent extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'zoomtomaxextent' => '',
    );
  }

  function attached() {
    return array(
      'js' => array(
        drupal_get_path('module', 'openlayers') . '/plugins/behaviors/openlayers_behavior_zoomtomaxextent.js'
      )
    );
  }
}
