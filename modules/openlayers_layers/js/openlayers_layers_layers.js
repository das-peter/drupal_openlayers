// $Id$

/**
 * @file
 *   JS functions to handle different kinds of layers
 */


/**
 * Process Google Layers
 */
function openlayersLayerHandlerGoogle(layerOptions, mapid) {
  var mapType;
  if (layerOptions.params.type == "street"){
    mapType = G_NORMAL_MAP;
  }
  else if (layerOptions.params.type == "satellite"){
   mapType = G_SATELLITE_MAP;
  }
  else if (layerOptions.params.type == "hybrid"){
    mapType = G_HYBRID_MAP;
  }
  else if (layerOptions.params.type == "physical"){
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


/**
 * Process Yahoo Layers
 */
function openlayersLayerHandlerYahoo(layerOptions, mapid) {
  var mapType;
  if (layerOptions.params.type == "street"){
    mapType = YAHOO_MAP_REG;
  }
  else if (layerOptions.params.type == "satellite"){
   mapType = YAHOO_MAP_SAT;
  }
  else if (layerOptions.params.type == "hybrid"){
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


/**
 * Process MS Virtual Earth Layers
 */
function openlayersLayerHandlerVirtualEarth(layerOptions, mapid) {
  var mapType;
  if (layerOptions.params.type == "street"){
    mapType = VEMapStyle.Road;
  }
  else if (layerOptions.params.type == "satellite"){
   mapType = VEMapStyle.Aerial;
  }
  else if (layerOptions.params.type == "hybrid"){
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


/**
 * Process OSM
 */
function openlayersLayerHandlerOSM(layerOptions, mapid) {
  
   var mapOptions = {
    sphericalMercator: true,
    maxExtent: new OpenLayers.Bounds(-20037508.34,-20037508.34,20037508.34,20037508.34)
  };
  
  jQuery.extend(mapOptions, layerOptions.options);
  
  var OSMLayer = new OpenLayers.Layer.OSM(
                layerOptions.name,
                layerOptions.url + "/${z}/${x}/${y}.png",
                mapOptions
  );

  return OSMLayer;
}