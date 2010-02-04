// $Id$

/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * Map Form Values Behavior
 */
Drupal.behaviors.openlayers_behavior_mapformvalues = function(context) {
  var data = $(context).data('openlayers');
  function updateForm(evt) {
    center = evt.object.getCenter().transform(
      evt.object.projection, 
      new OpenLayers.Projection('EPSG:4326')).toShortString();
    zoom = evt.object.getZoom();
    $('#edit-center-initial-centerpoint').val(center);
    $('#edit-center-initial-zoom').val(zoom);
  }
  if (data && data.map.behaviors['openlayers_behavior_mapformvalues']) {
    // Add control
    center_point = $('#edit-center-initial-centerpoint').val();
    zoom = $('#edit-center-initial-zoom').val();
    data.openlayers.setCenter(
      OpenLayers.LonLat.fromString(center_point).transform(
        new OpenLayers.Projection('EPSG:4326'),
        data.openlayers.projection)
      );
    data.openlayers.zoomTo(parseInt(zoom));
    data.openlayers.events.on({'moveend': updateForm});
  }
}
