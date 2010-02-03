// $Id$

/**
 * @file
 * JS functions to handle different kinds of behaviors
 *
 * @ingroup openlayers
 */

/**
 * OL Tooltip Behavior
 *
 * @param event
 *   Event Object
 */
OL.Behaviors.tooltip = function(event) {
  var mapDef = event.mapDef;
  var mapid = mapDef.id;
  var map = event.map;
  var behavior = event.behavior;
  
  // Set up the hover triggers
  var layer = OL.maps[mapid].layers[behavior.layer];
  var options = {
    hover: true, 
    highlightOnly: true, 
    renderIntent: 'temporary', 
    eventListeners: {
      featurehighlighted: OL.Behaviors.tooltipOver, 
      featureunhighlighted: OL.Behaviors.tooltipOut
    }
  };
  layer.drupalData.tooltipData = behavior;
  OL.maps[mapid].controls[behavior.id] = new OpenLayers.Control.SelectFeature(layer, options);
  
  // Add control
  map.addControl(OL.maps[mapid].controls[behavior.id]);
  OL.maps[mapid].controls[behavior.id].activate();
  
  // Set up the HTML div from themed container
  $("#" + mapid).after(behavior.container);
}

/**
 * OL Tooltip Behavior - Hover Over Handler
 *
 * @param event
 *   Event Object
 */
OL.Behaviors.tooltipOver = function(event) {
  var feature = event.feature;
  var behavior = feature.layer.drupalData.tooltipData;
  var tooltipText = feature.attributes[behavior.attribute];
  var $textContainer = $('#' + behavior.attribute_id);

  // Put text into tooltip
  $textContainer.html(tooltipText);

  // Set the tooltip location
  var $tooltipContainer = $('#' + behavior.container_id);
  var centroid = OL.Behaviors.tooltipGetCentroid(feature.geometry.clone());
  var centroidPixel = feature.layer.map.getPixelFromLonLat(centroid);
  var mapDivOffset = $('#' + feature.layer.map.mapid).offset();
  var scrollTop = $(window).scrollTop();
  var scrollLeft = $(window).scrollLeft();
  
  // Show the tooltip
  $tooltipContainer.css('display', 'block');
  
  // How much should we offset the tooltip from the top. Valid options are numeric or 'height' or 'width'.
  if (behavior.offset_top !== undefined) {
    if (isNaN(behavior.offset_top)) {
      if (behavior.offset_top == 'height') {
        var offset_top = $tooltipContainer.height();
      }
      if (behavior.offset_top == 'width') {
        var offset_top = $tooltipContainer.width();
      }
    }
    else {
      var offset_top = behavior.offset_top
    }
  }
  else {
    offset_top = 0;
  }

  // How much should we offset the tooltip from the left. Valid options are numeric or 'height' or 'width'.
  if (behavior.offset_left !== undefined) {
    if (isNaN(behavior.offset_left)) {
      if (behavior.offset_left == 'height') {
        var offset_left = $tooltipContainer.height();
      }
      if (behavior.offset_left == 'width') {
        var offset_left = $tooltipContainer.width();
      }
    }
    else {
      var offset_left = behavior.offset_left
    }
  }
  else {
    var offset_left = 0;
  }
  
  var absoluteTop = centroidPixel.y + mapDivOffset.top - scrollTop - offset_top;
  var absoluteLeft = centroidPixel.x + mapDivOffset.left - scrollLeft - offset_left;
  
  // Create offset
  $tooltipContainer.css('top', absoluteTop).css('left', absoluteLeft)  
}

/**
 * OL Tooltip Behavior - Hover Out Handler
 *
 * @param event
 *   Event Object
 */
OL.Behaviors.tooltipOut = function(event) {
  var behavior = event.feature.layer.drupalData.tooltipData;
  $('#' + behavior.container_id).css('display','none');
}

/**
 * OL Tooltip Behavior - Get Centroid for Tooltip
 *
 * Help function to get Centroid
 *
 * @param event
 *   Event Object
 */
OL.Behaviors.tooltipGetCentroid = function(geometry) {
  if (geometry.CLASS_NAME == 'OpenLayers.Geometry.Polygon') {
    var firstCentroid = geometry.getCentroid();
    if (geometry.containsPoint(firstCentroid)) {
      // The polygon contains it's centroid, easy!
      var baseCentroid = firstCentroid;
    }
    else {    
      // The polygon is a funny shape and does not contain 
      // it's own centroid. Find the closest vertex to the centroid.
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
  else if (geometry.CLASS_NAME == 'OpenLayers.Geometry.LineString') {
    // Simply use the middle vertices as the centroid. One day 
    // we may want to take into account the lengths of the different segments
    var vertices = geometry.getVertices();
    var midVerticesIndex = Math.round((vertices.length -1) / 2);
    var baseCentroid = vertices[midVerticesIndex];
  }
  else if (geometry.CLASS_NAME == 'OpenLayers.Geometry.Point') {
    var baseCentroid = geometry.getCentroid();
  }
  return new OpenLayers.LonLat(baseCentroid.x, baseCentroid.y);
}
