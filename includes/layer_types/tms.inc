<?php
// $Id$

/**
 * @file
 * TMS Layer Type
 */
 

class openlayers_layer_type_tms extends openlayers_layer_type {

  function __construct($layer = array(), $map = array()) {
    parent::__construct($layer, $map);
    if ($this->data) {
      $this->data += $this->options_init();
    }
    else {
      $this->data = $this->options_init();
    }
  }

  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'serverResolutions' => openlayers_get_resolutions('900913'),
      'maxExtent' => openlayers_get_extent('900913'),
      'projection' => array('900913'),
      'baselayer' => TRUE,
      'layer_handler' => 'tms',
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
      'resolutions' => array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#options' => array_combine(openlayers_get_resolutions('900913'), range(0, 18)),
        '#title' => t('Zoom Level Range'),
        '#default_value' => $this->data['resolutions'],
      ),
      'layer_type' => array(
        '#type' => 'hidden',
        '#value' => 'openlayers_layer_type_tms'
      ),
      'projection' => array(
        array(
        '#type' => 'hidden',
        '#value' => '900913'
        )
      )
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') .'/includes/layer_types/tms.js');
    return $this->options;
  }
}
