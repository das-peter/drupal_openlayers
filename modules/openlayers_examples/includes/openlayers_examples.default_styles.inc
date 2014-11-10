<?php

function openlayers_examples_default_styles() {
  $export = array();

  $style = new stdClass();
  $style->disabled = FALSE; /* Edit this to true to make a default style disabled initially */
  $style->api_version = 1;
  $style->machine_name = 'openlayers_examples_blue_marker';
  $style->name = 'OpenLayers blue marker';
  $style->description = '';
  $style->class = 'openlayers__style__js';
  $style->options = array(
    'javascript' => 'var style = new ol.style.Style({
                        image: new ol.style.Icon(({
                            scale: 1,
                            anchor: [0.5, 1],
                            anchorXUnits: \'fraction\',
                            anchorYUnits: \'fraction\',
                            src: \'/sites/all/modules/openlayers/modules/openlayers_examples/assets/marker-icon.png\'
                        }))
                    });',
  );
  $export['openlayers_examples_blue_marker'] = $style;

  return $export;
}
