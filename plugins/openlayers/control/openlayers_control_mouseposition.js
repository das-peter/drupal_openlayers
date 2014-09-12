Drupal.openlayers.openlayers_control_mouseposition = function(options) {
  options.coordinateFormat = ol.coordinate.createStringXY(4);
  //options.projection = 'EPSG:4326';
  return new ol.control.MousePosition(options);
}
