Drupal.openlayers.openlayers__source__imagestatic = function(data) {
  var pixelProjection = new ol.proj.Projection({
    code: 'pixel',
    units: 'pixels',
    extent: [0, 0, 1024, 968]
  });

  data.options.imageSize = [1024, 1024];
  data.options.projection = pixelProjection;
  data.options.imageExtent = pixelProjection.getExtent();

  data.map.setView(new ol.View({
    projection: pixelProjection,
    center: ol.extent.getCenter(pixelProjection.getExtent()),
    zoom: data.map.getView().getZoom()
  }));

  return new ol.source.ImageStatic(data.options);
};
