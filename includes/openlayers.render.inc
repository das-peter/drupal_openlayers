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

  foreach($layers as $layer) {
    if ($layer_object = openlayers_layer_load($layer)) {
      $layer_object->render($map);
      $layer_data[$layer_object->name] = $layer_object->data;
    }
    else {
      watchdog('openlayers', 'Layer %layer not found while rendering map.', 
        array('%layer' => $layer), WATCHDOG_ERROR);
    }
  }

  return $layer_data;
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
    elseif (!empty($styles_info[$style]) && $info = $styles_info[$style]->data) {
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
