// $Id$

/**
 * @file
 * Layer handler for KML layers
 */

/**
 * Openlayer layer handler for KML layer
 */
Drupal.openlayers.layer.kml = function(name, map, options) {
  // Get styles
  var styleMap = Drupal.openlayers.getStyleMap(map, name);
  
console.log(options);
  // Format options
  if (options.maxExtent !== undefined) {
    options.maxExtent = new OpenLayers.Bounds.fromArray(options.maxExtent) || new OpenLayers.Bounds(-20037508.34, -20037508.34, 20037508.34, 20037508.34);
  }
  options.format = OpenLayers.Format.KML;
  var layer_projection = options.custom_projection || options.projection;
  options.projection = new OpenLayers.Projection('EPSG:' + layer_projection);
  
  // Create layer
  var layer = new OpenLayers.Layer.GML('KML', options.url, options);
  layer.styleMap = styleMap;
  return layer;
};