// $Id$

/**
 * @file
 * Layer handler for WMS layers
 */

/**
 * Openlayer layer handler for WMS layer
 */
Drupal.openlayers.layer.wms = function (title, map, options) {
  var styleMap = Drupal.openlayers.getStyleMap(map, options.drupalID);
  options.options.transparent = true;
  var layer = new OpenLayers.Layer.WMS(title, 
    options.base_url, options.options, options.params);
  layer.styleMap = styleMap;
  return layer;
};
