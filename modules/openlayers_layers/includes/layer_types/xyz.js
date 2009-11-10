/**
 * Process XYZ Layers
 *
 * @param layerOptions
 *   Object of options
 * @param mapid
 *   Map ID
 * @return
 *   Valid OpenLayers layer
 */
OL.Layers.XYZ = function(layerOptions, mapid) {
  var mapOptions = {
    sphericalMercator: true,
    maxExtent: new OpenLayers.Bounds(-20037508.34, -20037508.34, 20037508.34, 20037508.34)
  };
  
  jQuery.extend(mapOptions, layerOptions.options);
  
  var returnXYZ = new OpenLayers.Layer.XYZ(layerOptions.name, layerOptions.url, mapOptions);
  return returnXYZ;
}

