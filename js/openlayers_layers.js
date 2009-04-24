// $Id$

/**
 * @file
 * JS functions to handle different types of layers for core OpenLayers modules
 *
 * @ingroup openlayers
 */

/**
 * Process WMS Layers
 */
function openlayersLayerHandlerWMS(layerOptions, mapid) {
  // Check if there is a defined format
  if (typeof(layerOptions.params.format) == "undefined"){
    layerOptions.params.format = "image/png";
  }

  // Return Layer object
  return new OpenLayers.Layer.WMS(layerOptions.name, layerOptions.url, layerOptions.params, layerOptions.options);
}

/**
 * Process Vector Layers
 */
function openlayersLayerHandlerVector(layerOptions, mapid) {
  // Get styles
  var stylesAll = [];
  // Process Options
  if (typeof(layerOptions.options) != "undefined"){
    // Process Styles
    if (typeof(layerOptions.options.styles) != "undefined") {
      var stylesAdded = [];
      for (var styleName in layerOptions.options.styles) {
        stylesAdded[styleName] = new OpenLayers.Style(layerOptions.options.styles[styleName].options);
      }
      stylesAll = new OpenLayers.StyleMap(stylesAdded);
    };  
 }
  
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
  
  // Define layer object
  var returnVector = new OpenLayers.Layer.Vector(layerOptions.name, {styleMap: myStyles});
  
  // Add features if they are defined
  if (typeof(layerOptions.features) != "undefined") {
    var wktFormat = new OpenLayers.Format.WKT();
    var newFeatures = [];
    
    // Go through features
    for (var feat in layerOptions.features) {
      // Extract geometry either from wkt property or lon/lat properties
      if (typeof(layerOptions.features[feat].wkt) != "undefined"){
        var newFeature = wktFormat.read(layerOptions.features[feat].wkt);
      }
      else if (typeof(layerOptions.features[feat].lon) != "undefined"){
        var newFeature = wktFormat.read("POINT(" + layerOptions.features[feat].lon + " " + layerOptions.features[feat].lat + ")");
      }
      
      // If we have successfully extracted geometry add additional properties and queue it for addition to the layer
      if (typeof(newFeature) != 'undefined'){
        
        // @@TODO: transform feature is "projection" attribute is set.
        
        // Add attribute data
        if (typeof(layerOptions.features[feat].attributes) != "undefined"){
          newFeature.attributes = layerOptions.features[feat].attributes;
          newFeature.data = layerOptions.features[feat].attributes;
        }
        
        // Add style information
        if (typeof(layerOptions.features[feat].style) != "undefined"){
          // Merge with defaults
          var featureStyle = jQuery.extend({}, OpenLayers.Feature.Vector.style['default'], layerOptions.features[feat].style);
          // Add style to feature
          newFeature.style = featureStyle;
        }
        
        newFeatures.push(newFeature);
      }
    }
    
    if (newFeatures.length != 0){
      returnVector.addFeatures(newFeatures);
    }
  }
  
  return returnVector;
}