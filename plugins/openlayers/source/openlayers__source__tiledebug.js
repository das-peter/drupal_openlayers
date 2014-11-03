Drupal.openlayers.openlayers__source__tiledebug = function(data) {

  var options = {
    tileGrid: new ol.tilegrid.XYZ({maxZoom: data.options.maxZoom}),
    // todo: handle projection stuff
    projection: 'EPSG:3857'
  };

  if (data.options.attributions !== undefined) {
    options.attributions = [new ol.Attribution({
      'html': data.options.attributions
    })];
  }

  return new ol.source.TileDebug(options);
};
