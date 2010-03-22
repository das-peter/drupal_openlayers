// $Id$

/**
 * @file
 * Main JS file for openlayers_cck
 *
 * @ingroup openlayers_cck
 */
Drupal.behaviors.openlayers_cck_vector_layer = function(context) {
  var data = $(context).data('openlayers');
  if (data && data.map.behaviors['openlayers_cck_vector_layer']) {
    features = data.map.behaviors['openlayers_cck_vector_layer'].features;

    // Create options and layer
    var options = {
      drupalID: 'openlayers_cck_vector_layer'
    };
    var data_layer = new OpenLayers.Layer.Vector(Drupal.t("Data Layer"), options);
    
    // Add features and layers
    Drupal.openlayers.addFeatures(data.map, data_layer, features);
    data.openlayers.addLayer(data_layer);
  }
};
