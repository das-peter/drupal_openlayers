<?php

function openlayers_default_interactions() {
  $export = array();

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_doubleclickzoom';
  $interaction->name = 'DoubleClickZoom';
  $interaction->description = 'DoubleClickZoom interaction description';
  $interaction->class = 'openlayers_interaction_doubleclickzoom';
  $interaction->options = array();
  $export['interaction_doubleclickzoom'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_draganddrop';
  $interaction->name = 'DragAndDrop';
  $interaction->description = 'DragAndDrop interaction description';
  $interaction->class = 'openlayers_interaction_draganddrop';
  $interaction->options = array();
  $export['interaction_draganddrop'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_dragbox';
  $interaction->name = 'DragBox';
  $interaction->description = 'DragBox interaction description';
  $interaction->class = 'openlayers_interaction_dragbox';
  $interaction->options = array();
  $export['interaction_dragbox'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_dragpan';
  $interaction->name = 'DragPan';
  $interaction->description = 'DragPan interaction description';
  $interaction->class = 'openlayers_interaction_dragpan';
  $interaction->options = array();
  $export['interaction_dragpan'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_dragrotate';
  $interaction->name = 'DragRotate';
  $interaction->description = 'DragRotate interaction description';
  $interaction->class = 'openlayers_interaction_dragrotate';
  $interaction->options = array();
  $export['interaction_dragrotate'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_dragrotateandzoom';
  $interaction->name = 'DragRotateAndZoom';
  $interaction->description = 'DragRotateAndZoom interaction description';
  $interaction->class = 'openlayers_interaction_dragrotateandzoom';
  $interaction->options = array();
  $export['interaction_dragrotateandzoom'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_dragzoom';
  $interaction->name = 'DragZoom';
  $interaction->description = 'DragZoom interaction description';
  $interaction->class = 'openlayers_interaction_dragzoom';
  $interaction->options = array();
  $export['interaction_dragzoom'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_draw';
  $interaction->name = 'Draw';
  $interaction->description = 'Draw interaction description';
  $interaction->class = 'openlayers_interaction_draw';
  $interaction->options = array();
  $export['interaction_draw'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_keyboardpan';
  $interaction->name = 'KeyboardPan';
  $interaction->description = 'KeyboardPan interaction description';
  $interaction->class = 'openlayers_interaction_keyboardpan';
  $interaction->options = array();
  $export['interaction_keyboardpan'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_keyboardzoom';
  $interaction->name = 'KeyboardZoom';
  $interaction->description = 'KeyboardZoom interaction description';
  $interaction->class = 'openlayers_interaction_keyboardzoom';
  $interaction->options = array();
  $export['interaction_keyboardzoom'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_modify';
  $interaction->name = 'Modify';
  $interaction->description = 'Modify interaction description';
  $interaction->class = 'openlayers_interaction_modify';
  $interaction->options = array();
  $export['interaction_modify'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_mousewheelzoom';
  $interaction->name = 'MouseWheelZoom';
  $interaction->description = 'MouseWheelZoom interaction description';
  $interaction->class = 'openlayers_interaction_mousewheelzoom';
  $interaction->options = array();
  $export['interaction_mousewheelzoom'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_pinchrotate';
  $interaction->name = 'PinchRotate';
  $interaction->description = 'PinchRotate interaction description';
  $interaction->class = 'openlayers_interaction_pinchrotate';
  $interaction->options = array();
  $export['interaction_pinchrotate'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_pinchzoom';
  $interaction->name = 'PinchZoom';
  $interaction->description = 'PinchZoom interaction description';
  $interaction->class = 'openlayers_interaction_pinchzoom';
  $interaction->options = array();
  $export['interaction_pinchzoom'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_pointer';
  $interaction->name = 'Pointer';
  $interaction->description = 'Pointer interaction description';
  $interaction->class = 'openlayers_interaction_pointer';
  $interaction->options = array();
  $export['interaction_pointer'] = $interaction;

  $interaction = new stdClass;
  $interaction->api_version = 1;
  $interaction->machine_name = 'interaction_select';
  $interaction->name = 'Select';
  $interaction->description = 'Select interaction description';
  $interaction->class = 'openlayers_interaction_select';
  $interaction->options = array();
  $export['interaction_select'] = $interaction;

  $interaction = new stdClass();
  $interaction->disabled = TRUE; /* Edit this to true to make a default interaction disabled initially */
  $interaction->api_version = 1;
  $interaction->machine_name = 'map_edit_form_values';
  $interaction->name = 'Map edit form values';
  $interaction->description = 'Provides values for the center, rotation and zoom in the map edit form.';
  $interaction->class = 'openlayers_interaction_setvalues';
  $interaction->options = array(
    'latitude' => 'edit-options-view-center-lat',
    'longitude' => 'edit-options-view-center-lon',
    'rotation' => 'edit-options-view-rotation',
    'zoom' => 'edit-options-view-zoom',
  );
  $export['map_edit_form_values'] = $interaction;

  return $export;
}
