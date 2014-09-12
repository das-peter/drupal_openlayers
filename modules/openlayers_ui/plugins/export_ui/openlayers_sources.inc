<?php
/**
 * CTools Export UI required function for plugin definition
 * See function ctools_plugin_load_includes() in the module ctools.
 */
function openlayers_ui_openlayers_sources_ctools_export_ui() {
  return array(
    'schema' => 'openlayers_sources',
    'access' => 'administer openlayers',
    'menu' => array(
      'menu prefix' => 'admin/structure/openlayers',
      'menu item' => 'sources',
      'menu title' => 'Sources',
      'menu description' => 'Administer OpenLayers sources.',
    ),

    'handler' => array(
      'class' => 'openlayers_sources_ui',
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
        'second' => t('Source type'),
        'third' => t('Source type options'),
      ),
      'forms' => array(
        'start' => array(
          'form id' => 'openlayers_source_form_start'
        ),
        'second' => array(
          'form id' => 'openlayers_source_form_second'
        ),
        'third' => array(
          'form id' => 'openlayers_source_form_third'
        ),
      )
    ),


    'title singular' => t('source'),
    'title plural' => t('sources'),
    'title singular proper' => t('OpenLayers source preset'),
    'title plural proper' => t('OpenLayers sources presets'),

    'strings' => array(
      'confirmation' => array(
        'add' => array(
          'success' => t('Source saved.'),
        ),
        'delete' => array(
          'success' => t('Source was deleted.'),
        )
      )
    ),
  );
}

function openlayers_source_form_start($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form($form, $form_state);
  return $form;
}

function openlayers_source_form_start_validate($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_validate($form, $form_state);
}

function openlayers_source_form_start_submit($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_submit($form, $form_state);
}

function openlayers_source_form_second($form, &$form_state) {
  $sources = ctools_get_plugins('openlayers', 'source');
  $options = array('' => t('<Choose the source type>'));
  foreach ($sources as $class => $plugin) {
    $options[$class] = $class;
  }

  $form['class'] = array(
    '#type' => 'select',
    '#title' => t('Source Type'),
    '#default_value' => isset($form_state['item']->class) ? $form_state['item']->class: '',
    '#description' => t('Select the type of source.'),
    '#options' => $options,
    '#required' => TRUE
  );

  return $form;
}

function openlayers_source_form_second_submit($form, &$form_state) {
  $form_state['item']->class = $form_state['values']['class'];
}


function openlayers_source_form_third($form, &$form_state) {
  $source = openlayer_object_factory_create('source', $form_state['item']->class, $form_state['item']);
  $form['options'] = $source->options_form();
  $form['options']['#tree'] = TRUE;

  return $form;
}
function openlayers_source_form_third_submit($form, &$form_state) {
  $form_state['item']->options = array_replace_recursive((array) $form_state['item']->options, $form_state['values']['options']);
}
