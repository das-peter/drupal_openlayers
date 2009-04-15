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
  // Get sensible module defaults
  $module_defaults = _openlayers_get_map_defaults();
  // Get saved defaults
  $saved_defaults = variable_get('openlayers_defaults', array());
  // Merge saved and sensible defaults
  $defaults = openlayers_merge_maps($module_defaults, $saved_defaults);

  // Get form
  $form = openlayers_map_form($defaults);
  
  // Add submit button
  $form['submit'] = array(
    '#type' => 'submit', 
    '#value' => t('Save')
  );

  // We should display a map for reference
  $map = openlayers_render_map(array());
  $form['openlayers_map'] = array(
    '#type' => 'item',
    '#title' => t('Example Map'),
    '#description' => t('Save these settings to see an updated map.'),
    '#value' => '<div id="'. $map['id'] .'"></div>',
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
  }
}