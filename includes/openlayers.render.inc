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
      if (!empty($layer_info[$layer]) && $info = $layer_info[$layer]) {
        
        // Check to see if we should use a callback, or use the default callback
        if ($info->data['callback']) {
          // Check if file exists
          if (is_file('./'. $info->data['file'])) {
            require_once './'. $info->data['file'];
            // Check for function
            if (function_exists($info->data['callback'])) {
              // Call function and give it the layer name
              $result = $info->data['callback']($info, $map);
            }
          }
        }
        else {
          // Use a default callback
          $result = _openlayers_default_layer_callback($info);
        }
        // Check for result
        if (isset($result) && is_array($result)) {
          $processed[$layer] = $result;
        }
      }
    }
  }

  // Add Handlers
  $handlers = module_invoke_all('openlayers_layers_handler_info', $map);
  // Go through processed
  foreach ($processed as $k => $l) {
    // Check for handler
    if (is_string($handlers[$l['type']]['layer_handler'])) {
      $processed[$k]['layer_handler'] = $handlers[$l['type']]['layer_handler'];
      // Include JS file if there is one
      if (is_string($handlers[$l['type']]['js_file'])) {
        drupal_add_js($handlers[$l['type']]['js_file'], 'module');
      }
    }
  }
  
  // Return processed
  return $processed;
}

function _openlayers_default_layer_callback ($info) {
  $layer = $info->data;
  $layer['name'] = $info->title;
  return $layer;
}


/**
 * Process Behaviors
 *
 * Get full data for any behaviors and add handlers
 *
 * @param $behaviors
 *   Array of behaviors to process
 * @param $map
 *   Map array
 * @return
 *   Array of processed behaviors
 */
function _openlayers_behaviors_process($behaviors = array(), &$map = array()) {
  $processed = array();

  // Get and go through behaviors
  foreach (openlayers_behaviors() as $key => $plugin) {
    // Check for behavior and plugin class
    if (isset($behaviors[$key]) && $class = ctools_plugin_get_class($plugin, 'behavior')) {
      // Instantiate new class and proccess
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
 * @param $layer_styles
 *   Array of styles to specific to layer
 * @param $map
 *   Map array
 * @return
 *   Array of processed styles
 */
function _openlayers_styles_process($styles = array(), $layer_styles = array(), &$map = array()) {
  $styles = is_array($styles) ? $styles : array();
  $layer_styles = is_array($layer_styles) ? $layer_styles : array();
  $map = is_array($map) ? $map : array();
  $processed = array();

  // Get styles
  $styles_info = openlayers_styles();

  // Go through styles
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
  // Set up variables
  $map_id = '';
  static $map_count = 0;
  // Put together ID
  $map_id = OPENLAYERS_MAP_ID_PREFIX .'-'. $map_count;
  // Add another
  $map_count += 1;
  // Return ID
  return $map_id;
}

/**
 * Debug Map
 *
 * Offers debugging if enabled.  Options are available in the
 * administration interface to enable different kinds of
 * debugging at different points of rendering.
 *
 * @param $op
 *   The operation that is getting carried out
 * @param $map
 *   map array to debug
 * @return
 *   none
 */
function _openlayers_render_debug_map($op = NULL, $map = array()) {
  // Check op
  switch ($op) {
    case 'pre-render':
      // Screen output, check function first
      if (function_exists('dpm')) {
        if (variable_get('openlayers_debug_screen_pre_render', FALSE)) {
          dpm($map);
        }
      }
      // Check watchdog
      if (variable_get('openlayers_debug_watchdog_pre_render', FALSE)) {
        watchdog('openlayers', '<p>Pre render output.</p><pre>!array_output</pre>', array('!array_output' => var_export($map, TRUE)),  WATCHDOG_DEBUG);
      }
      break;

    case 'post-render':
      // Screen output, check function first
      if (function_exists('dpm')) {
        if (variable_get('openlayers_debug_screen_post_render', FALSE)) {
          dpm($map);
        }
      }
      // Check watchdog
      if (variable_get('openlayers_debug_watchdog_post_render', FALSE)) {
        watchdog('openlayers', '<p>Post render output.</p><pre>!array_output</pre>', array('!array_output' => var_export($map, TRUE)),  WATCHDOG_DEBUG);
      }
      break;

  }
}
