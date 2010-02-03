<?php
// $Id$

/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Attribution Behavior
 */
class openlayers_behavior_zoomtolayer extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'point_zoom_level' => '5',
    );
  }

  function options_form($defaults) {
    return array(
      'point_zoom_level' => array(
        '#type' => 'textfield',
        '#default_value' => ($defaults['point_zoom_level']) ? 
          $defaults['point_zoom_level'] : 5,
        '#size' => 5,
        '#title' => t('Point Zoom Level')
      )
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') .'/includes/behaviors/js/openlayers_behavior_zoomtolayer.js');
    return $this->options;
  }
}
