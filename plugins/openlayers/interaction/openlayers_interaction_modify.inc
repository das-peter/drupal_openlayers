<?php

function openlayers_openlayers_interaction_modify_openlayers_interaction() {
  return array(
    'handler' => array(
      'class' => 'openlayers_interaction_modify',
      'file' => 'openlayers_interaction_modify.inc',
    )
  );
}

class openlayers_interaction_modify extends openlayers_interaction {

}
