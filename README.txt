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
      'projection' => "900913",
      'displayProjection' => "4326",
      'maxResolution' => 156543.0339,
      'maxExtent' => array(
        'left' => -20037508.34,
        'bottom' => -20037508.34,
        'right' => 20037508.34,
        'top' => 20037508.34,
      ),
    ),
    'controls' => array(
      'LayerSwitcher' => TRUE,
    ),
    'default_layer' => 'default_wms',
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
        	'loadstart'=> array('yourModulesJSFunction'),
        ),
      ),
    ),
    'draw_features' => array(
      'point' => array(
        'type' => 'Point',
        'vector' => 'default_vector',
        'featureadded_handler' => array('yourModulesJSFunction'),
        'featuremodified_handler' => array('yourModulesJSFunction'),
        'featureremoved_handler' => array('yourModulesJSFunction'),
      ),
      'path' => array(
        'type' => 'Path',
        'vector' => 'default_vector',
        'featureadded_handler' => array('yourModulesJSFunction'),
        'featuremodified_handler' => array('yourModulesJSFunction'),
        'featureremoved_handler' => array('yourModulesJSFunction'),
      ),
      'polygon' => array(
        'type' => 'Polygon',
        'vector' => 'default_vector',
        'featureadded_handler' => array('yourModulesJSFunction'),
        'featuremodified_handler' => array('yourModulesJSFunction'),
        'featureremoved_handler' => array('yourModulesJSFunction'),
      ),
    ),
    'events' => array(
      'addlayer' => array(''),
    ),
  );
  
 API: Events
============
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
  
  Available Events:

	Map Events:
	------------
	preaddlayer
	addlayer
	removelayer
	changelayer
	movestart
	move
	moveend
	zoomend
	popupopen
	popupclose
	addmarker
	removemarker
	clearmarkers
	mouseover
	mouseout
	mousemove
	dragstart
	drag
	dragend
	changebaselayer
	
	One-Time Map Events:
	These events are triggered during the map building process, letting you
	execute javascript at various points while the map is being built.
	--------------------
	beforeEverything  -- Executed as soon as possible for each map. The OpenLayers map object is not yet built.
	beforeLayers      -- After the map object is built, but before layers are created and added.
	beforeCenter      -- Before the map is zoomed and centered.
	beforeControls    -- Before controls are added to the map
	beforeEvents      -- Before events are added to the map
	beforeBehaviors   -- Before behaviors are triggered
	mapReady          -- Last call
	
	
	Layer Events:
	-------------
	beforefeatureadded
	beforefeaturesadded
	featureadded
	featuresadded
	beforefeatureremoved
	featureremoved
	featuresremoved
	beforefeatureselected
	featureselected
	featureunselected
	beforefeaturemodified
	featuremodified
	afterfeaturemodified
	refresh
	loadstart
	loadend
	loadcancel
	visibilitychanged
	moveend



API: Adding Features
===============

Although there are many paths to getting features onto maps via events, the API provides a standard way of adding features via the map array.
To do so built a feature of the Vector type and add geometry, style, and attribute information like so:

  'feature_example' => array(
    'id' => 'feature_example',
    'type' => 'Vector',
    'name' => t('Default Vector'),
    'options' => array(),
    'events' => array(),
    'features' => array(
      'feature_1' => array(
        'wkt' => 'POLYGON((1 1,5 1,5 5,1 5,1 1),(2 2, 3 2, 3 3, 2 3,2 2))',
        'attributes' => array(
          'name' => 'A Polygon with a hole in it',
          'date' => 'December 24, 2004',
          'author' => 'Santa Claus',
        ),
        'style' => array(
          'fillColor' => '#aa4400',
          'fillOpacity' => '0.7',
        ),
      ),
      'feature_2' => array(
        'lat' => '40.123',
        'lon' => '-20.123',
        'attributes' => array(
          'name' => 'A point',
          'date' => 'December 24, 2004',
          'author' => 'Rudolf',
        ),
        'style' => array(
          'externalGraphic' => 'http://openlayers.org/dev/img/marker.png',
          'graphicWidth' => 21,
          'graphicHeight' => 25,
          'graphicXOffset' => 10,
          'graphicYOffset' => 10,
        ),
      ),
    ),
  ),


Default style properties

    * fillColor: "#ee9900",
    * fillOpacity: 0.4,
    * strokeColor: "#ee9900",
    * strokeOpacity: 1,
    * strokeWidth: 1,
    * strokeLinecap: "round", [butt | round | square]
    * strokeDashstyle: "solid", [dot | dash | dashdot | longdash | longdashdot | solid]
    * pointRadius: 6,
    * pointerEvents: "visiblePainted”"
    * cursor: ""

Other style properties that have no default values

    * externalGraphic,
    * graphicWidth,
    * graphicHeight,
    * graphicOpacity,
    * graphicXOffset,
    * graphicYOffset,
    * graphicName,
    * display










 Authors/Credits
=================
...


 To Do
=======
...