<?php

function openlayers_openlayers_source_tilejson_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers_source_tilejson',
    )
  );
}

class openlayers_source_tilejson extends openlayers_source {

  function options_form() {
    return array(
      'url' => array(
        '#title' => t('URL'),
        '#type' => 'textfield',
        '#default_value' => $this->getOption('url'),
      )
    );
  }

}
