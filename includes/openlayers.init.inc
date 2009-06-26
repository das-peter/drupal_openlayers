<?php
// $Id: openlayers.init.inc

/**
 * Initialize Default Preset
 *
 * This is the "system defaults" that come with the module.
 * The goal of these defaults is so that a map can be rendered
 * simply by installing the OL API module.
 *
 */
function _openlayers_init_default_presets(){
  // Add default map preset
  $default_map = array(
    'projection' => '4326',
    'width' => 'auto',
    'default_layer' => 'openlayers_default_wms',
    'height' => '300px',
    'center' => array(
      'lat' => '0',
      'lon' => '0',
      'zoom' => '2',
    ),
    'options' => array(
      'displayProjection' => '4326',
    ),
    'controls' => array(
      'LayerSwitcher' => TRUE,
      'Navigation' => TRUE,
      'PanZoomBar' => TRUE,
      'MousePosition' => TRUE,
    ),
  );
  
  $preset = array(
    'preset_name' => 'default',
    'preset_title' => t('Default Map'),
    'preset_description' => t('This is the default map preset that comes with the OpenLayers module.'),
    'preset_data' => $default_map,
  );
  $created_default = openlayers_save_preset($preset);
  
  // Check if created
  if ($created_default == TRUE) {
    drupal_set_message(t('OpenLayers Default Preset created succesfully.'));
    variable_set('openlayers_default_preset_initialized',TRUE);
  }
  else {
    drupal_set_message(t('OpenLayers Default Preset not created succesfully.'), 'error');
  }
  
}