<?php

function openlayers_views_default_sources() {
  $export = array();

  foreach (views_get_all_views() as $view) {
    foreach ($view->display as $display => $data) {
      $view->set_display($display);
      if ($view->display_handler->get_option('style_plugin') == 'openlayers_source_vector' && $display != 'default') {

        dpm($view);

        $source = new stdClass;
        $source->api_version = 1;
        $source->machine_name = 'source_views_'. $view->name . '_' . $display;
        $source->name = 'Views source'. $view->name . '_' . $display;
        $source->description = '';
        $source->class = 'openlayers_source_vector';
        $source->options = array(
          'url'
        );
        $export[$source->machine_name] = $source;
      }
    }
  }

  return $export;
}

/*
function openlayers_views_openlayers_layer() {
  $layers = array();

  dpm('ici');

  // Attempt to load information from cache.
  // For now use a arg based check for skipping cache.
  if (arg(0) != 'admin') {
    $cache = cache_get('openlayers_views');
    if (isset($cache->data)) {
      return $cache->data;
    }
  }


  cache_set('openlayers_views', $layers);
  return $layers;
}
*/
