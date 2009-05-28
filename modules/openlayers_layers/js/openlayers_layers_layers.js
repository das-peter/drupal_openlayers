// $Id$

/**
 * @file
 * JS functions to handle different kinds of layers fo openlayers_layers module
 *
 * @ingroup openlayers
 */

/**
 * Process Google Layers
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

/**
 * Process Yahoo Layers
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

/**
 * Process MS Virtual Earth Layers
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

/**
 * Process KML Layers
 */
OL.Layers.KML = function(layerOptions, mapid) {
  
  var mapOptions = {
    projection: new OpenLayers.Projection("EPSG:4326"),
    format: OpenLayers.Format.KML,
    formatOptions: {extractStyles: true, extractAttributes: true}
  };
  
  jQuery.extend(mapOptions, layerOptions.options);
  
  var returnKML = new OpenLayers.Layer.GML(
    layerOptions.name, 
    layerOptions.url, 
    mapOptions
  );
  
  return returnKML;
}

/**
 * Process XYZ Layers
 */
OL.Layers.XYZ = function(layerOptions, mapid) {
  var mapOptions = {
    sphericalMercator: true,
    maxExtent: new OpenLayers.Bounds(-20037508.34,-20037508.34,20037508.34,20037508.34)
  };
  
  jQuery.extend(mapOptions, layerOptions.options);
  
  var returnXYZ = new OpenLayers.Layer.XYZ(layerOptions.name, layerOptions.url, mapOptions);
  return returnXYZ;
}