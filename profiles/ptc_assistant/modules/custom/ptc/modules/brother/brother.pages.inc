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
  
	$form['brother_name']=array(
    '#type' => 'fieldset',
    '#title' => t('Name'),
    '#weight' => 1,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
	);
  
	$form['brother_name']['brother_fname']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->brother_fname,
		'#suffix' => '</div>',
		'#weight' => 4,
	);
	$form['brother_name']['brother_mname']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->brother_mname,
		'#suffix' => '</div>',
		'#weight' => 5,
	);
	$form['brother_name']['brother_lname']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->brother_lname,
		'#suffix' => '</div>',
		'#weight' => 6,
	);
	
	$form['cid']=array(
		'#type'          => 'select',
		'#title'         => t('Congregation'),
		'#options'       => get_congregation_list(),
		'#default_value' => $brother->cid,
		'#weight'        => 7,
	);
  
	$form['address']=array(
    '#type' => 'fieldset',
    '#title' => t('Address'),
    '#weight' => 8,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
	);
	$form['address']['street']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->address,
		'#suffix' => '</div>',
		'#weight' => 9,
	);
  $form['address']['container']=array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'address-line',
      ),
    ),
    '#weight' => 10,
  );
	$form['address']['container']['city']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->city,
		'#suffix' => '</div>',
		'#weight' => 11,
	);
	$form['address']['container']['state']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->state,
		'#suffix' => '</div>',
		'#weight' => 12,
	);
	$form['address']['container']['zipcode']=array(
		'#prefix' => '<div>',
		'#markup' => $brother->zipcode,
		'#suffix' => '</div>',
		'#weight' => 13,
	);
  
 
	$form['cong_resp']=array(
    '#type' => 'fieldset',
    '#title' => t('Congregation Responsibilities'),
    '#weight' => 14,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
	);
  $form['cong_resp']['box-left']=array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'cong-resp-box-left',
      ),
    ),
    '#weight' => 15,
  );
	$form['cong_resp']['box-left']['elder_ms']=array(
		'#type'          => 'fieldset',
		'#title'         => t('Elder/MS'),
		'#weight'        => 16,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
	);
	$form['cong_resp']['box-left']['elder_ms']['elder']=array(
		'#type'          => 'checkbox',
		'#title'         => t('Elder'),
		'#default_value' => ($brother->elder_ms == 2) ? 1 : 0,
		'#weight'        => 17,
	);
	$form['cong_resp']['box-left']['elder_ms']['MS']=array(
		'#type'          => 'checkbox',
		'#title'         => t('MS'),
		'#default_value' => ($brother->elder_ms == 1) ? 1 : 0,
		'#weight'        => 18,
	);
	$form['cong_resp']['box-left']['wt_conductor']=array(
		'#type'          => 'checkbox',
		'#title'         => t('WT Conductor'),
		'#default_value' => $brother->wt_conductor,
		'#weight'        => 19,
	);
	$form['cong_resp']['box-left']['chairman']=array(
		'#type'          => 'checkbox',
		'#title'         => t('Chairman'),
		'#default_value' => $brother->chairman,
		'#weight'        => 20,
	);
	$form['cong_resp']['box-left']['wt_reader']=array(
		'#type'          => 'checkbox',
		'#title'         => t('WT Reader'),
		'#default_value' => $brother->wt_reader,
		'#weight'        => 21,
	);
  $form['cong_resp']['box_right']=array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'cong-resp-box-right',
      ),
    ),
    '#weight' => 22,
  );
	$form['cong_resp']['box_right']['ptc']=array(
		'#type'          => 'checkbox',
		'#title'         => t('PTC'),
		'#default_value' => $brother->ptc,
		'#weight'        => 23,
	);
	$form['cong_resp']['box_right']['cobe']=array(
		'#type'          => 'checkbox',
		'#title'         => t('COBE'),
		'#default_value' => $brother->cobe,
		'#weight'        => 24,
	);
	$form['cong_resp']['box_right']['sec']=array(
		'#type'          => 'checkbox',
		'#title'         => t('Sec'),
		'#default_value' => $brother->sec,
		'#weight'        => 25,
	);
	$form['cong_resp']['box_right']['so']=array(
		'#type'          => 'checkbox',
		'#title'         => t('SO'),
		'#default_value' => $brother->so,
		'#weight'        => 26,
	);
	$form['cong_resp']['box_right']['rbc']=array(
		'#type'          => 'checkbox',
		'#title'         => t('RBC'),
		'#default_value' => $brother->rbc,
		'#weight'        => 27,
	);
  
  
  
  
  
  
	$form['active']=array(
		'#type'          => 'checkbox',
		'#title'         => t('Active'),
		'#default_value' => $brother->active,
		'#weight'        => 75,
	);

	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'   => 'submit',
		'#value'  => t('Save'),
		'#weight' => 101,
		'#submit' => array('brother_form_submit'),
	);
	
	if (!empty($brother->cid)) {
		$form['buttons']['delete'] = array(
			'#type'   => 'submit',
			'#value'  => t('Delete'),
			'#access' => talk_access('delete', $brother),
			'#weight' => 105,
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