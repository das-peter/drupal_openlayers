// $Id$

/**
 * @file
 * Layer handler for OSM layers
 */

/**
 * Openlayer layer handler for OSM layer
 */
Drupal.openlayers.layer.osm = function (name, map, options) {
  var styleMap = Drupal.openlayers.getStyleMap(map, options.name);
    if (options.maxExtent !== undefined) {
      options.maxExtent = new OpenLayers.Bounds.fromArray(options.maxExtent);
    }
    if (options.type === undefined){
      options.type = "png";
    }
    options.projection = new OpenLayers.Projection('EPSG:'+options.projection);
    var layer = new OpenLayers.Layer.OSM(name, options.base_url, options);
    layer.styleMap = styleMap;
    return layer;
};
