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

  function options_form($form, &$form_state) {
    $layer_types = array(
      'Road',
      'Aerial',
      'AerialWithLabels',
      'collinsBart',
      'ordnanceSurvey'
    );

    return array(
      'key' => array(
        '#title' => t('Key'),
        '#type' => 'textfield',
        '#default_value' => $this->getOption('key', '')
      ),
      'imagerySet' => array(
        '#title' => t('Imagery set'),
        '#type' => 'select',
        '#default_value' => $this->getOption('imagerySet', 'Road'),
        '#options' => array_combine($layer_types, $layer_types)
      )
    );
  }

}
