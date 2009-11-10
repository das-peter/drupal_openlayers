/**
 * Process MS Virtual Earth Layers
 *
 * @param layerOptions
 *   Object of options
 * @param mapid
 *   Map ID
 * @return
 *   Valid OpenLayers layer
 */
OL.Layers.VirtualEarth = function(layerOptions, mapid) {
  var mapType;
  if (layerOptions.params.type == "street") {
    mapType = VEMapStyle.Road;
  }
  else if (layerOptions.params.type == "satellite") {
   mapType = VEMapStyle.Aerial;
  }
  else if (layerOptions.params.type == "hybrid") {
    mapType = VEMapStyle.Hybrid;
  }
  
  var mapOptions = {
    type: mapType,
    sphericalMercator: true,
    maxExtent: new OpenLayers.Bounds(-20037508.34,-20037508.34,20037508.34,20037508.34)
  };
  
  jQuery.extend(mapOptions, layerOptions.options);
  
  var virtualEarthLayer = new OpenLayers.Layer.VirtualEarth(
    layerOptions.name, 
    mapOptions
  );
  return virtualEarthLayer;
}


