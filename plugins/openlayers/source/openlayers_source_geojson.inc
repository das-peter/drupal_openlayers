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

  function options_form(&$form, &$form_state) {
    $form['options']['url'] = array(
      '#title' => t('URL'),
      '#type' => 'textfield',
      '#default_value' => $this->getOption('url'),
    );
  }
}
