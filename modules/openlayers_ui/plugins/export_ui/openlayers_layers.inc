<?php
/**
 * CTools Export UI required function for plugin definition
 * See function ctools_plugin_load_includes() in the module ctools.
 */
function openlayers_ui_openlayers_layers_ctools_export_ui() {
  return array(
    'schema' => 'openlayers_layers',
    'access' => 'administer openlayers',
    'menu' => array(
      'menu prefix' => 'admin/structure/openlayers',
      'menu item' => 'layers',
      'menu title' => 'Layers',
      'menu description' => 'Administer OpenLayers layers presets.',
    ),

    'handler' => array(
      'class' => 'openlayers_layers_ui',
      'parent' => 'ctools_export_ui'
    ),

    'use wizard' => TRUE,
    'form info' => array(
      'order' => array(
        'start' => t('Administrative settings'),
        'second' => t('type'),
        'third' => t('type options'),
      ),
      'forms' => array(
        'start' => array(
          'form id' => 'openlayers_layer_form_start'
        ),
        'second' => array(
          'form id' => 'openlayers_layer_form_second'
        ),
        'third' => array(
          'form id' => 'openlayers_layer_form_third'
        ),
      )
    ),

    'export' => array(
      'admin_title' => 'name',
      'admin_description' => 'description',
    ),

    'title singular' => t('layer'),
    'title plural' => t('layers'),
    'title singular proper' => t('OpenLayers preset'),
    'title plural proper' => t('OpenLayers Layers presets'),

    'strings' => array(
      'confirmation' => array(
        'add' => array(
          'success' => t('saved.'),
        ),
        'delete' => array(
          'success' => t('was deleted.'),
        )
      )
    ),
  );
}

function openlayers_layer_form_start($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form($form, $form_state);
  return $form;
}

function openlayers_layer_form_start_validate($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_validate($form, $form_state);
}

function openlayers_layer_form_start_submit($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_submit($form, $form_state);
}

function openlayers_layer_form_second($form, &$form_state) {
  $layers = ctools_get_plugins('openlayers', 'layer');
  $options = array('' => t('<Choose the layer type>'));
  foreach ($layers as $class => $plugin) {
    $options[$class] = $class;
  }

  $form['class'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#default_value' => isset($form_state['item']->class) ? $form_state['item']->class: '',
    '#description' => t('Select the type of layer.'),
    '#options' => $options,
    '#required' => TRUE
  );

  $sources = ctools_export_crud_load_all('openlayers_sources');
  $options = array('' => t('<Choose the source>'));
  foreach($sources as $machine_name => $data) {
    $options[$machine_name] = $data->name;
  }

  $form['options'] = array(
    '#tree' => TRUE
  );

  // Todo: Replace with getOption(). To get this, we'll probably need to use
  // 'object factory' in the appropriate schema from ctools export.
  // This way, objects create by ctools export UI will have the right class
  // and the getOption() method will be available.
  $form['options']['source'] = array(
    '#type' => 'select',
    '#title' => t('Source'),
    '#default_value' => isset($form_state['item']->options['source']) ? $form_state['item']->options['source']: '',
    '#description' => t('Select the source.'),
    '#options' => $options,
    '#required' => TRUE
  );

  return $form;
}

function openlayers_layer_form_second_submit($form, &$form_state) {
  $form_state['item']->class = $form_state['values']['class'];
  $form_state['item']->options = array_replace_recursive((array) $form_state['item']->options, $form_state['values']['options']);
}


function openlayers_layer_form_third($form, &$form_state) {
  $layer = openlayer_object_factory_create('layer', $form_state['item']->class, $form_state['item']);
  $form['options'] = $layer->options_form();
  $form['options']['#tree'] = TRUE;

  return $form;
}

function openlayers_layer_form_third_validate($form, &$form_state) {
/*
  $layer = openlayer_object_factory_create('layer', $form_state['item']->class, $form_state['item']);
  $layer->init($form_state['item']);
  $layer->options_form_validate($form, $form_state);
*/
}

function openlayers_layer_form_third_submit($form, &$form_state) {

  if (isset($form_state['item']->options['file']) && $file = file_load($form_state['item']->options['file'])) {
    file_delete($file);
  }

  if (isset($form_state['values']['file']) && $file = file_load($form_state['values']['file'])) {
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    file_usage_add($file, 'openlayers', 'layer', $form_state['item']->machine_name);
  }

  //$form_state['item']->options = array_replace_recursive((array) $form_state['item']->options, $form_state['values']['options']);
}
