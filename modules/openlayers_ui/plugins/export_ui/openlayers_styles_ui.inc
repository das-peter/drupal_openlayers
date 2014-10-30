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
      ),
      'forms' => array(
        'start' => array(
          'form id' => 'openlayers_style_form_start'
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
