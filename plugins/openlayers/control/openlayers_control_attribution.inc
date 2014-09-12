<?php

function openlayers_openlayers_control_attribution_openlayers_control() {
  return array(
    'handler' => array(
      'class' => 'openlayers_control_attribution',
    )
  );
}

class openlayers_control_attribution extends openlayers_control {

  function options_form() {
    return array(
      'collapsible' => array(
        '#type' => 'checkbox',
        '#title' => t('Collapsible'),
        '#default_value' => $this->getOption('collapsible'),
        '#description' => t(''),
      ),
    );
  }

}
