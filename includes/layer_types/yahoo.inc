<?php
// $Id$

/**
 * @file
 * Yahoo Layer Type
 */

/**
 * OpenLayers Yahoo Layer Type class
 */
class openlayers_layer_type_yahoo extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_type' => 'yahoo',
      'layer_handler' => 'yahoo',
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form() {
    return array();
  }

  function settings_form() {
    return array(
      'openlayers_layers_yahoo_api' => array(
        '#type' => 'textfield',
        '#title' => t('Yahoo API Key'),
        '#default_value' => variable_get('openlayers_layers_yahoo_api', ''),
      )
    );
  }


  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') .'/includes/layer_types/yahoo.js');
    drupal_set_html_head('<script src="' . check_url("http://api.maps.yahoo.com/ajaxymap?v=3.0&appid=" . variable_get('openlayers_layers_yahoo_api', '')) . '" type="text/javascript"></script>');
    return $this->options;
  }
}
