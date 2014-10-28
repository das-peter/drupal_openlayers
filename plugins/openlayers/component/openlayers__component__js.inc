<?php

function openlayers_openlayers__component__js_openlayers_component() {
  return array(
    'handler' => array(
      'class' => 'openlayers__component__js',
      'file' => 'openlayers__component__js.inc',
    )
  );
}

class openlayers__component__js extends openlayers_component {

  function options_form(&$form, &$form_state) {
    $attached = array();
    //$form = array();

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

    $form['options']['javascript'] = array(
      '#type' => 'textarea',
      '#title' => t('Javascript'),
      '#description' => t('Javascript to evaluate. The available variable is: <em>data</em>.'),
      '#rows' => 15,
      '#default_value' => $this->getOption('javascript'),
      '#attributes' => array(
        'data-editor' => 'javascript'
      ),
      '#attached' => $attached
    );
  }

}
