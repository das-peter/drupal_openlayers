<?php
 
function openlayers_behaviors_process_zoom_to_layer($behavior, &$map){
  // Check to make sure the layer attribute is properly set.
  if ($behavior['layer'] && $map['layers'][$behavior['layer']]) return $behavior;
}

function openlayers_behaviors_process_tooltip($behavior, &$map){
  // Check to make sure the layer attribute is properly set.
  if ($behavior['layer'] && $map['layers'][$behavior['layer']]) return $behavior;
}

function openlayers_behaviors_process_feature_highlight($behavior, &$map){
  return $behavior;
}