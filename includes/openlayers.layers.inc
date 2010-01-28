<?php
// $Id$

/**
 * @file
 *
 * OpenLayers default packaged layers
 */
function _openlayers_openlayers_layers_info() {
  $layers = array();
  
  // OpenStreetMap Mapnik
  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'osm_mapnik';
  $layer->title = t('OSM Mapnik');
  $layer->description = t('OSM Mapnik.  Needs better description.');
  $layer->data = array(
    'baselayer' => TRUE,
    'attribution' => t('&copy;<a href="@ccbysa">CCBYSA</a> 2010 
      <a href="@openstreetmap">OpenStreetMap.org</a> contributors',
      array(
        '@openstreetmap' => 'http://www.openstreetmap.org/',
        '@ccbysa' => 'http://creativecommons.org/licenses/by-sa/2.0/',
      )
    ),
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layer_type_xyz',
    'url' => 'http://tile.openstreetmap.org/${z}/${x}/${y}.png',
  );
  $layers[$layer->name] = $layer;
  
  // OpenStreetMap Tiles @ Home
  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'openlayers_layers_osm_tah';
  $layer->title = t('OSM Tiles@Home');
  $layer->description = t('OSM Tiles@Home.  Needs better description.');
  $layer->data = array(
    'baselayer' => TRUE,
    'attribution' => t('&copy;<a href="@ccbysa">CCBYSA</a> 2010 
      <a href="@openstreetmap">OpenStreetMap.org</a> contributors',
      array(
        '@openstreetmap' => 'http://www.openstreetmap.org/',
        '@ccbysa' => 'http://creativecommons.org/licenses/by-sa/2.0/',
      )
    ),
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layer_type_xyz',
    'url' => 'http://tah.openstreetmap.org/Tiles/tile/${z}/${x}/${y}.png',
  );
  $layers[$layer->name] = $layer;
  
  // OpenStreetMap Cycling Map
  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'openlayers_layers_osm_cycle';
  $layer->title = t('OSM Cycling Map');
  $layer->description = t('OSM Cycling Map.  Needs better description.');
  $layer->data = array(
    'baselayer' => TRUE,
    'attribution' => t('&copy;<a href="@ccbysa">CCBYSA</a> 2010 
      <a href="@openstreetmap">OpenStreetMap.org</a> contributors',
      array(
        '@openstreetmap' => 'http://www.openstreetmap.org/',
        '@ccbysa' => 'http://creativecommons.org/licenses/by-sa/2.0/',
      )
    ),
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layer_type_xyz',
    'url' => 'http://andy.sandbox.cloudmade.com/tiles/cycle/${z}/${x}/${y}.png',
  );
  $layers[$layer->name] = $layer;
  
  // OpenStreetMap 426 hybrid overlay
  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'openlayers_layers_osm_4326_hybrid';
  $layer->title = t('OSM Overlay');
  $layer->description = t('Semi-transparent hybrid overlay. Projected into WSG84 for use on non spherical-mercator maps.');
  $layer->data = array(
    'baselayer' => FALSE,
    'attribution' => t('&copy;<a href="@ccbysa">CCBYSA</a> 2010 
      <a href="@openstreetmap">OpenStreetMap.org</a> contributors',
      array(
        '@openstreetmap' => 'http://www.openstreetmap.org/',
        '@ccbysa' => 'http://creativecommons.org/licenses/by-sa/2.0/',
      )
    ),
    'projection' => array('4326'),
    'layer_type' => 'openlayers_layer_type_wms',
    'events' => array(),
    'url' => 'http://andy.sandbox.cloudmade.com/tiles/cycle/${z}/${x}/${y}.png',
    'url' => 'http://oam.hypercube.telascience.org/tiles',
    'params' => array(
      'layers' => 'osm-4326-hybrid',
    ),
    'options' => array(
      'isBaseLayer' => FALSE,
      'buffer' => 1,
    ),
  );
  $layers[$layer->name] = $layer;

  return $layers;
}
