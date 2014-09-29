<?php
/**
 * CTools Export UI required function for plugin definition
 * See function ctools_plugin_load_includes() in the module ctools.
 */
function openlayers_ui_openlayers_components_ui_ctools_export_ui() {
  return array(
    'schema' => 'openlayers_components',
    'access' => 'administer openlayers',
    'menu' => array(
      'menu prefix' => 'admin/structure/openlayers',
      'menu item' => 'components',
      'menu title' => 'Components',
      'menu description' => 'Administer OpenLayers components.',
    ),

    'handler' => array(
      'class' => 'openlayers_components_ui',
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
        'type' => t('Component type'),
        'options' => t('Component type options'),
      ),
      'forms' => array(
        'start' => array(
          'form id' => 'openlayers_component_form_start'
        ),
        'type' => array(
          'form id' => 'openlayers_component_form_type'
        ),
        'options' => array(
          'form id' => 'openlayers_component_form_options'
        ),
      )
    ),

    'title singular' => t('component'),
    'title plural' => t('components'),
    'title singular proper' => t('OpenLayers component preset'),
    'title plural proper' => t('OpenLayers component presets'),

    'strings' => array(
      'confirmation' => array(
        'add' => array(
          'success' => t('Component saved.'),
        ),
        'delete' => array(
          'success' => t('Component was deleted.'),
        )
      )
    ),
  );
}

function openlayers_component_form_start($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form($form, $form_state);

  $maps = ctools_export_crud_load_all('openlayers_maps');
  $options = array('' => 'Dont attach');
  foreach($maps as $machine_name => $data) {
    $map = openlayers_object_load('map', $machine_name);
    if (property_exists($map, 'disabled') && ($map->disabled == 1 || $map->disabled == TRUE)) continue;
    $options[$machine_name] = $data->name;
  }

  $form['attachToMap'] = array(
    '#type' => 'select',
    '#title' => 'Add this to a map ?',
    '#description' => 'Select the map to add this object to.',
    '#options' => $options
  );

  return $form;
}

function openlayers_component_form_start_validate($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_validate($form, $form_state);
}

function openlayers_component_form_start_submit($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_submit($form, $form_state);

  if ($form_state['values']['attachToMap']) {
    $map = ctools_export_crud_load('openlayers_maps', $form_state['values']['attachToMap']);
    $map->options['components'][] = $form_state['item']->machine_name;
    ctools_export_crud_save('openlayers_maps', $map);
  }
}

function openlayers_component_form_type($form, &$form_state) {
  $layers = ctools_get_plugins('openlayers', 'component');
  $options = array('' => t('<Choose the component type>'));
  foreach ($layers as $class => $plugin) {
    $options[$class] = $class;
  }

  $form['class'] = array(
    '#type' => 'select',
    '#title' => t('Component Type'),
    '#default_value' => isset($form_state['item']->class) ? $form_state['item']->class: '',
    '#description' => t('Select the type of component.'),
    '#options' => $options,
    '#required' => TRUE
  );

  return $form;
}

function openlayers_component_form_type_submit($form, &$form_state) {
  $form_state['item']->class = $form_state['values']['class'];
}

function openlayers_component_form_options($form, &$form_state) {
  $control = openlayers_object_load('component', $form_state['item']);
  $form['options'] = $control->options_form();
  $form['options']['#tree'] = TRUE;

  return $form;
}

function openlayers_component_form_options_validate($form, &$form_state) {
  $control = openlayers_object_load('component', $form_state['item']);
  $control->options_form_validate();
}

function openlayers_component_form_options_submit($form, &$form_state) {
  $form_state['item']->options = array_replace_recursive((array)$form_state['item']->options, $form_state['values']['options']);
}
