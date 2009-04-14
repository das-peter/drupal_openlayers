// $Id$

/**
 * @notes
 *
 *
 */

/**
 * When document is ready for JS
 * 
 * Add the themed map container (HTML) to the document. 
 * Also set-up the click functionality for the Show/Hide WKT Fields
 */
jQuery(document).ready(function() {
  // Go through CCK Fields and diplay map
  var fieldContainer = '';
  for (var mapid in Drupal.settings.openlayers_cck.maps) {
    fieldContainer = Drupal.settings.openlayers_cck.maps[mapid].field_container;
    // Add Themed Map container
    $('#' + fieldContainer).before(Drupal.settings.openlayers_cck.maps[mapid].field_map_themed);
    $('#' + fieldContainer).hide();
    
    // Define click actions for WKT Switcher
    $('#' + mapid + '-wkt-switcher').click(function() {
      var mapid = $(this).attr('rel');
      var fieldContainer = Drupal.settings.openlayers_cck.maps[mapid].field_container;
      $('#' + fieldContainer).toggle();
      return false;
    });
    
    //Link each textarea to their map
    $('#' + fieldContainer + ' textarea').attr('rel',mapid);
    
    // Set-up onblur event so that when users change the raw WKT fields, the map gets updated in real time
    // @@BUG: For some reason after adding another text field by drawing an extra feature (or clicking "add another item") this is no longer triggering
    $('#' + fieldContainer + ' textarea').blur(function() {
      var mapid = $(this).attr('rel');
      //Create the new feature
      if ($(this).val() != ''){
      	var newFeature = openlayersCCKLoadFeatureFromTextarea(mapid, this);
      }
      
      //Delete the existing feature
  		for (var l in Drupal.openlayers.activeObjects[mapid].layers['openlayers_cck_vector'].features) {
  		  if (Drupal.openlayers.activeObjects[mapid].layers['openlayers_cck_vector'].features[l].drupalField == $(this).attr('id')) {
  		  	Drupal.openlayers.activeObjects[mapid].layers['openlayers_cck_vector'].features[l].destroy();
  	    }
  	  }
  	    
  	  //Repopulate with a new feature.
      if ($(this).val() != ''){
	      Drupal.openlayers.activeObjects[mapid].layers['openlayers_cck_vector'].addFeatures([newFeature]);
  		}
    });
  }
});

/**
 * OpenLayers CCK Feature Added Handler
 * 
 * This function is triggered when a feature is added by the user
 */
function openlayersCCKFeatureAdded(event) {
	//Get the feature we have just added out of the event object
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
  
  // This is the id of the textfield we will be assigning this feature to.
  var wktFieldNewID = 'edit-' + fieldName + '-' + featureNew + '-wkt';
  // This is the "Add another item" button
  var wktFieldAddID = 'edit-' + fieldName + '-' + fieldName + '-add-more';
  
  // Clone the geometry so we may safetly work on it without hurting the feature
  var geometry = feature.geometry.clone();
    
  // Assign field to feature
  feature.drupalField = wktFieldNewID;
  
  // @@TODO:  Transform the geometry if nessisary
  // update CCK field with WKT values
  var wkt = geometry.toString();
  $('#' + wktFieldNewID).val(wkt);
  
  //Link the field to the map
  $('#' + wktFieldNewID).attr('rel',feature.layer.map.mapid);
    
  // Add another field ..
  // @@BUG:  When triggering this function it is reloading all of Drupal.settings.openlayers.  On the reload for some reason it is only reloading our current CCK-field, not all CCK-fields, and so is causing the error: Drupal.settings.openlayers.maps[parsedRel.mapid] is undefined
  $('#' + wktFieldAddID).trigger('mousedown');
}

/**
 * Get Values From CCK and populate the map with shapes
 */
function openlayersCCKPopulateMap(mapid){  
  var featuresToAdd = [];
  var fieldContainer = Drupal.settings.openlayers_cck.maps[mapid].field_container;
  
  // Cycle through the fieldContainer item and read WKT from all the textareas
  $('#' + fieldContainer + ' textarea').each(function(){
    if ($(this).val() != ''){
      var newFeature = openlayersCCKLoadFeatureFromTextarea(mapid, this);
      if (newFeature != false) featuresToAdd.push(newFeature);
    }
  });
  
  // Add features to vector
  if (featuresToAdd.length != 0){
    Drupal.openlayers.activeObjects[mapid].layers['openlayers_cck_vector'].addFeatures(featuresToAdd);
  }
}

/**
 * OpenLayers CCK Load Feature From Textarea
 * 
 * This function loads the WKT from a textarea, and returns an OpenLayers feature
 */
function openlayersCCKLoadFeatureFromTextarea(mapid, textarea){
	var wktFormat = new OpenLayers.Format.WKT();
	
	//read the wkt values into an OpenLayers geometry object
  var newFeature = wktFormat.read($(textarea).val());
  if (typeof(newFeature) == "undefined"){
    alert(Drupal.t('WKT is not valid'));
    return false;
  }
  else{
  	// @@TODO: project the geometry if our map has a different geospatial projection as our CCK geo data.
    
    // Link the feature to the field.
    newFeature.drupalField = $(textarea).attr('id');
    
    //Link the field to the map
    $(textarea).attr('rel',mapid);
    
		return newFeature;
  }
}


/**
 * When the layer is done loading, load in the values from the CCK text fields if it is the correct layer.
 */
function openlayersCCKLoadValues(event){
  if (event.layer.drupalId == "openlayers_cck_vector"){
    openlayersCCKPopulateMap(event.layer.map.mapid);
  }
}


/**
 * When the any feature on the layer is modified, fill in the WKT values into the text fields
 */
function openlayersCCKFeatureModified(event){
  var feature = event.feature;
  
  // If modified, update CCK fields
  var wkt = feature.geometry.toString();
  $('#' + feature.drupalField).val(wkt);
  
  // @@TODO: If deleted, remove value form field
  
}