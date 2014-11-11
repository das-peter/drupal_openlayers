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

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'openlayers_examples_geolocation';
  $component->name = 'Geolocation example';
  $component->description = '';
  $component->class = 'openlayers_examples__component__geolocation';
  $component->options = array(
    'checkboxID' => 'trackPosition',
    'positionAccuracyID' => 'positionAccuracy',
    'altitudeID' => 'altitude',
    'altitudeAccuracyID' => 'altitudeAccuracy',
    'headingID' => 'heading',
    'speedID' => 'speed',
  );
  $export['openlayers_examples_geolocation'] = $component;

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'openlayers_examples_graticule';
  $component->name = 'Graticule example';
  $component->description = '';
  $component->class = 'openlayers__component__graticule';
  $component->options = array(
    'rgba' => '0, 0, 0, 0.2',
    'width' => '2',
    'lineDash' => '0.5, 4',
  );
  $export['openlayers_examples_graticule'] = $component;

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'openlayers_examples_zoom_to_source';
  $component->name = 'Zoom To Source Examples';
  $component->description = '';
  $component->class = 'openlayers__component__zoomtosource';
  $component->options = array(
    'source' => 'views_geojson_openlayers_examples_geojson_feed_2',
    'animations' => array(
      'pan' => '500',
      'zoom' => '500',
    ),
    'zoom' => 'auto',
    'enableAnimations' => 1,
  );
  $export['openlayers_examples_zoom_to_source'] = $component;

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'openlayers_examples_autopopup';
  $component->name = 'OpenLayers Examples Autopopup';
  $component->description = '';
  $component->class = 'openlayers__component__autopopup';
  $component->options = array(
    'source' => 'views_geojson_openlayers_examples_geojson_feed_2',
    'zoom' => 'auto',
    'enableAnimations' => 1,
    'animations' => array(
      'pan' => '500',
      'zoom' => '500',
    ),
    'positioning' => 'top-right'
  );
  $export['openlayers_examples_autopopup'] = $component;

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'openlayers_examples_tooltip_earthquakes';
  $component->name = 'Earthquakes tooltip';
  $component->description = '';
  $component->class = 'openlayers__component__tooltip';
  $component->options = array(
    'layer' => 'layer_vector_kml_earthquakes_heatmap',
    'positioning' => 'top-right'
  );
  $export['openlayers_examples_tooltip_earthquakes'] = $component;

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'openlayers_examples_simple_popup';
  $component->name = 'Simple popup';
  $component->description = '';
  $component->class = 'openlayers__component__popup';
  $component->options = array(
    'layer' => 'openlayers_examples_views_geojson_popup',
  );
  $export['openlayers_examples_simple_popup'] = $component;

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'openlayers_examples_earthquake_style';
  $component->name = 'Earthquake style';
  $component->description = '';
  $component->class = 'openlayers__component__js';
  $component->options = array(
    'javascript' => 'var map = data.map;

var styleCache = {};
var styleFunction = function(feature, resolution) {
  // 2012_Earthquakes_Mag5.kml stores the magnitude of each earthquake in a
  // standards-violating <magnitude> tag in each Placemark.  We extract it from
  // the Placemark\'s name instead.
  var name = feature.get(\'name\');
  var magnitude = parseFloat(name.substr(2));
  var radius = 5 + 20 * (magnitude - 5);
  var style = styleCache[radius];
  if (!style) {
    style = [new ol.style.Style({
      image: new ol.style.Circle({
        radius: radius,
        fill: new ol.style.Fill({
          color: \'rgba(255, 153, 0, 0.4)\'
        }),
        stroke: new ol.style.Stroke({
          color: \'rgba(255, 204, 0, 0.2)\',
          width: 1
        })
      })
    })];
    styleCache[radius] = style;
  }
  return style;
};

map.getLayers().forEach(function(layer){
   var source = layer.getSource();
   if (source.machine_name == \'source_kml_earthquakes\') {
       layer.setStyle(styleFunction);
   }
});',
  );
  $export['openlayers_examples_earthquake_style'] = $component;

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'openlayers_examples_simple_popup_earthquakes';
  $component->name = 'Earthquakes popup';
  $component->description = '';
  $component->class = 'openlayers__component__popup';
  $component->options = array(
    'layer' => 'layer_vector_kml_earthquakes_heatmap',
    'positioning' => 'top-right'
  );
  $export['openlayers_examples_simple_popup_earthquakes'] = $component;

  $component = new stdClass();
  $component->disabled = FALSE; /* Edit this to true to make a default component disabled initially */
  $component->api_version = 1;
  $component->machine_name = 'openlayers_examples_component_blocklayerswitcher';
  $component->name = 'Block Layer Switcher';
  $component->description = '';
  $component->class = 'openlayers_examples__component__blocklayerswitcher';
  $export['openlayers_examples_component_blocklayerswitcher'] = $component;

  return $export;
}
