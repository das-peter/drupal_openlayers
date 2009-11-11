/**
 * Process MS Virtual Earth Layers
 *
 * @param layerOptions
 *   Object of options
 * @param mapid
 *   Map ID
 * @return
 *   Valid OpenLayers layer
 */
Drupal.openlayers.layer.virtualearth = function (name, map, options) {
  var styleMap = Drupal.openlayers.getStyleMap(map, options.name);

  virtualearth_type_map = {
    "street": VEMapStyle.Road,
    "satellite": VEMapStyle.Aerial,
    "hybrid": VEMapStyle.Hybrid,
  };

  options.sphericalMercator = true;
  options.maxExtent = new OpenLayers.Bounds(-20037508.34,-20037508.34,20037508.34,20037508.34);
  options.type = virtualearth_type_map[options.type];

  var layer = new OpenLayers.Layer.VirtualEarth(name, options);
  layer.styleMap = styleMap;
  return layer;
};
