<?php
// $Id$

/**
 * @file
 * This file holds the main Drupal hook functions
 * and private functions for the openlayers module.
 *
 * @ingroup openlayers
 */

/**
 * Speicifc Layer Callback for Geo Table Layers
 *
 * This function handles the speicifc layer handling
 * of layers enabled for Geo tables
 *
 * @param $layer
 *   Array of data passed by rendering
 * @return
 *   Layer data
 */
function openlayers_layers_process_geo_data_layers($info = NULL) {
  //@@TODO: This has not be converted to ctools style yet
  
  // Get table description
  $table_desc = geo('table_desc', $info->name);
  $attribute_cols = array();

  // Go through columns
  foreach ($table_desc as $cname => $cinfo) {
    if ($cinfo['type'] == 'geometry') {
      $geometry_col = $cname;
      $srid = $cinfo['srid'];
    }
    else {
      $attribute_cols[] = db_escape_table($cname);
    }
  }

  // Make values safe since not enritely sure how its getting there.
  $geometry_col = db_escape_table($geometry_col);

  // Get geometry text
  $query = "SELECT asText(%s) as %s, ". implode(',', $attribute_cols) ." from {%s}";
  $res = db_query($query, $geometry_col, $geometry_col, $info->name);
  $features = array();

  // Go through results
  while ($row = db_fetch_array($res)) {
    $attributes = array();
    foreach ($attribute_cols as $attr_name) {
      $attr_val = $row[$attr_name];
      $attributes[$attr_name] = $attr_val;
    }
    // Put together features
    $features[] = array(
      'wkt' => $row[$geometry_col],
      'attributes' => $attributes,
      'projection' => $srid,
    );
  }
  
  // Create layer data array
  $layer = $info->data;
  $layer['id'] = $info->name;
  $layer['name'] = $info->title;
  $layer['features'] = $features;
  
  return $layer;
}
