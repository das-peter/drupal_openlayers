<?php

function openlayers_default_components() {
  $export = array();

  $component = new stdClass;
  $component->api_version = 1;
  $component->machine_name = 'component_bootstrapjs_popup';
  $component->name = 'Bootstrap JS popup';
  $component->description = 'Bootstrap JS popup component is a component who allows you to display popup when clicking on a feature. It requires the bootstrapjs module to work.';
  $component->class = 'openlayers__component__bootstrapjs_popup';
  $component->options = array();
  $export['component_bootstrapjs_popup'] = $component;

  $component = new stdClass;
  $component->api_version = 1;
  $component->machine_name = 'component_bootstrapjs_alert';
  $component->name = 'Bootstrap JS alert';
  $component->description = 'Display an alert on the top of the map.';
  $component->class = 'openlayers__component__bootstrapjs_alert';
  $component->options = array(
    'message' => '<strong>Success !</strong>The map has been loaded.'
  );
  $export['component_bootstrapjs_alert'] = $component;

  $component = new stdClass();
  $component->disabled = TRUE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'map_edit_form_values';
  $component->name = 'Map edit form values';
  $component->description = 'Provides values for the center, rotation and zoom in the map edit form.';
  $component->class = 'openlayers__component__setvalues';
  $component->options = array(
    'latitude' => 'edit-options-view-center-lat',
    'longitude' => 'edit-options-view-center-lon',
    'rotation' => 'edit-options-view-rotation',
    'zoom' => 'edit-options-view-zoom',
  );
  $export['map_edit_form_values'] = $component;

  $component = new stdClass();
  $component->disabled = TRUE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'map_edit_form_setcenter';
  $component->name = 'Map center on mouse click';
  $component->description = 'Upon clicking, center the map at the mouse position.';
  $component->class = 'openlayers__component__js';
  $component->options = array(
    'javascript' => 'data.map.on(\'click\', function(evt){
  var coordinate = evt.coordinate;
  var pan = ol.animation.pan({
    duration: 2000,
    source: (data.map.getView().getCenter())
  });
  data.map.beforeRender(pan);
  data.map.getView().setCenter(coordinate);
});',
  );
  $export['map_edit_form_setcenter'] = $component;

  return $export;
}
