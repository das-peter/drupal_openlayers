<?php
// $Id$

/**
 * @file
 * This file holds the functions for the settings forms.
 */
 
/**
 * Get OpenLayers Form
 *
 * Get the form array to customize OpenLayers Maps.  This is a private
 * function for openlayers_map_form
 *
 * @param $defaults
 *   Array of defaults
 * @return
 *   Array of form items
 */
function _openlayers_map_form($defaults = array()) {
  // Names of fields and fieldssets should correspond to the map array
  $form = array();
  
  // Map general properties
  $form['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#description' => t('Please use a CSS Width value.'),
    '#default_value' => $defaults['width'],
    '#maxlength' => 128,
  );
  $form['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#description' => t('Please use a CSS Height value.'),
    '#default_value' => $defaults['height'],
    '#maxlength' => 128,
  );
  
  // Map center properties
  $form['center'] = array(
    '#type' => 'fieldset',
    '#title' => t('Center'),
    '#description' => t('Where the map will center itself initially.'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['center']['lat'] = array(
    '#type' => 'textfield',
    '#title' => t('Latitude'),
    '#description' => t('The latitude or X value for centering.'),
    '#default_value' => $defaults['center']['lat'],
    '#maxlength' => 128,
  );
  $form['center']['lon'] = array(
    '#type' => 'textfield',
    '#title' => t('Longitude'),
    '#description' => t('The longitude or Y value for centering.'),
    '#default_value' => $defaults['center']['lon'],
    '#maxlength' => 128,
  );
  $form['center']['zoom'] = array(
    '#type' => 'textfield',
    '#title' => t('Zoom Level'),
    '#description' => t('The zoom level for centering.'),
    '#default_value' => $defaults['center']['zoom'],
    '#maxlength' => 128,
  );
  
  return $form;
}

/**
 * OpenLayers Form to Map
 *
 * Converst Form submission to map array.
 *
 * @ingroup API
 * @param $values
 *   Array of values to convert
 * @return
 *   Array of form items
 */
function _openlayers_convert_form_to_map($values = array()) {
  $processed = array();
  
  // Take out form values
  // @@TODO: Is this the best way to do this?
  $throw = array('op', 'submit', 'form_build_id', 'form_token', 'form_id');
  foreach ($values as $k => $v) {
    if (!in_array($k, $throw)) {
      $processed[$k] = $v;
    }
  }
    
  return $processed;
}