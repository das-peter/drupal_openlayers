Drupal.openlayers.openlayers__source__osm = function(data) {

  if (data.options.attributions !== undefined) {
    data.options.attributions = [new ol.Attribution({
      'html': data.options.attributions
    })];
  }

  return new ol.source.OSM(data.options);
};
