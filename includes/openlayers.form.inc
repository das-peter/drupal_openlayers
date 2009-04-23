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
  // Get layers options
  $layers = openlayers_layers_get_info();
  // @@TODO: Best way
  foreach ($layers as $k => $v) {
    $layers[$k] = $v['name'];
  }
  
  // Form Propertieis
  $form['#tree'] = TRUE;
  
  $form['projection'] = array(
    '#type' => 'textfield',
    '#title' => t('Projection'),
    '#description' => t('The EPSG code of the '.l('geographical projection', 'http://en.wikipedia.org/wiki/Map_projection').' for your map. You will most likely want to use either 4326 for lat/lon coordinates, or 900913 to use Google and other web service provider base layers.'),
    '#default_value' => $defaults['projection'],
    '#maxlength' => 6
  );
  
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
  
  // Map options properties
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Options'),
    '#description' => t('Set additional options'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['options']['displayProjection'] = array(
    '#type' => 'textfield',
    '#title' => t('Display Projection'),
    '#description' => t('This is the projection that is presented to your users as the interface for viewing / editing location data. You will most likely want use 4326 for lat/lon coordinates.'),
    '#default_value' => $defaults['options']['displayProjection'],
    '#maxlength' => 6
  );
  $form['options']['maxResolution'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum Resolution'),
    '#description' => t('The maximum number of pixels / map unit at the highest zoom.'),
    '#default_value' => $defaults['options']['maxResolution'],
  );
  $form['options']['maxExtent'] = array(
    '#type' => 'fieldset',
    '#title' => t('Maximum Extent'),
    '#description' => t('Set the bounds for the edges of your map. Set them according to the units of your projection.'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['options']['maxExtent']['left'] = array(
    '#type' => 'textfield',
    '#title' => t('Left'),
    '#default_value' => $defaults['options']['maxExtent']['left'],
  );
  $form['options']['maxExtent']['right'] = array(
    '#type' => 'textfield',
    '#title' => t('Right'),
    '#default_value' => $defaults['options']['maxExtent']['right'],
  );
  $form['options']['maxExtent']['bottom'] = array(
    '#type' => 'textfield',
    '#title' => t('Bottom'),
    '#default_value' => $defaults['options']['maxExtent']['bottom'],
  );
  $form['options']['maxExtent']['top'] = array(
    '#type' => 'textfield',
    '#title' => t('Top'),
    '#default_value' => $defaults['options']['maxExtent']['top'],
  );
  
  // Map layer properties
  $form['layers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layers'),
    '#description' => t('Layer settings.'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['layers']['available_layers'] = array(
    '#type' => 'select',
    '#title' => t('Available Layers'),
    '#description' => t('Available layers on the map. This list is determined by the projection you select for your map.'),
    '#options' => $layers,
    '#multiple' => TRUE,
    '#default_value' => $defaults['layers']['available_layers'],
  );
  $form['layers']['default_layer'] = array(
    '#type' => 'select',
    '#title' => t('Default Base Layer'),
    '#description' => t('The default layer to use when rendering maps.  This will be included whether it is in the available layers or not.'),
    '#options' => $layers,
    '#default_value' => $defaults['layers']['default_layer'],
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
  
  // Go through layers (could be better way to do this)
  $layers = array();
  $layers = array_filter($values['layers']['available_layers']);
  // @@BUG: This shouldn't be here, it should be in openlayers_map_render. It currently will include the default layer even if a different "default_layer" is defined in the downstream map array.
  if (!in_array($values['layers']['default_layer'], $values['layers']['available_layers']) && ($values['layers']['default_layer'])) {
    $layers[$values['layers']['default_layer']] = $values['layers']['default_layer'];
  }
  $processed['layers'] = $layers;

  return $processed;
}