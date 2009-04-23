// $Id$

/**
 * When document is ready for JS
 */
jQuery(document).ready(function() {
  // Store rendered maps and other OpenLayer objects in Drupal.openlayers.activeObjects
  Drupal.openlayers = {}
  Drupal.openlayers.activeObjects = [];
  Drupal.openlayers.mapDefs = Drupal.settings.openlayers.maps;
  
  // Go through array and make maps
  for (var i in Drupal.openlayers.mapDefs) {
    var map = Drupal.openlayers.mapDefs[i];
    // Check to see if there is a div on the page ready for the map. If there is then proceed.
    if ($('#' + map.id).length > 0) {
      // Make div the right dimensions and add custom controls
      $('#' + map.id).css('width', map.width).css('height', map.height);
      $('#' + map.id).after('<div class="openlayers-controls" id="openlayers-controls-' + map.id + '"></div>');
      $('#openlayers-controls-' + map.id).css("position","relative").css("bottom",map.height);
      
      // Set-up our registry of active OpenLayers javascript objects for this particular map.
      Drupal.openlayers.activeObjects[map.id] = {};
      
      // Set up places for us to store layers, controls, etc.
      Drupal.openlayers.activeObjects[map.id].controls = [];
      Drupal.openlayers.activeObjects[map.id].layers = [];
      Drupal.openlayers.activeObjects[map.id].active = false;

      // Render Map
      openlayersRenderMap(Drupal.openlayers.mapDefs[i]);
    }
  }
});

/**
 * Render OpenLayers Map
 */
function openlayersRenderMap(map) {
  // Create Projection objects
  Drupal.openlayers.activeObjects[map.id].projection = new OpenLayers.Projection("EPSG:" + map.options.projection);
  Drupal.openlayers.activeObjects[map.id].displayProjection = new OpenLayers.Projection("EPSG:" + map.options.displayProjection);
  
  // Create base map options
  var options = openlayersCreateMapOptions(map.options, map.controls, map.id);
  
  // Store map in our registry of active OpenLayers objects
  Drupal.openlayers.activeObjects[map.id].map = new OpenLayers.Map(map.id, options);
    
  // Add ID to map.
  Drupal.openlayers.activeObjects[map.id].map.mapid = map.id;
  
  // Add events to the map 
  for (var evtype in map.events){
    for (var ev in map.events[evtype]){ 
      //@@TODO: Do this without eval. See http://drupal.org/node/172169 on why we should not use eval.
      eval("Drupal.openlayers.activeObjects[map.id].map.events.register(evtype,Drupal.openlayers.activeObjects[map.id].map," +  map.events[evtype][ev] + ");");
    }
  }
  
  //On MouseOver mark the map as "active".
  $('#' + map.id).mouseover(function(){
    Drupal.openlayers.activeObjects[$(this).attr('id')].active = true;
  }).mouseout(function(){
    Drupal.openlayers.activeObjects[$(this).attr('id')].active = false;
  });
  
  // We set up all our layers
  openlayersProcessLayers(map.layers, map.id);
  
  // Make some layers editable and set-up the editing interface.
  if (map.draw_features) {
    openlayersProcessDrawFeatures(map.draw_features, map.id);
  }
    
  // Add layers to map
  for (var l in Drupal.openlayers.activeObjects[map.id].layers) {
    var layer =  Drupal.openlayers.activeObjects[map.id].layers[l];
    Drupal.openlayers.activeObjects[map.id].map.addLayer(layer);
  }
  
  // Add controls to map
  for (var c in Drupal.openlayers.activeObjects[map.id].controls) {
    var control = Drupal.openlayers.activeObjects[map.id].controls[c];
    Drupal.openlayers.activeObjects[map.id].map.addControl(control);
    if (control.activeByDefault) control.activate();
  }
      
  // Zoom to Center
  var center = new OpenLayers.LonLat(map.center.lon, map.center.lon);
  Drupal.openlayers.activeObjects[map.id].map.setCenter(center, map.center.zoom);
  
  // Set our default base layer
  Drupal.openlayers.activeObjects[map.id].map.setBaseLayer(Drupal.openlayers.activeObjects[map.id].layers[map.default_layer]);
}

/**
 * Get OpenLayers Map Options
 */
function openlayersCreateMapOptions(options, controls, mapid) {
  // @@TODO: Dynamically put in controls and options
  
  var returnOptions = {};
  
  // These parameters are set in the default map array, so they will always be defined
  returnOptions.projection = Drupal.openlayers.activeObjects[mapid].projection;
  returnOptions.displayProjection = Drupal.openlayers.activeObjects[mapid].displayProjection;
  
  // These parameters may or may not be defined by the map array, so we must check. 
  if (typeof(options.maxResolution) != "undefined") returnOptions.maxResolution = options.maxResolution;
  
  if (typeof(options.maxExtent) != "undefined") {
    returnOptions.maxExtent =  new OpenLayers.Bounds(
      options.maxExtent.left,
      options.maxExtent.bottom,
      options.maxExtent.right,
      options.maxExtent.top
    );
  }
  
  returnOptions.controls = [
    new OpenLayers.Control.Navigation(),
    new OpenLayers.Control.PanZoomBar(),
    new OpenLayers.Control.LayerSwitcher({'ascending':false}),
    new OpenLayers.Control.MousePosition()
  ];

  return returnOptions;
}

/**
 * Process Draw Features. 
 *
 * This is for marking vector layers as editable. 
 * This function will add standard functionality for adding and editing features.
 * This function does no *do* anything with the features other than allow them to be drawn, edited and deleted by the interface. 
 * Use featureadded_handler, featuremodified_handler and featureremoved_handler if you wish to do something with the drawn/edited/deleted features.
 */
function openlayersProcessDrawFeatures(drawFeatures, mapid) {
  // Add Base Pan button
  // @@TODO: Make this out put a themed item in PHP
  $('#openlayers-controls-' + mapid).append('<a href="#" id="openlayers-controls-pan-' + mapid + '" class="openlayers-controls-draw-feature-link openlayers-controls-draw-feature-link-pan openlayers-controls-draw-feature-link-on" rel="type:pan;mapid:' + mapid + '"></a>');
  
  // Go through each type of feature (point, path, polygon) that is specified and build functionality
  for (var dF in drawFeatures) {
    // Get the OpenLayers layer object that will be editable.
    var layer = Drupal.openlayers.activeObjects[mapid].layers[drawFeatures[dF].vector];
    var typeLower = drawFeatures[dF].type.toLowerCase();
    
    // Determine what handler we need to use.
    if (drawFeatures[dF].type == 'Point')       var handler = OpenLayers.Handler.Point;
    if (drawFeatures[dF].type == 'Path')        var handler = OpenLayers.Handler.Path;
    if (drawFeatures[dF].type == 'Polygon')     var handler = OpenLayers.Handler.Polygon;
    
    // Create our conrols and attach them to our layer.
    var createControl = new OpenLayers.Control.DrawFeature(layer, handler);
    var modifyControl = new OpenLayers.Control.ModifyFeature(layer, {deleteCodes:[68]});
    
    //Disable the active mode by default.  This could be changed if we wanted people to draw on the map immediately.
    createControl.activeByDefault = false;
    modifyControl.activeByDefault = false;
    
    //Mark on the control what it is for drawing (point, path, or polygon)
    createControl.drupalDrawType = typeLower;
    modifyControl.drupalDrawType = typeLower;
    
    // Add our create and modify controls to the controls object.
    // Use a # prefix since these are special controls created by drawFeatures.
    Drupal.openlayers.activeObjects[mapid].controls['#create-' + typeLower] = createControl;
    Drupal.openlayers.activeObjects[mapid].controls['#modify-' + typeLower] = modifyControl;
    
    // Add special event handlers to controls
    if (drawFeatures[dF].featureadded_handler) {
      for (var ev in drawFeatures[dF].featureadded_handler){
          // @@TODO: Do this without eval. See http://drupal.org/node/172169 on why we should not use eval.
          eval("createControl.events.register('featureadded',createControl," + drawFeatures[dF].featureadded_handler[ev] + ");");
      }
    }
       
    if (drawFeatures[dF].featuremodified_handler) {
      for (var ev in drawFeatures[dF].featuremodified_handler){ 
        // @@TODO: Do this without eval.
        eval("layer.events.register('afterfeaturemodified',layer," + drawFeatures[dF].featuremodified_handler[ev] + ");");
      }
    }
    
    if (drawFeatures[dF].featureremoved_handler) {
      for (var ev in drawFeatures[dF].featureremoved_handler){ 
        // @@TODO: Do this without eval.
        eval("layer.events.register('beforefeatureremoved',layer," + drawFeatures[dF].featureremoved_handler[ev] + ");");
      }
    
      // If a user presses the delete key, delete the currently selected polygon. 
      // This will in turn trigger the featureremoved_handler function. 
      $(document).keydown(function(event) {
        vKeyCode = event.keyCode;
        // If it is the Mac delete key (63272), or regular delete key (46) delete all selected features for the active map.
        if ((vKeyCode == 63272) || vKeyCode == 46) {
          for (var m in Drupal.openlayers.activeObjects){
            if (Drupal.openlayers.activeObjects[m].active == true){
              for (var dF in Drupal.openlayers.mapDefs[m].draw_features){
                var vector = Drupal.openlayers.mapDefs[m].draw_features[dF].vector;
                var featureToErase = Drupal.openlayers.activeObjects[m].layers[vector].selectedFeatures[0];
                Drupal.openlayers.activeObjects[m].layers[vector].destroyFeatures([featureToErase]);
                // Reload the modification control so we dont have ghost control points from the recently deceased feature
                Drupal.openlayers.activeObjects[m].controls['#modify-' + dF].deactivate();
                Drupal.openlayers.activeObjects[m].controls['#modify-' + dF].activate();
              }
            }
          }
        }
      });
    }
        
    // Add action link (button)
    // We store the type and associated mapid in the rel attribute.
    // @@TODO: Make this out put a themed item in PHP, might need a placeholder for dF
    $('#openlayers-controls-' + mapid).append('<a href="#" id="openlayers-controls-draw-' + typeLower + '-' + mapid + '" class="openlayers-controls-draw-feature-link openlayers-controls-draw-feature-link-' + typeLower + ' openlayers-controls-draw-feature-link-off" rel="type:' + dF + ';mapid:' + mapid + '"></a>');
  }
  
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
      for (var f in Drupal.openlayers.mapDefs[parsedRel['mapid']].draw_features){
        var createControl = Drupal.openlayers.activeObjects[parsedRel['mapid']].controls['#create-' + f];
        var modifyControl = Drupal.openlayers.activeObjects[parsedRel['mapid']].controls['#modify-' + f];
        
        // Deactivate everything
        createControl.deactivate();
        modifyControl.deactivate();
          
        // Activate it if it matches
        if (parsedRel['type'] == createControl.drupalDrawType){
          createControl.activate();
          modifyControl.activate();
        }
      }
      return false;
    }
  );
}

/**
 * Process Layers
 */
function openlayersProcessLayers(layers, mapid) {
  
  Drupal.openlayers.activeObjects[mapid].layers = [];
  
  // Go through layers
  if (layers) {
    for (var layer in layers) {
      // Process layer
      // @@TODO: Do this without eval. See http://drupal.org/node/172169 on why we should not use eval.
      eval("var newLayer = " + layers[layer].layer_handler + "(layers[layer], mapid);");
      Drupal.openlayers.activeObjects[mapid].layers[layer] = newLayer;

      // Add our Drupal data to the layer
      newLayer.drupalId = layer;
      newLayer.drupalData = layers[layer];
      
      // Add events
      for (var evtype in layers[layer].events){
        for (var ev in layers[layer].events[evtype]){ 
          // @@TODO: Do this without eval. See http://drupal.org/node/172169 on why we should not use eval.
          eval("newLayer.events.register(evtype,newLayer," + layers[layer].events[evtype][ev] + ");");
        }
      }
    }
  }
}

/**
 * Parse out key / value pairs out of a string that looks like "key:value;key2:value2"
 */
function openlayersParseRel(rel){
  var outputArray = [];
  
  // Some preprosessing
  // replace dangling whitespaces. Use regex?
  rel = rel.replace('; ',';');
  //Cut out final ; if it exists
  if (rel.charAt(rel.length-1) == ";") rel = rel.substr(0,rel.length-1);
  
  //Get all the key:value strings
  var keyValueStrings = rel.split(';');
  
  // Process the key:value strings into key:value pairs
  for (var i in keyValueStrings){
    var singleKeyValue = keyValueStrings[i].split(':');
    outputArray[singleKeyValue[0]] = singleKeyValue[1];
  }
  
  return outputArray;
}

/**
 * Dump Variables -- This is a JS developer tool
 */
function openlayersVarDump(element, limit, depth) {
  limit = limit ? limit : 1;
  depth = depth ? depth : 0;
  returnString = '<ol>';
  
  for (property in element) {
    //Property domConfig isn't accessable
    if (property != 'domConfig') {
      returnString += '<li><strong>'+ property + '</strong> <small>(' + (typeof element[property]) + ')</small>';
      if (typeof element[property] == 'number' || typeof element[property] == 'boolean')
        returnString += ' : <em>' + element[property] + '</em>';
      if (typeof element[property] == 'string' && element[property])
        returnString += ': <div style="background:#C9C9C9;border:1px solid black; overflow:auto;"><code>' +
                  element[property].replace(/</g, '<').replace(/>/g, '>') + '</code></div>';
      if ((typeof element[property] == 'object') && (depth <limit))
        returnString += openlayersVarDump(element[property], limit, (depth + 1));
      returnString += '</li>';
    }
  }
  returnString += '</ol>';
  if (depth == 0) {
    winpop = window.open("", "","width=800,height=600,scrollbars,resizable");
    winpop.document.write('<pre>' + returnString + '</pre>');
    winpop.document.close();
  }
  return returnString;
}