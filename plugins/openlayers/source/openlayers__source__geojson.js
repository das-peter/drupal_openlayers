Drupal.openlayers.openlayers__source__geojson = function(data) {

  if (data.options.attributions !== undefined) {
    data.options.attributions = [new ol.Attribution({
      'html': data.options.attributions
    })];
  }

  data.options.projection = 'EPSG:3857';

  return new ol.source.GeoJSON(data.options);
};
