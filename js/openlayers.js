// $Id$

/**
 * When document is ready for JS
 */
jQuery(document).ready(function() {
  // Store rendered maps in Drupal.setting
  Drupal.settings.openlayers.mapsRendered = [];
  // Go through array and make maps
  for (var i in Drupal.settings.openlayers.maps) {
    var map = Drupal.settings.openlayers.maps[i];
    // Check there is an ID for the map
    if ($('#' + map.id).length > 0) {
      // Make div the right dimensions
      $('#' + map.id).css('width', map.width).css('height', map.height);
      $('#' + map.id).after('<div class="openlayers-controls" id="openlayers-controls-' + map.id + '"></div>');
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
  // Store map in Drupal settings
  Drupal.settings.openlayers.mapsRendered[map.id] = new OpenLayers.Map(map.id, options);
  // Add ID to map
  Drupal.settings.openlayers.mapsRendered[map.id].mapid = map.id;
  
  // Get Layers
  // We need an object and array for layers, mostly for Drawing Features.
  var layersObject = {};
  var layersArray = openlayersProcessLayers(map.layers, layersObject, map.id);
  
  // Draw Features
  if (map.draw_features) {
    openlayersProcessDrawFeatures(map.draw_features, layersObject, map.id);
  }
  
  // Add layers to map
  Drupal.settings.openlayers.mapsRendered[map.id].addLayers(layersArray);
               
  // Zoom to Center
  Drupal.settings.openlayers.mapsRendered[map.id].setCenter(new OpenLayers.LonLat(map.center.lon, map.center.lat), map.center.zoom);
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
 * Process Draw Features
 */
function openlayersProcessDrawFeatures(drawFeatures, layers, mapid) {
  var controls = {};
  
  // Add Base Pan button
  $('#openlayers-controls-' + mapid).append('<a href="#" id="openlayers-controls-pan-' + mapid + '" class="openlayers-controls-draw-feature-link openlayers-controls-draw-feature-link-pan openlayers-controls-draw-feature-link-on" rel="pan"></a>');
    
  // Go through draw features
  for (var dF in drawFeatures) {
    var layer = layers[drawFeatures[dF].vector];
    var typeLower = drawFeatures[dF].type.toLowerCase();
    
    // Add control to list
    eval('controls.' + dF + ' = {}');
    eval('controls.' + dF + '.create = new OpenLayers.Control.DrawFeature(layer, OpenLayers.Handler.' + drawFeatures[dF].type + ')');
    eval('controls.' + dF + '.modify = new OpenLayers.Control.ModifyFeature(layer)');
    // Add event handler
    if (drawFeatures[dF].handler) {
      eval('controls.' + dF + '.create.events.register("featureadded", controls.' + dF + '.create, ' +  drawFeatures[dF].handler + ')');
    }
    // Add action link
    $('#openlayers-controls-' + mapid).append('<a href="#" id="openlayers-controls-draw-point-' + mapid + '" class="openlayers-controls-draw-feature-link openlayers-controls-draw-feature-link-' + typeLower + ' openlayers-controls-draw-feature-link-off" rel="' + dF + '"></a>');
  }
  
  // Add Controls
  for (var c in controls) {
    Drupal.settings.openlayers.mapsRendered[mapid].addControl(controls[c].create);
    Drupal.settings.openlayers.mapsRendered[mapid].addControl(controls[c].modify);
  }
  
  // Add click event
  $('.openlayers-controls-draw-feature-link').click(
    function() {
      // @@TODO put in scope of map container.  Currently turning off all on page.
      $('.openlayers-controls-draw-feature-link').removeClass('openlayers-controls-draw-feature-link-on');
      $('.openlayers-controls-draw-feature-link').addClass('openlayers-controls-draw-feature-link-off');
      $(this).addClass('openlayers-controls-draw-feature-link-on');
      $(this).removeClass('openlayers-controls-draw-feature-link-off');
      // Go through controls
      for (var cKey in controls) {
        // If this one
        if ($(this).attr('rel') == cKey) {
          controls[cKey].create.activate();
          controls[cKey].modify.activate();
        } else {
          controls[cKey].create.deactivate();
          controls[cKey].modify.deactivate();
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
function openlayersProcessLayers(layers, layersObject, mapid) {
  var layersAdded = [];
  // Go through layers
  if (layers) {
    for (var layer in layers) {
      switch (layers[layer].type) {
        case 'WMS':
          layersAdded[layersAdded.length] = openlayersProcessLayerWMS(layers[layer], mapid);
          eval('layersObject.' + layer + ' = openlayersProcessLayerWMS(layers[layer], mapid)');
          break;
          
        case 'Vector':
          layersAdded[layersAdded.length] = openlayersProcessLayerVector(layers[layer], mapid);
          eval('layersObject.' + layer + ' = openlayersProcessLayerVector(layers[layer], mapid)');
          break;
      }
      // Add ID to layer
      eval('layersObject.' + layer + '.mapid = mapid');
    }
  }
  
  return layersAdded;
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
 * Dump Variables
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