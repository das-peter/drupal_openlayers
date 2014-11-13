<?php

function openlayers_views_default_sources() {
  $export = array();

  $views = openalyers_views_get_views('openlayers_source_vector');
  foreach ($views as $view_settings) {
    list($view_name, $display) = $view_settings;
    if ($view = views_get_view($view_name)) {
      $view->set_display($display);

      $source = new stdClass();
      $source->api_version = 1;
      $source->machine_name = 'source_views_' . $view->name . '_' . $display;
      $source->name = 'Views Source: ' . $view->name . '_' . $display;
      $source->description = '';
      $source->class = 'openlayers__source__vector';
      $source->options = array(
        'url' => url($view->display_handler->get_url(), array('absolute' => TRUE)),
      );
      $export[$source->machine_name] = $source;
    }
  }

  $views = openalyers_views_get_views('openlayers_map_views');
  foreach ($views as $view_settings) {
    list($view_name, $display) = $view_settings;
    $source = new stdClass();
    $source->api_version = 1;
    $source->machine_name = 'source_map_views_' . $view_name . '_' . $display;
    $source->name = 'Views Map: ' . $view_name . ':' . $display;
    $source->description = t('Source for !link views map', array('!link' => l(t('this'), 'admin/structure/views/view/' . $view_name . '/edit/' . $display)));
    $source->class = 'openlayers__source__vector';
    $source->options = array();
    $export[$source->machine_name] = $source;
  }

  return $export;
}
