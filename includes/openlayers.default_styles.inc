<?php

function openlayers_default_styles() {
  $export = array();

  $style = new stdClass;
  $style->api_version = 1;
  $style->machine_name = 'openlayers_style_default';
  $style->name = 'OpenLayers default style';
  $style->description = '';
  $style->class = 'openlayers__style__style';
  $style->options = array();
  $export['openlayers_style_default'] = $style;

  return $export;
}
