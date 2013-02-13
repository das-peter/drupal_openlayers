
/**
 * @file
 * Layer handler for WMS layers
 */

/**
 * Openlayer layer handler for WMS layer
 */
Drupal.openlayers.layer.wms = function(title, map, options) {
  var styleMap = Drupal.openlayers.getStyleMap(map, options.drupalID);

  /* TODO: have PHP take care of the casts here, not JS! */
  if (options.params.buffer) {
    options.params.buffer = parseInt(options.params.buffer, 10);
  }
  if (options.params.ratio) {
    options.params.ratio = parseFloat(options.params.ratio);
  }

  options.params.drupalID = options.drupalID;
  
  // Set isBaseLayer explicitly so that OpenLayers does not guess from transparency
  options.params.isBaseLayer = Boolean(options.isBaseLayer);
  
  // Convert to representation that match with WMS specification
  var optionsClone = jQuery.extend(true, {}, options.options);
  if(optionsClone.hasOwnProperty("TRANSPARENT") && optionsClone.TRANSPARENT===0){
    optionsClone.TRANSPARENT = "FALSE";
  }
  if(optionsClone.hasOwnProperty("TRANSPARENT") && optionsClone.TRANSPARENT===1){
    optionsClone.TRANSPARENT = "FALSE";
  }
  
  var layer = new OpenLayers.Layer.WMS(title,
    options.base_url, optionsClone, options.params);
  layer.styleMap = styleMap;
  return layer;
};
