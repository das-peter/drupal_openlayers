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

  /* TODO: have PHP take care of the casts here, not JS! */
  options.params.buffer = parseInt(options.params.buffer, 10);
  options.params.ratio = parseFloat(options.params.ratio);

  options.params.drupalID = options.drupalID;
  var layer = new OpenLayers.Layer.WMS(title, 
    options.base_url, options.options, options.params);
  layer.styleMap = styleMap;
  return layer;
};
