<?php
// $Id$

/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Zoom to Layer Behavior
 */
class openlayers_behavior_zoomtolayer extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'zoomtolayer' => '',
    );
  }
  
  /**
  * Settings form.
  */
  function options_form() {
    $options = $this->map['layers'];
    $form = array();
    $form['zoomtolayer'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#description' => t('Select layer to zoom to when map is loaded'),
      '#default_value' => $this->options['zoomlayer'],
    );
    return $form;
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers_behaviors') .'/behaviors/js/openlayers_behavior_zoomtolayer.js');
    return $this->options;
  }
}