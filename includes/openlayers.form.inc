<?php
// $Id$

/**
 * @file
 * This file holds the functions for the settings forms.
 */
 
/**
 * Get OpenLayers Form
 *
 * Get the form array to customize OpenLayers Maps.  This is a private
 * function for openlayers_map_form
 *
 * @param $defaults
 *   Array of defaults
 * @return
 *   Array of form items
 */
function _openlayers_map_form($defaults = array()) {
  // Names of fields and fieldssets should correspond to the map array
  $form = array();
  // Get layers options
  $layers = openlayers_layers_get_info();
  // @@TODO: Best way
  
  $baselayers = array();
  $overlays = array();
  
  // Determine which layer is a baselayer, and which is an overlay.
  foreach ($layers as $layer_key => $layer) {
    if ($layer['baselayer']){
      $baselayers[$layer_key] = $layer['name'];
      if ($layer['description']) $baselayers[$layer_key] .= " - <span class='openlayers-form-baselayer-description'>". $layer['description'] ."</span>";
    }
    else {
      $overlays[$layer_key] = $layer['name'];
      if ($layer['description']) $overlays[$layer_key] .= " - <span class='openlayers-form-baselayer-description'>". $layer['description'] ."</span>";
    }
  }
  
  // Set up our easy projection selector options. 
  // We are setting up the 'easy projection' options, a list of layers that are compatible with all projections,
  // and an array to pass to JS that contains a list of all the layers indexed by projection
  $easy_projections = array();
  $all_projections = array();
  $projection_layers = array();
  foreach ($layers as $layer_key => $layer) {
    if ($layer['projection']){
      foreach ($layer['projection'] as $projection){
        
        // Fill out the easy projection form options
        if (!array_key_exists($projection, $easy_projections)){
          $easy_projections[$projection] = $projection. " - <span class='openlayers-form-proj-layer-list'>". $layer['name'] ."</span>";
        }
        else{
          $easy_projections[$projection] .= "<span class='openlayers-form-proj-layer-list'>, ". $layer['name'] ."</span>";
        }
        
        // Fill out the array we will pass to javascript.
        if (!array_key_exists($projection, $projection_layers)){
          $projection_layers[$projection] = array();
        }
        $projection_layers[$projection][] = $layer_key;
        
      }
    }
    else{
      $all_projections[$layer_key] = $layer['name'];
    }
  }
 
  // Set the "Other" option for our easy projection selector
  $easy_projections['other'] = t("Other");
  
  // Add the layers that are compatible with all projections to our $projection_layers array
  foreach ($all_projections as $layer_key => $layer){
    foreach ($projection_layers as $projection => $list_of_layers){
      $projection_layers[$projection][] = $layer_key;
    }
  }
  
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
      'lat' => 0,
      'lon' => 0,
      'zoom' => 0,
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
      'moveend' => array('openlayersUpdateCenterFormValues'),
      'zoomend' => array('openlayersUpdateCenterFormValues'),
    ),
  );
  
  // Pass variables etc. to javascript
  $centermap = openlayers_render_map($centermap_def);
  
  $passvalues = array(
      'openlayersForm' => array(
        'projectionLayers' => $projection_layers,
      ),
  );
  drupal_add_js($passvalues, 'setting');
  
  
  // Form Properties
  $form['#tree'] = TRUE;

  $form['easy_projection'] = array(
    '#type' => 'radios',
    '#title' => t('Projection'),
    '#description' => t('Slect the EPSG code of the '.l('geographical projection', 'http://en.wikipedia.org/wiki/Map_projection').' for your map. The list next to each projection is the layers that support this projection. Layers that support all projections are: '. implode(', ', $all_projections)."."),
    '#options' => $easy_projections,
    '#attributes' => array('class' => 'openlayers-form-easy-projection'), 
  );
  
  $form['projection'] = array(
    '#type' => 'textfield',
    '#title' => t('Projection'),
    '#description' => t('The EPSG code of the geographical projection for your map.'),
    '#attributes' => array('class' => 'openlayers-form-projection'), 
    '#default_value' => $defaults['projection'],
    '#maxlength' => 6
  );
  
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
    '#description' => t('Where the map will center itself initially. You may use the small map to help you set your center and zoom'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['center']['helpmap'] = array(
    '#value' => '<div class="form-item openlayers-center-helpmap" style="display:block">'.$centermap['themed'].'</div>'
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
  
  // Map options properties
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Options'),
    '#description' => t('Set additional options'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
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
  
  // Map layer properties
  $form['layers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layers'),
    '#description' => t('Layer settings.'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['layers']['baselayers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Base Layers'),
    '#description' => t('Select the base layers to make available for your map. This list is determined by the projection you select for your map.'),
    '#options' => $baselayers,
    '#attributes' => array('class' => 'openlayers-form-baselayers'), 
    '#multiple' => TRUE,
    '#default_value' => $defaults['layers']['baselayers'],
  );
  $form['layers']['default_layer'] = array(
    '#type' => 'radios',
    '#title' => t('Default Base Layer'),
    '#description' => t('The default base layer to use when rendering maps.  This will be included whether it is in the base layers or not.'),
    '#options' => $baselayers,
    '#attributes' => array('class' => 'openlayers-form-default-layer'), 
    '#default_value' => $defaults['layers']['default_layer'],
  );
  $form['layers']['overlays'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Overlay Layers'),
    '#description' => t('Select the overlay layers to make available for your map.'),
    '#options' => $overlays,
    '#attributes' => array('class' => 'openlayers-form-overlays'), 
    '#multiple' => TRUE,
    '#default_value' => $defaults['layers']['overlays'],
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
 * @ingroup API
 * @param $values
 *   Array of values to convert
 * @return
 *   Array of form items
 */
function _openlayers_convert_form_to_map($values = array()) {
  // If the form values are empty then we have nothing to return.
  if (empty($values)){
    return array();
  }
  
  $processed = array();
  
  // Take out form values
  // @@TODO: Is this the best way to do this?
  $throw = array('op', 'submit', 'form_build_id', 'form_token', 'form_id', 'easy_projection','layers');
  foreach ($values as $k => $v) {
    if (!in_array($k, $throw)) {
      $processed[$k] = $v;
    }
  }
  
  // Put the default layer in the right place.
  $processed['default_layer'] = $values['layers']['default_layer'];
  
  // Merge our different layer sections together
  $baselayers = array_filter($values['layers']['baselayers']);
  $overlays = array_filter($values['layers']['overlays']);
  $processed['layers'] = array_merge($baselayers, $overlays);
  
  // Recursively unset any empty values
  $processed = openlayers_recursively_unset_empty_values($processed);
  
  return $processed;
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
function _openlayers_map_form_validate($map_form){
  $map = _openlayers_convert_form_to_map($map_form);
  $map = openlayers_prepare_map($map);
  
  // @@TODO: Invoke map alter?  It's possible that outside modules may detect and fix errors. 
  
  $error = openlayers_error_check_map($map, FALSE);
  
  if ($error){
    form_set_error('openlayers', "OpenLayers Map Error: ".$error);
  }
}

/**
 * Recursively unset empty values
 *
 * Go through an array recursively and unset empty strings and arrays
 *
 * @ingroup API
 * @param $values
 *   Array
 * @return
 *   Array with empty values unset
 */
function openlayers_recursively_unset_empty_values($array){
 foreach($array as $key => $value) {
  // If it is an array then recursively check it
  if (is_array($value)){
    $array[$key] = openlayers_recursively_unset_empty_values($value);
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