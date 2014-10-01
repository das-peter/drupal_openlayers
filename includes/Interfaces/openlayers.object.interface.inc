<?php

interface openlayers_object_interface {
  public function defauts_properties();
  public function init(array $data);
  public function getType();
  public function develop();
  public function clearOption($parents);
  public function getOption($parents, $default_value);
  public function setOption($parents, $value);
  public function options_form();
  public function options_form_validate();
  public function options_form_submit();
  public function toArray();
  public function attached();
  public function dependencies();
}
