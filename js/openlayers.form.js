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
});

function openlayersWebSpericalMercadorAutoSettings(){
  // @@TODO: Automatically set the MaxExtent and MaxResolution  


}


function openlayersUpdateSelectableLayers(projection){
  // @@TODO: Update our selectable layers list based on the map projection


}