<?php
// $Id$

/**
 * @file
 * Test 
 */

// Define plugin for CTools
$plugin = array(
  'title' => t('Example Plugin'),
  'description' => t('Example style plugin for context styling.
    Sets a random Fill Opacity.'),
  'style_plugin' => array(
    'class' => 'openlayers_style_plugin_test_plugin',
    'parent' => 'openlayers_style_plugin',
  ),
);

/**
 * Style Plugin for testing purposes.
 */
class openlayers_style_plugin_test_plugin extends 
  openlayers_style_plugin {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'context_properties' => array(
        'fillOpacity' => 'getFillOpacity',
      ),
      'context_object' => 'openlayersExampleContext',
    );
  }
  
  /**
   * Options form.
   */
  function options_form($defaults = array()) {
    return array();
  }

  /**
   * Render function
   */
  function render(&$style) {
    // For context styling, we want to replace the
    // style properties with their context value
    foreach ($this->options['context_properties'] as $prop => $callback) {
      $style->data[$prop] = '${' . $callback . '}';
    }
    
    // Enable context
    $style->data['context_object'] = $this->options['context_object'];
    
    // Add JS
    drupal_add_js(drupal_get_path('module', 'openlayers_test') .
      '/plugins/style_plugin/openlayers_test_test_plugin.js');
  }
}