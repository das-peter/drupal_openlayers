<?php

function openlayers_openlayers_source_osm_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers_source_osm',
      'file' => 'openlayers_source_osm.inc',
    )
  );
}

class openlayers_source_osm extends openlayers_source {

  function options_form(&$form, &$form_state) {
    $form['options']['url'] = array(
      '#type' => 'textarea',
      '#title' => t('Base URL (template)'),
      '#default_value' => $this->getOption('url') ? implode("\n", (array) $this->getOption('url')) : 'http://a.tile.openstreetmap.org/${z}/${x}/${y}.png',
      '#maxlength' => 2083,
    );
  }

  function options_form_submit($form, &$form_state) {
    if ($form_state['values']['options']['url'] == '') {
      unset($form_state['item']->options['url']);
    }
  }
}
