<?php
/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Pan Zoom Behavior
 */
class openlayers_behavior_panzoom extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'panzoom' => '',
    );
  }

  function options_form($defaults = array()) {
    return array(
    );
  }

  function attached() {
    return array(
      'js' => array(
        drupal_get_path('module', 'openlayers') . '/plugins/behaviors/openlayers_behavior_panzoom.js'
      )
    );
  }
}
