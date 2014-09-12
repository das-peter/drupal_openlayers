<?php

abstract class openlayers_layer extends openlayers_object {

  protected $attached = array();

  public function getSource() {
    return $this->getOption('source');
  }

  public function attached() {
    if ($source = $this->getSource()) {
      $source = openlayers_object_load('source', $source);
      $this->attached = drupal_array_merge_deep($this->attached, $source->attached());
    }
    $this->attached = drupal_array_merge_deep($this->attached, parent::attached());
    return $this->attached;
  }
}
