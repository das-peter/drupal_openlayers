<?php

function openlayers_openlayers__control__mouseposition_openlayers_control() {
  return array(
    'handler' => array(
      'class' => 'openlayers__control__mouseposition',
      'file' => 'openlayers__control__mouseposition.inc',
    )
  );
}

class openlayers__control__mouseposition extends openlayers_control {

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
