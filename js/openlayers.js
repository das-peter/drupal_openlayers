// $Id$

/**
 * When document is ready for JS
 */
jQuery(document).ready(function() {
  // Store rendered maps in Drupal.setting
  Drupal.openlayers = {}
  Drupal.openlayers.activeObjects = [];
  // Go through array and make maps
  for (var i in Drupal.settings.openlayers.maps) {
    var map = Drupal.settings.openlayers.maps[i];
    // Check there is an ID for the map
    if ($('#' + map.id).length > 0) {
      // Make div the right dimensions and add custom controls
      $('#' + map.id).css('width', map.width).css('height', map.height);
      $('#' + map.id).after('<div class="openlayers-controls" id="openlayers-controls-' + map.id + '"></div>');
      $('#openlayers-controls-' + map.id).css("position","relative").css("bottom",map.height);
      
      
      //Set-up our registry of active OpenLayers javascript objects
      Drupal.openlayers.activeObjects[map.id] = {};
      
      // Render Map
      openlayersRenderMap(Drupal.settings.openlayers.maps[i]);
    }
  }
});

/**
 * Render OpenLayers Map
 */
function openlayersRenderMap(map) {
		
  // Create base map options
  var options = openlayersCreateMapOptions(map.options, map.controls, map.id);
  
  // Store map in our registry of active OpenLayers objects
  Drupal.openlayers.activeObjects[map.id].map = new OpenLayers.Map(map.id, options);
    
  // Add ID to map
  Drupal.openlayers.activeObjects[map.id].map.mapid = map.id;
  
  //Add events to the map 
  for (var evtype in map.events){
  	for (var ev in map.events[evtype]){ 
 			eval("Drupal.openlayers.activeObjects[map.id].map.events.register(evtype,Drupal.openlayers.activeObjects[map.id].map," +  map.events[evtype][ev] + ");");  //Can we do this without using eval()?  		
  	}
  }
  
  // We set up all our layers
  openlayersProcessLayers(map.layers, map.id);
  
  // Set up layers for editablity
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
  var center = new OpenLayers.LonLat(map.center.lon, map.center.lat);
  Drupal.openlayers.activeObjects[map.id].map.setCenter(center,map.center.zoom);
}

/**
 * Get OpenLayers Map Options
 */
function openlayersCreateMapOptions(options, controls, mapid) {
  // @@TODO: Dynamically put in controls and options
  
  var returnOptions = {
    numZoomLevels: options.numZoomLevels,
    controls: [
      new OpenLayers.Control.PanZoomBar(),
      new OpenLayers.Control.MouseToolbar(),
      new OpenLayers.Control.LayerSwitcher({'ascending':false}),
      new OpenLayers.Control.Permalink(),
      new OpenLayers.Control.ScaleLine(),
      new OpenLayers.Control.Permalink('permalink'),
      new OpenLayers.Control.MousePosition(),
      new OpenLayers.Control.OverviewMap(),
      new OpenLayers.Control.KeyboardDefaults(),
      // new OpenLayers.Control.EditingToolbar()
    ],
  }
  return returnOptions;
}

/**
 * Process Draw Features. This is for marking vector layers as editable. Calling this function will add standard functionality for adding and editing features.
 */
function openlayersProcessDrawFeatures(drawFeatures, mapid) {
  
  //Set up a place to store our controls in our registry of active OpenLayers objects
  Drupal.openlayers.activeObjects[mapid].controls = [];
  
  // Add Base Pan button
  // TODO: Make this out put a themed item in PHP
  $('#openlayers-controls-' + mapid).append('<a href="#" id="openlayers-controls-pan-' + mapid + '" class="openlayers-controls-draw-feature-link openlayers-controls-draw-feature-link-pan openlayers-controls-draw-feature-link-on" rel="type:pan;mapid:'+mapid+'"></a>');
  
  // Go through draw features
  for (var dF in drawFeatures) {
    var layer = Drupal.openlayers.activeObjects[mapid].layers[drawFeatures[dF].vector];
    var typeLower = drawFeatures[dF].type.toLowerCase();
    
    // Add control to list
    if (drawFeatures[dF].type == 'Point')       var handler = OpenLayers.Handler.Point;
    if (drawFeatures[dF].type == 'Path')  			var handler = OpenLayers.Handler.Path;
    if (drawFeatures[dF].type == 'Polygon')     var handler = OpenLayers.Handler.Polygon;
		
		// Add our create and modify controls to the control object. Use a # prefix since these are speacial controls created by drawFeatures.
    var create_control = new OpenLayers.Control.DrawFeature(layer, handler);
    var modify_control = new OpenLayers.Control.ModifyFeature(layer);
    
    //Disable the active mode by default.  This could be changed if we wanted people to draw on the map immediately.
    create_control.activeByDefault = false;
    modify_control.activeByDefault = false;
    
    create_control.drawType = typeLower;
    modify_control.drawType = typeLower;
    
    Drupal.openlayers.activeObjects[mapid].controls['#create-' + typeLower] = create_control;
    Drupal.openlayers.activeObjects[mapid].controls['#modify-' + typeLower] = modify_control;
            
    // Add event handler
    if (drawFeatures[dF].featureadded_handler) {
      eval("create_control.events.register('featureadded',create_control," + drawFeatures[dF].featureadded_handler + ");");  //Can we do this without using eval()?
    }
        
    // Add action link
    // TODO: Make this out put a themed item in PHP, might need a placeholder for dF
    $('#openlayers-controls-' + mapid).append('<a href="#" id="openlayers-controls-draw-' + typeLower + '-' + mapid + '" class="openlayers-controls-draw-feature-link openlayers-controls-draw-feature-link-' + typeLower + ' openlayers-controls-draw-feature-link-off" rel="type:' + dF + ';mapid:'+ mapid +'"></a>');
  }
  
  // Add click event
  $('.openlayers-controls-draw-feature-link').click(
    function() {
      var parsedRel = openlayersParseRel($(this).attr('rel'));
      
      // @@TODO put in scope of map container.  Currently turning off all on page.
      $('.openlayers-controls-draw-feature-link').removeClass('openlayers-controls-draw-feature-link-on');
      $('.openlayers-controls-draw-feature-link').addClass('openlayers-controls-draw-feature-link-off');
      $(this).addClass('openlayers-controls-draw-feature-link-on');
      $(this).removeClass('openlayers-controls-draw-feature-link-off');
      
      for (var f in Drupal.settings.openlayers.maps[parsedRel['mapid']].draw_features){
      	var createControl = Drupal.openlayers.activeObjects[parsedRel['mapid']].controls['#create-'+f];
      	var modifyControl = Drupal.openlayers.activeObjects[parsedRel['mapid']].controls['#modify-'+f];
      	
      	//Deactivate everything
      	createControl.deactivate();
      	modifyControl.deactivate();
      		
      	//Activate it if it matches
      	if (parsedRel['type'] == createControl.drawType){
      		createControl.activate();
      		modifyControl.activate();
      	}
      }
      return false;
    }
  );
}

/**
 * Default Feature Handler
 */
function openlayersDefaultFeatureHandler(feature) {
  // Do something.
}

/**
 * Process Layers
 */
function openlayersProcessLayers(layers, mapid) {
	
	Drupal.openlayers.activeObjects[mapid].layers = [];
	
  // Go through layers
  if (layers) {
    for (var layer in layers) {
      switch (layers[layer].type) {
        case 'WMS':    
        	var new_layer = openlayersProcessLayerWMS(layers[layer], mapid);
        	Drupal.openlayers.activeObjects[mapid].layers[layer] = new_layer;
          break;    
        case 'Vector':
        	var new_layer = openlayersProcessLayerVector(layers[layer], mapid);
       		Drupal.openlayers.activeObjects[mapid].layers[layer] = new_layer;
          break;
      }
      //Add our Drupal data to the layer
      new_layer.drupalId = layer;
      new_layer.drupalData = layers[layer];
      
      //Add events
      for (var evtype in layers[layer].events){
      	for (var ev in layers[layer].events[evtype]){ 
      		eval("new_layer.events.register(evtype,new_layer," + layers[layer].events[evtype][ev] + ");");  //Can we do this without using eval()?  		
      	}
      }
    }
  }
}

/**
 * Process WMS Layers
 */
function openlayersProcessLayerWMS(layerOptions, mapid) {
  var wmsOptions = {
    layers: layerOptions.params.layers,
  };
  var returnWMS = new OpenLayers.Layer.WMS(layerOptions.name, layerOptions.url, wmsOptions);
  return returnWMS;
}

/**
 * Process Vector Layers
 */
function openlayersProcessLayerVector(layerOptions, mapid) {
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



/**
 * Parse out key / value pairs out of a string that looks like "key:value;key2:value2"
 */
function openlayersParseRel(rel){
	var outputArray = [];
	
	//Some preprosessing
	//replace dangling whitespaces. Use regex?
	rel = rel.replace('; ',';');
	//Cut out final ; if it exists
	if (rel.charAt(rel.length-1) == ";") rel = rel.substr(0,rel.length-1);
	
	//Get all the key:value strings
	var keyValueStrings = rel.split(';');
	
	//Process the key:value strings into key:value pairs
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
      returnString += '<li><strong>'+ property + '</strong> <small>(' + (typeof element[property]) +')</small>';
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
    winpop.document.write('<pre>'+returnString+ '</pre>');
    winpop.document.close();
  }
  return returnString;
}