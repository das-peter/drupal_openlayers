Drupal.openlayers.openlayers_source_vector = function(data) {

  var format = new ol.format.WKT();
  var feature = format.readFeature(data.options.features);
  feature.getGeometry().transform('EPSG:4326', 'EPSG:3857');

  var options = {
    features: [feature]
  };

  return new ol.source.Vector(options);
};
