<?php

function openlayers_openlayers_map_map_openlayers_map() {
  return array(
    'handler' => array(
      'class' => 'openlayers_map_map',
    )
  );
}

class openlayers_map_map extends openlayers_map {

  function options_form() {
    $form['options']['ui'] = array(
      '#type' => 'fieldset',
      '#title' => t('Size of the map'),
      '#tree' => TRUE,
      'width' => array(
        '#type' => 'textfield',
        '#title' => 'Width',
        '#default_value' => $this->getOption('width', 'auto'),
        '#parents' => array('options', 'width'),
      ),
      'height' => array(
        '#type' => 'textfield',
        '#title' => 'height',
        '#default_value' => $this->getOption('height', '300px'),
        '#parents' => array('options', 'height'),
      ),
      'contextualLinks' => array(
        '#type' => 'checkbox',
        '#title' => 'Contextual links',
        '#description' => t('Enable contextual links on the map.'),
        '#default_value' => $this->getOption('contextualLinks', TRUE),
        '#parents' => array('options', 'contextualLinks'),
      ),
      'provideBlock' => array(
        '#type' => 'checkbox',
        '#title' => 'Provide Drupal block',
        '#description' => t('Enable this to enable a block to display the map.'),
        '#default_value' => $this->getOption('provideBlock', TRUE),
        '#parents' => array('options', 'provideBlock'),
      ),
    );

    $form['options']['view'] = array(
      '#type' => 'fieldset',
      '#title' => t('View: center and rotation'),
      '#tree' => TRUE,
    );

    if ($this->machine_name != 'map_view_edit_form') {
      $map = openlayers_object_load('map', 'map_view_edit_form');
      if ($view = $this->getOption('view')) {
        $map->options['view'] = $view;
      }

      $form['options']['view']['map'] = array(
        '#title' => 'Map',
        '#markup' => openlayers_render_map($map),
      );
    }

    $form['options']['view']['center'] = array(
      'lat' => array(
        '#type' => 'textfield',
        '#title' => 'Latitude',
        // Todo: Replace with getOption() method.
        '#default_value' => isset($this->options['view']['center']['lat']) ? $this->options['view']['center']['lat']:0,
        '#parents' => array('options', 'view', 'center', 'lat'),
      ),
      'lon' => array(
        '#type' => 'textfield',
        '#title' => 'Longitude',
        '#default_value' => isset($this->options['view']['center']['lon']) ? $this->options['view']['center']['lon']:0,
        '#parents' => array('options', 'view', 'center', 'lon'),
      )
    );
    $form['options']['view']['rotation'] = array(
      'rotation' => array(
        '#type' => 'textfield',
        '#title' => 'Rotation',
        '#default_value' => isset($this->options['view']['rotation']) ? $this->options['view']['rotation']:0,
        '#parents' => array('options', 'view', 'rotation'),
      ),
    );
    $form['options']['view']['zoom'] = array(
      'zoom' => array(
        '#type' => 'textfield',
        '#title' => 'Zoom',
        '#default_value' => isset($this->options['view']['zoom']) ? $this->options['view']['zoom']:0,
        '#parents' => array('options', 'view', 'zoom'),
      ),
    );

    return $form;
  }
}
