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
 * Move Map Event Handler
 *
 * This event is called when before map is rendered
 * in order to move the elemnts outside of the fields.
 *
 * @param event
 *   Event object
 */
OL.EventHandlers.CCKMoveMap = function(event) {
  var mapid = event.mapDef.id;
  var fieldContainer = Drupal.settings.openlayers_cck.maps[mapid].field_container;
  var mapContainer = Drupal.settings.openlayers_cck.maps[mapid].map_container;
  var $fieldContainer = $('#' + fieldContainer);
  var $mapFull = $('#' + mapContainer);
  var $clonedMap = $mapFull.clone(true);
  $mapFull.remove();
  $fieldContainer.before($clonedMap);
}

/**
 * Main Setup Event for CCK Processing
 *
 * Evnet callback for map.
 *
 * @param event
 *   Event object
 */
OL.EventHandlers.CCKProcess = function(event) {
  OL.CCK.maps = OL.CCK.maps || Drupal.settings.openlayers_cck.maps || [];
  var mapid = event.mapDef.id;
  var $map = $('#' + mapid);
  var $textareas = $('textarea[rel=' + mapid + ']');
  var $wktSwitcher = $('#' + mapid + '-wkt-switcher');
  var fieldContainer = OL.CCK.maps[mapid].field_container;

  // WKT Switcher event
  $wktSwitcher.click(function() {
    $('#' + fieldContainer).toggle('normal');
    return false;
  });
  
  // Hide textareas by default
  $('#' + fieldContainer).hide();
  
  // Populate any existing fields
  OL.CCK.populateMap(mapid);
  
  // Add blur events to textareas
  $textareas.blur(function() {
    OL.CCK.alterFeatureFromField($(this));
  });
}

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
  $('#' + fieldContainer + ' textarea').each(function() {
    var $thisField = $(this);
    
    // Check value
    if ($thisField.val() != '') {
      var newFeature = OL.CCK.loadFeatureFromTextarea(mapid, $thisField);
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
 *   jQuery element
 * @return
 *   New feature object or false if error
 */
OL.CCK.loadFeatureFromTextarea = function(mapid, $textarea) {
	var wktFormat = new OpenLayers.Format.WKT();
  var newFeature = wktFormat.read($textarea.val());
	
	// Check if feature is defined
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
    newFeature.cckField = $textarea.attr('id');
		return newFeature;
  }
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
  $("#" + feature.cckField).addClass('openlayers-cck-feature-selected');
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
  $("#" + feature.cckField).removeClass('openlayers-cck-feature-selected');
}

/**
 * OpenLayers CCK Alter Feature from Field
 * 
 * This will generally be called by an onblur event so that 
 * when users change the raw WKT fields, the map gets updated 
 * in real time
 *
 * @param $textarea
 *   jQuery object
 */
OL.CCK.alterFeatureFromField = function($textarea) {
  var mapid = $textarea.attr('rel');
  var wkt = $textarea.val();
  
  // Create the new feature
  if ($textarea.val() != '') {
    var newFeature = OL.CCK.loadFeatureFromTextarea(mapid, $textarea);
  }
  
  // Delete the existing feature
  for (var l in OL.maps[mapid].layers['openlayers_cck_vector'].features) {
	  if (OL.maps[mapid].layers['openlayers_cck_vector'].features[l].cckField == $textarea.attr('id')) {
	    OL.maps[mapid].layers['openlayers_cck_vector'].features[l].destroy();
    }
  }
    
  // Repopulate with a new feature.
   if (wkt != '') {
    $textarea.val(wkt);
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
  var feature = event.feature;
  var mapid = feature.layer.map.mapid;
  var fieldName = OL.CCK.maps[mapid].field_name_js;
  var fieldContainer = OL.CCK.maps[mapid].field_container;
  var $textareas = $('#' + fieldContainer + ' textarea');
  var $addMore = $('#' + 'edit-' + fieldName + '-' + fieldName + '-add-more');
  var inputCount = $textareas.length;
  var isMultiple = $addMore.length;
  var newNode = true;
  var found = false;
  var firstTextareaID = $textareas.filter(':first').attr('id');
  var lastTextareaID = $textareas.filter(':last').attr('id');
  var newFeatureID = firstTextareaID;
  var geometry = feature.geometry.clone();

  // Check if there is an add more button
  if (isMultiple) {
    // Check if new field
    if (!newNode) {
      $addMore.trigger('mousedown');
    }
  }
  else {
    // Get next empty textarea
    $textareas.each(function(i) {
      var $thisField = $(this);
      if (($thisField.val() == '')) {
        newFeatureID = $thisField.attr('id');
        found = true;
        return false;
      }
    });
    
    // If empty textarea not found, use last one
    if (found == false) {
      // Make new feature ID, last counted textarea
      newFeatureID = lastTextareaID;
      // Clear out current feature
      $('#' + newFeatureID).val('').trigger('blur');
    }
    
    // This is the object of the textfield we will be assigning this feature to.
    var $wktFieldNew = $('#' + newFeatureID);
  
    // Assign field to feature
    feature.cckField = newFeatureID;
    
    // Project the geometry if our map has a different geospatial projection as our CCK geo data.
    if (OL.maps[mapid].projection != OL.mapDefs[mapid].options.displayProjection){
      geometry.transform(OL.maps[mapid].projection, OL.maps[mapid].displayProjection);
    }
    
    // Update CCK field with WKT values
    $wktFieldNew.val(geometry.toString());
    
    // Link the field to the map
    $wktFieldNew.attr('rel', feature.layer.map.mapid);
  }
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
  $('#' + feature.cckField).val(wkt);
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
  $('#' + feature.cckField).val('').removeClass('openlayers-cck-feature-selected');
}