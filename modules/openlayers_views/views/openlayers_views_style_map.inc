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
 * Extension of the Views Plugin Syle for OpenLayers
 *
 * This class extended the default views plugin class to provide
 * a style plugin for the Open Layers module.
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
    $fields = array();
    $geo_field_options = array();
    $location_field_options = array();
    $data_source_options = array();
    
    // Get list of fields in this view & flag available geodata fields
    $handlers = $this->display->handler->get_handlers('field');
    
    // Check for any fields, as the view needs them
    if (empty($handlers)){
      $form['error_markup'] = array(
        '#value' => t('You need to enable at least one field before you can configure your field settings'),
        '#prefix' => '<div class="error form-item description">',
        '#suffix' => '</div>',
      );
      
      parent::options_form($form, $form_state);
      return; 
    }

    // Go through fields
    foreach ($handlers as $field_id => $handler) {
      // Collect fields per types
      switch ($handler->content_field['type']) {
        case 'geo':
          $geo_field_options[$handler->content_field['field_name']] = $handler->content_field['widget']['label'];
          break;
          
        case 'location':
          $location_field_options[$handler->content_field['field_name']] = $handler->content_field['widget']['label'];
          break;
          
        default:
          $fields[$field_id] = $handler->definition['title'];
          break;
          
      }
    }
        
    // Check Geo fields found
    if (count($geo_field_options) > 0){
      $data_source_options['geo'] = t('Geo Module');
    }
    // Check Location fields found
    if (count($location_field_options) > 0) {
      $data_source_options['location'] = t('Location CCK Fields');
    }
    // Check Node Location found
    if (module_exists('location_node')){
      $data_source_options['node_locations'] = t('Node Locations');
    }
    // Default data source
    $data_source_options['other_latlon'] = t('Other: Lat/Lon Point');
    $data_source_options['other_wkt'] = t('Other: Well Known Text');
        
    // Data Source options
    $form['data_source'] = array(
      '#type' => 'fieldset',
      '#tree' => TRUE,
      '#title' => t('Data Source'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['data_source']['value'] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#title' => t('Map Data Sources'),
      '#description' => t('Choose which sources of data that the map will provide features for.'),
      '#options' => $data_source_options,
      '#default_value' => $this->options['data_source']['value'], 
    );
    // Geo Data source options
    if ($data_source_options['geo']) {
      $form['data_source']['geo_fields'] = array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#title' => t('Geo Module Fields'),
        '#description' => t('Choose the fields provide by the Geo Module that will be used for feature data.'),
        '#options' => $geo_field_options,
        '#default_value' => $this->options['data_source']['geo_fields'],
        '#process' => array('views_process_dependency'),
        '#dependency' => array('edit-style-options-data-source-value' => array('geo')),
      );
    }
    // Location data source options
    if ($data_source_options['location']){
      $form['data_source']['location_fields'] = array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#title' => t('Location Fields'),
        '#description' => t('Choose the fields provided by the Location module that will be used for feature data.'),
        '#options' => $location_field_options,
        '#default_value' => $this->options['data_source']['location_fields'],
        '#process' => array('views_process_dependency'),
        '#dependency' => array('edit-style-options-data-source-value' => array('location')),
      );
    }
    // Other Lat and Lon data sources
    if (count($fields > 0)) {
      $form['data_source']['other_lat'] = array(
        '#type' => 'select',
        '#title' => t('Latitude Field'),
        '#description' => t('Choose a field for Latitude.  This should be a field that is a decimal or float value.'),
        '#options' => $fields,
        '#default_value' => $this->options['data_source']['other_lat'],
        '#process' => array('views_process_dependency'),
        '#dependency' => array('edit-style-options-data-source-value' => array('other_latlon')),
      );
      $form['data_source']['other_lon'] = array(
        '#type' => 'select',
        '#title' => t('Longitude Field'),
        '#description' => t('Choose a field for Longitude.  This should be a field that is a decimal or float value.'),
        '#options' => $fields,
        '#default_value' => $this->options['data_source']['other_lon'],
        '#process' => array('views_process_dependency'),
        '#dependency' => array('edit-style-options-data-source-value' => array('other_latlon')),
      );
    }
    // Other Well Known Text
    if (count($fields > 0)) {
      $form['data_source']['other_wkt'] = array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#title' => t('WKT Field'),
        '#description' => t('Choose the fields for Well Known Text data.'),
        '#options' => $fields,
        '#default_value' => $this->options['data_source']['other_wkt'],
        '#process' => array('views_process_dependency'),
        '#dependency' => array('edit-style-options-data-source-value' => array('other_wkt')),
      );
    }
    
    // Map Preset
    $form['presets'] = array(
      '#type' => 'fieldset',
      '#title' => t('Map Presets'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['presets']['map_preset'] = array(
      '#type' => 'select',
      '#title' => t('Map Preset'),
      '#description' => t('This is map that will be used to render the view.'),
      '#options' => openlayers_get_presets(),
      '#default_value' => variable_get('openlayers_default_preset', 'default'),
    );
    
    // Behavior options
    if (module_exists('openlayers_behaviors')){
      $form['behaviors'] = array(
        '#type' => 'fieldset',
        '#title' => t('Map Behaviors Options'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );
      $form['behaviors']['zoom_to_layer'] = array(
        '#type' => 'checkbox',
        '#title' => t('Zoom to Features'),
        '#description' => t('Automatically zoom to encompass views data (overrides map settings)'),
        '#default_value' => $this->options['behaviors']['zoom_to_layer'], 
      );
      $form['behaviors']['fullscreen'] = array(
        '#type' => 'checkbox',
        '#title' => t('Fullscreen'),
        '#description' => t('Allow map to be viewed fullscreen'),
        '#default_value' => $this->options['behaviors']['fullscreen'], 
      );
      // Tooltip options if fields
      if (count($fields) > 0) {
        $tooltip_options = array_merge(array('0' => t('Do not use a tooltip')), $fields);
        $form['behaviors']['tooltip'] = array(
          '#type' => 'select',
          '#title' => t('Tooltip Field'),
          '#title' => t('Select the field you would like to use as a tooltip'),
          '#options' => $tooltip_options,
          '#default_value' => $this->options['behaviors']['tooltip'], 
        );
      }
    }
    
    // Variable Styles
    $form['style'] = array(
        '#type' => 'fieldset',
        '#title' => t('Feature Styles'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
    );
    $form['style']['enable_styling'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable Variable Styling'),
      '#description' => t('This will enable the view to run the features through the theming styles functions to determine each feature\'s style.  This allows for variable styling, such as changing the color based on another field in the view.  See the OpenLayers theming documentation for details.'),
      '#default_value' => $this->options['style']['enable_styling'],
    );
  }
     
  /**
   * Map features
   */
  function map_features($rows = array()) {  
    $features = array();    
    $data_source = $this->options['data_source'];
            
    // Get list of fields in this view
    $handlers = $this->display->handler->get_handlers('field');
    $fields = array();
    foreach ($handlers as $field_id => $handler) {      
      $fields[$field_id] = $handler->definition;
      $fields[$field_id]['field_alias'] = $handler->field_alias;
    }
          
    // Build feature. We create one feature per field per row.
    foreach ($rows as $id => $row) {
      // Go through data sources
      // In theory, there could be multiple features per row.
      // TODO: allow for multiple features per row
      foreach ($data_source['value'] as $data_source_value) {
        switch ($data_source_value) {
          case 'node_locations':
            // TODO: These fields are provided only if the fields are chosen in the interface.
            $wkt_string = 'POINT(' . $row->location_longitude . ' ' . $row->location_latitude . ')';
            $feature['wkt'] = $wkt_string;
            $feature['projection'] = '4326';
            break;
            
          case 'geo':
            foreach ($data_source['geo_fields'] as $geo_field) {            
              $wkt_field = $geo_field.'_wkt';
              
              if ($row->$wkt_field) {
                $feature['wkt'] = $row->$wkt_field;
                $feature['projection'] ='4326';
              }
            }
            break;
            
          case 'location':
            // @@TODO
            break;
            
          case 'other_latlon':   
            $lon = $row->$fields[$data_source['other_lon']]['field_alias'];
            $lat = $row->$fields[$data_source['other_lat']]['field_alias'];
            
            if ($lat && $lon) {
              $feature['wkt'] = 'POINT('.$lon.' '.$lat.')';
              $feature['projection'] = '4326';
            }
            break;
            
          case 'other_wkt':
            // Go through selected field
            foreach ($data_source['other_wkt'] as $wkt_field) {
              $feature['wkt'] = $row->$fields[$wkt_field]['field_alias'];
              $feature['projection'] ='4326';
            }
            break;
            
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
      
      // Check for varable styling
      if ($this->options['style']['enable_styling']) {
        $feature_style = theme('openlayers_views_feature_style', $this, $row);
        if (is_array($feature_style) && !empty($feature_style)) {
          $feature['style'] = $feature_style;
        }
      }
      
      // Only add features with WKT data
      if ($feature['wkt']) {
        $features[] = $feature;
      }
    }    
    return $features;    
  }
  
  function query() {
    $data_source = $this->options['data_source'];
    
    // Load data from Node Locations
    if ($data_source['value'] == 'node_locations') {
      $table = $this->view->query->ensure_table('location');
      $this->view->query->add_field($table, 'latitude', 'openlayers_node_locations_lat');
      $this->view->query->add_field($table, 'longitude', 'openlayers_node_locations_lon');
    }
        
    if ($data_source['value'] == 'geo') {                
      $content_fields = content_fields();
      foreach ($content_fields as $content_field){
        if(in_array($content_field['field_name'],array_keys($data_source['geo_fields']))) {
          $content_table = $this->view->query->ensure_table('node_data_'.$content_field['field_name']);         
          $this->view->query->add_field($wkt_table, $content_field['field_name'].'_wkt');
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
      
      // Get selected preset
      $preset_name = $this->options['presets']['map_preset'];
      $preset = openlayers_get_preset($preset_name);
      $map = $preset['preset_data'];
      
      // Define ID
      $map['id'] = OPENLAYERS_VIEWS_MAP_ID_PREFIX . '-' . $this->view->name;
      
      // @@TODO: Reduce and sort duplicates
      
      // Get features
      $features = $this->map_features($rows);

      // Define a layer for the features
      $map['layers']['openlayers_views_layer'. $this->view->name] = array(
        'id' => 'openlayers_views_layer_'. $this->view->name,
        'type' => 'Vector',
        'name' => $this->display->display_title,
        'options' => array(),
        'events' => array(),
        'features' => $features,
      );
      
      // Set up behaviors
      $map['behaviors'] = ($map['behaviors']) ? $map['behaviors'] : array();
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
      
      // Render map
      $map = openlayers_render_map($map);
      
      // Return map array
      $output .= theme($this->theme_functions(), $this->view, $this->options, $map, $title);
    }
    
    return $output;
  }
}
