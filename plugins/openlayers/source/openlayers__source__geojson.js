Drupal.openlayers.openlayers__source__geojson = function(data) {
  data.options.projection = 'EPSG:3857';

  //// If GeoJSON data is provided with the layer, use that.  Otherwise
  //// check if BBOX, then finally use AJAX method.
  if (data.options.geojson_data) {
    data.options.text = data.options.geojson_data;
    return new ol.source.GeoJSON(data.options);
  }
  else {
    // @todo Add more strategies. Paging strategy would be really interesting
    //   to use with views_geojson.
    if (data.options.useBBOX) {
      data.options.format = new ol.format.GeoJSON();
      data.options.strategy = ol.loadingstrategy.bbox;
      data.options.loader = function(extent, resolution, projection) {
        // Ensure the bbox values are in the correct projection.
        var bbox = ol.proj.transformExtent(extent, data.map.getView().getProjection(), 'EPSG:4326');


        // Check if parameter forwarding is enabled.
        var params = {};
        if (data.options.paramForwarding) {
          var get_params = location.search.substring(location.search.indexOf('?') + 1 ).split('&');
          jQuery.each(get_params, function(i, val){
            var param = val.split('=');
            params[param[0]] = param[1] || '';
          })
        }
        params.bbox = bbox.join(',');
        params.zoom = data.map.getView().getZoom();

        var url = data.options.url;
        jQuery(document).trigger('openlayers.bbox_pre_loading', [{'url': url, 'params': params, 'data':  data}]);

        var that = this;
        jQuery.ajax({
          url: url,
          data: params,
          success: function(data) {
            that.addFeatures(that.readFeatures(data));
          }
        });
      };
      var vectorSource = new ol.source.ServerVector(data.options);
      return vectorSource;
    }
  //else {
  //  // Fixed strategy.
  //  // @see http://dev.ol.org/releases/OpenLayers-2.12/doc/apidocs/files/OpenLayers/Strategy/Fixed-js.html
  //  if (data.options.preload) {
  //    data.options.strategies = [new ol.Strategy.Fixed({preload: true})];
  //  }
  //  else {
  //    data.options.strategies = [new ol.Strategy.Fixed()];
  //  }
  //}
  //  if(data.options.useScript){
  //    //use Script protocol to get around xss issues and 405 error
  //    data.options.protocol = new ol.Protocol.Script({
  //      url: data.options.url,
  //      callbackKey: data.options.callbackKey,
  //      callbackPrefix: "callback:",
  //      filterToParams: function(filter, params) {
  //        // example to demonstrate BBOX serialization
  //        if (filter.type === ol.Filter.Spatial.BBOX) {
  //          params.bbox = filter.value.toArray();
  //          if (filter.projection) {
  //            params.bbox.push(filter.projection.getCode());
  //          }
  //        }
  //        return params;
  //      }
  //    });
  //  }
  //  else{
  //    data.options.protocol = new ol.Protocol.HTTP({
  //      url: data.options.url,
  //      format: new ol.Format.GeoJSON()
  //    });
  //  }
  //  var layer = new ol.Layer.Vector(title, options);
  }

  return new ol.source.GeoJSON(data.options);
};
