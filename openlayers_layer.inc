<?php
// $Id$

/**
 * Implementation of hook_access
 */
function openlayers_layer_access($op, $node) {
  global $user;
  switch ($op) {
    case 'create':
      return user_access('create layer');
      break;
    case 'update':
    case 'delete':
      if (user_access('edit own layer') && ($user->uid == $node->uid)) {
        return TRUE;
      }
      return user_access('edit layer');
      break;
  }
}

/**
 * Implementation of hook_load
 */
function openlayers_layer_load($node) {
  $fetch = db_fetch_object(db_query('SELECT type, uri, sublayers, properties, add_js FROM {ol_layers} WHERE vid = %d', $node->vid));
  $layer['title'] = $node->title;
  $layer['type'] = $fetch->type;
  $layer['uri'] = $fetch->uri;
  $layer['sublayers'] = unserialize($fetch->sublayers);
  $layer['properties'] = unserialize($fetch->properties);
  $layer['add_js'] = $fetch->add_js;

  $obj = new StdClass();
  $obj->layer = $layer;
  return $obj;
}

/**
 * Implementation of hook_prepare
 */
function openlayers_layer_prepare(&$node) {
  //TODO; Needed?
}

/**
 * Implementation of hook_form
 */
function openlayers_layer_form(&$node, &$param) {
  global $ol_layertypes;
  $nodetype = node_get_types('type', $node);
  $form = array();
  // this will be set to textfield type in form_alter once the layer type is set.
  $form['title']= array(
    '#type' => 'value',
    '#title' => check_plain($nodetype->title_label),
    '#required' => TRUE,
    '#default_value' => $node->title,
    '#size' => 60,
    '#maxlength' => 255,
    '#weight' => -5
  );

  $layers['none'] = t('Select type...');
  foreach ($ol_layertypes as $layername => $layertype) {
    $layers[$layername] = $layertype['shortname'];
  }

  $form['layertype'] = array(
    '#type' => 'select',
    '#title' => t('layer resource type'),
    '#options' => $layers,
    '#default_value' => $node->layer['type'],
    '#weight' => -4,
    '#attributes' => array('onchange' => '$("#node-form").submit()'),
  );
  $form['ahah_target'] = array(
    '#type' => 'item',
    '#value' => '<p>' . t('Select a layer type first...') . '</p>',
    '#prefix' => '<div id="ahah_target">',
    '#suffix' => '</div>',
  );

  // The rest of the form (URI, Properties, etc.) will be build
  // in openlayers_layer_node_form_alter once the layer type is set

  $form['body_filter'] = array(
    '#weight' => 20,
  );
  $form['body_filter']['body'] = array(
    '#type' => 'value',
    '#title' => check_plain($nodetype->body_label),
    '#default_value' => $node->body,
    '#required' => FALSE
  );
  $form['body_filter']['filter'] = filter_form($node->format);

  return $form;
}

/**
 * This gets called for hook_form_alter('ol_layer_node_form', &$form)
 */
function openlayers_layer_node_form_alter(&$form) {
  $layertypes = openlayers_get_layertypes();
  //Get layer type when editing existing nodes
  if (!empty($form['#node']->layer['type'])) {
    $type = $form['#node']->layer['type'];
  }
  //Get layer type when creating new nodes (or changing layer type for exising nodes???)
  if (!empty($form['#post']['layertype'])) {
    $type = $form['#post']['layertype'];
  }

  if (!in_array($type, array_keys($layertypes))) {
    return;
  }

  $layer = $layertypes[$type];

  $form['title']['#type'] = 'textfield';
  $form['body']['#type'] = 'textarea';

  if ($layer['uri']) {
    $form['uri'] = array(
      '#type' => 'textfield',
      '#title' => t('URI'),
      '#description' => t('Enter the URI of the layer'),
      '#default_value' => $form['#node']->layer['uri'],
      '#required' => TRUE,
      '#weight' => -3,
    );
  }

  //Sublayers
  if ($layer['sublayers']) {
    //TODO: jQuery interface for this
    $value = '';
    if ($form['#node']->layer['sublayers'] != '') {
      $value = implode(',', $form['#node']->layer['sublayers']);
    }
    $form['sublayers'] = array(
      '#type' => 'textfield',
      '#title' => t('Sublayers'),
      '#description' => $layer['sublayers_help'],
      '#default_value' => $value,
      '#required' => TRUE,
      '#weight' => -2,
    );
  }

  if (count($layer['properties'])) {
    $form['layer_properties'] = array(
      '#type' => 'fieldset',
      '#title' => t('Properties'),
      '#collapsible' => TRUE,
      '#description' => t("The way we build the node edit form breaks edited properties for the layer when the node fails validation - the default property value will be set again. So if you change a layer property from it's default value and validation fails for some reason, then make sure to set you non-default properties again."),
      '#weight' => -1,
    );

    foreach ($layer['properties'] as $pname => $property) {
      $form['layer_properties'][$pname] = array(
        '#type' => $property['type'],
        '#title' => $property['title'],
        '#description' => $property['description'],
        '#default_value' => $form['#node']->$pname, //Kinda senseless - we enforce a value below, see comment there
        '#weight' => $property['weight'],
        '#required' => $property['required'],
      );

      //Let's try to find which value we need to enforce instead of the posted one
      //This is kinda hard and works except for when a new node fails validation,
      //for which the default property value will be enforced.

      //First, rule out we are heading into hook_submit
      if ($form['#post']['op'] != 'Submit') {
        //Use property default - breaks posted value for new nodes failing validation
        $form['layer_properties'][$pname]['#value'] = $property['default'];
        //Editing an existing node: If there's no posted value, use the
        //stored value from the node, otherwise use the posted value
        if (isset($form['#node']->nid)) {
          if (count($form['#post'])) {
            $form['layer_properties'][$pname]['#value'] = $form['#post'][$pname];
          }
          else {
            $form['layer_properties'][$pname]['#value'] = $form['#node']->layer['properties'][$pname];
          }
        }
      }
    }
  }

  $form['add_js'] = array(
    '#type' => 'textarea',
    '#title' => t('Additional JavaScript'),
    '#rows' => 15,
    '#default_value' => $node->layer['add_js'],
    '#weight' => 0,
  );
}

/**
 * Implementation of hook_validate
 */
function openlayers_layer_validate($node, &$form) {
  $layertypes = openlayers_get_layertypes();
  $layertype = $layertypes[$form['#post']['layertype']];
  //TODO
}

/**
 * Implementation of hook_submit
 */
function openlayers_layer_submit(&$node) {
  $layertypes = openlayers_get_layertypes();
  $layertype = $layertypes[$node->layertype];

  $layer['type'] = $node->layertype;
  $layer['uri'] = $node->uri;
  $layer['sublayers'] = explode(',', $node->sublayers);

  foreach ($layertype['properties'] as $pname => $property) {
    $layer['properties'][$pname] = $node->$pname;
  }

  $layer['add_js'] = $node->add_js;
  $node->layer = $layer;
}

/**
 * Implementation of hook_insert
 */
function openlayers_layer_insert($node) {
  db_query("INSERT INTO {ol_layers} (nid, vid, type, uri, sublayers, properties, add_js) VALUES (%d, %d, '%s', '%s', '%s', '%s', '%s')", $node->nid,
    $node->vid,
    $node->layer['type'],
    $node->layer['uri'],
    serialize($node->layer['sublayers']),
    serialize($node->layer['properties']),
    $node->layer['add_js']);
}

/**
 * Implementation of hook_update
 */
function openlayers_layer_update($node) {
  db_query("UPDATE {ol_layers} SET type = '%s', uri = '%s', sublayers = '%s', properties = '%s', add_js = '%s' WHERE vid = %d", $node->layer['type'],
    $node->layer['uri'],
    serialize($node->layer['sublayers']),
    serialize($node->layer['properties']),
    $node->layer['add_js'],
    $node->vid);
}

/**
 * Implementation of hook_delete
 */
function openlayers_layer_delete(&$node) {
  db_query('DELETE FROM {ol_layers} WHERE nid = %d', $node->nid);
}

/**
 * Implementation of hook_view
 * For layer nodes display description
 */
function openlayers_layer_view($node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);
  if ($teaser) {
  }
  else {
    $node->content['layer'] = array(
      '#value' => theme('openlayers_map', "node_{$node->nid}", array($node->layer)),
      '#weight' => 1,
    );
  }
  return $node;
}

function openlayers_get_layertypes() {
  static $layertypes;
  if (!isset($layertypes)) {
    $layertypes = array();
    $path = drupal_get_path('module', 'openlayers') .'/layers';
    $files = file_scan_directory($path, '.*\.inc$');
    foreach ($files as $filename => $file) {
      include_once($filename);
      $layername = strtolower(basename($filename, '.inc'));
      $layerfunc = "layertype_$layername";
      $layertypes[$layername] = $layerfunc();
    }
  }

  return $layertypes;
}