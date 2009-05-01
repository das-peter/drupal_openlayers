$(document).ready(function(){
  // @@TODO: Namespace this using the form ID?
  // Hide the textfield form
  $(".openlayers-form-projection").parent().css("display","none");
  
  // Attach events to the projection radio buttons
  $(".openlayers-form-easy-projection input").each(function(){
    $(this).change(function(){
      
      var projection = $(this).val();
      if (projection == 'other'){
        $(".openlayers-form-projection").parent().css("display","block");
      }
      else{
        $(".openlayers-form-projection").parent().css("display","none");
        $(".openlayers-form-projection").val(projection);
        
        // If we are using a web spherical-mercador projection, set the MaxResolution and MaxExtent (If they are not already set)
        if (projection == '900913' || projection == '3785') openlayersWebSpericalMercadorAutoSettings();
        
        // Update our selectable layers
        openlayersUpdateSelectableLayers(projection);
      }
    });
  });
  
  // Center and zoom for zoom / center helper
  $('#edit-center-lat').change(openlayersUpdateHelpmapCenter);
  $('#edit-center-lon').change(openlayersUpdateHelpmapCenter);
  $('#edit-center-zoom').change(openlayersUpdateHelpmapCenter);
  openlayersUpdateHelpmapCenter();
});

function openlayersWebSpericalMercadorAutoSettings(){
  // @@TODO: Automatically set the MaxExtent and MaxResolution  


}


function openlayersUpdateSelectableLayers(projection){
  // @@TODO: Update our selectable layers list based on the map projection


}


function openlayersUpdateHelpmapCenter() {
  var projection = $('#edit-projection').val();
  var zoom = $('#edit-center-zoom').val();
  var lat = $('#edit-center-lat').val();
  var lon = $('#edit-center-lon').val();
  
  var center = new OpenLayers.LonLat(lon, lat);
  center.transform(new OpenLayers.Projection('EPSG:' + projection), new OpenLayers.Projection('EPSG:4326'));
  
  Drupal.openlayers.activeObjects['openlayers-center-helpmap'].map.setCenter(center, zoom);
}

function openlayersUpdateCenterFormValues() {
  var helpmap = Drupal.openlayers.activeObjects['openlayers-center-helpmap'].map;
  var projection = $('#edit-projection').val();
  var zoom = helpmap.getZoom();
  
  var center = helpmap.getCenter();
  center.transform(new OpenLayers.Projection('EPSG:4326'),new OpenLayers.Projection('EPSG:' + projection));
  
  var lat = center.lat;
  var lon = center.lon;
  
  $('#edit-center-zoom').val(zoom);
  $('#edit-center-lat').val(lat);
  $('#edit-center-lon').val(lon);
}
