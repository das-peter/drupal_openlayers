<?php

/**
 * @file
 * This file holds the theme functions for openlayers module
 *
 * @ingroup openlayers
 */

/**
 * Theme function for openlayers_map
 */
function theme_openlayers_map($args) {
  $map = $args['map'];
  $map_name = isset($map['map_name']) ? $map['map_name'] : '';
  // To ensure that any controls are on the map correctly, we need to
  // wrap the map in a container, and take into account percentage dimensions
  $container_width = $map['width'];
  $container_height = $map['height'];
  $map['width'] = (strpos($map['width'], '%') > 0) ? '100%' : $map['width'];
  $map['height'] = (strpos($map['height'], '%') > 0) ? '100%' : $map['height'];

  $links = array();
  if (isset($map['map_name'])) {
    $links = array(
      '#type' => 'contextual_links',
      '#contextual_links' => array(
        'openlayers' => array(
          'admin/structure/openlayers/maps/list', array($map['map_name'])
        )
      )
    );
  }

  // Create output
  $output = '
    <div style="width: ' . $container_width . '; height: ' . $container_height .
      ';" id="openlayers-container-' . $map['id'] .
      '" class="contextual-links-region openlayers-container openlayers-container-map-' . $map_name . '">';
  $output .= drupal_render($links);
  $output .= '<div style="width: ' . $map['width'] . '; height: ' . $map['height'] . ';" id="' .
      $map['id'] . '" class="openlayers-map openlayers-map-' . $map_name . '"></div>
    </div>';
  return $output;
}

/**
 * Theme function to be able to override styles
 */
function theme_openlayers_styles($args) {
  return $args['styles'];
}
