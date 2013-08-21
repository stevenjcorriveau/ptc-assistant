<?php

/**
 * TODO: Create dropdown for brother ids from brother record
 */

function kingdom_hall_kingdom_halls() {
  //Create a list of headers for the Html table
  $header = array(		
	  array('data' => 'Kingdom Hall ID', 'field' => 'khid'),
	  array('data' => 'Name', 'field' => 'kingdom_hall_name'),
	  array('data' => 'Active', 'field' => 'active'),
	  array('data' => 'Address', 'field' => 'address'),
	  array('data' => 'City', 'field' => 'city'),
	  array('data' => 'State', 'field' => 'state'),
	  array('data' => 'Zipcode', 'field' => 'zipcode'),
	  array('data' => 'Directions', 'field' => 'directions'),
	  array('data' => 'Print Directions', 'field' => 'print_directions'),
	  array('data' => 'Travel Time', 'field' => 'approx_travel_time'),
	  array('data' => 'Reference', 'field' => 'travel_reference'),
	);

  // Create the Sql query. This uses various parts of Drupal 7's new DBTNG 
	// database abstraction layer.
  $query = db_select('kingdom_hall', 'kh')
			->extend('PagerDefault')
				->limit(variable_get('kingdom_hall_list_limit', 25))
			->extend('TableSort')
				->orderByHeader($header)
			->fields('kh', array('khid', 'kingdom_hall_name', 'active', 'address', 
			         'city', 'state', 'zipcode', 'directions', 'print_directions', 
							 'approx_travel_time', 'travel_reference'));

  $results = $query->execute();

  $rows = array();	
  foreach ($results as $kingdom_hall) {
	  $rows[] = array(
			'data' => array(
				$kingdom_hall->khid,
				l($kingdom_hall->kingdom_hall_name, 'kingdom_hall/' . $kingdom_hall->khid . '/edit'),
				($kingdom_hall->active > 0) ? 'Yes' : 'No',
			  $kingdom_hall->address,
			  $kingdom_hall->city,
			  $kingdom_hall->state,
			  $kingdom_hall->zipcode,
			  $kingdom_hall->directions,
			  ($kingdom_hall->print_directions > 0) ? 'Yes' : 'No',
			  $kingdom_hall->approx_travel_time,
			  $kingdom_hall->travel_reference,
			)
		);
  }

	//Theme the html table
	$html = theme('table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No Kingdom Halls created...',
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
 * this is function which print the actual entity whether in a full page, or a 
 * teaser it attaches any fields required to attach to the view mode
 */
function kingdom_hall_page_view($kingdom_hall, $view_mode = 'full') {
	$kingdom_hall->content = array();

	$kingdom_hall->content['khid']=array(
		'#prefix' => '<div>',
		'#markup' => $kingdom_hall->khid,
		'#suffix' => '</div>',
		'#weight' => 1,
	);
	$kingdom_hall->content['kingdom_hall_name']=array(
		'#prefix' => '<div>',
		'#markup' => $kingdom_hall->kingdom_hall_name,
		'#suffix' => '</div>',
		'#weight' => 2,
	);
	$kingdom_hall->content['active']=array(
		'#prefix' => '<div>',
		'#markup' => $kingdom_hall->active,
		'#suffix' => '</div>',
		'#weight' => 3,
	);
	$kingdom_hall->content['address']=array(
		'#prefix' => '<div>',
		'#markup' => $kingdom_hall->address,
		'#suffix' => '</div>',
		'#weight' => 4,
	);
	$kingdom_hall->content['city']=array(
		'#prefix' => '<div>',
		'#markup' => $kingdom_hall->city,
		'#suffix' => '</div>',
		'#weight' => 5,
	);
	$kingdom_hall->content['state']=array(
		'#prefix' => '<div>',
		'#markup' => $kingdom_hall->state,
		'#suffix' => '</div>',
		'#weight' => 6,
	);
	$kingdom_hall->content['zipcode']=array(
		'#prefix' => '<div>',
		'#markup' => $kingdom_hall->zipcode,
		'#suffix' => '</div>',
		'#weight' => 7,
	);
	$kingdom_hall->content['directions']=array(
		'#prefix' => '<div>',
		'#markup' => $kingdom_hall->directions,
		'#suffix' => '</div>',
		'#weight' => 8,
	);
	$kingdom_hall->content['print_directions']=array(
		'#prefix' => '<div>',
		'#markup' => $kingdom_hall->print_directions,
		'#suffix' => '</div>',
		'#weight' => 9,
	);
	$kingdom_hall->content['approx_travel_time']=array(
		'#prefix' => '<div>',
		'#markup' => $kingdom_hall->approx_travel_time,
		'#suffix' => '</div>',
		'#weight' => 10,
	);
	$kingdom_hall->content['travel_reference']=array(
		'#prefix' => '<div>',
		'#markup' => $kingdom_hall->travel_reference,
		'#suffix' => '</div>',
		'#weight' => 11,
	);
	
	entity_prepare_view('kingdom_hall', array($kingdom_hall->khid => $kingdom_hall));
	
	return $kingdom_hall->content;
}

/*
 * This is the edit page
 */
function kingdom_hall_page_edit($kingdom_hall) {
	drupal_set_title(t('<em>Edit @type:<em>', array('@type'=>'Kingdom Hall')), PASS_THROUGH);
	return drupal_get_form('kingdom_hall_form', $kingdom_hall);
}

function kingdom_hall_form($form, &$form_state, $kingdom_hall) {
	module_load_include('inc', 'ptc', 'ptc.pages');
	
	$form['#id'] = 'kingdom-hall-form';
	$form['#kingdom_hall'] = $kingdom_hall;
	$form_state['kingdom_hall'] = $kingdom_hall;
	
	$form['khid']=array(
		'#type'          => 'hidden',
		'#weight'        => 1,
	);
	$form['kingdom_hall_name']=array(
		'#type'          => 'textfield',
		'#title'         => t('Kingdom Hall'),
		'#default_value' => $kingdom_hall->kingdom_hall_name,
		'#weight'        => 2,
	);
	$form['active']=array(
		'#type'          => 'checkbox',
		'#title'         => t('Active'),
		'#default_value' => $kingdom_hall->active,
		'#weight'        => 3,
	);
	$form['address']=array(
		'#type'          => 'textfield',
		'#title'         => t('Address'),
		'#default_value' => $kingdom_hall->address,
		'#weight'        => 4,
	);
	$form['city']=array(
		'#type'          => 'textfield',
		'#title'         => t('City'),
		'#default_value' => $kingdom_hall->city,
		'#weight'        => 5,
	);
	$form['state']=array(
		'#type'          => 'select',
		'#title'         => t('State'),
		'#options'       => get_state_options(),
		'#default_value' => $kingdom_hall->state,
		'#weight'        => 6,
	);
	$form['zipcode']=array(
		'#type'          => 'textfield',
		'#title'         => t('Zip'),
		'#default_value' => $kingdom_hall->zipcode,
		'#weight'        => 7,
	);
	$form['directions']=array(
		'#type'          => 'textarea',
		'#title'         => t('Directions'),
		'#default_value' => $kingdom_hall->directions,
		'#weight'        => 8,
	);
	$form['print_directions']=array(
		'#type'          => 'checkbox',
		'#title'         => t('Print directions'),
		'#default_value' => $kingdom_hall->print_directions,
		'#weight'        => 9,
	);
	$form['approx_travel_time']=array(
		'#type'          => 'textfield',
		'#title'         => t('Approx. Travel Time'),
		'#default_value' => $kingdom_hall->approx_travel_time,
		'#weight'        => 10,
	);
	$form['travel_reference']=array(
		'#type'          => 'textfield',
		'#title'         => t('Travel Reference'),
		'#default_value' => $kingdom_hall->travel_reference,
		'#weight'        => 11,
	);

	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'   => 'submit',
		'#value'  => t('Save'),
		'#weight' => 25,
		'#submit' => array('kingdom_hall_form_submit'),
	);
	
	if (!empty($kingdom_hall->khid)) {
		$form['buttons']['delete'] = array(
			'#type'   => 'submit',
			'#value'  => t('Delete'),
			'#access' => talk_access('delete', $kingdom_hall),
			'#weight' => 35,
			'#submit' => array('kingdom_hall_form_delete_submit'),
		);
	}
	$form['#validate'][] = 'kingdom_hall_form_validate';
	return $form;
}

function kingdom_hall_form_validate($form, &$form_state) {
	$kingdom_hall = $form_state['kingdom_hall'];
}

function kingdom_hall_form_submit($form, &$form_state) {
	$kingdom_hall = $form_state['kingdom_hall'];
	//$kingdom_hall->khid = $form_state['values']['khid'];
	$kingdom_hall->kingdom_hall_name = $form_state['values']['kingdom_hall_name'];
	$kingdom_hall->active = $form_state['values']['active'];
	$kingdom_hall->address = $form_state['values']['address'];
	$kingdom_hall->city = $form_state['values']['city'];
	$kingdom_hall->state = $form_state['values']['state'];
	$kingdom_hall->zipcode = $form_state['values']['zipcode'];
	$kingdom_hall->directions = $form_state['values']['directions'];
	$kingdom_hall->print_directions = $form_state['values']['print_directions'];
	$kingdom_hall->approx_travel_time = $form_state['values']['approx_travel_time'];
	$kingdom_hall->travel_reference = $form_state['values']['travel_reference'];
	
	kingdom_hall_save($kingdom_hall);
	drupal_set_message(t('Kingdom Hall saved'));
	$form_state['redirect'] = 'setup/congregations/kingdom_hall';
}

function kingdom_hall_form_delete_submit($form, &$form_state) {
	$destination = array();
	
	if(isset($_GET['destination'])){
		$destination=drupal_get_destination();
		unset($_GET['destination']);
	}
	
	$kingdom_hall = $form['#kingdom_hall'];
	$form_state['redirect'] = array('kingdom_hall/' . $kingdom_hall->khid . '/delete', array('query' => $destination));
}

function kingdom_hall_delete_confirm($form, &$form_state, $kingdom_hall) {
	$form['#kingdom_hall'] = $kingdom_hall;
	$form['khid'] = array(
		'#type' => 'value',
		'#value' => $kingdom_hall->khid,
	);

	return confirm_form(
		$form,
		t('Are you sure you want to delete %title', array('%title' => $kingdom_hall->kingdom_hall_name)),
		'kingdom_hall/' . $kingdom_hall->khid . '/edit',
		t('This action cannot be undone'),
		t('Delete'),
		t('Cancel')
	);
}

function kingdom_hall_delete_confirm_submit($form, &$form_state) {
	if($form_state['values']['confirm']){
		$kingdom_hall = kingdom_hall_load($form_state['values']['khid']);
		kingdom_hall_delete($form_state['values']['khid']);
		watchdog('kingdom_hall', '@type: deleted %title', array('@type'=>'kingdom_hall', '%title'=>$kingdom_hall->kingdom_hall_name));
		drupal_set_message(t('@type has been deleted', array('@type'=>'Kingdom Hall')));
	}
	$form_state['redirect'] = 'setup/congregations/kingdom_hall';
}

function kingdom_hall_delete($khid){
	return kingdom_hall_delete_multiple(array($khid));
}

function kingdom_hall_delete_multiple($khids){
	return entity_get_controller('kingdom_hall')->delete($khids);
}

/*
this is the add page
*/
function kingdom_hall_add_page() {
	$item = menu_get_item();
	$items = array();
	$links = system_admin_menu_block($item);

	foreach ($links as $link) {
		$items[]=l($link['title'], $link['href'], $link['localized_options']) . ':' . filter_xss_admin($link['description']);
	}
	return theme('item_list', array('items' => $items));
}

function kingdom_hall_add() {
	$type = 'kingdom_hall';
	
	$kingdom_hall = entity_get_controller('kingdom_hall')->create($type);
	drupal_set_title(t('Create @name', array('@name' => 'Kingdom Hall')), PASS_THROUGH);
	return drupal_get_form('kingdom_hall_form', $kingdom_hall);
}

function kingdom_hall_save($kingdom_hall) {
	return entity_get_controller('kingdom_hall')->save($kingdom_hall);
}