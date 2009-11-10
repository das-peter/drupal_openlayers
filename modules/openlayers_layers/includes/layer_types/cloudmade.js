/**
 * Process CloudMade Layers
 *
 * @param layerOptions
 *   Object of options
 * @param mapid
 *   Map ID
 * @return
 *   Valid OpenLayers layer
 */
OL.Layers.CloudMade = function(layerOptions, mapid) {
  // @@TODO: Check for CloudMade definition since it is in another file
  // Make sure there is options for a key
  if (OL.isSet(layerOptions.options)) {
    if (OL.isSet(layerOptions.options.key)) {
      var mapOptions = {
      };
      jQuery.extend(mapOptions, layerOptions.options);
    
      var cloudmade = new OpenLayers.Layer.CloudMade(layerOptions.name, layerOptions.options);
      return cloudmade;
    }
  }
}
