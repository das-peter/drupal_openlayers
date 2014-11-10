(function($) {
  Drupal.behaviors.openlayers = {
    'attach': function(context, settings) {

      $('.openlayers-map').once('openlayers-map', function() {
        var map_id = $(this).attr('id');
        if (Drupal.settings.openlayers.maps[map_id] !== undefined) {

          var object = Drupal.settings.openlayers.maps[map_id];
          $(document).trigger('openlayers.build_start', [{'type': 'objects', 'objects': object, 'context': context}]);

          var count = 1,
            layers = object.layer || [],
            styles = object.style || [],
            controls = object.control || [],
            interactions = object.interaction || [],
            sources = object.source || [],
            components = object.component || [],
            objects = {sources: {}, controls: {}, interactions: {}, components: {}, styles: {}, layers: {}, maps: {}};

          object.map.options.layers = [];
          object.map.options.styles = [];
          object.map.options.controls = [];
          object.map.options.interactions = [];
          object.map.options.components = [];

          try {
            var map = Drupal.openlayers.getObject(context, 'maps', object.map, null, count);
            objects.maps[map.machine_name] = map;

            count = sources.length;
            sources.map(function(data) {
              if (data.options !== undefined && data.options.attributions !== undefined) {
                data.options.attributions = [new ol.Attribution({
                  'html': data.options.attributions
                })];
              }
              objects.sources[data.machine_name] = Drupal.openlayers.getObject(context, 'sources', data, map, count--);
            });

            count = controls.length;
            controls.map(function(data) {
              map.addControl(Drupal.openlayers.getObject(context, 'controls', data, map, count--));
            });

            count = interactions.length;
            interactions.map(function(data) {
              objects.interactions[data.machine_name] = Drupal.openlayers.getObject(context, 'interactions', data, map, count--);
              map.addInteraction(objects.interactions[data.machine_name]);
            });

            count = styles.length;
            styles.map(function(data) {
              objects.styles[data.machine_name] = Drupal.openlayers.getObject(context, 'styles', data, map, count--);
            });

            count = layers.length;
            layers.map(function(data) {
              data.options.source = objects.sources[data.options.source];
              if ((data.options.style !== undefined) && (objects.styles[data.options.style] !== undefined)) {
                data.options.style = objects.styles[data.options.style];
              }
              objects.layers[data.machine_name] = Drupal.openlayers.getObject(context, 'layers', data, map, count--);
              map.addLayer(objects.layers[data.machine_name]);
            });

            count = components.length;
            components.map(function(data) {
              objects.components[data.machine_name] = Drupal.openlayers.getObject(context, 'components', data, map, count--);
            });

            // Attach data to map DOM object
            $(document).trigger('openlayers.build_stop', [{'type': 'objects', 'objects': object, 'context': context}]);
            jQuery('body').data('openlayers', {'objects': objects});

          } catch (e) {
            if (typeof console !== 'undefined') {
              Drupal.openlayers.console.log(e.message);
              Drupal.openlayers.console.log(e.stack);
            } else {
              $(this).text('Error during map rendering: ' + e.message);
              $(this).text('Stack: ' + e.stack);
            }
          }
        }
      });
    }
  };

  /**
   * Collection of helper methods.
   */
  Drupal.openlayers = {

    'getObject': (function (context, type, data, map, count) {
      var cache = $('body').data('openlayers') || {};

      if (typeof cache.objects !== 'undefined') {
        cache = cache.objects;
      } else {
        cache.sources = [];
        cache.controls = [];
        cache.styles = [];
        cache.layers = [];
        cache.interactions = [];
        cache.components = [];
        cache.maps = [];
      }

      cache = $.extend({}, cache.objects, cache);

      $(document).trigger('openlayers.object_pre_alter', [{'type': type, 'machine_name': data.machine_name, 'data': data, 'map': map, 'cache': cache, 'context': context, 'count': count}]);
      var object;
      if (!(data.machine_name in cache[type])) {
        // TODO: Check why layers and maps doesnt cache.
        var object = Drupal.openlayers[data['class']]({'options': data.options, 'map': map, 'context': context, 'cache': cache});
        if (typeof object === 'object') {
          object.machine_name = data.machine_name;
        }
        cache[type][data.machine_name] = object;
      } else {
        object = cache[type][data.machine_name];
      }

      $(document).trigger('openlayers.object_post_alter', [{'type': type, 'object': object, 'data': data, 'map': map, 'cache': cache, 'context': context, 'count': count}]);
      jQuery('body').data('openlayers', {'objects': cache});
      return object;
    }),

    /**
     * Logging implementation that logs using the browser's logging API.
     * Falls back to doing nothing in case no such API is available. Simulates
     * the presece of Firebug's console API in Drupal.openlayers.console.
     */
    'console': (function(){
      var api = {};
      var logger;
      if (typeof(console)==="object" && typeof(console.log)==="function"){
        logger = function(){
          // Use console.log as fallback for missing parts of API if present.
          console.log.apply(console, arguments);
        };
      } else {
        logger = function (){
          // Ignore call as no logging facility is available.
        };
      }
      jQuery(["log", "debug", "info", "warn", "exception", "assert", "dir","dirxml", "trace", "group", "groupEnd", "groupCollapsed", "profile","profileEnd", "count", "clear", "time", "timeEnd", "timeStamp", "table","error"]).each(function(index, functionName){
        if (typeof(console)!=="object" || typeof(console[functionName])!=="function"){
          // Use fallback as browser does not provide implementation.
          api[functionName] = logger;
        } else {
          api[functionName] = function(){
            // Use browsers implementation.
            console[functionName].apply(console, arguments);
          };
        }
      });
      return api;
    })()
  };

})(jQuery);
