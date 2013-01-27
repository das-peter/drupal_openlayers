<?php

/**
 * Define the Ctools plugin options.
 */
function openlayers_openlayers_layer_type_mapbox_openlayers_layer_types() {
  return array(
    'title' => t('MapBox'),
    'description' => t('<a href="!url">MapBox</a> Custom Map',
      array('!url' => 'http://mapbox.com/')),
    'layer_type' => array(
      'file' => 'openlayers_layer_type_mapbox.inc',
      'class' => 'openlayers_layer_type_mapbox',
      'parent' => 'openlayers_layer_type',
    ),
  );
}

/**
 * @file MapBox layer type definition for OpenLayers
 */
class openlayers_layer_type_mapbox extends openlayers_layer_type {

  /**
   * Provide initial values for options.
   */
  function options_init() {
    return parent::options_init() +
    array(
      'urls' => implode("\n", array(
        'http://a.tiles.mapbox.com/mapbox/',
        'http://b.tiles.mapbox.com/mapbox/',
        'http://c.tiles.mapbox.com/mapbox/',
        'http://d.tiles.mapbox.com/mapbox/',
      )),
      'osm' => FALSE,
      'layername' => '',
      'layer_handler' => 'MapBox',
      'type' => 'png',
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form() {
    return array(
      'urls' => array(
        '#type' => 'textarea',
        '#title' => t('Base URLs'),
        '#description' => t('The list of base URLs specified on !tiles (with trailing "/"). For details, visit the !support site.', array(
          '!tiles' => l(t('TileStream'), 'http://tiles.mapbox.com/'),
          '!support' => l(t('MapBox Support'), 'http://support.mapbox.com/kb/tilestream/using-tilestream-with-drupal'),
        )),
        '#default_value' => !empty($this->data['urls']) ? $this->data['urls'] : '',
      ),
      'layername' => array(
        '#type' => 'textfield',
        '#title' => t('MapBox Layer Name'),
        '#description' => t('The layer name specified on !tiles.', array(
          '!tiles' => l(t('TileStream'), 'http://tiles.mapbox.com/'),
        )),
        '#default_value' => $this->data['layername']
      ),
      'layer_type' => array(
        '#type' => 'hidden',
        '#value' => 'openlayers_layer_type_mapbox',
      ),
      'osm' => array(
        '#type' => 'checkbox',
        '#default_value' => $this->data['osm'],
        '#title' => t('OSM Attribution'),
        '#description' => t('Required if OpenStreetMap data is used.'),
      ),
      'baselayer' => array(
        '#type' => 'checkbox',
        '#default_value' => $this->data['baselayer'],
        '#title' => t('BaseLayer'),
        '#description' => t('Uncheck to make this map an overlay.'),
      ),
      'type' => array(
        '#title' => t('File extension'),
        '#type' => 'select',
        '#default_value' => $this->data['type'],
        '#options' => drupal_map_assoc(array('png', 'jpg')),
      ),
      'resolutions' => array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#options' => array_combine(array_map('strval', openlayers_get_resolutions('900913')), range(0, 18)),
        '#title' => t('Zoom Level Range'),
        '#default_value' => isset($this->data['resolutions']) ? array_map('strval', $this->data['resolutions']) : array(),
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') . '/plugins/layer_types/openlayers_layer_type_mapbox.js');
    $this->data['urls'] = explode("\n", $this->data['urls']);
    $this->data['resolutions'] = array_map('floatval', array_values($this->data['serverResolutions']));
    return $this->options;
  }
}
