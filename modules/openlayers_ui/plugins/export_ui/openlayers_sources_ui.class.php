<?php

class openlayers_sources_ui extends openlayers_objects_ui {

  /**
   * hook_menu() entry point.
   *
   * Child implementations that need to add or modify menu items should
   * probably call parent::hook_menu($items) and then modify as needed.
   */
  function hook_menu(&$items) {
    parent::hook_menu($items);
    $items['admin/structure/openlayers/sources']['type'] = MENU_LOCAL_TASK;
    $items['admin/structure/openlayers/sources']['weight'] = -1;
  }

}
