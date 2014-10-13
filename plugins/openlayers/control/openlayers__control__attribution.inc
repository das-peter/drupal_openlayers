<?php

function openlayers_openlayers__control__attribution_openlayers_control() {
  return array(
    'handler' => array(
      'class' => 'openlayers__control__attribution',
      'file' => 'openlayers__control__attribution.inc',
    )
  );
}

class openlayers__control__attribution extends openlayers_control {

  function options_form(&$form, &$form_state) {
    $form['options']['collapsible'] = array(
      '#type' => 'checkbox',
      '#title' => t('Collapsible'),
      '#default_value' => $this->getOption('collapsible'),
      '#description' => t(''),
    );
  }

}
