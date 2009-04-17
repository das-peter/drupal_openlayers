<?php
// $Id$

/**
 * @file
 * This file holds the functions for the openlayers Defaults settings.
 */

/**
 * Menu callback; displays the openlayers module default settings page.
 *
 * @ingroup forms
 */
function openlayers_admin_default_settings($form_state) {
  // Get current default map
  $map = openlayers_render_map(array());
  $defaults = variable_get('openlayers_defaults_form', array());

  // Get form defaults
  // @@TODO: find an easy way to get system map defaults into this array
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
 * Menu callback; displays the openlayers module default settings page.
 *
 * @ingroup forms
 */
function openlayers_admin_default_settings_submit($form, &$form_state) {
  // Save into a system variable
  if ($form_state['values']['op'] == t('Save')) {
    // Convert values to map array
    $map = openlayers_convert_form_to_map($form_state['values']);
    variable_set('openlayers_defaults', $map);
    // Save values for easy defaults
    variable_set('openlayers_defaults_form', $form_state['values']);
  }
}