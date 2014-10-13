<?php

function openlayers_openlayers__source__osm_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers__source__osm',
      'file' => 'openlayers__source__osm.inc',
    )
  );
}

class openlayers__source__osm extends openlayers_source {

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
