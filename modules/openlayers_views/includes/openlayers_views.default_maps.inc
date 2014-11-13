<?php

function openlayers_views_default_maps() {
  $export = array();

  $views = openalyers_views_get_views('openlayers_map_views');
  foreach ($views as $view_settings) {
    list($view_name, $display) = $view_settings;
    $map = new stdClass();
    $map->api_version = 1;
    $map->machine_name = 'map_views_' . $view_name . '_' . $display;
    $map->name = 'Views Map: ' . $view_name . ':' . $display;
    $map->description = t('Map from !link views map', array('!link' => l(t('this'), 'admin/structure/views/view/' . $view_name . '/edit/' . $display)));
    $map->class = 'openlayers__map__views';
    $map->options = array(
      'views_display' => $view_name . ':' . $display,
      'view' => array(
        'center' => array(
          'lat' => '',
          'lon' => '',
        ),
        'rotation' => '0',
        'zoom' => '2',
        'minZoom' => '',
        'maxZoom' => '',
      ),
      'sources' => array(
        'source_map_views_' . $view_name . '_' . $display,
      ),
      'layers' => array(
        'layer_map_views_' . $view_name . '_' . $display,
      ),
    );
    $export[$map->machine_name] = $map;
  }

  return $export;
}
