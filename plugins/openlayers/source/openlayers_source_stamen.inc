<?php

function openlayers_openlayers_source_stamen_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers_source_stamen',
    )
  );
}

class openlayers_source_stamen extends openlayers_source {

  function options_form() {
    return array(
      'layer' => array(
        '#title' => t('Source type'),
        '#type' => 'select',
        '#default_value' => $this->getOption('layer', 'osm'),
        '#options' => array(
          'terrain-labels' => 'Terrain labels',
          'watercolor' => 'Watercolor',
        )
      )
    );
  }

}
