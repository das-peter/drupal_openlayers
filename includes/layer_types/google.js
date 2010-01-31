// $Id$

/**
 * Process Google Layers
 *
 * @param layerOptions
 *   Object of options
 * @param mapid
 *   Map ID
 * @return
 *   Valid OpenLayers layer
 */
Drupal.openlayers.layer.google = function (name, map, options) {
  var styleMap = Drupal.openlayers.getStyleMap(map, options.name);

  var google_type_map = {
    "normal": G_NORMAL_MAP,
    "satellite": G_SATELLITE_MAP,
    "hybrid": G_HYBRID_MAP,
    "physical": G_PHYSICAL_MAP
  };

  options.sphericalMercator = true;
  options.maxExtent = new OpenLayers.Bounds(-20037508.34,-20037508.34,20037508.34,20037508.34);
  options.type = google_type_map[options.type];

  var layer = new OpenLayers.Layer.Google(name, options);
  layer.styleMap = styleMap;
  return layer;
};
