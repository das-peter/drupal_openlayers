<?php

function openlayers_openlayers_source_geojson_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers_source_geojson',
      'file' => 'openlayers_source_geojson.inc',
    )
  );
}

class openlayers_source_geojson extends openlayers_source {

}
