<?php

function openlayers_default_layers() {
  $export = array();

  $layer = new stdClass;
  $layer->api_version = 1;
  $layer->machine_name = 'layer_tile_mapquest_osm';
  $layer->name = 'MapQuest OpenStreetMap';
  $layer->description = 'Layer MapQuest OpenStreetMap description';
  $layer->class = 'openlayers_layer_tile';
  $layer->options = array(
    'source' => 'source_mapquest_osm',
  );
  $export['layer_tile_mapquest_osm'] = $layer;

  $layer = new stdClass;
  $layer->api_version = 1;
  $layer->machine_name = 'layer_tile_mapquest_sat';
  $layer->name = 'MapQuest Satellite';
  $layer->description = 'Layer MapQuest Satellite description';
  $layer->class = 'openlayers_layer_tile';
  $layer->options = array(
    'source' => 'source_mapquest_sat',
  );
  $export['layer_tile_mapquest_sat'] = $layer;

  $layer = new stdClass;
  $layer->api_version = 1;
  $layer->machine_name = 'layer_tile_mapquest_hyb';
  $layer->name = 'MapQuest Hybrid';
  $layer->description = 'Layer MapQuest Hybrid description';
  $layer->class = 'openlayers_layer_tile';
  $layer->options = array(
    'source' => 'source_mapquest_hyb',
  );
  $export['layer_tile_mapquest_hyb'] = $layer;

  $layer = new stdClass;
  $layer->api_version = 1;
  $layer->machine_name = 'layer_tile_mapbox_geography_class';
  $layer->name = 'MapBox Geography Class';
  $layer->description = 'Layer MapBox Geography Class description';
  $layer->class = 'openlayers_layer_tile';
  $layer->options = array(
    'source' => 'source_mapbox_geography_class',
  );
  $export['layer_tile_mapbox_geography_class'] = $layer;

  $layer = new stdClass;
  $layer->api_version = 1;
  $layer->machine_name = 'layer_tile_mapbox_natural_earth_hypso_bathy';
  $layer->name = 'MapBox Natural Earth Hypso Bathy';
  $layer->description = 'Layer MapBox Natural Earth Hypso Bathy description';
  $layer->class = 'openlayers_layer_tile';
  $layer->options = array(
    'source' => 'source_mapbox_natural_earth_hypso_bathy',
  );
  $export['layer_tile_mapbox_natural_earth_hypso_bathy'] = $layer;

  $layer = new stdClass;
  $layer->api_version = 1;
  $layer->machine_name = 'layer_image';
  $layer->name = 'Drupal logo layer image';
  $layer->description = 'Layer image description';
  $layer->class = 'openlayers_layer_image';
  $layer->options = array(
    'source' => 'source_imagestatic'
  );
  $export['layer_image'] = $layer;

  $layer = new stdClass();
  $layer->disabled = FALSE; /* Edit this to true to make a default layer disabled initially */
  $layer->api_version = 1;
  $layer->machine_name = 'layer_tile_openstreetmap';
  $layer->name = 'OpenStreetMap';
  $layer->description = '';
  $layer->class = 'openlayers_layer_tile';
  $layer->options = array(
    'source' => 'source_osm'
  );
  $export['layer_tile_openstreetmap'] = $layer;

  $layer = new stdClass();
  $layer->disabled = FALSE; /* Edit this to true to make a default layer disabled initially */
  $layer->api_version = 1;
  $layer->machine_name = 'layer_tile_tiledebug';
  $layer->name = 'Tile Debug';
  $layer->description = '';
  $layer->class = 'openlayers_layer_tile';
  $layer->options = array(
    'source' => 'source_tiledebug'
  );
  $export['layer_tile_tiledebug'] = $layer;

  return $export;
}
