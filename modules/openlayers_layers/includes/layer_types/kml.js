// $Id

/**
 * Process KML Layers
 *
 * @param layerOptions
 *   Object of options
 * @param mapid
 *   Map ID
 * @return
 *   Valid OpenLayers layer
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
