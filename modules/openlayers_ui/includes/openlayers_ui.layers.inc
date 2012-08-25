<?php

/**
 * @file
 * This file holds the functions handling layers in the
 * Openlayers UI.
 *
 * @ingroup openlayers
 */

/**
 * Layer add/edit form.
 */
function openlayers_ui_layers_form($form_state, $layer = NULL) {
  $form = array();

  $form['basics'] = array(
    '#tree' => FALSE,
    '#type' => 'fieldset',
    '#title' => t('Layer Basics'),
    '#description' => t('The following settings are for all layers.'),
  );
  $form['basics']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Layer Title'),
    '#default_value' => isset($layer->title) ? $layer->title : '',
    '#description' => t('The friendly name of your layer, which will appear in the administration interface as well on the map interface if it is exposed.'),
  );
  $form['basics']['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($layer->name) ? $layer->name : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'openlayers_layer_type_load',
      'source' => array('basics', 'title'),
    ),
    '#description' => t('A unique machine-readable name for this block type. It must only contain lowercase letters, numbers, and underscores.'),
    '#disabled' => !!$layer,
  );
  $form['basics']['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Layer Description'),
    '#default_value' => isset($layer->description) ? $layer->description : '',
    '#description' => t('The description of your layer, which will appear in the administration interface.'),
  );

  $layers_options = array();
  $layers = openlayers_layer_types();
  $options = array('' => t('Select the layer type'));

  foreach ($layers as $id => $data) {
    if (!($obj = openlayers_layer_type_load($data['name']))) {
      continue;
    };
    if (in_array($data['name'], array('openlayers_views_vector', 'openlayers_layer_type_raw'))) {
      continue;
    }


    $layers_option = array(
      '#type' => 'fieldset',
      '#tree' => TRUE,
      '#title' => t('Layer specific options for @layer_title', array('@layer_title' => $data['title'])),
    );
    if (method_exists($obj, 'options_form')) {
      $layers_option += $obj->options_form();
      $layers_option['#states'] = array(
        'visible' => array(
          ':input[name="layer_type"]' => array('value' => $id),
        ),
      );
      $layers_options[$id] = $layers_option;
    }
    $options[$id] = $data['title'];
  }

  $form['layer_type'] = array(
    '#type' => 'select',
    '#title' => t('Layer Type'),
    '#default_value' => isset($layer->data['layer_type']) ? $layer->data['layer_type']: '',
    '#description' => t('Select the type of layer.'),
    '#options' => $options,
  );

  $form += $layers_options;

  return $form;
}

/**
 * Layer-wide-settings form
 */
function openlayers_ui_layers_settings($form, &$form_state, $layer = NULL) {
  $form = array();
  $layer_types = openlayers_layer_types();

  foreach ($layer_types as $name => $type_def) {
    $type = openlayers_layer_type_load($name);
    if (method_exists($type, 'settings_form')) {
      $form[$name] = array(
        '#type' => 'fieldset',
        '#tree' => TRUE,
        '#title' => $type_def['title']);
      $form[$name]['settings'] = $type->settings_form();
    }
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;

}

/**
 * Submit handler for openlayers_ui_layers_settings
*/
function openlayers_ui_layers_settings_submit(&$form, &$form_state) {
  $layer_types = openlayers_layer_types();
  foreach ($form_state['values'] as $key => $value) {
    if (in_array($key, array_keys($layer_types))) {
      foreach ($value['settings'] as $k => $v) {
        variable_set($k, $v);
      }
    }
  }
}
