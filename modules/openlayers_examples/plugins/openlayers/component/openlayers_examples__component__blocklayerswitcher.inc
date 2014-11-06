<?php

function openlayers_examples_openlayers_examples__component__blocklayerswitcher_openlayers_component() {
  return array(
    'handler' => array(
      'class' => 'openlayers_examples__component__blocklayerswitcher',
      'file' => 'openlayers_examples__component__blocklayerswitcher.inc',
    )
  );
}

class openlayers_examples__component__blocklayerswitcher extends openlayers_component {

  function alterBuild(&$build, $map) {
    $build['component'] = array(
      '#type' => 'fieldset',
      '#title' => 'Layer Switcher',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE
    );

    $build['component']['block'] = drupal_get_form('olebs_blockswitcher_form', $map);

    $build['map']['#attributes']['style'] = $build['#attributes']['style'];
    unset($build['#attributes']['style']);
  }

}
