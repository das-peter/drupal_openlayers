Drupal.openlayers.openlayers_source_stamen = function(data) {

  var options = {
    layer: data.options.layer
  };

  return new ol.source.Stamen(options);
};
