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

  $style = new stdClass();
  $style->disabled = FALSE; /* Edit this to true to make a default style disabled initially */
  $style->api_version = 1;
  $style->machine_name = 'openlayers_green_style';
  $style->name = 'OpenLayers green style';
  $style->description = '';
  $style->class = 'openlayers__style__js';
  $style->options = array(
    'javascript' => 'var fill = new ol.style.Fill({
   color: \'rgba(0, 255, 0, 0.7)\'
 });
 var stroke = new ol.style.Stroke({
   color: \'#FFFFFF\',
   width: 1
 });
 var style = [
   new ol.style.Style({
     image: new ol.style.Circle({
       fill: fill,
       stroke: stroke,
       radius: 2
     }),
     fill: fill,
     stroke: stroke
   })
 ];',
  );
  $export['openlayers_green_style'] = $style;

  $style = new stdClass();
  $style->disabled = FALSE; /* Edit this to true to make a default style disabled initially */
  $style->api_version = 1;
  $style->machine_name = 'openlayers_red_style';
  $style->name = 'OpenLayers red style';
  $style->description = '';
  $style->class = 'openlayers__style__js';
  $style->options = array(
    'javascript' => 'var fill = new ol.style.Fill({
   color: \'rgba(255, 0, 0, 0.7)\'
 });
 var stroke = new ol.style.Stroke({
   color: \'#FFFFFF\',
   width: 1
 });
 var style = [
   new ol.style.Style({
     image: new ol.style.Circle({
       fill: fill,
       stroke: stroke,
       radius: 2
     }),
     fill: fill,
     stroke: stroke
   })
 ];',
  );
  $export['openlayers_red_style'] = $style;

  $style = new stdClass();
  $style->disabled = FALSE; /* Edit this to true to make a default style disabled initially */
  $style->api_version = 1;
  $style->machine_name = 'openlayers_blue_style';
  $style->name = 'OpenLayers blue style';
  $style->description = '';
  $style->class = 'openlayers__style__js';
  $style->options = array(
    'javascript' => 'var fill = new ol.style.Fill({
   color: \'rgba(0, 0, 255, 0.7)\'
 });
 var stroke = new ol.style.Stroke({
   color: \'#FFFFFF\',
   width: 1
 });
 var style = [
   new ol.style.Style({
     image: new ol.style.Circle({
       fill: fill,
       stroke: stroke,
       radius: 2
     }),
     fill: fill,
     stroke: stroke
   })
 ];',
  );
  $export['openlayers_green_style'] = $style;

  return $export;
}
