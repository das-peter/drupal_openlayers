Drupal.openlayers.openlayers__source__imagevector = function(data) {

  for (source in data.cache.sources) {
    if (source === data.options.source) {
      data.options.source = data.cache.sources[source];
      return new ol.source.ImageVector(data.options);
    }
  }

};
