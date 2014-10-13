<?php

function openlayers_examples_default_components() {
  $export = array();

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'openlayers_examples_geofield';
  $component->name = 'OpenLayers Example geofield';
  $component->description = '';
  $component->class = 'openlayers_examples__component__geofield';
  $component->options = '';
  $export['openlayers_examples_geofield'] = $component;

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'openlayers_examples_ajax_values';
  $component->name = 'openlayers_examples_ajax_values';
  $component->description = '';
  $component->class = 'openlayers__component__setvalues';
  $component->options = array(
    'latitude' => 'lat',
    'longitude' => 'lon',
    'rotation' => 'rot',
    'zoom' => 'zoom',
  );
  $export['openlayers_examples_ajax_values'] = $component;

  return $export;
}
