/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * OpenLayers Zoom to Layer Behavior
 */
Drupal.openlayers.addBehavior('openlayers_behavior_zoomtolayer', function (data, options) {
  var map = data.openlayers;
  var zoomtolayer_scale = options.zoomtolayer_scale;

  var layers = map.getLayersBy('drupalID', {
    test: function(id) {
      for (var i in options.zoomtolayer) {
        if (options.zoomtolayer[i] == id) {
          return true;
        }
      }
      return false;
    }
  });

  // Go through selected layers to get full extent.
  map.fullExtent = new OpenLayers.Bounds();

  jQuery(layers).each(function(index, layer) {

    if (layer instanceof OpenLayers.Layer.Vector) {

      if (layer.getDataExtent() !== null) {
        var layerextent = layer.getDataExtent().scale(zoomtolayer_scale);
        map.fullExtent.extend(layerextent);
        map.zoomToExtent(map.fullExtent);

        // If unable to find width due to single point,
        // zoom in with point_zoom_level option.
        if (layerextent.getWidth() == 0.0) {
          map.zoomTo(options.point_zoom_level);
        }

      } else {

        layer.events.register('loadend', layer, function() {
          var layerextent = layer.getDataExtent().scale(zoomtolayer_scale);
          map.fullExtent.extend(layerextent);
          map.zoomToExtent(map.fullExtent);

          // If unable to find width due to single point,
          // zoom in with point_zoom_level option.
          if (layerextent.getWidth() == 0.0) {
            map.zoomTo(options.point_zoom_level);
          }
        });

      }

    } else {
      var layerextent = layer.getDataExtent();
      // Check for valid layer extent
      if (layerextent != null) {
        map.fullExtent.extend(layerextent);
        map.zoomToExtent(map.fullExtent);
      }
    }
  });

  // If unable to find width due to single point,
  // zoom in with point_zoom_level option.
  if (map.fullExtent.getWidth() == 0.0) {
    map.zoomTo(options.point_zoom_level);
  }
  else {
    map.zoomToExtent(map.fullExtent.scale(zoomtolayer_scale));
  }
});
