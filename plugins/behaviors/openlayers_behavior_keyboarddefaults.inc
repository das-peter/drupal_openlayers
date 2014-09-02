<?php
/**
 * @file
 * Implementation of OpenLayers behavior.
 */

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

  function attached() {
    return array(
      'js' => array(
        drupal_get_path('module', 'openlayers') . '/plugins/behaviors/openlayers_behavior_keyboarddefaults.js'
      )
    );
  }
}
