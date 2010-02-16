<?php
// $Id$

/**
 * @file
 * This file contains preset implementations
 *
 * @ingroup openlayers
 */

/**
 * Preset Implementation
 *
 * Internal callback for openlayers preset implementation.
 *
 * @return
 *   Array of presets
 */
function _openlayers_openlayers_presets() {
  // Create full preset array
  $default = new stdClass();
  $default->api_version = 1;
  $default->name = 'default';
  $default->title = t('Default Map');
  $default->description = t('This is the default map preset that comes with the OpenLayers module.');
  $default->data = array(
    'projection' => '4326',
    'width' => 'auto',
    'default_layer' => 'osm_mapnik',
    'height' => '400px',
    'center' => array(
      'initial' => array(
        'centerpoint' => '0,0',
        'zoom' => '2'
      )
    ),
    'options' => array(
      'displayProjection' => '4326',
      'maxExtent' => openlayers_get_extent('4326'),
    ),
    'behaviors' => array(
      'openlayers_behavior_panzoombar' => array(),
      'openlayers_behavior_layerswitcher' => array(),
      'openlayers_behavior_attribution' => array(),
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_navigation' => array(),
    ),
    'layers' => array(
      'osm_mapnik' => 'osm_mapnik',
    )
  );
  return array('default' => $default);
}
