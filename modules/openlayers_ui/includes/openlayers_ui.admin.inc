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
function openlayers_ui_admin_settings($form, &$form_state) {
  ctools_include('plugins');
  ctools_include('export');
  $maps = ctools_export_crud_load_all('openlayers_maps');
  $options = array();
  foreach($maps as $machine_name => $data) {
    $map = openlayers_object_load('map', $machine_name);
    // Todo: Rewrite properly and create a generic function to load all objects.
    if (property_exists($map, 'disabled') && ($map->disabled == 1 || $map->disabled == TRUE)) continue;
    $options[$machine_name] = $data->name;
  }

  $map = 'map_openstreetmap';
  if (isset($form_state['values']['openlayers_default_map'])) {
    $map = $form_state['values']['openlayers_default_map'];
  }

  $form['openlayers_default_map'] = array(
    '#type' => 'select',
    '#title' => t('OpenLayers maps'),
    '#description' => t('This form is just a test, it just shows the AJAX possibility of the module.'),
    '#options' => $options,
    '#default_value' => $map,
    '#ajax' => array(
      'callback' => '_ajax_reload_default_map',
      'method' => 'replace',
      'wrapper' => 'default_map_ajax',
      'effect' => 'fade'
    ),
  );


  $map = openlayers_object_load('map', $map);
  $map->clearOption('contextualLinks');
  $map->setOption('height', '500px');
  $map->setOption('controls', array('control_zoom', 'control_rotate'));
  $map->setOption('interactions', array('interaction_doubleclickzoom', 'interaction_dragpan', 'interaction_dragrotate', 'interaction_mousewheelzoom'));
  $map->setOption('components', array('component_olmenu_values'));

  if (isset($form_state['input']['zoom'])) {
    $map->setOption(array('view', 'zoom'), $form_state['input']['zoom']);
  }
  if (isset($form_state['input']['rot'])) {
    $map->setOption(array('view','rotation'), $form_state['input']['rot']);
  }
  if (isset($form_state['input']['lat'])) {
    $map->setOption(array('view', 'center', 'lat'), $form_state['input']['lat']);
  }
  if (isset($form_state['input']['lon'])) {
    $map->setOption(array('view', 'center', 'lon'), $form_state['input']['lon']);
  }

  $form['default_map'] = array(
    '#prefix' => '<div id="default_map_ajax">',
    '#suffix' => '</div>',
    '#type' => 'openlayers',
    '#map' => $map,
  );

  $form['lat'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'lat'),
    '#value' => 0
  );
  $form['lon'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'lon'),
    '#value' => 0
  );
  $form['rot'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'rot'),
    '#value' => 0
  );
  $form['zoom'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'zoom'),
    '#value' => 0
  );

  // This is for preventing 'system/ajax' as destination when using AJAX maps.
  // See: http://drupal.stackexchange.com/questions/86958/get-current-url-arguments-inside-ajax-callback
  $form['current_path'] = array('#type' => 'hidden', '#value' => current_path());

  // Make a system setting form and return
  return system_settings_form($form);
}

function _ajax_reload_default_map($form, &$form_state) {
  // This is for preventing 'system/ajax' as destination when using AJAX maps.
  // See: http://drupal.stackexchange.com/questions/86958/get-current-url-arguments-inside-ajax-callback
  $_SESSION['current_path'] = $form_state['input']['current_path'];
  return $form['default_map'];
}
