<?php

function _openlayers_openlayers_layers_info() {
  $layers = array();

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'google_satellite';
  $layer->title = t('Google Maps Satellite');
  $layer->description = t('Google Maps Satellite Imagery. Legally encumbered.');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'satellite',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layers_google',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'google_hybrid';
  $layer->title = t('Google Maps Hybrid');
  $layer->description = t('Google Maps with roads and terrain.');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'hybrid',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layers_google',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'google_normal';
  $layer->title = t('Google Maps Normal');
  $layer->description = t('Standard Google Maps Roads');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'normal',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layers_google',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'google_physical';
  $layer->title = t('Google Maps Physical');
  $layer->description = t('Google Maps Hillshades');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'physical',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layers_google',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'yahoo_satellite';
  $layer->title = t('Yahoo Maps Satellite');
  $layer->description = t('');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'satellite',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layers_yahoo',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'yahoo_street';
  $layer->title = t('Yahoo Maps Street');
  $layer->description = t('');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'street',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layers_yahoo',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'yahoo_hybrid';
  $layer->title = t('Yahoo Maps Hybrid');
  $layer->description = t('');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'hybrid',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layers_yahoo',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;
  
  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'virtualearth_street';
  $layer->title = t('Virtual Earth Street');
  $layer->description = t('');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'street',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layers_virtualearth',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'virtualearth_satellite';
  $layer->title = t('Virtual Earth Satellite');
  $layer->description = t('');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'satellite',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layers_virtualearth',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  $layer = new stdClass();
  $layer->api_version = 1;
  $layer->name = 'virtualearth_hybrid';
  $layer->title = t('Virtual Earth Hybrid');
  $layer->description = t('');
  $layer->data = array(
    'baselayer' => TRUE,
    'type' => 'hybrid',
    'projection' => array('900913'),
    'layer_type' => 'openlayers_layers_virtualearth',
    'events' => array(),
  );
  $layers[$layer->name] = $layer;

  return $layers;
}
