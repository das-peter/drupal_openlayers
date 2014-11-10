<?php

function openlayers_openlayers__component__autopopup_openlayers_component() {
  return array(
    'handler' => array(
      'class' => 'openlayers__component__autopopup',
      'file' => 'openlayers__component__autopopup.inc',
    )
  );
}

class openlayers__component__autopopup extends openlayers_component {

  function options_form(&$form, &$form_state) {
    $sources = ctools_export_crud_load_all('openlayers_sources');
    $options = array('' => t('<Choose the source>'));
    foreach($sources as $machine_name => $data) {
      $options[$machine_name] = $data->name;
    }

    $form['options']['source'] = array(
      '#type' => 'select',
      '#title' => t('Source'),
      '#default_value' => isset($form_state['item']->options['source']) ? $form_state['item']->options['source']: '',
      '#description' => t('Select the source.'),
      '#options' => $options,
      '#required' => TRUE
    );
    $form['options']['zoom'] = array(
      '#type' => 'textfield',
      '#title' => t('Zoom'),
      '#default_value' => isset($form_state['item']->options['zoom']) ? $form_state['item']->options['zoom']: 10,
      '#description' => t('Integer or <em>auto</em>.'),
      '#required' => TRUE
    );

    $form['options']['enableAnimations'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable animations'),
      '#default_value' => isset($form_state['item']->options['enableAnimations']) ? $form_state['item']->options['enableAnimations']: FALSE,
      '#description' => t('Enable pan and zoom animation.'),
    );

    $form['options']['animations'] = array(
      '#type' => 'fieldset',
      '#title' => 'Animations options',
      '#states' => array(
        'visible' => array(
          'input[name="options[enableAnimations]"' => array('checked' => TRUE)
        )
      )
    );

    $form['options']['animations']['pan'] = array(
      '#type' => 'textfield',
      '#title' => t('Pan animation duration'),
      '#default_value' => isset($form_state['item']->options['animations']['pan']) ? $form_state['item']->options['animations']['pan']: '500',
      '#description' => t('Duration of the pan animation.'),
    );

    $form['options']['animations']['zoom'] = array(
      '#type' => 'textfield',
      '#title' => t('Zoom animation duration'),
      '#default_value' => isset($form_state['item']->options['animations']['zoom']) ? $form_state['item']->options['animations']['zoom']: '500',
      '#description' => t('Duration of the zoom animation.'),
    );
  }
}
