<?php
// $Id$

/**
 * @file
 * This file holds the functions handling styles in the 
 * Openlayers UI.
 *
 * @ingroup openlayers
 */

/**
 * Styles add/edit form.
 */
function openlayers_ui_styles_form(&$form_state, $style = NULL, $edit = FALSE) {
  $form = array();

  $form['info'] = array(
    '#type' => 'fieldset',
    '#tree' => FALSE,
  );
  $form['info']['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => !empty($style->name) ? $style->name : '',
  );
  $form['info']['title'] = array(
    '#title' => t('Title'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => !empty($style->title) ? $style->title : '',
  );
  $form['info']['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textfield',
    '#default_value' => !empty($style->description) ? $style->description : '',
  );

  $form['data'] = array('#type' => 'fieldset', '#tree' => TRUE);
  
  $form['data']['externalGraphic'] = array(
    '#title' => 'externalGraphic',
    '#type' => 'textfield',
    '#description' => t('The URL of an icon for points in a layer.'),
    '#default_value' => isset($style->data['externalGraphic']) ? 
      $style->data['externalGraphic'] : '',
  );
  $form['data']['pointRadius'] = array(
    '#title' => 'pointRadius',
    '#type' => 'textfield',
    '#description' => t('The radius of a vector point or the size of 
      an icon. Note that, when using icons, this value should be half the 
      width of the icon image.'),
    '#default_value' => isset($style->data['pointRadius']) ? 
      $style->data['pointRadius'] : 5,
  );
  $form['data']['fillColor'] = array(
    '#title' => 'fillColor',
    '#type' => 'textfield',
    '#default_value' => isset($style->data['fillColor']) ? 
      $style->data['fillColor'] : "#FFFFFF",
  );
  $form['data']['strokeColor'] = array(
    '#title' => 'strokeColor',
    '#type' => 'textfield',
    '#description' => t('The color of the border around a vector 
      point'),
    '#default_value' => isset($style->data['strokeColor']) ? 
      $style->data['strokeColor'] : "#FFFFFF",
  );
  $form['data']['strokeWidth'] = array(
    '#title' => 'strokeWidth',
    '#type' => 'textfield',
    '#description' => t('The width of the border around a vector 
      point'),
    '#default_value' => isset($style->data['strokeWidth']) ? 
      $style->data['strokeWidth'] : 5,
  );
  $form['data']['fillOpacity'] = array(
    '#title' => 'fillOpacity',
    '#type' => 'textfield',
    '#default_value' => isset($style->data['fillOpacity']) ? 
      $style->data['fillOpacity'] : 0.5,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * Submit handler for layers.
 */
function openlayers_ui_styles_form_submit(&$form, &$form_state) {
  $style = new stdClass();
  $style->name = $form_state['values']['name'];
  $style->title = $form_state['values']['title'];
  $style->description = $form_state['values']['description'];
  $style->data = $form_state['values']['data'];

  $success = openlayers_style_save($style);

  // Redirect to edit page
  if ($success) {
    drupal_set_message(t('Style saved.'));
    $form_state['redirect'] = 'admin/settings/openlayers/styles/' . $style->name . '/edit';
  }
  else {
    form_set_error('openlayers', t('Error trying to save style.'));
  }
}
