<?php
// $Id$

/**
 * @file
 * Theme functions for openlayers_cck
 */

/**
 * Theme function for openlayers_wkt_widget element
 */
function theme_openlayers_wkt_widget($element) {
  return $element['#children'];
}

/**
 * Theme function for openlayers cck default formatters
 */
function theme_openlayers_cck_formatter_default($element) {
  $features = array();

  // Create array of $features
  foreach (element_children($element) as $delta) {
    // First look in the 'wkt' key (where geo stores it), 
    // then look in 'openlayers_wkt' key (where the non-spatial openlayers wkt field stores it).
    $features[$delta] = $element[$delta]['#item']['openlayers_wkt'];
  }
  
  // Clean features array of empty and null values
  $features = array_filter($features);
  return array_pop($features);
}

/**
 * Theme function for openlayers cck formatters
 */
function theme_openlayers_cck_formatter_map($element) {
  $features = array();
  $field = content_fields($element['#field_name'], $element['#type_name']);
  
  // Create array of $features
  foreach (element_children($element) as $delta) {
    $features['openlayers_cck_vector_feature_' . $delta] = array(
      // First look for geo_field data, then for openlayers wkt data
      'wkt' => $element[$delta]['#item']['openlayers_wkt'],
      'projection' => $element[$delta]['#item']['srid'] ? 
        $element[$delta]['#item']['srid'] : 
        '4326',
    );
  }

  // Get preset name from formatter. Strip off 'openlayers_cck_formatter_' and 'openlayers_map_' from the beginning.
  if (substr($element['#formatter'], 25) == 'openlayers_cck_formatter_') {
    $preset_name = substr($element['#formatter'], 25);
  }
  if (substr($element['#formatter'], 0, 15) == 'openlayers_map_') {
    $preset_name = substr($element['#formatter'], 15);
  }

  // Get map preset
  $preset = openlayers_preset_load($preset_name);

  /*
  // Set map ID
  static $formatter_count = array();
  if (isset($formatter_count[$field['field_name']])) {
    $formatter_count[$field['field_name']]++;
  }
  else {
    $formatter_count[$field['field_name']] = 0;
  }
  $map['id'] = OPENLAYERS_CCK_FORMATTER_MAP_ID_PREFIX .'-'. 
    str_replace('_', '-', $field['field_name']) .'-'. $formatter_count[$field['field_name']];
  $formatter_count++;
  
  // Add features and vector layer
  if (count($features) > 0) {
    $map['layers']['openlayers_cck_vector'] = array(
      'id' => 'openlayers_cck_vector',
      'name' => $field['widget']['label'],
      'type' => 'Vector',
      'options' => array(),
      'features' => $features,
    );
    $map['options']['displayProjection'] = ($field['srid'] != 0) ? $field['srid'] : '4326';
  }
   */
  
  // Render map
  return openlayers_render_map(array(), $preset);
}

/**
 * Theme function for openlayers_cck_map
 */
function theme_openlayers_cck_map($field = array(), $map = array()) {
  // TODO: fix
  return $map;
}

