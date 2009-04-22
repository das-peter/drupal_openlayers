// $Id$

/**
 * @file
 * Main JS file for open_layers_cck
 *
 * @ingroup openlayers
 */

/**
 * When document is ready for JS
 * 
 * Add the themed map container (HTML) to the document. 
 * Also set-up the click functionality for the Show/Hide WKT Fields
 */
jQuery(document).ready(function() {
  // Move our openlayers_cck map definitions so they will not be overwritten by Drupal AJAX / AHAH trigers.
  Drupal.openlayers_cck = {};
  Drupal.openlayers_cck.maps = Drupal.settings.openlayers_cck.maps;
  
  // Go through CCK Fields and diplay map
  var fieldContainer = '';
  for (var mapid in Drupal.openlayers_cck.maps) {
    fieldContainer = Drupal.openlayers_cck.maps[mapid].field_container;
    // Add Themed Map container
    $('#' + fieldContainer).before(Drupal.openlayers_cck.maps[mapid].field_map_themed);
    $('#' + fieldContainer).hide();
    
    // Define click actions for WKT Switcher
    $('#' + mapid + '-wkt-switcher').click(function() {
      var mapid = $(this).attr('rel');
      var fieldContainer = Drupal.openlayers_cck.maps[mapid].field_container;
      $('#' + fieldContainer).toggle();
      return false;
    });
    
    // Add onblur events to fields
    $('textarea[rel=' + mapid + ']').blur(function() {
      openlayersCCKAlterFeatureFromField($(this));
    });
  }
});

/**
 * OpenLayers CCK Populate Map
 * 
 * Get Values From CCK and populate the map with shapes
 */
function openlayersCCKPopulateMap(mapid){  
  var featuresToAdd = [];
  var fieldContainer = Drupal.openlayers_cck.maps[mapid].field_container;
  
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
    
		return newFeature;
  }
}

/**
 * OpenLayers CCK Load Values
 * 
 * When the layer is done loading, load in the values from the CCK text fields if it is the correct layer.
 */
function openlayersCCKLoadValues(event){
  if (event.layer.drupalId == "openlayers_cck_vector"){
    openlayersCCKPopulateMap(event.layer.map.mapid);
  }
}

/**
 * OpenLayers CCK Feature Selected
 * 
 * When a feature is selected, make the WKT field light up so we know which field we are editing
 */
function openlayersCCKFeaturesSelected(event){
 var feature = event.feature;
 $("#" + feature.drupalField).addClass('openlayers-cck-feature-selected');
}

/**
 * OpenLayers CCK Feature Unselected
 * 
 * When a feature is selected, make the WKT field light up so we know which field we are editing
 */
function openlayersCCKFeaturesUnselected(event){
 var feature = event.feature;
 $("#" + feature.drupalField).removeClass('openlayers-cck-feature-selected');
}

/**
 * OpenLayers CCK Alter Feature from Field
 * 
 * This will generally be called by an onblur event so that when users change the raw WKT fields,
 * the map gets updated in real time
 */
function openlayersCCKAlterFeatureFromField(textarea){
  var mapid = $(textarea).attr('rel');
  var wkt = $(textarea).val();
  
  //Create the new feature
  if ($(textarea).val() != ''){
    var newFeature = openlayersCCKLoadFeatureFromTextarea(mapid, textarea);
  }
  
  //Delete the existing feature
  for (var l in Drupal.openlayers.activeObjects[mapid].layers['openlayers_cck_vector'].features) {
	  if (Drupal.openlayers.activeObjects[mapid].layers['openlayers_cck_vector'].features[l].drupalField == $(textarea).attr('id')) {
	    Drupal.openlayers.activeObjects[mapid].layers['openlayers_cck_vector'].features[l].destroy();
    }
  }
    
  //Repopulate with a new feature.
   if (wkt != ''){
    $(textarea).val(wkt);
    if (newFeature != false) {
      Drupal.openlayers.activeObjects[mapid].layers['openlayers_cck_vector'].addFeatures([newFeature]);
    }
	}
}

/**
 * OpenLayers CCK Feature Added Handler
 * 
 * This function is triggered when a feature is added by the user
 */
function openlayersCCKFeatureAdded(event) {
	//Get the feature we have just added out of the event object
  var feature = event.feature;
  var mapid = feature.layer.map.mapid;
  
  // Get field names
  var fieldName;
  for (var map in Drupal.openlayers_cck.maps) {
    if (map == mapid) {
      fieldName = Drupal.openlayers_cck.maps[map].field_name_js;
    }
  }
  
  // Get the index number of the newly added field
  // Check if we are creating a new node with 2 fresh fields open
  if ($('#' + fieldName + '-items textarea').size() == 2 && $('#' + fieldName + '-items textarea:first').val() == ''){
  	// We are creating a new node with two fresh fields open
  	var newNode = true;
  	var newFeatureID = 0;
  }
  else{
  	// We are either not creating a new node, or there is already data filled in.
  	var newNode = false;
  	var newFeatureID = $('#' + fieldName + '-items textarea').size() -1;
  }

  // This is the id of the textfield we will be assigning this feature to.
  var wktFieldNewID = 'edit-' + fieldName + '-' + newFeatureID + '-wkt';
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
    
  // Add another field if we need to..
  if (!newNode) $('#' + wktFieldAddID).trigger('mousedown');
}

/**
 * OpenLayers CCK Feaure Modified Handler
 * 
 * When the any feature on the layer is modified, fill in the WKT values into the text fields.
 */
function openlayersCCKFeatureModified(event){
  var feature = event.feature;
    
  // update CCK fields
  var wkt = feature.geometry.toString();
  $('#' + feature.drupalField).val(wkt);
}

/**
 * OpenLayers CCK Feaure Removed Handler
 * 
 * When the any feature on the layer is deleted, strip out the WKT values from the CCK value fields.
 */
function openlayersCCKFeatureRemoved(event){
  var feature = event.feature;
  
  // Empty the CCK field values.
  $('#' + feature.drupalField).val('').removeClass('openlayers-cck-feature-selected');
}