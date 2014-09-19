<?php
/**
 * CTools Export UI required function for plugin definition
 * See function ctools_plugin_load_includes() in the module ctools.
 */
function openlayers_ui_openlayers_interactions_ctools_export_ui() {
  return array(
    'schema' => 'openlayers_interactions',
    'access' => 'administer openlayers',
    'menu' => array(
      'menu prefix' => 'admin/structure/openlayers',
      'menu item' => 'interactions',
      'menu title' => 'Interactions',
      'menu description' => 'Administer OpenLayers interactions.',
    ),

    'handler' => array(
      'class' => 'openlayers_interactions_ui',
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
        'type' => t('Interaction type'),
        'options' => t('Interaction type options'),
      ),
      'forms' => array(
        'start' => array(
          'form id' => 'openlayers_interaction_form_start'
        ),
        'type' => array(
          'form id' => 'openlayers_interaction_form_type'
        ),
        'options' => array(
          'form id' => 'openlayers_interaction_form_options'
        ),
      )
    ),

    'title singular' => t('interaction'),
    'title plural' => t('interactions'),
    'title singular proper' => t('OpenLayers interaction preset'),
    'title plural proper' => t('OpenLayers interaction presets'),

    'strings' => array(
      'confirmation' => array(
        'add' => array(
          'success' => t('Interaction saved.'),
        ),
        'delete' => array(
          'success' => t('Interaction was deleted.'),
        )
      )
    ),
  );
}

function openlayers_interaction_form_start($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form($form, $form_state);
  return $form;
}

function openlayers_interaction_form_start_validate($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_validate($form, $form_state);
}

function openlayers_interaction_form_start_submit($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_submit($form, $form_state);
}

function openlayers_interaction_form_type($form, &$form_state) {
  $layers = ctools_get_plugins('openlayers', 'interaction');
  $options = array('' => t('<Choose the interaction type>'));
  foreach ($layers as $class => $plugin) {
    $options[$class] = $class;
  }

  $form['class'] = array(
    '#type' => 'select',
    '#title' => t('Interaction Type'),
    '#default_value' => isset($form_state['item']->class) ? $form_state['item']->class: '',
    '#description' => t('Select the type of interaction.'),
    '#options' => $options,
    '#required' => TRUE
  );

  return $form;
}
function openlayers_interaction_form_type_submit($form, &$form_state) {
  $form_state['item']->class = $form_state['values']['class'];
}

function openlayers_interaction_form_options($form, &$form_state) {
  $interaction = openlayer_object_factory_create('interaction', $form_state['item']->class, $form_state['item']);
  $form['options'] = $interaction->options_form();
  $form['options']['#tree'] = TRUE;

  return $form;
}
function openlayers_interaction_form_options_submit($form, &$form_state) {
  $form_state['item']->options = array_replace_recursive((array) $form_state['item']->options, $form_state['values']['options']);
}
