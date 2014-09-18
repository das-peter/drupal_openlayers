(function ($) {
  Drupal.behaviors.olebs =  {
    attach: function(context, settings) {

      var data = $(context).data('openlayers');
      if (jQuery.isEmptyObject(data)) {
        return;
      }

      $(".form-item-overlays input[type='radio']").change(function(e) {
        var map = $(this).closest('form').find("input[name='map']").val();
        console.log(data.objects);
        if (map in data.objects.maps) {
          var map = data.objects.maps[map];
          var layers = map.getLayers();

          var layer = $(this).val();
          var layers = data.openlayers.layers.slice();
          for(var i=0, len=layers.length; i<len; i++) {
            if (layers[i].drupalID == layer) {
              data.openlayers.setBaseLayer(layers[i]);
            }
          }
        }
      });

    }
  };
})(jQuery);

