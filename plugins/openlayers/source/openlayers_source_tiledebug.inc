<?php

function openlayers_openlayers_source_tiledebug_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers_source_tiledebug',
      'file' => 'openlayers_source_tiledebug.inc'
    )
  );
}

class openlayers_source_tiledebug extends openlayers_source {

  function options_form() {
    return array(
      'maxZoom' => array(
        '#title' => t('Maxzoom'),
        '#type' => 'textfield',
        '#default_value' => $this->getOption('maxZoom', 22),
      )
    );
  }

}
