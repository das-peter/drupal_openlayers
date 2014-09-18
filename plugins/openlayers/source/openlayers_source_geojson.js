Drupal.openlayers.openlayers_source_geojson = function(options, map) {
  options.projection = 'EPSG:3857';


  return new ol.source.GeoJSON(options);
};
