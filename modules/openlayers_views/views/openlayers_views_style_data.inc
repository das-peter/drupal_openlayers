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
class openlayers_views_style_data extends views_plugin_style {
  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  /**
   * Options form
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $fields = array();
    $data_source_options = array();

    // Get list of fields in this view & flag available geodata fields
    $handlers = $this->display->handler->get_handlers('field');

    // Check for any fields, as the view needs them
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#value' => t('You need to enable at least one field before you can configure your field settings'),
        '#prefix' => '<div class="error form-item description">',
        '#suffix' => '</div>',
      );
      return; 
    }

    // Go through fields
    foreach ($handlers as $field_id => $handler) {
        $fields[$field_id] = $handler->definition['title'];
    }

    // Default data source
    $data_source_options['other_latlon'] = t('Other: Lat/Lon Point');

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
    $form['data_source']['name_field'] = array(
        '#type' => 'select',
        '#title' => t('Title Field'),
        '#description' => t('Choose the field which will appear as a title on tooltips.'),
        '#options' => array_merge(array('' => ''), $fields),
        '#default_value' => $this->options['data_source']['name_field'],
    );
    $form['data_source']['description_field'] = array(
        '#type' => 'select',
        '#title' => t('Description Field'),
        '#description' => t('Choose the field which will appear as a description on tooltips.'),
        '#required' => FALSE,
        '#options' => array_merge(array('' => ''), $fields),
        '#default_value' => $this->options['data_source']['description_field'],
    );
  }

  /**
   * Map features
   */
  function map_features($records = array()) {      
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
    
    // Separate mapping for grouped views.  Currently only adds name and count. 
    if (!empty($this->options['grouping'])) {
      $this->view->row_index = 0;
      foreach ($records as $id => $record) {
        $feature = array();
        $feature['attributes']['name'] = $id;
        $lat_field = $fields[$data_source['other_lat']]['field_alias'];
        $lon_field = $fields[$data_source['other_lon']]['field_alias'];
        $lon = $record[0]->$lon_field;
        $lat = $record[0]->$lat_field;
        if (!empty($lat) && !empty($lon)) {
          $feature['wkt'] = 'POINT(' . $lon . ' ' . $lat . ')';
          $feature['projection'] = '4326';
        }

        $descriptions = array();
        foreach ($record as $k => $v) {
          foreach ($handlers as $hid => $handler) {
            $rendered_record[$handler->field_alias] = $handler->advanced_render($v);
          }
          $item = '';
          if ($data_source['name_field']) {
            $name_field = $fields[$data_source['name_field']]['field_alias'];
            $item .= "<h2 class='point-title'>". $rendered_record[$name_field] ."</h2>";
          } 
          if ($data_source['description_field']) {
            $description_field = $fields[$data_source['description_field']]['field_alias'];
            $item .= "<div class='point-content'>". $rendered_record[$description_field] ."</div>";
          }
          $descriptions[] = $item;
        }

        $grouped_description = theme('item_list', $descriptions);

        $feature['attributes']['description'] = $grouped_description;
        $feature['attributes']['count'] = count($record);
        // Only add features with WKT data
        if (!empty($feature['wkt'])) {
          $features[] = $feature;
        }
        $this->view->row_index++;
      }
      unset($this->view->row_index);
      return $features;
    }
    
    // Separate mapping for non-grouped views. 
    else {
      $records = array_shift($records);
      foreach ($records as $id => $record) {
        $feature = array();
        $rendered_record = array();
        foreach ($handlers as $hid => $handler) {
          $rendered_record[$handler->field_alias] = $handler->advanced_render($record);
        }
                
        $lat_field = $fields[$data_source['other_lat']]['field_alias'];
        $lon_field = $fields[$data_source['other_lon']]['field_alias'];
        $lon = $record->$lon_field;
        $lat = $record->$lat_field;
        if (!empty($lat) && !empty($lon)) {
          $feature['wkt'] = 'POINT(' . $lon . ' ' . $lat . ')';
          $feature['projection'] = '4326';
        }

        // Fill in all attributes
        foreach ($fields as $fid => $field) {
          $field_alias = $field['field_alias'];
          $feature['attributes'][$field_alias] = $record->$field_alias;
          $feature['attributes'][$field_alias . "_rendered"] = $rendered_record[$field_alias];
        }

        if ($data_source['name_field']) {
          $name_field = $fields[$data_source['name_field']]['field_alias'];
          $feature['attributes']['name'] = $rendered_record[$name_field];
        } 
                        
        if ($data_source['description_field']) {
          $description_field = $fields[$data_source['description_field']]['field_alias'];
          $feature['attributes']['description'] = $record->$description_field;
        }

        // Only add features with WKT data
        if (!empty($feature['wkt'])) {
          $features[] = $feature;
        }
      }          
      return $features;
    }  
  }

  /**
   * Returns an array of features for the map (data for an OL map view)
   */
  function pre_render() {
    // Group the rows according to the grouping field, if specified.
    $grouped = !empty($this->options['grouping']) ? TRUE : FALSE;
    $sets = $this->render_grouping($this->view->result, $this->options['grouping']);
    
    $features = array();
    $features = $this->map_features($sets);                
    return $features;
  }
  
  /**
   * Called by view_ui, do some basic checks
   */
  function render() {
    // Check for live preview.
    if (!empty($this->view->live_preview)) {
      return t('OpenLayers views are not compatible with live preview.');
    }
    
    // Check row plugin if using it.
    if (empty($this->row_plugin)) {
      drupal_set_message("Mising Row Plug-in", "error");
      vpr('views_plugin_style_default: Missing row plugin');
      return;
    }
  }
}
