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
  $map = $(this.map.div);
  extent = $map.data('openlayers').openlayers.getExtent();
  
  $map.parent().toggleClass('openlayers_map_fullscreen');
  $map.toggleClass('openlayers_map_fullscreen');
  $map.data('openlayers').openlayers.updateSize();
  $map.data('openlayers').openlayers.zoomToExtent(extent, true);
}
