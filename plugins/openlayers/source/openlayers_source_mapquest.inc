<?php

function openlayers_openlayers_source_mapquest_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers_source_mapquest',
    )
  );
}

class openlayers_source_mapquest extends openlayers_source {

  function options_form() {
    $layer_types = array(
      'osm' => 'OpenStreetMap',
      'sat' => 'Satellite',
      'hyb' => 'Hybrid',
    );

    return array(
      'layer' => array(
        '#title' => t('Source type'),
        '#type' => 'select',
        '#default_value' => $this->getOption('layer', 'osm'),
        '#options' => $layer_types
      )
    );
  }

}
