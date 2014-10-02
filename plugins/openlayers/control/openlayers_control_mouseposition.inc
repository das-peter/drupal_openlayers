<?php

function openlayers_openlayers_control_mouseposition_openlayers_control() {
  return array(
    'handler' => array(
      'class' => 'openlayers_control_mouseposition',
      'file' => 'openlayers_control_mouseposition.inc',
    )
  );
}

class openlayers_control_mouseposition extends openlayers_control {

  function options_form(&$form, &$form_state) {
    $form['options']['target'] = array(
      '#type' => 'textfield',
      '#title' => t('ID of the element.'),
      '#default_value' => $this->getOption('target'),
      '#description' => t(''),
    );
    $form['options']['undefinedHTML'] = array(
      '#type' => 'textfield',
      '#title' => t('undefinedHTML'),
      '#default_value' => $this->getOption('undefinedHTML'),
      '#description' => t('Markup for undefined coordinates. Default is an empty string.'),
    );
  }

}
