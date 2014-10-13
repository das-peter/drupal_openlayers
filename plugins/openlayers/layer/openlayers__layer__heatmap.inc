<?php

function openlayers_openlayers__layer__heatmap_openlayers_layer() {
  return array(
    'handler' => array(
      'class' => 'openlayers__layer__heatmap',
      'file' => 'openlayers__layer__heatmap.inc',
    )
  );
}

class openlayers__layer__heatmap extends openlayers_layer {

  function options_form(&$form, &$form_state) {
    $form['options']['opacity'] = array(
      '#type' => 'textfield',
      '#description' => 'Opacity (0, 1). Default is 1.',
      '#default_value' => $this->getOption('opacity', 1),
    );
    $form['options']['preload'] = array(
      '#type' => 'textfield',
      '#description' => 'Preload. Load low-resolution tiles up to preload levels. By default preload is 0, which means no preloading.',
      '#default_value' => $this->getOption('preload', 1),
    );
  }

}
