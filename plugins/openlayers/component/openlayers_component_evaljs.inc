<?php

function openlayers_openlayers_component_evaljs_openlayers_component() {
  return array(
    'handler' => array(
      'class' => 'openlayers_component_evaljs',
      'file' => 'openlayers_component_evaljs.inc',
    )
  );
}

class openlayers_component_evaljs extends openlayers_component {

  function options_form() {
    $attached = array();
    $form = array();

    if (module_exists('ace_editor')) {
      $attached = array(
        'library' => array(
          array('ace_editor', 'ace-editor')
        ),
        'js' => array(
          drupal_get_path('module', 'openlayers') . '/plugins/openlayers/component/openlayers_component_evaljs_editor.js'
        )
      );
    } else {
        drupal_set_message(t('To get syntax highlighting, you should install the module <a href="@url1">ace_editor</a> and its <a href="@url2">library</a>.', array('@url1' => 'http://drupal.org/project/ace_editor', '@url2' => 'http://ace.c9.io/')), 'warning');
    }

    $form['javascript'] = array(
      '#type' => 'textarea',
      '#title' => t('Javascript'),
      '#description' => t('Javascript to eval. The available variables are: options and map'),
      '#rows' => 15,
      '#default_value' => $this->getOption('javascript'),
      '#attributes' => array(
        'data-editor' => 'javascript'
      ),
      '#attached' => $attached
    );

    return $form;
  }

}
