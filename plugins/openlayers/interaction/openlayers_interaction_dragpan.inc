<?php

function openlayers_openlayers_interaction_dragpan_openlayers_interaction() {
  return array(
    'handler' => array(
      'class' => 'openlayers_interaction_dragpan',
    )
  );
}

class openlayers_interaction_dragpan extends openlayers_interaction {
  function options_form() {
    return array(
      'decay' => array(
        '#type' => 'textfield',
        '#title' => t('Decay'),
        '#default_value' => $this->getOption('decay', -0.005),
        '#description' => t('Rate of decay (must be negative).'),
      ),
      'minVelocity' => array(
        '#type' => 'textfield',
        '#title' => t('Minimum velocity'),
        '#default_value' => $this->getOption('minVelocity', 0.05),
        '#description' => t('Minimum velocity (pixels/millisecond).'),
      ),
      'delay' => array(
        '#type' => 'textfield',
        '#title' => t('Delay'),
        '#default_value' => $this->getOption('delay', 100),
        '#description' => t('Delay to consider to calculate the kinetic.'),
      ),
    );
  }
}
