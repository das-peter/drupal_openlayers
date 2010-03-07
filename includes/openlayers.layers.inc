<?php
// $Id$

/**
 * @file
 *
 * OpenLayers default packaged layers
 */
function _openlayers_openlayers_layers() {
  $layers = array();

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'google_satellite';
  $layer->title = t('Google Maps Satellite');
  $layer->description = t('Google Maps Satellite Imagery.');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'satellite',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layer_type_google',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'google_hybrid';
  $layer->title = t('Google Maps Hybrid');
  $layer->description = t('Google Maps with roads and terrain.');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'hybrid',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layer_type_google',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'google_normal';
  $layer->title = t('Google Maps Normal');
  $layer->description = t('Standard Google Maps Roads');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'normal',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layer_type_google',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'google_physical';
  $layer->title = t('Google Maps Physical');
  $layer->description = t('Google Maps Hillshades');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'physical',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layer_type_google',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'yahoo_satellite';
  $layer->title = t('Yahoo Maps Satellite');
  $layer->description = t('Yahoo satellite imagery tiles.');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'satellite',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layer_type_yahoo',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'yahoo_street';
  $layer->title = t('Yahoo Maps Street');
  $layer->description = t('Yahoo streets tiles.');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'street',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layer_type_yahoo',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'yahoo_hybrid';
  $layer->title = t('Yahoo Maps Hybrid');
  $layer->description = t('Yahoo hybrid of streets and satellite tiles.');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'hybrid',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layer_type_yahoo',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;
  
  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'virtualearth_street';
  $layer->title = t('Virtual Earth Street');
  $layer->description = t('Virtual Earth (Bing) street tiles.');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'street',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layer_type_virtualearth',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'virtualearth_satellite';
  $layer->title = t('Virtual Earth Satellite');
  $layer->description = t('Virtual Earth (Bing) satellite tiles.');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'satellite',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layer_type_virtualearth',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'virtualearth_hybrid';
  $layer->title = t('Virtual Earth Hybrid');
  $layer->description = t('Virtual Earth (Bing) hybrid of streets and satellite tiles.');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'hybrid',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layer_type_virtualearth',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;
  
  // OpenStreetMap Mapnik
  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'osm_mapnik';
  $layer->title = t('OSM Mapnik');
  $layer->description = t('The main OpenStreetMap map');
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
  $layer->name = 'osm_tah';
  $layer->title = t('OSM Tiles@Home');
  $layer->description = t('Alternative, community-rendered OpenStreetMap');
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
  $layer->name = 'osm_cycle';
  $layer->title = t('OSM Cycling Map');
  $layer->description = t('OpenStreetMap with highlighted bike lanes');
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
  $layer->name = 'osm_4326_hybrid';
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

  $layer = new StdClass();
  $layer->api_version = 1;
  $layer->name = 'wms_default';
  $layer->title = t('Default OpenLayers WMS');
  $layer->description = t('MetaCarta basemap of province and water boundaries');
  $layer->data = array(
    'projection' => array('4326'),
    'baselayer' => TRUE,
    'layer_type' => 'openlayers_layer_type_wms',
    'url' => 'http://labs.metacarta.com/wms/vmap0',
    'params' => array('layers' => 'basic'),
    'options' => array(
      'maxExtent' => openlayers_get_extent('4326'),
    ),
    'events' => array(),
  );
  $layers[$layer->name] = $layer;
  

  return $layers;
}
