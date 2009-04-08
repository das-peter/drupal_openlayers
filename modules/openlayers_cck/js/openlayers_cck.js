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
    // @@TODO: not working, seems to keep the most recent fieldContainer
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
  var geometry = feature.layer.features[featureNew].geometry.clone();
  // Assign field to feature
  feature.layer.features[featureNew].field = wktFieldNewID;
  // geometry.transform(map_proj, maps[field_name]['dbproj']);
  var wkt = geometry.toString();
  $('#' + wktFieldNewID).val(wkt);
  
  // If delete, remove value form field
  
  // Add another field
  $('#' + wktFieldAddID).trigger('mousedown');
}

/**
 * Get Values From CCK
 */
function openlayersCCKPopulateMap(features, vector){
  var featuresAdd = [];
  var wktFormat = new OpenLayers.Format.WKT();
  
  // Get Features
  for (var f in features) {
    if (features[f].wkt) {
      var wkt = wktFormat.read(features[f].wkt);
      // wkt.geometry.transform(maps[field_name]['dbproj'], map_proj);
      featuresAdd.push(wkt);
    }
  }
  
  // Add features to vector
  if (featuresAdd.length != 0){
    vector.addFeatures(featuresAdd);
  }
}