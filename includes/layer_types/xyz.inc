<?php
// $Id$

/**
 * @file
 * XYZ Layer Type
 * http://dev.openlayers.org/docs/files/OpenLayers/Layer/XYZ-js.html
 */
 
class openlayers_layer_type_xyz extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'serverResolutions' => openlayers_get_resolutions('900913'),
      'maxExtent' => openlayers_get_extent('900913'),
      'layer_handler' => 'xyz'
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
    drupal_add_js(drupal_get_path('module', 'openlayers') .'/includes/layer_types/xyz.js');
    return $this->options;
  }
}
