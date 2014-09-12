<?php

function openlayers_default_sources() {
  $export = array();

  $source = new stdClass;
  $source->api_version = 1;
  $source->machine_name = 'source_osm';
  $source->name = 'OpenStreetMap';
  $source->description = 'Source OpenStreetMap description';
  $source->class = 'openlayers_source_osm';
  $source->options = array();
  $export['source_osm'] = $source;

  $source = new stdClass;
  $source->api_version = 1;
  $source->machine_name = 'source_bingmaps';
  $source->name = 'Bing Maps';
  $source->description = 'Source Bingmaps description';
  $source->class = 'openlayers_source_bingmaps';
  $source->options = array();
  $export['source_bingmaps'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_mapquest_sat';
  $source->name = 'MapQuest Satellite';
  $source->description = 'Source MapQuest Satellite description';
  $source->class = 'openlayers_source_mapquest';
  $source->options = array(
    'layer' => 'sat',
  );
  $export['source_mapquest_sat'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_mapquest_osm';
  $source->name = 'MapQuest OpenStreetMap';
  $source->description = 'Source MapQuest OpenStreetMap description';
  $source->class = 'openlayers_source_mapquest';
  $source->options = array(
    'layer' => 'osm',
  );
  $export['source_mapquest_osm'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_mapquest_hyb';
  $source->name = 'MapQuest Hybrid';
  $source->description = 'Source MapQuest Hybrid';
  $source->class = 'openlayers_source_mapquest';
  $source->options = array(
    'layer' => 'hyb',
  );
  $export['source_mapquest_hyb'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_mapbox_geography_class';
  $source->name = 'MapBox Geography Class';
  $source->description = 'Source MapBox Geography Class description';
  $source->class = 'openlayers_source_tilejson';
  $source->options = array(
    'url' => 'http://api.tiles.mapbox.com/v3/mapbox.geography-class.jsonp',
  );
  $export['source_mapbox_geography_class'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_mapbox_natural_earth_hypso_bathy';
  $source->name = 'MapBox Natural Earth Hypso Bathy';
  $source->description = 'Source MapBox Natural Hearth Hypso Bathy description';
  $source->class = 'openlayers_source_tilejson';
  $source->options = array(
    'url' => 'http://api.tiles.mapbox.com/v3/mapbox.natural-earth-hypso-bathy.jsonp',
  );
  $export['source_mapbox_natural_earth_hypso_bathy'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_imagestatic';
  $source->name = 'Image Static';
  $source->description = 'Source Image Static description';
  $source->class = 'openlayers_source_imagestatic';
  $source->options = array(
    'url' => url(drupal_get_path('module', 'openlayers') . '/images/druplicon.png', array('absolute' => TRUE)),
  );
  $export['source_imagestatic'] = $source;

  return $export;
}
