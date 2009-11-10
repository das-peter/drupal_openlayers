/**
 * Process XYZ Layers
 *
 * @param layerOptions
 *   Object of options
 * @param mapid
 *   Map ID
 * @return
 *   Valid OpenLayers layer
 */
Drupal.openlayers.layer.xyz = function (name, map, options) {
  var styleMap = Drupal.openlayers.getStyleMap(map, options.name);

  options.sphericalMercator = true;
  options.maxExtent = new OpenLayers.Bounds(-20037508.34,-20037508.34,20037508.34,20037508.34);

  var layer = new OpenLayers.Layer.XYZ(name, options.base_url, options);
  layer.styleMap = styleMap;
  return layer;
};
