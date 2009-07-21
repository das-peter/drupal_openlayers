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
      '#default_value' => $this->options['presets']['map_preset'] ? $this->options['presets']['map_preset'] : variable_get('openlayers_default_preset', 'default'),
    );
    
    // Behavior options
    if (module_exists('openlayers_behaviors')) {
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
      $form['behaviors']['declutter'] = array(
        '#type' => 'checkbox',
        '#title' => t('Declutter'),
        '#description' => t('Automagically space points so they do not overlap.'),
        '#default_value' => $this->options['behaviors']['declutter'], 
      );
      $form['behaviors']['declutter_adjustment'] = array(
        '#type' => 'textfield',
        '#title' => t('Declutter Distance Adjustment'),
        '#description' => t('Set to a negative number to have icons cluster closer together. Set to a positive number to have them furthur apart. Leave blank for default.'),
        '#default_value' => $this->options['behaviors']['declutter_adjustment'],
        '#process' => array('views_process_dependency'),
        '#dependency' => array('edit-style-options-behaviors-declutter' => array('1')),
      );

      // Tooltip options if fields
      if (count($fields) > 0) {
        $tooltip_options = array_merge(array('0' => t('<none>')), $fields);
        $form['behaviors']['tooltip'] = array(
          '#type' => 'select',
          '#title' => t('Tooltip Field'),
          '#title' => t('Select the field you would like to use as a tooltip'),
          '#options' => $tooltip_options,
          '#default_value' => $this->options['behaviors']['tooltip'], 
        );
      }
    }
    
    // Grouping
    $form['grouping_set'] = array(
      '#type' => 'fieldset',
      '#title' => t('Grouping'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $grouping_options = array_merge(array('0' => t('<none>')), $fields);
    $form['grouping_set']['grouping'] = array(
      '#type' => 'select',
      '#title' => t('Grouping Field'),
      '#options' => $grouping_options,
      '#default_value' => $this->options['grouping_set']['grouping'],
      '#description' => t('You can group features by field.  This means that each group will be a separate layer with those specific features.'),
    );
    
    // Variable Styles
    $form['style'] = array(
        '#type' => 'fieldset',
        '#title' => t('Feature Styles'),
        '#description' => t('For advanced users only'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
    $form['style']['snippet'] = array(
      '#type' => 'textarea',
      '#title' => t('Feature Styles function'),
      '#description' => t('Enter PHP code that returns a style array for each feature. This will overrirde theme feature styling functions. <br/> $fields contains your defined fields, $row contains instances of those fields along with geometries. Array should be of the form \'styleProperty\' => \'styleValue\'. You may return false to use defaults. See documentation for available style Properties.'),
      '#default_value' => $this->options['style']['snippet'],
    );
    
  }
     
  /**
   * Map features
   */
  function map_features($rows = array(), $group = NULL) {  
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
      $feature = array();
      
      // Go through data sources
      // @@TODO: In theory, there could be multiple features per row., allow for multiple features per row
      foreach ($data_source['value'] as $data_source_value) {
        switch ($data_source_value) {
          case 'node_locations':
            // @@TODO: These fields are provided only if the fields are chosen in the interface.
            if (!empty($row->location_longitude) && !empty($row->location_latitude)) {
              $wkt_string = 'POINT(' . $row->location_longitude . ' ' . $row->location_latitude . ')';
              $feature['wkt'] = $wkt_string;
              $feature['projection'] = '4326';
            }
            break;
            
          case 'geo':
            // @@TODO: Geo does not work
            foreach ($data_source['geo_fields'] as $geo_field) {            
              $wkt_field = $geo_field . '_wkt';
              
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
            
            if (!empty($lat) && !empty($lon)) {
              $feature['wkt'] = 'POINT(' . $lon . ' ' . $lat . ')';
              $feature['projection'] = '4326';
            }
            break;
            
          case 'other_wkt':
            // Go through selected field
            foreach ($data_source['other_wkt'] as $wkt_field) {
              if (!empty($row->$fields[$wkt_field]['field_alias'])) {
                $feature['wkt'] = $row->$fields[$wkt_field]['field_alias'];
                $feature['projection'] ='4326';
              }
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
      if (!empty($this->options['behaviors']['tooltip'])) {
        $tooltip_field = $this->options['behaviors']['tooltip'];
        $tooltip_field_alias = $fields[$tooltip_field]['field_alias'];
        $feature['attributes']['openlayers_tooltip'] = $row->$tooltip_field_alias;
      }
      
      // Run feature styles through theme function
      $feature_style = theme('openlayers_views_feature_style', $this, $row, $group);
      if (is_array($feature_style) && !empty($feature_style)) {
        $feature['style'] = $feature_style;
      }
      
      // Run feature styles through custom php function
      if ($this->options['style']['snippet']) {
        $feature_style = eval($this->options['style']['snippet']);
        if (is_array($feature_style)){
          $feature['style'] = $feature_style;
        }
      }
      
      // Only add features with WKT data
      if (!empty($feature['wkt'])) {
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
      foreach ($content_fields as $content_field) {
        if (in_array($content_field['field_name'], array_keys($data_source['geo_fields']))) {
          $content_table = $this->view->query->ensure_table('node_data_' . $content_field['field_name']);         
          $this->view->query->add_field($wkt_table, $content_field['field_name'] . '_wkt');
        }
      }    
    }
  }
  
  /**
   * Renders views (map)
   */
  function render() {
    $output = '';
    
    // Check for live preview.
    if (!empty($this->view->live_preview)) {
      return t('OpenLayers views are not compatible with live preview.');
    }
    
    // Check row plugin if using it.
    if ($this->uses_row_plugin() && empty($this->row_plugin)) {
      vpr('views_plugin_style_default: Missing row plugin');
      return;
    }

    // Get selected preset
    $preset_name = $this->options['presets']['map_preset'];
    $preset = openlayers_get_preset($preset_name);
    $map = $preset['preset_data'];

    // Define ID
    $map['id'] = OPENLAYERS_VIEWS_MAP_ID_PREFIX . '-' . $this->view->name;

    // Group the rows according to the grouping field, if specified.
    $sets = $this->render_grouping($this->view->result, $this->options['grouping_set']['grouping']);
    $grouped = !empty($this->options['grouping_set']['grouping']) ? TRUE : FALSE;
    
    // Render each group separately and concatenate.  Plugins may override this
    // method if they wish some other way of handling grouping.
    foreach ($sets as $group_title => $records) {
      // Make 'machine readable' format
      $group_name = strtolower(str_replace(' ', '_', $group_title));
    
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
      
      // @@TODO: Reduce and sort duplicates
      
      // Style the features based on group (can override this with the theme hook)
      $features = $this->map_features($rows, $group_name);
      
      // Create name of layer and id
      $layer_name = $grouped ? $group_title . ' layer' : $this->display->display_title;
      $layer_id = 'openlayers_views_layer_' . $this->view->name;
      $layer_id .= $grouped ? '_' . $group_name : '';

      // Define a layer for the features
      $map['layers'] = is_array($map['layers']) ? $map['layers'] : array();
      $map['layers'][$layer_id] = array(
        'id' => $layer_id,
        'type' => 'Vector',
        'name' => $layer_name,
        'options' => array(),
        'events' => array(),
        'features' => $features,
      );
      
      // Set up tooltip behavior
      if (module_exists('openlayers_behaviors')) {
        if (!empty($this->options['behaviors']['tooltip'])) {
          $map['behaviors'] = is_array($map['behaviors']) ? $map['behaviors'] : array();
          $field_id = $this->view->display_handler->get_handler('field', $this->options['behaviors']['tooltip'])->field_alias;
          $map['behaviors']['openlayers_views_tooltip_' . $layer_id] = array(
            'id' => 'openlayers_views_tooltip_' . $layer_id,
            'type' => 'openlayers_behaviors_tooltip',
            'layer' => $layer_id,
            'attribute' => 'openlayers_tooltip',
          );
        }
      }
    }
    
    // Sort layers by id
    ksort($map['layers']);
    
    // Check other beahvior options
    if (module_exists('openlayers_behaviors')) {
      $map['behaviors'] = is_array($map['behaviors']) ? $map['behaviors'] : array();
      // Zoom to layer., assuming last layer
      // @@TODO: Use better logic or use options
      if ($this->options['behaviors']['zoom_to_layer']) {
        $map['behaviors']['openlayers_views_zoom_to_layer'] = array(
          'id' => 'openlayers_views_zoom_to_layer',
          'type' => 'openlayers_behaviors_zoom_to_layer',
          'layer' => 'openlayers_views_layer_'. $this->view->name,
        );
      }
      // Full screen
      if ($this->options['behaviors']['fullscreen']) {
        $map['behaviors']['openlayers_views_fullscreen'] = array(
          'id' => 'openlayers_views_fullscreen',
          'type' => 'openlayers_behaviors_fullscreen'
        );
      }
      // Declutter
      if ($this->options['behaviors']['declutter']) {
        $map['behaviors']['openlayers_views_declutter'] = array(
          'id' => 'openlayers_views_declutter',
          'type' => 'openlayers_behaviors_declutter',
          'layer' => 'openlayers_views_layer_'. $this->view->name,
        );
        
        if ($this->options['behaviors']['declutter_adjustment']) {
          $map['behaviors']['openlayers_views_declutter']['adjustment'] = intval($this->options['behaviors']['declutter_adjustment']);
        }
      }
    }
    
    // Render map
    $map = openlayers_render_map($map);
      
    // Return map array
    $output .= theme($this->theme_functions(), $this->view, $this->options, $map, $group_name);
    return $output;
  }
}
