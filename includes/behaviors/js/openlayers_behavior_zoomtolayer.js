// $Id$

/**
 * OpenLayers Popup Behavior
 */
Drupal.behaviors.openlayers_zoomtolayer = function(context) {
  var layerextent, layers, data = $(context).data('openlayers');
  if (data && data.map.behaviors['openlayers_behavior_zoomtolayer']) {
    map = data.openlayers;
    // TODO: just select layers you want, instead of all vector layers
    layers = map.getLayersByName(data.map.behaviors['openlayers_behavior_zoomtolayer'].zoomtolayer);
    for (var i in layers) {
      if (layers[i].features !== undefined) {
        layerextent = layers[i].getDataExtent();
        map.zoomToExtent(layerextent);
        if (layerextent.getWidth() == 0.0) {
          map.zoomTo(data.map.behaviors['openlayers_behavior_zoomtolayer'].point_zoom_level);
        }
      }
    }
  }
}
