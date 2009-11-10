<?php
class openlayers_layer_type_yahoo extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_type' => 'yahoo',
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form() {
    return array(
      'base_url' => array(
        '#type' => 'textfield',
        '#title' => t('Yahoo API Key'),
      )
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_set_html_head('<script src="' . check_url("http://api.maps.yahoo.com/ajaxymap?v=3.0&appid=" . variable_get('openlayers_layers_yahoo_api', '')) . '" type="text/javascript"></script>');
    return $this->options;
  }
}
