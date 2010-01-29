/**
 * Process CloudMade Layers
 *
 * @param layerOptions
 *   Object of options
 * @param mapid
 *   Map ID
 * @return
 *   Valid OpenLayers layer
 */
Drupal.openlayers.layer.cloudmade = function (name, map, options) {
  var styleMap = Drupal.openlayers.getStyleMap(map, options.name);

  // options.sphericalMercator = true;
  options.maxExtent = new OpenLayers.Bounds(-20037508.34,-20037508.34,20037508.34,20037508.34);
  options.projection = new OpenLayers.Projection('EPSG:'+options.projection);

  var layer = new OpenLayers.Layer.CloudMade(name, options);
  layer.styleMap = styleMap;
  return layer;
};
