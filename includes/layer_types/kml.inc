<?php
// $Id$

/**
 * @file
 * KML Layer Type
 */

/**
 * OpenLayers KML Layer Type class
 */
class openlayers_layer_type_kml extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_type' => 'kml',
      'layer_handler' => 'kml',
      'projection' => array('900913', '4326'),
      'baselayer' => FALSE,
      'formatOptions' => array(
        'extractStyles' => TRUE,
        'extractAttributes' => TRUE,
      ),
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form() {
    return array(
      'url' => array(
        '#type' => 'textfield',
        '#title' => t('URL'),
        '#description' => t('The URL of the KML file.  Note that without a proxy, you will not be able to use external URLs.'),
        '#maxlength' => 1024,
        '#default_value' => $this->data['url']
      ),
      'formatOptions' => array(
        'extractStyles' => array(
          '#type' => 'checkbox',
          '#title' => t('Extract Stlyes'),
          '#description' => t('Extract styles from KML.'),
          '#default_value' => isset($this->data['extractStyles']) ? $this->data['extractStyles'] : TRUE,
        ),
        'extractAttributes' => array(
          '#type' => 'checkbox',
          '#title' => t('Extract Attributes'),
          '#description' => t('Extract attributes from KML.'),
          '#default_value' => isset($this->data['extractAttributes']) ? $this->data['extractAttributes'] : TRUE,
        ),
      ),
      'custom_projection' => array(
        '#type' => 'select',
        '#title' => t('Custom Projection'),
        '#description' => t('Depending on the feed, choose the correct projection.'),
        '#options' => array('900913' => '900913', '4326' => '4326'),
        '#default_value' => isset($this->data['custom_projection']) ? $this->data['custom_projection'] : '4326',
      ),
      'layer_type' => array(
        '#type' => 'hidden',
        '#value' => 'openlayers_layer_type_kml'
      ),
      // Should allow for other projections
      'projection' => array(
       '0' => array(
          '#type' => 'hidden',
          '#value' => '900913',
        ),
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') .'/includes/layer_types/kml.js');
    return $this->options;
  }
}
