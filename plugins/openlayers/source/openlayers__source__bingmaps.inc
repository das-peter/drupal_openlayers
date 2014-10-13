<?php

function openlayers_openlayers__source__bingmaps_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers__source__bingmaps',
      'file' => 'openlayers__source__bingmaps.inc',
    )
  );
}

class openlayers__source__bingmaps extends openlayers_source {

  function options_form(&$form, &$form_state) {
    $layer_types = array(
      'Road',
      'Aerial',
      'AerialWithLabels',
      'collinsBart',
      'ordnanceSurvey'
    );

    $form['options']['key'] = array(
      '#title' => t('Key'),
      '#type' => 'textfield',
      '#default_value' => $this->getOption('key', '')
    );
    $form['options']['imagerySet'] = array(
      '#title' => t('Imagery set'),
      '#type' => 'select',
      '#default_value' => $this->getOption('imagerySet', 'Road'),
      '#options' => array_combine($layer_types, $layer_types)
    );
  }

}
