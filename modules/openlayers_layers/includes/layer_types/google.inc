<?php
class openlayers_layer_type_google extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_type' => 'google',
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
      'base_url' => array(
        '#type' => 'textfield',
        '#title' => t('Google API Key'),
      )
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_set_html_head('<script src="'. check_url("http://maps.google.com/maps?file=api&v=2&sensor=false&key=" . variable_get('openlayers_layers_google_api', variable_get('googlemap_api_key', ''))) . '" type="text/javascript"></script>');
    return $this->options;
  }
}
