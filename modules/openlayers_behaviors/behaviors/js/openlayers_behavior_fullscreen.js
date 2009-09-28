// $Id$

/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * Fullscreen Behavior
 */
Drupal.behaviors.openlayers_behavior_fullscreen = function(context) {
  var data = $(context).data('openlayers');
  if (data && OL.isSet(data.map.behaviors) && data.map.behaviors['openlayers_behavior_fullscreen']) {
    var panel = new OpenLayers.Control.Panel({
      allowSelection: true
    });      
    
    data.openlayers.addControl(panel);
    panel.activate();
              
    var button = new OpenLayers.Control.Button({
      displayClass: "openlayers-control-fullscreen", 
      allowSelection: true,
      trigger: function() {
        data.openlayers.fullscreenmode = (data.openlayers.fullscreenmode == true ? false : true );
        Drupal.openlayers_behavior_fullscreen.fullscreen(data);
      },
    });
    
    panel.addControls(button);
  }
}

Drupal.openlayers_behavior_fullscreen = {
  'fullscreen': function(data) {
      var $map = $('#' + data.map.id);
      if (data.openlayers.fullscreenmode == true) {
        $map.addClass("fullscreen-map");
      }
      else {
        $map.removeClass("fullscreen-map");
      }
    }
}
