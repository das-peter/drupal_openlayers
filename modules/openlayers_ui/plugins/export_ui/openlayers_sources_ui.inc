<?php
/**
 * CTools Export UI required function for plugin definition
 * See function ctools_plugin_load_includes() in the module ctools.
 */
function openlayers_ui_openlayers_sources_ui_ctools_export_ui() {
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
        'type' => t('Source type'),
        'options' => t('Source type options'),
      ),
      'forms' => array(
        'start' => array(
          'form id' => 'openlayers_source_form_start'
        ),
        'type' => array(
          'form id' => 'openlayers_source_form_type'
        ),
        'options' => array(
          'form id' => 'openlayers_source_form_options'
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

  $layers = ctools_export_crud_load_all('openlayers_layers');
  $options = array('' => 'Dont attach');
  foreach($layers as $machine_name => $data) {
    $layer = openlayers_object_load('layer', $machine_name);
    if (property_exists($layer, 'disabled') && ($layer->disabled == 1 || $layer->disabled == TRUE)) continue;
    $options[$machine_name] = $data->name;
  }

  $form['attachToLayer'] = array(
    '#type' => 'select',
    '#title' => 'Add this to a layer ?',
    '#description' => 'Select the layer to add this object to.',
    '#options' => $options
  );

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

  if ($form_state['values']['attachToLayer']) {
    $layer = ctools_export_crud_load('openlayers_layers', $form_state['values']['attachToLayer']);
    $layer->options['source'] = $form_state['item']->machine_name;
    ctools_export_crud_save('openlayers_layers', $layer);
  }
}

function openlayers_source_form_type($form, &$form_state) {
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

function openlayers_source_form_type_submit($form, &$form_state) {
  $form_state['item']->class = $form_state['values']['class'];
}

function openlayers_source_form_options($form, &$form_state) {
  $source = openlayers_object_load('source', $form_state['item']);
  $form['options'] = $source->options_form();
  $form['options']['#tree'] = TRUE;

  return $form;
}

function openlayers_source_form_options_validate($form, &$form_state) {
  $source = openlayers_object_load('source', $form_state['item']);
  $source->options_form_validate();
}

function openlayers_source_form_options_submit($form, &$form_state) {
  $form_state['item']->options = array_replace_recursive((array) $form_state['item']->options, $form_state['values']['options']);
}
