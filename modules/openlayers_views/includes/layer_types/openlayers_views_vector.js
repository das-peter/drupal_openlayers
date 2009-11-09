Drupal.openlayers.layer.openlayers_views_vector = function (name, map, options) {
  var styleMap = Drupal.openlayers.getStyleMap(map, options.name);
    options.projection = new OpenLayers.Projection('EPSG:'+options.projection);
    //layer.styleMap = styleMap;
    var styleMap = Drupal.openlayers.getStyleMap(map, options.name);
    var layer = new OpenLayers.Layer.Vector(name, {'styleMap': styleMap});
    if (options.features) {
      Drupal.openlayers.addFeatures(map, layer, options.features);
    }
    return layer;
};
