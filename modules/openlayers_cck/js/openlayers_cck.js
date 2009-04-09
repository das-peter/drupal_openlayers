// $Id$

/**
 * @notes
 *
 *
 */

/**
 * When document is ready for JS
 */
jQuery(document).ready(function() {
  // Go through CCK Fields and diplay map
  var fieldContainer = '';
  for (var map in Drupal.settings.openlayers_cck.maps) {
    fieldContainer = Drupal.settings.openlayers_cck.maps[map].field_container;
    // Add Themed Map container
    $('#' + fieldContainer).before(Drupal.settings.openlayers_cck.maps[map].field_map_themed);
    $('#' + fieldContainer).hide();
    
    // Get default features
    // @@TODO: not sure how to do this?	
    // openlayersCCKPopulateMap(Drupal.settings.openlayers_cck.maps[map].field_items, vector)
    
    // Define click actions for WKT Switcher
    $('#' + map + '-wkt-switcher').click(function() {
    	var mapid = $(this).attr('rel');
    	var fieldContainer = Drupal.settings.openlayers_cck.maps[mapid].field_container;
      $('#' + fieldContainer).toggle();
      return false;
    });
  }
});

/**
 * OpenLayers CCK Feature Handler
 */
function openlayersCCKFeatureHandler(event) {
	
	var feature = event.feature;
	
  // Make some variables
  var featureCount = feature.layer.features.length;
  var featureNew = featureCount - 1;
  
  var mapid = feature.layer.map.mapid;
  
  // Get field names
  var fieldName;
  for (var map in Drupal.settings.openlayers_cck.maps) {
    if (map == mapid) {
      fieldName = Drupal.settings.openlayers_cck.maps[map].field_name_js;
    }
  }
  
  var wktFieldNewID = 'edit-' + fieldName + '-' + featureNew + '-wkt';
  var wktFieldAddID = 'edit-' + fieldName + '-' + fieldName + '-add-more';
  
  // If new features, add field to feature
    
  var geometry = feature.geometry.clone();
    
  // Assign field to feature
  feature.drupalField = wktFieldNewID;
  // geometry.transform(map_proj, maps[field_name]['dbproj']);
  var wkt = geometry.toString();
  $('#' + wktFieldNewID).val(wkt);
  
  // If delete, remove value form field
  
  // Add another field ..
  // @@TODO:  When reloading this function is reloading all of Drupal.settings.openlayers  .  On the reload for some reason it is only reloading our current CCK-field, not all CCK-fields, and so is causing the error: Drupal.settings.openlayers.maps[parsedRel.mapid] is undefined
  $('#' + wktFieldAddID).trigger('mousedown');
}

/**
 * Get Values From CCK
 */
function openlayersCCKPopulateMap(features, vector){
  var featuresToAdd = [];
  var wktFormat = new OpenLayers.Format.WKT();
  
  // Get Features
  for (var f in features) {
    if (features[f].wkt) {
      var wkt = wktFormat.read(features[f].wkt);
      // wkt.geometry.transform(maps[field_name]['dbproj'], map_proj);
      featuresToAdd.push(wkt);
    }
  }
  
  // Add features to vector
  if (featuresToAdd.length != 0){
    vector.addFeatures(featuresToAdd);
  }
}


/**
 * When the layer is done loading, load in the values from the CCK text fields if it is the correct layer.
 */
function openlayersCCKLoadValues(event){
	if (event.layer.drupalId == "default_vector"){
		//Do something with openlayersCCKPopulateMap
	}
}