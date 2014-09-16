Drupal.openlayers.openlayers_source_tiledebug = function(options) {

  var options = {
    tileGrid: new ol.tilegrid.XYZ({maxZoom: options.maxZoom}),
    // todo: handle projection stuff
    projection: 'EPSG:3857'
  };

  return new ol.source.TileDebug(options);
};
