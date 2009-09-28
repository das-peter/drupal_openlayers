<?php
// $Id$

/**
 * @file
 * This file holds layer processing function
 * for views powered data layers
 *
 * @ingroup openlayers
 */

/**
 * Speicifc Layer Callback for Views Layers
 *
 * This function handles the speicifc layer handling
 * of views data layers
 *
 * @param $layer
 *   Array of data passed by rendering
 * @return
 *   Layer data
 */
function openlayers_views_process_layers($info = NULL) {
  $layer = $info->data;
  $layer['name'] = $info->title;
  
  if (isset($layer['views']['view'], $layer['views']['display'])) {
    if ($view = views_get_view($layer['views']['view'])) {
      $args = array();
    
      // Retrieve args/filters from current view to pass on to our vector layer.
      $current_view = views_get_current_view();
      if ($current_view) {
        $args = $current_view->args;
        $view->set_exposed_input($current_view->exposed_input);
      }
    
      $view->execute_display($l['views']['display'], $args);
      $view->init_style();
      
      $layer['features'] = $view->style_plugin->pre_render($view->result);
      
      $view->destroy();          
     }
   }
  return $layer;

}
