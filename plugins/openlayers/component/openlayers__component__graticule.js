Drupal.openlayers.openlayers__component__graticule = function(data) {

  var graticule = new ol.Graticule({
    strokeStyle: new ol.style.Stroke({
      color: 'rgba(' + data.options.rgba + ')',
      width: data.options.width,
      lineDash: data.options.lineDash.split(',').map(Number)
    }),
    map: data.map,
    projection: data.map.getView().getProjection()
  });

};
