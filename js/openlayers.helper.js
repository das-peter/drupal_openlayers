// $Id$

/**
 * @file
 * This file holds help functions in the OL object.  The main
 * reason for this is just to keep things organized
 *
 * @ingroup openlayers
 */

/**
 * Global Object for Namespace
 */
var OL = OL || {'Layers': {}, 'EventHandlers': {} ,'Behaviors': {}, 'maps': []};

/**
 * Process Events
 *
 * Process the layers part of the map definition into OpenLayers layer objects
 *
 * @param events
 *   The events section of the map definition array.
 * @param mapid
 *   The id of the map to which we will add these events.
 */
OL.processEvents = function(events, mapid) {
  // Go through events
  for (var evtype in events){
    // Exclude One-Time map events.
    if (evtype != 'beforeEverything' && evtype != 'beforeLayers' && evtype != 'beforeCenter' && evtype != 'beforeControls' && evtype != 'beforeEvents' && evtype != 'beforeBehaviors' && evtype != 'mapReady') {
      for (var ev in events[evtype]) {
        OL.maps[mapid].map.events.register(evtype, OL.maps[mapid].map, OL.EventHandlers[events[evtype][ev]]);
      }
    }
  }
}

/**
 * Trigger Custom Event
 *
 * @param map
 *   Map object
 * @param eventName
 *   String of the name of the event
 * @param event
 *   Event object
 */
OL.triggerCustom = function(map, eventName, event) {
  if (OL.isSet(map.events) && OL.isSet(map.events[eventName])) {
    for (var ev in map.events[eventName]) {
      OL.EventHandlers[map.events[eventName][ev]](event);
    }
  }
}

/**
 * Parse out key / value pairs out of a string that looks like "key:value;key2:value2"
 *
 * @param rel
 *   The string to parse. Usually the rel attribute of a html tag.
 * @return
 *   Array of key:value pairs
 */
OL.parseRel = function(rel) {
  var outputArray = [];

  // Some preprosessing
  // replace dangling whitespaces. Use regex?
  rel = rel.replace('; ',';');
  //Cut out final ; if it exists
  if (rel.charAt(rel.length-1) == ";") rel = rel.substr(0,rel.length-1);

  //Get all the key:value strings
  var keyValueStrings = rel.split(';');

  // Process the key:value strings into key:value pairs
  for (var i in keyValueStrings){
    var singleKeyValue = keyValueStrings[i].split(':');
    outputArray[singleKeyValue[0]] = singleKeyValue[1];
  }

  return outputArray;
}

/**
 * Given a string of the form 'OL.This.that', get the object that the
 * string refers to.
 *
 * @param string
 *   The string to parse.
 * @return
 *   Object
 */
OL.getObject = function(string) {
  var parts = string.split('.');
  i = 0;
  var object = window;
  while (i < parts.length){
    object = object[parts[i]];
    i++;
  }
  return object;
}

/**
 * Check if Variable is define
 *
 * @params variable
 *   Any variable
 * @return
 *   Boolean if the variable is definied or not
 */
OL.isSet = function(variable) {
  if (typeof(variable) == 'undefined') {
    return false;
  }
  else {
    return true;
  }
}
