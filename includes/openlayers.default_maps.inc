<?php

function openlayers_default_maps() {
  $export = array();

  $map = new stdClass();
  $map->api_version = 1;
  $map->machine_name = 'map_mapbox_natural_earth_hypso_bathy';
  $map->name = 'MapBox Natural Earth Hypso Bathy';
  $map->description = '';
  $map->class = 'openlayers_map_map';
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
      0 => 'layer_tile_mapbox_natural_earth_hypso_bathy',
    ),
    'controls' => array(
      0 => 'control_rotate',
      1 => 'control_scaleline',
      2 => 'control_zoom',
      3 => 'control_zoomslider',
      4 => 'control_zoomtoextent',
    ),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_dragrotate',
      3 => 'interaction_mousewheelzoom',
    ),
  );
  $export['map_mapbox_natural_earth_hypso_bathy'] = $map;

  $map = new stdClass();
  $map->api_version = 1;
  $map->machine_name = 'map_mapbox_geography_class';
  $map->name = 'MapBox Geography Class';
  $map->description = '';
  $map->class = 'openlayers_map_map';
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
    ),
    'controls' => array(
      0 => 'control_rotate',
      1 => 'control_scaleline',
      2 => 'control_zoom',
      3 => 'control_zoomslider',
      4 => 'control_zoomtoextent',
    ),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_dragrotate',
      3 => 'interaction_mousewheelzoom',
    ),
  );
  $export['map_mapbox_geography_class'] = $map;

  $map = new stdClass();
  $map->api_version = 1;
  $map->machine_name = 'map_mapquest_openstreetmap';
  $map->name = 'MapQuest OpenStreetMap';
  $map->description = '';
  $map->class = 'openlayers_map_map';
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
      0 => 'layer_tile_mapquest_osm',
    ),
    'controls' => array(
      0 => 'control_rotate',
      1 => 'control_scaleline',
      2 => 'control_zoom',
      3 => 'control_zoomslider',
      4 => 'control_zoomtoextent',
    ),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_dragrotate',
      3 => 'interaction_keyboardpan',
      4 => 'interaction_mousewheelzoom',
    ),
  );
  $export['map_mapquest_openstreetmap'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'map_mapquest_hybrid';
  $map->name = 'MapQuest Hybrid';
  $map->description = '';
  $map->class = 'openlayers_map_map';
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
      1 => 'layer_tile_mapquest_hyb',
    ),
    'controls' => array(
      0 => 'control_attribution',
      1 => 'control_mouseposition',
      2 => 'control_rotate',
      3 => 'control_zoom',
    ),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_dragrotateandzoom',
      3 => 'interaction_mousewheelzoom',
    ),
  );
  $export['map_mapquest_hybrid'] = $map;

  $map = new stdClass();
  $map->api_version = 1;
  $map->machine_name = 'map_mapquest_satellite';
  $map->name = 'MapQuest Satellite';
  $map->description = '';
  $map->class = 'openlayers_map_map';
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
    ),
    'controls' => array(
      0 => 'control_mouseposition',
      1 => 'control_scaleline',
    ),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_dragrotateandzoom',
      3 => 'interaction_mousewheelzoom',
    ),
  );
  $export['map_mapquest_satellite'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'map_openstreetmap';
  $map->name = 'OpenStreetMap';
  $map->description = '';
  $map->class = 'openlayers_map_map';
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
  );
  $export['map_openstreetmap'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'map_opencyclemap';
  $map->name = 'OpenCycleMap';
  $map->description = '';
  $map->class = 'openlayers_map_map';
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
      0 => 'layer_tile_opencyclemap',
    ),
    'controls' => array(
      0 => 'control_zoom',
      1 => 'control_zoomslider',
    ),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    ),
    'components' => array(),
  );
  $export['map_opencyclemap'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'map_openstreetmap_tiledebug';
  $map->name = 'OpenStreetMap with tile debug.';
  $map->description = '';
  $map->class = 'openlayers_map_map';
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
      1 => 'layer_tile_tiledebug'
    ),
    'controls' => array(),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    ),
  );
  $export['map_openstreetmap_tiledebug'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'map_stamen';
  $map->name = 'Stamen map';
  $map->description = '';
  $map->class = 'openlayers_map_map';
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
      0 => 'layer_tile_stamen_watercolor',
      1 => 'layer_tile_stamen_terrain_labels',
    ),
    'controls' => array(
      0 => 'control_zoom'
    ),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    ),
  );
  $export['map_stamen'] = $map;

  $map = new stdClass();
  $map->disabled = FALSE; /* Edit this to true to make a default map disabled initially */
  $map->api_version = 1;
  $map->machine_name = 'map_esri';
  $map->name = 'ESRI map';
  $map->description = '';
  $map->class = 'openlayers_map_map';
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
      0 => 'layer_tile_esri',
    ),
    'controls' => array(
      0 => 'control_zoom'
    ),
    'interactions' => array(
      0 => 'interaction_doubleclickzoom',
      1 => 'interaction_dragpan',
      2 => 'interaction_mousewheelzoom',
    ),
  );
  $export['map_esri'] = $map;

  $map = new stdClass;
  $map->disabled = TRUE;
  $map->api_version = 1;
  $map->machine_name = 'map_view_edit_form';
  $map->name = 'Map view edit form';
  $map->description = 'Map used in the the map edit form to get center, zoom';
  $map->class = 'openlayers_map_map';
  $map->options = array(
    'width' => 'auto',
    'height' => '400px',
    'view' => array(
      'center' => array(
        'lat' => '0',
        'lon' => '0',
      ),
      'rotation' => '0',
      'zoom' => '2',
    ),
    'contextualLinks' => 0,
    'provideBlock' => 0,
    'layers' => array(
      0 => 'layer_tile_mapquest_osm',
    ),
    'controls' => array(
      0 => 'control_mouseposition',
      1 => 'control_rotate',
      2 => 'control_scaleline',
      3 => 'control_zoom',
      4 => 'control_zoomslider',
      5 => 'control_zoomtoextent',
    ),
    'interactions' => array(
      0 => 'interaction_dragpan',
      1 => 'interaction_dragrotateandzoom',
      2 => 'interaction_mousewheelzoom',
    ),
    'components' => array(
      0 => 'map_edit_form_values',
      1 => 'map_edit_form_setcenter',
    )
  );
  $export['map_view_edit_form'] = $map;

  return $export;
}
