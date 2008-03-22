<?php
// $Id$

/**
 * This defines the WMS map type
 */
function layertype_wms() {
  $type = array(
    'shortname' => 'WMS',
    'longname' => t('Web Map Service'),
    'uri' => TRUE,
    'properties' => array(
      'isBaseMap' => array(
        'type' => 'checkbox',
        'default' => TRUE,
        'title' => t('Use as base map')),
      'encodeBBOX' => array(
        'type' => 'checkbox',
        'default' => FALSE,
        'title' => t('Encode bounding box commas.'),
        'description' => t('Should the BBOX commas be encoded?  The WMS spec says ‘no’, but some services want it that way.  Default false.')),
    ),
    'sublayers' => TRUE,
    'sublayers_callback' => 'layertype_wms_get_maps',
    'sublayers_help' => t('Enter (sub)layers to request from this WMS layer'),
  );

  return $type;
}

/**
 * Using the map array from a node, build the constructor
 */
function layertype_wms_js_constructor($layer) {
  return "new OpenLayers.Layer.WMS('{$layer['title']}', '{$layer['uri']}', {layers: '" . implode(',', $layer['sublayers']) . "'});";
}