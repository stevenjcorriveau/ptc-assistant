<?php

/*
 * This is the edit page
 */
function meeting_time_page_edit($meeting_time) {
	drupal_set_title(t('<em>Edit @type:<em>', array('@type'=>'Meeting Time')), PASS_THROUGH);
	return drupal_get_form('meeting_time_form', $meeting_time);
}

function meeting_time_form($form, &$form_state, $meeting_time) {
	module_load_include('inc', 'ptc', 'ptc.pages');
	
	$form['#id'] = 'meeting-time-form';
	$form['#meeting_time'] = $meeting_time;
	$form_state['meeting_time'] = $meeting_time;
	
	$form['cid']=array(
		'#type'          => 'hidden',
		'#value'         => $meeting_time->cid,
		'#weight'        => 1,
	);
	$form['time_code']=array(
		'#type'          => 'textfield',
		'#title'         => t('Time Code'),
		'#default_value' => $meeting_time->time_code,
		'#weight'        => 2,
	);
	$form['meeting_time']=array(
		'#type'          => 'textfield',
		'#title'         => t('Meeting Time'),
		'#default_value' => $meeting_time->meeting_time,
		'#weight'        => 3,
	);

	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'   => 'submit',
		'#value'  => t('Save'),
		'#weight' => 25,
		'#submit' => array('meeting_time_form_submit'),
	);
	
	if (!empty($meeting_time->mtid)) {
		$form['buttons']['delete'] = array(
			'#type'   => 'submit',
			'#value'  => t('Delete'),
			'#access' => talk_access('delete', $meeting_time),
			'#weight' => 35,
			'#submit' => array('meeting_time_form_delete_submit'),
		);
	}
	$form['#validate'][] = 'meeting_time_form_validate';
	return $form;
}

function meeting_time_form_validate($form, &$form_state) {
	$meeting_time = $form_state['meeting_time'];
}

function meeting_time_form_submit($form, &$form_state) {
	$meeting_time = $form_state['meeting_time'];
	$meeting_time->cid = $form_state['values']['cid'];
	$meeting_time->time_code = $form_state['values']['time_code'];
	$meeting_time->meeting_time = $form_state['values']['meeting_time'];
	
	meeting_time_save($meeting_time);
	drupal_set_message(t('Meeting time saved'));
	$form_state['redirect'] = '/congregation/'. $meeting_time->cid .'/edit';
}

function meeting_time_form_delete_submit($form, &$form_state) {
	$destination = array();
	
	if(isset($_GET['destination'])){
		$destination=drupal_get_destination();
		unset($_GET['destination']);
	}
	
	$meeting_time = $form['#meeting_time'];
	$form_state['redirect'] = array('meeting_time/' . $meeting_time->mtid . '/delete', array('query' => $destination));
}

function meeting_time_delete_confirm($form, &$form_state, $meeting_time) {
	$form['#meeting_time'] = $meeting_time;
	$form['mtid'] = array(
		'#type' => 'value',
		'#value' => $meeting_time->mtid,
	);

	return confirm_form(
		$form,
		t('Are you sure you want to delete %title', array('%title' => $meeting_time->time_code)),
		'meeting_time/' . $meeting_time->mtid . '/edit',
		t('This action cannot be undone'),
		t('Delete'),
		t('Cancel')
	);
}

function meeting_time_delete_confirm_submit($form, &$form_state) {
	if($form_state['values']['confirm']){
		$meeting_time = meeting_time_load($form_state['values']['mtid']);
		meeting_time_delete($form_state['values']['mtid']);
		watchdog('meeting_time', '@type: deleted %title', array('@type'=>'meeting_time', '%title'=>$meeting_time->time_code));
		drupal_set_message(t('@type has been deleted', array('@type'=>'Meeting time')));
	}
	$form_state['redirect'] = '/congregation/' . $meeting_time->cid . '/edit';
}

function meeting_time_delete($mtid){
	return meeting_time_delete_multiple(array($mtid));
}

function meeting_time_delete_multiple($mtids){
	return entity_get_controller('meeting_time')->delete($mtids);
}

/*
this is the add page
*/
function meeting_time_add_page() {
	$item = menu_get_item();
	$items = array();
	$links = system_admin_menu_block($item);

	foreach ($links as $link) {
		$items[]=l($link['title'], $link['href'], $link['localized_options']) . ':' . filter_xss_admin($link['description']);
	}
	return theme('item_list', array('items' => $items));
}

function meeting_time_add() {
  $cong = arg(2);
	$type = 'meeting_time';
	
	$meeting_time = entity_get_controller('meeting_time')->create($type);
	$meeting_time->cid = $cong;

	drupal_set_title(t('Create @name', array('@name' => 'Meeting time')), PASS_THROUGH);
	return drupal_get_form('meeting_time_form', $meeting_time);
}

function meeting_time_save($meeting_time) {
	return entity_get_controller('meeting_time')->save($meeting_time);
}