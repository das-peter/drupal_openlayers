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
  $fetch = db_fetch_object(db_query('SELECT layers, controls, init_js, add_js FROM {ol_maps} WHERE vid = %d', $node->vid));
  $map['title'] = $node->title;
  $map['layers'] = unserialize($fetch->layers);
  $map['controls'] = unserialize($fetch->controls);
  $map['init_js'] = $fetch->init_js;
  $map['add_js'] = $fetch->add_js;

  $obj = new StdClass();
  $obj->map = $map;
  return $obj;
}

/**
 * Implementation of hook_prepare
 */
function openlayers_map_prepare(&$node) {
  //TODO; Needed?
}

/**
 * Implementation of hook_form
 */
function openlayers_map_form(&$node, &$param) {
  $nodetype = node_get_types('type', $node);
  $form = array();
  $form['title']= array(
    '#type' => 'textfield',
    '#title' => check_plain($nodetype->title_label),
    '#required' => TRUE,
    '#default_value' => $node->title,
    '#size' => 60,
    '#maxlength' => 255,
    '#weight' => -5
  );

  $form['body_filter'] = array(
    '#weight' => -4,
  );
  $form['body_filter']['body'] = array(
    '#type' => 'textarea',
    '#title' => check_plain($nodetype->body_label),
    '#default_value' => $node->body,
    '#required' => FALSE
  );
  $form['body_filter']['filter'] = filter_form($node->format);

  $form['layers'] = array(
    '#type' => 'textarea',
    '#title' => t('Layers'),
    '#description' => t('List all layers to be displayed. Enter one node id per line, top-most layer to bottom-most.'),
    '#rows' => 10,
    '#default_value' => ($node->nid ? implode("\n", $node->map['layers']) : ''),
    '#weight' => -3,
  );

  $form['controls'] = array(
    '#type' => 'fieldset',
    '#title' => t('Map controls'),
    '#description' => 'TODO',
    '#weight' => -2,
  );
  //TODO: All controls, and control-specific options (so each control into it's own fieldset and unchecked fieldsets collapsed?)
  $form['controls']['controls'] = array(
    '#type' => 'checkboxes',
    '#options' => array(
      'PanZoomBar' => t('Pan and Zoom'),
      'MouseToolbar' => t('Mouse toolbar'),
      'LayerSwitcher' => t('Layer switcher'),
      'Permalink' => t('Permalink'),
      'MousePosition' => t('Mouse position'),
      'OverviewMap' => t('Overview map'),
    ),
    '#default_value' => variable_get($node->map['controls'], array('PanZoomBar', 'OverviewMap')),
  );

  $form['init_js'] = array(
    '#type' => 'textarea',
    '#title' => t('Initialization javascript'),
    '#description' => t('Enter javascript to be executed after Mapset has been declared as <kbd>var map = new OpenLayers.Map();</kbd> and before layers will be declared and added to the mapset.'),
    '#rows' => 10,
    '#default_value' => $node->map['init_js'],
    '#weight' => -1,
  );

  $form['add_js'] = array(
    '#type' => 'textarea',
    '#title' => t('Additional JavaScript'),
    '#rows' => 15,
    '#default_value' => $node->map['add_js'],
    '#weight' => 0,
  );

  return $form;
}

/**
 * This gets called for hook_form_alter('ol_map_node_form', &$form)
 */
function openlayers_map_node_form_alter(&$form) {
  //TODO; Needed?
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
  $map['layers'] = explode("\n", $node->layers);
  $map['controls'] = $node->controls; //TODO
  $map['init_js'] = $node->init_js;
  $map['add_js'] = $node->add_js;

  $node->map = $map;
}

/**
 * Implementation of hook_insert
 */
function openlayers_map_insert($node) {
  db_query("INSERT INTO {ol_maps} (nid, vid, layers, controls, init_js, add_js) VALUES (%d, %d, '%s', '%s', '%s', '%s')", $node->nid,
    $node->vid,
    serialize($node->map['layers']),
    serialize($node->map['controls']),
    $node->map['init_js'],
    $node->map['add_js']);
}

/**
 * Implementation of hook_update
 */
function openlayers_map_update($node) {
  db_query("UPDATE {ol_maps} SET layers = '%s', controls = '%s', init_js = '%s', add_js = '%s' WHERE vid = %d", serialize($node->map['layers']),
    serialize($node->map['controls']),
    $node->map['init_js'],
    $node->map['add_js'],
    $node->vid);
}

/**
 * Implementation of hook_delete
 */
function openlayers_map_delete(&$node) {
  db_query('DELETE FROM {ol_maps} WHERE nid = %d', $node->nid);
}

/**
 * Implementation of hook_view
 * For map nodes display an OpenLayers viewer
 */
function openlayers_map_view($node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);
  if ($teaser) {
  }
  else {
    $layers = array();

    foreach ($node->map['layers'] as $lid) {
      $layer = node_load($lid);
      $layers[] = $layer->layer;
    }

    $node->content['map'] = array(
      '#value' => theme('openlayers_map', "node_{$node->nid}", $layers, $node->map['controls'], $node->map['init_js'], $node->map['add_js']),
      '#weight' => 1,
    );
  }
  return $node;
}

function theme_openlayers_map($id, $layers, $controls = array(), $init_js = '', $add_js = '') {
  if (DEVELMODE) {
    drupal_add_js(drupal_get_path('module', 'openlayers') .'/lib/OpenLayers.js');
  }
  else {
    drupal_add_js(drupal_get_path('module', 'openlayers') .'/OpenLayers.js');
  }
  drupal_add_css(drupal_get_path('module', 'openlayers') .'/openlayers.css');

  $ol_js_head  = "$(document).ready(function() {\n";
  $ol_js_head .= "  var map = new OpenLayers.Map('$id', { controls: [] });\n";

//TODO - add these settings.
// OpenLayers.ImgPath = '';
  if (($ol_image_error_color = variable_get('ol_image_error_color', 'pink')) != 'pink') {
  }
  if (($ol_image_reload_attempts = variable_get('ol_image_reload_attempts', '0')) != 0) {
  }
  if (($ol_dpi = variable_get('ol_dpi', 72)) != 72) {
  }

  if ($init_js != '') {
    $ol_js_head .= "  $init_js";
  }

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

  foreach ($controls as $control => $active) {
    if ($active != '0') {
      switch ($control) {
        case 'PanZoomBar':
          $ol_js_body .= "  map.addControl(new OpenLayers.Control.PanZoomBar());\n";
          break;
        case 'MouseToolbar':
          $ol_js_body .= "  map.addControl(new OpenLayers.Control.MouseToolbar());\n";
          break;
        case 'LayerSwitcher':
          $ol_js_body .= "  map.addControl(new OpenLayers.Control.LayerSwitcher());\n";
          break;
        case 'Permalink':
          $ol_js_body .= "  map.addControl(new OpenLayers.Control.Permalink());\n";
          break;
        case 'MousePosition':
          $ol_js_body .= "  map.addControl(new OpenLayers.Control.MousePosition());\n";
          break;
        case 'OverviewMap':
          $ol_js_body .= "  map.addControl(new OpenLayers.Control.OverviewMap());\n";
          break;
      }
    }
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