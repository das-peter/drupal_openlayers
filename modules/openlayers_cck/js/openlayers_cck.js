// $Id$

/**
 * @file
 * Interface enhancements for the OpenLayers CCK module.
 */

/**
 * Implements Drupal Behaviors
 */
Drupal.behaviors.openlayers_cck_wkt_hide = function(context) {
  // Hide WKT field and allow to toggle visibility.
  if (typeof Drupal.settings.openlayers_cck.wkt_hide != 'undefined') {
    var textShow = Drupal.settings.openlayers_cck.wkt_hide.text_show;
    var textHide = Drupal.settings.openlayers_cck.wkt_hide.text_hide;

    for (field in Drupal.settings.openlayers_cck.wkt_hide.fields) {
      var fieldID = '#edit-' + field + '-openlayers-wkt-wrapper';
      
      $(fieldID + ':not(.openlayers-cck-processed)').each(function() {
        $thisField = $(this);
        
        $thisField.addClass('openlayers-cck-processed');
        // Add a link to be able to hide and show, and hide by default.
        $thisField.before('<a href="" id="' + field + '-toggle" class="openlayers-cck-hide-link">' + textShow + '</a>')
          .hide();
        $('#' + field + '-toggle').toggle(
          function () {
            $(fieldID).slideDown();
            $(this).text(textHide);
          },
          function () {
            $(fieldID).slideUp();
            $(this).text(textShow);
          }
        );
      });
    }
  }
};