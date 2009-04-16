// $Id$

/**
 * @file
 *   JS functions to handle different kinds of layers
 */

/**
 * Process XYZ Layers
 */
function openlayersLayerHandlerXYZ(layerOptions, mapid) {
  var returnXYZ = new OpenLayers.Layer.XYZ(layerOptions.name, layerOptions.url, layerOptions.options);
  return returnXYZ;
}