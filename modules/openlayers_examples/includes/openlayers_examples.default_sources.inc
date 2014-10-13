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

  https://b.tiles.mapbox.com/v3/financialtimes.map-w7l4lfi8/9/261/172.png
  return $export;
}