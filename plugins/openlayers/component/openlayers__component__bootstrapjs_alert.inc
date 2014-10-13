<?php

function openlayers_openlayers__component__bootstrapjs_alert_openlayers_component() {
  return array(
    'handler' => array(
      'class' => 'openlayers__component__bootstrapjs_alert',
      'file' => 'openlayers__component__bootstrapjs_alert.inc',
    )
  );
}

class openlayers__component__bootstrapjs_alert extends openlayers_component {

  function attached() {
    $attached = parent::attached();
    $attached['libraries_load'][] = array('bootstrapjs');
    return $attached;
  }

  function dependencies() {
    return array(
      'bootstrapjs'
    );
  }

  function options_form(&$form, &$form_state) {
    $form['options']['message'] = array(
      '#type' => 'textarea',
      '#title' => t('Text to display'),
      '#default_value' => $this->getOption('message'),
    );
  }

}
