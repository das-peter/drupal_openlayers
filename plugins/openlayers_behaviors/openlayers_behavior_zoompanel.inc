<?php
/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Ctools plugin definition.
 */
$plugin = array(
  'title' => t('Zoom Panel'),
  'description' => t('Provides a Zoom In, Zoom Out, and Zoom to Max Extent Button'),
  'type' => 'map',
  'behavior' => array(
    'class' => 'openlayers_behavior_zoompanel',
    'parent' => 'openlayers_behavior',
  ),
);

/**
 * Zoom Panel Behavior
 */
class openlayers_behavior_zoompanel extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'panzoom' => '',
    );
  }

  function js_dependency() {
    return array(
      'OpenLayers.Control.ZoomPanel'
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') . 
      '/includes/behaviors/js/openlayers_behavior_zoompanel.js');
    return $this->options;
  }
}
