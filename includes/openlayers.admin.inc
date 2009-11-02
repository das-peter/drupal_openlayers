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
  $source_description = t('The source for the OpenLayers library can be one of two things:')
    .'<ul><li>'
    . t('URL: This means that the OpenLayers JS library is not 
    hosted on this site.  OpenLayers provides a hosted JS file.  
    By default the Open Layers module will use this, since the 
    JS file cannot be included with the module.  This is @ol_api_url.
    This may effect performance as it is not hosted on your site. 
    Also, depending on how the OpenLayers JS API changes, this module 
    may not be compatible with this version.', 
    array('@ol_api_url' => 'http://openlayers.org/api/OpenLayers.js'))
    .'</li><li>'
    . t('Drupal Path: This is a path relative to the Drupal base.  
    For instance, if you <a href="!ol_url">Download OpenLayers</a> 
    manually to the OpenLayers module folder and extract it, 
    you may use a value like: @suggested_path',
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
    '#description' => t('This is the default preset that will be used 
      in cases where one is not defined.  It will also be used as the default when creating new presets.'),
    '#options' => openlayers_preset_options(),
    '#default_value' => variable_get('openlayers_default_preset', 'default'),
  );

  // Make a system setting form and return
  return system_settings_form($form);
}

/**
 * Menu callback for Layers.
 */
function openlayers_ui_object_list($type) {
  $rows = array();

  switch ($type) {
    case 'styles':
      $objects = openlayers_styles(TRUE);
      break;
    case 'layers':
      $objects = openlayers_layers(TRUE);
      break;
    case 'presets':
      $objects = openlayers_presets(TRUE);
      break;
  }

  // Make table of presets and actions
  $header = array(t('Title'), t('Description'), t('Actions'));

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
 * Layer add/edit form.
 */
function openlayers_ui_layers_form(&$form_state, $layer = NULL, $edit = FALSE) {
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
 * Styles add/edit form.
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
 * Submit handler for layers.
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
 * Menu Callback for Add Preset
 */
function openlayers_ui_presets_form(&$form_state, $preset = NULL, $edit = FALSE) {
  openlayers_include();
  drupal_add_js(drupal_get_path('module', 'openlayers') .'/includes/openlayers.admin.js', 'module');
  drupal_add_css(drupal_get_path('module', 'openlayers') .'/includes/openlayers.admin.css');

  // If cloning or editing, attempt to get preset
  if (empty($preset)) {
    $default_preset = openlayers_preset_load(variable_get('openlayers_default_preset', 'default'));
    if ($default_preset) {
      $defaults = $default_preset->data;
    }
  }
  else {
    $defaults = $preset->data;
  }

  $form = array(
    '#tree' => TRUE,
    '#cache' => TRUE,
    'preset_edit' => array('#type' => 'value', '#value' => $edit),
    'default_map' => array('#type' => 'value', '#value' => $defaults),
  );

  // General information
  $form['info'] = array(
    '#title' => t('General information'),
    '#tree' => FALSE,
  );
  $form['info']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('This is the machine readable identifier.
      This should be all lowercase characters, numbers, or underscores (_).'),
    '#maxlength' => 255,
    '#default_value' => !empty($preset->name) ? $preset->name : '',
    '#disabled' => $edit,
  );
  if ($edit) {
    $form['info']['name']['#value'] = $preset->name;
  }
  $form['info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('This is the descriptive title of the preset and will show up most often in the interface.'),
    '#maxlength' => 255,
    '#default_value' => !empty($preset->title) ? $preset->title : '',
  );
  $form['info']['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Preset Description'),
    '#description' => t('This is full description of the preset and is mostly used on the preset overview list page.'),
    '#default_value' => !empty($preset->description) ? $preset->description : '',
  );
  $form['info']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#description' => t('A CSS width value.'),
    '#default_value' => !empty($defaults['width']) ? $defaults['width'] : '',
    '#maxlength' => 128,
  );
  $form['info']['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#description' => t('A CSS height value.'),
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

  // Center
  $form['center'] = array(
    '#title' => t('Center & Bounds'),
    '#description' => t('Where the map will center itself initially. Shift-drag on the map to set the restrictedExtent.'),
    '#tree' => TRUE,
  );
  $form['center']['helpmap'] = array(
    '#value' => '<div class="form-item openlayers-center-helpmap" 
      style="display:block">'. openlayers_ui_presets_form_center_map($defaults) .'</div>'
  );
  $form['center']['initial'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Initial Map View')
  );
  $form['center']['initial']['centerpoint'] = array(
    '#type' => 'textfield',
    '#title' => t('Centerpoint'),
    '#description' => t('Coordinates that are the intial focus of the map'),
    '#default_value' => $defaults['center']['initial']['centerpoint'],
    '#attributes' => array('class' => 'openlayers-form-centerpoint'),
    '#size' => 25,
  );
  $form['center']['initial']['zoom'] = array(
    '#type' => 'textfield',
    '#title' => t('Zoom Level'),
    '#description' => t('Initial Zoom Level when the map intially displays'),
    '#default_value' => $defaults['center']['initial']['zoom'],
    '#attributes' => array('class' => 'openlayers-form-zoom'),
    '#size' => 25,
  );
  

  $form['center']['restrict'] = array(
    '#type' => 'fieldset',
    '#title' => t('Restrict Extent')
  );
  $form['center']['restrict']['restrictextent'] = array(
    '#type' => 'checkbox',
    '#title' => t('Restrict Extent'),
    '#default_value' => $defaults['center']['restrict']['restrictextent'],
  );
  $form['center']['restrict']['restrictedExtent'] = array(
    '#type' => 'textfield',
    '#title' => t('Restricted Extent'),
    '#description' => t('Prevents users from panning outside of a specific bounding box'),
    '#default_value' => $defaults['center']['restrict']['restrictedExtent'],
    '#attributes' => array('class' => 'openlayers-form-restrictedExtent'), 
    '#size' => 25,
  );

  // Behaviors
  $form['behaviors'] = array(
    '#title' => t('Behaviors'),
    '#description' => t('Configure interactive map behaviors.'),
    '#tree' => TRUE,
  );
  $form['behaviors'] = $form['behaviors'] + openlayers_ui_get_behavior_options('map', $defaults);

  // Layers & styles
  $form['layerstyles'] = array(
    '#title' => t('Layers & Styles'),
    '#description' => t('Layer settings.  The Layer options will change based on the projection chosen.'),
    '#theme' => 'openlayers_ui_presets_form_layers',
    '#tree' => FALSE,
  );

  // Start AHAH Wrapper
  $form['layerstyles']['ahah-start'] = array('#value' => '<div id="openlayers-layers-select">');

  // Projections

  // Grab default from submitted form values on AHAH rebuild.
  if (isset($form_state['values']['projections'])) {
    if ($form_state['values']['projections']['easy_projection'] == 'other') {
      $defaults['projection'] = $form_state['values']['projections']['projection'];
    }
    else {
      $defaults['projection'] = $form_state['values']['projections']['easy_projection'];
    }
  }

  // Projection options
  $projections = array();
  foreach (openlayers_ui_get_projection_options() as $projection) {
    $projection_layers = openlayers_ui_get_layer_options('baselayer', $projection);
    $projections[$projection] = theme('openlayers_ui_form_projection_description', $projection, array_keys($projection_layers));
  }
  $projections['other'] = t("Other");

  $form['layerstyles']['projections'] = $base_fieldset;
  $form['layerstyles']['projections']['#collapsible'] = FALSE;
  $form['layerstyles']['projections']['#tree'] = TRUE;

  $form['layerstyles']['projections']['#title'] = t('Projection');
  $form['layerstyles']['projections']['#description'] = t('Select the EPSG code of the !link_proj for your map. 
    The list next to each projection is the layers that support this projection.', array(
    '!link_proj' => l('geographical projection', 'http://en.wikipedia.org/wiki/Map_projection'),
  ));
  $form['layerstyles']['projections']['easy_projection'] = array(
    '#type' => 'radios',
    '#title' => t('Map Projection'),
    '#description' => t('The !link_proj of this map: all layers will either be requested or reprojected to this format.', array(
      '!link_proj' => l('geographical projection', 'http://en.wikipedia.org/wiki/Map_projection'),
    )),
    '#default_value' => $defaults['projection'],
    '#options' => $projections,
    '#attributes' => array('class' => 'openlayers-form-easy-projection'),
    '#ahah' => array(
      'path' => 'openlayers/ahah/preset',
      'wrapper' => 'openlayers-layers-select',
      'event' => 'change',
      'method' => 'replace',
    ),
  );
  $form['layerstyles']['projections']['projection'] = array(
    '#type' => 'textfield',
    '#attributes' => array('class' => 'openlayers-form-projection'),
    '#default_value' => $defaults['projection'],
    '#maxlength' => 16,
  );

  // Map options properties
  $form['layerstyles']['projections']['displayProjection'] = array(
    '#type' => 'textfield',
    '#title' => t('Display Projection'),
    '#description' => t('All interaction with the map - drawing, panning, centering, and more - occurs in the display projection. The vast majority of maps use 4326 (latitude/longitude) for this value.'),
    '#default_value' => !empty($defaults['layerstyles']['projections']['displayProjection']) ? $defaults['layerstyles']['projections']['displayProjection'] : '4326',
    '#maxlength' => 6
  );

  /* Base layers */
  $form['layerstyles']['layers']['#tree'] = TRUE;
  $form['layerstyles']['layers']['baselabels'] = array();
  $base_options = openlayers_ui_get_layer_options('baselayer', $defaults['projection']);
  if (!empty($base_options)) {
    foreach ($base_options as $id => $description) {
      $form['layerstyles']['layers']['baselabels'][$id] = array('#type' => 'markup', '#value' => $description);
    }
  }
  $form['layerstyles']['layers']['baselayers'] = array(
    '#type' => 'checkboxes',
    '#options' => $base_options,
    '#default_value' => !empty($defaults['layers']) ? array_intersect_key($defaults['layers'], $base_options) : array(),
  );
  $form['layerstyles']['layers']['default_layer'] = array(
    '#type' => 'radios',
    '#options' => $base_options,
    '#default_value' => !empty($defaults['default_layer']) && isset($base_options[$defaults['default_layer']]) ? $defaults['default_layer'] : NULL,
  );

  /* Overlay layers */
  $overlay_options = openlayers_ui_get_layer_options('overlay', $defaults['projection']);
  $form['layerstyles']['layers']['overlaylabels'] = array();
  if (!empty($overlay_options)) {
    foreach ($overlay_options as $id => $description) {
      $form['layerstyles']['layers']['overlaylabels'][$id] = array('#type' => 'markup', '#value' => $description);
      $form['layerstyles']['layer_styles']['#tree'] = TRUE;
      $form['layerstyles']['layer_styles'][$id] = array(
        '#type' => 'select',
        '#options' => array('-- '. t('Default style') .' --') + openlayers_ui_get_style_options(),
        '#default_value' => !empty($defaults['layer_styles'][$id]) ? $defaults['layer_styles'][$id] : '',
      );
    }
  }
  $form['layerstyles']['layers']['overlays'] = array(
    '#type' => 'checkboxes',
    '#options' => $overlay_options,
    '#default_value' => !empty($defaults['layers']) ? array_intersect_key($defaults['layers'], $overlay_options) : array(),
  );
  $form['layerstyles']['layer_activated'] = array(
    '#type' => 'checkboxes',
    '#options' => $overlay_options,
    '#default_value' => !empty($defaults['layer_activated']) ? array_intersect_key($defaults['layer_activated'], $overlay_options) : array(),
  );

  

  /* Styles */
  $form['layerstyles']['styles'] = array('#tree' => TRUE);
  $form['layerstyles']['styles']['default'] = array(
    '#type' => 'select',
    '#title' => t('Default style'),
    '#description' => t('Default style for features in a vector.'),
    '#options' => openlayers_ui_get_style_options(),
    '#default_value' => !empty($defaults['styles']['default']) ? $defaults['styles']['default'] : NULL,
  );
  $form['layerstyles']['styles']['select'] = array(
    '#type' => 'select',
    '#title' => t('Select style'),
    '#description' => t('Style for features in a vector that are selected.'),
    '#options' => openlayers_ui_get_style_options(),
    '#default_value' => !empty($defaults['styles']['select']) ? $defaults['styles']['select'] : NULL,
  );
  $form['layerstyles']['styles']['temporary'] = array(
    '#type' => 'select',
    '#title' => t('Temporary Style'),
    '#description' => t('Default style for any temporary features in a vector. 
      This will also be used for rollovers for things like Tooltips.'),
    '#options' => openlayers_ui_get_style_options(),
    '#default_value' => !empty($defaults['styles']['temporary']) ? $defaults['styles']['temporary'] : NULL,
  );


  // End AHAH Wrapper
  $form['layerstyles']['ahah-end'] = array('#value' => '</div>');

  // Save button
  $form['buttons'] = array('#tree' => FALSE);
  $form['buttons']['openlayers_save'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );
  // Cancel button
  $form['buttons']['openlayers_cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel')
  );

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
  if (empty($values['name'])) {
    form_set_error('name', t('Preset name is required.'));
    $found_error = TRUE;
  }
  if (empty($values['title'])) {
    form_set_error('title', t('Preset title is required.'));
    $found_error = TRUE;
  }
  if (empty($values['description'])) {
    form_set_error('description', t('Preset description is required.'));
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
  if (!preg_match('!^[a-z0-9_]+$!', $values['name'])) {
    form_set_error('name', t('Preset Name must contain only lowercase letters, numbers, and underscores.'));
    $found_error = TRUE;
  }

  // Check if adding and name already exists
  $existing = openlayers_preset_load($values['name'], TRUE);
  if (!empty($existing) && (!$form_state['values']['preset_edit']) && ($existing->get_type & EXPORT_IN_DATABASE)) {
    form_set_error('name', t('The Preset Name already exists.'));
    $found_error = TRUE;
  }

  // Attempt to render map to find any errors
  $map = openlayers_ui_presets_form_process($form_state['values']);
  $map = openlayers_build_map($map);
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
function openlayers_ui_presets_add_projection_submit($form, &$form_state) {
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
    $map = openlayers_ui_presets_form_process($form_state['values']);

    // Save preset
    $preset = new stdClass();
    $preset->name = $form_state['values']['name'];
    $preset->title = $form_state['values']['title'];
    $preset->description = $form_state['values']['description'];
    $preset->data = $map;
    $success = openlayers_preset_save($preset);

    // Redirect to edit page
    if ($success) {
      drupal_set_message(t('Map saved.'));
      $form_state['redirect'] = "admin/settings/openlayers/presets/{$preset->name}/edit";
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

  // Rebuild form and remove any submit handlers
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);

  // Unset wrapper and create output
  $output = theme('status_messages') . drupal_render($form['layerstyles']);

  // Final rendering callback.
  drupal_json(array('status' => TRUE, 'data' => $output));
}

/**
 * Process form submission into a map array.
 *
 * @param $values
 *   Array of values to process.
 * @return
 *   Map data array.
 */
function openlayers_ui_presets_form_process($values = array()) {
  // Valid keys that we will cherry-pick from the form values.
  $keys = array(
    'width',
    'height',
    'image_path',
    'css_path',
    'center',
    'behaviors',
    'layers',
    'layer_styles',
    'layer_activated',
    'projections',
    'styles',
    'options',
  );

  $processed = array();
  foreach ($keys as $key) {
    switch ($key) {
      case 'behaviors':
        $processed['behaviors'] = array();
        foreach ($values['behaviors'] as $behavior => $settings) {
          if ($settings['enabled']) {
            $processed['behaviors'][$behavior] = isset($settings['options']) ? 
              $settings['options'] : 
              array();
          }
        }
        break;
      case 'projections':
        $processed['projection'] = ($values['projections']['easy_projection'] != 'other') ? 
          $values['projections']['easy_projection'] : 
          $values['projections']['projection'];
        $processed['displayProjection'] = $values['projections']['displayProjection'];
        break;
      case 'layers':
        // Put the default layer in the right place.
        $processed['default_layer'] = $values['layers']['default_layer'];

        // Merge our different layer sections together
        $baselayers = array_filter($values['layers']['baselayers']);
        $overlays = array_filter($values['layers']['overlays']);
        $processed['layers'] = array_merge($baselayers, $overlays);
        break;
      default:
        $processed[$key] = is_array($values[$key]) ? array_filter($values[$key]) : $values[$key];
        break;
    }
  }

  // Ensure these values are arrays
  $ensure_array = array('behaviors', 'layers', 'layer_styles', 'styles');
  foreach ($ensure_array as $key) {
    if (empty($processed[$key])) {
      $processed[$key] = array();
    }
  }

  return $processed;
}

/**
 * Get behavior options.
 */
function openlayers_ui_get_behavior_options($type, $defaults) {
  $form = array();
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

/**
 * Get layer options.
 */
function openlayers_ui_get_layer_options($type = 'baselayer', $projection = NULL) {
  $options = array();
      
  foreach (openlayers_layers() as $key => $layer) {
    if (!isset($projection) || (in_array($projection, $layer->data['projection']))) {
      if ($type == 'baselayer' && $layer->data['baselayer']) {
        $options[$key] = theme('openlayers_ui_form_layer_description', $layer->name, $layer->description);
      }
      else if ($type != 'baselayer' && empty($layer->data['baselayer'])) {
        $options[$key] = theme('openlayers_ui_form_layer_description', $layer->name, $layer->description);
      }
    }
  }
  return $options;
}

/**
 * Get projection options.
 *
 * @return
 *   Array of projection options suitable for use in a FormAPI element.
 */
function openlayers_ui_get_projection_options() {
  $options = array();
  foreach (openlayers_layers() as $key => $layer) {
    foreach ($layer->data['projection'] as $projection) {
      $options[$projection] = $projection;
    }
  }
  return $options;
}

/**
 * Get style options.
 *
 * @return
 *   Array of style options suitable for use in a FormAPI element.
 */
function openlayers_ui_get_style_options() {
  $options = array();
  foreach (openlayers_styles() as $key => $style) {
    $options[$key] = $style->name;
  }
  return $options;
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
function openlayers_ui_presets_form_center_map($defaults = array()) {
  // Pass variables etc. to javascript
  $pass_values = array(
    'openlayersForm' => array(
      'projectionLayers' => openlayers_ui_get_projection_options(),
    ),
  );
  drupal_add_js($pass_values, 'setting');

  // Set up our map to help set center lat, lon and zoom
  // This map will always be projected as 4326 and use just the basic layer so that
  // even if the user is using screwed up map settings, this map will still function.
  $centermap_def = array(
    'id' => 'openlayers-center-helpmap',
    'projection' => '4326',
    'default_layer' => 'openlayers_default_wms',
    'width' => '500px',
    'height' => '300px',
    'center' => array(
      'lat' => ($defaults['center']['lat']) ? $defaults['center']['lat'] : 0,
      'lon' => ($defaults['center']['lon']) ? $defaults['center']['lon'] : 0,
      'zoom' => ($defaults['center']['zoom']) ? $defaults['center']['zoom'] : 2,
    ),
    'layers' => array(
      'openlayers_default_wms',
    ),
    'behaviors' => array(
      'openlayers_behavior_panzoombar' => array(),
      'openlayers_behavior_dragpan' => array(),
      'openlayers_behavior_mapformvalues' => array(),
      'openlayers_behavior_boxselect' => array(),
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
  );
  return openlayers_render_map($centermap_def);
}
