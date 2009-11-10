Drupal.openlayers.layer.wms = function (name, map, options) {
  var styleMap = Drupal.openlayers.getStyleMap(map, name);
  if (options.maxExtent !== undefined) {
    options.maxExtent = new OpenLayers.Bounds.fromArray(options.maxExtent);
  }
  if (options.type === undefined){
    options.type = "png";
  }
  options.projection = new OpenLayers.Projection('EPSG:'+options.projection);
  var layer = new OpenLayers.Layer.WMS(name, options.url, options.params, options);
  layer.styleMap = styleMap;
  return layer;
};
