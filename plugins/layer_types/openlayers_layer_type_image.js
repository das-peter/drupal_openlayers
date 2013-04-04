/**
 * OpenLayers Image Layer Handler
 */
Drupal.openlayers.layer.image = function(title, map, options) {
  if (options.maxExtent === null) {
    // Stretch image to cover whole map if not specified.
    options.maxExtent = map.maxExtent;
  }

  return new OpenLayers.Layer.Image(
    title,
    options.file,
    OpenLayers.Bounds.fromArray(options.maxExtent),
    new OpenLayers.Size(options.size.w/options.factors.x, options.size.h/options.factors.y),
    {
      numZoomLevels: options.numZoomLevels,
      opacity: options.opacity,
      projection: options.projection,
      transitionEffect: options.transitionEffect,
      isBaseLayer: options.isBaseLayer,
      attribution: options.attribution
    }
  );
};
