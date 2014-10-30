Drupal.openlayers.openlayers__source__cluster = function(data) {

  for (source in data.cache.sources) {
    if (source === data.options.source) {
      var source = new ol.source.Cluster({
        distance: data.options.distance,
        source: data.cache.sources[source]
      });
      return source;
    }
  }

};
