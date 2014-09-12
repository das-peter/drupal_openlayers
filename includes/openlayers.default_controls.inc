<?php

function openlayers_default_controls() {
  $export = array();

  $control = new stdClass;
  $control->api_version = 1;
  $control->machine_name = 'control_attribution';
  $control->name = 'Attribution';
  $control->description = 'Attribution control description';
  $control->class = 'openlayers_control_attribution';
  $control->options = array(
    'collapsible' => 1,
  );
  $export['control_attribution'] = $control;

  $control = new stdClass;
  $control->api_version = 1;
  $control->machine_name = 'control_fullscreen';
  $control->name = 'Fullscreen';
  $control->description = 'Fullscreen control description';
  $control->class = 'openlayers_control_fullscreen';
  $control->options = array();
  $export['control_fullscreen'] = $control;

  $control = new stdClass;
  $control->api_version = 1;
  $control->machine_name = 'control_mouseposition';
  $control->name = 'Mouse position';
  $control->description = 'Mouse position control description';
  $control->class = 'openlayers_control_mouseposition';
  $control->options = array();
  $export['control_mouseposition'] = $control;

  $control = new stdClass;
  $control->api_version = 1;
  $control->machine_name = 'control_rotate';
  $control->name = 'Rotate';
  $control->description = 'Rotate control description';
  $control->class = 'openlayers_control_rotate';
  $control->options = array();
  $export['control_rotate'] = $control;

  $control = new stdClass;
  $control->api_version = 1;
  $control->machine_name = 'control_scaleline';
  $control->name = 'Scaleline';
  $control->description = 'Scaleline control description';
  $control->class = 'openlayers_control_scaleline';
  $control->options = array();
  $export['control_scaleline'] = $control;

  $control = new stdClass;
  $control->api_version = 1;
  $control->machine_name = 'control_zoom';
  $control->name = 'Zoom';
  $control->description = 'Zoom control description';
  $control->class = 'openlayers_control_zoom';
  $control->options = array();
  $export['control_zoom'] = $control;

  $control = new stdClass;
  $control->api_version = 1;
  $control->machine_name = 'control_zoomslider';
  $control->name = 'Zoom slider';
  $control->description = 'Zoom slider control description';
  $control->class = 'openlayers_control_zoomslider';
  $control->options = array();
  $export['control_zoomslider'] = $control;

  $control = new stdClass;
  $control->api_version = 1;
  $control->machine_name = 'control_zoomtoextent';
  $control->name = 'Zoom to extent';
  $control->description = 'Zoom to extent control description';
  $control->class = 'openlayers_control_zoomtoextent';
  $control->options = array();
  $export['control_zoomtoextent'] = $control;

  return $export;
}
