
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
  
  
  // Set up the hover triggers
  var layer = Drupal.openlayers.activeObjects[mapid].layers[behavior.layer];
  layer.drupalData.tooltipAttribute = behavior.attribute;
  Drupal.openlayers.activeObjects[mapid].controls[behavior.id] = new OpenLayers.Control.SelectFeature(
    layer,
      {hover: true, onSelect: openlayersBehaviorsTooltipOver, onUnselect: openlayersBehaviorsTooltipOut}
  );
  map.addControl(Drupal.openlayers.activeObjects[mapid].controls[behavior.id]);
  Drupal.openlayers.activeObjects[mapid].controls[behavior.id].activate();
  
  // Set up the HTML div
  $("#"+mapid).after('<div id="'+ mapid +'-tooltip" class="openlayers-behaviors-tooltip"><img class="openlayers-behaviors-pointy" src="'+ Drupal.settings.basePath + behavior.pointy_path +'" alt="pointy" /><span id="'+ mapid +'-tooltip-text"></span></div>');
  
}

function openlayersBehaviorsTooltipOver(feature){ 
  var tooltipText = feature.attributes[feature.layer.drupalData.tooltipAttribute];
  $('#'+ feature.layer.map.mapid + "-tooltip-text").html(tooltipText);
  
  
  // Set the tooltip location
  var centroid = openlayersBehaviorsTooltipGetCentroid(feature.geometry.clone());
  var centroidPixel = feature.layer.map.getPixelFromLonLat(centroid);
  var mapDivOffset = $('#'+feature.layer.map.mapid).offset();
  var scrollTop = $(window).scrollTop();
  var scrollLeft = $(window).scrollLeft();
  
  // @@TODO: Can this -12 and -30 put in openlayers_behavior.css and then be read out and into this script? This would allow easier styling
  var absoluteTop = centroidPixel.y + mapDivOffset.top - scrollTop -30;
  var absoluteLeft = centroidPixel.x + mapDivOffset.left - scrollLeft -12;
  $('#'+ feature.layer.map.mapid + "-tooltip").css('top',absoluteTop).css('left',absoluteLeft).css('display','block');
}

function openlayersBehaviorsTooltipOut(feature){
  $('#'+ feature.layer.map.mapid + "-tooltip").css('display','none');
}

function openlayersBehaviorsTooltipGetCentroid(geometry){
  if (geometry.CLASS_NAME == 'OpenLayers.Geometry.Polygon'){
    var firstCentroid = geometry.getCentroid();
    if (geometry.containsPoint(firstCentroid)){
      // The polygon contains it's centroid, easy!
      var baseCentroid = firstCentroid;
    }else{    
      // The polygon is a funny shape and does not contain it's own centroid. Find the closest vertex to the centroid.
      var vertices = geometry.getVertices();
      var minDistance;
      for (var v in vertices){
        var distance = vertices[v].distanceTo(firstCentroid);
        if (distance < minDistance || v == 0){
          minDistance = distance;
          var closestVertices = vertices[v];
        }
      }
     var baseCentroid = closestVertices;
    }

  }
  else if (geometry.CLASS_NAME == 'OpenLayers.Geometry.LineString'){
    // Simply use the middle vertices as the centroid. One day we may want to take into account the lengths of the different segments
    var vertices = geometry.getVertices();
    var midVerticesIndex = Math.round((vertices.length -1) / 2);
    var baseCentroid = vertices[midVerticesIndex];
  }
  else if (geometry.CLASS_NAME == 'OpenLayers.Geometry.Point'){
    var baseCentroid = geometry.getCentroid();
  }
  return new OpenLayers.LonLat(baseCentroid.x, baseCentroid.y);
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