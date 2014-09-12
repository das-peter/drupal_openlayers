<?php

function openlayers_openlayers_layer_heatmap_openlayers_layer() {
  return array(
    'handler' => array(
      'class' => 'openlayers_layer_heatmap',
    )
  );
}

class openlayers_layer_heatmap extends openlayers_layer {

  function options_form($defaults = array()) {
    return array(
      'opacity' => array(
        '#type' => 'textfield',
        '#description' => 'Opacity (0, 1). Default is 1.',
        '#default_value' => $this->getOption('opacity', 1),
      ),
      'preload' => array(
        '#type' => 'textfield',
        '#description' => 'Preload. Load low-resolution tiles up to preload levels. By default preload is 0, which means no preloading.',
        '#default_value' => $this->getOption('preload', 1),
      )
    );
  }

}
