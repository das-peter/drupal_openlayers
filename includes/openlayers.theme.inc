<?php
// $Id$

/**
 * @file
 * This file holds the theme functions for openlayers module
 *
 * @ingroup openlayers
 */

/**
 * Theme function for openlayers_map
 */
function theme_openlayers_map($map = array()) {
  $output = '
    <div id="'. $map['id'] .'" class="openlayers-map openlayers-preset-' . $map['preset_name'] .'"></div>
  ';
  return $output;
}

/**
 * Theme function to be able to override styles
 */
function theme_openlayers_vector_styles($styles = array(), $map = array()) {
  // Default is to just send the processed styles back
  return $styles;
}