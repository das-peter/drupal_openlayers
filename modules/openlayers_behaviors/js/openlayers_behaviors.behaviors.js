
/**
 * @file
 * JS functions to handle different kinds of behaviors
 *
 * @ingroup openlayers
 */

function openlayersBehaviorsTooltip(event){
  var mapDef = event.mapDef;
  var mapid = mapDef.id;
  var map = event.map;
  var behavior = event.behavior;
  
  var layer = Drupal.openlayers.activeObjects[mapid].layers[behavior.layer];
  Drupal.openlayers.activeObjects[mapid].controls[behavior.id] = new OpenLayers.Control.SelectFeature(
    layer,
      {hover: true, onSelect: openlayersBehaviorsTooltipOver, onUnselect: openlayersBehaviorsTooltipOut}
  );
  map.addControl(Drupal.openlayers.activeObjects[mapid].controls[behavior.id]);
  Drupal.openlayers.activeObjects[mapid].controls[behavior.id].activate();
}

function openlayersBehaviorsTooltipOver(event){
  // Do something
}

function openlayersBehaviorsTooltipOut(event){
  // Do something
}


function openlayersBehaviorsZoomToLayer(event){
  var mapDef = event.mapDef;
  var mapid = mapDef.id;
  var map = event.map;
  var behavior = event.behavior;
  
  var layer = Drupal.openlayers.activeObjects[mapid].layers[behavior.layer];
  if (layer.features.length != 0){
    // Check to see if we are dealing with just a single point.
    if (layer.features.length == 1 && layer.features[0].geometry.getArea() == 0){
      var center = new OpenLayers.LonLat(layer.features[0].geometry.x, layer.features[0].geometry.y);
      // If pointZoom has been set, then center and zoom, else just center and don't zoom
      if (openlayersIsSet(behavior.pointZoom)){
        map.setCenter(center, mapDef.behaviors.pointZoom);
      }
      else{
        map.setCenter(center); 
      }
    }
    // Else we are dealing with either a polygon, a line, or multiple points, all of which have bounds to which we can zoom
    else{
      var extentToZoom = new OpenLayers.Bounds();
      // Go through the feautres of the layer, building out the bounds to which we wish to zoom.
      for (var f in layer.features){
        extentToZoom.extend(layer.features[f].geometry.getBounds());
      }
      // Zoom the map to the bounds of the layer
      map.zoomToExtent(extentToZoom);
    }
  }

}

function openlayersBehaviorsFeatureHighlight(event){
  // Do Something
}