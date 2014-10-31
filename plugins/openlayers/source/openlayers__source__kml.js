Drupal.openlayers.openlayers__source__kml = function(data) {
  data.options.projection = 'EPSG:3857';
  data.options.extractStyles = false;
  return new ol.source.KML(data.options);
};
