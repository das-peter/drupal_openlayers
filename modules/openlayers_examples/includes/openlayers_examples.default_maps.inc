<?php

function openlayers_examples_default_maps() {
  $export = array();

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

  return $export;
}
