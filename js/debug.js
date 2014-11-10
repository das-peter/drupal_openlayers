(function($) {
  $(document).on('openlayers.build_start', function(event, objects) {
    console.time('Building time');
    Drupal.openlayers.console.info("********************* Starting building OL objects *********************");
  });

  $(document).on('openlayers.object_pre_alter', function(event, objects) {
    Drupal.openlayers.console.info("Building " + objects.type + "...");
    if (!(objects.data.machine_name in objects.cache[objects.type])) {
      Drupal.openlayers.console.info(" Computing " + objects.type + " " + objects.data.machine_name + "...");
    } else {
      Drupal.openlayers.console.info(" Loading " + objects.type + " " + objects.data.machine_name + " from cache...");
    }
  });

  $(document).on('openlayers.object_post_alter', function(event, objects) {
    Drupal.openlayers.console.info("Building " + objects.type + "... done.");
  });

  $(document).on('openlayers.build_stop', function(event, objects) {
    Drupal.openlayers.console.info("********************* End of building OL objects *********************");
    console.timeEnd('Building time');
  });
})(jQuery);
