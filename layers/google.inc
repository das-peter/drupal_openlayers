<?php
// $Id$

function layertype_google() {
  $type = array(
    'shortname' => 'Google Maps',
    'longname' => t('Google Maps'),
    'uri' => FALSE,
    'properties' => array(
      'sphericalMercator' => array(
        'type' => 'checkbox',
        'title' => t('Use as spherical Mercator?'),
        'description' => t('This will cause all interactions with the map to be in the actual map projection, which allows support for vector drawing, overlaying other maps, etc.'),
      ),
    ),
  );

  return $type;
}

/**
 * Using the map array from a node, build the constructor
 */
function layertype_google_js_constructor($layer) {
  static $gmap_key;
  if (!isset($gmap_key)) {
    $gmap_key = keys_api_get_key('gmap', $_SERVER['HTTP_HOST']);
    drupal_set_html_head('<script src="http://maps.google.com/maps?file=api&amp;v=2&amp;key='. $gmap_key .'" type="text/javascript"></script>');
  }
  return "new OpenLayers.Layer.Google('{$layer['title']}');";
}
