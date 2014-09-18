<?php

function openlayers_openlayers_component_bootstrapjs_popup_openlayers_component() {
  return array(
    'handler' => array(
      'class' => 'openlayers_component_bootstrapjs_popup',
      'file' => 'openlayers_component_bootstrapjs_popup.inc',
    )
  );
}

class openlayers_component_bootstrapjs_popup extends openlayers_component {

  function attached() {
    $attached = parent::attached();
    $attached['libraries_load'][] = array('bootstrapjs');
    return $attached;
  }

  function dependencies() {
    return array(
      'bootstrapjs'
    );
  }

}
