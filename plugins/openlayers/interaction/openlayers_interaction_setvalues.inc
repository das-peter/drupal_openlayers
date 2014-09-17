<?php

function openlayers_openlayers_interaction_setvalues_openlayers_interaction() {
  return array(
    'handler' => array(
      'class' => 'openlayers_interaction_setvalues',
      'file' => 'openlayers_interaction_setvalues.inc',
    )
  );
}

class openlayers_interaction_setvalues extends openlayers_interaction {

  function options_form() {
    return array(
      'latitude' => array(
        '#type' => 'textfield',
        '#title' => t('Latitude'),
        '#default_value' => $this->getOption('latitude'),
        '#description' => t(''),
      ),
      'longitude' => array(
        '#type' => 'textfield',
        '#title' => t('Longitude'),
        '#default_value' => $this->getOption('longitude'),
        '#description' => t(''),
      ),
      'rotation' => array(
        '#type' => 'textfield',
        '#title' => t('Rotation'),
        '#default_value' => $this->getOption('rotation', 0),
        '#description' => t(''),
      ),
      'zoom' => array(
        '#type' => 'textfield',
        '#title' => t('Zoom'),
        '#default_value' => $this->getOption('zoom', 0),
        '#description' => t(''),
      ),
    );
  }

}
