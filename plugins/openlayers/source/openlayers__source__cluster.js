Drupal.openlayers.openlayers__source__cluster = function(data) {

  for (source in data.cache.sources) {
    if (source === data.options.source) {

      if (data.options.attributions !== undefined) {
        data.options.attributions = [new ol.Attribution({
          'html': data.options.attributions
        })];
      }

      data.options.source = data.cache.sources[source];

      return new ol.source.Cluster(data.options);
    }
  }

};
