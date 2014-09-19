<?php

function openlayers_default_components() {
  $export = array();

  $component = new stdClass;
  $component->api_version = 1;
  $component->machine_name = 'component_bootstrapjs_popup';
  $component->name = 'Bootstrap JS popup';
  $component->description = 'Bootstrap JS popup component is a component who allows you to display popup when clicking on a feature. It requires the bootstrapjs module to work.';
  $component->class = 'openlayers_component_bootstrapjs_popup';
  $component->options = array();
  $export['component_bootstrapjs_popup'] = $component;

  $component = new stdClass;
  $component->api_version = 1;
  $component->machine_name = 'component_bootstrapjs_alert';
  $component->name = 'Bootstrap JS alert';
  $component->description = '';
  $component->class = 'openlayers_component_bootstrapjs_alert';
  $component->options = array(
    'message' => '<strong>Success !</strong>The map has been loaded.'
  );
  $export['component_bootstrapjs_alert'] = $component;

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'graticule_with_inline_js';
  $component->name = 'Graticule with inline JS';
  $component->description = '';
  $component->class = 'openlayers_component_evaljs';
  $component->options = array(
    'javascript' => 'var graticule = new ol.Graticule({
    strokeStyle: new ol.style.Stroke({
        color: \'rgba(255,120,0,0.9)\',
        width: 2,
        lineDash: [0.5, 4]
    })
});
graticule.setMap(map);',
  );
  $export['graticule_with_inline_js'] = $component;

  return $export;
}
