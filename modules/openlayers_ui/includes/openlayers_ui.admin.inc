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

  /*
  $form['test'] = array(
    '#type' => 'openlayers',
    '#map' => array(
      'name' => 'super test',
      'machine_name' => 'super_test',
      'class' => 'openlayers_map_map',
      'options' => array(
        'width' => 'auto',
        'height' => '300px',
        'contextualLinks' => 0,
        'provideBlock' => 0,
        'view' => array(
          'center' => array(
            'lat' => '0',
            'lon' => '0',
          ),
          'rotation' => '0',
          'zoom' => '2',
        ),
        'layers' => array(
          '0' => array(
            'name' => 'Ma super layer',
            'machine_name' => 'plouf',
            'class' => 'openlayers_layer_tile',
            'options' => array(
              'source' => array(
                'name' => 'Ma super source',
                'class' => 'openlayers_source_osm'
              ),
            )
          ),
        ),
        'controls' => array(
          'control_mouseposition',
          'openlayers_control_attribution' => array(
            'name' => 'Control attribution',
            'machine_name' => 'openlayers_control_attribution',
            'class' => 'openlayers_control_attribution',
            'options' => array(
              'collapsible' => 1
            )
          ),
          'control_rotate',
          'control_zoom',
        ),
        'interactions' => array(
          'interaction_doubleclickzoom',
          'interaction_dragpan',
          'interaction_dragrotateandzoom',
          'interaction_mousewheelzoom',
        ),
      )
    )
  );

  $form['test2'] = array(
    '#type' => 'openlayers',
    '#map' => array(
      'name' => 'super test',
      'class' => 'openlayers_map_map',
      'options' => array(
        'width' => 'auto',
        'height' => '300px',
        'contextualLinks' => 0,
        'provideBlock' => 0,
        'view' => array(
          'center' => array(
            'lat' => '0',
            'lon' => '0',
          ),
          'rotation' => '0',
          'zoom' => '2',
        ),
        'layers' => array(
          '0' => array(
            'name' => 'Ma super layer',
            'machine_name' => 'plouf',
            'class' => 'openlayers_layer_tile',
            'options' => array(
              'source' => array(
                'name' => 'Ma super source',
                'class' => 'openlayers_source_osm'
              ),
            )
          ),
        ),
        'controls' => array(
          'control_zoomslider',
          'openlayers_control_attribution' => array(
            'name' => 'Control attribution',
            'machine_name' => 'openlayers_control_attribution',
            'class' => 'openlayers_control_attribution',
            'options' => array(
              'collapsible' => 1
            )
          ),
        ),
      )
    )
  );

  return system_settings_form($form);
  */

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

  $form['openlayers_default_map'] = array(
    '#type' => 'select',
    '#title' => t('OpenLayers maps'),
    '#description' => t('This form is just a test, it just shows the AJAX possibility of the module.'),
    '#options' => $options,
    '#default_value' => 'map_mapquest_openstreetmap',
    '#ajax' => array(
      'callback' => '_ajax_reload_default_map',
      'method' => 'replace',
      'wrapper' => 'default_map_ajax',
      'effect' => 'fade'
    ),
  );

  $form['default_map'] = array(
    '#prefix' => '<div id="default_map_ajax">',
    '#suffix' => '</div>',
    '#type' => 'openlayers',
    '#map' => 'map_mapquest_openstreetmap'
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
  $map = openlayers_object_load('map', $form_state['values']['openlayers_default_map']);
  $form['default_map']['map'] = array(
    '#markup' => openlayers_render_map($map)
  );
  return $form['default_map'];
}
