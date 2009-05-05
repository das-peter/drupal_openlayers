<?php
// $Id$

/**
 * @file
 * This file contains layer instances for the default openlayers WMS
 *
 */

/**
 * Process Layers
 *
 * Call back to process layers provided by the
 * openlayers_openlayers_layers_info() function
 *
 * @param $layer
 *   String ID for the layer
 * @return
 *   Array formated for an OpenLayers map layer
 */
function openlayers_process_layers($layer = NULL) {
  $layer_data = array();
  
  // Make sure layer is a string
  if (!is_string($layer)) {
    return FALSE;
  }
  
  // Get info array to reference title
  $layer_info = openlayers_openlayers_layers_info();
  
  // Determine what data to send back
  switch ($layer) {
    case 'openlayers_default_wms':
      $layer_data = array(
        'id' => $layer,
        'type' => 'WMS',
        'name' => $layer_info[$layer]['name'],
        'description' => $layer_info[$layer]['description'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'url' => 'http://labs.metacarta.com/wms/vmap0',
        'params' => array(
          'layers' => 'basic',
        ),
        'options' => array(),
        'events' => array(),
      );
      break;
     
    default:
      break;
  }
  
  return $layer_data;
}
