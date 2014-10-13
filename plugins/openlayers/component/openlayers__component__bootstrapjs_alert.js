Drupal.openlayers.openlayers__component__bootstrapjs_alert = function(data) {

  jQuery("#" + data.map.getTarget()).before("<div class='alert alert-success' data-dismiss='alert'><a href='#' class='close' data-dismiss='alert'>&times;</a>" + data.options.message + "</div>");

};
