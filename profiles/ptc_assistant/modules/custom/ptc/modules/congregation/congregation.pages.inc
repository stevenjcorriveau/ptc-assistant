<?php

/**
 * TODO: Create dropdown for brother ids from brother record
 */

function congregation_congregations() {
  //Create a list of headers for the Html table
  $header = array(		
	  array('data' => 'Congregation ID', 'field' => 'cid'),
	  array('data' => 'Name', 'field' => 'congregation_name'),
	  array('data' => 'Kingdom Hall', 'field' => 'khid'),
	  array('data' => 'Phone', 'field' => 'phone'),
	  array('data' => 'PTC', 'field' => 'ptcid'),
	  array('data' => 'Last Trade', 'field' => 'last_trade_date'),
	  array('data' => 'Active', 'field' => 'active'),
	  array('data' => 'Circuit', 'field' => 'circuit'),
	);

  // Create the Sql query. This uses various parts of Drupal 7's new DBTNG 
	// database abstraction layer.
  $query = db_select('congregation', 'c')
			->extend('PagerDefault')
				->limit(variable_get('congregation_list_limit', 25))
			->extend('TableSort')
				->orderByHeader($header)
			->fields('c', array('cid', 'congregation_name', 'khid', 
			         'phone', 'ptcid', 'last_trade_date', 'active', 'circuit'));

  $results = $query->execute();

  $rows = array();	
  foreach ($results as $congregation) {
	  $rows[] = array(
			'data' => array(
				$congregation->cid,
				l($congregation->congregation_name, 'congregation/' . $congregation->cid . '/edit'),
				$congregation->khid, // should show name not id
			  $congregation->phone,
			  $congregation->ptcid, // should show name not id
			  ptc_epoch2date($congregation->last_trade_date),
			  ($congregation->active > 0) ? 'Yes' : 'No',
			  $congregation->circuit,
			)
		);
  }

	//Theme the html table
	$html = theme('table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No congregations created...',
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
function congregation_page_view($congregation, $view_mode = 'full') {
	$congregation->content = array();

	$congregation->content['cid']=array(
		'#prefix' => '<div>',
		'#markup' => $congregation->cid,
		'#suffix' => '</div>',
		'#weight' => 1,
	);
	$congregation->content['congregation_name']=array(
		'#prefix' => '<div>',
		'#markup' => $congregation->congregation_name,
		'#suffix' => '</div>',
		'#weight' => 2,
	);
	$congregation->content['khid']=array(
		'#prefix' => '<div>',
		'#markup' => $congregation->khid,
		'#suffix' => '</div>',
		'#weight' => 3,
	);
	$congregation->content['phone']=array(
		'#prefix' => '<div>',
		'#markup' => $congregation->phone,
		'#suffix' => '</div>',
		'#weight' => 4,
	);
	$congregation->content['ptcid']=array(
		'#prefix' => '<div>',
		'#markup' => $congregation->ptcid,
		'#suffix' => '</div>',
		'#weight' => 5,
	);
	$congregation->content['last_trade_date']=array(
		'#prefix' => '<div>',
		'#markup' => ptc_epoch2date($congregation->last_trade_date),
		'#suffix' => '</div>',
		'#weight' => 6,
	);
	$congregation->content['active']=array(
		'#prefix' => '<div>',
		'#markup' => ($congregation->active > 0) ? 'Yes' : 'No',
		'#suffix' => '</div>',
		'#weight' => 7,
	);
	$congregation->content['circuit']=array(
		'#prefix' => '<div>',
		'#markup' => $congregation->circuit,
		'#suffix' => '</div>',
		'#weight' => 8,
	);
	
	entity_prepare_view('congregation', array($congregation->cid => $congregation));
	
	return $congregation->content;
}

/*
 * This is the edit page
 */
function congregation_page_edit($congregation) {
	drupal_set_title(t('<em>Edit @type:<em>', array('@type'=>'Congregation')), PASS_THROUGH);
	return drupal_get_form('congregation_form', $congregation);
}

function congregation_form($form, &$form_state, $congregation) {
	module_load_include('inc', 'ptc', 'ptc.pages');
	
	$form['#id'] = 'congregation-form';
	$form['#congregation'] = $congregation;
	$form_state['congregation'] = $congregation;
	
	$form['cid']=array(
		'#type'          => 'hidden',
		'#weight'        => 1,
	);
	$form['congregation_name']=array(
		'#type'          => 'textfield',
		'#title'         => t('Congregation'),
		'#default_value' => $congregation->congregation_name,
		'#weight'        => 2,
	);
	$form['khid']=array(
		'#type'          => 'select',
		'#title'         => t('Kingdom Hall'),
		'#options'       => get_kingdom_hall_list(),
		'#default_value' => $congregation->khid,
		'#weight'        => 3,
	);
	$form['phone']=array(
		'#type'          => 'textfield',
		'#title'         => t('Phone'),
		'#default_value' => $congregation->phone,
		'#weight'        => 4,
	);
	$form['ptcid']=array(
		'#type'          => 'textfield',
		'#title'         => t('PTC'),
		'#default_value' => $congregation->ptcid, // Should show dropdown of names for brothers in the cong not ID
		'#weight'        => 5,
	);
	$form['last_trade_date']=array(
		'#type'          => 'textfield',
		'#title'         => t('Last Trade'),
		'#default_value' => !empty($congregation->last_trade_date) ? ptc_epoch2date($congregation->last_trade_date) : NULL,
		'#weight'        => 6,
	);
	$form['active']=array(
		'#type'          => 'checkbox',
		'#title'         => t('Active'),
		'#default_value' => $congregation->active,
		'#weight'        => 7,
	);
	$form['circuit']=array(
		'#type'          => 'textfield',
		'#title'         => t('Circuit'),
		'#default_value' => $congregation->circuit,
		'#weight'        => 8,
	);

	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'   => 'submit',
		'#value'  => t('Save'),
		'#weight' => 25,
		'#submit' => array('congregation_form_submit'),
	);
	
	if (!empty($congregation->cid)) {
		$form['buttons']['delete'] = array(
			'#type'   => 'submit',
			'#value'  => t('Delete'),
			'#access' => talk_access('delete', $congregation),
			'#weight' => 35,
			'#submit' => array('congregation_form_delete_submit'),
		);
	}
	$form['#validate'][] = 'congregation_form_validate';
	return $form;
}

function congregation_form_validate($form, &$form_state) {
	$congregation = $form_state['congregation'];
}

function congregation_form_submit($form, &$form_state) {
	$congregation = $form_state['congregation'];
	//$kingdom_hall->khid = $form_state['values']['khid'];
	$congregation->congregation_name = $form_state['values']['congregation_name'];
	$congregation->khid = $form_state['values']['khid'];
	$congregation->phone = $form_state['values']['phone'];
	$congregation->ptcid = $form_state['values']['ptcid'];
	$congregation->last_trade_date = ptc_date2epoch($form_state['values']['last_trade_date']);
	$congregation->active = $form_state['values']['active'];
	$congregation->circuit = $form_state['values']['circuit'];
	
	congregation_save($congregation);
	drupal_set_message(t('Congregation saved'));
	$form_state['redirect'] = 'setup/congregations/congregation';
}

function congregation_form_delete_submit($form, &$form_state) {
	$destination = array();
	
	if(isset($_GET['destination'])){
		$destination=drupal_get_destination();
		unset($_GET['destination']);
	}
	
	$congregation = $form['#congregation'];
	$form_state['redirect'] = array('congregation/' . $congregation->cid . '/delete', array('query' => $destination));
}

function congregation_delete_confirm($form, &$form_state, $congregation) {
	$form['#congregation'] = $congregation;
	$form['cid'] = array(
		'#type' => 'value',
		'#value' => $congregation->cid,
	);

	return confirm_form(
		$form,
		t('Are you sure you want to delete %title', array('%title' => $congregation->congregation_name)),
		'congregation/' . $congregation->cid . '/edit',
		t('This action cannot be undone'),
		t('Delete'),
		t('Cancel')
	);
}

function congregation_delete_confirm_submit($form, &$form_state) {
	if($form_state['values']['confirm']){
		$congregation = congregation_load($form_state['values']['cid']);
		congregation_delete($form_state['values']['cid']);
		watchdog('congregation', '@type: deleted %title', array('@type'=>'congregation', '%title'=>$congregation->congregation_name));
		drupal_set_message(t('@type has been deleted', array('@type'=>'Congregation')));
	}
	$form_state['redirect'] = 'setup/congregations/congregation';
}

function congregation_delete($cid){
	return congregation_delete_multiple(array($cid));
}

function congregation_delete_multiple($cids){
	return entity_get_controller('congregation')->delete($cids);
}

/*
this is the add page
*/
function congregation_add_page() {
	$item = menu_get_item();
	$items = array();
	$links = system_admin_menu_block($item);

	foreach ($links as $link) {
		$items[]=l($link['title'], $link['href'], $link['localized_options']) . ':' . filter_xss_admin($link['description']);
	}
	return theme('item_list', array('items' => $items));
}

function congregation_add() {
	$type = 'congregation';
	
	$congregation = entity_get_controller('congregation')->create($type);
	drupal_set_title(t('Create @name', array('@name' => 'Congregation')), PASS_THROUGH);
	return drupal_get_form('congregation_form', $congregation);
}

function congregation_save($congregation) {
	return entity_get_controller('congregation')->save($congregation);
}