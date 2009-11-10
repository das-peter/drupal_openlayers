<?php
class openlayers_layer_type_cloudmade extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_type' => 'osm',
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form() {
    return array(
      'base_url' => array(
        '#type' => 'textfield',
        '#title' => t('Base URL'),
      )
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    return $this->options;
  }
}
