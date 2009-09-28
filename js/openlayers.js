// $Id$

/**
 * @file
 * This file holds the main javascript API for OpenLayers. It is 
 * responsable for loading and displaying the map.
 *
 * @ingroup openlayers
 */

/**
 * Global Object for Namespace
 */
var OL = OL || {'Layers': {}, 'EventHandlers': {} ,'Behaviors': {}, 'maps': []};

/**
 * OpenLayers Base Drupal Behavoirs
 */
Drupal.behaviors.openlayers = function(context) {
  // Store rendered maps and other OpenLayer objects in OL object
  OL.mapDefs = Drupal.settings.openlayers.maps;
  
  // Check that there is openlayers data sent from PHP, and
  // there is maps data, and that we are not going
  // through a map again
  if (typeof(Drupal.settings.openlayers) == 'object' && (OL.isSet(Drupal.settings.openlayers.maps)) && !$(context).data('openlayers')) {
    // Get all non-processed maps
    $('.openlayers-map:not(.openlayers-processed)').each(function() {
      var $map = $(this);
      
      // Mark as processed
      $map.addClass('openlayers-processed');

      // Get map ID and check for map data
      var map_id = $map.attr('id');
      if (OL.isSet(Drupal.settings.openlayers.maps[map_id])) {
        var map = Drupal.settings.openlayers.maps[map_id];
  
        // Trigger beforeEverything event
        var event = {'mapDef': map};
        OL.triggerCustom(map, 'beforeEverything', event);
      
        // Add any custom controls
        $map.after(Drupal.theme('mapControls', map_id, map.height));
        
        // Set-up our registry of active OpenLayers javascript objects for this particular map.
        OL.maps[map_id] = {};
        // Set up places for us to store layers, controls, etc.
        OL.maps[map_id].controls = [];
        OL.maps[map_id].layers = [];
        OL.maps[map_id].active = false;
  
        // Render Map
        var rendered = OL.renderMap(map);

        // Attach data to map DOM object
        $map.data('openlayers', {'map': map, 'openlayers': rendered});

        // Finally, attach behaviors
        Drupal.attachBehaviors($map);
      }
    });
  }
};

/**
 * Render OpenLayers Map
 * 
 * The main function to go through all the steps nessisary for rendering a map.
 * 
 * @param map
 *   The map definition array.
 * @return
 *   The rendered map object
 */
OL.renderMap = function(map) {
  // Create Projection objects
  OL.maps[map.id].projection = new OpenLayers.Projection('EPSG:' + map.projection);
  
  if (OL.isSet(map.options)) {
    OL.maps[map.id].displayProjection = new OpenLayers.Projection('EPSG:' + map.options.displayProjection);
  
    // Create base map options
    var options = OL.createMapOptions(map.options, map.controls, map.id);
  }
  else {
    OL.maps[map.id].displayProjection = OL.maps[map.id].projection;
    var options = [];
  }

  // Change image path if specified
  if (OL.isSet(map.image_path) && map.image_path) {
    OpenLayers.ImgPath = map.image_path;
  }
  
  // Store map in our registry of active OpenLayers objects
  OL.maps[map.id].map = new OpenLayers.Map(map.id, options);
  
  // Add ID to map.
  OL.maps[map.id].map.mapid = map.id;
  
  // On MouseOver mark the map as "active".
  $('#' + map.id).mouseover(function() {
    OL.maps[map.id].active = true;
  })
  .mouseout(function() {
    OL.maps[map.id].active = false;
  });

  // Trigger beforeLayers event
  var event = {'mapDef': map, 'map': OL.maps[map.id].map};
  OL.triggerCustom(map, 'beforeLayers', event);
  
  // We set up all our layers
  OL.processLayers(map.layers, map.id);
  
  // Add layers to map
  for (var l in OL.maps[map.id].layers) {
    var layer =  OL.maps[map.id].layers[l];
    OL.maps[map.id].map.addLayer(layer);
  }
  
  // Trigger beforeCenter event
  var event = {'mapDef': map, 'map': OL.maps[map.id].map};
  OL.triggerCustom(map, 'beforeCenter', event);
  
  // Zoom to Center
  // @@TODO: Do this in the map options -- As isthis will result in a bug in the zoom map helper in the map form
  if (OL.isSet(map.center)) {
    var center = new OpenLayers.LonLat(map.center.lon, map.center.lat);
	  var zoom = parseInt(map.center.zoom);
    OL.maps[map.id].map.setCenter(center, zoom, false, false);
  }
  
  // Set our default base layer
  OL.maps[map.id].map.setBaseLayer(OL.maps[map.id].layers[map.default_layer]);

  // Trigger beforeControls event
  var event = {'mapDef': map, 'map': OL.maps[map.id].map};
  OL.triggerCustom(map, 'beforeControls', event);
  
  // Add controls to map
  for (var c in OL.maps[map.id].controls) {
    var control = OL.maps[map.id].controls[c];
    OL.maps[map.id].map.addControl(control);
    if (control.activeByDefault) {
      control.activate();
    }
  }

  // Trigger beforeEvents event
  var event = {'mapDef': map, 'map': OL.maps[map.id].map};
  OL.triggerCustom(map, 'beforeEvents', event);
  
  // Add events to the map 
  OL.processEvents(map.events, map.id); 

  // Trigger beforeBehaviors event
  var event = {'mapDef': map, 'map': OL.maps[map.id].map};
  OL.triggerCustom(map, 'beforeBehaviors', event);
  
  // Trigger mapReady event
  var event = {'mapDef': map, 'map': OL.maps[map.id].map};
  OL.triggerCustom(map, 'mapReady', event);
      
  // Mark as Rendered
  OL.maps[map.id].rendered = true;
  
  // Return rendered map
  return OL.maps[map.id].map;
}

/**
 * Get OpenLayers Map Options
 *
 * @param options
 *   Object of options to include
 * @param controls
 *   Object of controls to add
 * @param mapid
 *   String Id of map
 * @return
 *   Object of processed options
 */
OL.createMapOptions = function(options, controls, mapid) {
  var returnOptions = {};
  
  // Projections 
  if (OL.isSet(OL.maps[mapid].projection) && OL.isSet(OL.maps[mapid].displayProjection)) {
    returnOptions.projection = OL.maps[mapid].projection;
    returnOptions.displayProjection = OL.maps[mapid].displayProjection;
  }
  
  // Max resolution and Extent
  if (OL.isSet(options.maxResolution)) {
    returnOptions.maxResolution = options.maxResolution;
  }
  if (typeof(options.maxExtent) != "undefined") {
    returnOptions.maxExtent =  new OpenLayers.Bounds(
      options.maxExtent.left,
      options.maxExtent.bottom,
      options.maxExtent.right,
      options.maxExtent.top
    );
  }
 
  // Controls
  if (OL.isSet(controls)) {
    // @@TODO: This should be a little more dynamic
    returnOptions.controls = [];
    if (controls.LayerSwitcher)   returnOptions.controls.push( new OpenLayers.Control.LayerSwitcher() );
    if (controls.Navigation)      returnOptions.controls.push( new OpenLayers.Control.Navigation() );
    if (controls.Attribution)     returnOptions.controls.push( new OpenLayers.Control.Attribution() );
    if (controls.PanZoomBar)      returnOptions.controls.push( new OpenLayers.Control.PanZoomBar() );
    if (controls.PanZoom)         returnOptions.controls.push( new OpenLayers.Control.PanZoom() );
    if (controls.MousePosition)   returnOptions.controls.push( new OpenLayers.Control.MousePosition() );
    if (controls.Permalink)       returnOptions.controls.push( new OpenLayers.Control.Permalink() );
    if (controls.ScaleLine)       returnOptions.controls.push( new OpenLayers.Control.ScaleLine() );
    if (controls.KeyboardDefaults)returnOptions.controls.push( new OpenLayers.Control.KeyboardDefaults() );
    if (controls.ZoomBox)         returnOptions.controls.push( new OpenLayers.Control.ZoomBox() );
    if (controls.ZoomToMaxExtent) returnOptions.controls.push( new OpenLayers.Control.ZoomToMaxExtent() );
  }

  if(OL.isSet(options.fractionalZoom)) {
    returnOptions.fractionalZoom = options.fractionalZoom;
  }
  
  // Return processed options
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
OL.processLayers = function(layers, mapid) {
  OL.maps[mapid].layers = [];
  
  // Go through layers
  if (layers) {
    for (var layer in layers) {
      // Process layer, check for function
      if (OL.isSet(OL.Layers) && typeof(OL.Layers[layers[layer].layer_handler]) == 'function') {
        var newLayer = OL.Layers[layers[layer].layer_handler](layers[layer], mapid);
        OL.maps[mapid].layers[layer] = newLayer;
  
        // Add our Drupal data to the layer
        newLayer.drupalId = layer;
        newLayer.drupalData = layers[layer];
        
        // Add events
        for (var evtype in layers[layer].events){
          for (var ev in layers[layer].events[evtype]) { 
            newLayer.events.register(evtype, newLayer, OL.EventHandlers[layers[layer].events[evtype][ev]]);
          }
        }
      }
    }
  }
}

/**
 * Map Controls Theme Function
 *
 * @param mapid
 *   String of mapid
 * @param height
 *   String of the height of the map
 * @return
 *   Themed map control division
 */
Drupal.theme.prototype.mapControls = function(mapid, height) {
  var newcontainer = $('<div></div>');
  newcontainer.addClass('openlayers-controls').attr('id', 'openlayers-controls-' + mapid).css('position', 'relative').css('top', '-' + height);
  return newcontainer;
}
