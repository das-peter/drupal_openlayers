<?php
// $Id$

/**
 * @file
 * This file holds the functions for the openlayers Admin settings.
 *
 * @ingroup openlayers
 */

/**
 * Menu callback; displays the openlayers module settings page.
 *
 * @see system_settings_form()
 */
function openlayers_admin_settings() {
  // Initialize
  openlayers_initialize();
  
  // Let user know about advanced help
  if (module_exists('advanced_help')) {
    $form['openlayers_advanced_help'] = array(
      '#type' => 'item',
      '#title' => t('OpenLayers Help') . theme('advanced_help_topic', 'openlayers', 'openlayers-about'),
      '#value' => t('Access the advanced help here: !link or click the small help icon.', array(
        '!link' => l(t('Advanced Help'), 'admin/advanced_help'),
      )),
    );
  }
  else {
    drupal_set_message(t('This module has extensive help text available with the <a href="http://drupal.org/project/advanced_help">Advanced Help module</a>'));
  }

  // Source description
  $source_description = t('The source for the OpenLayers library can be one of two things:')
    .'<ul><li>'
    . t('URL: This means that the OpenLayers JS library is not hosted on this site.  OpenLayers provides a hosted JS file.  By default the Open Layers module will use this, since the JS file cannot be included with the module.  This is @ol_api_url.  This may effect performance as it is not hosted on your site. Also, depending on how the OpenLayers JS API changes, this module may not be compatible with this version.', array('@ol_api_url' => 'http://openlayers.org/api/OpenLayers.js'))
    .'</li><li>'
    . t('Drupal Path: This is a path relative to the Drupal base.  For instance, if you <a href="!ol_url">Download OpenLayers</a> manually to the OpenLayers module folder and extract it, you may use a value like: @suggested_path',
      array(
        '!ol_url' => 'http://openlayers.org/',
        '@suggested_path' => drupal_get_path('module', 'openlayers') . '/OpenLayers-2.7/OpenLayers.js',
      )
    )
    .'</li></ul>';

  // Define Form
  $form['openlayers_source'] = array(
    '#type' => 'textfield',
    '#title' => t('OpenLayers Source'),
    '#description' => $source_description,
    '#default_value' => variable_get('openlayers_source', 'http://openlayers.org/api/OpenLayers.js'),
  );
  $form['openlayers_default_preset'] = array(
    '#type' => 'select',
    '#title' => t('OpenLayers Default Preset'),
    '#description' => t('This is the default preset that will be used in cases where one is not defined.  It will also be used as the default when creating new presets.'),
    '#options' => openlayers_get_presets(),
    '#default_value' => variable_get('openlayers_default_preset', 'default'),
  );

  // Allow debug options
  $form['openlayers_debug'] = array(
    '#type' => 'fieldset',
    '#title' => t('OpenLayers Debug Options'),
    '#description' => t('Options to allow for different debugging.  Enabled the devel module to allow for screen output.'),
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,
  );
  // Screen output is based on dpm() function
  if (function_exists('dpm')) {
    $form['openlayers_debug']['openlayers_debug_screen_pre_render'] = array(
      '#type' => 'checkbox',
      '#title' => t('Pre-Render Screen'),
      '#description' => t('This will output each map array to the screen with dpm() before it is rendered.'),
      '#default_value' => variable_get('openlayers_debug_screen_pre_render', FALSE),
    );
    $form['openlayers_debug']['openlayers_debug_screen_post_render'] = array(
      '#type' => 'checkbox',
      '#title' => t('Post-Render Screen'),
      '#description' => t('This will output each map array to the screen with dpm() after it is rendered.'),
      '#default_value' => variable_get('openlayers_debug_screen_post_render', FALSE),
    );
  }
  $form['openlayers_debug']['openlayers_debug_watchdog_pre_render'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pre-Render Watchdog'),
    '#description' => t('This will output each map array to the watchdog log before it is rendered.'),
    '#default_value' => variable_get('openlayers_debug_watchdog_pre_render', FALSE),
  );
  $form['openlayers_debug']['openlayers_debug_watchdog_post_render'] = array(
    '#type' => 'checkbox',
    '#title' => t('Post-Render Watchdog'),
    '#description' => t('This will output each map array to the watchdog log after it is rendered.'),
    '#default_value' => variable_get('openlayers_debug_watchdog_post_render', FALSE),
  );

  // Make a system setting form and return
  return system_settings_form($form);
}
