
/**
 * @file
 * Layer handler for XYZ layers
 */

/**
 * Openlayer layer handler for XYZ layer
 */
Drupal.openlayers.layer.xyz = function(title, map, options) {
  var styleMap = Drupal.openlayers.getStyleMap(map, options.drupalID);
  if (options.maxExtent !== undefined) {
    options.maxExtent = new OpenLayers.Bounds.fromArray(options.maxExtent) || new OpenLayers.Bounds(-20037508.34, -20037508.34, 20037508.34, 20037508.34);
  }
  options.projection = 'EPSG:' + options.projection;
  
  // Server resolutions are very particular in OL 2.11
  var r = options.serverResolutions;
  if (r == null || typeof r == 'undefined' || r.length == 0) {
    options.serverResolutions = null;
  }

  var layer = new OpenLayers.Layer.XYZ(title, options.url, options);
  layer.styleMap = styleMap;
  return layer;
};