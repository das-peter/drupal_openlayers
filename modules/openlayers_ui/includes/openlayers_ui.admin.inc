<?php

/**
 * @file
 * This file holds the functions for the main openlayers Admin settings.
 *
 * @ingroup openlayers
 */

/**
 * Menu callback; displays the openlayers module settings page.
 *
 * @see system_settings_form()
 */
function openlayers_ui_admin_settings() {
  $source_description = 
    t('By default the your site will point to a hosted version of the 
      OpenLayers library, at %ol_api_url.  For better performance and 
      reliability, you should <a href="!ol_url">download the OpenLayers 
      library</a>, and add it to your Drupal installation. For instance, 
      you could use a Drupal relative path like: %suggested_path.',
      array(
        '%ol_api_url' => OPENLAYERS_DEFAULT_LIBRARY,
        '!ol_url' => 'http://openlayers.org/',
        '%suggested_path' => 'sites/all/libraries/OpenLayers-2.11/OpenLayers.js',
      )
    );

  // Define Form
  $form['openlayers_source'] = array(
    '#type' => 'textfield',
    '#title' => t('OpenLayers Source'),
    '#description' => $source_description,
    '#default_value' => variable_get('openlayers_source', OPENLAYERS_DEFAULT_LIBRARY),
  );

  $form['openlayers_default_map'] = array(
    '#type' => 'select',
    '#title' => t('OpenLayers Default Map'),
    '#description' => t('This is the default map that will be used
      in cases where one is not defined.  It will also be used as 
      the default when creating new maps.'),
    '#options' => openlayers_map_options(),
    '#default_value' => variable_get('openlayers_default_map', 'default'),
  );

  $form['openlayers_ui_preview_map'] = array(
    '#type' => 'checkbox',
    '#title' => t('Preview Map'),
    '#description' => t('Turning this on will show you a map preview when editing it through the !link.',
      array('!link' => l(t('Map Interface'), 'admin/structure/openlayers/maps'))),
    '#default_value' => variable_get('openlayers_ui_preview_map', FALSE),
  );

  // Make a system setting form and return
  return system_settings_form($form);
}
