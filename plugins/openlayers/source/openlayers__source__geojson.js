Drupal.openlayers.openlayers__source__geojson = function(data) {
  data.options.projection = 'EPSG:3857';

  //// If GeoJSON data is provided with the layer, use that.  Otherwise
  //// check if BBOX, then finally use AJAX method.
  //if (data.options.geojson_data) {
  //  var layer = new ol.Layer.Vector(title, options);
  //
  //  // Read data in.
  //  features = new ol.Format.GeoJSON(geojson_options).read(data.options.geojson_data);
  //  if (features) {
  //    // If not array (ie only one feature)
  //    if (features.constructor != Array) {
  //      features = [features];
  //    }
  //  }
  //
  //  // Add features, if needed
  //  if (features) {
  //    layer.addFeatures(features);
  //    layer.events.triggerEvent('loadend');
  //  }
  //}
  //else {
    // @todo Add more strategies. Paging strategy would be really interesting
    //   to use with views_geojson.
    if (data.options.useBBOX) {
      data.options.format = new ol.format.GeoJSON();
      data.options.strategy = ol.loadingstrategy.bbox;
      data.options.loader = function(extent, resolution, projection) {
        // Ensure the bbox values are in the correct projection.
        var bbox = ol.proj.transformExtent(extent, data.map.getView().getProjection(), 'EPSG:4326');

        var params = {
          'bbox': bbox.join(','),
          'zoom': data.map.getView().getZoom()
        };
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

      ///*
      // * We override the triggerRead of the strategy so we can add a zoom=thecurrentzoomlevel in the URL
      // * This is used by the geocluster module http://drupal.org/project/geocluster
      // */
      //strategy.triggerRead =
      //  function(options) {
      //    if (this.response && !(options && data.options.noAbort === true)) {
      //      this.layer.protocol.abort(this.response);
      //      this.layer.events.triggerEvent("loadend");
      //    }
      //    this.layer.events.triggerEvent("loadstart");
      //    data.options.params = new Array();
      //    data.options.params['zoom'] = data.options.object.map.zoom;
      //    this.response = this.layer.protocol.read(
      //      ol.Util.applyDefaults({
      //        filter: this.createFilter(),
      //        callback: this.merge,
      //        scope: this
      //      }, options));
      //  };
      //data.options.strategies = [strategy];
    }
    else {
      // Fixed strategy.
      // @see http://dev.ol.org/releases/OpenLayers-2.12/doc/apidocs/files/OpenLayers/Strategy/Fixed-js.html
      if (data.options.preload) {
        data.options.strategies = [new ol.Strategy.Fixed({preload: true})];
      }
      else {
        data.options.strategies = [new ol.Strategy.Fixed()];
      }
    }
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
  //}

  return new ol.source.GeoJSON(data.options);
};
