<?php

function openlayers_openlayers_layer_tile_openlayers_layer() {
  return array(
    'handler' => array(
      'class' => 'openlayers_layer_tile',
    )
  );
}

class openlayers_layer_tile extends openlayers_layer {

  function options_form($defaults = array()) {
    return array(
      'url' => array(
        '#type' => 'textarea',
        '#title' => t('Base URL (template)'),
        '#default_value' => $this->getOption('url') ? implode("\n", (array) $this->getOption('url')) : '',
        '#maxlength' => 2083,
        '#description' => t('This is the base URL template for the XYZ layer.  It should be something similar to <em>http://example.com/tiles/1.0.0/layer_name/${z}/${x}/${y}.png</em>.'),
      ),
      'zoomOffset' => array(
        '#type' => 'select',
        '#description' => t('Zoom offset.'),
        '#options' => array_combine(
          range(0, 21),
          range(0, 21)),
        '#title' => t('Zoom offset'),
        '#default_value' => $this->getOption('zoomOffset')
      ),
      'wrapDateLine' => array(
        '#type' => 'checkbox',
        '#title' => t('Wrap Date Line'),
        '#default_value' => $this->getOption('wrapDateLine'),
        '#description' => t('This allows the user to continually pan left and right as the tiles will repeat themselves.  Note that this option is known to not work well with the 2.10 OL library.'),
      ),
    );
  }

}
