Drupal.openlayers.openlayers_component_bootstrapjs_popup = function(options, map) {

  jQuery("body").append("<div id='popup'></div>");

  var element = document.getElementById('popup');

  var popup = new ol.Overlay({
    element: element,
    positioning: 'bottom-center',
    stopEvent: false
  });
  map.addOverlay(popup);

  map.on('click', function(evt) {
    var feature = map.forEachFeatureAtPixel(evt.pixel,
      function(feature, layer) {
        return feature;
      });
    if (feature) {
      var geometry = feature.getGeometry();
      var coord = geometry.getCoordinates();
      popup.setPosition(coord);
      jQuery(element).popover({
        'placement': 'top',
        'html': true,
        'title': feature.get('name'),
        'content': feature.get('description')
      });
      jQuery(element).popover('show');
    } else {
      jQuery(element).popover('destroy');
    }
  });
};
