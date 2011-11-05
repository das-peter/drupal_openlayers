<?php
/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Ctools plugin definition.
 */
$plugin = array(
  'title' => t('PanZoom'),
  'description' => t('Provides the ability to pan and zoom in the map interface.'),
  'type' => 'map',
  'behavior' => array(
    'class' => 'openlayers_behavior_panzoom',
    'parent' => 'openlayers_behavior',
  ),
);

/**
 * Pan Zoom Bar Behavior
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

  function options_form($defaults) {
    return array(
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') . 
      '/includes/behaviors/js/openlayers_behavior_panzoom.js');
    return $this->options;
  }
}
