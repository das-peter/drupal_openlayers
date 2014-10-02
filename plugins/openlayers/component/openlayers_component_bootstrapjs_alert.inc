<?php

function openlayers_openlayers_component_bootstrapjs_alert_openlayers_component() {
  return array(
    'handler' => array(
      'class' => 'openlayers_component_bootstrapjs_alert',
      'file' => 'openlayers_component_bootstrapjs_alert.inc',
    )
  );
}

class openlayers_component_bootstrapjs_alert extends openlayers_component {

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

  function options_form($form, &$form_state) {
    return array(
      'message' => array(
        '#type' => 'textarea',
        '#title' => t('Text to display'),
        '#default_value' => $this->getOption('message'),
      ),
    );
  }

}
