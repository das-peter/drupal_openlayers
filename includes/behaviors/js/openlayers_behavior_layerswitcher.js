Drupal.behaviors.openlayers_behavior_layerswitcher = function(context) {
  var data = $(context).data('openlayers');
  if (data && data.map.behaviors['openlayers_behavior_layerswitcher']) {
    // Add control
    var control = new OpenLayers.Control.LayerSwitcher();
    data.openlayers.addControl(control);
    control.activate();
  }
}