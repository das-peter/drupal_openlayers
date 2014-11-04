<?php

abstract class openlayers_layer extends openlayers_object implements openlayers_layer_interface {

  protected $attached = array();

  public function getSource() {
    if ($source = $this->getOption('source')) {
      return openlayers_object_load('source', $this->getOption('source'));
    }
    return FALSE;
  }

  public function getStyle() {
    if ($style = $this->getOption('style')) {
      return openlayers_object_load('style', $this->getOption('style'));
    }
    return FALSE;
  }

  public function develop() {
    if ($data = $this->getSource()) {
      $this->setOption('source', $data);
    }
  }
}
