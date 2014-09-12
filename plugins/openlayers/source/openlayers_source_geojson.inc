<?php

function openlayers_openlayers_source_geojson_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers_source_geojson',
    )
  );
}

class openlayers_source_geojson extends openlayers_source {

  function options_init() {
    return array(
      'data' => array()
    );
  }

  function options_form($defaults = array()) {
    $layer_types = array(
      'Road' => 'Road',
      'AerialWithLabels' => 'Hybrid',
      'Aerial' => 'Aerial',
    );

    return array(
      'type' => array(
        '#title' => t('Source type'),
        '#type' => 'select',
        '#default_value' => isset($this->data['type']) ? $this->data['type'] : 'Road',
        '#options' => $layer_types
      )
    );
  }

  function settings_form() {
    return array();
  }

  function attached() {
    return array(
      'js' => array(
        drupal_get_path('module', 'openlayers') . '/plugins/source/openlayers_source_geojson.js'
      )
    );
  }

  function render(&$map) {}
}
