// $Id$

/**
 * @file
 * File to hold custom context styling
 */

/**
 * Global variable for context styling.
 */
Drupal.openlayers.styleContext.openlayersExampleContext = {
  'getFillOpacity': function(feature) {
    // Random fill opacity
    return Math.random();
  }
};