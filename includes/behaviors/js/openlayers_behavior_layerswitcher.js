
/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * Layer Switcher Behavior
 */
(function($) {
  Drupal.behaviors.openlayers_behavior_layerswitcher = {
    'attach': function(context, settings) {
      var data = $(context).data('openlayers');
      if (data && data.map.behaviors['openlayers_behavior_layerswitcher']) {
        var options = data.map.behaviors['openlayers_behavior_layerswitcher'];

        // Add control
        var control = new OpenLayers.Control.LayerSwitcher(options);
        data.openlayers.addControl(control);
        control.activate();
      }
    }
  };
})(jQuery);
