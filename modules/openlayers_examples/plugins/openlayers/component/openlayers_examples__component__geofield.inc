<?php

function openlayers_examples_openlayers_examples__component__geofield_openlayers_component() {
  return array(
    'handler' => array(
      'class' => 'openlayers_examples__component__geofield',
      'file' => 'openlayers_examples__component__geofield.inc',
    )
  );
}

class openlayers_examples__component__geofield extends openlayers_component {

  function alterBuild(&$build) {
    $build['component'] = array(
      '#type' => 'fieldset',
      '#title' => 'Example Geofield component'
    );

    $build['component']['actionFeature'] = array(
      '#type' => 'select',
      '#options' => array('draw' => 'Draw', 'modify' => 'Modify'),
      '#attributes' => array(
        'id' => 'actionFeature'
      )
    );

    $build['component']['dataType'] = array(
      '#type' => 'select',
      '#options' => array('GeoJSON' => 'GeoJSON', 'KML' => 'KML', 'GPX' => 'GPX', 'WKT' => 'WKT'),
      '#attributes' => array(
        'id' => 'dataType'
      )
    );

    $build['component']['typeOfFeature'] = array(
      '#type' => 'select',
      '#options' => array('Point' => 'Point', 'LineString' => 'LineString', 'Polygon' => 'Polygon'),
      '#attributes' => array(
        'id' => 'typeOfFeature'
      )
    );

    $build['component']['data'] = array(
      '#type' => 'textarea',
      '#attributes' => array(
        'id' => 'data'
      ),
      '#value' => ''
    );

    $build['component']['clearmap'] = array(
      '#markup' => "<a href='#' id='clearmap'>Clear the map</a>",
    );
  }

}
