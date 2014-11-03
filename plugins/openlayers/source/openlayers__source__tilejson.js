Drupal.openlayers.openlayers__source__tilejson = function(data) {

  if (data.options.attributions !== undefined) {
    data.options.attributions = [new ol.Attribution({
      'html': data.options.attributions
    })];
  }

  return new ol.source.TileJSON(data.options);
};
