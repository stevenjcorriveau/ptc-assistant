<?php

/**
 * TODO: Create dropdown for brother ids from brother record
 */

function brother_brothers() {
  //Create a list of headers for the Html table
  $header = array(
	  array('data' => 'Name', 'field' => 'brother_lname'),
	  array('data' => 'Congregation', 'field' => 'congregation_name'),
	  array('data' => 'COBE', 'field' => 'cobe'),
	  array('data' => 'Sec', 'field' => 'sec'),
	);

  $query = db_select('brother', 'b')
			->extend('PagerDefault')
				->limit(variable_get('brother_list_limit', 25))
			->extend('TableSort')
				->orderByHeader($header)
			->fields('b', array('bid', 'brother_lname', 'brother_fname', 
			         'brother_mname', 'elder_ms', 'cobe', 'sec'));
               
  $query->join('congregation', 'c', 'b.cid = c.cid');
  $query->fields('c', array('congregation_name'));

  $results = $query->execute();

  $rows = array();	
  foreach ($results as $brother) {
	  $rows[] = array(
			'data' => array(
				l($brother->brother_lname . ", " . $brother->brother_fname . " " . $brother->brother_mname, 'brother/' . $brother->bid . '/edit'),
				$brother->congregation_name,
			  //$brother->elder_ms,
			  ($brother->cobe > 0) ? 'Yes' : 'No',
			  ($brother->sec > 0) ? 'Yes' : 'No',
			)
		);
  }

	//Theme the html table
	$html = theme('table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No brothers created...',
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
function brother_page_view($brother, $view_mode = 'full') {
	$brother->content = array();
  
	$brother->content['cid']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->cid, //change to congregation name
		'#suffix' => '</div>',
		'#weight' => 1,
	);
	$brother->content['brother_name']=array(
    '#type' => 'fieldset',
    '#title' => t('Name'),
    '#weight' => 2,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
	);
	$brother->content['brother_name']['brother_fname']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->brother_fname,
		'#suffix' => '</div>',
		'#weight' => 3,
	);
	$brother->content['brother_name']['brother_mname']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->brother_mname,
		'#suffix' => '</div>',
		'#weight' => 4,
	);
	$brother->content['brother_name']['brother_lname']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->brother_lname,
		'#suffix' => '</div>',
		'#weight' => 5,
	);
	$brother->content['address']=array(
    '#type' => 'fieldset',
    '#title' => t('Address'),
    '#weight' => 6,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
	);
	$brother->content['address']['street']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->address,
		'#suffix' => '</div>',
		'#weight' => 7,
	);
	$brother->content['address']['city']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->city,
		'#suffix' => '</div>',
		'#weight' => 8,
	);
	$brother->content['address']['state']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->state,
		'#suffix' => '</div>',
		'#weight' => 9,
	);
	$brother->content['address']['zipcode']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->zipcode,
		'#suffix' => '</div>',
		'#weight' => 10,
	);
	$brother->content['rating']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->rating,
		'#markup' => $brother->notes,
		'#suffix' => '</div>',
		'#weight' => 1,
	);
	$brother->content['elder_ms']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->elder_ms,
		'#suffix' => '</div>',
		'#weight' => 5,
	);
	$brother->content['ptc']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->outgoing_sp,
		'#markup' => $brother->outgoing_ms,
		'#markup' => $brother->ptc,
		'#markup' => $brother->cobe,
		'#markup' => $brother->sec,
		'#markup' => $brother->so,
		'#markup' => $brother->wt_conductor,
		'#markup' => $brother->chairman,
		'#markup' => $brother->wt_reader,
		'#markup' => $brother->rbc,
		'#suffix' => '</div>',
		'#weight' => 6,
	);
	$brother->content['available']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->contact_notes,
		'#markup' => $brother->available,
		'#markup' => $brother->avail_comment,
		'#markup' => $brother->no_am_talks,
		'#markup' => $brother->no_noon_talks,
		'#markup' => $brother->no_pm_talks,
		'#markup' => $brother->available,
		'#suffix' => '</div>',
		'#weight' => 8,
	);
	$brother->content['active']=array(
		'#prefix' => '<div>',
		'#markup' => ($brother->active > 0) ? 'Yes' : 'No',
		'#suffix' => '</div>',
		'#weight' => 7,
	);
	$brother->content['br_last_update']=array(
		'#prefix' => '<div>',
		'#markup' => ptc_epoch2date($brother->br_last_update),
		'#suffix' => '</div>',
		'#weight' => 7,
	);
	
	entity_prepare_view('brother', array($brother->btid => $brother));
	
	return $brother->content;
}

/*
 * This is the edit page
 */
function brother_page_edit($brother) {
	drupal_set_title(t('<em>Edit @type:<em>', array('@type'=>'Brother')), PASS_THROUGH);
	return drupal_get_form('brother_form', $brother);
}

function brother_form($form, &$form_state, $brother) {
	module_load_include('inc', 'ptc', 'ptc.pages');
	
	$form['#id'] = 'brother-form';
	$form['#brother'] = $brother;
	$form_state['brother'] = $brother;
	
	$form['cid']=array(
		'#type'          => 'hidden',
		'#weight'        => 1,
	);
	$form['brother_name']=array(
		'#type'          => 'textfield',
		'#title'         => t('Congregation'),
		'#default_value' => $brother->brother_name,
		'#weight'        => 2,
	);
	$form['khid']=array(
		'#type'          => 'select',
		'#title'         => t('Kingdom Hall'),
		'#options'       => get_kingdom_hall_list(),
		'#default_value' => $brother->khid,
		'#weight'        => 3,
	);
	$form['phone']=array(
		'#type'          => 'textfield',
		'#title'         => t('Phone'),
		'#default_value' => $brother->phone,
		'#weight'        => 4,
	);
	$form['ptcid']=array(
		'#type'          => 'textfield',
		'#title'         => t('PTC'),
		'#default_value' => $brother->ptcid, // Should show dropdown of names for brothers in the cong not ID
		'#weight'        => 5,
	);
	$form['last_trade_date']=array(
		'#type'          => 'textfield',
		'#title'         => t('Last Trade'),
		'#default_value' => !empty($brother->last_trade_date) ? ptc_epoch2date($brother->last_trade_date) : NULL,
		'#weight'        => 6,
	);
	$form['active']=array(
		'#type'          => 'checkbox',
		'#title'         => t('Active'),
		'#default_value' => $brother->active,
		'#weight'        => 7,
	);
	$form['circuit']=array(
		'#type'          => 'textfield',
		'#title'         => t('Circuit'),
		'#default_value' => $brother->circuit,
		'#weight'        => 8,
	);

	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'   => 'submit',
		'#value'  => t('Save'),
		'#weight' => 25,
		'#submit' => array('brother_form_submit'),
	);
	
	if (!empty($brother->cid)) {
		$form['buttons']['delete'] = array(
			'#type'   => 'submit',
			'#value'  => t('Delete'),
			'#access' => talk_access('delete', $brother),
			'#weight' => 35,
			'#submit' => array('brother_form_delete_submit'),
		);
	}
	$form['#validate'][] = 'brother_form_validate';
	return $form;
}

function brother_form_validate($form, &$form_state) {
	$brother = $form_state['brother'];
}

function brother_form_submit($form, &$form_state) {
	$brother = $form_state['brother'];
	//$kingdom_hall->khid = $form_state['values']['khid'];
	$brother->brother_name = $form_state['values']['brother_name'];
	$brother->khid = $form_state['values']['khid'];
	$brother->phone = $form_state['values']['phone'];
	$brother->ptcid = $form_state['values']['ptcid'];
	$brother->last_trade_date = ptc_date2epoch($form_state['values']['last_trade_date']);
	$brother->active = $form_state['values']['active'];
	$brother->circuit = $form_state['values']['circuit'];
	
	brother_save($brother);
	drupal_set_message(t('Congregation saved'));
	$form_state['redirect'] = 'setup/brothers/brother';
}

function brother_form_delete_submit($form, &$form_state) {
	$destination = array();
	
	if(isset($_GET['destination'])){
		$destination=drupal_get_destination();
		unset($_GET['destination']);
	}
	
	$brother = $form['#brother'];
	$form_state['redirect'] = array('brother/' . $brother->cid . '/delete', array('query' => $destination));
}

function brother_delete_confirm($form, &$form_state, $brother) {
	$form['#brother'] = $brother;
	$form['cid'] = array(
		'#type' => 'value',
		'#value' => $brother->cid,
	);

	return confirm_form(
		$form,
		t('Are you sure you want to delete %title', array('%title' => $brother->brother_name)),
		'brother/' . $brother->cid . '/edit',
		t('This action cannot be undone'),
		t('Delete'),
		t('Cancel')
	);
}

function brother_delete_confirm_submit($form, &$form_state) {
	if($form_state['values']['confirm']){
		$brother = brother_load($form_state['values']['cid']);
		brother_delete($form_state['values']['cid']);
		watchdog('brother', '@type: deleted %title', array('@type'=>'brother', '%title'=>$brother->brother_name));
		drupal_set_message(t('@type has been deleted', array('@type'=>'Congregation')));
	}
	$form_state['redirect'] = 'setup/brothers/brother';
}

function brother_delete($cid){
	return brother_delete_multiple(array($cid));
}

function brother_delete_multiple($cids){
	return entity_get_controller('brother')->delete($cids);
}

/*
this is the add page
*/
function brother_add_page() {
	$item = menu_get_item();
	$items = array();
	$links = system_admin_menu_block($item);

	foreach ($links as $link) {
		$items[]=l($link['title'], $link['href'], $link['localized_options']) . ':' . filter_xss_admin($link['description']);
	}
	return theme('item_list', array('items' => $items));
}

function brother_add() {
	$type = 'brother';
	
	$brother = entity_get_controller('brother')->create($type);
	drupal_set_title(t('Create @name', array('@name' => 'Congregation')), PASS_THROUGH);
	return drupal_get_form('brother_form', $brother);
}

function brother_save($brother) {
	return entity_get_controller('brother')->save($brother);
}