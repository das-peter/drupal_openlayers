<?php

function openlayers_openlayers__source__kml_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers__source__kml',
      'file' => 'openlayers__source__kml.inc',
    )
  );
}

class openlayers__source__kml extends openlayers_source {

  function options_form(&$form, &$form_state) {
    $form['options']['url'] = array(
      '#title' => t('URL'),
      '#type' => 'textfield',
      '#default_value' => $this->getOption('url'),
    );
  }
}
