// $Id$

/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * Zoom to Layer Behavior
 */
Drupal.behaviors.openlayers_behavior_zoomtolayer = function(context) {
 var data = $(context).data('openlayers');
 if (data && data.map.behaviors['openlayers_behavior_zoomtolayer']) {
     Drupal.openlayers_behavior_zoomtolayer.zoom(data);
  }
}

Drupal.openlayers_behavior_zoomtolayer = {
  'zoom': function(data) {    
    var zoomlayer = data.map.behaviors.openlayers_behavior_zoomtolayer.zoomtolayer;
    var layer = data.map.layers[zoomlayer];  
    if (layer.features.length != 0) {
     // Check to see if we are dealing with just a single point.
     if (layer.features.length == 1) {
       var point = new OpenLayers.Geometry.fromWKT(layer.features[0].wkt);
       point.transform(new OpenLayers.Projection('EPSG:' + layer.features[0].projection), data.openlayers.projection);
       var center = new OpenLayers.LonLat(point.x, point.y);
       data.openlayers.setCenter(center);  
     }
     // Else we are dealing with multiple points
     else {
       var extentToZoom = new OpenLayers.Bounds();
       // Go through the features of the layer, building out the bounds to which we wish to zoom.
       for (var f in layer.features) {
         var point = new OpenLayers.Geometry.fromWKT(layer.features[f].wkt);
         point.transform(new OpenLayers.Projection('EPSG:' + layer.features[f].projection), data.openlayers.projection);
         extentToZoom.extend(point);   
       }
       // Zoom the map to the bounds of the layer
       data.openlayers.zoomToExtent(extentToZoom);
     }
   }
 }
}