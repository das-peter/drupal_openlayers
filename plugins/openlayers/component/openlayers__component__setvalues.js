Drupal.openlayers.openlayers__component__setvalues = function(data) {

  data.map.on('moveend', function(evt){
    var selector = '#' + data.options.latitude;
    jQuery(selector).val(data.map.getView().getCenter()[0]);
    var selector = '#' + data.options.longitude;
    jQuery(selector).val(data.map.getView().getCenter()[1]);
    var selector = '#' + data.options.rotation;
    jQuery(selector).val(Math.round(data.map.getView().getRotation() * (180 / Math.PI)));
    var selector = '#' + data.options.zoom;
    jQuery(selector).val(data.map.getView().getZoom());
  });

};
