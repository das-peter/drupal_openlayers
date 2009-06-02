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
    
    // Get list of fields in this view
    $handlers = $this->display->handler->get_handlers('field');
    $fields = array();
    foreach ($handlers as $field_id => $handler){      
      $fields[$field_id] = $handler->definition['title'];
    }
    
    // Get a list of globally available geodata fields
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
    
    // Behaviors
    if (module_exists('openlayers_behaviors')){
      $form['behaviors'] = array(
        '#type' => 'fieldset',
        '#title' => t('Map Behaviors'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );
      
      $form['behaviors']['zoom_to_layer'] = array(
        '#type' => 'checkbox',
        '#title' => t('Automatically zoom to encompass views data (overrides map settings)'),
        '#default_value' => $this->options['behaviors']['zoom_to_layer'], 
      );
      $form['behaviors']['fullscreen'] = array(
        '#type' => 'checkbox',
        '#title' => t('Allow map to be viewed fullscreen'),
        '#default_value' => $this->options['behaviors']['fullscreen'], 
      );
      $tooltip_options = array_merge(array('0' => t('Do not use a tooltip')), $fields);
      $form['behaviors']['tooltip'] = array(
        '#type' => 'radios',
        '#title' => t('Select the field you would like to use as a tooltip'),
        '#options' => $tooltip_options,
        '#default_value' => $this->options['behaviors']['tooltip'], 
      );
    }
    
    // Theming
    $form['style'] = array(
        '#type' => 'fieldset',
        '#title' => t('Feature Styles'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
      
    $form['style']['snippet'] = array(
      '#type' => 'textarea',
      '#title' => t('Feature Styles function'),
      '#description' => t('Enter PHP code that returns a style array for each feature. $fields contains your defined fields, $row contains instances of those fields along with geometries. Array should be of the form \'styleProperty\' => \'styleValue\'. You may return false to use defaults. See documentation for available style Properties.'),
      '#default_value' => $this->options['style']['snippet'], 
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
    
    // Get list of fields in this view
    $handlers = $this->display->handler->get_handlers('field');
    $fields = array();
    foreach ($handlers as $field_id => $handler) {      
      $fields[$field_id] = $handler->definition;
      $fields[$field_id]['field_alias'] = $handler->field_alias;
    }
    
    // Clean read_geo of non-selected fields.
    $read_geo = array_values(array_filter($read_geo));
    
    // Build feature. We create one feature per field per row.
    foreach ($rows as $id => $row) {
      foreach ($read_geo as $geo_field) {
        if ($geo_field){
          // Set up feature      
          $feature = array(
            'attributes' => array(),
          );
          
          // Extract geometry / location information
          if ($geo_field == 'node_locations') {
             $wkt_string = 'POINT('.$row->openlayers_node_locations_lon.' '.$row->openlayers_node_locations_lat.')';
             $feature['wkt'] = $wkt_string;
             $feature['projection'] = '4326';
          }
          else {
            // It's a cck field
            if ($content_fields[$geo_field]['type'] == 'geo') {
              $wkt_field = $geo_field.'_wkt';
              $feature['wkt'] = $row->$wkt_field;
              $feature['projection'] = $content_fields[$geo_field]['srid'] ? $content_fields[$geo_field]['srid'] : '4326';
            }
            
            if ($content_fields[$geo_field]['type'] == 'location') {
              // @@TODO
            }
          }
          
          // Fill in all attributes
          foreach ($fields as $fid => $field) {
            $field_alias = $field['field_alias'];
            $feature['attributes'][$field_alias] = $row->$field_alias;
          }
          
          // Fill in tooltip attribute
          if ($this->options['behaviors']['tooltip']) {
            $tooltip_field = $this->options['behaviors']['tooltip'];
            $tooltip_field_alias = $fields[$tooltip_field]['field_alias'];
            // @@TODO: This needs to be themed. I don't know how.
            $feature['attributes']['openlayers_tooltip'] = $row->$tooltip_field_alias;
          }
          
          // Get feature styles
          if ($this->options['style']['snippet']) {
            $feature_style = eval($this->options['style']['snippet']);
            if (is_array($feature_style)){
              $feature['style'] = $feature_style;
            }
            else {
             //@@TODO: Error 
            }
          }
          
          // Push feature to features array
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
      
      // Set up behaviors
      $map['behaviors'] = array();
      
      if (module_exists('openlayers_behaviors')){
        // Set up tooltip behavior
        if ($this->options['behaviors']['tooltip']){
          $field_id = $this->view->display_handler->get_handler('field', $this->options['behaviors']['tooltip'])->field_alias;
          $map['behaviors']['openlayers_views_tooltip'] = array(
            'id' => 'openlayers_views_tooltip',
            'type' => 'openlayers_behaviors_tooltip',
            'layer' => 'openlayers_views_layer'. $this->view->name,
            'attribute' => 'openlayers_tooltip',
          );
        }
        if ($this->options['behaviors']['zoom_to_layer']){
          $map['behaviors']['openlayers_views_zoom_to_layer'] = array(
            'id' => 'openlayers_views_zoom_to_layer',
            'type' => 'openlayers_behaviors_zoom_to_layer',
            'layer' => 'openlayers_views_layer'. $this->view->name,
          );
        }
        if ($this->options['behaviors']['fullscreen']){
          $map['behaviors']['openlayers_views_fullscreen'] = array(
            'id' => 'openlayers_views_fullscreen',
            'type' => 'openlayers_behaviors_fullscreen'
          );
        }
      }
      // @@TODO Add settings from plugin options
      
      // Render map
      $map = openlayers_render_map($map);
      
      // Return map array
      $output .= theme($this->theme_functions(), $this->view, $this->options, $map, $title);
    }
    
    return $output;
  }
}