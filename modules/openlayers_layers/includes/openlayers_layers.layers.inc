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
    case 'openlayers_layers_nasa_global_mosaic':
      $layer_data = array(
        'id' => $layer,
        'type' => 'WMS',
        'name' => $layer_info[$layer]['name'],
        'url' => 'http://t1.hypercube.telascience.org/cgi-bin/landsat7',
        'params' => array(
          'layers' => 'landsat7',
        ),
        'options' => array(),
        'events' => array(),
      );
      break;
      
    case 'openlayers_layers_open_aerial':
      $layer_data = array(
        'id' => $layer,
        'type' => 'XYZ',
        'name' => $layer_info[$layer]['name'],
        'url' => 'http://tile.openaerialmap.org/tiles/1.0.0/openaerialmap-900913/${z}/${x}/${y}.png',
        'options' => array(
          'sphericalMercator' => TRUE,
        ),
        'events' => array(),
      );
      break;
      
    default:
      break;
  }

  return $layer_data;
}