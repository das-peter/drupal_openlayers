<?php

function openlayers_openlayers__source__stamen_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers__source__stamen',
      'file' => 'openlayers__source__stamen.inc',
    )
  );
}

class openlayers__source__stamen extends openlayers_source {

  function options_form(&$form, &$form_state) {
    $form['options']['layer'] = array(
      '#title' => t('Source type'),
      '#type' => 'select',
      '#default_value' => $this->getOption('layer', 'osm'),
      '#options' => array(
        'terrain-labels' => 'Terrain labels',
        'watercolor' => 'Watercolor',
      )
    );
  }

}
