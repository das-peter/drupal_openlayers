Drupal.openlayers.openlayers_source_imagestatic = function(options, map) {

  var pixelProjection = new ol.proj.Projection({
    code: 'pixel',
    units: 'pixels',
    extent: [0, 0, 1024, 968]
  });

  options.imageSize = [1024, 1024];
  options.projection = pixelProjection;
  options.imageExtent = pixelProjection.getExtent();

  map.setView(new ol.View({
    projection: pixelProjection,
    center: ol.extent.getCenter(pixelProjection.getExtent()),
    zoom: map.getView().getZoom()
  }));

  return new ol.source.ImageStatic(options);
};
