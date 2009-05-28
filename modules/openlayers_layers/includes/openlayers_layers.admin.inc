<?php
// $Id$

/**
 * @file
 * This file holds the functions for the openlayers layers Admin settings.
 *
 * @ingroup openlayers
 */

/**
 * Menu callback; displays the openlayers_layers module settings page.
 *
 * @see system_settings_form()
 */
function openlayers_layers_admin_settings() {
  $form = array();

  $form['openlayers_layers_google_api'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Maps API Key'),
    '#description' => t("Your personal Googlemaps API key.  You must get this for each separate website at <a href='http://www.google.com/apis/maps/'>Google Map API website</a>."),
    '#default_value' => variable_get('openlayers_layers_google_api', variable_get('googlemap_api_key', '')),
  );
  
  $form['openlayers_layers_yahoo_api'] = array(
    '#type' => 'textfield',
    '#title' => t('Yahoo Maps API Key'),
    '#description' => t("Your personal Yahoo API key.  You must get this for each separate website at <a href='http://developer.yahoo.com/maps/'>Yahoo Maps API website</a>."),
    '#default_value' => variable_get('openlayers_layers_yahoo_api',''),
  );  
  
  return system_settings_form($form);
}