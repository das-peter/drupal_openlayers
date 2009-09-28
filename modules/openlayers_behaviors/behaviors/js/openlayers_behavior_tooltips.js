// $Id$

/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * Tooltips Behavior
 */
Drupal.behaviors.openlayers_behavior_tooltips = function(context) {
  var data = $(context).data('openlayers');
  if (data && data.map.behaviors['openlayers_behavior_tooltips']) {
    // Collect vector layers
    var vector_layers = [];
    for (var key in data.openlayers.layers) {
      var layer = data.openlayers.layers[key];
      if (layer.isVector == true) {
        vector_layers.push(layer);
      }
    }

    // Add control
    var control = new OpenLayers.Control.SelectFeature(
      vector_layers,
      {
        activeByDefault: true,
        highlightOnly: false,
        onSelect: Drupal.openlayers_behavior_tooltips.select,
        onUnselect: Drupal.openlayers_behavior_tooltips.unselect,
        multiple: false,
        hover: true,
        callbacks: {
          'over': Drupal.openlayers_behavior_tooltips.select,
          'out': Drupal.openlayers_behavior_tooltips.unselect
        }
      }
    );
    data.openlayers.addControl(control);
    control.activate();
  }
}

Drupal.openlayers_behavior_tooltips = {
  'select': function(feature) {
    selectedFeature = feature;
    if(feature.attributes.name) {
      text = "<div class='ol-popup-name'>" + feature.attributes.name + "</div>";
    }
    if(feature.attributes.description) {
      text += "<div class='ol-popup-description'>"+feature.attributes.description + "</div>";
    }
    popup = new OpenLayers.Popup.Anchored(
      "openlayers_behavior_tooltips",
      feature.geometry.getBounds().getCenterLonLat(),
      new OpenLayers.Size(75, 75),
      text,
      feature.marker,
      false,
      function() {});

    // Clear out styles on popup -- themers can alter the styles of the inner DIVs effectively enough.
    popup.setBackgroundColor('transparent');
    popup.setBorder('0px');
    $(popup.contentDiv).hover(
      function() { Drupal.openlayers_popup_retain = true; },
      function() { 
        Drupal.openlayers_popup_retain = false;
        Drupal.openlayers_behavior_tooltips.unselect(selectedFeature);
      }
    );
    feature.popup = popup;
    feature.layer.map.addPopup(popup);
  },

  'unselect': function(feature) {
    if(!Drupal.openlayers_popup_retain) {
      feature.layer.map.removePopup(feature.popup);
      feature.popup.destroy();
      feature.popup = null;
    }
  }
}
