<?php
// $Id$

/**
 * @file
 * This file holds the functions for the settings forms.
 *
 * @ingroup openlayers
 */
 
/**
 * OpenLayers AHAH
 *
 * Function to handle the AHAH request of the openlayers form
 */
function openlayers_ahah() {
  // Since the default form is called within a specific file, we
  // need to include it.  This is not that great.
  module_load_include('inc', 'openlayers', '/includes/openlayers.defaults');

  // We're starting in step #3, preparing for #4.
  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  // Step #4.
  $form = form_get_cache($form_build_id, $form_state);

  // Preparing for #5.
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;

  // Step #5.
  drupal_process_form($form_id, $form, $form_state);
  // Step #6 and #7 and #8.
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);

  // Step #9. Unset and create ouput
  unset($form['openlayers-ahah-wrapper-start'], $form['openlayers-ahah-wrapper-end']);
  $output = theme('status_messages') . drupal_render($form['layers']) . drupal_render($form['options']);

  // Final rendering callback.
  drupal_json(array('status' => TRUE, 'data' => $output));
}
 
/**
 * Get OpenLayers Form
 *
 * Get the form array to customize OpenLayers Maps.  This is a private
 * function for openlayers_map_form.  It is the responsibility
 * of the process calling this function to define defaults
 *
 * @param $form_state
 *   Array of defaults.
 * @return
 *   Array of form items
 */
function _openlayers_map_form($form_state) {
  // Initialize variables
  $form = array();
  $layers = openlayers_layers_get_info();
  $baselayers = array();
  $overlays = array();
  $defaults = $form_state;
  
  // Get layer options
  $layer_options = array(
    'overlays' => array(), 
    'baselayers' => array(),
  );
  
  // Determine which layer is a baselayer, and which is an overlay, and add
  // approrpriate descriptions to the options array.
  foreach ($layers as $layer_key => $layer) {
    $description = theme('openlayers_form_layer_description', $layer['name'], $layer['description']);
    if ($layer['baselayer']) {
      $layer_options['baselayers'][$layer_key] = $description;
    }
    else {
      $layer_options['overlays'][$layer_key] = $description;
    }
  }

  // Define list of projections
  $sorted_projections = _openlayers_get_projections($layers);
  $projections = array();
  foreach ($sorted_projections as $projection => $available_layers) {
    $projections[$projection] = theme('openlayers_form_projection_description', $projection, $available_layers, $layers);
  }
  // Set the "Other" option for our easy projection selector
  $projections['other'] = t("Other");
  // Unset All
  unset($projections['all']);
  
  // Figure out the projection we are using with AHAH involved
  if ($defaults['projections']['easy_projection'] && $defaults['projections']['easy_projection'] != 'other') {
    $default_proj = $defaults['projections']['easy_projection'];
  } elseif ($defaults['projections']['projection'] && $defaults['projections']['easy_projection'] == 'other') {
    $default_proj = $defaults['projections']['projection'];
  } else {
    $default_proj = $defaults['projection'];
  }
  
  // Check for other, which will show all layers available
  if (!$default_proj || $defaults['projections']['easy_projection'] == 'other') {
    $base_options = $layer_options['baselayers'];
    $reg_layer_options = $layer_options['baselayers'];
  }
  else {  
    // Create specific layer options for given projection
    foreach ($sorted_projections[$default_proj] as $p => $l) {
      if ($layer_options['baselayers'][$l]) {
        $base_options[$l] = $layer_options['baselayers'][$l];
      }
      if ($layer_options['baselayers'][$l]) {
        $reg_layer_options[$l] = $layer_options['baselayers'][$l];
      }
    }
  }

  // Centering map
  $centering_map = _openlayers_form_center_map($defaults);
  
  // Options
  if ($defaults['options']['automatic_options']) {
    $defaults['options']['displayProjection'] = '4326';
    
    // Check project
    if ($default_proj == '900913' || $default_proj == '3785') {
      $defaults['options']['maxResolution'] = '156543.0339';
      $defaults['options']['maxExtent']['left'] = '-20037508.34';
      $defaults['options']['maxExtent']['right'] = '20037508.34';
      $defaults['options']['maxExtent']['bottom'] = '-20037508.34';
      $defaults['options']['maxExtent']['top'] = '20037508.34';
    }
    else {
      $defaults['options']['maxResolution'] = '';
      $defaults['options']['maxExtent']['left'] = '';
      $defaults['options']['maxExtent']['right'] = '';
      $defaults['options']['maxExtent']['bottom'] = '';
      $defaults['options']['maxExtent']['top'] = '';
    }
  }
  
  // Form Properties
  $form['#tree'] = TRUE;
  $form['#cache'] = TRUE;
  
  // Map general properties
  $form['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#description' => t('Please use a CSS Width value.'),
    '#default_value' => $defaults['width'],
    '#maxlength' => 128,
  );
  $form['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#description' => t('Please use a CSS Height value.'),
    '#default_value' => $defaults['height'],
    '#maxlength' => 128,
  );
  
  // Map center properties
  $form['center'] = array(
    '#type' => 'fieldset',
    '#title' => t('Center'),
    '#description' => t('Where the map will center itself initially. You may use the small map to help you set your center and zoom.  Pan and zoom where you want the centering defaults to be.'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['center']['helpmap'] = array(
    '#value' => '<div class="form-item openlayers-center-helpmap" style="display:block">'. $centering_map['themed'] .'</div>'
  );
  $form['center']['lat'] = array(
    '#type' => 'textfield',
    '#title' => t('Latitude'),
    '#description' => t('Latitude or X value for centering.'),
    '#default_value' => $defaults['center']['lat'],
    '#attributes' => array('class' => 'openlayers-form-lat'), 
    '#size' => 25,
  );
  $form['center']['lon'] = array(
    '#type' => 'textfield',
    '#title' => t('Longitude'),
    '#description' => t('Longitude or Y value for centering.'),
    '#default_value' => $defaults['center']['lon'],
    '#attributes' => array('class' => 'openlayers-form-lon'), 
    '#size' => 25,
  );
  $form['center']['zoom'] = array(
    '#type' => 'textfield',
    '#title' => t('Zoom Level'),
    '#description' => t('Zoom level for centering.'),
    '#default_value' => $defaults['center']['zoom'],
    '#attributes' => array('class' => 'openlayers-form-zoom'), 
    '#size' => 25,
  );
  
  // Projections
  $form['projections'] = array(
    '#type' => 'fieldset',
    '#title' => t('Projection'),
    '#description' => t('Select projection for map.  This will affect which layers are available to choose from.'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // This will create an easy way to select projections and have layers change accordingly
  $form['projections']['easy_projection'] = array(
    '#type' => 'radios',
    '#title' => t('Projection'),
    '#description' => t('Select the EPSG code of the !link_proj for your map. The list next to each projection is the layers that support this projection.', array(
      '!link_proj' => l('geographical projection', 'http://en.wikipedia.org/wiki/Map_projection'),
    )),
    '#default_value' => $default_proj,
    '#options' => $projections,
    '#attributes' => array('class' => 'openlayers-form-easy-projection'),
    '#ahah' => array(
      'path' => 'openlayers/ahah',
      'wrapper' => 'openlayers-layers-select',
      'event' => 'change',
    ),
  );
  $form['projections']['projection'] = array(
    '#type' => 'textfield',
    '#title' => t('Projection'),
    '#description' => t('The EPSG code of the geographical projection for your map.'),
    '#attributes' => array('class' => 'openlayers-form-projection'), 
    '#default_value' => $default_proj,
    '#maxlength' => 16
  );
  
  // Start AHAH Wrapper
  $form['openlayers-ahah-wrapper-start'] = array(
    '#value' => '<div id="openlayers-layers-select">',
  );
  
  // Layers
  $form['layers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layers'),
    '#description' => t('Layer settings.  The Layer options will change based on the projection chosen above.'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['layers']['baselayers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Base Layers'),
    '#description' => t('Select the base layers to make available for your map. This list is determined by the projection you select for your map.'),
    '#options' => $base_options,
    '#attributes' => array('class' => 'openlayers-form-baselayers'), 
    '#multiple' => TRUE,
    '#default_value' => $defaults['layers']['baselayers'] ? $defaults['layers']['baselayers'] : array(),
  );
  $form['layers']['default_layer'] = array(
    '#type' => 'radios',
    '#title' => t('Default Base Layer'),
    '#description' => t('The default base layer to use when rendering maps.  This will be included whether it is in the base layers or not.'),
    '#options' => $base_options,
    '#attributes' => array('class' => 'openlayers-form-default-layer'), 
    '#default_value' => $defaults['layers']['default_layer'],
  );
  $form['layers']['overlays'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Overlay Layers'),
    '#description' => t('Select the overlay layers to make available for your map.'),
    '#options' => $layer_options['overlays'],
    '#attributes' => array('class' => 'openlayers-form-overlays'), 
    '#multiple' => TRUE,
    '#default_value' => $defaults['layers']['overlays'] ? $defaults['layers']['overlays'] : array(),
  );
  
  // Map options properties
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Options'),
    '#description' => t('Set additional options'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['options']['automatic_options'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatic Options'),
    '#description' => t('If this is checked, options will be automatically filled for you.'),
    '#default_value' => $defaults['options']['automatic_options'],
    '#maxlength' => 6
  );
  $form['options']['displayProjection'] = array(
    '#type' => 'textfield',
    '#title' => t('Display Projection'),
    '#description' => t('This is the projection that is presented to your users as the interface for viewing / editing location data. You will most likely want use 4326 for lat/lon coordinates.'),
    '#default_value' => $defaults['options']['displayProjection'],
    '#maxlength' => 6
  );
  $form['options']['maxResolution'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum Resolution'),
    '#description' => t('The maximum number of pixels / map unit at the highest zoom.'),
    '#default_value' => $defaults['options']['maxResolution'],
    '#attributes' => array('class' => 'openlayers-form-maxResolution'), 
  );
  $form['options']['maxExtent'] = array(
    '#type' => 'fieldset',
    '#title' => t('Maximum Extent'),
    '#description' => t('Set the bounds for the edges of your map. Set them according to the units of your projection.'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['options']['maxExtent']['left'] = array(
    '#type' => 'textfield',
    '#title' => t('Left'),
    '#default_value' => $defaults['options']['maxExtent']['left'],
    '#attributes' => array('class' => 'openlayers-form-maxExtent-left'), 
  );
  $form['options']['maxExtent']['right'] = array(
    '#type' => 'textfield',
    '#title' => t('Right'),
    '#default_value' => $defaults['options']['maxExtent']['right'],
    '#attributes' => array('class' => 'openlayers-form-maxExtent-right'), 
  );
  $form['options']['maxExtent']['bottom'] = array(
    '#type' => 'textfield',
    '#title' => t('Bottom'),
    '#default_value' => $defaults['options']['maxExtent']['bottom'],
    '#attributes' => array('class' => 'openlayers-form-maxExtent-bottom'), 
  );
  $form['options']['maxExtent']['top'] = array(
    '#type' => 'textfield',
    '#title' => t('Top'),
    '#default_value' => $defaults['options']['maxExtent']['top'],
    '#attributes' => array('class' => 'openlayers-form-maxExtent-top'), 
  );
  
  // End AHAH Wrapper
  $form['openlayers-ahah-wrapper-end'] = array(
    '#value' => '</div>',
  );
  
  // Add JavaScript
  drupal_add_js(drupal_get_path('module', 'openlayers') .'/js/openlayers.form.js', 'module');
  
  return $form;
}

/**
 * OpenLayers Form to Map
 *
 * Converst Form submission to map array.
 *
 * @param $values
 *   Array of values to convert
 * @return
 *   Array of form items
 */
function _openlayers_convert_form_to_map($values = array()) {
  // If the form values are empty then we have nothing to return.
  if (empty($values)) {
    return array();
  }
  $processed = array();
  
  // Take out form values
  $throw = array('op', 'submit', 'form_build_id', 'form_token', 'form_id', 'easy_projection','layers');
  foreach ($values as $k => $v) {
    if (!in_array($k, $throw)) {
      $processed[$k] = $v;
    }
  }
  
  // Put projection in right place.
  $processed['projection'] = ($values['projections']['easy_projection'] != 'other') ? $values['projections']['easy_projection'] : $values['projections']['projection'];
  
  // Put the default layer in the right place.
  $processed['default_layer'] = $values['layers']['default_layer'];
  
  // Merge our different layer sections together
  $baselayers = array_filter($values['layers']['baselayers']);
  $overlays = array_filter($values['layers']['overlays']);
  $processed['layers'] = array_merge($baselayers, $overlays);
  
  // Recursively unset any empty values
  $processed = _openlayers_unset_empty_values($processed);
  return $processed;
}

/**
 * OpenLayers Map to Form
 *
 * Converts Map array to form defaults array.
 *
 * @param $map
 *   Array of map values to convert
 * @return
 *   Array of default form values
 */
function _openlayers_convert_map_to_form($map = array()) {
  $processed = array();
  // Check input
  if (!is_array($map) || empty($map)) {
    return $processed;
  }
  $processed = $map;
  $layer_defs = openlayers_layers_get_info();
  
  // Manual changes
  $processed['layers'] = array();
  $processed['layers']['default_layer'] = $map['default_layer'];
  $processed['layers']['baselayers'] = array();
  $processed['layers']['overlays'] = array();
  
  if (is_array($map['layers'])) {
    foreach ($map['layers'] as $layer_id => $layer){
      if ($layer_defs[$layer_id]['baselayer']){
        $processed['layers']['baselayers'][] = $layer_id;
      }
      else {
        $processed['layers']['overlays'][] = $layer_id;
      }
    }
  }
    
  // Return processed
  return $processed;
}

/**
 * Sort Projections
 *
 * Given layers, sort projections out
 *
 * @param $layers
 *   Array of layers
 * @return
 *   Return sorted array
 */
function _openlayers_get_projections($layers = array()) {
  $all_projections = array();
  $projection_layers = array();
  
  // Check $layers
  if (!is_array($layers)) {
    return $projection_layers;
  }
  
  // Go through layers
  foreach ($layers as $layer_key => $layer) {
    // Check projections
    if ($layer['projection']) {
      // Go through projections
      foreach ($layer['projection'] as $projection) {
        if (!array_key_exists($projection, $projection_layers)){
          $projection_layers[$projection] = array();
        }
        $projection_layers[$projection][] = $layer_key;
      }
    }
  }
  
  // Add any layers that do not have a projection specified to all
  foreach ($layers as $layer_key => $layer) {
    // Check projections
    if (!$layer['projection']) {
      // Go through projections
      foreach ($projection_layers as $k => $v) {
        $projection_layers[$k][] = $layer_key;
      }
    }
  }
  
  // Return array
  return $projection_layers;
}

/**
 * OpenLayers Form Validate
 *
 * Validates a form submission. This is a private
 * function for openlayers_map_form_validate
 *
 * @param $map_form
 *   Array of values to validate
 * @return
 *   Does not return anything. Uses form_set_error() to communicate errors.
 */
function _openlayers_map_form_validate($form) {
  // Convert form to map array
  $map = _openlayers_convert_form_to_map($form);
  // Attempt to render map to find any errors
  $map = openlayers_render_map($map, FALSE);
  // Check if any errors found
  if (is_array($map['errors']) && count($map['errors']) > 0) {
    foreach ($map['errors'] as $error) {
      form_set_error('openlayers', t('OpenLayers Map Rendering Error: !error', array('!error' => $error)));
    }
  }
}

/**
 * Recursively unset empty values
 *
 * Go through an array recursively and unset empty strings and arrays
 *
 * @param $values
 *   Array
 * @return
 *   Array with empty values unset
 */
function _openlayers_unset_empty_values($array) {
  foreach($array as $key => $value) {
    // If it is an array then recursively check it
    if (is_array($value)){
      $array[$key] = _openlayers_unset_empty_values($value);
    }
    // If it is an array then check if it is empty. We don't use $value so that if it
    // is emptied by the previous check then it will still unset.
    if (is_array($array[$key])){
      if (empty($array[$key])){
        unset($array[$key]);
      }
    }
  
    // If it is an empty string then unset it
    if ($value == "") {
      unset($array[$key]);
    }
  }
  return $array;
}

/**
 * Create Centering Map
 *
 * Create map for interactive default centering
 *
 * @param $defaults
 *   Array of defults to use for the map of centering and zooming
 * @return
 *   Themed map array
 */
function _openlayers_form_center_map($defaults = array()) {
  // Set up our map to help set center lat, lon and zoom
  // This map will always be projected as 4326 and use just the basic layer so that
  // even if the user is using screwed up map settings, this map will still function.
  $centermap_def = array(
    'id' => 'openlayers-center-helpmap',
    'projection' => '4326',
    'default_layer' => 'openlayers_default_wms',
    'width' => '400px',
    'height' => '300px',
    'center' => array(
      'lat' => ($defaults['center']['lat']) ? $defaults['center']['lat'] : 0,
      'lon' => ($defaults['center']['lon']) ? $defaults['center']['lon'] : 0,
      'zoom' => ($defaults['center']['zoom']) ? $defaults['center']['zoom'] : 2,
    ),
    'only_these_layers' => TRUE,
    'layers' => array(
      'openlayers_default_wms',
    ),
    'options' => array(
      'displayProjection' => $defaults['projection'],
      'maxResolution' => '1.40625',
      'maxExtent' => array(
        'top' => 90,
        'bottom' => -90,
        'left' => -180,
        'right' => 180
      ),
    ),
    'events' => array(
      'moveend' => array('updateCenterFormValues'),
      'zoomend' => array('updateCenterFormValues'),
    ),
  );
  
  // Pass variables etc. to javascript
  $passvalues = array(
    'openlayersForm' => array(
      'projectionLayers' => _openlayers_get_projections($layers),
    ),
  );
  drupal_add_js($passvalues, 'setting');
  // Render map
  return openlayers_render_map($centermap_def);
}