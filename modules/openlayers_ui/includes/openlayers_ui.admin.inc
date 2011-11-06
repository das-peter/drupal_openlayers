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
  $source_description = '<p>'
    . t('By default the your site will point to a hosted version of
    the OpenLayers library, at <code>@ol_api_url.</code>',
    array('@ol_api_url' => OPENLAYERS_DEFAULT_LIBRARY))
    . t('Alternately, you can <a href="!ol_url">download OpenLayers</a>,
    add it to your Drupal installation, and use a relative path like
    <code>@suggested_path</code>',
      array(
        '!ol_url' => 'http://openlayers.org/',
        '@suggested_path' => drupal_get_path('module', 'openlayers') . '/OpenLayers-2.7/OpenLayers.js',
      )
    )
    . '</li></ul>';

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
      in cases where one is not defined.  It will also be used as the default when creating new maps.'),
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
