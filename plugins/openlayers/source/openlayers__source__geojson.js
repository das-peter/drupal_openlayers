Drupal.openlayers.openlayers__source__geojson = function(data) {
  data.options.projection = 'EPSG:3857';
  return new ol.source.GeoJSON(data.options);
};
