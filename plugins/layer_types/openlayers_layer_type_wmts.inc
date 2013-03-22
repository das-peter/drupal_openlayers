<?php
/**
 * @file
 * WMTS Layer Type
 */

/**
 * Define the Ctools plugin options.
 */
function openlayers_openlayers_layer_type_wmts_openlayers_layer_types() {
  return array(
    'title' => t('WMTS'),
    'description' => t('<a href="!url">Web Map Tile Service</a>',
      array('!url' => 'http://en.wikipedia.org/wiki/Tile_Map_Service')),
    'layer_type' => array(
      'file' => 'openlayers_layer_type_wmts.inc',
      'class' => 'openlayers_layer_type_wmts',
      'parent' => 'openlayers_layer_type',
    ),
  );
}

/**
 * OpenLayers TMS Layer Type class
 */
class openlayers_layer_type_wmts extends openlayers_layer_type {

  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_handler' => 'wmts',
    ) + parent::options_init();
  }

  /**
   * Options form which generates layers
   */
  function options_form($defaults = array()) {
    return array(
      'url' => array(
        '#type' => 'textfield',
        '#title' => t('Base URL'),
        '#default_value' => isset($this->data['url']) ? $this->data['url'] : '',
        '#description' => t('The base URL or request URL template for the WMTS service. Must be provided.'),
      ),
      'layer' => array(
        '#type' => 'textfield',
        '#title' => t('Layer Name'),
        '#default_value' => isset($this->data['layer']) ? $this->data['layer'] : '',
        '#description' => t('The layer identifier advertised by the WMTS service. Must be provided.'),
      ),
      'style' => array(
        '#type' => 'textfield',
        '#title' => t('Style'),
        '#default_value' => isset($this->data['style']) ? $this->data['style'] : '',
        '#description' => t('One of the advertised layer styles.'),
      ),
      'attribution' => array(
        '#type' => 'textfield',
        '#title' => t('Attribution'),
        '#default_value' => isset($this->data['attribution']) ? $this->data['attribution'] : '',
        '#description' => t('Attribution text, displayed when the attribution behavior has been added to the map.'),
      ),
      'matrixSet' => array(
        '#type' => 'textfield',
        '#title' => t('Matrix Set'),
        '#default_value' => isset($this->data['matrixSet']) ? $this->data['matrixSet'] : '',
        '#description' => t('One of the advertised matrix set identifiers. Must be provided.'),
      ),
      'formatSuffix' => array(
        '#type' => 'textfield',
        '#title' => t('Format Suffix'),
        '#default_value' => isset($this->data['formatSuffix']) ? $this->data['formatSuffix'] : '',
        '#description' => t('For REST request encoding, an image format suffix must be included in the request. If not provided, the suffix will be derived from the format property.'),
      ),
      'maxExtent' => array(
        '#type' => 'textfield',
        '#title' => t('Max Extent'),
        '#default_value' => isset($this->data['maxExtent']) ? $this->data['maxExtent'] : '',
        '#description' => t('Should consist of four values (left, bottom, right, top). The maximum extent for the layer. Defaults to null.'),
      ),
      'resolutions' => array(
        '#type' => 'textfield',
        '#title' => t('Resolutions'),
        '#default_value' => isset($this->data['resolutions']) ? $this->data['resolutions'] : '',
        '#description' => t('A list of map resolutions (map units per pixel) in descending order.'),
      ),
      'serverResolutions' => array(
        '#type' => 'textfield',
        '#title' => t('Server Resoultions'),
        '#maxlength'=>500,
        '#default_value' => isset($this->data['serverResolutions']) ? $this->data['serverResolutions'] : '',
        '#description' => t('A list of all resolutions available on the server.  Only set this property if the map resolutions differ from the server.'),
      ),
      'requestEncoding' => array(
        '#type' => 'select',
        '#title' => t('Request encoding'),
        '#options' => array('KVP' => 'KVP', 'REST' => 'REST'),
        '#default_value' => isset($this->data['requestEncoding']) ? $this->data['requestEncoding'] : '',
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') .
      '/plugins/layer_types/openlayers_layer_type_wmts.js');
  }
}
