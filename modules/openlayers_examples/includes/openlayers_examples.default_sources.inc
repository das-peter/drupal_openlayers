<?php

function openlayers_examples_default_sources() {
  $export = array();

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_mapbox_example1';
  $source->name = 'MapBox example 1';
  $source->description = 'Source MapBox example 1';
  $source->class = 'openlayers__source__tilejson';
  $source->options = array(
    'url' => 'http://api.tiles.mapbox.com/v3/examples.map-i86nkdio.jsonp',
  );
  $export['source_mapbox_example1'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_mapbox_example2';
  $source->name = 'MapBox example 2';
  $source->description = 'Source MapBox example 2';
  $source->class = 'openlayers__source__tilejson';
  $source->options = array(
    'url' => 'http://api.tiles.mapbox.com/v3/examples.c7d2024a.jsonp',
  );
  $export['source_mapbox_example2'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_mapbox_example3';
  $source->name = 'MapBox example 3';
  $source->description = 'Source MapBox example 3, used by ft.com.';
  $source->class = 'openlayers__source__tilejson';
  $source->options = array(
    'url' => 'http://api.tiles.mapbox.com/v3/financialtimes.map-w7l4lfi8.jsonp',
  );
  $export['source_mapbox_example3'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_geojson_cities';
  $source->name = 'Cities GeoJSON';
  $source->description = '';
  $source->class = 'openlayers__source__geojson';
  $source->options = array(
    'url' => file_create_url(drupal_get_path('module', 'openlayers_examples') . '/assets/cities.json'),
  );
  $export['source_geojson_cities'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_kml_earthquakes';
  $source->name = '2012 Earthquakes';
  $source->description = '';
  $source->class = 'openlayers__source__kml';
  $source->options = array(
    'url' => url(drupal_get_path('module', 'openlayers_examples') . '/assets/2012_Earthquakes_Mag5.kml', array('absolute' => TRUE)),
  );
  $export['source_kml_earthquakes'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_cluster_cities';
  $source->name = 'Cluster cities';
  $source->description = '';
  $source->class = 'openlayers__source__cluster';
  $source->options = array(
    'source' => 'source_geojson_cities',
    'distance' => '50',
  );
  $export['source_cluster_cities'] = $source;

  return $export;
}
