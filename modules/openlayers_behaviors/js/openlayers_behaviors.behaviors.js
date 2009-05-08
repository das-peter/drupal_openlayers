
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

/**
 * Process Draw Features. 
 *
 * This is for marking vector layers as editable. 
 * This function will add standard functionality for adding and editing features.
 * This function does no *do* anything with the features other than allow them to be drawn, edited and deleted by the interface. 
 * Use featureadded_handler, featuremodified_handler and featureremoved_handler if you wish to do something with the drawn/edited/deleted features.
 */
function openlayersBehaviorsDrawFeatures(event) {
  var mapDef = event.mapDef;
  var mapid = mapDef.id;
  var behavior = event.behavior;  
  
  // Add Base Pan button
  // @@TODO: Make this out put a themed item in PHP
  $('#openlayers-controls-' + mapid).append('<a href="#" id="openlayers-controls-pan-' + mapid + '" class="openlayers-controls-draw-feature-link openlayers-controls-draw-feature-link-pan openlayers-controls-draw-feature-link-on" rel="type:pan;mapid:' + mapid + '"></a>');
  
  // Get the OpenLayers layer object that will be editable.
  var layer = Drupal.openlayers.activeObjects[mapid].layers[behavior.layer];
    
  // Determine what handler we need to use.
  if (behavior.feature_type == 'point')       var handler = OpenLayers.Handler.Point;
  if (behavior.feature_type == 'path')        var handler = OpenLayers.Handler.Path;
  if (behavior.feature_type == 'polygon')     var handler = OpenLayers.Handler.Polygon;
  
  // Create our conrols and attach them to our layer.
  var createControl = new OpenLayers.Control.DrawFeature(layer, handler);  
  var modifyControl = new OpenLayers.Control.ModifyFeature(layer, {deleteCodes:[68]});
  
  Drupal.openlayers.activeObjects[mapid].map.addControl(createControl);
  Drupal.openlayers.activeObjects[mapid].map.addControl(modifyControl);

  //Disable the active mode by default.  This could be changed if we wanted people to draw on the map immediately.
  createControl.activeByDefault = false;
  modifyControl.activeByDefault = false;
  
  //Mark on the control what it is for drawing (point, path, or polygon)
  createControl.drupalDrawType = behavior.feature_type;
  modifyControl.drupalDrawType = behavior.feature_type;
  
  // Add our create and modify controls to the controls object.
  // Use a # prefix since these are special controls created by drawFeatures.
  Drupal.openlayers.activeObjects[mapid].controls['#create-' + behavior.feature_type] = createControl;
  Drupal.openlayers.activeObjects[mapid].controls['#modify-' + behavior.feature_type] = modifyControl;
  
  // Add special event handlers to controls
  if (behavior.featureadded_handler) {
    for (var ev in behavior.featureadded_handler){
      createControl.events.register('featureadded',createControl,window[behavior.featureadded_handler[ev]]);
    }
  }
     
  if (behavior.featuremodified_handler) {
    for (var ev in behavior.featuremodified_handler){ 
      layer.events.register('afterfeaturemodified',layer,window[behavior.featuremodified_handler[ev]]);
    }
  }
  
  if (behavior.featureremoved_handler) {
    for (var ev in behavior.featureremoved_handler){ 
      layer.events.register('beforefeatureremoved',layer,window[behavior.featureremoved_handler[ev]]);
    }
    
    // If a user presses the delete key, delete the currently selected polygon. 
    // This will in turn trigger the featureremoved_handler function. 
    $(document).keydown(function(event) {
      vKeyCode = event.keyCode;
      // If it is the Mac delete key (63272), or regular delete key (46) delete all selected features for the active map.
      if ((vKeyCode == 63272) || vKeyCode == 46) {
        for (var m in Drupal.openlayers.activeObjects){
          if (Drupal.openlayers.activeObjects[m].active == true){
            for (var b in Drupal.openlayers.mapDefs[m].behaviors){
              var behavior = Drupal.openlayers.mapDefs[m].behaviors[b];
              if (behavior.type == 'openlayers_behaviors_draw_features'){
                var featureToErase = Drupal.openlayers.activeObjects[m].layers[behavior.layer].selectedFeatures[0];
                Drupal.openlayers.activeObjects[m].layers[behavior.layer].destroyFeatures([featureToErase]);
                // Reload the modification control so we dont have ghost control points from the recently deceased feature
                Drupal.openlayers.activeObjects[m].controls['#modify-' + behavior.feature_type].deactivate();
                Drupal.openlayers.activeObjects[m].controls['#modify-' + behavior.feature_type].activate();
              }
            }
          }
        }
      }
    });
    
  }
      
  // Add action link (button)
  // We store the type and associated mapid in the rel attribute.
  // @@TODO: Make this out put a themed item in PHP, might need a placeholder for dF
  $('#openlayers-controls-' + mapid).append('<a href="#" id="openlayers-controls-draw-' + behavior.feature_type + '-' + mapid + '" class="openlayers-controls-draw-feature-link openlayers-controls-draw-feature-link-' + behavior.feature_type + ' openlayers-controls-draw-feature-link-off" rel="type:' + behavior.feature_type + ';mapid:' + mapid + ';behaviorid:' + behavior.id + '"></a>');
}

function openlayersBehaviorsDrawFeaturesMapReady(event){
  // Add click event to the action link (button)
  $('.openlayers-controls-draw-feature-link').click(
    function() {
      // Grab the mapid and the type from the rel attribute.
      var parsedRel = openlayersParseRel($(this).attr('rel'));
      
      // Change the look of the action link
      $('.openlayers-controls-draw-feature-link').removeClass('openlayers-controls-draw-feature-link-on');
      $('.openlayers-controls-draw-feature-link').addClass('openlayers-controls-draw-feature-link-off');
      $(this).addClass('openlayers-controls-draw-feature-link-on');
      $(this).removeClass('openlayers-controls-draw-feature-link-off');
      
      // Cycle through the different possible types of controls (polygon, line, point, pan)
      for (var b in Drupal.openlayers.mapDefs[parsedRel['mapid']].behaviors){
        var behavior  = Drupal.openlayers.mapDefs[parsedRel['mapid']].behaviors[b];
        if (behavior.type == 'openlayers_behaviors_draw_features'){
                    
          var createControl = Drupal.openlayers.activeObjects[parsedRel['mapid']].controls['#create-' + behavior.feature_type];
          var modifyControl = Drupal.openlayers.activeObjects[parsedRel['mapid']].controls['#modify-' + behavior.feature_type];
          
          // Deactivate everything
          createControl.deactivate();
          modifyControl.deactivate();
            
          // Activate it if it matches
          if (parsedRel['type'] == behavior.feature_type){
            createControl.activate();
            modifyControl.activate();
          }
        }
      }
      return false;
    }
  );
}