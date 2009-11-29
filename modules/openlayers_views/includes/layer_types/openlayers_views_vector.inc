<?php
// $Id$

/**
 * @file
 * OpenLayers Views Vector Layer Type
 */
 

class openlayers_layer_type_openlayers_views_vector extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_type' => 'openlayers_layer_type_openlayers_views_vector',
      'layer_handler' => 'openlayers_views_vector',
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form() {
    return array(
    );
  }

  /*
   * Get features for this view
   * @param $view_name the view name
   * @param $display_name the view display name
   * @return array of features
   */
  function get_features($view_name, $display_name) {
    $features = array();
    if ($view = views_get_view($view_name)) {
      $args = array();
      // Retrieve args/filters from current view to pass on to our vector layer.
      $current_view = views_get_current_view();
      if ($current_view) {
        $args = $current_view->args;
        $view->set_exposed_input($current_view->exposed_input);
      }
      $view->execute_display($display_name, $args);
      $view->init_style();
      $features = $view->style_plugin->pre_render($view->result);
      $view->destroy();
    } 
    return $features;
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers_views') .
      '/includes/layer_types/openlayers_views_vector.js');
    //$processed[$layer_name]['features'] 
    $features = $this->get_features($this->data['views']['view'],
      $this->data['views']['display']);
    $this->data['features'] = $features;
    return $this->options;
  }
}
