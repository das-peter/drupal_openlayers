<?php

function openlayers_examples_default_maps() {
  $export = array();

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'openlayers_examples_map_earthquake';
  $map->name = '2012 Earthquakes map, tooltips and popups.';
  $map->description = '';
  $map->class = 'openlayers__map__map';
  $map->options = array(
    'width' => 'auto',
    'height' => '300px',
    'contextualLinks' => 1,
    'provideBlock' => 1,
    'view' => array(
      'center' => array(
        'lat' => 0,
        'lon' => 0,
      ),
      'rotation' => '0',
      'zoom' => '2',
    ),
    'layers' => array(
      0 => 'layer_tile_stamen_toner',
      1 => 'layer_vector_kml_earthquakes_heatmap'
    ),
    'controls' => array(
      0 => 'control_zoom'
    ),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    ),
    'components' => array(
      0 => 'openlayers_examples_earthquake_style',
      1 => 'openlayers_examples_simple_popup_earthquakes',
      2 => 'openlayers_examples_tooltip_earthquakes'
    )
  );
  $export['openlayers_examples_map_earthquake'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'map_openstreetmap_geofield';
  $map->name = 'OpenStreetMap with features';
  $map->description = '';
  $map->class = 'openlayers__map__map';
  $map->options = array(
    'width' => 'auto',
    'height' => '300px',
    'contextualLinks' => 1,
    'provideBlock' => 1,
    'view' => array(
      'center' => array(
        'lat' => '0',
        'lon' => '0',
      ),
      'rotation' => '0',
      'zoom' => '2',
    ),
    'layers' => array(
      0 => 'layer_tile_openstreetmap',
    ),
    'controls' => array(),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    ),
    'components' => array(
      0 => 'openlayers_examples_geofield',
    ),
  );
  $export['map_openstreetmap_geofield'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'map_mapbox_example1';
  $map->name = 'Mapbox example 1';
  $map->description = '';
  $map->class = 'openlayers__map__map';
  $map->options = array(
    'width' => 'auto',
    'height' => '300px',
    'contextualLinks' => 1,
    'provideBlock' => 1,
    'view' => array(
      'center' => array(
        'lat' => '0',
        'lon' => '0',
      ),
      'rotation' => '0',
      'zoom' => '2',
    ),
    'layers' => array(
      0 => 'layer_tile_mapbox_example1',
    ),
    'controls' => array(),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    )
  );
  $export['map_mapbox_example1'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'map_mapbox_example2';
  $map->name = 'Mapbox example 2';
  $map->description = '';
  $map->class = 'openlayers__map__map';
  $map->options = array(
    'width' => 'auto',
    'height' => '300px',
    'contextualLinks' => 1,
    'provideBlock' => 1,
    'view' => array(
      'center' => array(
        'lat' => '0',
        'lon' => '0',
      ),
      'rotation' => '0',
      'zoom' => '2',
    ),
    'layers' => array(
      0 => 'layer_tile_mapbox_example2',
    ),
    'controls' => array(),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    )
  );
  $export['map_mapbox_example2'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'map_mapbox_example3';
  $map->name = 'Mapbox example 3';
  $map->description = '';
  $map->class = 'openlayers__map__map';
  $map->options = array(
    'width' => 'auto',
    'height' => '300px',
    'contextualLinks' => 1,
    'provideBlock' => 1,
    'view' => array(
      'center' => array(
        'lat' => '0',
        'lon' => '0',
      ),
      'rotation' => '0',
      'zoom' => '2',
    ),
    'layers' => array(
      0 => 'layer_tile_mapbox_example3',
    ),
    'controls' => array(),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    )
  );
  $export['map_mapbox_example3'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'map_geojson_cities';
  $map->name = 'Map GeoJSON Cities';
  $map->description = '';
  $map->class = 'openlayers__map__map';
  $map->options = array(
    'width' => 'auto',
    'height' => '300px',
    'contextualLinks' => 1,
    'provideBlock' => 1,
    'view' => array(
      'center' => array(
        'lat' => '0',
        'lon' => '0',
      ),
      'rotation' => '0',
      'zoom' => '2',
    ),
    'layers' => array(
      0 => 'layer_tile_mapbox_example3',
      1 => 'layer_vector_geojson_cities',
    ),
    'controls' => array(),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    )
  );
  $export['map_geojson_cities'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'map_geojson_cities_heatmap';
  $map->name = 'Map GeoJSON Cities Heatmap';
  $map->description = '';
  $map->class = 'openlayers__map__map';
  $map->options = array(
    'width' => 'auto',
    'height' => '300px',
    'contextualLinks' => 1,
    'provideBlock' => 1,
    'view' => array(
      'center' => array(
        'lat' => '0',
        'lon' => '0',
      ),
      'rotation' => '0',
      'zoom' => '2',
    ),
    'layers' => array(
      0 => 'layer_tile_mapbox_example3',
      1 => 'layer_vector_geojson_cities_heatmap',
    ),
    'controls' => array(),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    )
  );
  $export['map_geojson_cities_heatmap'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'map_geolocation';
  $map->name = 'Map geolocation';
  $map->description = '';
  $map->class = 'openlayers__map__map';
  $map->options = array(
    'width' => 'auto',
    'height' => '300px',
    'contextualLinks' => 1,
    'provideBlock' => 1,
    'view' => array(
      'center' => array(
        'lat' => '0',
        'lon' => '0',
      ),
      'rotation' => '0',
      'zoom' => '2',
    ),
    'layers' => array(
      0 => 'layer_tile_openstreetmap',
    ),
    'controls' => array(),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    ),
    'components' => array(
      0 => 'openlayers_examples_geolocation'
    )
  );
  $export['map_geolocation'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'openlayers_examples_mapquest_sat_geojson_views';
  $map->name = 'MapQuest Satellite with features from Views GeoJSON';
  $map->description = '';
  $map->class = 'openlayers__map__map';
  $map->options = array(
    'width' => 'auto',
    'height' => '300px',
    'contextualLinks' => 1,
    'provideBlock' => 1,
    'view' => array(
      'center' => array(
        'lat' => '0',
        'lon' => '0',
      ),
      'rotation' => '0',
      'zoom' => '2',
    ),
    'layers' => array(
      0 => 'layer_tile_mapquest_sat',
      1 => 'openlayers_examples_views_geojson',
    ),
    'controls' => array(
      0 => 'control_zoom',
      1 => 'control_zoomslider',
    ),
    'interactions' => array(),
    'components' => array(
      0 => 'openlayers_examples_zoom_to_source',
    ),
  );
  $export['openlayers_examples_mapquest_sat_geojson_views'] = $map;


  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'openlayers_examples_cluster';
  $map->name = 'Map with cluster';
  $map->description = '';
  $map->class = 'openlayers__map__map';
  $map->options = array(
    'width' => 'auto',
    'height' => '300px',
    'contextualLinks' => 1,
    'provideBlock' => 1,
    'view' => array(
      'center' => array(
        'lat' => '0',
        'lon' => '0',
      ),
      'rotation' => '0',
      'zoom' => '2',
      'minZoom' => '0',
      'maxZoom' => '0',
    ),
    'layers' => array(
      0 => 'layer_tile_mapquest_osm',
      1 => 'layer_cluster_cities',
    ),
    'sources' => array(
      0 => 'source_mapquest_osm',
      1 => 'source_geojson_cities',
      2 => 'source_cluster_cities',
    ),
    'controls' => array(
      0 => 'control_zoom',
      1 => 'control_zoomslider',
    ),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
    ),
    'components' => array(),
  );
  $export['openlayers_examples_cluster'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'openlayers_examples_map_popup_overlay';
  $map->name = 'Map with simple popup overlay';
  $map->description = '';
  $map->class = 'openlayers__map__map';
  $map->options = array(
    'width' => 'auto',
    'height' => '300px',
    'contextualLinks' => 1,
    'provideBlock' => 1,
    'view' => array(
      'center' => array(
        'lat' => '0',
        'lon' => '0',
      ),
      'rotation' => '0',
      'zoom' => '2',
      'minZoom' => '0',
      'maxZoom' => '0',
    ),
    'layers' => array(
      0 => 'layer_tile_mapquest_osm',
      1 => 'openlayers_examples_views_geojson_popup',
    ),
    'sources' => array(
      0 => 'source_mapquest_osm',
      1 => 'views_geojson_openlayers_examples_geojson_feed_2',
    ),
    'controls' => array(
      0 => 'control_attribution',
      1 => 'control_scaleline',
      2 => 'control_zoom',
    ),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    ),
    'components' => array(
      0 => 'openlayers_examples_simple_popup',
      1 => 'openlayers_examples_zoom_to_source',
    ),
  );
  $export['openlayers_examples_map_popup_overlay'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'openlayers_examples_blocklayerswitcher';
  $map->name = 'Map with block layer switcher';
  $map->description = '';
  $map->class = 'openlayers__map__map';
  $map->options = array(
    'width' => 'auto',
    'height' => '300px',
    'contextualLinks' => 1,
    'provideBlock' => 1,
    'view' => array(
      'center' => array(
        'lat' => '0',
        'lon' => '0',
      ),
      'rotation' => '0',
      'zoom' => '2',
    ),
    'layers' => array(
      0 => 'layer_tile_mapbox_geography_class',
      1 => 'layer_tile_mapquest_hyb',
      2 => 'layer_tile_mapquest_sat',
      3 => 'layer_tile_stamen_toner',
      4 => 'layer_tile_mapquest_osm',
      5 => 'layer_tile_openstreetmap',
      6 => 'layer_vector_kml_earthquakes',
      7 => 'openlayers_examples_views_geojson',
      8 => 'layer_vector_geojson_cities_heatmap',
      9 => 'layer_vector_kml_earthquakes_heatmap',
      10 => 'layer_vector_geojson_cities',
      11 => 'layer_cluster_cities',
    ),
    'controls' => array(
      0 => 'control_zoom',
    ),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    ),
    'sources' => array(
      0 => 'source_osm',
      1 => 'source_mapbox_geography_class',
      2 => 'source_mapquest_hyb',
      3 => 'source_mapquest_sat',
      4 => 'source_stamen3',
      5 => 'source_mapquest_osm',
      6 => 'source_kml_earthquakes',
      7 => 'views_geojson_openlayers_examples_geojson_feed_1',
      8 => 'source_geojson_cities',
      9 => 'source_cluster_cities',
    ),
    'components' => array(
      0 => 'openlayers_examples_component_blocklayerswitcher',
    ),
  );
  $export['openlayers_examples_blocklayerswitcher'] = $map;

  return $export;
}
