Drupal.openlayers.openlayers_component_bootstrapjs_popup = function(options, map) {

  jQuery("body").append("<div id='popup'></div>");

  var popup = new ol.Overlay({
    element: document.getElementById('popup'),
    positioning: 'bottom-center',
    stopEvent: false
  });
  map.addOverlay(popup);

  map.on('click', function(evt) {
    var feature = map.forEachFeatureAtPixel(evt.pixel,
      function(feature, layer) {
        return feature;
      });

    var element = popup.getElement();
    jQuery(element).popover('destroy');

    if (feature) {
      var geometry = feature.getGeometry();
      var coord = geometry.getCoordinates();

      jQuery(element).popover('destroy');

      jQuery(element).popover({
        'placement': 'top',
        'html': true,
        'title': feature.get('name'),
        'content': feature.get('description')
      });

      popup.setPosition(coord);
      jQuery(element).popover('show');
    }
  });

};
