Drupal.openlayers.openlayers__source__vector = function(data) {

  var format = new ol.format.WKT();
  var feature = format.readFeature(data.options.features);
  feature.getGeometry().transform('EPSG:4326', 'EPSG:3857');

  var options = {
    features: [feature]
  };

  if (data.options.attributions !== undefined) {
    options.attributions = [new ol.Attribution({
      'html': data.options.attributions
    })];
  }

  return new ol.source.Vector(options);
};
