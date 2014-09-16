Drupal.openlayers.openlayers_source_stamen = function(options) {

  var options = {
    layer: options.layer
  };

  return new ol.source.Stamen(options);
};
