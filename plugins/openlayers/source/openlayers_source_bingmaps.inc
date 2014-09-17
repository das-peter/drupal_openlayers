<?php

function openlayers_openlayers_source_bingmaps_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers_source_bingmaps',
      'file' => 'openlayers_source_bingmaps.inc',
    )
  );
}

class openlayers_source_bingmaps extends openlayers_source {

  function options_form($defaults = array()) {
    $layer_types = array(
      'Road' => 'Road',
      'AerialWithLabels' => 'Hybrid',
      'Aerial' => 'Aerial',
    );

    return array(
      'type' => array(
        '#title' => t('Source type'),
        '#type' => 'select',
        '#default_value' => isset($this->data['type']) ? $this->data['type'] : 'Road',
        '#options' => $layer_types
      )
    );
  }

}
