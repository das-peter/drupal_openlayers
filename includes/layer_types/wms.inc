<?php
class openlayers_layer_type_wms extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'serverResolutions' => openlayers_get_resolutions('900913'),
      'maxExtent' => openlayers_get_extent('900913')
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
        '#default_value' => $this->data['base_url']
      ),
      'layername' => array(
        '#type' => 'textfield',
        '#title' => t('Layer Name'),
        '#default_value' => $this->data['layername']
      ),
      'layer_type' => array(
        '#type' => 'hidden',
        '#value' => 'openlayers_layer_type_wms'
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
