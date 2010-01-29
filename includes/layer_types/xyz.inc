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
        '#default_value' => $this->data['base_url']
      ),
      'layer_type' => array(
        '#type' => 'hidden',
        '#value' => 'openlayers_layer_type_xyz'
      ),
      'resolutions' => array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#options' => array_combine(
          array_map(strval, openlayers_get_resolutions('900913')), 
          range(0, 18)),
        '#title' => t('Zoom Level Range'),
        '#default_value' => ($this->data['resolutions']) ? 
                              $this->data['resolutions'] : 
                              array_map(strval, openlayers_get_resolutions('900913'))
      ),
      'projection' =>
        array(
         '0' => array(
          '#type' => 'hidden',
          '#value' => '900913',
        ),
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
