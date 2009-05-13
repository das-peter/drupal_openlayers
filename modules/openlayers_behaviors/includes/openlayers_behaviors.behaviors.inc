<?php
 
function openlayers_behaviors_process_zoom_to_layer($behavior, &$map){
  // Check to make sure the layer attribute is properly set.
  if ($behavior['layer'] && $map['layers'][$behavior['layer']]) return $behavior;
}

function openlayers_behaviors_process_fullscreen($behavior, &$map){
  return $behavior;
}

function openlayers_behaviors_process_tooltip($behavior, &$map){
  // Check to make sure the layer attribute is properly set.
  if ($behavior['layer'] && $map['layers'][$behavior['layer']]){
    drupal_add_css(drupal_get_path('module', 'openlayers_behaviors') .'/openlayers_behaviors.css', 'module');
    $behavior['pointy_path'] = drupal_get_path('module', 'openlayers_behaviors') .'/images/pointy.png';
    
    // Assume we want to display the name attribute if no attribute is specified
    if (!$behavior['attribute']){
      $behavior['attribute'] = 'name';
    }
    
    return $behavior;
  }
}

function openlayers_behaviors_process_draw_features($behavior, &$map){
  // Check to make sure the layer attribute is properly set.
  if ($behavior['layer'] && $map['layers'][$behavior['layer']]){
    // Add mapReady Event
    if (!$map['events']) $map['events'] = array();
    if (!$map['events']['mapReady']) $map['events']['mapReady'] = array();
    $map['events']['mapReady'][] = 'openlayersBehaviorsDrawFeaturesMapReady';
    
    return $behavior;
  }
}