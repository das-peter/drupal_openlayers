(function($) {
  $(document).on('openlayers.build_start', function(event, objects) {
    console.time('Total building time');
    Drupal.openlayers.console.info("********************* Starting building OL objects *********************");
  });

  var message;
  $(document).on('openlayers.object_pre_alter', function(event, objects) {
    console.groupEnd();
    console.group("Building " + objects.type);
    if (!(objects.data.machine_name in objects.cache[objects.type])) {
      message = " Computing " + objects.type + " " + objects.data.machine_name + "...";
    } else {
      message = " Loading " + objects.type + " " + objects.data.machine_name + " from cache...";
    }
    console.time(message);
  });

  $(document).on('openlayers.object_post_alter', function(event, objects) {
    console.timeEnd(message);
  });

  $(document).on('openlayers.build_stop', function(event, objects) {
    console.groupEnd();
    Drupal.openlayers.console.info("********************* End of building OL objects *********************");
    console.timeEnd('Total building time');
  });
})(jQuery);
