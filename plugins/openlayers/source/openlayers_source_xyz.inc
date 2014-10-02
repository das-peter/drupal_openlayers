<?php

function openlayers_openlayers_source_xyz_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers_source_xyz',
      'file' => 'openlayers_source_xyz.inc'
    )
  );
}

class openlayers_source_xyz extends openlayers_source {
  function options_form($form, &$form_state) {
    return array(
      'url' => array(
        '#title' => t('URL(s)'),
        '#type' => 'textarea',
        '#default_value' => $this->getOption('url') ? $this->getOption('url') : '',
      )
    );
  }
}
