<?php
// $Id$

/**
 * @file
 *
 * OpenLayers CloudMade layer type
 */
class openlayers_layers_type_cloudmade extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_type' => 'cloudmade',
      'layer_handler' => 'cloudmade',
      'key' => variable_get('openlayers_layers_cloudmade_api', ''),
      'projection' => array('900913'),
      'baselayer' => TRUE,
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form() {
    return array(
      'style_id' => array(
        '#type' => 'textfield',
        '#title' => t('Style ID'),
        '#default_value' => $this->data['style_id']
      ),
      'layer_type' => array(
        '#type' => 'hidden',
        '#value' => 'openlayers_layers_type_cloudmade'
      ),
    );
  }

  /**
   * Layer-type-wide settings form
   */
  function settings_form() {
    return array(
      'openlayers_layers_cloudmade_api' => array(
        '#type' => 'textfield',
        '#title' => t('CloudMade API Key'),
        '#default_value' => variable_get('openlayers_layers_cloudmade_api', ''),
      ),
      'openlayers_layers_cloudmade_js' => array(
        '#type' => 'textfield',
        '#title' => t('CloudMade Javascript Location'),
        '#default_value' => variable_get('openlayers_layers_cloudmade_js', ''),
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers_layers') .'/includes/layer_types/cloudmade.js');
    drupal_add_js(variable_get('openlayers_layers_cloudmade_js', ''));
    return $this->options;
  }
}
