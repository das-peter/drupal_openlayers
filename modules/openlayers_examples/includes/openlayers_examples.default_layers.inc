<?php

function openlayers_examples_default_layers() {
  $export = array();

  $layer = new stdClass;
  $layer->api_version = 1;
  $layer->machine_name = 'layer_tile_mapbox_example1';
  $layer->name = 'MapBox example 1';
  $layer->description = 'Layer MapBox example 1';
  $layer->class = 'openlayers__layer__tile';
  $layer->options = array(
    'source' => 'source_mapbox_example1',
  );
  $export['layer_tile_mapbox_example1'] = $layer;

  $layer = new stdClass;
  $layer->api_version = 1;
  $layer->machine_name = 'layer_tile_mapbox_example2';
  $layer->name = 'MapBox example 2';
  $layer->description = 'Layer MapBox example 2';
  $layer->class = 'openlayers__layer__tile';
  $layer->options = array(
    'source' => 'source_mapbox_example2',
  );
  $export['layer_tile_mapbox_example2'] = $layer;

  $layer = new stdClass;
  $layer->api_version = 1;
  $layer->machine_name = 'layer_tile_mapbox_example3';
  $layer->name = 'MapBox example 2';
  $layer->description = 'Layer MapBox example 3';
  $layer->class = 'openlayers__layer__tile';
  $layer->options = array(
    'source' => 'source_mapbox_example3',
  );
  $export['layer_tile_mapbox_example3'] = $layer;

  $layer = new stdClass;
  $layer->api_version = 1;
  $layer->machine_name = 'layer_vector_geojson_cities';
  $layer->name = 'GeoJSON Cities';
  $layer->description = 'GeoJSON Cities';
  $layer->class = 'openlayers__layer__vector';
  $layer->options = array(
    'source' => 'source_geojson_cities',
  );
  $export['layer_vector_geojson_cities'] = $layer;

  $layer = new stdClass;
  $layer->api_version = 1;
  $layer->machine_name = 'layer_vector_geojson_cities_heatmap';
  $layer->name = 'GeoJSON Cities heatmap';
  $layer->description = 'GeoJSON Cities Heatmap';
  $layer->class = 'openlayers__layer__heatmap';
  $layer->options = array(
    'source' => 'source_geojson_cities',
  );
  $export['layer_vector_geojson_cities_heatmap'] = $layer;

  return $export;
}
