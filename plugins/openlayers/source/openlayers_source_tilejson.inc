<?php

function openlayers_openlayers_source_tilejson_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers_source_tilejson',
      'file' => 'openlayers_source_tilejson.inc'
    )
  );
}

class openlayers_source_tilejson extends openlayers_source {

  function options_form(&$form, &$form_state) {
    $form['options']['url'] = array(
      '#title' => t('URL'),
      '#type' => 'textfield',
      '#default_value' => $this->getOption('url'),
    );
  }

}
