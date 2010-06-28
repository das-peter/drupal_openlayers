// $Id$

/**
 * @file
 * Layer handler for KML layers
 */

/**
 * Openlayer layer handler for KML layer
 */
Drupal.openlayers.layer.kml = function(title, map, options) {
  // Get styles
  var styleMap = Drupal.openlayers.getStyleMap(map, options.drupalID);
  
  // Format options
  if (options.maxExtent !== undefined) {
    options.maxExtent = OpenLayers.Bounds.fromArray(options.maxExtent);
  }

  // Create layer
  var layer = new OpenLayers.Layer.Vector(
    title, 
    {
    strategies: [new OpenLayers.Strategy.Fixed()],
    protocol: new OpenLayers.Protocol.HTTP({
        url: options.url, 
        format: new OpenLayers.Format.KML(
          options.formatOptions
        )
      })
    }
  );
  layer.styleMap = styleMap;
  return layer;
};
