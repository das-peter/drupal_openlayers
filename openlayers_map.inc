<?php
// $Id$

/**
 * Implementation of hook_access
 */
function openlayers_map_access($op, $node) {
  global $user;
  switch ($op) {
    case 'create':
      return user_access('create map');
      break;
    case 'update':
    case 'delete':
      if (user_access('edit own map') && ($user->uid == $node->uid)) {
        return TRUE;
      }
      return user_access('edit map');
      break;
  }
}

/**
 * Implementation of hook_load
 */
function openlayers_map_load($node) {
  //TODO
  //dpm(__FUNCTION__);
}

/**
 * Implementation of hook_prepare
 */
function openlayers_map_prepare(&$node) {
  //TODO
  //dpm(__FUNCTION__);
}

/**
 * Implementation of hook_form
 */
function openlayers_map_form(&$node, &$param) {
  //TODO
  //dpm(__FUNCTION__);
}

/**
 * This gets called for hook_form_alter('ol_map_node_form', &$form)
 */
function openlayers_map_node_form_alter(&$form) {
  //TODO
  //dpm(__FUNCTION__);
}

/**
 * Implementation of hook_validate
 */
function openlayers_map_validate($node, &$form) {
  //TODO
  //dpm(__FUNCTION__);
}

/**
 * Implementation of hook_submit
 */
function openlayers_map_submit(&$node) {
  //TODO
  //dpm(__FUNCTION__);
}

/**
 * Implementation of hook_insert
 */
function openlayers_map_insert($node) {
  //TODO
  //dpm(__FUNCTION__);
}

/**
 * Implementation of hook_update
 */
function openlayers_map_update($node) {
  //TODO
  //dpm(__FUNCTION__);
}

/**
 * Implementation of hook_delete
 */
function openlayers_map_delete(&$node) {
  //TODO
  //dpm(__FUNCTION__);
}

/**
 * Implementation of hook_view
 * For map nodes display an OpenLayers viewer
 */
function openlayers_map_view($node) {
  //TODO
  //dpm(__FUNCTION__);
}

function theme_openlayers_map($id, $layers, $controls = array(), $add_js = '') {
  if (DEVELMODE) {
    drupal_add_js(drupal_get_path('module', 'openlayers') .'/lib/OpenLayers.js');
  }
  else {
    drupal_add_js(drupal_get_path('module', 'openlayers') .'/OpenLayers.js');
  }
  drupal_add_css(drupal_get_path('module', 'openlayers') .'/openlayers.css');

  $ol_js_head  = "$(document).ready(function() {\n";
  $ol_js_head .= "  var map = new OpenLayers.Map('$id');\n";
//TODO - add these settings.
// OpenLayers.ImgPath = '';
// variable_get('ol_image_error_color', 'pink')
// variable_get('ol_image_reload_attempts', 0)
// variable_get('ol_dpi', 72)

  $layer_ids = array();
  $layer_add_js = array();
  $counter = 0;
  $ol_js_body = '';
  $ol_js_foot = "  " .variable_get('ol_add_js', '') ."\n  ";
  foreach ($layers as $layer) {
    $counter++;
    $constructor = "layertype_{$layer['type']}_js_constructor";
    $ol_js_body .= "  var layer$counter = " . $constructor($layer) . "\n";
    $layer_ids[] = "layer$counter";
    $layer_add_js[] = $layer['add_js'];
  }
  $ol_js_body .= "  map.addLayers([" . implode(',', $layer_ids) . "]);\n";
  $ol_js_body .= "  map.zoomToMaxExtent();\n"; //TODO - Make some choices for this

  $ol_js_foot .= implode("\n  ", $layer_add_js);
  $ol_js_foot .= "\n  ";
  $ol_js_foot .= ($add_js != '' ? $add_js . "\n" : '');
  $ol_js_foot .= "});";

  $js = $ol_js_head . $ol_js_body . $ol_js_foot;
  drupal_add_js($js, 'inline');

  return "<div id=\"$id\" class=\"ol-map\"></div>";
}