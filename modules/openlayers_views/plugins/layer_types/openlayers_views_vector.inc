<?php
/**
 * @file
 * OpenLayers Views Vector Layer Type
 */

/**
 * Ctools plugin definition
 */
function openlayers_views_openlayers_views_vector_openlayers_layer_types() {
  return array(
    'title' => t('OpenLayers_Views'),
    'description' => t('OpenLayers Views Vector'),
    'layer_type' => array(
      'file' => 'openlayers_views_vector.inc',
      'class' => 'openlayers_layer_type_openlayers_views_vector',
      'parent' => 'openlayers_layer_type',
    ),
  );
}

class openlayers_layer_type_openlayers_views_vector
  extends openlayers_layer_type {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_type' => 'openlayers_layer_type_openlayers_views_vector',
      'layer_handler' => 'openlayers_views_vector',
      'vector' => TRUE,
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form($defaults = array()) {
    return array(
    );
  }

  /**
   * Get features for this view
   *
   * @param $view_name
   *   the view name
   * @param $display_name
   *   the view display name
   * @return
   *   array of features
   */
  function get_features() {
    if ($view = views_get_view($this->data['views']['view'])) {
      $args = array();
      // Retrieve args/filters from current view
      // to pass on to our vector layer.
      $current_view = views_get_current_view();
      if (!empty($current_view)) {
        $args = $current_view->args;
        if (isset($current_view->exposed_input)) {
          $view->set_exposed_input($current_view->exposed_input);
        }
      }
      $features = $view->execute_display($this->data['views']['display'], $args);

      // Get dynamic title from view
      $this->title = $view->get_title();

      $view->destroy();
    }

    $this->data['features'] = isset($features) ? $features : array();
    return $this->data['features'];
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers_views') .
      '/plugins/layer_types/openlayers_views_vector.js');
    $this->get_features();
    return $this->options;
  }
}
