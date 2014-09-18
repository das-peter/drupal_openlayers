Drupal.openlayers.openlayers_component_bootstrapjs_alert = function(options, map) {

  jQuery("#"+map.getTarget()).before("<div class='alert alert-success' data-dismiss='alert'><a href='#' class='close' data-dismiss='alert'>&times;</a>"+options.message+"</div>");

};
