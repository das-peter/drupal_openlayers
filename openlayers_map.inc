<?php
// $Id$

function openlayers_form(&$node) {
	$type = node_get_types('type', $node);

	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => check_plain($type->title_label),
		'#required' => TRUE,
		'#default_value' => $node->title,
		'#weight' => -5
	);

	$form['body_filter']['body'] = array(
    	'#type' => 'textarea',
    	'#title' => check_plain($type->body_label),
    	'#default_value' => $node->body,
    	'#required' => FALSE
	);
	
	$form['body_filter']['filter'] = filter_form($node->format);
	
	return $form;
}

function openlayers_insert() {

}

function openlayers_update() {

}

function openlayers_delete() {

}

function openlayers_validate() {

}

function openlayers_nodeapi() {

}

function openlayers_view() {

}

function openlayers_load() {

}
