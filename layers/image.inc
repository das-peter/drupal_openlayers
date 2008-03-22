<?php
// $Id$

function layertype_image() {
  $type = array(
    'shortname' => 'Image',
    'longname' => t('Static image'),
    'uri' => TRUE,
    'properties' => array(
      'extent' => array(
        'type' => 'textfield',
        'title' => t('Image extent'),
        'description' => t('Enter the extent the image represents like "-180, -88.759, 180, 88.759"'),
        'required' => TRUE),
      'size' => array(
        'type' => 'textfield',
        'title' => t('Image size'),
        'description' => t('Image size in pixel like "580, 288".'),
        'required' => TRUE),
    ),
  );

  return $type;
}

/**
 * Using the map array from a node, build the constructor
 */
function layertype_image_js_constructor($layer) {
  return "new OpenLayers.Layer.Image('{$layer['title']}', '{$layer['uri']}', new OpenLayers.Bounds({$layer['properties']['extent']}), new OpenLayers.Size({$layer['properties']['size']}));";
}
