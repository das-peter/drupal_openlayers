<?php
class openlayers_layer_type_virtualearth extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_type' => 'virtualearth',
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form() {
    return array(
      'base_url' => array(
        '#type' => 'textfield',
        '#title' => t('VirtualEarth API Key'),
      )
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_set_html_head('<script src="' . check_url("http://dev.virtualearth.net/mapcontrol/mapcontrol.ashx?v=6.1") . '" type="text/javascript"></script>');
    return $this->options;
  }
}
