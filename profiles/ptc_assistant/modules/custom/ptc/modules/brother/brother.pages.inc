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
  
	$form['brother_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Personal Info'),
    '#attributes' => array('class' => array('brother-info')),
    '#weight' => 1,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
	);
  $form['brother_info']['container1'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('brother-name-line')),
    '#weight' => 2,
  );  
	$form['brother_info']['container1']['brother_fname'] = array(
    '#type' => 'textfield',
    '#title' => t('First: '),
    '#default_value' => $brother->brother_fname,
    '#size' => 25,
    '#maxlength' => 25,
    '#attributes' => array('class' => array('brother-fname')),
    '#required' => TRUE,
		'#weight' => 3,
	);
	$form['brother_info']['container1']['brother_mname'] = array(
    '#type' => 'textfield',
    '#title' => t('Middle: '),
    '#default_value' => $brother->brother_mname,
    '#size' => 25,
    '#maxlength' => 25,
    '#attributes' => array('class' => array('brother-mname')),
		'#weight' => 4,
	);
	$form['brother_info']['container1']['brother_lname'] = array(
    '#type' => 'textfield',
    '#title' => t('Last: '),
    '#default_value' => $brother->brother_lname,
    '#size' => 30,
    '#maxlength' => 30,
    '#attributes' => array('class' => array('brother-lname')),
    '#required' => TRUE,
		'#weight' => 5,
	);
  
	$form['brother_info']['street'] = array(
    '#type' => 'textfield',
    '#title' => t('Street: '),
    '#default_value' => $brother->address,
    '#size' => 50,
    '#maxlength' => 50,
    '#attributes' => array('class' => array('brother-info-street')),
		'#weight' => 11,
	);
  $form['brother_info']['container2'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('brother-info-line')),
    '#weight' => 12,
  );
	$form['brother_info']['container2']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City: '),
    '#default_value' => $brother->city,
    '#size' => 50,
    '#maxlength' => 50,
    '#attributes' => array('class' => array('brother-info-city')),
		'#weight' => 13,
	);
	$form['brother_info']['container2']['state'] = array(
		'#type' => 'select',
		'#title' => t('State: '),
		'#options' => get_state_options(),
		'#default_value' => $brother->state,
		'#weight' => 14,
	);
	$form['brother_info']['container2']['zipcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Zipcode: '),
    '#default_value' => $brother->zipcode,
    '#size' => 10,
    '#maxlength' => 10,
    '#attributes' => array('class' => array('brother-info-zipcode')),
		'#weight' => 15,
	);
	$form['brother_info']['last_update'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="brother-info-last-update">',
    '#markup' => !empty($brother->br_last_update) ? 'Last updated: ' . ptc_epoch2date($brother->br_last_update) : 'No last update date available',
    '#suffix' => '</div>',
		'#weight' => 16,
  );
  
 
	$form['cong_resp'] = array(
    '#type' => 'fieldset',
    '#title' => t('Congregation Responsibilities'),
    '#weight' => 20,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
	);
	$form['cong_resp']['cong'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('cong-resp-cong')),
    '#weight' => 21,
  );
	$form['cong_resp']['cong']['cid'] = array(
		'#type' => 'select',
		'#title' => t('Congregation'),
		'#options' => get_congregation_list(),
		'#default_value' => $brother->cid,
    '#attributes' => array('class' => array('cong-resp-cong-congregation')),
		'#weight' => 22,
	);
  $form['cong_resp']['elder_ms'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('cong-resp-elder-ms')),
    '#weight' => 23,
  );
	$form['cong_resp']['elder_ms']['elder'] = array(
		'#type' => 'checkbox',
		'#title' => t('Elder'),
		'#default_value' => ($brother->elder_ms == 2) ? 1 : 0,
    '#attributes' => array('class' => array('elder-ms-elder')),
		'#weight' => 24,
	);
	$form['cong_resp']['elder_ms']['MS'] = array(
		'#type' => 'checkbox',
		'#title' => t('MS'),
		'#default_value' => ($brother->elder_ms == 1) ? 1 : 0,
    '#attributes' => array('class' => array('elder-ms-ms')),
		'#weight' => 25,
	);
  
  $form['cong_resp']['outgoing'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('cong-resp-outgoing')),
    '#weight' => 26,
  );
	$form['cong_resp']['outgoing']['out_elder'] = array(
		'#type' => 'checkbox',
		'#title' => t('Outgoing speaker'),
		'#default_value' => $brother->outgoing_sp,
    '#attributes' => array('class' => array('cong-resp-outgoing-sp')),
		'#weight' => 27,
	);
	$form['cong_resp']['outgoing']['out_ms'] = array(
		'#type' => 'checkbox',
		'#title' => t('Outgoing servant'),
		'#default_value' => $brother->outgoing_ms,
    '#attributes' => array('class' => array('cong-resp-outgoing-ms')),
		'#weight' => 28,
	);
  
  $form['cong_resp']['col_1'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('cong-resp-col-1')),
    '#weight' => 30,
  );
	$form['cong_resp']['col_1']['cobe'] = array(
		'#type' => 'checkbox',
		'#title' => t('COBE'),
		'#default_value' => $brother->cobe,
		'#weight' => 31,
	);
	$form['cong_resp']['col_1']['sec'] = array(
		'#type' => 'checkbox',
		'#title' => t('Sec'),
		'#default_value' => $brother->sec,
		'#weight' => 32,
	);
	$form['cong_resp']['col_1']['so'] = array(
		'#type' => 'checkbox',
		'#title' => t('SO'),
		'#default_value' => $brother->so,
		'#weight' => 33,
	);
  
  $form['cong_resp']['col_2'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('cong-resp-col-2')),
    '#weight' => 40,
  );
	$form['cong_resp']['col_2']['ptc'] = array(
		'#type' => 'checkbox',
		'#title' => t('PTC'),
		'#default_value' => $brother->ptc,
		'#weight' => 41,
	);
	$form['cong_resp']['col_2']['rbc'] = array(
		'#type' => 'checkbox',
		'#title' => t('RBC'),
		'#default_value' => $brother->rbc,
		'#weight' => 42,
	);
  
  $form['cong_resp']['col_3'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('cong-resp-col-3')),
    '#weight' => 50,
  );
	$form['cong_resp']['col_3']['wt_conductor'] = array(
		'#type' => 'checkbox',
		'#title' => t('WT Conductor'),
		'#default_value' => $brother->wt_conductor,
		'#weight' => 51,
	);
	$form['cong_resp']['col_3']['chairman'] = array(
		'#type' => 'checkbox',
		'#title' => t('Chairman'),
		'#default_value' => $brother->chairman,
		'#weight' => 52,
	);
	$form['cong_resp']['col_3']['wt_reader'] = array(
		'#type' => 'checkbox',
		'#title' => t('WT Reader'),
		'#default_value' => $brother->wt_reader,
		'#weight' => 53,
	);
  
  $form['cong_resp']['col_4'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('cong-resp-col-4')),
    '#weight' => 60,
  );
  
 $form['availibility'] = array(
    '#type' => 'fieldset',
    '#title' => t('Availibility'),
    '#weight' => 71,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
	);
  $form['availibility']['col_1'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('availibility-col-1')),
    '#weight' => 72,
  );
	$form['availibility']['col_1']['active'] = array(
		'#type'          => 'checkbox',
		'#title'         => t('Active'),
		'#default_value' => $brother->active,
		'#weight'        => 73,
	);
	$form['availibility']['col_1']['available'] = array(
		'#type'          => 'checkbox',
		'#title'         => t('Available'),
		'#default_value' => $brother->active,
		'#weight'        => 74,
	);
  $form['availibility']['col_2'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('availibility-col-2')),
    '#weight' => 75,
  );
	$form['availibility']['col_2']['no_am_talks'] = array(
		'#type' => 'checkbox',
		'#title' => t('No morning talks'),
		'#default_value' => $brother->no_am_talks,
    '#attributes' => array('class' => array('availibility-no-am')),
		'#weight' => 76,
	);
	$form['availibility']['col_2']['no_noon_talks'] = array(
		'#type' => 'checkbox',
		'#title' => t('No midday talks'),
		'#default_value' => $brother->no_noon_talks,
    '#attributes' => array('class' => array('availibility-no-noon')),
		'#weight' => 77,
	);
	$form['availibility']['col_2']['no_pm_talks'] = array(
		'#type' => 'checkbox',
		'#title' => t('No evening talks'),
		'#default_value' => $brother->no_pm_talks,
    '#attributes' => array('class' => array('availibility-no-pm')),
		'#weight' => 78,
	);
  $form['availibility']['col_3'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('availibility-col-3')),
    '#weight' => 79,
  );
	$form['availibility']['col_3']['avail_notes'] = array(
		'#type' => 'textarea',
		'#title' => t('Availability notes'),
		'#default_value' => $brother->avail_comment,
    '#attributes' => array('class' => array('availibility-notes')),
		'#weight' => 80,
	);
  
 $form['comments'] = array(
    '#type' => 'fieldset',
    '#title' => t('Other notes'),
    '#weight' => 90,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
	);
  $form['comments']['col_1'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('comments-col-1')),
    '#weight' => 91,
  );
	$form['comments']['col_1']['rating'] = array(
		'#type' => 'textarea',
		'#title' => t('Brother rating'),
		'#default_value' => $brother->rating,
    '#attributes' => array('class' => array('comments-rating')),
		'#weight' => 92,
	);
  $form['comments']['col_2'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('comments-col-2')),
    '#weight' => 93,
  );
	$form['comments']['col_2']['notes'] = array(
		'#type' => 'textarea',
		'#title' => t('Other notes'),
		'#default_value' => $brother->notes,
    '#attributes' => array('class' => array('comments-notes')),
		'#weight' => 94,
	);

	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'   => 'submit',
		'#value'  => t('Save'),
		'#weight' => 101,
		'#submit' => array('brother_form_submit'),
	);
	
	if (!empty($brother->bid)) {
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
  
  if ($form_state['input']['elder'] == 1 &&
      $form_state['input']['MS'] == 1) {
    form_error($form['cong_resp']['elder_ms']['MS'], 'Cannot select both elder AND MS');   
  }
  
  if ($form_state['input']['elder'] == 1 &&
      $form_state['input']['out_ms'] == 1) {
    form_error($form['cong_resp']['outgoing']['out_ms'], 'An elder cannot be an outgoing servant');   
  }
  
  if ($form_state['input']['MS'] == 1 &&
      $form_state['input']['out_elder'] == 1) {
    form_error($form['cong_resp']['outgoing']['out_elder'], 'An servant cannot be an outgoing speaker (this is used for elders)');   
  }
  
  if (($form_state['input']['cobe'] == 1 ||
       $form_state['input']['sec'] == 1 ||
       $form_state['input']['so'] == 1) &&
      $form_state['input']['MS'] == 1) {
    form_error($form['cong_resp']['elder_ms']['MS'], 'You cannot assign COBE, SEC, or SO to a servant');   
  }
}

function brother_form_submit($form, &$form_state) {
	$brother = $form_state['brother'];
  $brother->cid = $form_state['values']['cid'];
	$brother->brother_fname = $form_state['values']['brother_fname'];
	$brother->brother_mname = $form_state['values']['brother_mname'];
	$brother->brother_lname = $form_state['values']['brother_lname'];
	$brother->street = $form_state['values']['street'];
	$brother->city = $form_state['values']['city'];
	$brother->state = $form_state['values']['state'];
	$brother->zipcode = $form_state['values']['zipcode'];
	$brother->cobe = $form_state['values']['cobe'];
	$brother->sec = $form_state['values']['sec'];
	$brother->so = $form_state['values']['so'];
	$brother->ptc = $form_state['values']['ptc'];
	$brother->rbc = $form_state['values']['rbc'];
	$brother->wt_conductor = $form_state['values']['wt_conductor'];
	$brother->chairman = $form_state['values']['chairman'];
	$brother->wt_reader = $form_state['values']['wt_reader'];
	$brother->active = $form_state['values']['active'];
	$brother->available = $form_state['values']['available'];
	$brother->no_am_talks = $form_state['values']['no_am_talks'];
	$brother->no_noon_talks = $form_state['values']['no_noon_talks'];
	$brother->no_pm_talks = $form_state['values']['no_pm_talks'];
	$brother->avail_comment = $form_state['values']['avail_notes'];
	$brother->rating = $form_state['values']['rating'];
	$brother->notes = $form_state['values']['notes'];
	$brother->outgoing_sp = $form_state['values']['out_elder'];
	$brother->outgoing_ms = $form_state['values']['out_ms'];
  
  if ($form_state['values']['elder'] == 1) {
    $brother->elder_ms = 2;
  }
  else if ($form_state['values']['MS'] == 1) {
    $brother->elder_ms = 1;
  }
  else {
    $brother->elder_ms = 0;
  }
  
	$brother->br_last_update = time();
	
	brother_save($brother);
	drupal_set_message(t('Brother saved'));
	$form_state['redirect'] = 'setup/brothers/brother';
}

function brother_form_delete_submit($form, &$form_state) {
	$destination = array();
	
	if(isset($_GET['destination'])){
		$destination=drupal_get_destination();
		unset($_GET['destination']);
	}
	
	$brother = $form['#brother'];
	$form_state['redirect'] = array('brother/' . $brother->bid . '/delete', array('query' => $destination));
}

function brother_delete_confirm($form, &$form_state, $brother) {
	$form['#brother'] = $brother;
	$form['bid'] = array(
		'#type' => 'value',
		'#value' => $brother->bid,
	);

	return confirm_form(
		$form,
		t('Are you sure you want to delete %title', array('%title' => $brother->brother_fname . ' ' . $brother->brother_mname . ' ' . $brother->brother_lname)),
		'brother/' . $brother->bid . '/edit',
		t('This action cannot be undone'),
		t('Delete'),
		t('Cancel')
	);
}

function brother_delete_confirm_submit($form, &$form_state) {
	if($form_state['values']['confirm']){
		$brother = brother_load($form_state['values']['bid']);
		brother_delete($form_state['values']['bid']);
		watchdog('brother', '@type: deleted bid = %title', array('@type'=>'brother', '%title'=>$brother->bid));
		drupal_set_message(t('@type has been deleted', array('@type'=>'Brother')));
	}
	$form_state['redirect'] = 'setup/brothers/brother';
}

function brother_delete($bid){
	return brother_delete_multiple(array($bid));
}

function brother_delete_multiple($bids){
	return entity_get_controller('brother')->delete($bids);
}

function brother_add() {
	$type = 'brother';
	
	$brother = entity_get_controller('brother')->create($type);
	drupal_set_title(t('Create @name', array('@name' => 'Brother')), PASS_THROUGH);
	return drupal_get_form('brother_form', $brother);
}

function brother_save($brother) {
	return entity_get_controller('brother')->save($brother);
}