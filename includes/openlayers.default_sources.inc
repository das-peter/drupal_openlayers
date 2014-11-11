<?php

function openlayers_default_sources() {
  $export = array();

  $source = new stdClass;
  $source->api_version = 1;
  $source->machine_name = 'source_osm';
  $source->name = 'OpenStreetMap';
  $source->description = 'Source OpenStreetMap description';
  $source->class = 'openlayers__source__osm';
  $source->options = array();
  $export['source_osm'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_osm_opencyclemap';
  $source->name = 'OpenCycleMap';
  $source->description = 'Source OpenCycleMap description';
  $source->class = 'openlayers__source__osm';
  $source->options = array(
    'url' => 'http://{a-c}.tile.opencyclemap.org/cycle/{z}/{x}/{y}.png',
  );
  $export['source_osm_opencyclemap'] = $source;

  $source = new stdClass;
  $source->api_version = 1;
  $source->machine_name = 'source_bingmaps';
  $source->name = 'Bing Maps';
  $source->description = 'Source Bingmaps description';
  $source->class = 'openlayers__source__bingmaps';
  $source->options = array();
  $export['source_bingmaps'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_mapquest_sat';
  $source->name = 'MapQuest Satellite';
  $source->description = 'Source MapQuest Satellite description';
  $source->class = 'openlayers__source__mapquest';
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
  $source->class = 'openlayers__source__mapquest';
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
  $source->class = 'openlayers__source__mapquest';
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
  $source->class = 'openlayers__source__tilejson';
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
  $source->class = 'openlayers__source__tilejson';
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
  $source->class = 'openlayers__source__imagestatic';
  $source->options = array(
    'url' => url(drupal_get_path('module', 'openlayers') . '/images/druplicon.png', array('absolute' => TRUE)),
  );
  $export['source_imagestatic'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_tiledebug';
  $source->name = 'Tile debug';
  $source->description = 'A pseudo tile source, which does not fetch tiles from a server, but renders a grid outline for the tile grid/projection along with the coordinates for each tile.';
  $source->class = 'openlayers__source__tiledebug';
  $source->options = array(
    'maxZoom' => 22
  );
  $export['source_tiledebug'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_stamen1';
  $source->name = 'Stamen terrain labels';
  $source->description = '';
  $source->class = 'openlayers__source__stamen';
  $source->options = array(
    'layer' => 'terrain-labels'
  );
  $export['source_stamen1'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_stamen2';
  $source->name = 'Stamen watercolor';
  $source->description = '';
  $source->class = 'openlayers__source__stamen';
  $source->options = array(
    'layer' => 'watercolor'
  );
  $export['source_stamen2'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_stamen3';
  $source->name = 'Stamen toner';
  $source->description = '';
  $source->class = 'openlayers__source__stamen';
  $source->options = array(
    'layer' => 'toner'
  );
  $export['source_stamen3'] = $source;

  $source = new stdClass();
  $source->disabled = FALSE; /* Edit this to true to make a default source disabled initially */
  $source->api_version = 1;
  $source->machine_name = 'source_esri';
  $source->name = 'ESRI';
  $source->description = '';
  $source->class = 'openlayers__source__xyz';
  $source->options = array(
    'url' => 'http://server.arcgisonline.com/ArcGIS/rest/services/World_Topo_Map/MapServer/tile/{z}/{y}/{x}'
  );
  $export['source_esri'] = $source;

  return $export;
}

/**
 * On behalf of views_geojson.
 */
function views_geojson_default_sources() {
  $export = array();
  foreach (views_get_all_views() as $view) {
    foreach ($view->display as $display => $data) {
      $view->set_display($display);
      if (in_array($view->display_handler->get_option('style_plugin'), array('views_geojson_feed', 'views_geojson'))) {
        $source = new stdClass();
        $source->api_version = 1;
        $source->machine_name = 'views_geojson_' . $view->name . '_' . $display;
        $source->name = 'Views GeoJSON source: ' . $view->name . '_' . $display;
        $source->description = 'This source is automatically generated. See View ' . $view->name . ' at display ' . $display;
        $source->class = 'openlayers__source__geojson';

        $source->options = array(
          'url' => url($view->display_handler->get_url(), array('absolute' => TRUE)),
        );

        // Determine if we should use a BBox strategy.
        if ($arguments = $view->display_handler->get_option('arguments')) {
          foreach ($arguments as $id => $argument) {
            if (strpos($id, 'bbox') !== FALSE && $argument['default_argument_type'] == 'querystring') {
              if (isset($argument['default_argument_options'])) {
                $source->options['useBBOX'] = TRUE;
              }
            }
          }
        }
        $export[$source->machine_name] = $source;
      }
    }
  }

  return $export;
}
