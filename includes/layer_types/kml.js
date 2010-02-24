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
  
  // Format options
  if (options.maxExtent !== undefined) {
    options.maxExtent = OpenLayers.Bounds.fromArray(options.maxExtent);
  }

  options.format = OpenLayers.Format.KML;
  options.projection = new OpenLayers.Projection('EPSG:4326');
  
  // Create layer
  var layer = new OpenLayers.Layer.GML(name, options.url, options);
  layer.styleMap = styleMap;
  return layer;
};
