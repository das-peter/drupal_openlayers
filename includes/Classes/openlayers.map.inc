<?php

class openlayers_map extends openlayers_object implements openlayers_map_interface {

  protected $id;

  function init(array $data) {
    parent::init($data);

    $this->setOption('target', $this->getId());
  }


  public function getId() {
    if (isset($this->id)) {
      return $this->id;
    }

    $css_map_name = drupal_clean_css_identifier($this->machine_name);
    $this->id = drupal_html_id('openlayers-map-' . $css_map_name);
    return $this->id;
  }

  public function getLayers() {
    if ($layers = $this->getOption('layers')) {
      $result = array();
      foreach($layers as $layer) {
        $result[] = clone openlayers_object_load('layer', $layer);
      }
      return $result;
    }
    return array();
  }

  public function getSources() {
    $sources = array();
    $layers = $this->getLayers();

    foreach($layers as $index => $layer) {
      if ($source = $layer->getSource()) {
        $sources[] = $source;
      }
    }

    return $sources;
  }

  public function getControls() {
    $result = array();
    if ($controls = $this->getOption('controls')) {
      foreach($controls as $control) {
        $result[] = clone openlayers_object_load('control', $control);
      }
    }
    return $result;
  }

  public function getInteractions() {
    $result = array();
    if ($interactions = $this->getOption('interactions')) {
      foreach($interactions as $index => $interaction) {
        $result[] = clone openlayers_object_load('interaction', $interaction);
      }
    }
    return $result;
  }

  public function getComponents() {
    $result = array();
    if ($components = $this->getOption('components')) {
      foreach($components as $component) {
        $result[] = clone openlayers_object_load('component', $component);
      }
    }
    return $result;
  }

  public function develop() {
    if ($layers = $this->getLayers()) {
      $this->options['layers'] = array();
      foreach ($layers as $data) {
        $object = clone openlayers_object_load('layer', $data);
        $this->options['layers'][] = $object;
      }
    }
    if ($controls = $this->getControls()) {
      $this->options['controls'] = array();
      foreach ($controls as $data) {
        $object = clone openlayers_object_load('control', $data);
        $this->options['controls'][] = $object;
      }
    }
    if ($interactions = $this->getInteractions()) {
      $this->options['interactions'] = array();
      foreach ($interactions as $index => $data) {
        $object = clone openlayers_object_load('interaction', $data);
        $this->options['interactions'][] = $object;
      }
    }
    if ($components = $this->getComponents()) {
      $this->options['components'] = array();
      foreach ($components as $index => $data) {
        $object = clone openlayers_object_load('component', $data);
        $this->options['components'][] = $object;
      }
    }
  }

  public function getObjects() {
    $objects = array();
    $objects['layer'] = $this->getLayers();
    $objects['source'] = $this->getSources();
    $objects['control'] = $this->getControls();
    $objects['interaction'] = $this->getInteractions();
    $objects['component'] = $this->getComponents();

    $objects = unserialize(serialize($objects));

    foreach($objects['layer'] as $index => $layer) {
      if ($source = $layer->getSource()) {
        $objects['layer'][$index]->options['source'] = $source->machine_name;
      }
    }

    return $objects;
  }

  public function getJSObjects() {
    $objects = $this->getObjects();

    foreach(array('layer', 'source', 'control', 'interaction', 'component') as $type) {
      foreach($objects[$type] as $index => $object) {
        $objects[$type][$index] = (array) $object->toJSArray();
      }
    }

    $objects['map'] = $this->toJSArray();

    $objects = array_map_recursive('_floatval_if_numeric', $objects);
    $objects = removeEmptyElements($objects);

    return $objects;
  }

  public function attached() {
    $this->attached = parent::attached();
    $objects = $this->getObjects();

    foreach($objects as $type => $list) {
      if ($list == FALSE) continue;
      foreach($list as $index => $data) {
        $this->attached = drupal_array_merge_deep($this->attached, $data->attached());
      }
    }

    return $this->attached;
  }
}
