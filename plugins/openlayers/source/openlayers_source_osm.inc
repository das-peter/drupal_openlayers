<?php

function openlayers_openlayers_source_osm_openlayers_source() {
  return array(
    'handler' => array(
      'class' => 'openlayers_source_osm',
      'file' => 'openlayers_source_osm.inc',
    )
  );
}

class openlayers_source_osm extends openlayers_source {
  function options_form($defaults = array()) {
    return array(
      'url' => array(
        '#type' => 'textarea',
        '#title' => t('Base URL (template)'),
        '#default_value' => $this->getOption('url') ? implode("\n", (array) $this->getOption('url')) : '',
        '#maxlength' => 2083,
      ),
    );
  }
}
