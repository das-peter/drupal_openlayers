<?php

function openlayers_openlayers_component_setvalues_openlayers_component() {
  return array(
    'handler' => array(
      'class' => 'openlayers_component_setvalues',
      'file' => 'openlayers_component_setvalues.inc',
    )
  );
}

class openlayers_component_setvalues extends openlayers_component {

  function options_form($form, &$form_state) {
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
