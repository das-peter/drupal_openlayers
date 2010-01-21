// $Id$

/**
 * @file
 * Layer handler for TMS layers
 */

/**
 * Openlayer layer handler for TMS layer
 */
Drupal.openlayers.layer.tms = function (name, map, options) {
  var styleMap = Drupal.openlayers.getStyleMap(map, options.name);
    if (options.maxExtent !== undefined) {
      options.maxExtent = new OpenLayers.Bounds.fromArray(options.maxExtent);
    }
    if (options.type === undefined){
      options.type = "png";
    }
    options.projection = new OpenLayers.Projection('EPSG:'+options.projection);
    var layer = new OpenLayers.Layer.TMS(name, options.base_url, options);
    layer.styleMap = styleMap;
    return layer;
};
