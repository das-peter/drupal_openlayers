<?php

class openlayers_map extends openlayers_object {

  protected $id;
  protected $attached = array();

  public function getId() {
    if (isset($this->id)) {
      return $this->id;
    }

    $css_map_name = drupal_clean_css_identifier($this->machine_name);
    $this->id = drupal_html_id('openlayers-map-' . $css_map_name);
    return $this->id;
  }

  public function getLayers() {
    if ($this->getOption('layers')) {
      if (is_array($this->getOption('layers'))) {
        return $this->getOption('layers');
      }
    }
    return FALSE;
  }

  public function getSources() {
    if ($this->getOption('layers')) {
      if (is_array($this->getOption('layers'))) {
        $sources = array();
        foreach($this->getOption('layers') as $index => $machine_name) {
          $layer = openlayers_object_load('layer', $machine_name);
          if ($source = $layer->getOption('source')) {
            $sources[] = $source;
          }
        }
        return $sources;
      }
    }
    return FALSE;
  }

  public function getControls() {
    if ($this->getOption('controls')) {
      if (is_array($this->getOption('controls'))) {
        return $this->getOption('controls');
      }
    }
    return FALSE;
  }

  public function getInteractions() {
    if ($this->getOption('interactions')) {
      if (is_array($this->getOption('interactions'))) {
        return $this->getOption('interactions');
      }
    }
    return FALSE;
  }

  public function attached() {
    $this->attached = parent::attached();

    if ($layers = $this->getLayers()) {
      foreach($layers as $index => $machine_name) {
        $layer = openlayers_object_load('layer', $machine_name);
        $this->attached = drupal_array_merge_deep($this->attached, $layer->attached());
      }
    }
    if ($interactions = $this->getControls()) {
      foreach($interactions as $index => $machine_name) {
        $control = openlayers_object_load('control',$machine_name);
        $this->attached = drupal_array_merge_deep($this->attached, $control->attached());
      }
    }
    if ($interactions = $this->getInteractions()) {
      foreach($interactions as $index => $machine_name) {
        $interaction = openlayers_object_load('interaction',$machine_name);
        $this->attached = drupal_array_merge_deep($this->attached, $interaction->attached());
      }
    }
    return $this->attached;
  }
}
