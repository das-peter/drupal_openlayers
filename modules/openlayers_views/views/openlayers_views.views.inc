<?php
// $Id$

/**
 * @file
 * This file holds main views functions for the openlayers_views module.
 *
 * @ingroup openlayers
 */

/**
 * Implementation of hook_views_plugins().
 */
function openlayers_views_views_plugins() {
  return array(
    'module' => 'openlayers_views',
    'style' => array(
      'openlayers_views' => array(
        'title' => t('OpenLayers Map Original'),
        'help' => t('Displays an OpenLayers map -- 1.x style'),
        'handler' => 'openlayers_views_style_map',
        'theme' => 'openlayers_views_map',
        'theme file' => 'openlayers_views.views.theme.inc',
        'theme path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'uses fields' => TRUE,
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'uses grouping' => TRUE,
        'type' => 'normal',
        'even empty' => TRUE,
      ),
      'openlayers_map' => array(
        'title' => t('OpenLayers Map Simple'),
        'help' => t('Displays a View as an OpenLayers map -- 0.x style'),
        'handler' => 'openlayers_views_style_map_simple',
        'theme' => 'openlayers_views_map',
        'theme file' => 'openlayers_views.views.theme.inc',
        'theme path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'uses fields' => FALSE,
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
        'even empty' => TRUE,
      ),
      'openlayers_data' => array(
        'title' => t('OpenLayers Data'),
        'help' => t('Provides a views powered layer that can be added to any map.'),
        'handler' => 'openlayers_views_style_data',
        'theme' => 'openlayers_views_data',
        'theme path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'uses fields' => TRUE,
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'uses grouping' => TRUE,
        'type' => 'normal',
        'even empty' => TRUE,
      ),
    ),
  );
}
