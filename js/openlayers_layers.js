// $Id$

/**
 * @file
 *   JS functions to handle different kinds of layers
 */

/**
 * Process WMS Layers
 */
function openlayersLayerHandlerWMS(layerOptions, mapid) {
  var wmsOptions = {
    layers: layerOptions.params.layers,
  };
  var returnWMS = new OpenLayers.Layer.WMS(layerOptions.name, layerOptions.url, wmsOptions);
  return returnWMS;
}

/**
 * Process Vector Layers
 */
function openlayersLayerHandlerVector(layerOptions, mapid) {
  var stylesAll = [];
  if (layerOptions.options.styles) {
    var stylesAdded = [];
    for (var styleName in layerOptions.options.styles) {
      stylesAdded[styleName] = new OpenLayers.Style(layerOptions.options.styles[styleName].options);
    }
    stylesAll = new OpenLayers.StyleMap(stylesAdded);
  };
  
  // @@TODO: not be hard-coded
  var myStyles = new OpenLayers.StyleMap({
                "default": new OpenLayers.Style({
                    pointRadius: 5, // sized according to type attribute
                    fillColor: "#ffcc66",
                    strokeColor: "#ff9933",
                    strokeWidth: 4,
                    fillOpacity:0.5
                }),
                "select": new OpenLayers.Style({
                    fillColor: "#66ccff",
                    strokeColor: "#3399ff"
                })
    });
    
  var returnVector = new OpenLayers.Layer.Vector(layerOptions.name, {styleMap: myStyles});
  return returnVector;
}