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
    'display' => array(
      'openlayers' => array(
        'title' => t('OpenLayers Data Overlay'),
        'help' => t('Data layer for OpenLayers maps.'),
        'handler' => 'openlayers_views_plugin_display_openlayers',
        'path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'uses hook menu' => FALSE,
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'accept attachments' => FALSE,
        'admin' => t('OpenLayers Data Overlay'),
      ),
    ),
    'style' => array(
      'openlayers_map' => array(
        'title' => t('OpenLayers Map'),
        'help' => t('Displays a View as an OpenLayers map.'),
        'handler' => 'openlayers_views_style_map',
        'theme' => 'openlayers_views_map',
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
        'title' => t('OpenLayers Data Overlay'),
        'help' => t('Provides Data to Power an OpenLayers map.'),
        'handler' => 'openlayers_views_style_data',
        'theme' => 'openlayers_views_data',
        'theme path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'uses fields' => TRUE,
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'uses grouping' => TRUE,
        'type' => 'openlayers',
        'even empty' => TRUE,
      ),
    ),
    'row' => array(
      'point' => array(
        'title' => t('Point'),
        'help' => t('Formats points'),
        'handler' => 'openlayers_views_plugin_row_point',
        'theme' => 'openlayers_row_point',
        'theme path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-row-fields',
      ),
      'bounding_box' => array(
        'title' => t('Bounding Box'),
        'help' => t('Formats bounding boxes'),
        'handler' => 'openlayers_views_plugin_row_bounding_box',
        'theme' => 'openlayers_row_bounding_box',
        'theme path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-row-fields',
      ),
      'geometry' => array(
        'title' => t('Geometry'),
        'help' => t('Formats geometries'),
        'handler' => 'openlayers_views_plugin_row_geometry',
        'theme' => 'openlayers_row_geometry',
        'theme path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'path' => drupal_get_path('module', 'openlayers_views') .'/views',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-row-fields',
      ),
    ),
  );
}
