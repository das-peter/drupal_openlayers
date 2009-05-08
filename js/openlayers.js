// $Id$

/**
 * @file
 * This file holds the main javascript API for OpenLayers. It is responsable for loading and displaying the map.
 */

/**
 * When document is ready for JS
 */
jQuery(document).ready(function() {
  openlayersLoadMaps();
});

function openlayersLoadMaps(){
  // @@TODO: Implement proxy
  OpenLayers.ProxyHost = "http://raider/proxy/?proxy_url=";
  
  // Store rendered maps and other OpenLayer objects in Drupal.openlayers.activeObjects
  Drupal.openlayers = {}
  Drupal.openlayers.activeObjects = [];
  Drupal.openlayers.mapDefs = Drupal.settings.openlayers.maps;
  
  // Go through array and make maps
  for (var i in Drupal.openlayers.mapDefs) {
    var map = Drupal.openlayers.mapDefs[i];
    
    // Trigger beforeEverything event
    var event = { 'mapDef': map};
    openlayersTiggerCustomEvent(map, 'beforeEverything', event);
    
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
};

/**
 * Render OpenLayers Map
 * 
 * The main function to go through all the steps nessisary for rendering a map.
 * 
 * @param map
 *   The map definition array.
 */
function openlayersRenderMap(map) {
  // Create Projection objects
  Drupal.openlayers.activeObjects[map.id].projection = new OpenLayers.Projection("EPSG:" + map.projection);
  Drupal.openlayers.activeObjects[map.id].displayProjection = new OpenLayers.Projection("EPSG:" + map.options.displayProjection);
  
  // Create base map options
  var options = openlayersCreateMapOptions(map.options, map.controls, map.id);
  
  // Store map in our registry of active OpenLayers objects
  Drupal.openlayers.activeObjects[map.id].map = new OpenLayers.Map(map.id, options);
    
  // Add ID to map.
  Drupal.openlayers.activeObjects[map.id].map.mapid = map.id;
  
  //On MouseOver mark the map as "active".
  $('#' + map.id).mouseover(function(){
    Drupal.openlayers.activeObjects[$(this).attr('id')].active = true;
  }).mouseout(function(){
    Drupal.openlayers.activeObjects[$(this).attr('id')].active = false;
  });

  // Trigger beforeLayers event
  var event = { 'mapDef': map, 'map': Drupal.openlayers.activeObjects[map.id].map};
  openlayersTiggerCustomEvent(map, 'beforeLayers', event);
  
  // We set up all our layers
  openlayersProcessLayers(map.layers, map.id);
  
  // Add layers to map
  for (var l in Drupal.openlayers.activeObjects[map.id].layers) {
    var layer =  Drupal.openlayers.activeObjects[map.id].layers[l];
    Drupal.openlayers.activeObjects[map.id].map.addLayer(layer);
  }
  
  // Trigger beforeCenter event
  var event = { 'mapDef': map, 'map': Drupal.openlayers.activeObjects[map.id].map};
  openlayersTiggerCustomEvent(map, 'beforeCenter', event);
  
  // Zoom to Center
  // @@TODO: Do this in the map options -- As isthis will result in a bug in the zoom map helper in the map form
  var center = new OpenLayers.LonLat(map.center.lon, map.center.lat);
  Drupal.openlayers.activeObjects[map.id].map.setCenter(center, map.center.zoom, false, false);
  
  // Set our default base layer
  Drupal.openlayers.activeObjects[map.id].map.setBaseLayer(Drupal.openlayers.activeObjects[map.id].layers[map.default_layer]);

  // Trigger beforeControls event
  var event = { 'mapDef': map, 'map': Drupal.openlayers.activeObjects[map.id].map};
  openlayersTiggerCustomEvent(map, 'beforeControls', event);
  
  // Add controls to map
  for (var c in Drupal.openlayers.activeObjects[map.id].controls) {
    var control = Drupal.openlayers.activeObjects[map.id].controls[c];
    Drupal.openlayers.activeObjects[map.id].map.addControl(control);
    if (control.activeByDefault) control.activate();
  }

  // Trigger beforeEvents event
  var event = { 'mapDef': map, 'map': Drupal.openlayers.activeObjects[map.id].map};
  openlayersTiggerCustomEvent(map, 'beforeEvents', event);
  
  // Add events to the map 
  openlayersProcessEvents(map.events, map.id); 

  // Trigger beforeBehaviors event
  var event = { 'mapDef': map, 'map': Drupal.openlayers.activeObjects[map.id].map};
  openlayersTiggerCustomEvent(map, 'beforeBehaviors', event);
  
  // Add behaviors to map
  for (var b in Drupal.openlayers.mapDefs[map.id].behaviors) {
    var event = {};
    event.mapDef = map;
    event.map = Drupal.openlayers.activeObjects[map.id].map;
    event.behavior = Drupal.openlayers.mapDefs[map.id].behaviors[b];
    window[Drupal.openlayers.mapDefs[map.id].behaviors[b].js_callback](event);
  }
  
  // Trigger mapReady event
  var event = { 'mapDef': map, 'map': Drupal.openlayers.activeObjects[map.id].map};
  openlayersTiggerCustomEvent(map, 'mapReady',event);
  
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
  if (openlayersIsSet(options.maxResolution)) returnOptions.maxResolution = options.maxResolution;
  
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
 * Process Layers
 *
 * Process the layers part of the map definition into OpenLayers layer objects
 * 
 * @param layers
 *   The layers section of the map definition array.
 * @param mapid
 *   The id of the map to which we will eventually add these layers.
 */
function openlayersProcessLayers(layers, mapid) {
  
  Drupal.openlayers.activeObjects[mapid].layers = [];
  
  // Go through layers
  if (layers) {
    for (var layer in layers) {
      // Process layer
      var newLayer = window[layers[layer].layer_handler](layers[layer], mapid);
      Drupal.openlayers.activeObjects[mapid].layers[layer] = newLayer;

      // Add our Drupal data to the layer
      newLayer.drupalId = layer;
      newLayer.drupalData = layers[layer];
      
      // Add events
      for (var evtype in layers[layer].events){
        for (var ev in layers[layer].events[evtype]){ 
          newLayer.events.register(evtype,newLayer,window[layers[layer].events[evtype][ev]]);
        }
      }
    }
  }
}


/**
 * Process Events
 *
 * Process the layers part of the map definition into OpenLayers layer objects
 * 
 * @param events
 *   The events section of the map definition array.
 * @param mapid
 *   The id of the map to which we will add these events.
 */
function openlayersProcessEvents(events, mapid) {
  // Go through events
  for (var evtype in events){
    // Exclude One-Time map events. 
    if (evtype != 'beforeEverything' && evtype != 'beforeLayers' && evtype != 'beforeCenter' && evtype != 'beforeControls' && evtype != 'beforeEvents' && evtype != 'beforeBehaviors' && evtype != 'mapReady'){
      for (var ev in events[evtype]){ 
        Drupal.openlayers.activeObjects[mapid].map.events.register(evtype,Drupal.openlayers.activeObjects[mapid].map,window[events[evtype][ev]]);
      }
    }
  }
}


/**
 * Parse out key / value pairs out of a string that looks like "key:value;key2:value2"
 * 
 * @param rel
 *   The string to parse. Usually the rel attribute of a html tag.
 * @return
 *   Array of key:value pairs
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
 * 
 * @param element
 *   The element to dump
 * @param limit
 *   The depth we should go to.
 * @param depth
 *   The depth we should start at.
 * @return
 *   Nothing. Displaying in a pop-up.
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

function openlayersTiggerCustomEvent(map, eventname,event){
  if (openlayersIsSet(map.events) && openlayersIsSet(map.events[eventname])){
    for (var ev in map.events[eventname]){
      window[map.events[eventname][ev]](event);
    }
  }
}

// @@TODO: Replace all typeof with this (it's shorter - do we even need to namespace it? ideally it would be isset() or defined() )
function openlayersIsSet(variable){
  if (typeof(variable) == 'undefined') return false;
  else return true;
}
