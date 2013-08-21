<?php

/**
 * TODO: Create dropdown for brother ids from brother record
 */

function restriction_restrictions() {
  //Create a list of headers for the Html table
  $header = array(		
	  array('data' => 'Restriction ID', 'field' => 'rid'),
	  array('data' => 'Date', 'field' => 'restriction_date'),
	  array('data' => 'Restriction Code', 'field' => 'restriction_code'),
	  array('data' => 'Brother ID', 'field' => 'bid'),
	);

  //Create the Sql query. This uses various parts of Drupal 7's new DBTNG database abstraction layer.
  $query = db_select('restriction', 'r')
			->extend('PagerDefault')
				->limit(variable_get('restriction_list_limit', 25))
			->extend('TableSort')
				->orderByHeader($header)
			->fields('r', array('rid', 'restriction_date', 'bid', 'restriction_code'));

  $results = $query->execute();

  $rows = array();	
  foreach ($results as $restriction) {
	  $rows[] = array(
			'data' => array(
				$restriction->rid,
				l(ptc_epoch2date($restriction->restriction_date), 'restriction/' . $restriction->rid . '/edit'),
				$restriction->restriction_code,
			  $restriction->bid,
			)
		);
  }

	//Theme the html table
	$html = theme('table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No restrictions created...',
		)
	);

	//Append pager
	$html .= theme('pager',
		array(
			'tags' => array()
		)
	);
		
	return ($html);
}

/*
this is function which print the actual entity whether in a full page, or a teaser
it attaches any fields required to attach to the view mode
*/
function restriction_page_view($restriction, $view_mode = 'full') {
	$restriction->content = array();

	$restriction->content['rid']=array(
		'#prefix' => '<div>',
		'#markup' => $restriction->rid,
		'#suffix' => '</div>',
		'#weight' => -8,
	);
	$restriction->content['restriction_date']=array(
		'#prefix' => '<div>',
		'#markup' => ptc_epoch2date($restriction->restriction_date),
		'#suffix' => '</div>',
		'#weight' => -7,
	);
	$restriction->content['bid']=array(
		'#prefix' => '<div>',
		'#markup' => $restriction->bid,
		'#suffix' => '</div>',
		'#weight' => -6,
	);
	$restriction->content['restriction_code']=array(
		'#prefix' => '<div>',
		'#markup' => $restriction->restriction_code,
		'#suffix' => '</div>',
		'#weight' => -5,
	);
	
	entity_prepare_view('restriction', array($restriction->rid => $restriction));
	
	return $restriction->content;
}

/*
this is the edit page
*/
function restriction_page_edit($restriction) {
	drupal_set_title(t('<em>Edit @type:<em>', array('@type'=>'Restriction')), PASS_THROUGH);
	return drupal_get_form('restriction_form', $restriction);
}

function restriction_form($form, &$form_state, $restriction) {
	$form['#id'] = 'restriction-form';
	$form['#restriction'] = $restriction;
	$form_state['restriction'] = $restriction;
	
	$form['rid']=array(
		'#type'          => 'hidden',
		'#weight'        => 1,
	);
	$form['restriction_date']=array(
		'#type'          => 'textfield',
		'#title'         => t('Restriction Date'),
		'#default_value' => !empty($restriction->restriction_date) ? ptc_epoch2date($restriction->restriction_date) : NULL,
		'#weight'        => 2,
	);
	$form['bid']=array(
		'#type'          => 'textfield',
		'#title'         => t('BID'),
		'#default_value' => $restriction->bid,
		'#weight'        => 3,
	);
	$form['restriction_code']=array(
		'#type'          => 'select',
		'#title'         => t('Restriction Code'),
		'#options'       => get_restriction_reason_options(),
		'#default_value' => $restriction->restriction_code,
		'#weight'        => 4,
	);

	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'   => 'submit',
		'#value'  => t('Save'),
		'#weight' => 25,
		'#submit' => array('restriction_form_submit'),
	);
	
	if (!empty($restriction->rid)) {
		$form['buttons']['delete'] = array(
			'#type'   => 'submit',
			'#value'  => t('Delete'),
			'#access' => talk_access('delete', $restriction),
			'#weight' => 35,
			'#submit' => array('restriction_form_delete_submit'),
		);
	}
	$form['#validate'][] = 'restriction_form_validate';
	return $form;
}

function restriction_form_validate($form, &$form_state) {
	$restriction = $form_state['restriction'];
}

function restriction_form_submit($form, &$form_state) {
	$restriction = $form_state['restriction'];
	//$restriction->rid = $form_state['values']['rid'];
	$restriction->restriction_date = ptc_date2epoch($form_state['values']['restriction_date']);
	$restriction->bid = $form_state['values']['bid'];
	$restriction->restriction_code = $form_state['values']['restriction_code'];
	
	restriction_save($restriction);
	drupal_set_message(t('Restriction saved'));
	$form_state['redirect'] = 'setup/restrictions/restriction';
}

function restriction_form_delete_submit($form, &$form_state) {
	$destination = array();
	
	if(isset($_GET['destination'])){
		$destination=drupal_get_destination();
		unset($_GET['destination']);
	}
	
	$restriction = $form['#restriction'];
	$form_state['redirect'] = array('restriction/' . $restriction->rid . '/delete', array('query' => $destination));
}

function restriction_delete_confirm($form, &$form_state, $restriction) {
	$form['#restriction'] = $restriction;
	$form['tid'] = array(
		'#type' => 'value',
		'#value' => $restriction->rid,
	);

	return confirm_form(
		$form,
		t('Are you sure you want to delete %title', array('%title' => $restriction->restriction_code)),
		'restriction/' . $restriction->rid,
		t('This action cannot be undone'),
		t('Delete'),
		t('Cancel')
	);
}

function restriction_delete_confirm_submit($form, &$form_state) {
	if($form_state['values']['confirm']){
		$restriction = restriction_load($form_state['values']['rid']);
		restriction_delete($form_state['values']['rid']);
		watchdog('restriction', '@type: deleted %title', array('@type'=>'restriction', '%title'=>$restriction->restriction_code));
		drupal_set_message(t('@type has been deleted', array('@type'=>'restriction')));
	}
	$form_state['redirect'] = 'setup/restrictions/restriction';
}

function restriction_delete($rid){
	return restriction_delete_multiple(array($rid));
}

function restriction_delete_multiple($rids){
	return entity_get_controller('restriction')->delete($rids);
}

/*
this is the add page
*/
function restriction_add_page() {
	$item = menu_get_item();
	$items = array();
	$links = system_admin_menu_block($item);

	foreach ($links as $link) {
		$items[]=l($link['title'], $link['href'], $link['localized_options']) . ':' . filter_xss_admin($link['description']);
	}
	return theme('item_list', array('items' => $items));
}

function restriction_add() {
	$type = 'restriction';
	
	$restriction = entity_get_controller('restriction')->create($type);
	drupal_set_title(t('Create @name', array('@name' => 'restriction')), PASS_THROUGH);
	return drupal_get_form('restriction_form', $restriction);
}

function restriction_save($restriction) {
	return entity_get_controller('restriction')->save($restriction);
}

function get_restriction_reason_options() {
	$result = db_select('restriction_reason', 'rr')
			->fields('rr', array('restriction_code', 'restriction_description'))
			->execute();
			
	$array = $result->fetchAllKeyed();
	
	return $array;
}