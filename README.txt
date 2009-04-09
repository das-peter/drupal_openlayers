$Id$

 OpenLayers for Drupal
=======================
This module tries to bring the great OpenLayers to Drupal.


 Installation
==============
1) Normal Drupal module installation
2) ...


 API
=====

Maps are built using an array that looks like this:

  $map = array(
    'id' => _openlayers_create_map_id(),
    'width' => 'auto',
    'height' => '300px',
    'center' => array(
      'lat' => 40,
      'lon' => 5,
      'zoom' => 5,
    ),
    'options' => array(
      'numZoomLevels' => 10,
    ),
    'controls' => array(
      'LayerSwitcher' => TRUE,
    ),
    'layers' => array(
      'default_wms' => array(
        'id' => 'default_wms',
        'type'=> 'WMS',
        'name' => t('Default Open Layers WMS'),
        'url' => 'http://labs.metacarta.com/wms/vmap0',
        'params' => array(
          'layers' => 'basic',
        ),
        'options' => array(),
        'events' => array(
        	'loadstart'=> array(),
        	'loadend' => array(),
        	'loadcancel' => array(),
          'visibilitychanged' => array(),
          'moveend' => array(),
        ),
      ),
      'default_vector' => array(
        'id' => 'default_vector',
        'type' => 'Vector',
        'name' => t('Default Vector'),
        'options' => array(),
        'events' => array(
        	'loadstart'=> array(),
        	'loadend' => array(),
        	'loadcancel' => array(),
          'visibilitychanged' => array(),
          'moveend' => array(),
        ),
      ),
    ),
    'draw_features' => array(
      'point' => array(
        'type' => 'Point',
        'vector' => 'default_vector',
        'featureadded_handler' => 'openlayersDefaultFeatureHandler',
      ),
      'path' => array(
        'type' => 'Path',
        'vector' => 'default_vector',
        'featureadded_handler' => 'openlayersDefaultFeatureHandler',
      ),
      'polygon' => array(
        'type' => 'Polygon',
        'vector' => 'default_vector',
        'featureadded_handler' => 'openlayersDefaultFeatureHandler',
      ),
    ),
    'events' => array(
      'addlayer' => array(''),
    ),
  );
  
 
 Events are currently supported for both the map object, and layer objects.
 To define an event you would first modify the map or layer's PHP array like so:
  'default_vector' => array(
     'events' => array(
      'moveend' => array('customModuleLoadSomeData','customModuleDoSomethingElse'),
      'zoomend' => array('customModuleLoadSomeData'),
    ),
  )
  
  You would then be responsible for making sure that the customModuleLoadSomeData, and customModuleDoSomethingElse javascript functions are available.
  They would follow the following format:
  
  function customModuleLoadSomeData(event){
    var layer = event.layer;
    
    //Our user has panned or zoomed the map. Let's load some more data into this layer
    ....
  }


 Authors/Credits
=================
...


 To Do
=======
...