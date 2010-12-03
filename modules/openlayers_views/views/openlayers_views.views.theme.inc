<?php
// $Id$

/**
 * @file
 * This file holds views theme function for style plugin.
 *
 * @ingroup openlayers
 */

/**
 * Implementation of theme function
 */
function theme_openlayers_views_map($view, $options = array(),
  $map = array(), $title = FALSE) {
  return (($title) ? '<h3>'. $title .'</h3>' : '') . 
    '<div class="openlayers-views-map">'
    . $map['themed']
    . '</div>';
}

/**
 * Implementation of theme function
 */
function theme_openlayers_row_geometry($vars) {
  $view = $vars['view'];

  // Loop through the fields for this view.
  $inline = FALSE;
  $vars['fields'] = array();
  $feature = array();
  foreach ($view->field as $id => $field) {
    // render this even if set to exclude so it can be used elsewhere.
    $field_output = $view->style_plugin->get_field($view->row_index, $id);
    $empty = $field_output !== 0 && empty($field_output);
    if (empty($field->options['exclude']) &&
        (!$empty || (empty($field->options['hide_empty']) &&
        empty($vars['options']['hide_empty'])))) {
      $object = new stdClass();

      $object->content = $field_output;
      if (isset($view->field[$id]->field_alias) &&
          isset($vars['row']->{$view->field[$id]->field_alias})) {
        $object->raw = $vars['row']->{$view->field[$id]->field_alias};
      }
      else {
        $object->raw = NULL; // make sure it exists to reduce NOTICE
      }

      $object->handler = &$view->field[$id];
      $object->element_type = $object->handler->element_type();

      $feature[$id] = $object->content;
      if ($id == $vars['options']['geometry']) {
        $feature['geometry'] = $object->content;
      }
    }
  }
  print_r($feature);
}
