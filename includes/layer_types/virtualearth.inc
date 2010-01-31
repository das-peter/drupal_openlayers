<?php
// $Id$

/**
 * @file
 *
 * OpenLayers VirtualEarth layer type
 */

/**
 * OpenLayers VirtualEarth Layer Type class
 */
class openlayers_layer_type_virtualearth extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_type' => 'virtualearth',
      'layer_handler' => 'virtualearth',
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form() {
    return array(

    );
  }

  /**
   * Layer-type-wide settings form
   */
  function settings_form() {
    return array(
      'openlayers_layers_virtualearth_api' => array(
        '#type' => 'textfield',
        '#title' => t('VirtualEarth API Key'),
        '#default_value' => variable_get('openlayers_layers_virtualearth_api', ''),
      )
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers_layers') .'/includes/layer_types/virtualearth.js');
    drupal_set_html_head('<script src="' . check_url("http://dev.virtualearth.net/mapcontrol/mapcontrol.ashx?v=6.1") . '" type="text/javascript"></script>');
    return $this->options;
  }
}
