<?php
/**
 * CTools Export UI required function for plugin definition
 * See function ctools_plugin_load_includes() in the module ctools.
 */
function openlayers_ui_openlayers_styles_ui_ctools_export_ui() {
  return array(
    'schema' => 'openlayers_styles',
    'access' => 'administer styles',
    'menu' => array(
      'menu prefix' => 'admin/structure/openlayers',
      'menu item' => 'styles',
      'menu title' => 'Styles',
      'menu description' => 'Administer OpenLayers styles.',
    ),

    'handler' => array(
      'class' => 'openlayers_styles_ui',
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
        'type' => t('Style type'),
        'options' => t('Style options'),
      ),
      'forms' => array(
        'start' => array(
          'form id' => 'openlayers_style_form_start'
        ),
        'type' => array(
          'form id' => 'openlayers_style_form_type'
        ),
        'options' => array(
          'form id' => 'openlayers_style_form_options'
        ),
      )
    ),

    'title singular' => t('style'),
    'title plural' => t('styles'),
    'title singular proper' => t('OpenLayers style preset'),
    'title plural proper' => t('OpenLayers styles presets'),

    'strings' => array(
      'confirmation' => array(
        'add' => array(
          'success' => t('Style saved.'),
        ),
        'delete' => array(
          'success' => t('Style was deleted.'),
        )
      )
    ),
  );
}

function openlayers_style_form_start($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form($form, $form_state);

  return $form;
}

function openlayers_style_form_start_validate($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_validate($form, $form_state);
}

function openlayers_style_form_start_submit($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_submit($form, $form_state);
}

function openlayers_style_form_type($form, &$form_state) {
  $styles = ctools_get_plugins('openlayers', 'style');
  $options = array('' => t('<Choose the style type>'));
  foreach ($styles as $class => $plugin) {
    $options[$class] = $class;
  }

  $form['class'] = array(
    '#type' => 'select',
    '#title' => t('Style type'),
    '#default_value' => isset($form_state['item']->class) ? $form_state['item']->class: '',
    '#description' => t('Select the type of style.'),
    '#options' => $options,
    '#required' => TRUE
  );

  return $form;
}

function openlayers_style_form_type_submit($form, &$form_state) {
  if (!empty($form_state['values']['options'])) {
    $form_state['item']->options = array_replace_recursive((array) $form_state['item']->options, (array) $form_state['values']['options']);
  }

  $form_state['item']->class = $form_state['values']['class'];
}

function openlayers_style_form_options($form, &$form_state) {
  $style = openlayers_object_load('style', $form_state['item']);
  $style->options_form($form, $form_state);
  $form['options']['#tree'] = TRUE;

  return $form;
}

function openlayers_style_form_options_validate($form, &$form_state) {
  $style = openlayers_object_load('style', $form_state['item']);
  $style->options_form_validate($form, $form_state);
}

function openlayers_style_form_options_submit($form, &$form_state) {
  $form_state['item']->options = array_replace_recursive((array) $form_state['item']->options, (array) $form_state['values']['options']);
  $style = openlayers_object_load('style', $form_state['item']);
  $style->options_form_submit($form, $form_state);
}
