// $Id$

/**
 * @file
 * Main JS file for open_layers_cck
 *
 * @ingroup openlayers
 */

/**
 * Global Object for Namespace
 */
var OL = OL || {};
OL.CCK = OL.CCK || {};

/**
 * When document is ready for JS
 * 
 * Add the themed map container (HTML) to the document. 
 * Also set-up the click functionality for the Show/Hide WKT Fields
 */
jQuery(document).ready(function() {
  // Move our openlayers_cck map definitions so they will not 
  // be overwritten by Drupal AJAX / AHAH trigers.
  OL.CCK.maps = Drupal.settings.openlayers_cck.maps;
  
  // Go through CCK Fields and diplay map
  var fieldContainer = '';
  for (var mapid in OL.CCK.maps) {
    fieldContainer = OL.CCK.maps[mapid].field_container;
    // Add Themed Map container
    $('#' + fieldContainer).before(OL.CCK.maps[mapid].field_map_themed);
    $('#' + fieldContainer).hide();
    
    // Define click actions for WKT Switcher
    $('#' + mapid + '-wkt-switcher').click(function() {
      var mapid = $(this).attr('rel');
      var fieldContainer = OL.CCK.maps[mapid].field_container;
      $('#' + fieldContainer).toggle();
      return false;
    });
  }
  
  // Attach Drupal Behavoirs which will call the openlayers rendering function
  // again now that we have put in the correct markup for the maps.
  Drupal.attachBehaviors();
});

/**
 * Implementation of Drupal Behavoir
 */
Drupal.behaviors.openlayers_cck = function(context) {
  // Go through OpenLayers data
  for (var mapid in Drupal.settings.openlayers_cck.maps) {
    // Add onblur events to fields
    $('textarea[rel=' + mapid + ']').blur(function() {
      OL.CCK.alterFeatureFromField($(this));
    });
  }
};

/**
 * OpenLayers CCK Populate Map
 * 
 * Get Values From CCK and populate the map with shapes
 *
 * @param mapid
 *   String ID of map
 */
OL.CCK.populateMap = function(mapid) {  
  var featuresToAdd = [];
  var fieldContainer = OL.CCK.maps[mapid].field_container;
  
  // Cycle through the fieldContainer item and read WKT from all the textareas
  $('#' + fieldContainer + ' textarea').each(function(){
    if ($(this).val() != ''){
      var newFeature = OL.CCK.loadFeatureFromTextarea(mapid, this);
      if (newFeature != false) featuresToAdd.push(newFeature);
    }
  });
  
  // Add features to vector
  if (featuresToAdd.length != 0) {
    OL.maps[mapid].layers['openlayers_cck_vector'].addFeatures(featuresToAdd);
  }
}

/**
 * OpenLayers CCK Load Feature From Textarea
 * 
 * This function loads the WKT from a textarea, and returns an OpenLayers feature
 *
 * @param mapid
 *   String ID of map
 * @param textarea
 *   DOM element
 * @return
 *   New feature object or false if error
 */
OL.CCK.loadFeatureFromTextarea = function(mapid, textarea) {
	var wktFormat = new OpenLayers.Format.WKT();
	
	// read the wkt values into an OpenLayers geometry object
  var newFeature = wktFormat.read($(textarea).val());
  if (typeof(newFeature) == "undefined") {
    // TODO: Notification a little less harsh
    alert(Drupal.t('WKT is not valid'));
    return false;
  }
  else {
  	// Project the geometry if our map has a different geospatial 
  	// projection as our CCK geo data.
    if (OL.maps[mapid].projection != OL.mapDefs[mapid].options.displayProjection) {
      newFeature.geometry.transform(OL.maps[mapid].displayProjection, OL.maps[mapid].projection);
    }
    
    // Link the feature to the field.
    newFeature.drupalField = $(textarea).attr('id');
		return newFeature;
  }
}

/**
 * OpenLayers CCK Load Values
 * 
 * When the layer is done loading, load in the values from 
 * the CCK text fields if it is the correct layer.
 *
 * @param event
 *   Event object
 */
OL.EventHandlers.CCKLoadValues = function(event) {
  OL.CCK.populateMap(event.mapDef.id);
}

/**
 * OpenLayers CCK Feature Selected
 * 
 * When a feature is selected, make the WKT field light 
 * up so we know which field we are editing
 *
 * @param event
 *   Event object
 */
OL.EventHandlers.CCKFeaturesSelected = function(event) {
  var feature = event.feature;
  $("#" + feature.drupalField).addClass('openlayers-cck-feature-selected');
}

/**
 * OpenLayers CCK Feature Unselected
 * 
 * When a feature is selected, make the WKT field light 
 * up so we know which field we are editing
 *
 * @param event
 *   Event object
 */
OL.EventHandlers.CCKFeaturesUnselected = function(event) {
  var feature = event.feature;
  $("#" + feature.drupalField).removeClass('openlayers-cck-feature-selected');
}

/**
 * OpenLayers CCK Alter Feature from Field
 * 
 * This will generally be called by an onblur event so that 
 * when users change the raw WKT fields, the map gets updated 
 * in real time
 *
 * @param textarea
 *   DOM element
 */
OL.CCK.alterFeatureFromField = function(textarea) {
  var mapid = $(textarea).attr('rel');
  var wkt = $(textarea).val();
  
  // Create the new feature
  if ($(textarea).val() != ''){
    var newFeature = OL.CCK.loadFeatureFromTextarea(mapid, textarea);
  }
  
  // Delete the existing feature
  for (var l in OL.maps[mapid].layers['openlayers_cck_vector'].features) {
	  if (OL.maps[mapid].layers['openlayers_cck_vector'].features[l].drupalField == $(textarea).attr('id')) {
	    OL.maps[mapid].layers['openlayers_cck_vector'].features[l].destroy();
    }
  }
    
  // Repopulate with a new feature.
   if (wkt != '') {
    $(textarea).val(wkt);
    if (newFeature != false) {
      OL.maps[mapid].layers['openlayers_cck_vector'].addFeatures([newFeature]);
    }
	}
}

/**
 * OpenLayers CCK Feature Added Handler
 * 
 * This function is triggered when a feature is added by the user
 *
 * @param event
 *   Event object
 */
OL.CCK.featureAdded = function(event) {
	//Get the feature we have just added out of the event object
  var feature = event.feature;
  var mapid = feature.layer.map.mapid;
  
  // Get field names
  var fieldName = OL.CCK.maps[mapid].field_name_js;
  
  // Get the index number of the newly added field
  // Check if we are creating a new node with 2 fresh fields open
  if ($('#' + fieldName + '-items textarea').size() == 2 && $('#' + fieldName + '-items textarea:first').val() == '') {
  	// We are creating a new node with two fresh fields open
  	var newNode = true;
  	var newFeatureID = 0;
  }
  else {
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
  
  // Project the geometry if our map has a different geospatial projection as our CCK geo data.
  if (OL.maps[mapid].projection != OL.mapDefs[mapid].options.displayProjection){
    geometry.transform(OL.maps[mapid].projection, OL.maps[mapid].displayProjection);
  }
  
  // Update CCK field with WKT values
  var wkt = geometry.toString();
  $('#' + wktFieldNewID).val(wkt);
  
  // Link the field to the map
  $('#' + wktFieldNewID).attr('rel',feature.layer.map.mapid);
    
  // Add another field if we need to..
  if (!newNode) $('#' + wktFieldAddID).trigger('mousedown');
}

/**
 * OpenLayers CCK Feaure Modified Handler
 * 
 * When the any feature on the layer is modified, fill in 
 * the WKT values into the text fields.
 *
 * @param event
 *   Event object
 */
OL.CCK.featureModified = function(event) {
  var feature = event.feature;
  var mapid = feature.layer.map.mapid;
  
  // Clone the geometry so we may safetly work on it without hurting the feature
  var geometry = feature.geometry.clone();
  
  // Project the geometry if our map has a different geospatial projection as our CCK geo data.
  if (OL.maps[mapid].projection != OL.maps[mapid].displayProjection) {
    geometry.transform(OL.maps[mapid].projection, OL.maps[mapid].displayProjection);
  }
  
  // update CCK fields
  var wkt = geometry.toString();
  $('#' + feature.drupalField).val(wkt);
}

/**
 * OpenLayers CCK Feaure Removed Handler
 * 
 * When the any feature on the layer is deleted, strip out the 
 * WKT values from the CCK value fields.
 *
 * @param event
 *   Event object
 */
OL.CCK.featureRemoved = function(event) {
  var feature = event.feature;
  
  // Empty the CCK field values.
  $('#' + feature.drupalField).val('').removeClass('openlayers-cck-feature-selected');
}