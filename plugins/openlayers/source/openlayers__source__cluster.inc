<?php

function openlayers_openlayers__source__cluster_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers__source__cluster',
      'file' => 'openlayers__source__cluster.inc',
    )
  );
}

class openlayers__source__cluster extends openlayers_source {

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

    $form['options']['distance'] = array(
      '#type' => 'textfield',
      '#title' => t('Cluster distance'),
      '#default_value' => isset($form_state['item']->options['distance']) ? $form_state['item']->options['distance']: 50,
      '#description' => t('Cluster distance.'),
    );
  }
}
