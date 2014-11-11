<?php

function openlayers_openlayers__component__tooltip_openlayers_component() {
  return array(
    'handler' => array(
      'class' => 'openlayers__component__tooltip',
      'file' => 'openlayers__component__tooltip.inc',
    )
  );
}

class openlayers__component__tooltip extends openlayers_component {

  function options_form(&$form, &$form_state) {
    $layers = ctools_export_crud_load_all('openlayers_layers');
    $options = array('' => t('<Choose the layer>'));
    foreach($layers as $machine_name => $data) {
      $options[$machine_name] = $data->name;
    }

    $form['options']['layer'] = array(
      '#type' => 'select',
      '#title' => t('Layer'),
      '#default_value' => isset($form_state['item']->options['layer']) ? $form_state['item']->options['layer']: '',
      '#description' => t('Select the layer.'),
      '#options' => $options,
      '#required' => TRUE
    );

    $positioning = array('bottom-left', 'bottom-center', 'bottom-right', 'center-left', 'center-center', 'center-right', 'top-left', 'top-center', 'top-right');

    $form['options']['positioning'] = array(
      '#type' => 'select',
      '#title' => t('Positioning'),
      '#default_value' => isset($form_state['item']->options['positioning']) ? $form_state['item']->options['positioning']: 'top-left',
      '#description' => t('Defines how the overlay is actually positioned. Default is top-left.'),
      '#options' => array_combine($positioning, $positioning),
      '#required' => TRUE
    );
  }
}
