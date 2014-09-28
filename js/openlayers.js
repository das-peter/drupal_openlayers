/*jslint white: false */
/*jslint forin: true */
/*global OpenLayers Drupal $ document jQuery window */

document.namespaces;

(function($) {
  Drupal.behaviors.openlayers = {
    'attach': function(context, settings) {

      if (typeof(Drupal.settings.openlayers) === 'object' && Drupal.settings.openlayers.maps) {
        $('.openlayers-map').once('openlayers-map', function() {
          var map_id = $(this).attr('id');
          if (map_id in Drupal.settings.openlayers.maps) {
            try {
              var object = Drupal.settings.openlayers.maps[map_id];

              var layers = object.layer || [];
              var controls = object.control || [];
              var interactions = object.interaction || [];
              var sources = object.source || [];
              var components = object.component || [];
              // Todo: see why this is not working with ajax.
              var objects = {};
              objects.sources = {};
              objects.controls = {};
              objects.interactions = {};
              objects.components = {};
              objects.layers = {};
              objects.maps = {};

              object.map.options.layers = [];
              object.map.options.controls = [];
              object.map.options.interactions = [];
              object.map.options.components = [];

              Drupal.openlayers.console.info("Creating map " + object.map.machine_name + "...");
              var map = Drupal.openlayers[object.map.class](object.map.options, object.map, context);
              objects.maps[map_id] = map;
              Drupal.openlayers.console.info("Creating map object... done !");

              Drupal.openlayers.console.info("Building sources...");
              sources.map(function(data) {
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

              Drupal.openlayers.console.info("Building layers...");
              layers.map(function(data) {
                Drupal.openlayers.console.info(" Adding source to layer...");
                data.options.source = objects.sources[data.options.source];
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
              jQuery(context).data('openlayers', {'objects': objects});
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
    }
  };

  /**
   * Collection of helper methods.
   */
  Drupal.openlayers = {

    getObject: (function (context, type, data, map) {
      var cache = $(context).data('openlayers') || {};

      if (typeof cache.objects !== 'undefined') {
        cache = cache.objects;
      } else {
        cache.sources = [];
        cache.controls = [];
        cache.layers = [];
        cache.interactions = [];
        cache.components = [];
        cache.map = [];
      }

      cache = $.extend({}, cache.objects, cache);

      var object;
      if (typeof cache[type][data.machine_name] === 'undefined') {
        Drupal.openlayers.console.info(" Computing " + type + " " + data.machine_name + "...");
        cache[type][data.machine_name] = Drupal.openlayers[data.class](data.options, map, context);
        object = cache[type][data.machine_name];
      } else {
        Drupal.openlayers.console.info(" Loading " + type + " " + data.machine_name +" from cache...");
        object = cache[type][data.machine_name];
      }

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
      jQuery(["log", "debug", "info", "warn", "exception", "assert", "dir",
        "dirxml", "trace", "group", "groupEnd", "groupCollapsed", "profile",
        "profileEnd", "count", "clear", "time", "timeEnd", "timeStamp", "table",
        "error"]).each(function(index, functionName){
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
