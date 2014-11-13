<?php

function openlayers_views_default_layers() {
  $export = array();

  $views = openalyers_views_get_views('openlayers_map_views');
  foreach ($views as $view_settings) {
    list($view_name, $display) = $view_settings;
    $layer = new stdClass();
    $layer->api_version = 1;
    $layer->machine_name = 'layer_map_views_' . $view_name . '_' . $display;
    $layer->name = 'Views Map:' . $view_name . ':' . $display;
    $layer->description = t('Layer for !link views map', array('!link' => l(t('this'), 'admin/structure/views/view/' . $view_name . '/edit/' . $display)));
    $layer->class = 'openlayers__layer__vector';
    $layer->options = array(
      'source' => 'source_map_views_' . $view_name . '_' . $display,
    );
    $export[$layer->machine_name] = $layer;
  }

  return $export;
}
