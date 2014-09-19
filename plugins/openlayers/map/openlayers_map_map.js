Drupal.openlayers.openlayers_map_map = function(options, map, context) {
  var projection = ol.proj.get('EPSG:3857');

  options.view = new ol.View({
    center: [options.view.center.lat, options.view.center.lon],
    rotation: options.view.rotation * (Math.PI/180),
    zoom: options.view.zoom,
    projection: projection,
    extent: projection.getExtent()
  });

  return new ol.Map(options);
};
