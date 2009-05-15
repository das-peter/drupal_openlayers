<?php
// $Id$

/**
 * @file
 * This file holds the main Drupal hook functions 
 * and private functions for the openlayers module.
 *
 * @ingroup openlayers
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
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
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
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
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
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
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
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'url' => 'http://tile.openaerialmap.org/tiles/1.0.0/openaerialmap-900913/${z}/${x}/${y}.png',
        'options' => array(
          'sphericalMercator' => TRUE,
        ),
        'events' => array(),
      );
      break;
    
    case 'openlayers_layers_google_street':
      openlayers_layers_include_google_map_api();
      $layer_data = array(
        'id' => $layer,
        'type' => 'Google',
        'name' => $layer_info[$layer]['name'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'params' => array(
          'type' => 'street'
        ),
      );
      break;
    
    case 'openlayers_layers_google_satellite':
      openlayers_layers_include_google_map_api();
      $layer_data = array(
        'id' => $layer,
        'type' => 'Google',
        'name' => $layer_info[$layer]['name'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'params' => array(
          'type' => 'satellite'
        ),
      );
      break;
    
    case 'openlayers_layers_google_hybrid':
      openlayers_layers_include_google_map_api();
      $layer_data = array(
        'id' => $layer,
        'type' => 'Google',
        'name' => $layer_info[$layer]['name'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'params' => array(
          'type' => 'hybrid'
        ),
      );
      break;
    
    case 'openlayers_layers_google_physical':
      openlayers_layers_include_google_map_api();
      $layer_data = array(
        'id' => $layer,
        'type' => 'Google',
        'name' => $layer_info[$layer]['name'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'params' => array(
          'type' => 'physical'
        ),
      );
      break;
    
    case 'openlayers_layers_yahoo_street':
      openlayers_layers_include_yahoo_api();
      $layer_data = array(
        'id' => $layer,
        'type' => 'Yahoo',
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'name' => $layer_info[$layer]['name'],
        'params' => array(
          'type' => 'street'
        ),
      );
      break;
    
    case 'openlayers_layers_yahoo_satellite':
      openlayers_layers_include_yahoo_api();
      $layer_data = array(
        'id' => $layer,
        'type' => 'Yahoo',
        'name' => $layer_info[$layer]['name'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'params' => array(
          'type' => 'satellite'
        ),
      );
      break;
    
    case 'openlayers_layers_yahoo_hybrid':
      openlayers_layers_include_yahoo_api();
      $layer_data = array(
        'id' => $layer,
        'type' => 'Yahoo',
        'name' => $layer_info[$layer]['name'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'params' => array(
          'type' => 'hybrid'
        ),
      );
      break;
    
    case 'openlayers_layers_virtual_earth_street':
      openlayers_layers_include_virtual_earth_api();
      $layer_data = array(
        'id' => $layer,
        'type' => 'VirtualEarth',
        'name' => $layer_info[$layer]['name'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'params' => array(
          'type' => 'street'
        ),
      );
      break;
    
    case 'openlayers_layers_virtual_earth_satellite':
      openlayers_layers_include_virtual_earth_api();
      $layer_data = array(
        'id' => $layer,
        'type' => 'VirtualEarth',
        'name' => $layer_info[$layer]['name'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'params' => array(
          'type' => 'satellite'
        ),
      );
      break;
    
    case 'openlayers_layers_virtual_earth_hybrid':
      openlayers_layers_include_virtual_earth_api();
      $layer_data = array(
        'id' => $layer,
        'type' => 'VirtualEarth',
        'name' => $layer_info[$layer]['name'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'params' => array(
          'type' => 'hybrid'
        ),
      );
      break;
    
    case 'openlayers_layers_osm_mapnik':
      $layer_data = array(
        'id' => $layer,
        'type' => 'XYZ',
        'name' => $layer_info[$layer]['name'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'url' => 'http://tile.openstreetmap.org/${z}/${x}/${y}.png',
      );
      break;
    
    case 'openlayers_layers_osm_tah':
      $layer_data = array(
        'id' => $layer,
        'type' => 'XYZ',
        'name' => $layer_info[$layer]['name'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'url' => 'http://tah.openstreetmap.org/Tiles/tile/${z}/${x}/${y}.png',
      );
      break;
    
    case 'openlayers_layers_osm_cycle':
      $layer_data = array(
        'id' => $layer,
        'type' => 'XYZ',
        'name' => $layer_info[$layer]['name'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'url' => 'http://andy.sandbox.cloudmade.com/tiles/cycle/${z}/${x}/${y}.png',
      );
      break;

    case 'openlayers_layers_osm_4326_hybrid':
      $layer_data = array(
        'id' => $layer,
        'type' => 'WMS',
        'name' => $layer_info[$layer]['name'],
        'projection' => $layer_info[$layer]['projection'],
        'baselayer' => $layer_info[$layer]['baselayer'],
        'url' => 'http://oam.hypercube.telascience.org/tiles',
        'params' => array(
          'layers' => 'osm-4326-hybrid',
        ),
        'options' => array(
          'isBaseLayer' => false,
          'buffer' => 1,
        ),
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


function openlayers_layers_process_geo_data_layers($layer = NULL) {
  $table_desc = geo('table_desc', $layer);
  $attribute_cols = array();
  foreach ($table_desc as $cname => $cinfo){
    if ($cinfo['type'] == 'geometry'){
      $geometry_col = $cname;
      $srid = $cinfo['srid'];
    }
    else $attribute_cols[] = $cname;
  }
  
  $res = db_query("SELECT asText($geometry_col) as $geometry_col, ".implode(',',$attribute_cols)." from {$layer}");
  $features = array();
  while ($row = db_fetch_array($res)){
    $attributes = array();
    foreach ($attribute_cols as $attr_name){
      $attr_val = $row[$attr_name];
      $attributes[$attr_name] = $attr_val;
    }
    
    $features[] = array(
      'wkt' => $row[$geometry_col],
      'attributes' => $attributes,
      'projection' => $srid,
    );
  }
  
  $layer_data = array(
    'id' => $layer,
    'type' => 'Vector',
    // @@TODO: Actually have a real name
    'name' => $layer,
    'features' => $features,
  );
  
  return $layer_data;
}


/**
 * The following functions are more temporary and used for including libraries for certain layers
 */
function openlayers_layers_include_google_map_api() {
  static $included = FALSE;
  if (!$included) {
    // Include Google Map API JS (maybe getting key from GMap)
    drupal_set_html_head('<script src="'. check_url("http://maps.google.com/maps?file=api&v=2&sensor=false&key=".variable_get('openlayers_layers_google_api', variable_get('googlemap_api_key', ''))) .'" type="text/javascript"></script>');
    $included = TRUE;
  }
}

function openlayers_layers_include_yahoo_api() {
  static $included = FALSE;
  if (!$included) {
    drupal_set_html_head('<script src="'. check_url("http://api.maps.yahoo.com/ajaxymap?v=3.0&appid=".variable_get('openlayers_layers_yahoo_api','')) .'" type="text/javascript"></script>');
    $included = TRUE;
  }
}

function openlayers_layers_include_virtual_earth_api() {
  static $included = FALSE;
  if (!$included) {
    drupal_set_html_head('<script src="'. check_url("http://dev.virtualearth.net/mapcontrol/mapcontrol.ashx?v=6.1") .'" type="text/javascript"></script>');
    $included = TRUE;
  }
}