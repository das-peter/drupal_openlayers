<?php
// $Id$

/**
 * @file
 * Google Layer Type
 */

/**
 * OpenLayers Google Layer Type class
 */
class openlayers_layer_type_google extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_type' => 'google',
      'layer_handler' => 'google',
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form() {
    return array();
  }

  /**
   * Layer-type-wide settings form
   */
  function settings_form() {
    return array(
      'openlayers_layers_google_api' => array(
        '#type' => 'textfield',
        '#title' => t('Google API Key'),
        '#default_value' => variable_get('openlayers_layers_google_api', ''),
        '#description' => t('<a href="@google">Obtain an API key from Google for your domain</a>',
          array('@google' => 'http://code.google.com/apis/maps/signup.html'))
      )
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') .'/includes/layer_types/google.js');
    drupal_set_html_head('<script src="'. check_url("http://maps.google.com/maps?file=api&v=2&sensor=false&key=" . variable_get('openlayers_layers_google_api', variable_get('googlemap_api_key', ''))) . '" type="text/javascript"></script>');
    return $this->options;
  }
}
