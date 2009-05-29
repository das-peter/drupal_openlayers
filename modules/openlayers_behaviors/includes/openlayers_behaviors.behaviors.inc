<?php
// $Id$

/**
 * @file
 * This file holds the main Drupal hook functions 
 * and private functions for the openlayers_behaviors module.
 *
 * @ingroup openlayers
 */

/**
 * Callback for OpenLayers Behaviors (Zoom to Layer)
 *
 * @param $behavoir
 *   Data about behavoir
 * @param $map
 *   Map array
 * @return
 *   Behavior array
 */
function openlayers_behaviors_process_zoom_to_layer($behavior, &$map) {
  // Check to make sure the layer attribute is properly set.
  if ($behavior['layer'] && $map['layers'][$behavior['layer']]) {
    return $behavior;
  }
}

/**
 * Callback for OpenLayers Behaviors (Fullscreen)
 *
 * @param $behavoir
 *   Data about behavoir
 * @param $map
 *   Map array
 * @return
 *   Behavior array
 */
function openlayers_behaviors_process_fullscreen($behavior, &$map) {
  return $behavior;
}

/**
 * Callback for OpenLayers Behaviors (Tooltip)
 *
 * @param $behavoir
 *   Data about behavoir
 * @param $map
 *   Map array
 * @return
 *   Behavior array
 */
function openlayers_behaviors_process_tooltip($behavior, &$map) {
  // Check to make sure the layer attribute is properly set.
  if ($behavior['layer'] && $map['layers'][$behavior['layer']]) {
    drupal_add_css(drupal_get_path('module', 'openlayers_behaviors') .'/openlayers_behaviors.css', 'module');
    $behavior['pointy_path'] = drupal_get_path('module', 'openlayers_behaviors') .'/images/pointy.png';
    
    // Assume we want to display the name attribute if no attribute is specified
    if (!$behavior['attribute']) {
      $behavior['attribute'] = 'name';
    }
    
    return $behavior;
  }
}

/**
 * Callback for OpenLayers Behaviors (Draw Features)
 *
 * @param $behavoir
 *   Data about behavoir
 * @param $map
 *   Map array
 * @return
 *   Behavior array
 */
function openlayers_behaviors_process_draw_features($behavior, &$map) {
  // Check to make sure the layer attribute is properly set.
  if ($behavior['layer'] && $map['layers'][$behavior['layer']]) {
    drupal_add_css(drupal_get_path('module', 'openlayers_behaviors') .'/openlayers_behaviors.css', 'module');
    
    // Add mapReady Event
    $map['events'] = ($map['events']) ? $map['events'] : array();
    $map['events']['mapReady'] = ($map['events']['mapReady']) ? $map['events']['mapReady'] : array();
    $map['events']['mapReady'][] = 'drawFeaturesMapReady';
    
    return $behavior;
  }
}