(function($) {
  Drupal.behaviors.openlayers = {
    'attach': function(context, settings) {

      $('.openlayers-map').once('openlayers-map', function() {
        var map_id = $(this).attr('id');
        if (Drupal.settings.openlayers.maps[map_id] !== undefined) {

          var object = Drupal.settings.openlayers.maps[map_id],
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
            Drupal.openlayers.console.info("Creating map " + object.map.machine_name + "...");
            var map = Drupal.openlayers[object.map['class']]({'map': object.map, 'context': context});
            map.machine_name = object.map.machine_name;
            objects.maps[map_id] = map;
            Drupal.openlayers.console.info("Creating map object... done !");

            Drupal.openlayers.console.info("Building sources...");
            sources.map(function(data) {

              if (data.options !== undefined && data.options.attributions !== undefined) {
                data.options.attributions = [new ol.Attribution({
                  'html': data.options.attributions
                })];
              }

              objects.sources[data.machine_name] = Drupal.openlayers.getObject(context, 'sources', data, map);
            });
            Drupal.openlayers.console.info("Building sources... done !");

            Drupal.openlayers.console.info("Building controls...");
            controls.map(function(data) {
              map.addControl(Drupal.openlayers.getObject(context, 'controls', data, map));
            });
            Drupal.openlayers.console.info("Building controls... done !");

            Drupal.openlayers.console.info("Building interactions...");
            interactions.map(function(data) {
              objects.interactions[data.machine_name] = Drupal.openlayers.getObject(context, 'interactions', data, map);
              map.addInteraction(objects.interactions[data.machine_name]);
            });
            Drupal.openlayers.console.info("Building interactions... done !");

            Drupal.openlayers.console.info("Building styles...");
            styles.map(function(data) {
              objects.styles[data.machine_name] = Drupal.openlayers.getObject(context, 'styles', data, map);
            });
            Drupal.openlayers.console.info("Building styles... done !");

            Drupal.openlayers.console.info("Building layers...");
            layers.map(function(data) {
              Drupal.openlayers.console.info(" Adding source to layer...");
              data.options.source = objects.sources[data.options.source];
              if ((data.options.style !== undefined) && (objects.styles[data.options.style] !== undefined)) {
                Drupal.openlayers.console.info(" Adding style to layer...");
                data.options.style = objects.styles[data.options.style];
              }
              objects.layers[data.machine_name] = Drupal.openlayers.getObject(context, 'layers', data, map);
              Drupal.openlayers.console.info(" Adding layer to map...");
              map.addLayer(objects.layers[data.machine_name]);
            });
            Drupal.openlayers.console.info("Building layers... done !");

            Drupal.openlayers.console.info("Building components...");
            components.map(function(data) {
              objects.components[data.machine_name] = Drupal.openlayers.getObject(context, 'components', data, map);
            });
            Drupal.openlayers.console.info("Building components... done !");

            // Attach data to map DOM object
            Drupal.openlayers.console.info("Caching objects...");
            jQuery('body').data('openlayers', {'objects': objects});
            Drupal.openlayers.console.info("Caching objects... done !");

          } catch (e) {
            var errorMessage = e.name + ': ' + e.message;
            if (typeof console !== 'undefined') {
              Drupal.openlayers.console.log(errorMessage);
            } else {
              $(this).text('Error during map rendering: ' + errorMessage);
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

    'getObject': (function (context, type, data, map) {
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
        cache.map = [];
      }

      cache = $.extend({}, cache.objects, cache);

      var object;
      if (!(data.machine_name in cache[type])) {
        // TODO: Check why layers doesnt cache
        Drupal.openlayers.console.info(" Computing " + type + " " + data.machine_name + "...");
        var object = Drupal.openlayers[data['class']]({'options': data.options, 'map': map, 'context': context, 'cache': cache});
        if (typeof object === 'object') {
          object.machine_name = data.machine_name;
        }
        cache[type][data.machine_name] = object;
      } else {
        Drupal.openlayers.console.info(" Loading " + type + " " + data.machine_name +" from cache...");
        object = cache[type][data.machine_name];
      }

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
