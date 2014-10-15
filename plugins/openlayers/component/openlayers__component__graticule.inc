<?php

function openlayers_openlayers__component__graticule_openlayers_component() {
  return array(
    'handler' => array(
      'class' => 'openlayers__component__graticule',
      'file' => 'openlayers__component__graticule.inc',
    )
  );
}

class openlayers__component__graticule extends openlayers_component {

  function options_form(&$form, &$form_state) {
    $form['options']['rgba'] = array(
      '#type' => 'textfield',
      '#title' => t('RGBA'),
      '#default_value' => $this->getOption('rgba', '0, 0, 0, 0.2'),
      '#description' => t('RGBA, a string of 4 numbers, separated by a comma.'),
    );
    $form['options']['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#default_value' => $this->getOption('width', 2),
      '#description' => t('Width'),
    );
    $form['options']['lineDash'] = array(
      '#type' => 'textfield',
      '#title' => t('Line dash'),
      '#default_value' => $this->getOption('lineDash', '0.5, 4'),
      '#description' => t('Line dash, a string of 2 numbers, separated by a comma.'),
    );
  }

}
