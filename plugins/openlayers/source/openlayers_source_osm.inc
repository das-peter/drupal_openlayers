<?php

function openlayers_openlayers_source_osm_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers_source_osm',
      'file' => 'openlayers_source_osm.inc',
    )
  );
}

class openlayers_source_osm extends openlayers_source {

}
