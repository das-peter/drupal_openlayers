// $Id$

/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * Attribution Behavior
 */
Drupal.behaviors.openlayers_behavior_fullscreen = function(context) {
  var fullscreen_panel, data = $(context).data('openlayers');
  if (data && data.map.behaviors['openlayers_behavior_fullscreen']) {
    fullscreen_panel = new OpenLayers.Control.Panel(
      {
        displayClass: "openlayers_behavior_fullscreen_button_panel"
      }
    );
    data.openlayers.addControl(fullscreen_panel);
    var button = new OpenLayers.Control.Button({
      displayClass: "openlayers_behavior_fullscreen_button", 
      title: "Fullscreen", 
      trigger: openlayers_behavior_fullscreen_toggle
    });
    fullscreen_panel.addControls([button]);
  }
}

openlayers_behavior_fullscreen_toggle = function(context) {
  $(this.map.div).parent().toggleClass('openlayers_map_fullscreen');
  $(this.map.div).toggleClass('openlayers_map_fullscreen');
}


/**
 * Fullsceen Behavoir
 *
 * @param event
 *   Event Object
OL.Behaviors.fullscreen = function(event) {
  var mapDef = event.mapDef;
  var mapid = mapDef.id;
  var $map = $('#' + mapid);
  var $mapControls = $('#openlayers-controls-' + mapid);
  
  $('<a href="#"></a>')
    .attr('id', 'openlayers-controls-fullscreen-' + mapid)
    .addClass('openlayers-controls-fullscreen')
    .data('mapid', mapid)
    .appendTo('#openlayers-controls-' + mapid)
    .click(function() {
      var $thisElement = $(this);
    
      // Store data
      if (!OL.isSet(OL.Behaviors.fullscreenRegistry)) {
        OL.Behaviors.fullscreenRegistry = [];
      }
      if (!OL.isSet(OL.Behaviors.fullscreenRegistry[mapid])) {
        OL.Behaviors.fullscreenRegistry[mapid] = {};
        OL.Behaviors.fullscreenRegistry[mapid].fullscreen = false;
        OL.Behaviors.fullscreenRegistry[mapid].mapstyle = [];
        OL.Behaviors.fullscreenRegistry[mapid].controlsstyle = [];
      }
      
      // Check if fullscreen
      if (!OL.Behaviors.fullscreenRegistry[mapid].fullscreen) {
        OL.Behaviors.fullscreenRegistry[mapid].fullscreen = true;
      
        // Store old css values
        var mapStylesToStore = ['position','top','left','width','height','z-index'];
        var controlStylesToStore = ['position','top','right'];
        for (var ms in mapStylesToStore) {
          OL.Behaviors.fullscreenRegistry[mapid].mapstyle[mapStylesToStore[ms]] = $('#' + mapid).css(mapStylesToStore[ms]);
        }
        for (var cs in controlStylesToStore) {
          OL.Behaviors.fullscreenRegistry[mapid].controlsstyle[controlStylesToStore[cs]] = $('#openlayers-controls-' + mapid).css(controlStylesToStore[cs]);
        }
      
        // Resize the map.
        $map.css('position','fixed')
          .css('top','0px')
          .css('left','0px')
          .css('width','100%')
          .css('height','100%')
          .css('z-index','999');
        // Change CSS on map controls
        $mapControls.css('position','fixed')
          .css('top','0px')
          .css('right','0px');
        // Update classes
        $thisElement.removeClass('openlayers-controls-fullscreen')
          .addClass('openlayers-controls-unfullscreen');
        
        // Update size of OpenLayers
        event.map.updateSize();
      }
      else {
        // Restore styles, resizing the map.
        for (var ms in OL.Behaviors.fullscreenRegistry[mapid].mapstyle) {
          $('#' + mapid).css(ms,OL.Behaviors.fullscreenRegistry[mapid].mapstyle[ms]);
        };
        for (var cs in OL.Behaviors.fullscreenRegistry[mapid].controlsstyle) {
          $('#openlayers-controls-' + mapid).css(cs,OL.Behaviors.fullscreenRegistry[mapid].controlsstyle[cs]);
        };
        
        // Update classes
        $thisElement.removeClass('openlayers-controls-unfullscreen')
          .addClass('openlayers-controls-fullscreen');
          
        // Update stored registry and OpenLayers map size
        OL.Behaviors.fullscreenRegistry[mapid].fullscreen = false;
        event.map.updateSize();
      }
    });
    
    if ('default' in event.behavior) {
      if (event.behavior['default'] == 'on') {
        $('#openlayers-controls-fullscreen-' + mapid).click();
      }
      if (event.behavior['default'] == 'locked') {
        $('#openlayers-controls-fullscreen-' + mapid).click().hide();
      }
    }
    
}
*/
