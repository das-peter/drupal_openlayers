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
 * Extension of the Views Plugin Style for OpenLayers
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
    $options['data_source'] = 'openlayers_wkt';
    return $options;
  }

  /**
   * Options form
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Get list of fields in this view & flag available geodata fields
    $handlers = $this->display->handler->get_handlers('field');

    // Check for any fields, as the view needs them
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#value' => t('You need to enable at least one field before you can '
        . 'configure your field settings'),
        '#prefix' => '<div class="error form-item description">',
        '#suffix' => '</div>',
      );
      return;
    }

    $fields = array();
    foreach ($handlers as $field_id => $handler) {
      $fields[$field_id] = $handler->definition['title'];
    }

    $form['data_source'] = array(
      '#type' => 'fieldset',
      '#tree' => TRUE,
      '#title' => t('Data Source'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['data_source']['name_field'] = array(
        '#type' => 'select',
        '#title' => t('Title Field'),
        '#description' => t('Choose the field which will appear as a title '
        . 'on tooltips.'),
        '#options' => array_merge(array('' => ''), $fields),
        '#default_value' => $this->options['data_source']['name_field'],
    );
    $form['data_source']['description_field'] = array(
        '#type' => 'select',
        '#title' => t('Description Field'),
        '#description' => t('Choose the field which will appear as a '
        . 'description on tooltips.'),
        '#required' => FALSE,
        '#options' => array_merge(array('' => ''), $fields),
        '#default_value' => $this->options['data_source']['description_field'],
    );

    $form['attributes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Attributes and Styling'),
      '#description' => t('Attributes are field data attached to each feature.'
      . ' This can be used with styling to create Variable styling.'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $variable_fields = array();
    if (!empty($this->options['data_source']['name_field'])) {
      $variable_fields['name'] = '${name}';
    }
    if (!empty($this->options['data_source']['description_field'])) {
      $variable_fields['description'] = '${description}';
    }
    foreach ($this->view->display_handler->get_handlers('field') as
      $field => $handler) {
      if (($field != $this->options['data_source']['name_field']) &&
          ($field != $this->options['data_source']['description_field'])) {
        $variable_fields[$field] = '${' . $field . '}';
        $variable_fields[$field . '_rendered'] = '${' . $field . '_rendered}';
      }
    }
    $form['attributes']['styling'] = array(
      '#markup' => '
      <p>' . t('Any fields that you add to this view will be attached to '
      . 'their respective feature (point, line, polygon) as attributes.  '
      . 'These attributes can then be used to add variable styling to your '
      . 'themes.  This is accomplished by using the %syntax syntax in the '
      . 'values for a style.  The following is a list of formatted variables '
      . 'that are currently available; these can be placed right in the style '
      . 'interface.  The %rendered one means that it has been processed by '
      . 'Views and may have a different value.',
      array(
          '%syntax' => '${field_name}',
          '%rendered' => '_rendered')
      )
      . '</p>' 
      . theme('item_list', $variable_fields) . '<p>'
      . t('Please note that this does not apply to Grouped Displays.')
      . '</p>',
    );
  }

  /**
   * Map features
   *
   * @param $records ...
   */
  function map_features($records = array()) {
    $rows = '';
    foreach ($this->view->result as $row) {
      $rows .= $this->row_plugin->render($row);
    }
    return $rows;
  }

  /**
   * Render the map features.
   */
  function render($result) {
    // if (!empty($this->view->live_preview)) {
    //   return t('OpenLayers views are not compatible with live preview.');
    // }

    $sets = $this->render_grouping($result, $this->options['grouping']);
    return $this->map_features($sets);
  }
}
