<?php
/**
 * Defines default projections so that most users don't need to bother about setting up projections.
 * 
 * @return array<stdClass>
 */
function _openlayers_openlayers_projections(){
  $projections = array();
  
  $openlayers_projections = new stdClass();
  $openlayers_projections->disabled = FALSE; /* Edit this to true to make a default openlayers_projections disabled initially */
  $openlayers_projections->api_version = 1;
  $openlayers_projections->identifier = 'EPSG:2056';
  $openlayers_projections->authority = 'EPSG';
  $openlayers_projections->code = '2056';
  $openlayers_projections->definition = '+proj=somerc +lat_0=46.95240555555556 +lon_0=7.439583333333333 +k_0=1 +x_0=2600000 +y_0=1200000 +ellps=bessel +towgs84=674.374,15.056,405.346,0,0,0,0 +units=m +no_defs';
  $openlayers_projections->projectedextentleft = '2485869.5728';
  $openlayers_projections->projectedextentbottom = '1076443.1884';
  $openlayers_projections->projectedextentright = '2837076.5648';
  $openlayers_projections->projectedextenttop = '1299941.7864';
  $openlayers_projections->data = '';
  $projections[$openlayers_projections->identifier] = $openlayers_projections;
  
  $openlayers_projections = new stdClass();
  $openlayers_projections->disabled = FALSE; /* Edit this to true to make a default openlayers_projections disabled initially */
  $openlayers_projections->api_version = 1;
  $openlayers_projections->identifier = 'EPSG:3857';
  $openlayers_projections->authority = 'EPSG';
  $openlayers_projections->code = '3857';
  $openlayers_projections->definition = '+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +wktext  +no_defs';
  $openlayers_projections->projectedextentleft = '-20037508.34';
  $openlayers_projections->projectedextentbottom = '-20037508.34';
  $openlayers_projections->projectedextentright = '20037508.34';
  $openlayers_projections->projectedextenttop = '20037508.34';
  $openlayers_projections->data = '';
  $projections[$openlayers_projections->identifier] = $openlayers_projections;
  
  $openlayers_projections = new stdClass();
  $openlayers_projections->disabled = FALSE; /* Edit this to true to make a default openlayers_projections disabled initially */
  $openlayers_projections->api_version = 1;
  $openlayers_projections->identifier = 'EPSG:4326';
  $openlayers_projections->authority = 'EPSG';
  $openlayers_projections->code = '4326';
  $openlayers_projections->definition = '+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs';
  $openlayers_projections->projectedextentleft = '-180';
  $openlayers_projections->projectedextentbottom = '-90';
  $openlayers_projections->projectedextentright = '180';
  $openlayers_projections->projectedextenttop = '90';
  $openlayers_projections->data = '';
  $projections[$openlayers_projections->identifier] = $openlayers_projections;

  // TODO Remove before publishing as replaced by EPSG:3857
  $openlayers_projections = new stdClass();
  $openlayers_projections->disabled = FALSE; /* Edit this to true to make a default openlayers_projections disabled initially */
  $openlayers_projections->api_version = 1;
  $openlayers_projections->identifier = 'EPSG:900913';
  $openlayers_projections->authority = 'EPSG';
  $openlayers_projections->code = '900913';
  $openlayers_projections->definition = '+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +wktext  +no_defs';
  $openlayers_projections->projectedextentleft = '345';
  $openlayers_projections->projectedextentbottom = '3245';
  $openlayers_projections->projectedextentright = '3245';
  $openlayers_projections->projectedextenttop = '345';
  $openlayers_projections->data = '';
  $projections[$openlayers_projections->identifier] = $openlayers_projections;
  
  return $projections;
}