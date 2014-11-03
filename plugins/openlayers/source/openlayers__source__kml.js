Drupal.openlayers.openlayers__source__kml = function(data) {

  if (data.options.attributions !== undefined) {
    data.options.attributions = [new ol.Attribution({
      'html': data.options.attributions
    })];
  }

  data.options.projection = 'EPSG:3857';
  data.options.extractStyles = false;
  return new ol.source.KML(data.options);
};
