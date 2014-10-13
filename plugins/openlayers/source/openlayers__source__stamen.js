Drupal.openlayers.openlayers__source__stamen = function(data) {

  var options = {
    layer: data.options.layer
  };

  return new ol.source.Stamen(options);
};
