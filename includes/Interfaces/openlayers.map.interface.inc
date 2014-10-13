<?php

interface openlayers_map_interface {
  public function getId();
  public function getObjects();
  public function getJSObjects();
  public function getLayers();
  public function getSources();
  public function getControls();
  public function getInteractions();
  public function getComponents();
}
