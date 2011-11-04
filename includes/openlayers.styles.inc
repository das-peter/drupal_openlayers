<?php

/**
 * @file
 * This file contains styles implementations
 *
 * @ingroup openlayers
 */

/**
 * Style Implementation
 *
 * Internal callback for openlayers style implementation.
 *
 * @return
 *   Array of styles for an OpenLayers map
 */
function _openlayers_openlayers_styles() {
  $styles = array();

  $style = new stdClass();
  $style->api_version = 1;
  $style->name = 'default';
  $style->title = t('Default style');
  $style->description = t('Basic default style.');
  $style->data = array(
    'pointRadius' => '6',
    'fillColor' => '#888888',
    'strokeColor' => '#222222',
    'strokeWidth' => '4',
    'fillOpacity' => '0.5',
    'strokeOpacity' => '0.7',
  );
  $styles[$style->name] = $style;

  $style = new stdClass();
  $style->api_version = 1;
  $style->name = 'invisible';
  $style->title = t('Invisible style');
  $style->description = t('Invisible default style.');
  $style->data = array(
    'pointRadius' => '0',
    'strokeWidth' => '0',
    'fillOpacity' => '0'
  );
  $styles[$style->name] = $style;

  $style = new stdClass();
  $style->api_version = 1;
  $style->name = 'default_select';
  $style->title = t('Default select style');
  $style->description = t('Default style for selected geometries');
  $style->data = array(
    'pointRadius' => '6',
    'fillColor' => '#222222',
    'strokeColor' => '#888888',
    'strokeWidth' => '4',
    'fillOpacity' => '0.7',
    'strokeOpacity' => '0.8',
  );
  $styles[$style->name] = $style;

  return $styles;
}
