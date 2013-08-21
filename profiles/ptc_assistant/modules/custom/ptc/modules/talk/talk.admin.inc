<?php

function talk_overview_types() {
	foreach (talk_types() as $type => $info) {
		$type_url_str = str_replace('_', '-', $type);
		$label = t('View @type', array('@type' => $info->name));
		$items[] = l($label, 'admin/structure/talk/manage/' . $type_url_str);
	}

	return theme('item_list', array('items' => $items));
}

function talk_information($talk_type) {
	return $talk_type->name . ':' . $talk_type->description;
}

function talk_admin(){
	return;
}