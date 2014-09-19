Drupal.openlayers.openlayers_interaction_setvalues = function(options, map) {

  map.on('moveend', function(evt){
    var selector = '#' + options.latitude;
    jQuery(selector).val(map.getView().getCenter()[0]);
    var selector = '#' + options.longitude;
    jQuery(selector).val(map.getView().getCenter()[1]);
    var selector = '#' + options.rotation;
    jQuery(selector).val(Math.round(map.getView().getRotation()*(180/Math.PI)));
    var selector = '#' + options.zoom;
    jQuery(selector).val(map.getView().getZoom());
  });

  map.on('click', function(evt){
    var coordinate = evt.coordinate;
    var pan = ol.animation.pan({
      duration: 2000,
      source: (map.getView().getCenter())
    });
    map.beforeRender(pan);
    map.getView().setCenter(coordinate);
  });

  return new ol.interaction.Select(options);
};
