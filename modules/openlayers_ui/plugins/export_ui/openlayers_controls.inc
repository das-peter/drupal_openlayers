<?php
/**
 * CTools Export UI required function for plugin definition
 * See function ctools_plugin_load_includes() in the module ctools.
 */
function openlayers_ui_openlayers_controls_ctools_export_ui() {
  return array(
    'schema' => 'openlayers_controls',
    'access' => 'administer openlayers',
    'menu' => array(
      'menu prefix' => 'admin/structure/openlayers',
      'menu item' => 'controls',
      'menu title' => 'Controls',
      'menu description' => 'Administer OpenLayers controls.',
    ),

    'handler' => array(
      'class' => 'openlayers_controls_ui',
      'parent' => 'ctools_export_ui'
    ),

    'export' => array(
      'admin_title' => 'name',
      'admin_description' => 'description',
    ),

    'use wizard' => TRUE,
    'form info' => array(
      'order' => array(
        'start' => t('Administrative settings'),
        'second' => t('Control type'),
        'third' => t('Control type options'),
      ),
      'forms' => array(
        'start' => array(
          'form id' => 'openlayers_control_form_start'
        ),
        'second' => array(
          'form id' => 'openlayers_control_form_second'
        ),
        'third' => array(
          'form id' => 'openlayers_control_form_third'
        ),
      )
    ),

    'title singular' => t('control'),
    'title plural' => t('controls'),
    'title singular proper' => t('OpenLayers control preset'),
    'title plural proper' => t('OpenLayers control presets'),

    'strings' => array(
      'confirmation' => array(
        'add' => array(
          'success' => t('Control saved.'),
        ),
        'delete' => array(
          'success' => t('Control was deleted.'),
        )
      )
    ),
  );
}

function openlayers_control_form_start($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form($form, $form_state);
  return $form;
}

function openlayers_control_form_start_validate($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_validate($form, $form_state);
}

function openlayers_control_form_start_submit($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_submit($form, $form_state);
}

function openlayers_control_form_second($form, &$form_state) {
  $layers = ctools_get_plugins('openlayers', 'control');
  $options = array('' => t('<Choose the control type>'));
  foreach ($layers as $class => $plugin) {
    $options[$class] = $class;
  }

  $form['class'] = array(
    '#type' => 'select',
    '#title' => t('Control Type'),
    '#default_value' => isset($form_state['item']->class) ? $form_state['item']->class: '',
    '#description' => t('Select the type of control.'),
    '#options' => $options,
    '#required' => TRUE
  );

  return $form;
}
function openlayers_control_form_second_submit($form, &$form_state) {
  $form_state['item']->class = $form_state['values']['class'];
}

function openlayers_control_form_third($form, &$form_state) {
  $control = openlayer_object_factory_create('control', $form_state['item']->class, $form_state['item']);
  $form['options'] = $control->options_form();
  $form['options']['#tree'] = TRUE;

  return $form;
}
function openlayers_control_form_third_submit($form, &$form_state) {
  $form_state['item']->options = array_replace_recursive($form_state['item']->options, $form_state['values']['options']);
}
