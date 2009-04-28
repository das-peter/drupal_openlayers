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
        
        var wkt;
        
        // Check to see if it is a string of wkt, or an array for a multipart feature.
        if (typeof(layerOptions.features[feat].wkt) == "string"){
          wkt = layerOptions.features[feat].wkt;
        }
        if (typeof(layerOptions.features[feat].wkt) == "object" && layerOptions.features[feat].wkt.length != 0){
          wkt = "GEOMETRYCOLLECTION(" + layerOptions.features[feat].wkt.join(',') + ")";
        }
        
        var newFeatureObject = wktFormat.read(wkt);
        
      }
      else if (typeof(layerOptions.features[feat].lon) != "undefined"){
        var newFeatureObject = wktFormat.read("POINT(" + layerOptions.features[feat].lon + " " + layerOptions.features[feat].lat + ")");    
      }
      
      // If we have successfully extracted geometry add additional properties and queue it for addition to the layer
      if (typeof(newFeatureObject) != 'undefined'){
        
        var newFeatureSet = [];
        
        // Check to see if it is a new feature, or an array of new features.
        if (typeof(newFeatureObject[0]) == 'undefined'){
          // It's an actual OpenLayers feature object.
          newFeatureSet[0] = newFeatureObject;
        }
        else{
          // It's an array of OpenLayers objects
          newFeatureSet = newFeatureObject;
        }
        
        for (var i in newFeatureSet){
          
          var newFeature = newFeatureSet[i];
          
          // Transform the geometry if the 'projection' property is different from the map projection
          if (typeof(layerOptions.features[feat].projection) != 'undefined'){
            if (layerOptions.features[feat].projection != Drupal.openlayers.mapDefs[mapid].projection){
              var featureProjection = new OpenLayers.Projection("EPSG:" + layerOptions.features[feat].projection);
              var mapProjection = Drupal.openlayers.activeObjects[mapid].projection;
              newFeature.geometry.transform(featureProjection,mapProjection);
            }
          }
          
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
    }
    
    if (newFeatures.length != 0){
      returnVector.addFeatures(newFeatures);
    }
  }
  
  return returnVector;
}