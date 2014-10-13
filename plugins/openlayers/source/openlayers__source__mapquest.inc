<?php

function openlayers_openlayers__source__mapquest_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers__source__mapquest',
      'file' => 'openlayers__source__mapquest.inc',
    )
  );
}

class openlayers__source__mapquest extends openlayers_source {

  function options_form(&$form, &$form_state) {
    $layer_types = array(
      'osm' => 'OpenStreetMap',
      'sat' => 'Satellite',
      'hyb' => 'Hybrid',
    );

    $form['options']['layer'] = array(
      '#title' => t('Source type'),
      '#type' => 'select',
      '#default_value' => $this->getOption('layer', 'osm'),
      '#options' => $layer_types
    );
  }

}
