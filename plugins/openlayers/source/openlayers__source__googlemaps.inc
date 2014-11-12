<?php
/**
 * @file
 * Google maps API integration based on the example here:
 * http://openlayers.org/en/v3.0.0/examples/google-map.html
 * http://bl.ocks.org/elemoine/e82c7dd4b1d0ef45a9a4
 */

/**
 * Defines the google source handler plugin.
 *
 * @return array
 *   The plugin data.
 */
function openlayers_openlayers__source__googlemaps_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers__source__googlemaps',
      'file' => 'openlayers__source__googlemaps.inc',
    ),
  );
}

/**
 * Class openlayers__source__googlemaps.
 */
class openlayers__source__googlemaps extends openlayers_source {

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    $layer_types = array(
      'ROADMAP',
      'SATELLITE',
      'HYBRID',
      'TERRAIN',
    );

    $form['options']['key'] = array(
      '#title' => t('Key'),
      '#type' => 'textfield',
      '#default_value' => $this->getOption('key', ''),
    );
    $form['options']['client'] = array(
      '#title' => t('Client'),
      '#type' => 'textfield',
      '#default_value' => $this->getOption('client', ''),
    );
    $form['options']['channel'] = array(
      '#title' => t('Channel'),
      '#type' => 'textfield',
      '#default_value' => $this->getOption('client', ''),
    );
    $form['options']['mapTypeId'] = array(
      '#title' => t('Mapy Type'),
      '#type' => 'select',
      '#default_value' => $this->getOption('mapTypeId', 'ROADMAP'),
      '#options' => array_combine($layer_types, $layer_types),
    );
    $form['options']['sensor'] = array(
      '#title' => t('Sensor'),
      '#type' => 'checkbox',
      '#default_value' => $this->getOption('sensor', FALSE),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function alterBuild(&$build, $map) {
    $gmap_id = 'gmap-' . $map->getId();
    $build['gmap'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'div',
      '#value' => '',
      '#attributes' => array(
        'id' => $gmap_id,
        'class' => array('gmap-map'),
        'style' => 'height: 100%; width: 100%;',
      ),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function attached() {
    $google_maps_script = '//maps.google.com/maps/api/js?v=3&language=' . $GLOBALS['language']->language . '&';
    $google_maps_script .= 'sensor=' . ($this->getOption('sensor', FALSE) ? 'false' : 'true') . '&';
    if (($key = $this->getOption('key', ''))) {
      $google_maps_script .= 'key=' . $key . '&';
    }
    if (($client = $this->getOption('client', ''))) {
      $google_maps_script .= 'client=' . $client . '&';
    }
    if (($channel = $this->getOption('channel', ''))) {
      $google_maps_script .= 'channel=' . $channel . '&';
    }
    $this->attached['js'][$google_maps_script] = array(
      'data' => $google_maps_script,
      'type' => 'external',
      'group' => openlayers_config::JS_GROUP,
      'weight' => (openlayers_config::JS_WEIGHT - 1),
    );

    return parent::attached();
  }

}
