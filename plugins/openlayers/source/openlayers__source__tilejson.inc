<?php

function openlayers_openlayers__source__tilejson_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers__source__tilejson',
      'file' => 'openlayers__source__tilejson.inc'
    )
  );
}

class openlayers__source__tilejson extends openlayers_source {

  function options_form(&$form, &$form_state) {
    $form['options']['url'] = array(
      '#title' => t('URL'),
      '#type' => 'textfield',
      '#default_value' => $this->getOption('url'),
    );
  }

}
