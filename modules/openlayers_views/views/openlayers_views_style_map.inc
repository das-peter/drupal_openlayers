<?php
// $Id$

/**
 * @file
 * This file holds style plugin for OpenLayers Views
 *
 * @ingroup openlayers
 */

/**
 * @class
 */
class openlayers_views_style_map extends views_plugin_style {
  
  /**
   * Set default options
   */
  function option_definition() {
    // Get parent options
    $options = parent::option_definition();
    
    return $options;
  }
   
  /**
   * Options form
   */
  function options_form(&$form, &$form_state) {
    
    // @@TODO: Include Map settings form
    
    // Check for fields
    $handlers = $this->display->handler->get_handlers('field');
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#value' => t('You need at least one field before you can configure your field settings'),
        '#prefix' => '<div class="error form-item description">',
        '#suffix' => '</div>',
      );
      
      // Get parent form
      parent::options_form($form, $form_state);
      return;
    }
    
    // Read Geo Data
    $form['read_geo'] = array(
      '#type' => 'checkbox',
      '#title' => t('Read Geo Data'),
      '#description' => t('If this is checked, the map will attempt to read any geo fields included in the view.'),
      '#default_value' => $this->options['read_geo'], 
    );
    
    // Create the custom field options.
    /*
    // Get field names
    $field_names[$field] = array('' => '--');
    foreach ($handlers as $field => $handler) {
      if ($label = $handler->label()) {
        $field_names[$field] = $label;
      }
      else {
        $field_names[$field] = $handler->ui_name();
      }
    }
    // Define what options are for the fields
    $field_options = array(
      'title' => t('Title'),
      'latitude' => t('Latitude'),
      'longitude' => t('Longitude'),
      'class' => t('Class'),
    );
    $form['custom_fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Custom Fields'),
      '#description' => t('Select the fields that contain the latitude, longitude and title of each point. If selected, the class field will be used to apply a class to each point. Remaining fields will be available in the hidden "content" region of the point.'),
    );
    // Create a field association form item
    foreach ($field_options as $k => $v) {
      $form['custom_fields'][$k] = array(
        '#type' => 'select',
        '#title' => $v,
        '#options' => $field_names,
        '#default_value' => $this->options['fields'][$k],
        '#required' => ($k == 'class' ? FALSE : TRUE),
      );
    }
    */
  }
  
  /**
   * Options form submit
   */
  function options_submit($form, &$form_state) {
    // TODO: ??
  }
   
  /**
   * Options form validate
   */
  function validate() {
    $errors = array();
    // TODO: ??
    return $errors;
  }
     
  /**
   * Map features
   */
  function map_features($rows = array()) {
    // @@TODO: If we have multiple geometries per row, create a multi-geometry feaure. This will likely take some work in the Vector layer definition.
    
    $features = array();
    $wkb_fields = array();
    
    // Check if views want to read geo data
    if ($this->options['read_geo']) {
      // Look for wkb fields
      foreach ($rows as $id => $row) {
        foreach ($row as $fid => $field) {
          if (substr($fid, -4) == '_wkb') {
            if (!in_array($fid, $wkb_fields)){
              $wkb_fields[] = $fid;
            }
          }
        }
      }
      // Check if any fields found, include files
      if (count($wkb_fields) > 0) {
        module_load_include('inc', 'geo', 'includes/geo.wkb');
      }
    }
    
    // Build feature
    foreach ($rows as $id => $row) {
      
      // Set up feature      
      $feature = array(
        'attributes' => array(),
      );
      
      // Check to see if read geo data
      $num_wkb_fields = count($wkb_fields);
      if ($num_wkb_fields > 1) $feature['wkt'] = array();
      if ($this->options['read_geo'] && ($num_wkb_fields > 0)) {
        // Go through fields and create a feature for each geo field of each row
        foreach ($wkb_fields as $wkb_field) {
          // Read WKB format
          // NOTE: The following geo function is not possible without including the file above
          
          // If there is anything in the wkb field then read it and populate the wkt value of the feature
          if ($row->$wkb_field){
            // Extract wkt from wkb
            $wkb_data = geo('wkb_get_data', $row->$wkb_field, 'wkt');
            
            // Populate wkt value
            $feature['wkt'] = $wkb_data['value'];
            
            // Go through fields
            foreach ($this->view->field as $key => $field) {
              if ($key == $this->options['fields']['title']) {
                $feature['attributes']['name'] = $field->theme($row);
              }
              elseif ($key == $this->options['fields']['latitude']) {
                $feature['lat'] = $field->theme($row);
              }
              elseif ($key == $this->options['fields']['longitude']) {
                $feature['lon'] = $field->theme($row);
              }
              elseif ($key == $this->options['fields']['class']) {
                $feature['attributes']['class'] = strip_tags(strtolower($field->theme($row)));
              }
              else {
                // Add all other field data to the attribute table.
                $feature['attributes'][$key] = $field->theme($row);
              }
            }
            
            $features[] = $feature;
          }
        }
      }
    }
    
    var_dump($features);
    
    return $features;
  }
  
  /**
   * Renders views (map)
   */
  function render() {
    
    // Check for live preview.
    if (isset($this->view->live_preview) && $this->view->live_preview) {
      return t('OpenLayers views are not compatible with live preview.');
    }
    
    // Check row plugin if using it.
    if ($this->uses_row_plugin() && empty($this->row_plugin)) {
      vpr('views_plugin_style_default: Missing row plugin');
      return;
    }

    // Group the rows according to the grouping field, if specified.
    $sets = $this->render_grouping($this->view->result, $this->options['grouping']);
    
    // Render each group separately and concatenate.  Plugins may override this
    // method if they wish some other way of handling grouping.
    $output = '';
    foreach ($sets as $title => $records) {
    
      // Get rows
      if ($this->uses_row_plugin()) {
        $rows = array();
        foreach ($records as $label => $row) {
          $rows[] = $this->row_plugin->render($row);
        }
      }
      else {
        $rows = $records;
      }
      
      // Define map array
      $map = array();
      
      // Define ID
      $map['id'] = OPENLAYERS_VIEWS_MAP_ID_PREFIX .'-'. $this->view->name;
      
      // Get features
      $features = $this->map_features($rows);
      
      // Define a layer for the features
      $map['layers'] = array(
        'openlayers_views_layer'. $this->view->name => array(
          'id' => 'openlayers_views_layer_'. $this->view->name,
          'type' => 'Vector',
          'name' => $this->display->display_title,
          'options' => array(),
          'events' => array(),
          'features' => $features,
        ),
      );
      
      // Add settings from plugin options
      // @@TODO;
      
      // Render map
      $map = openlayers_render_map($map);
      
      // Return map array
      $output .= theme($this->theme_functions(), $this->view, $this->options, $map, $title);
    }
    
    return $output;
  }
}