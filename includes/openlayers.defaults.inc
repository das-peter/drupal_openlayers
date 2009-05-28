<?php
// $Id$

/**
 * @file
 * This file holds the functions for the openlayers Defaults settings.
 *
 * @ingroup openlayers
 */

/**
 * Menu callback; Displays the openlayers module default settings page.
 */
function openlayers_admin_default_settings($form_state) {
  // Get current default map
  $map = openlayers_render_map(array());
  // Get system default maps
  $map_defaults = variable_get('openlayers_defaults', array());
  $map_system = _openlayers_get_map_defaults();
  $map_merged = openlayers_merge_maps($map_system, $map_defaults);
  // Convert to form defaults
  $defaults = openlayers_convert_map_to_form($map_merged);
  
  // Get default form
  $form = openlayers_map_form($defaults);
  
  // Add submit button
  $form['submit'] = array(
    '#type' => 'submit', 
    '#value' => t('Save')
  );

  // Display a map for reference
  $form['openlayers_map'] = array(
    '#type' => 'item',
    '#title' => t('Example Map'),
    '#description' => t('Save these settings to see an updated map.'),
    '#value' => $map['themed'],
    '#weight' => -100,
  );
  
  return $form;
}

/**
 * Form submit for openlayers_admin_default_settings form
 */
function openlayers_admin_default_settings_submit($form, &$form_state) {
  // Save into a system variable
  if ($form_state['values']['op'] == t('Save')) {
    // Convert values to map array
    $map = openlayers_convert_form_to_map($form_state['values']);
    variable_set('openlayers_defaults', $map);
  }
}