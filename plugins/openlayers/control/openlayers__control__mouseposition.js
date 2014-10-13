Drupal.openlayers.openlayers__control__mouseposition = function(data) {
  data.options.coordinateFormat = ol.coordinate.createStringXY(4);
  //options.projection = 'EPSG:4326';
  return new ol.control.MousePosition(data.options);
}
