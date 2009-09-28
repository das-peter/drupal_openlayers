<?php
// $Id$

/**
 * @file
 * This file holds the theme functions for openlayers ui module
 *
 * @ingroup openlayers
 */

/**
 * Theme function for form description of layers
 */
function theme_openlayers_ui_form_layer_description($layer_title = '', $layer_description = '') {
  if ($layer_description) {
    $output = $layer_title . ' - <span class="openlayers-form-layer-description">' . $layer_description . '</span>';
  }
  else {
    $output = $layer_title;
  }
  return $output;
}

/**
 * Theme function for form description of projection
 */
function theme_openlayers_ui_form_projection_description($projection_title = '', $available_layers = array(), $layers = array()) {
  // Get names of layers
  $names = array();
  foreach ($available_layers as $k => $val) {
    $names[] = $layers[$val]->name;
  }

  if ($names) {
    $output = '
      ' . $projection_title . ' -
      <span class="openlayers-form-projection-description">
        ' . t('Available Layers') . ':
        ' . implode(', ', $names) . '
      </span>
    ';
  }
  else {
    $output = $projection_title;
  }
  return $output;
}

/**
 * Theme function for preset form
 */
function theme_openlayers_ui_presets_form($form) {
  $links = $panels = array();
  $first = TRUE;
  $no_panels = array('buttons', 'map_preview');

  // Go through form
  foreach (element_children($form) as $key) {
    if (!isset($form[$key]['#type']) && element_children($form[$key]) && (!in_array($key, $no_panels))) {
      $class = $first ? 'openlayers-panel-active' : '';

      $links[$key] = array(
        'title' => $form[$key]['#title'],
        'href' => $_GET['q'],
        'fragment' => "openlayers-panel-{$key}",
        'attributes' => array('class' => $class),
      );

      unset($form[$key]['#title']);
      $panels[$key] = "<div class='openlayers-panel openlayers-panel-{$key} {$class}'>";
      $panels[$key] .= isset($form[$key]['#description']) ? "<div class='description'>{$form[$key]['#description']}</div>" : '';
      $panels[$key] .= drupal_render($form[$key]);
      $panels[$key] .= "</div>";
      $first = FALSE;
    }
  }

  $panels = implode("\n", $panels);
  $links = theme('links', $links, array('id' => 'openlayers-panel-links'));
  $buttons = drupal_render($form['buttons']);
  $preview_map = drupal_render($form['map_preview']);
  $form = drupal_render($form);

  // Create output
  return '
    <div class="openlayers-ui-preview-map">
      ' . $preview_map . '
    </div>
    <div class="openlayers-column-left">
      ' . $links . '
      <div class="buttons">
        ' . $buttons . '
      </div>
    </div>
    <div class="openlayers-column-right">
      ' . $panels . $form . '
    </div>
  ';
}

/**
 * Theme function for layers in preset form
 */
function theme_openlayers_ui_presets_form_layers($form) {
  $output = '';
  $output .= drupal_render($form['ahah-start']);
  $output .= drupal_render($form['projections']);

  // Base layers
  $rows = array();
  foreach (element_children($form['layers']['baselabels']) as $key) {
    $row = array();
    unset($form['layers']['default_layer'][$key]['#title']);
    unset($form['layers']['baselayers'][$key]['#title']);
    $row[] = drupal_render($form['layers']['baselabels'][$key]);
    $row[] = drupal_render($form['layers']['baselayers'][$key]);
    $row[] = drupal_render($form['layers']['default_layer'][$key]);
    $rows[] = $row;
  }
  $output .= theme('table', array(t('Base layers'), t('Enabled'), t('Default')), $rows);

  // Overlay layers
  $rows = array();
  foreach (element_children($form['layers']['overlaylabels']) as $key) {
    $row = array();
    unset($form['layers']['overlays'][$key]['#title']);
    unset($form['layer_activated'][$key]['#title']);
    $row[] = drupal_render($form['layers']['overlaylabels'][$key]);
    $row[] = drupal_render($form['layers']['overlays'][$key]);
    $row[] = drupal_render($form['layer_activated'][$key]);
    $row[] = drupal_render($form['layer_styles'][$key]);
    $rows[] = $row;
  }
  $output .= theme('table', array(t('Overlay layers'), t('Enabled'), t('Activated'), t('Style')), $rows);
  $output .= drupal_render($form);
  return $output;
}