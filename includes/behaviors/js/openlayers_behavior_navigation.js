Drupal.behaviors.openlayers_behavior_navigation = function(context) {
  var data = $(context).data('openlayers');
  if (data && data.map.behaviors['openlayers_behavior_navigation']) {
    // Add control
    var control = new OpenLayers.Control.Navigation();
    data.openlayers.addControl(control);
    control.activate();
  }
}