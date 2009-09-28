<?php
// $Id$

/**
 * @file
 * This file holds the functions for the openlayers presets ui
 *
 * @ingroup openlayers
 */

/**
 * Menu Callback for Various Object Lists
 */
function openlayers_ui_object_list($type = 'presets') {
  $rows = array();

  // Make table of presets and actions
  $header = array(
    t('Title'),
    t('Description'),
    t('Actions'),
  );

  // Get objects
  switch ($type) {
    case 'presets':
      $objects = openlayers_presets(TRUE);
      break;
      
    case 'styles':
      $objects = openlayers_styles(TRUE);
      break;
      
    case 'layers':
      $objects = openlayers_layers(TRUE);
      break;

  }

  // Create table rows
  foreach ($objects as $object) {
    $row = array();
    $links = array();
    $row[] = $object->title;
    $row[] = $object->description;
    // Check preset type and create links accordingly.
    if ($object->export_type == (EXPORT_IN_CODE | EXPORT_IN_DATABASE)) {
      $links[] = l(t('Edit'), "admin/settings/openlayers/{$type}/{$object->name}/edit");
      $links[] = l(t('Revert'), "admin/settings/openlayers/{$type}/{$object->name}/delete");
    }
    elseif ($object->export_type == EXPORT_IN_DATABASE) {
      $links[] = l(t('Edit'), "admin/settings/openlayers/{$type}/{$object->name}/edit");
      $links[] = l(t('Delete'), "admin/settings/openlayers/{$type}/{$object->name}/delete");
    }
    $links[] = l(t('Export'), "admin/settings/openlayers/{$type}/{$object->name}/export");
    $links[] = l(t('Clone'), "admin/settings/openlayers/{$type}/add/{$object->name}");
    $row[] = implode(' | ', $links);
    $rows[] = $row;
  }

  // Output themed table
  $output = theme('table', $header, $rows);
  return $output;
}

/**
 * Menu callback for object delete form.
 */
function openlayers_ui_object_delete(&$form_state, $type, $object) {
  if ($object->export_type & EXPORT_IN_DATABASE) {
    // Create delete form
    $form = array(
      'type' => array('#type' => 'value', '#value' => $type),
      'object' => array('#type' => 'value', '#value' => $object),
    );
    $message = ($object->export_type & EXPORT_IN_CODE) ?
      t('Are you sure you want to revert %object?', array('%object' => $object->title)) :
      t('Are you sure you want to delete %object?', array('%object' => $object->title));
    return confirm_form($form, $message, 'admin/settings/openlayers/'. $type);
  }
}

/**
 * Form Submit Callback for Preset Delete Form
 */
function openlayers_ui_object_delete_submit($form, &$form_state) {
  $type = $form_state['values']['type'];
  $object = $form_state['values']['object'];

  switch ($type) {
    case 'styles':
      $result = db_query("DELETE FROM {openlayers_styles} WHERE name = '%s'", $object->name);
      break;
      
    case 'layers':
      $result = db_query("DELETE FROM {openlayers_layers} WHERE name = '%s'", $object->name);
      break;
      
    case 'presets':
      $result = db_query("DELETE FROM {openlayers_map_presets} WHERE name = '%s'", $object->name);
      break;
  }

  // Check query results
  if ($result) {
    drupal_set_message(t('%name was deleted.', array('%name' => $object->name)));
  }
  else {
    drupal_set_message(t('Error when attempting to delete %name.', array('%name' => $object->name)), 'error');
  }

  // Redirect
  $form_state['redirect'] = 'admin/settings/openlayers/'. $type;
}

/**
 * Menu callback for object export form.
 */
function openlayers_ui_object_export(&$form_state, $type, $object) {
  switch ($type) {
    case 'styles':
      $api = 'openlayers_styles';
      break;
    case 'layers':
      $api = 'openlayers_layers';
      break;
    case 'presets':
      $api = 'openlayers_map_presets';
      break;

  }
  ctools_include('export');
  $code = '$items = array();' ."\n";
  $code .= ctools_export_object($api, $object, '');
  $code .= '$items["'. $object->name .'"] = $' . $api . ';' ."\n";
  $code .= 'return $items;';

  $rows = substr_count($code, "\n") + 1;

  // Create form
  $form = array();
  $form['export'] = array(
    '#type' => 'textarea',
    '#default_value' => $code,
    '#rows' => $rows,
    '#resizable' => FALSE,
  );
  $form['done'] = array(
    '#type' => 'submit',
    '#value' => t('Done'),
  );
  $form['#redirect'] = 'admin/settings/openlayers/'. $type;

  return $form;
}

/**
 * Menu Callback for Preset Form
 */
function openlayers_ui_presets_form(&$form_state, $preset = NULL, $edit = FALSE) {
  $form = array();
  $layers = openlayers_layers();
  $baselayers = array();
  $overlays = array();
  $available_controls = _openlayers_ui_available_controls();
  $styles = openlayers_styles_get_info();
  $available_styles = array();

  // Ensure we are not editing any coded presets
  if (($preset->export_type == EXPORT_IN_CODE) && $edit) {
    drupal_set_message(t('Cannot edit default preset.'), 'error');
    drupal_goto('admin/settings/openlayers/presets');
  }

  // If cloning or editing, attempt to get preset
  if (empty($preset)) {
    $default_map = openlayers_get_default_map();
  }
  else {
    $default_map = $preset->data;
    // Push the preset data into the map
    $default_map['title'] = $preset->title;
    $default_map['description'] = $preset->description;
  }

  // Update map for new form
  if (!empty($form_state['values'])) {
    $form_map = _openlayers_ui_convert_form_to_map($form_state['values']);
    $default_map = openlayers_merge_maps($default_map, $form_map);
  }

  // Change map to form values
  $defaults = _openlayers_ui_convert_map_to_form($default_map);
  // Merge with form values
  $defaults = (is_array($form_state['values'])) ? $form_state['values'] + $defaults : $defaults;
  $rendered_map = (is_array($default_map)) ? openlayers_render_map($default_map) : array();

  // Get layer options
  $layer_options = array(
    'overlays' => array(),
    'baselayers' => array(),
  );

  // Determine which layer is a baselayer, and which is an overlay, and add
  // approrpriate descriptions to the options array.
  foreach ($layers as $layer_key => $layer) {
    $description = theme('openlayers_ui_form_layer_description', $layer->name, $layer->description);
    if ($layer->data['baselayer']) {
      $layer_options['baselayers'][$layer_key] = $description;
    }
    else {
      $layer_options['overlays'][$layer_key] = $description;
    }
  }

  // Define list of projections
  $sorted_projections = _openlayers_ui_get_projections($layers);
  $projections = array();
  foreach ($sorted_projections as $projection => $available_layers) {
    $projections[$projection] = theme('openlayers_ui_form_projection_description', $projection, $available_layers, $layers);
  }
  // Set the "Other" option for our easy projection selector
  $projections['other'] = t("Other");
  // Unset All
  unset($projections['all']);

  // Default projection
  $default_proj = $defaults['projections']['projection'];

  // Check for other, which will show all layers available
  if (!$default_proj || $defaults['projections']['easy_projection'] == 'other') {
    $base_options = $layer_options['baselayers'];
    $overlay_options = $layer_options['overlays'];
  }
  else {
    // Create specific layer options for given projection
    foreach ($sorted_projections[$default_proj] as $p => $l) {
      if ($layer_options['baselayers'][$l]) {
        $base_options[$l] = $layer_options['baselayers'][$l];
      }
      if ($layer_options['overlays'][$l]) {
        $overlay_options[$l] = $layer_options['overlays'][$l];
      }
    }
  }

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

  // Make style options array
  foreach ($styles as $k_style => $style) {
    $avilable_styles[$k_style] = $style['name'];
  }

  // Centering map
  $centering_map = _openlayers_ui_form_center_map($defaults);

  // Form Properties
  $form['#tree'] = TRUE;
  $form['#cache'] = TRUE;

  // Pass editing along
  $form['preset_edit'] = array(
    '#type' => 'value',
    '#value' => $edit,
  );

  // Pass along map data, since it can hold stuff
  // that the UI cannot account for
  $form['default_map'] = array(
    '#type' => 'value',
    '#value' => $default_map,
  );

  // Preview of map
  $form['map_preview'] = array(
    '#type' => 'item',
    '#title' => t('Example Map'),
    '#description' => t('This is a preview of current map before saving.'),
    '#value' => $rendered_map['themed'],
  );

  // General properties
  $form['info'] = array(
    '#title' => t('General information'),
    '#tree' => FALSE,
  );
  $form['info']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Preset Name'),
    '#description' => t('This is the machine readable identifier.  This should be all lowercase characters, numbers, or underscores (_).'),
    '#maxlength' => 255,
    '#default_value' => !empty($defaults['name']) ? $defaults['name'] : '',
    '#disabled' => $edit,
  );
  // If edit, set value
  if ($edit) {
    $form['preset_name']['#value'] = $defaults['preset_name'];
  }

  $form['info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Preset Title'),
    '#description' => t('This is the descriptive title of the preset and will show up most often in the interface.'),
    '#maxlength' => 255,
    '#default_value' => !empty($defaults['title']) ? $defaults['title'] : '',
  );
  $form['info']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Preset Description'),
    '#description' => t('This is full description of the preset and is mostly used on the preset overview list page.'),
    '#rows' => 2,
    '#default_value' => !empty($defaults['description']) ? $defaults['description'] : '',
  );
  $form['info']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#description' => t('Please use a CSS Width value.'),
    '#default_value' => !empty($defaults['width']) ? $defaults['width'] : '',
    '#maxlength' => 128,
  );
  $form['info']['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#description' => t('Please use a CSS Height value.'),
    '#default_value' => !empty($defaults['height']) ? $defaults['height'] : '',
    '#maxlength' => 128,
  );
  $form['info']['image_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Image Path'),
    '#description' => t('The path to a directory for OpenLayers to look for UI graphics. If blank, default graphics are used.'),
    '#default_value' => !empty($defaults['image_path']) ? $defaults['image_path'] : '',
  );
  $form['info']['css_path'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS Path'),
    '#description' => t('Path for where OpenLayers should look for its theme CSS file. The default hosted OpenLayers URL is http://openlayers.org/api/theme/default/style.css'),
    '#default_value' => !empty($defaults['css_path']) ? $defaults['css_path'] : '',
  );

  // Map center properties
  $form['center'] = array(
    '#title' => t('Center'),
    '#description' => t('Where the map will center itself initially. You may use the small map to help you set your center and zoom.  Pan and zoom where you want the centering defaults to be.'),
    '#tree' => TRUE,
  );
/*
  $form['center']['helpmap'] = array(
    '#value' => '<div class="form-item openlayers-center-helpmap" style="display:block">'. $centering_map['themed'] .'</div>'
  );
*/
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
  
  // Behaviors
  $form['behaviors'] = array(
    '#title' => t('Behaviors'),
    '#description' => t('Configure interactive map behaviors and controls.'),
    '#tree' => TRUE,
  );
  $form['behaviors'] = $form['behaviors'] + _openlayers_ui_get_behavior_options('map', $defaults);

  // Vector Styles
  $form['styles'] = array(
    '#title' => t('Vector Styles'),
    '#description' => t('Styles used on features in vector layers.'),
    '#tree' => TRUE,
  );
  $form['styles']['default'] = array(
    '#type' => 'select',
    '#title' => t('Default Style'),
    '#description' => t('Default style for features in a vector.'),
    '#options' => $avilable_styles,
    '#default_value' => $defaults['styles']['default'],
  );
  $form['styles']['select'] = array(
    '#type' => 'select',
    '#title' => t('Select Style'),
    '#description' => t('Default style for features in a vector that are selected.'),
    '#options' => $avilable_styles,
    '#default_value' => $defaults['styles']['select'],
  );
  $form['styles']['temporary'] = array(
    '#type' => 'select',
    '#title' => t('Temporary Style'),
    '#description' => t('Default style for any temporary features in a vector.  This will also be used for rollovers for things like Tooltips.'),
    '#options' => $avilable_styles,
    '#default_value' => $defaults['styles']['temporary'],
  );

  // Projections and Layers
  $form['projection_layers'] = array(
    '#title' => t('Projection and Layers'),
    '#description' => t('Manage projections and layers for the map.'),
    '#tree' => FALSE,
  );
  // Projections
  $form['projection_layers']['projections'] = array(
    '#type' => 'fieldset',
    '#title' => t('Projection'),
    '#description' => t('Select projection for map.  This will affect which layers are available to choose from.'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  // This will create an easy way to select projections and have layers change accordingly
  $form['projection_layers']['projections']['easy_projection'] = array(
    '#type' => 'radios',
    '#title' => t('Projection'),
    '#description' => t('Select the EPSG code of the !link_proj for your map. The list next to each projection is the layers that support this projection.', array(
      '!link_proj' => l(t('geographical projection'), 'http://en.wikipedia.org/wiki/Map_projection'),
    )),
    '#default_value' => $defaults['projections']['easy_projection'],
    '#options' => $projections,
    '#attributes' => array('class' => 'openlayers-form-easy-projection'),
    '#ahah' => array(
      'path' => 'openlayers/ahah/preset',
      'wrapper' => 'openlayers-layers-select',
      'event' => 'change',
    ),
  );
  $form['projection_layers']['projections']['projection'] = array(
    '#type' => 'textfield',
    '#title' => t('Projection'),
    '#description' => t('The EPSG code of the geographical projection for your map.'),
    '#attributes' => array('class' => 'openlayers-form-projection'),
    '#default_value' => $defaults['projections']['projection'],
    '#maxlength' => 16,
  );

  // Start AHAH Wrapper
  $form['projection_layers']['openlayers-ahah-wrapper-start'] = array(
    '#value' => '<div id="openlayers-layers-select">',
  );

  // Layers
  $form['projection_layers']['layers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layers'),
    '#description' => t('Layer settings.  The Layer options will change based on the projection chosen above.'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['projection_layers']['layers']['baselayers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Base Layers'),
    '#description' => t('Select the base layers to make available for your map. This list is determined by the projection you select for your map.'),
    '#options' => $base_options,
    '#attributes' => array('class' => 'openlayers-form-baselayers'),
    '#multiple' => TRUE,
    '#default_value' => $defaults['layers']['baselayers'] ? $defaults['layers']['baselayers'] : array(),
  );
  $form['projection_layers']['layers']['default_layer'] = array(
    '#type' => 'radios',
    '#title' => t('Default Base Layer'),
    '#description' => t('The default base layer to use when rendering maps.  This will be included whether it is in the base layers or not.'),
    '#options' => $base_options,
    '#attributes' => array('class' => 'openlayers-form-default-layer'),
    '#default_value' => $defaults['layers']['default_layer'],
  );
  $form['projection_layers']['layers']['overlays'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Overlay Layers'),
    '#description' => t('Select the overlay layers to make available for your map.'),
    '#options' => $overlay_options,
    '#attributes' => array('class' => 'openlayers-form-overlays'),
    '#multiple' => TRUE,
    '#default_value' => $defaults['layers']['overlays'] ? $defaults['layers']['overlays'] : array(),
  );

  // Map options properties
  $form['projection_layers']['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Options'),
    '#description' => t('Set additional options'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['projection_layers']['options']['automatic_options'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatic Options'),
    '#description' => t('If this is checked, options will be automatically filled for you.'),
    '#default_value' => isset($defaults['options']['automatic_options']) ?$defaults['options']['automatic_options'] : TRUE,
    '#maxlength' => 6
  );
  $form['projection_layers']['options']['displayProjection'] = array(
    '#type' => 'textfield',
    '#title' => t('Display Projection'),
    '#description' => t('This is the projection that is presented to your users as the interface for viewing / editing location data. You will most likely want use 4326 for lat/lon coordinates.'),
    '#default_value' => $defaults['options']['displayProjection'],
    '#maxlength' => 6
  );
  $form['projection_layers']['options']['maxResolution'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum Resolution'),
    '#description' => t('The maximum number of pixels / map unit at the highest zoom.'),
    '#default_value' => $defaults['options']['maxResolution'],
    '#attributes' => array('class' => 'openlayers-form-maxResolution'),
  );
  $form['projection_layers']['options']['maxExtent'] = array(
    '#type' => 'fieldset',
    '#title' => t('Maximum Extent'),
    '#description' => t('Set the bounds for the edges of your map. Set them according to the units of your projection.'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['projection_layers']['options']['maxExtent']['left'] = array(
    '#type' => 'textfield',
    '#title' => t('Left'),
    '#default_value' => $defaults['options']['maxExtent']['left'],
    '#attributes' => array('class' => 'openlayers-form-maxExtent-left'),
  );
  $form['projection_layers']['options']['maxExtent']['right'] = array(
    '#type' => 'textfield',
    '#title' => t('Right'),
    '#default_value' => $defaults['options']['maxExtent']['right'],
    '#attributes' => array('class' => 'openlayers-form-maxExtent-right'),
  );
  $form['projection_layers']['options']['maxExtent']['bottom'] = array(
    '#type' => 'textfield',
    '#title' => t('Bottom'),
    '#default_value' => $defaults['options']['maxExtent']['bottom'],
    '#attributes' => array('class' => 'openlayers-form-maxExtent-bottom'),
  );
  $form['projection_layers']['options']['maxExtent']['top'] = array(
    '#type' => 'textfield',
    '#title' => t('Top'),
    '#default_value' => $defaults['options']['maxExtent']['top'],
    '#attributes' => array('class' => 'openlayers-form-maxExtent-top'),
  );

  // End AHAH Wrapper
  $form['projection_layers']['openlayers-ahah-wrapper-end'] = array(
    '#value' => '</div>',
  );
  
  // Buttons
  $form['buttons'] = array(
    '#tree' => FALSE,
  );

  // Add a submit button that is the submit handler for the
  // AHAH change event on projections
  $form['buttons']['openlayers_projection_ahah'] = array(
    '#type' => 'submit',
    '#value' => t('Update Projections'),
    '#submit' => array('openlayers_presets_manage_add_projection_submit'),
  );

  // Save button
  $form['buttons']['openlayers_save'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );
  // Cancel button
  $form['buttons']['openlayers_cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel')
  );

  // Add JavaScript
  drupal_add_js(drupal_get_path('module', 'openlayers_ui') .'/js/openlayers_ui.ui.js', 'module');
  // Add CSS
  drupal_add_css(drupal_get_path('module', 'openlayers_ui') .'/openlayers_ui.css');

  return $form;
}

/**
 * OpenLayers Preset Form Validate
 *
 * Validates a preset form submission.
 *
 * @param $map_form
 *   Array of values to validate
 * @return
 *   Does not return anything. Uses form_set_error() to communicate errors.
 */
function openlayers_ui_presets_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  $found_error = FALSE;

  // Check if ahah submitting
  if ($form_state['clicked_button']['#id'] == 'edit-openlayers-projection-ahah') {
    return TRUE;
  }

  // Check for cancel
  if ($form_state['clicked_button']['#id'] == 'edit-openlayers-cancel') {
    return TRUE;
  }

  // Check for values.  We manually do required fields because, it would otherwise
  // mess with the AHAH stuff.  Maybe a way around it.
  if (empty($values['preset_name'])) {
    form_set_error('preset_name', t('Preset Name is required.'));
    $found_error = TRUE;
  }
  if (empty($values['preset_title'])) {
    form_set_error('preset_title', t('Preset Title is required.'));
    $found_error = TRUE;
  }
  if (empty($values['preset_description'])) {
    form_set_error('preset_description', t('Preset Description is required.'));
    $found_error = TRUE;
  }
  if (empty($values['width'])) {
    form_set_error('width', t('Width is required.'));
    $found_error = TRUE;
  }
  if (empty($values['height'])) {
    form_set_error('height', t('Height is required.'));
    $found_error = TRUE;
  }

  // Check preset name first
  if (!preg_match('!^[a-z0-9_]+$!', $values['preset_name'])) {
    form_set_error('preset_name', t('Preset Name must contain only lowercase letters, numbers, and underscores.'));
    $found_error = TRUE;
  }

  // Check if adding and name already exists
  $existing = openlayers_get_preset($values['preset_name'], TRUE);
  if (!empty($existing) && (!$form_state['values']['preset_edit']) && $existing->get_type & EXPORT_IN_DATABASE) {
    form_set_error('preset_name', t('The Preset Name already exists.'));
    $found_error = TRUE;
  }

  // Convert form to map array
  $map = _openlayers_ui_convert_form_to_map($form_state['values']);
  
  // Attempt to render map to find any errors
  $map = openlayers_render_map($map, FALSE);
  
  // Check if any errors found
  if (is_array($map['errors']) && count($map['errors']) > 0) {
    foreach ($map['errors'] as $error) {
      form_set_error('openlayers', t('OpenLayers Map Rendering Error: !error', array('!error' => $error)));
      $found_error = TRUE;
    }
  }

  // If found error, rebuild form
  if ($found_error) {
    $form_state['rebuild'] = TRUE;
  }
}

/**
 * Form submit for preset add form, for the projection add ahah
 */
function openlayers_ui_presets_form_projection_submit($form, &$form_state) {
  unset($form_state['submit_handlers']);
  form_execute_handlers('submit', $form, $form_state);
  $form_state['rebuild'] = TRUE;
}

/**
 * Form submit for preset add form
 */
function openlayers_ui_presets_form_submit($form, &$form_state) {
  // Check for cancel
  if ($form_state['clicked_button']['#id'] == 'edit-openlayers-cancel') {
    $form_state['redirect'] = 'admin/settings/openlayers/presets/list';
  }

  // Only save if save button is pressed
  if ($form_state['clicked_button']['#id'] == 'edit-openlayers-save') {
    // Merge with original map data to account for data
    // that cannot be accounted for UI
    if (!empty($form_state['values']['default_map'])) {
      // Convert form, but keep empty values, so merging is subtractive
      $map = _openlayers_ui_convert_form_to_map($form_state['values'], FALSE);
      $map = _openlayers_ui_merge_maps($map, $form_state['values']['default_map']);
    }
    else {
      $map = _openlayers_ui_convert_form_to_map($form_state['values']);
    }

    // Create preset object
    $preset = new stdClass();
    $preset->name = $form_state['values']['preset_name'];
    $preset->title = $form_state['values']['preset_title'];
    $preset->description = $form_state['values']['preset_description'];
    $preset->data = $map;

    // Save preset
    $success = openlayers_save_preset($preset);
    // Redirect to edit page
    if ($success) {
      drupal_set_message(t('Map saved.'));
      $form_state['redirect'] = 'admin/settings/openlayers/presets/' . $preset->name . '/edit';
    }
    else {
      form_set_error('openlayers', t('Error trying to save map'));
    }
  }
}

/**
 * OpenLayers AHAH
 *
 * Function to handle the AHAH request of the openlayers form
 */
function openlayers_ui_preset_ahah() {
  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);

  // Get variables
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;

  // Reprocess form with new form state
  drupal_process_form($form_id, $form, $form_state);
  // Rebuild form and remove any submot handlers
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);

  // Unset wrapper and create output
  unset($form['openlayers-ahah-wrapper-start'], $form['openlayers-ahah-wrapper-end']);
  $output = theme('status_messages') . drupal_render($form['layers']) . drupal_render($form['options']);

  // Final rendering callback.
  drupal_json(array('status' => TRUE, 'data' => $output));
}

/**
 * Drupal Form for Layer add/edit form.
 */
function openlayers_ui_layers_form(&$form_state, $layer = NULL, $edit = FALSE) {
  // TODO: Need to be able to add types of layers, each with their
  // own set of form
  $form = array();

  $form['info'] = array(
    '#type' => 'fieldset',
    '#tree' => FALSE,
  );
  $form['info']['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => !empty($layer->name) ? $layer->name : '',
  );
  $form['info']['title'] = array(
    '#title' => t('Title'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => !empty($layer->title) ? $layer->title : '',
  );
  $form['info']['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textfield',
    '#default_value' => !empty($layer->description) ? $layer->description : '',
  );

  if (empty($layer) || (!empty($layer->data['type']) && $layer->data['type'] == "KMLHTTP")) {
    $form['data'] = array('#type' => 'fieldset', '#tree' => TRUE);
    $defaults = array(
      'type' => 'KMLHTTP',
      'projection' => array(4326, 900913),
      'baselayer' => FALSE,
      'options' => array('isBaseLayer' => FALSE),
      'events' => array('loadend' => array()),
    );
    foreach ($defaults as $key => $value) {
      $form['data'][$key] = array('#type' => 'value', '#value' => $value);
    }
    $form['data']['url'] = array(
      '#title' => t('URL of KML feed'),
      '#type' => 'textfield',
      '#default_value' => !empty($layer->data['url']) ? $layer->data['url'] : '',
    );
  }
  else if (!empty($layer)) {
    $form['data'] = array('#type' => 'value', '#value' => $layer->data);
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * Submit handler for layers.
 */
function openlayers_ui_layers_form_submit(&$form, &$form_state) {
  // Save preset
  $layer = new stdClass();
  $layer->name = $form_state['values']['name'];
  $layer->title = $form_state['values']['title'];
  $layer->description = $form_state['values']['description'];
  $layer->data = $form_state['values']['data'];

  // Doctor some values
  $layer->data['id'] = $layer->name;
  $layer->data['name'] = $layer->name;

  $success = openlayers_layer_save($layer);

  // Redirect to edit page
  if ($success) {
    drupal_set_message(t('Layer saved.'));
    $form_state['redirect'] = 'admin/settings/openlayers/layers/' . $layer->name . '/edit';
  }
  else {
    form_set_error('openlayers', t('Error trying to save layer.'));
  }
}

/**
 * Drupal Form for Styles add/edit.
 */
function openlayers_ui_styles_form(&$form_state, $style = NULL, $edit = FALSE) {
  $form = array();

  $form['info'] = array(
    '#type' => 'fieldset',
    '#tree' => FALSE,
  );
  $form['info']['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => !empty($style->name) ? $style->name : '',
  );
  $form['info']['title'] = array(
    '#title' => t('Title'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => !empty($style->title) ? $style->title : '',
  );
  $form['info']['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textfield',
    '#default_value' => !empty($style->description) ? $style->description : '',
  );

  $form['data'] = array('#type' => 'fieldset', '#tree' => TRUE);
  $defaults = array(
    'externalGraphic' => '',
    'pointRadius' => 5,
    'fillColor' => '#FFFFFF',
    'strokeColor' => '#FFFFFF',
    'strokeWidth' => 5,
    'fillOpacity' => 0.5,
  );
  foreach ($defaults as $key => $value) {
    $form['data'][$key] = array(
      '#title' => $key,
      '#type' => 'textfield',
      '#default_value' => isset($style->data[$key]) ? $style->data[$key] : $value,
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * Submit handler for styles.
 */
function openlayers_ui_styles_form_submit(&$form, &$form_state) {
  $style = new stdClass();
  $style->name = $form_state['values']['name'];
  $style->title = $form_state['values']['title'];
  $style->description = $form_state['values']['description'];
  $style->data = $form_state['values']['data'];

  $success = openlayers_style_save($style);

  // Redirect to edit page
  if ($success) {
    drupal_set_message(t('Style saved.'));
    $form_state['redirect'] = 'admin/settings/openlayers/styles/' . $style->name . '/edit';
  }
  else {
    form_set_error('openlayers', t('Error trying to save style.'));
  }
}

/**
 * OpenLayers Form to Map
 *
 * Converst Form submission to map array.
 *
 * @param $values
 *   Array of values to convert
 * @param $clear_empty
 *   Boolean of whether empty values should be cleared
 * @return
 *   Array of form items
 */
function _openlayers_ui_convert_form_to_map($values = array(), $clear_empty = TRUE) {
  // If the form values are empty then we have nothing to return.
  if (empty($values)) {
    return array();
  }
  $processed = array();

  // Put projection in right place.
  $processed['projection'] = ($values['projections']['easy_projection'] != 'other') ? $values['projections']['easy_projection'] : $values['projections']['projection'];

  // Put the default layer in the right place.
  $processed['default_layer'] = $values['layers']['default_layer'];

  // Merge our different layer sections together
  $baselayers = array_filter($values['layers']['baselayers']);
  $overlays = array_filter($values['layers']['overlays']);
  $processed['layers'] = array_merge($baselayers, $overlays);

  // Take out form values that are no good
  $throw = array('op', 'submit', 'form_build_id', 'form_token', 'form_id', 'projections', 'layers', 'openlayers_save', 'preset_name', 'preset_title', 'preset_description', 'map_preview', 'openlayers_projection_ahah', 'openlayers_cancel', 'default_map');
  foreach ($values as $k => $v) {
    if (!in_array($k, $throw)) {
      $processed[$k] = $v;
    }
  }

  // Recursively unset any empty values
  if ($clear_empty) {
    $processed = _openlayers_ui_unset_empty_values($processed);
  }
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
function _openlayers_ui_convert_map_to_form($map = array()) {
  $processed = array();
  // Check input
  if (!is_array($map) || empty($map)) {
    return $processed;
  }
  $processed = $map;
  $layer_defs = openlayers_layers();

  // Manual changes
  $processed['layers'] = array();
  $processed['layers']['default_layer'] = $map['default_layer'];
  $processed['layers']['baselayers'] = array();
  $processed['layers']['overlays'] = array();

  // Run Image path through url()
  if ($processed['image_path']) {
    $processed['image_path'] = check_url($processed['image_path']);
  }

  // Set projection
  $processed['projections']['easy_projection'] = $processed['projection'];
  $processed['projections']['projection'] = $processed['projection'];

  // Get layers
  if (is_array($map['layers'])) {
    foreach ($map['layers'] as $layer_id => $layer) {
      if ($layer_defs[$layer_id]->data['baselayer']) {
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
function _openlayers_ui_get_projections($layers = array()) {
  $all_projections = array();
  $projection_layers = array();

  // Check $layers
  if (!is_array($layers)) {
    return $projection_layers;
  }

  // Go through layers
  foreach ($layers as $layer_key => $layer) {
    // Check projections
    if ($layer->data['projection']) {
      // Go through projections
      foreach ($layer->data['projection'] as $projection) {
        if (!array_key_exists($projection, $projection_layers)) {
          $projection_layers[$projection] = array();
        }
        $projection_layers[$projection][] = $layer_key;
      }
    }
  }

  // Add any layers that do not have a projection specified to all
  foreach ($layers as $layer_key => $layer) {
    // Check projections
    if (!$layer->data['projection']) {
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
 * Recursively unset empty values
 *
 * Go through an array recursively and unset empty strings and arrays
 *
 * @param $values
 *   Array
 * @return
 *   Array with empty values unset
 */
function _openlayers_ui_unset_empty_values($array) {
  foreach ($array as $key => $value) {
    // If it is an array then recursively check it
    if (is_array($value)) {
      $array[$key] = _openlayers_ui_unset_empty_values($value);
    }
    // If it is an array then check if it is empty. We don't use $value so that if it
    // is emptied by the previous check then it will still unset.
    if (is_array($array[$key])) {
      if (empty($array[$key])) {
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
function _openlayers_ui_form_center_map($defaults = array()) {
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
  $pass_values = array(
    'openlayersForm' => array(
      'projectionLayers' => _openlayers_ui_get_projections($layers),
    ),
  );
  drupal_add_js($pass_values, 'setting');
  // Render map
  return openlayers_render_map($centermap_def);
}

/**
 * Get Available Controls
 *
 * Builds an array of available controls for the form.
 *
 * @return
 *   Array of available controls
 */
function _openlayers_ui_available_controls() {
  $available = array();

  // Define array
  $available['Attribution'] = array(
    'title' => t('Attribution'),
    'description' => t('Allows layers to provide attribution to the map if it exists.'),
  );
  $available['KeyboardDefaults'] = array(
    'title' => t('Keyboard Defaults'),
    'description' => t('Provides a the ability to use the keyboard to pan and zoom map.'),
  );
  $available['LayerSwitcher'] = array(
    'title' => t('Layer Switcher'),
    'description' => t('Gives user ability to switch Layers in the map interface.'),
  );
  $available['MousePosition'] = array(
    'title' => t('Mouse Position'),
    'description' => t('Gives a visual indication of the mouse position to the user.'),
  );
  $available['Navigation'] = array(
    'title' => t('Navigation'),
    'description' => t('Gives the user the ability to navigate the map interface.'),
  );
  $available['PanZoomBar'] = array(
    'title' => t('Pan Zoom Bar'),
    'description' => t('Gives user ability to pan and zoom in the map interface.'),
  );
  $available['Permalink'] = array(
    'title' => t('Permanent Link'),
    'description' => t('Prvides a URL that will link to a specific map position.'),
  );
  $available['ScaleLine'] = array(
    'title' => t('Scale Line'),
    'description' => t('Provides the user with a line of scale in the map interface.'),
  );
  $available['ZoomBox'] = array(
    'title' => t('Zoom Box'),
    'description' => t('Allows user to draw a box on screen to zoom with Shift + Click.'),
  );
  $available['ZoomToMaxExtent'] = array(
    'title' => t('Zoom to Max Extent'),
    'description' => t('Provides button to zoom to the maximum extent of the map.'),
  );

  return $available;
}

/**
 * Merge maps from form and original preset
 *
 * Takes data from form and data from original map and merges
 * them together, taking into account any manual changes
 *
 * @param $submitted_map
 *   Map array from form that has been convertted
 * @param $orig_map
 *   Map array form the original map
 * @return
 *   Merged map array
 */
function _openlayers_ui_merge_maps($submitted_map = array(), $orig_map = array()) {
  $merged_map = array();

  // Check map arrays
  if (!is_array($submitted_map) || empty($submitted_map) || !is_array($orig_map) || empty($orig_map)) {
    return (is_array($submitted_map)) ? $submitted_map : array();
  }

  // Unset values in original map that can be altered by preset form
  unset($orig_map['preset_name']);
  unset($orig_map['preset_title']);
  unset($orig_map['preset_description']);
  
  // Any layer that is referenced by a string is an exposed / permanent layer and is visible to the UI.
  // We should therefore remove it from our $orig_map display since we will prefer selections from the UI.
  // Any layer that is an array will not have been exposed to the UI and therefore should be kept.
  if ($orig_map['layers']) {
    foreach ($orig_map['layers'] as $key => $layer) {
      if (is_string($layer)) {
        unset($orig_map['layers'][$key]);
      }
    }
  }

  // Merge maps.  The passed in submitted map has not had empty values removed.
  // This ensures that there is a subtractive merge
  $merged_map = openlayers_merge_maps($orig_map, $submitted_map);
  $merged_map = _openlayers_ui_unset_empty_values($merged_map);
  return $merged_map;
}

/**
 * Get behavior options.
 *
 * Gets form items for each behaviors.
 *
 * @param $type
 *   Type or scope of behaviors.  This will probably
 *   be map or layer
 * @param $defaults
 *   Array of defaults
 * @return
 *   Form array
 */
function _openlayers_ui_get_behavior_options($type = 'map', $defaults = array()) {
  $form = array();
  
  // Go through each behavior
  foreach (openlayers_behaviors() as $key => $plugin) {
    $class = ctools_plugin_get_class($plugin, 'behavior');
    if ($class) {
      // Build form.
      $form[$key] = array(
        '#tree' => TRUE,
        '#type' => 'fieldset',
        '#title' => $plugin['title'],
        '#description' => $plugin['description'],
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        'enabled' => array(
          '#type' => 'checkbox',
          '#title' => t('Enabled'),
          '#default_value' => isset($defaults['behaviors'][$key]),
        ),
      );

      $options = isset($defaults['behaviors'][$key]) ? $defaults['behaviors'][$key] : array();
      $behavior = new $class($options, $defaults);
      $form[$key]['options'] = $behavior->options_form();
    }
  }
  return $form;
}
