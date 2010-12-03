<?php
// $Id$

/**
 * @file
 * This file holds views theme function for style plugin.
 *
 * @ingroup openlayers
 */

/**
 * Implementation of theme function
 */
function theme_openlayers_views_map($view, $options = array(),
  $map = array(), $title = FALSE) {
  return (($title) ? '<h3>'. $title .'</h3>' : '') . 
    '<div class="openlayers-views-map">'
    . $map['themed']
    . '</div>';
}
