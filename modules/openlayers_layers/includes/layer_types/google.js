/**
 * Process Google Layers
 *
 * @param layerOptions
 *   Object of options
 * @param mapid
 *   Map ID
 * @return
 *   Valid OpenLayers layer
 */
OL.Layers.Google = function(layerOptions, mapid) {
  var mapType;
  if (layerOptions.params.type == "street") {
    mapType = G_NORMAL_MAP;
  }
  else if (layerOptions.params.type == "satellite") {
   mapType = G_SATELLITE_MAP;
  }
  else if (layerOptions.params.type == "hybrid") {
    mapType = G_HYBRID_MAP;
  }
  else if (layerOptions.params.type == "physical") {
    mapType = G_PHYSICAL_MAP;
  }
  
  var mapOptions = {
    type: mapType,
    sphericalMercator: true,
    maxExtent: new OpenLayers.Bounds(-20037508.34,-20037508.34,20037508.34,20037508.34)
  };
  
  jQuery.extend(mapOptions, layerOptions.options);
  
  var googleLayer = new OpenLayers.Layer.Google(
    layerOptions.name, 
    mapOptions
  );
  return googleLayer;
}


