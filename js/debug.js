(function($) {
  $(document).on('openlayers.build_start', function(event, objects) {
    console.time('Total building time');
    console.groupCollapsed("********************* Starting building " + objects.objects.map.machine_name + " *********************");
  });

  var message;
  var type = null;
  $(document).on('openlayers.object_pre_alter', function(event, objects) {
    if (!(objects.data.machine_name in objects.cache[objects.type])) {
      message = " Computing " + objects.type + " " + objects.data.machine_name + "...";
    } else {
      message = " Loading " + objects.type + " " + objects.data.machine_name + " from cache...";
    }

    if (type == undefined || type != objects.type) {
      console.groupCollapsed("Building " + objects.type);
    }
    type = objects.type;

    console.time(message);

  });

  $(document).on('openlayers.object_post_alter', function(event, objects) {
    console.timeEnd(message);
    if (objects.count == 1) {
      console.groupEnd();
    }
  });

  $(document).on('openlayers.build_stop', function(event, objects) {
    console.timeEnd('Total building time');
    console.groupEnd();
  });
})(jQuery);
