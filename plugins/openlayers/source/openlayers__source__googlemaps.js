Drupal.openlayers.openlayers__source__googlemaps = function(data) {

  var olMapDiv = jQuery(data.map.getViewport()).parent();
  var gmapDiv = jQuery('#gmap-' + olMapDiv.attr('id'));

  var gmap = new google.maps.Map(gmapDiv[0], {
    disableDefaultUI: true,
    keyboardShortcuts: false,
    draggable: false,
    disableDoubleClickZoom: true,
    scrollwheel: false,
    streetViewControl: false,
    mapTypeId: google.maps.MapTypeId[data.options.mapTypeId] || 'roadmap'
  });
  gmapDiv.data('gmap', gmap);

  data.map.getView().on('change:center', function() {
    var center = ol.proj.transform(data.map.getView().getCenter(), 'EPSG:3857', 'EPSG:4326');
    gmap.setCenter(new google.maps.LatLng(center[1], center[0]));
  });
  data.map.getView().on('change:resolution', function() {
    gmap.setZoom(data.map.getView().getZoom());
  });

  data.map.getView().setCenter(data.map.getView().getCenter());
  data.map.getView().setZoom(data.map.getView().getZoom());

  olMapDiv[0].parentNode.removeChild(olMapDiv[0]);
  gmap.controls[google.maps.ControlPosition.TOP_LEFT].push(olMapDiv[0]);

  return new ol.source.Vector();
};

/**
 * Helper to access the gmap instance in a ol.Map.
 */
Drupal.openlayers.openlayers__source__googlemaps_get_map = function(map){
  var olMapDiv = jQuery(map.getViewport()).parent();
  return jQuery('#gmap-' + olMapDiv.attr('id')).data('gmap');
}
