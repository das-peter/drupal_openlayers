Drupal.behaviors.openlayers_behavior_mapformvalues = function(context) {
  var data = $(context).data('openlayers');
  function updateForm(evt) {
    center = evt.object.getCenter().toShortString();
    zoom = evt.object.getZoom();
    $('#edit-center-initial-centerpoint').val(center);
    $('#edit-center-initial-zoom').val(zoom);
  }
  if (data && data.map.behaviors['openlayers_behavior_mapformvalues']) {
    // Add control
    center_point = $('#edit-center-initial-centerpoint').val();
    zoom = $('#edit-center-initial-zoom').val();
    data.openlayers.setCenter(new OpenLayers.LonLat.fromString(center_point));
    data.openlayers.zoomTo(parseInt(zoom));
    data.openlayers.events.on({'moveend': updateForm});
  }
}
