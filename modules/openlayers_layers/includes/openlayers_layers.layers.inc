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
 * @param $map
 *   Map array
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
      
    case 'openlayers_layers_nasa_daily_planet':
      $layer_data = array(
        'id' => $layer,
        'type' => 'WMS',
        'name' => $layer_info[$layer]['name'],
        'url' => 'http://wms.jpl.nasa.gov/wms.cgi?',
        'params' => array(
          'layers' => 'daily_planet',
          'format' => 'image/png'
        ),
        'options' => array(),
        'events' => array(),
      );
      break;
    
    case 'openlayers_layers_nasa_blue_marble':
      $layer_data = array(
        'id' => $layer,
        'type' => 'WMS',
        'name' => $layer_info[$layer]['name'],
        'url' => 'http://wms.jpl.nasa.gov/wms.cgi?',
        'params' => array(
          'layers' => 'BMNG',
          'format' => 'image/png'
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
    
    case 'openlayers_layers_google_street':
      $layer_data = array(
        'id' => $layer,
        'type' => 'Google',
        'name' => $layer_info[$layer]['name'],
        'params' => array(
          'type' => 'street'
        )
      );
      break;
    
    case 'openlayers_layers_google_satellite':
      $layer_data = array(
        'id' => $layer,
        'type' => 'Google',
        'name' => $layer_info[$layer]['name'],
        'params' => array(
          'type' => 'satellite'
        )
      );
      break;
    
    case 'openlayers_layers_google_hybrid':
      $layer_data = array(
        'id' => $layer,
        'type' => 'Google',
        'name' => $layer_info[$layer]['name'],
        'params' => array(
          'type' => 'hybrid'
        )
      );
      break;
    
    case 'openlayers_layers_google_physical':
      $layer_data = array(
        'id' => $layer,
        'type' => 'Google',
        'name' => $layer_info[$layer]['name'],
        'params' => array(
          'type' => 'physical'
        )
      );
      break;
    
    case 'openlayers_layers_yahoo_street':
      $layer_data = array(
        'id' => $layer,
        'type' => 'Yahoo',
        'name' => $layer_info[$layer]['name'],
        'params' => array(
          'type' => 'street'
        )
      );
      break;
    
    case 'openlayers_layers_yahoo_satellite':
      $layer_data = array(
        'id' => $layer,
        'type' => 'Yahoo',
        'name' => $layer_info[$layer]['name'],
        'params' => array(
          'type' => 'satellite'
        )
      );
      break;
    
    case 'openlayers_layers_yahoo_hybrid':
      $layer_data = array(
        'id' => $layer,
        'type' => 'Yahoo',
        'name' => $layer_info[$layer]['name'],
        'params' => array(
          'type' => 'hybrid'
        )
      );
      break;
    
    case 'openlayers_layers_virtual_earth_street':
      $layer_data = array(
        'id' => $layer,
        'type' => 'VirtualEarth',
        'name' => $layer_info[$layer]['name'],
        'params' => array(
          'type' => 'street'
        )
      );
      break;
    
    case 'openlayers_layers_virtual_earth_satellite':
      $layer_data = array(
        'id' => $layer,
        'type' => 'VirtualEarth',
        'name' => $layer_info[$layer]['name'],
        'params' => array(
          'type' => 'satellite'
        )
      );
      break;
    
    case 'openlayers_layers_virtual_earth_hybrid':
      $layer_data = array(
        'id' => $layer,
        'type' => 'VirtualEarth',
        'name' => $layer_info[$layer]['name'],
        'params' => array(
          'type' => 'hybrid'
        )
      );
      break;
    
    case 'openlayers_layers_osm_mapnik':
      $layer_data = array(
        'id' => $layer,
        'type' => 'OSM',
        'name' => $layer_info[$layer]['name'],
        'url' => 'http://tile.openstreetmap.org'
      );
      break;
    
    case 'openlayers_layers_osm_tah':
      $layer_data = array(
        'id' => $layer,
        'type' => 'OSM',
        'name' => $layer_info[$layer]['name'],
        'url' => 'http://tah.openstreetmap.org/Tiles/tile'
      );
      break;
    
    case 'openlayers_layers_osm_cycle':
      $layer_data = array(
        'id' => $layer,
        'type' => 'OSM',
        'name' => $layer_info[$layer]['name'],
        'url' => 'http://andy.sandbox.cloudmade.com/tiles/cycle'
      );
      break;
   
   case 'openlayers_layers_local_kml':
      $layer_data = array(
        'id' => $layer,
        'type' => 'KML',
        'name' => $layer_info[$layer]['name'],
        'url' => url('kml/node'),
      );
      break;
     
    default:
      break;
  }
  
  return $layer_data;
}
