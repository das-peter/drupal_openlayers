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
    
    $read_geo_options = array();
    
    if (module_exists('content')){
      // Get all fields.
      $content_fields = content_fields();
      
      foreach ($content_fields as $field){
        if ($field['type'] == 'geo' || $field['type'] == 'location'){
          $read_geo_options[$field['field_name']] = $field['widget']['label'];
        }
      }
    }
    
    if (module_exists('location_node')){
      $read_geo_options['node_locations'] = "Node Locations";
    }
    
    if (empty($read_geo_options)){
      
      $form['error_markup'] = array(
        '#value' => t('You need at least one geo or location field before you can configure your field settings'),
        '#prefix' => '<div class="error form-item description">',
        '#suffix' => '</div>',
      );
      
      parent::options_form($form, $form_state);
      return; 
    }
    
    // Read Geo Data
    $form['read_geo'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Which fields would you like to extract geo data from?'),
      '#options' => $read_geo_options,
      '#default_value' => $this->options['read_geo'], 
    );
    
  }
  
  /**
   * Options form submit
   */
  function options_submit($form, &$form_state) {
    // @@TODO: ??
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
    $features = array();
    $content_fields = content_fields();
    $read_geo = $this->options['read_geo'];
    
    // Clean read_geo of non-selected fields.
    $read_geo = array_values(array_filter($read_geo));
    
    // Build feature. We create one feature per field per row.
    foreach ($rows as $id => $row) {
      foreach ($read_geo as $geo_field){
        if ($geo_field){
          
         // Set up feature      
         $feature = array(
           'attributes' => array(),
         );
          
         // Extract geometry / location information
         if ($geo_field == 'node_locations'){
            $wkt_string = 'POINT('.$row->openlayers_node_locations_lon.' '.$row->openlayers_node_locations_lat.')';
            $feature['wkt'] = $wkt_string;
            $feature['projection'] = '4326';
          }
          else{
            // It's a cck field
            if ($content_fields[$geo_field]['type'] == 'geo'){
              $wkt_field = $geo_field.'_wkt';
              $feature['wkt'] = $row->$wkt_field;
              $feature['projection'] = $content_fields[$geo_field]['srid'] ? $content_fields[$geo_field]['srid'] : '4326';
            }
            
            if ($content_fields[$geo_field]['type'] == 'location'){
              // @@TODO
            }
          }
          
          // Fill in all attributes
          foreach ($row as $fid => $field){
            $feature['attributes'][$fid] = $field;
          }
          
          $features[] = $feature;
          
        }
      }
      
    }
    
    return $features;
  }
  
  function query() {
    $read_geo = $this->options['read_geo'];
    
    // Get all fields.
    $content_fields = content_fields();
    
    // Load data from Node Locations
    if ($read_geo['node_locations']) {
      $table = $this->view->query->ensure_table('location');
      $this->view->query->add_field($table, 'latitude', 'openlayers_node_locations_lat');
      $this->view->query->add_field($table, 'longitude', 'openlayers_node_locations_lon');
    }
    
    // Load data from cck fields
    foreach ($content_fields as $content_field){
      if ($read_geo[$content_field['field_name']]){
        $field_name = $content_field['field_name'];
        $content_table = $this->view->query->ensure_table('node_data_'.$field_name);
        if ($content_field['type'] == 'geo'){
          $this->view->query->add_field($wkt_table, $field_name.'_wkt');
        }
        if ($content_field['type'] == 'location'){
          // @@TODO: I don't know how to handle this.
        }
      }
    }
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
      
      // @@TODO: Reduce and sort duplicates
      
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
      
      // @@TODO Add settings from plugin options
      
      // Render map
      $map = openlayers_render_map($map);
      
      // Return map array
      $output .= theme($this->theme_functions(), $this->view, $this->options, $map, $title);
    }
    
    return $output;
  }
}