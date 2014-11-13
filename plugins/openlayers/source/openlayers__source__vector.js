Drupal.openlayers.openlayers__source__vector = function(data) {

  var options = {
    features: []
  };
  if (goog.isDef(data.options.features)) {
    // Ensure the features are really an array.
    if (!(data.options.features instanceof Array)) {
      data.options.features = [{geometry: data.options.features}];
    }
    var format = new ol.format.WKT();
    for (var i in data.options.features) {
      var data_projection = data.options.features[i].projection || 'EPSG:4326';
      var feature = format.readFeature(data.options.features[i].wkt, {
        dataProjection: data_projection,
        featureProjection: data.map.getView().getProjection()
      });
      if (goog.isDef(data.options.features[i].attributes)) {
        feature.setProperties(data.options.features[i].attributes);
      }
      options.features.push(feature);
    }
  }
  return new ol.source.Vector(options);
};
