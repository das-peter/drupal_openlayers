(function($) {
  $(document).on('openlayers.build_start', function(event, objects) {
    console.time('Total building time');
    console.group("********************* Starting building " + objects.objects.map.machine_name + " *********************");
  });

  var message;
  var type = null;
  $(document).on('openlayers.object_pre_alter', function(event, objects) {
    if (type == undefined) {
      console.groupCollapsed("Building " + objects.type);
    } else if (type != objects.type) {
      console.groupEnd();
      console.groupCollapsed("Building " + objects.type);
    }
    type = objects.type;

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
    console.timeEnd('Total building time');
  });
})(jQuery);
