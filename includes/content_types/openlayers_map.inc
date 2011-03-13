<?php
// $Id: no_context_content_type.inc,v 1.2 2010/01/29 19:53:48 merlinofchaos Exp $

/**
 * @file
 * OpenLayers Map Content Type. Displays a map from a preset
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  // And this is just the administrative title.
  // All our callbacks are named according to the standard pattern and can be deduced.
  'title' => t('Openlayers Map'),
  'content type' => 'openlayers_openlayers_map_content_type_content_types',
  'render callback' => 'openlayers_map_content_type_render',
);

/**
 * Return all content types available.
 */
function openlayers_openlayers_map_content_type_content_types($plugin) {
  $types = array();
  $presets = openlayers_presets();

  foreach ($presets as $preset) {
    $types[$preset->name] = array (
      'preset' => $preset->name,
      'title' => $preset->title,
      'description' => $preset->description,
      'category' => t('OpenLayers Preset Maps'),
    );
  }

  return $types;
}

/**
 * Run-time rendering of the body of the block.
 *
 * @param $subtype
 * @param $conf
 *   Configuration as done at admin time.
 * @param $args
 * @param $context
 *   Context - in this case we don't have any.
 *
 * @return
 *   An object with at least title and content members.
 */
function openlayers_map_content_type_render($subtype, $conf, $args, $context) {
  $preset = openlayers_preset_load($subtype);

  $block = new stdClass();
  $block->title = $preset->title;
  $block->content = openlayers_render_preset($preset);
  
  return $block;
}


/**
 * Empty form so we can have the default override title.
 */
function openlayers_openlayers_map_content_type_edit_form($form, &$form_state) {
  // Does nothing!
  return $form;
}
