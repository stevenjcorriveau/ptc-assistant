<?php

function restriction_reason_restriction_reasons() {
  //Create a list of headers for the Html table
  $header = array(		
	  array('data' => 'Restriction Reason ID', 'field' => 'rid'),
	  array('data' => 'Restriction Reason Code', 'field' => 'restriction_code'),
	  array('data' => 'Description', 'field' => 'restriction_description'),
	  array('data' => 'Hard/Soft', 'field' => 'hard_soft_code'),
	);

  //Create the Sql query. This uses various parts of Drupal 7's new DBTNG database abstraction layer.
  $query = db_select('restriction_reason', 'rr')
			->extend('PagerDefault')
				->limit(variable_get('restriction_reason_list_limit', 25))
			->extend('TableSort')
				->orderByHeader($header)
			->fields('rr', array('rid', 'restriction_code', 'restriction_description', 'hard_soft_code'));

  $results = $query->execute();

  $rows = array();	
  foreach ($results as $restriction_reason) {
	  $rows[] = array(
			'data' => array(
				$restriction_reason->rid,
				l($restriction_reason->restriction_code, 'restriction_reason/' . $restriction_reason->rid . '/edit'),
				$restriction_reason->restriction_description,
			  ($restriction_reason->hard_soft_code > 0) ? 'Hard' : 'Soft',
			)
		);
  }

	//Theme the html table
	$html = theme('table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No restriction reasons created...',
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
function restriction_reason_page_view($restriction_reason, $view_mode = 'full') {
	$restriction_reason->content = array();

	$restriction_reason->content['rid']=array(
		'#prefix' => '<div>',
		'#markup' => $restriction_reason->rid,
		'#suffix' => '</div>',
		'#weight' => 1,
	);
	$restriction_reason->content['restriction_code']=array(
		'#prefix' => '<div>',
		'#markup' => $restriction_reason->restriction_code,
		'#suffix' => '</div>',
		'#weight' => 2,
	);
	$restriction_reason->content['restriction_description']=array(
		'#prefix' => '<div>',
		'#markup' => $restriction_reason->restriction_description,
		'#suffix' => '</div>',
		'#weight' => 3,
	);
	$restriction_reason->content['hard_soft_code']=array(
		'#prefix' => '<div>',
		'#markup' => isset($restriction_reason->hard_soft_code) ? 'Hard' : 'Soft',
		'#suffix' => '</div>',
		'#weight' => 4,
	);
	
	entity_prepare_view('restriction_reason', array($restriction_reason->rid => $restriction_reason));
	
	return $restriction_reason->content;
}

/*
this is the edit page
*/
function restriction_reason_page_edit($restriction_reason) {
	drupal_set_title(t('<em>Edit @type:<em>', array('@type'=>'Restriction Reason')), PASS_THROUGH);
	return drupal_get_form('restriction_reason_form', $restriction_reason);
}

function restriction_reason_form($form, &$form_state, $restriction_reason) {
	$form['#id'] = 'restriction-reason-form';
	$form['#restriction_reason'] = $restriction_reason;
	$form_state['restriction_reason'] = $restriction_reason;
	
	$form['rid']=array(
		'#type'          => 'hidden',
		'#weight'        => 1,
	);
	$form['restriction_code']=array(
		'#type'          => 'textfield',
		'#title'         => t('Restriction Code'),
		'#default_value' => $restriction_reason->restriction_code,
		'#weight'        => 2,
	);
	$form['restriction_description']=array(
		'#type'          => 'textfield',
		'#title'         => t('Description'),
		'#default_value' => $restriction_reason->restriction_description,
		'#weight'        => 3,
	);
	$types = array(0 => t('Soft'), 1 => t('Hard'));
	$form['hard_soft_code']=array(
		'#type'          => 'radios',
		'#title'         => t('Type'),
		'#default_value' => isset($restriction_reason->hard_soft_code) ? $restriction_reason->hard_soft_code : 1,
    '#options'       => $types,
		'#weight'        => 4,
	);

	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'   => 'submit',
		'#value'  => t('Save'),
		'#weight' => 25,
		'#submit' => array('restriction_reason_form_submit'),
	);
	
	if (!empty($restriction_reason->rid)) {
		$form['buttons']['delete'] = array(
			'#type'   => 'submit',
			'#value'  => t('Delete'),
			'#access' => talk_access('delete', $restriction_reason),
			'#weight' => 35,
			'#submit' => array('restriction_reason_form_delete_submit'),
		);
	}
	$form['#validate'][] = 'restriction_reason_form_validate';
	return $form;
}

function restriction_reason_form_validate($form, &$form_state) {
	$restriction_reason = $form_state['restriction_reason'];
}

function restriction_reason_form_submit($form, &$form_state) {
	$restriction_reason = $form_state['restriction_reason'];
	//$restriction->rid = $form_state['values']['rid'];
	$restriction_reason->restriction_code = $form_state['values']['restriction_code'];
	$restriction_reason->restriction_description = $form_state['values']['restriction_description'];
	$restriction_reason->hard_soft_code = $form_state['values']['hard_soft_code'];
	
	restriction_reason_save($restriction_reason);
	drupal_set_message(t('Restriction Reason saved'));
	$form_state['redirect'] = 'setup/restrictions/restriction_reason';
}

function restriction_reason_form_delete_submit($form, &$form_state) {
	$destination = array();
	
	if(isset($_GET['destination'])){
		$destination=drupal_get_destination();
		unset($_GET['destination']);
	}
	
	$restriction_reason = $form['#restriction_reason'];
	$form_state['redirect'] = array('restriction_reason/' . $restriction_reason->rid . '/delete', array('query' => $destination));
}

function restriction_reason_delete_confirm($form, &$form_state, $restriction_reason) {
	$form['#restriction_reason'] = $restriction_reason;
	$form['rid'] = array(
		'#type' => 'value',
		'#value' => $restriction_reason->rid,
	);

	return confirm_form(
		$form,
		t('Are you sure you want to delete %title', array('%title' => $restriction_reason->restriction_code)),
		'restriction_reason/' . $restriction_reason->rid . '/edit',
		t('This action cannot be undone'),
		t('Delete'),
		t('Cancel')
	);
}

function restriction_reason_delete_confirm_submit($form, &$form_state) {
	if($form_state['values']['confirm']){
		$restriction_reason = restriction_reason_load($form_state['values']['rid']);
		restriction_reason_delete($form_state['values']['rid']);
		watchdog('restriction_reason', '@type: deleted %title', array('@type'=>'restriction_reason', '%title'=>$restriction_reason->restriction_code));
		drupal_set_message(t('@type has been deleted', array('@type'=>'restriction_reason')));
	}
	$form_state['redirect'] = 'setup/restrictions/restriction_reason';
}

function restriction_reason_delete($rid){
	return restriction_reason_delete_multiple(array($rid));
}

function restriction_reason_delete_multiple($rids){
	return entity_get_controller('restriction_reason')->delete($rids);
}

/*
this is the add page
*/
function restriction_reason_add_page() {
	$item = menu_get_item();
	$items = array();
	$links = system_admin_menu_block($item);

	foreach ($links as $link) {
		$items[]=l($link['title'], $link['href'], $link['localized_options']) . ':' . filter_xss_admin($link['description']);
	}
	return theme('item_list', array('items' => $items));
}

function restriction_reason_add() {
	$type = 'restriction_reason';
	
	$restriction_reason = entity_get_controller('restriction_reason')->create($type);
	drupal_set_title(t('Create @name', array('@name' => 'restriction_reason')), PASS_THROUGH);
	return drupal_get_form('restriction_reason_form', $restriction_reason);
}

function restriction_reason_save($restriction_reason) {
	return entity_get_controller('restriction_reason')->save($restriction_reason);
}