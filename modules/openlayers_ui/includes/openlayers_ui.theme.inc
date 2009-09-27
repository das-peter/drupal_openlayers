<?php
// $Id$

/**
 * @file
 * This file holds the theme functions for openlayers ui module
 *
 * @ingroup openlayers
 */

/**
 * Theme function for form description of layers
 */
function theme_openlayers_ui_form_layer_description($layer_title = '', $layer_description = '') {
  if ($layer_description) {
    $output = $layer_title . ' - <span class="openlayers-form-layer-description">' . $layer_description . '</span>';
  }
  else {
    $output = $layer_title;
  }
  return $output;
}

/**
 * Theme function for form description of projection
 */
function theme_openlayers_ui_form_projection_description($projection_title = '', $available_layers = array(), $layers = array()) {
  // Get names of layers
  $names = array();
  foreach ($available_layers as $k => $val) {
    $names[] = $layers[$val]['name'];
  }

  if ($names) {
    $output = '
      ' . $projection_title . ' -
      <span class="openlayers-form-projection-description">
        ' . t('Available Layers') . ':
        ' . implode(', ', $names) . '
      </span>
    ';
  }
  else {
    $output = $projection_title;
  }
  return $output;
}
