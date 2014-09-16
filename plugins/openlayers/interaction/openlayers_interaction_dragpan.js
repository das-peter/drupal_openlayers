Drupal.openlayers.openlayers_interaction_dragpan = function(options) {
  // Todo: make a check on those values in js or php ?
  var kinetic = new ol.Kinetic(options.decay, options.minVelocity, options.delay);
  return new ol.interaction.DragPan({kinetic: kinetic});
};
