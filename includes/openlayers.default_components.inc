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
  $component->description = 'Display an alert on the top of the map.';
  $component->class = 'openlayers_component_bootstrapjs_alert';
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
  $component->class = 'openlayers_component_setvalues';
  $component->options = array(
    'latitude' => 'edit-options-view-center-lat',
    'longitude' => 'edit-options-view-center-lon',
    'rotation' => 'edit-options-view-rotation',
    'zoom' => 'edit-options-view-zoom',
  );
  $export['map_edit_form_values'] = $component;

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'map_edit_form_setcenter';
  $component->name = 'Map center on mouse click';
  $component->description = 'Upon clicking, center the map at the mouse position.';
  $component->class = 'openlayers_component_js';
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

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'graticule';
  $component->name = 'Graticule with inline JS';
  $component->description = 'Display a graticule on the map.';
  $component->class = 'openlayers_component_js';
  $component->options = array(
    'javascript' => 'var graticule = new ol.Graticule({
    strokeStyle: new ol.style.Stroke({
        color: \'rgba(255,120,0,0.9)\',
        width: 2,
        lineDash: [0.5, 4]
    })
});
graticule.setMap(data.map);',
  );
  $export['graticule'] = $component;

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'geolocation';
  $component->name = 'Geolocation';
  $component->description = '';
  $component->class = 'openlayers_component_js';
  $component->options = array(
    'javascript' => 'var geolocation = new ol.Geolocation({
  projection: data.map.getView().getProjection()
});

var accuracyFeature = new ol.Feature();
accuracyFeature.bindTo(\'geometry\', geolocation, \'accuracyGeometry\');

var positionFeature = new ol.Feature();
positionFeature.setStyle(new ol.style.Style({
  image: new ol.style.Circle({
    radius: 6,
    fill: new ol.style.Fill({
      color: \'#000000\'
    }),
    stroke: new ol.style.Stroke({
      color: \'#fff\',
      width: 2
    })
  })
}));

positionFeature.bindTo(\'geometry\', geolocation, \'position\')
    .transform(function() {}, function(coordinates) {
      return coordinates ? new ol.geom.Point(coordinates) : null;
    });

// from https://github.com/DmitryBaranovskiy/raphael
function elastic(t) {
  return Math.pow(2, -10 * t) * Math.sin((t - 0.075) * (2 * Math.PI) / 0.3) + 1;
}

// listen to changes in position
geolocation.on(\'change\', function(evt) {
    var coordinate = geolocation.getPosition();
    var duration = 2000;
    var start = +new Date();
    var pan = ol.animation.pan({
        duration: duration,
        source: (data.map.getView().getCenter()),
        start: start
    });
    var bounce = ol.animation.bounce({
        duration: duration,
        resolution: 2 * data.map.getView().getResolution(),
        start: start
    });
    var rotate = ol.animation.rotate({
        duration: duration,
        rotation: -4 * Math.PI,
        start: start
    });
    data.map.beforeRender(pan, bounce, rotate);
    data.map.getView().setZoom(6);
    data.map.getView().setCenter(coordinate);
});

geolocation.setTracking(true);

var featuresOverlay = new ol.FeatureOverlay({
  map: data.map,
  features: [accuracyFeature, positionFeature]
});
',
  );
  $export['geolocation'] = $component;

  return $export;
}
