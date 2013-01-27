<?php
/**
 * @file
 * KML Layer Type
 */

/**
 * Define the Ctools plugin options.
 */
function openlayers_openlayers_layer_type_kml_openlayers_layer_types() {
  return array(
    'title' => t('KML'),
    'description' => t('<a href="!url">KML</a> overlay.',
      array('!url' => 'http://en.wikipedia.org/wiki/Keyhole_Markup_Language')),
    'layer_type' => array(
      'file' => 'openlayers_layer_type_kml.inc',
      'class' => 'openlayers_layer_type_kml',
      'parent' => 'openlayers_layer_type',
    ),
  );
}

/**
 * OpenLayers KML Layer Type class
 */
class openlayers_layer_type_kml extends openlayers_layer_type {

  /**
   * Provide initial values for options.
   */
  function options_init() {
    return parent::options_init() +
    array(
      'layer_handler' => 'kml',
      'projection' => array('4326'),
      'baselayer' => FALSE,
      'vector' => TRUE,
      'formatOptions' => array(
        'extractStyles' => TRUE,
        'extractAttributes' => TRUE,
      ),
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form($defaults = array()) {
    return array(
      'url' => array(
        '#type' => 'textfield',
        '#title' => t('URL'),
        '#description' => t('The URL of the KML file.'),
        '#maxlength' => 1024,
        '#default_value' => isset($this->data['url']) ?
          $this->data['url'] : ''
      ),
      'formatOptions' => array(
        'extractStyles' => array(
          '#type' => 'checkbox',
          '#title' => t('Extract Styles'),
          '#description' => t('Extract styles from KML.'),
          '#default_value' => isset(
            $this->data['formatOptions']['extractStyles']) ?
            $this->data['formatOptions']['extractStyles'] : TRUE,
        ),
        'extractTracks' => array(
          '#type' => 'checkbox',
          '#title' => t('Extract Tracks'),
          '#description' => t('Extract tracks from KML.'),
          '#default_value' => isset(
          $this->data['formatOptions']['extractTracks']) ?
            $this->data['formatOptions']['extractTracks'] : TRUE,
        ),
        'extractAttributes' => array(
          '#type' => 'checkbox',
          '#title' => t('Extract Attributes'),
          '#description' => t('Extract attributes from KML.'),
          '#default_value' => isset(
            $this->data['formatOptions']['extractAttributes']) ?
            $this->data['formatOptions']['extractAttributes'] : TRUE,
        ),
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers')
      . '/plugins/layer_types/openlayers_layer_type_kml.js');
  }
}
