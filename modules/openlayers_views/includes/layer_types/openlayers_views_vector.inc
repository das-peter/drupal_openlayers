<?php

class openlayers_layer_type_openlayers_views_vector extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_type' => 'openlayers_layer_type_openlayers_views_vector',
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
   * Render.
   */
  function render(&$map) {
    return $this->options;
  }
}
