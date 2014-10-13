<?php

function openlayers_openlayers__interaction__dragpan_openlayers_interaction() {
  return array(
    'handler' => array(
      'class' => 'openlayers__interaction__dragpan',
      'file' => 'openlayers__interaction__dragpan.inc',
    )
  );
}

class openlayers__interaction__dragpan extends openlayers_interaction {
  function options_form(&$form, &$form_state) {
    $form['options']['decay'] = array(
      '#type' => 'textfield',
      '#title' => t('Decay'),
      '#default_value' => $this->getOption('decay', -0.005),
      '#description' => t('Rate of decay (must be negative).'),
    );
    $form['options']['minVelocity'] = array(
      '#type' => 'textfield',
      '#title' => t('Minimum velocity'),
      '#default_value' => $this->getOption('minVelocity', 0.05),
      '#description' => t('Minimum velocity (pixels/millisecond).'),
    );
    $form['options']['delay'] = array(
      '#type' => 'textfield',
      '#title' => t('Delay'),
      '#default_value' => $this->getOption('delay', 100),
      '#description' => t('Delay to consider to calculate the kinetic.'),
    );
  }
}
