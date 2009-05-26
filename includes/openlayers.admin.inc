<?php
// $Id$

/**
 * @file
 * This file holds the functions for the openlayers Admin settings.
 */

/**
 * Menu callback; displays the openlayers module settings page.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function openlayers_admin_settings() {
  // Initialize
  openlayers_intialize();

  // Source description
  $source_description = t('The source for the OpenLayers library can be one of two things:')
    .'<ul><li>'
    . t('URL: This means that the OpenLayers JS library is not hosted on this site.  OpenLayers provides a hosted JS file.  By default the Open Layers module, will use this, since the JS file cannot be included with the module.  This is !ol_api_url.  This will may effect performance as it is not hosted on your site. Also, depending on how the OpenLayers JS API changes, this module may not be compatible with this version.', array('@ol_api_url' => 'http://openlayers.org/api/OpenLayers.js'))
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
  
  // Make a system setting form and return
  return system_settings_form($form);
}