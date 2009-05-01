$(document).ready(function(){
  // @@TODO: Namespace this using the form ID
  // @@BUG:  Maps will not display inside fieldsets that are collapsed by default
  
  // Hide the textfield form
  $('.openlayers-form-projection').parent().css('display','none');
  
  var trueProjection = $('.openlayers-form-projection').val();
  var radioSelected = false;
  
  // Go through each radio projection option
  $('.openlayers-form-easy-projection input').each(function(){
    
    // If it matches the true projection, then select it. 
    if ($(this).val() == trueProjection){
      $(this).attr('checked','checked');
      $('.openlayers-form-projection').parent().css('display','none');
      radioSelected = true;
    }
    
    // Attach events to the projection radio buttons
    $(this).change(function(){
      
      var projection = $(this).val();
      if (projection == 'other'){
        $('.openlayers-form-projection').parent().css('display','block');
      }
      else{
        $('.openlayers-form-projection').parent().css('display','none');
        $('.openlayers-form-projection').val(projection);
        
        // If we are using a web spherical-mercador projection, set the MaxResolution and MaxExtent (If they are not already set)
        openlayersWebSpericalMercadorAutoSettings();
        
        // Update our selectable layers
        openlayersUpdateSelectableLayers(projection);
      }
    });
    
    //If no radio has been selected, select "other"
    if (radioSelected == false){
      // @@TODO: use class to do this
      $('#edit-easy-projection-other').attr('checked','checked');
      $('.openlayers-form-projection').parent().css('display','block');
    }
    
  });
  
  // Center and zoom for zoom / center helper
  $('openlayers-form-lat').change(openlayersUpdateHelpmapCenter);
  $('openlayers-form-lon').change(openlayersUpdateHelpmapCenter);
  $('openlayers-form-zoom').change(openlayersUpdateHelpmapCenter);
  openlayersUpdateHelpmapCenter();
  
  // Set up the manual projection input so that layers will filter.
  $('.openlayers-form-projection').change(function(){
    openlayersUpdateSelectableLayers(false);
  });
  
  // Do an initial filter of the available layers
  openlayersUpdateSelectableLayers(trueProjection);
  
});

function openlayersWebSpericalMercadorAutoSettings(){
  
  
  // If the projection matches, we should potentially set max extent and max resolution.
  var projection = $('.openlayers-form-projection').val();
  if (projection == '900913' || projection == '3785') {
    var maxResolutionSet = false;
    var maxExtentSet = false;
    
    // Checking to see if we should automatically set the maximum Resolution
    if ($('.openlayers-form-maxResolution').val() == ''){
     $('.openlayers-form-maxResolution').val('156543.0339');
     maxResolutionSet = true;
    }
    
    // Checking to see if we should automatically set the maximum Extent
    if ($('.openlayers-form-maxExtent-left').val() == '' && $('.openlayers-form-maxExtent-right').val() == '' && $('.openlayers-form-maxExtent-bottom').val() == '' && $('.openlayers-form-maxExtent-top').val() == ''){
      $('.openlayers-form-maxExtent-left').val('-20037508.34');
      $('.openlayers-form-maxExtent-right').val('20037508.34');
      $('.openlayers-form-maxExtent-bottom').val('-20037508.34');
      $('.openlayers-form-maxExtent-top').val('20037508.34');
      maxExtentSet = true;
    }
    
    // Letting the user know we did some automatic changes
    if (maxResolutionSet && maxExtentSet){
      alert("Maximum Resolution and Maximum Extent have automatically been set for this projection.");
    }
    if (maxResolutionSet && !maxExtentSet){
      alert("Maximum Resolution has automatically been set for this projection.");
    }
    if (!maxResolutionSet && maxExtentSet){
      alert("Maximum Extent has automatically been set for this projection.");
    }
  }
  
  // If the projection does not match, we should potentially unset max extent and max resolution.
  if (projection != '900913'&& projection != '3785') {
    var maxResolutionUnset = false;
    var maxExtentUnset = false;
    
    // Checking to see if we should automatically unset the maximum Resolution
    if ($('.openlayers-form-maxResolution').val() == '156543.0339'){
     $('.openlayers-form-maxResolution').val('');
     maxResolutionUnset = true;
    }
    
    // Checking to see if we should automatically set the maximum Extent
    if ($('.openlayers-form-maxExtent-left').val() == '-20037508.34' && $('.openlayers-form-maxExtent-right').val() == '20037508.34' && $('.openlayers-form-maxExtent-bottom').val() == '-20037508.34' && $('.openlayers-form-maxExtent-top').val() == '20037508.34'){
      $('.openlayers-form-maxExtent-left').val('');
      $('.openlayers-form-maxExtent-right').val('');
      $('.openlayers-form-maxExtent-bottom').val('');
      $('.openlayers-form-maxExtent-top').val('');
      maxExtentUnset = true;
    }
    
    // Letting the user know we did some automatic changes
    if (maxResolutionUnset && maxExtentUnset){
      alert("Maximum Resolution and Maximum Extent have automatically been unset.");
    }
    if (maxResolutionUnset && !maxExtentUnset){
      alert("Maximum Resolution has automatically been unset.");
    }
    if (!maxResolutionUnset && maxExtentUnset){
      alert("Maximum Extent has automatically been unset.");
    }
  }
  
}


function openlayersUpdateSelectableLayers(projection){
  if (projection){
    $('input.openlayers-form-baselayers').each(function(){
      openlayersLayerCheckProjection(projection, this);
    });
    
    $('input.openlayers-form-default-layer').each(function(){
      openlayersLayerCheckProjection(projection, this);
    });
    
    $('input.openlayers-form-overlays').each(function(){
      openlayersLayerCheckProjection(projection, this);
    });
  }
  else {
    // No projection specified. Assume the user knows what they are doing and show all layers. 
    $('input.openlayers-form-baselayers').each(function(){
      $(this).parent().parent().css('display','block');
    });
    
    $('input.openlayers-form-default-layer').each(function(){
       $(this).parent().parent().css('display','block');
    });
    
    $('input.openlayers-form-overlays').each(function(){
       $(this).parent().parent().css('display','block');
    });
  }
}

function openlayersLayerCheckProjection(projection, domInputObject){
  $(domInputObject).parent().parent().css('display','none');
 
  var projectionMatch = false
  for (var l in Drupal.settings.openlayersForm.projectionLayers[projection]){
    if ($(domInputObject).val() == Drupal.settings.openlayersForm.projectionLayers[projection][l]){
      projectionMatch = true;
    }
  }
  
  if (projectionMatch){
    $(domInputObject).parent().parent().css('display','block');
  }
  else{
    $(domInputObject).removeAttr('checked');
  }
}


function openlayersUpdateHelpmapCenter() {
  var projection = $('.openlayers-form-projection').val();
  var zoom = $('.openlayers-form-zoom').val();
  var lat = $('.openlayers-form-lat').val();
  var lon = $('.openlayers-form-lon').val();
  
  if (lat != '' && lon != ''){
    var center = new OpenLayers.LonLat(lon, lat);
    center.transform(new OpenLayers.Projection('EPSG:' + projection), new OpenLayers.Projection('EPSG:4326'));
    
    Drupal.openlayers.activeObjects['openlayers-center-helpmap'].map.setCenter(center, zoom);  
  }
  
}

function openlayersUpdateCenterFormValues() {
  var helpmap = Drupal.openlayers.activeObjects['openlayers-center-helpmap'].map;
  var projection = $('.openlayers-form-projection').val();
  var zoom = helpmap.getZoom();
  
  var center = helpmap.getCenter();
  center.transform(new OpenLayers.Projection('EPSG:4326'),new OpenLayers.Projection('EPSG:' + projection));
  
  var lat = center.lat;
  var lon = center.lon;
  
  $('.openlayers-form-zoom').val(zoom);
  $('.openlayers-form-lat').val(lat);
  $('.openlayers-form-lon').val(lon);
}
