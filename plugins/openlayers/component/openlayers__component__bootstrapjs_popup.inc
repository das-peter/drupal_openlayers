<?php

function openlayers_openlayers__component__bootstrapjs_popup_openlayers_component() {
  return array(
    'handler' => array(
      'class' => 'openlayers__component__bootstrapjs_popup',
      'file' => 'openlayers__component__bootstrapjs_popup.inc',
    )
  );
}

class openlayers__component__bootstrapjs_popup extends openlayers_component {

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
