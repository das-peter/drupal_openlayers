<?php

/**
 * @file
 * This file holds views theme function for style plugin.
 *
 * @ingroup openlayers
 */

/**
 * Implementation of theme function
 */
function theme_openlayers_views_map($args) {
  return (isset($args['title']) ? '<h3>' . $args['title'] . '</h3>' : '') .
    '<div class="openlayers-views-map">'
    . $args['map']
    . '</div>';
}

/**
 * Implementation of theme function
 */
function theme_openlayers_image_formatter($variables) {
  $item = $variables['item'];

  $image = array(
    'path' => $item['uri'],
    'alt'  => $item['alt'],
  );

  if (isset($item['width']) && isset($item['height'])) {
    $image['width'] = $item['width'];
    $image['height'] = $item['height'];
  }

  if ($variables['display_settings']['imageStyle']) {
    $image_style = image_style_load($variables['display_settings']['imageStyle']);
    $preview_file = image_style_url($image_style['name'], $image['path']);
    image_style_create_derivative($image_style, $image['path'], $preview_file);
    $output = $preview_file;
  }
  else {
    $output = file_create_url($image['path']);
  }

  return $output;
}
