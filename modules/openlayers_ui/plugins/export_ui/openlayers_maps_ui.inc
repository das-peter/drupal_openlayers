<?php
/**
 * CTools Export UI required function for plugin definition
 * See function ctools_plugin_load_includes() in the module ctools.
 */
function openlayers_ui_openlayers_maps_ui_ctools_export_ui() {
  return array(
    'schema' => 'openlayers_maps',
    'access' => 'administer openlayers',
    'menu' => array(
      'menu prefix' => 'admin/structure/openlayers',
      'menu item' => 'maps',
      'menu title' => 'Maps',
      'menu description' => 'Administer OpenLayers maps presets.',
    ),

    'handler' => array(
      'class' => 'openlayers_maps_ui',
      'parent' => 'ctools_export_ui'
    ),

    'use wizard' => TRUE,
    'form info' => array(
      'order' => array(
        'start' => t('Administrative settings'),
        'settings' => t('Map settings'),
        'layers' => t('Layers'),
        'controls' => t('Controls'),
        'interactions' => t('Interactions'),
        'components' => t('Components'),
        'styles' => t('Styles'),
        'preview' => t('Preview')
      ),
      'forms' => array(
        'start' => array(
          'form id' => 'openlayers_map_form_start'
        ),
        'settings' => array(
          'form id' => 'openlayers_map_form_settings'
        ),
        'layers' => array(
          'form id' => 'openlayers_map_form_layers'
        ),
        'controls' => array(
          'form id' => 'openlayers_map_form_controls'
        ),
        'interactions' => array(
          'form id' => 'openlayers_map_form_interactions'
        ),
        'components' => array(
          'form id' => 'openlayers_map_form_components'
        ),
        'styles' => array(
          'form id' => 'openlayers_map_form_styles'
        ),
        'preview' => array(
          'form id' => 'openlayers_map_form_preview'
        )
      )
    ),

    'export' => array(
      'admin_title' => 'name',
      'admin_description' => 'description',
    ),

    'title singular' => t('map'),
    'title plural' => t('maps'),
    'title singular proper' => t('OpenLayers map preset'),
    'title plural proper' => t('OpenLayers maps presets'),

    'strings' => array(
      'confirmation' => array(
        'add' => array(
          'success' => t('Map saved.'),
        ),
        'delete' => array(
          'success' => t('Map was deleted.'),
        )
      )
    ),
  );
}

function openlayers_map_form_start($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form($form, $form_state);
  return $form;
}

function openlayers_map_form_start_validate($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_validate($form, $form_state);
}

function openlayers_map_form_start_submit($form, &$form_state) {
  $class = new ctools_export_ui();
  $class->init($form_state['plugin']);
  $class->edit_form_submit($form, $form_state);
}

function openlayers_map_form_settings($form, &$form_state) {
  $form_state['item']->class = 'openlayers_map_map';
  $map = openlayers_object_load('map', $form_state['item']);
  $form['options'] = $map->options_form();
  $form['options']['#tree'] = TRUE;

  return $form;
}

function openlayers_map_form_settings_validate($form, &$form_state) {
  $item = $form_state['item'];
  $item->class = 'openlayers_map_map';
  $item->options = array_replace_recursive((array) $form_state['item']->options, $form_state['values']['options']);

  $map = openlayers_object_load('map', $item);
  $map->options_form_validate();
}

function openlayers_map_form_settings_submit($form, &$form_state) {
  // todo: fix
  $form_state['item']->class = 'openlayers_map_map';
  $form_state['item']->options = array_replace_recursive((array) $form_state['item']->options, $form_state['values']['options']);
}

function openlayers_map_form_layers($form, &$form_state) {
  $all_layers = ctools_export_crud_load_all('openlayers_layers');
  $map = openlayers_object_load('map', $form_state['item']);

  $layers = array();
  foreach($map->getLayers() as $index => $layer) {
    if (isset($all_layers[$layer->machine_name])) {
      $layers[$layer->machine_name] = $all_layers[$layer->machine_name];
      $layers[$layer->machine_name]->enable = 1;
      unset($all_layers[$layer->machine_name]);
    }
  }

  $layers = array_merge($layers, $all_layers);

  $data = array();

  $i = 0;
  foreach ($layers as $machine_name => $layer) {
    $data[$machine_name] = array(
      'name' => $layer->name,
      'machine_name' => $layer->machine_name,
      'description' => $layer->description,
      'class' => $layer->class,
      'weight' => $i++,
      'enable' => isset($layer->enable) ? $layer->enable : 0,
      'default' => 1
    );
  }

  $rows = array();
  foreach($data as $id => $entry) {
    $rows[$id] = array(
      'data' => array(
        array('class', array('entry-cross')),
        array('data' => array(
          '#type' => 'weight',
          '#title' => t('Weight'),
          '#title_display' => 'invisible',
          '#default_value' => $entry['weight'],
          '#parents' => array('layers', $id, 'weight'),
          '#attributes' => array(
            'class' => array('entry-order-weight'),
          )
        )),
        array('data' => array(
          '#type' => 'checkbox',
          '#title' => t('Enable'),
          '#title_display' => 'invisible',
          '#default_value' => $entry['enable'],
          '#parents' => array('layers', $id, 'enable'),
        )),
        array('data' => array(
          '#type' => 'checkbox',
          '#title' => t('Default'),
          '#title_display' => 'invisible',
          '#default_value' => $entry['default'],
          '#parents' => array('layers', $id, 'default'),
        )),
        check_plain($entry['name']),
        check_plain($entry['machine_name']),
        check_plain($entry['description']),
        check_plain($entry['class']),
        l(t('Edit'), 'admin/structure/openlayers/layers/list/'.$entry['machine_name'].'/edit/options',
          array(
            'query' => array(
              'destination' => current_path(),
            ),
            'attributes' => array(
              // Todo: Use CTools modal window ajax for this form.
              'class' => 'ctools-use-modall'
            )
          )
        )
      ),
      'class' => array('draggable'),
    );
    // Build rows of the form elements in the table.
    $row_elements[$id] = array(
      'weight' => &$rows[$id]['data'][1]['data'],
      'enabled' => &$rows[$id]['data'][2]['data'],
      'default' => &$rows[$id]['data'][3]['data'],
    );
  }

  // Add the table to the form.
  $form['table'] = array(
    '#theme' => 'table',
    // The row form elements need to be processed and build,
    // therefore pass them as element children.
    'elements' => $row_elements,
    '#header' => array(
      // We need two empty columns for the weigth field and the cross.
      array('data' => NULL, 'colspan' => 2),
      t('Enabled'),
      t('Default'),
      t('Name'),
      t('Machine name'),
      t('Description'),
      t('Class'),
      t('Operations'),
    ),
    '#rows' => $rows,
    '#empty' => t('There are no entries available.'),
    '#attributes' => array('id' => 'entry-order'),
  );
  drupal_add_tabledrag('entry-order', 'order', 'sibling', 'entry-order-weight');
  return $form;
}

function openlayers_map_form_layers_submit($form, &$form_state) {
  $layers = $form_state['values']['layers'];

  $layers_enabled = array();
  foreach($layers as $id => $data) {
    if ($data['enable'] == 1) {
      $layers_enabled[$data['weight']] = $id;
    }
  }

  ksort($layers_enabled);

  $form_state['item']->options['layers'] = array_values($layers_enabled);
}

function openlayers_map_form_controls($form, &$form_state) {
  $all_controls = ctools_export_crud_load_all('openlayers_controls');

  $header = array(
    'name' => t('Name'),
    'machine_name' => t('Machine name'),
    'description' => t('Description'),
    'operations' => t('Operations')
  );

  ctools_include('modal');
  ctools_modal_add_js();

  $plugin_name = 'openlayers_controls';
  $plugin = ctools_get_export_ui($plugin_name);

  $rows = array();
  foreach ($all_controls as $machine_name => $control) {
    $rows[$machine_name] = array(
      'name' => $control->name,
      'machine_name' => $control->machine_name,
      'description' => $control->description,
      'operations' => l(
        t('Edit'),
        'admin/structure/openlayers/controls/list/' . $machine_name . '/edit',
        array(
          'query' => array(
            'destination' => current_path(),
          ),
          'attributes' => array(
            // Todo: Use CTools modal window ajax for this form.
            'class' => 'ctools-use-modall'
          )
        )
      )
    );
  }

  $form['options']['#tree'] = TRUE;

  if (!isset($form_state['item']->options['controls'])) {
    $form_state['item']->options['controls'] = array();
  }

  $form['options']['controls'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $rows,
    '#default_value' => drupal_map_assoc($form_state['item']->options['controls'])
  );

  return $form;
}

function openlayers_map_form_controls_submit($form, &$form_state) {
  $form_state['item']->options['controls'] = array_filter(array_values($form_state['values']['options']['controls']));
}

function openlayers_map_form_interactions($form, &$form_state) {
  $all_interactions = ctools_export_crud_load_all('openlayers_interactions');

  $header = array(
    'name' => t('Name'),
    'machine_name' => t('Machine name'),
    'description' => t('Description'),
    'operations' => t('Operations')
  );

  $rows = array();
  foreach ($all_interactions as $machine_name => $interaction) {
    $rows[$machine_name] = array(
      'name' => $interaction->name,
      'machine_name' => $interaction->machine_name,
      'description' => $interaction->description,
      'operations' => l(
        t('Edit'),
        'admin/structure/openlayers/interactions/list/'.$machine_name.'/edit/options',
        array(
          'query' => array(
            'destination' => current_path(),
          ),
          'attributes' => array(
            // Todo: Use CTools modal window ajax for this form.
            'class' => 'ctools-use-modall'
          )
        )
      )
    );
  }

  $form['options']['#tree'] = TRUE;

  if (!isset($form_state['item']->options['interactions'])) {
    $form_state['item']->options['interactions'] = array();
  }

  $form['options']['interactions'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $rows,
    '#default_value' => drupal_map_assoc($form_state['item']->options['interactions'])
  );

  return $form;
}

function openlayers_map_form_interactions_submit($form, &$form_state) {
  $form_state['item']->options = array_replace_recursive($form_state['item']->options, $form_state['values']['options']);
  $form_state['item']->options['interactions'] = array_filter(array_values($form_state['values']['options']['interactions']));
}

function openlayers_map_form_components($form, &$form_state) {
  $all_components = ctools_export_crud_load_all('openlayers_components');

  $header = array(
    'name' => t('Name'),
    'machine_name' => t('Machine name'),
    'description' => t('Description'),
    'operations' => t('Operations')
  );

  $rows = array();
  foreach ($all_components as $machine_name => $component) {
    $rows[$machine_name] = array(
      'name' => $component->name,
      'machine_name' => $component->machine_name,
      'description' => $component->description,
      'operations' => l(
        t('Edit'),
        'admin/structure/openlayers/components/list/'.$machine_name.'/edit/options',
        array(
          'query' => array(
            'destination' => current_path(),
          ),
          'attributes' => array(
            // Todo: Use CTools modal window ajax for this form.
            'class' => 'ctools-use-modall'
          )
        )
      )
  );
  }

  $form['options']['#tree'] = TRUE;

  if (!isset($form_state['item']->options['components'])) {
    $form_state['item']->options['components'] = array();
  }

  $form['options']['components'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $rows,
    '#default_value' => drupal_map_assoc($form_state['item']->options['components'])
  );

  return $form;
}

function openlayers_map_form_components_submit($form, &$form_state) {
  $form_state['item']->options = array_replace_recursive($form_state['item']->options, $form_state['values']['options']);
  $form_state['item']->options['components'] = array_filter(array_values($form_state['values']['options']['components']));
}

function openlayers_map_form_styles($form, &$form_state) {
  return $form;
}

function openlayers_map_form_styles_submit($form, &$form_state) {
//  $form_state['item']->options = $form_state['item']->options, (array) $form_state['values']['options']);
}

function openlayers_map_form_preview($form, &$form_state) {
  $map = openlayers_object_load('map', $form_state['item']);
  $map->setOption('contextualLinks', FALSE);

  $form['preview'] = array(
    '#markup' => openlayers_render_map($map)
  );

  return $form;
}
function openlayers_map_form_preview_submit($form, &$form_state) {}

function _openlayers_maps_sort_by_weight($a, $b) {
  if (isset($a['weight']) && isset($b['weight'])) {
    return $a['weight'] < $b['weight'] ? -1 : 1;
  }
  return 0;
}

