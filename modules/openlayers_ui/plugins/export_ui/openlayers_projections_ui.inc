<?php
/**
 * CTools Export UI required function for plugin definition
 * See function ctools_plugin_load_includes() in the module ctools.
 */
function openlayers_ui_openlayers_projections_ui_ctools_export_ui() {
  return array(
    'schema' => 'openlayers_projections',
    'access' => 'administer projections',
    'menu' => array(
      'menu prefix' => 'admin/structure/openlayers',
      'menu item' => 'projections',
      'menu title' => 'Projections',
      'menu description' => 'Administer OpenLayers projections.',
    ),

    'handler' => array(
      'class' => 'openlayers_projections_ui',
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
      ),
      'forms' => array(
        'start' => array(
          'form id' => 'openlayers_projection_form_start'
        ),
      )
    ),

    'title singular' => t('projection'),
    'title plural' => t('projections'),
    'title singular proper' => t('OpenLayers projection preset'),
    'title plural proper' => t('OpenLayers projection presets'),

    'strings' => array(
      'confirmation' => array(
        'add' => array(
          'success' => t('Projection saved.'),
        ),
        'delete' => array(
          'success' => t('Projection was deleted.'),
        )
      )
    ),
  );
}

function openlayers_projection_form_start($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form($form, $form_state);

  $form['definition'] = array(
    '#type' => 'textarea',
    '#title' => t('Projection definition'),
    '#rows' => '10',
    '#default_value' => isset($form_state['item']->definition) ? $form_state['item']->definition : ''
  );

  return $form;
}

function openlayers_projection_form_start_validate($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_validate($form, $form_state);
}

function openlayers_projection_form_start_submit($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_submit($form, $form_state);
}
