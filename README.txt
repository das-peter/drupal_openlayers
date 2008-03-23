$Id$

 OpenLayers for Drupal
=======================
This module tries to bring the great OpenLayers to Drupal.
For this it defines two node types:

 Node type layer
-----------------
This lets you define single layers, like a Google Maps layer or a WMS layer.
Certain layer types (like WMS) need sublayers to be specified.
The basic display of a layer node is a OpenLayers viewer showing the layer.
AS OF NOW WMS AND GOOGLE MAP LAYERS ARE SUPPORTED.

 Node type map
---------------
Maps are collection of layers plus a set of controls to display in an OpenLayers
viewer.
(NOT YET IMPLEMENTED)

 Installation
==============
* Copy the files and directories into a single module directory, e.g.
  sites/all/modules/openlayers.
* Grab a copy of OpenLayers at http://openlayers.org and copy OpenLayers.js into
  the same directory.
* Then just enable the module at admin/build/modules.

Be aware though that at the moment you will need the keys_api module to keep a
valid Google Maps API key.
(This will be made optional in the future, because we don't want you to enter
the lion's den to request a Google Maps API key)

The WMS layer type needs PHP cURL and XSL to be enabled.

 TRAPS
=======
The way we build the node edit form breaks edited properties for the layer when
the node fails validation - the default property value will be set again. So if
you change a layer property from it's default value and validation fails for
some reason, then make sure to set you non-default properties again.