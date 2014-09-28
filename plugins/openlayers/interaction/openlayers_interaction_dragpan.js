Drupal.openlayers.openlayers_interaction_dragpan = function(data) {
  // Todo: make a check on those values in js or php ?
  var kinetic = new ol.Kinetic(data.options.decay, data.options.minVelocity, data.options.delay);
  return new ol.interaction.DragPan({kinetic: kinetic});
};
