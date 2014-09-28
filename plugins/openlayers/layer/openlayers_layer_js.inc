<?php

function openlayers_openlayers_layer_js_openlayers_control() {
  return array(
    'handler' => array(
      'class' => 'openlayers_layer_js',
      'file' => 'openlayers_layer_js.inc',
    )
  );
}

class openlayers_layer_js extends openlayers_layer {

  function options_form() {
    $attached = array();
    $form = array();

    if (module_exists('ace_editor')) {
      $attached = array(
        'library' => array(
          array('ace_editor', 'ace-editor')
        ),
        'js' => array(
          drupal_get_path('module', 'openlayers') . '/js/editor.js'
        )
      );
    } else {
      drupal_set_message(t('To get syntax highlighting, you should install the module <a href="@url1">ace_editor</a> and its <a href="@url2">library</a>.', array('@url1' => 'http://drupal.org/project/ace_editor', '@url2' => 'http://ace.c9.io/')), 'warning');
    }

    $form['javascript'] = array(
      '#type' => 'textarea',
      '#title' => t('Javascript'),
      '#description' => t('Javascript to evaluate. The available variable is: <em>data</em>. You must create the openlayers variable <em>layer</em>.'),
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
