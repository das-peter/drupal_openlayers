<?php
/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Scaleline Behavior
 */
class openlayers_behavior_scaleline extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'scaleline' => '',
    );
  }

  function js_dependency() {
    return array('OpenLayers.Control.ScaleLine');
  }

  function options_form($defaults = array()) {
    return array();
  }

  function attached() {
    return array(
      'js' => array(
        drupal_get_path('module', 'openlayers') . '/plugins/behaviors/openlayers_behavior_scaleline.js'
      )
    );
  }
}
