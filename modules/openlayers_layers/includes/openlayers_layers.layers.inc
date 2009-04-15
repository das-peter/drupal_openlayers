<?php
// $Id$

/**
 * @file
 * This file holds the main Drupal hook functions 
 * and private functions for the openlayers module.
 */
 
/**
 * Process Layers
 *
 * Call back to process layers provided by the
 * openlayers_layers_openlayers_layers_info() function
 *
 * @param $layer
 *   String ID for the layer
 * @return
 *   Array formated for an OpenLayers map layer
 */
function openlayers_layers_process_layers($layer = NULL) {
  $layer_data = array();
  
  // Make sure layer is a string
  if (!is_string($layer)) {
    return FALSE;
  }
  
  // Get info array to reference title
  $layer_info = openlayers_layers_openlayers_layers_info();
  
  // Determine what data to send back
  switch ($layer) {
    case 'openlayers_layers_jpl_nasa_wms':
      $layer_data = array(
        'id' => $layer,
        'type' => $layer_info[$layer]['name'],
        'url' => 'http://wms.jpl.nasa.gov/wms.cgi',
        'params' => array(
          'layers' => 'modis,global_mosaic',
        ),
        'options' => array(),
        'events' => array(),
      );
      break
      
    default
      break;
  }
  
  return $layer_data;
}