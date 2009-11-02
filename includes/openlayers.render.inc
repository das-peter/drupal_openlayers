<?php
// $Id$

/**
 * @file
 * This file holds the functions the extra processing of rendering a map
 *
 * @ingroup openlayers
 */

/**
 * Process Layers
 *
 * Get full data for any layers and add handlers
 *
 * @param $layers
 *   Array of layers to process
 * @param $map
 *   Map array
 * @return
 *   Array of processed layers
 */
function _openlayers_layers_process($layers = array(), &$map = array()) {  
  if (!$layers) {
    $layers = array();
  }
  if (!is_array($map)) {
    $map = array();
  }
  $processed = array();
  
  // Get layer info array
  $layer_info = openlayers_layers();

  // Check to make sure our default layer is present, if it isn't then add it.
  if (!array_key_exists($map['default_layer'], $layers) && ($map['default_layer'])) {
    $layers[$map['default_layer']] = $map['default_layer'];
  }

  // Go through layers
  foreach ($layers as $k => $layer) {
    // Check if array, if array, just pass on
    if (is_array($layer)) {
      $processed[$k] = $layer;
    }
    else {
      // If not array, we want to include the file and call the function
      if (!empty($layer_info[$layer]) && $info = $layer_info[$layer]->data) {
        $processed[$layer] = $info;
        // Make sure layer title is set    
        $processed[$layer]['title'] = $layer_info[$layer]->title;
      }
    }
  }

  // Add Handlers
  $handlers = module_invoke_all('openlayers_layers_handler_info', $map);
  
  // Go through processed
  foreach ($processed as $k => $l) {
    
    // Make sure layer name and title is set    

    $processed[$k]['options']['title'] = $l['title'] ? $l['title'] : $k;  
    $processed[$k]['name'] = $k; 
  
    
    // Check for handler
    if (is_string($handlers[$l['type']]['layer_handler'])) {
      $processed[$k]['layer_handler'] = $handlers[$l['type']]['layer_handler'];

      // Extra processing for views to include arguments and exposed filters
      if (isset($l['views']['view'], $l['views']['display'])) {
        if ($view = views_get_view($l['views']['view'])) {
          $args = array();

          // Retrieve args/filters from current view to pass on to our vector layer.
          $current_view = views_get_current_view();
          if ($current_view) {
            $args = $current_view->args;
            $view->set_exposed_input($current_view->exposed_input);
          }

          $view->execute_display($l['views']['display'], $args);
          $view->init_style();
          $processed[$k]['features'] = $view->style_plugin->pre_render($view->result);

          $view->destroy();          
        }
      } 
      
      // Include JS file if there is one
      if (is_string($handlers[$l['type']]['js_file'])) {
        drupal_add_js($handlers[$l['type']]['js_file'], 'module');
      }
    }
  }

  // Return processed
  return $processed;
}

/**
 * Process Behaviors
 *
 * Execute render() method for all enabled behaviors.
 *
 * @param $behaviors
 *   Array of behaviors to process
 * @param $map
 *   Map array
 */
function _openlayers_behaviors_process($behaviors = array(), &$map = array()) {
  $processed = array();
  foreach (openlayers_behaviors() as $key => $plugin) {
    if (isset($behaviors[$key]) && $class = ctools_plugin_get_class($plugin, 'behavior')) {
      $behavior = new $class($behaviors[$key], $map);     
      $processed[$key] = $behavior->render($map);
    }
  }
  return $processed;
}

/**
 * Process Styles
 *
 * Get full data for any styles
 *
 * @param $styles
 *   Array of styles to process
 * @param $map
 *   Map array
 * @return
 *   Array of processed styles
 */
function _openlayers_styles_process($styles = array(), $layer_styles = array(), &$map = array()) {
  // Initial variables
  $styles = is_array($styles) ? $styles : array();
  $layer_styles = is_array($layer_styles) ? $layer_styles : array();
  $map = is_array($map) ? $map : array();

  // Get behavior info array
  $styles_info = openlayers_styles();

  // Go through styles
  $processed = array();
  foreach ($styles as $k => $style) {
    // Check if array, if array, just pass on
    if (is_array($style)) {
      $processed[$k] = $style;
    }
    else if (!empty($styles_info[$style]) && $info = $styles_info[$style]->data) {
      $processed[$k] = $info;
    }
  }

  // Add layer styles
  foreach ($layer_styles as $style) {
    if (!isset($processed[$style]) && !empty($styles_info[$style]) && $info = $styles_info[$style]->data) {
      $processed[$style] = $info;
    }
  }

  // Run through theme function
  $processed = theme('openlayers_styles', $processed, $map);

  // Return processed
  return $processed;
}

/**
 * Create Map ID
 *
 * Create a unique ID for any maps that are not assigned an ID
 *
 * @note
 *   Technically someone can assign a map ID identical
 *   to the one that is created
 * @return
 *   New map id
 */
function _openlayers_create_map_id() {
  static $map_count = 0;
  $id = 'openlayers-map-auto-id-'. $map_count;
  $map_count++;
  return $id;
}
