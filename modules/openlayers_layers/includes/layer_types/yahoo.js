/**
 * Process Yahoo Layers
 *
 * @param layerOptions
 *   Object of options
 * @param mapid
 *   Map ID
 * @return
 *   Valid OpenLayers layer
 */
OL.Layers.Yahoo = function(layerOptions, mapid) {
  var mapType;
  if (layerOptions.params.type == "street") {
    mapType = YAHOO_MAP_REG;
  }
  else if (layerOptions.params.type == "satellite") {
   mapType = YAHOO_MAP_SAT;
  }
  else if (layerOptions.params.type == "hybrid") {
    mapType = YAHOO_MAP_HYB;
  }
  
  var mapOptions = {
    type: mapType,
    sphericalMercator: true,
    maxExtent: new OpenLayers.Bounds(-20037508.34,-20037508.34,20037508.34,20037508.34)
  };
  
  jQuery.extend(mapOptions, layerOptions.options);
  
  var yahooLayer = new OpenLayers.Layer.Yahoo(
    layerOptions.name, 
    mapOptions
  );
  return yahooLayer;
}


