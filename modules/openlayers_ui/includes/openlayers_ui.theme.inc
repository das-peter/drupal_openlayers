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
function theme_openlayers_ui_form_layer_description($args) {
  return $args['layer_title'] . ($args['layer_description'] ?
    ': <span class="openlayers-form-layer-description">' .
    $args['layer_description'] . '</span>' :
    '');
}

/**
 * Theme function for form description of projection
 */
function theme_openlayers_ui_form_projection_description($args) {
  $output = $args['projection_title'];
  if (count($args['available_layers'])) {
    $names = implode(', ', $args['available_layers']);
    $output .= " - <span class='openlayers-form-projection-description'>$names</span>";
  }
  return $output;
}

/**
 * Theme function for presets form
function theme_openlayers_ui_presets_form($form) {
  $links = $panels = array();
  $first = TRUE;

  foreach (element_children($form) as $key) {
    if (!isset($form[$key]['#type']) && element_children($form[$key]) && $key != 'buttons') {
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
  $form = drupal_render($form);

  $left = "<div class='openlayers-column-left'>{$links}<div class='buttons'>{$buttons}</div></div>";
  $right = "<div class='openlayers-column-right'>{$panels}{$form}</div>";
  return $right . $left;
}
 */

function theme_openlayers_ui_presets_form_layers($form) {
  $output = '';
  $output .= drupal_render($form['ahah-start']) .
    drupal_render($form['projections']);

  // Base layers
  $rows = array();
  foreach (element_children($form['layers']['baselabels']) as $key) {
    unset($form['layers']['default_layer'][$key]['#title']);
    unset($form['layers']['baselayers'][$key]['#title']);
    
    $rows[] = array(
      drupal_render($form['layers']['baselabels'][$key]),
      drupal_render($form['layers']['baselayers'][$key]),
      drupal_render($form['layers']['default_layer'][$key]));
  }
  $output .= theme('table', array(
    'header' => array(t('Base layers'), t('Enabled'), t('Default')), 
    'rows' => $rows)
  );

  // Overlay layers
  $rows = array();
  foreach (element_children($form['layers']['overlaylabels']) as $key) {
    unset($form['layers']['overlays'][$key]['#title']);
    unset($form['layer_activated'][$key]['#title']);
    unset($form['layer_switcher'][$key]['#title']);

    $rows[] = array(
      'data' => array(
        drupal_render($form['layers']['overlaylabels'][$key]),
        drupal_render($form['layer_weight'][$key]),
        drupal_render($form['layers']['overlays'][$key]),
        drupal_render($form['layer_activated'][$key]),
        drupal_render($form['layer_switcher'][$key]),
        drupal_render($form['layer_styles'][$key])),
      'class' => 'draggable'
    );
  }
  $output .= theme('table', 
    array(
      'header' => array(t('Overlay layers'),
        t('Weight'), t('Enabled'), t('Activated'),
        t('In Switcher'), t('Style')), 
      'rows' => $rows, 
      array('id' => 'overlay-layer-table')
    )
  );

  drupal_add_tabledrag('overlay-layer-table', 'order', 'sibling', 'layer-weight');
  $output .= drupal_render($form);
  return $output;
}

/**
 * Drupal theme implementation for Behaviors in the Preset form
 */
function theme_openlayers_ui_presets_form_behaviors($form) {
  $output = '';
  $rows = array();
  foreach (element_children($form) as $key) {
    $rows[] = drupal_render($form[$key]['enabled']) . 
      drupal_render($form[$key]['options_set']) . 
      drupal_render($form[$key]['dependencies']);
  }
  
  // Create table
  $output .= theme('table', array('header' => array(t('Behaviors')), 'rows' => $rows));
  return $output;
}
