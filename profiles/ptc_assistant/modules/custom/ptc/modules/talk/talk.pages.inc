<?php

function talk_public_talks() {
  //Create a list of headers for the Html table
  $header = array(
	  array('data' => 'Outline Num', 'field' => 'outline_number'),
	  array('data' => 'Version', 'field' => 'outline_version'),
	  array('data' => 'Title', 'field' => 'title'),
	  array('data' => 'Lang', 'field' => 'language'),
	  array('data' => 'Last Given', 'field' => 'last_given'),
	);

  //Create the Sql query. This uses various parts of Drupal 7's new DBTNG database abstraction layer.
  $query = db_select('talk', 't')
			->condition('talk_type', 'public_talk', '=')
			->extend('PagerDefault')
				->limit(variable_get('talk_list_limit', 25))
			->extend('TableSort')
				->orderByHeader($header)
			->fields('t', array('tid', 'outline_number', 'outline_version', 'talk_type', 'language', 'title', 'last_given', 'prev_given'));

  $results = $query->execute();

  $rows = array();	
  foreach ($results as $talk) {
	  $rows[] = array(
			'data' => array(
			  $talk->outline_number,
				$talk->outline_version,
				l($talk->title, 'talk/'. $talk->tid .'/edit'),
				$talk->language,
				ptc_epoch2date($talk->last_given),
			)
		);
  }

	//Theme the html table
	$html = theme('table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No public talks created...',
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

function talk_co_themes() {
  //Create a list of headers for the Html table
  $header = array(
	  array('data' => 'Theme', 'field' => 'title'),
	  array('data' => 'Lang', 'field' => 'language'),
	  array('data' => 'Date Given', 'field' => 'last_given'),
	);

  //Create the Sql query. This uses various parts of Drupal 7's new DBTNG database abstraction layer.
  $query = db_select('talk', 't')
			->condition('talk_type', 'co_theme', '=')
			->extend('PagerDefault')
				->limit(variable_get('talk_list_limit', 25))
			->extend('TableSort')
				->orderByHeader($header)
			->fields('t', array('tid', 'outline_number', 'talk_type', 'language', 'title', 'last_given', 'prev_given'));

  $results = $query->execute();

  $rows = array();	
  foreach ($results as $talk) {
	  $rows[] = array(
			'data' => array(
				l($talk->title, 'talk/'. $talk->tid .'/edit'),
				$talk->language,
				ptc_epoch2date($talk->last_given),
			)
		);
  }

	//Theme the html table
	$html = theme('table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No Circuit Overseer themes created...',
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

function talk_do_themes() {
  //Create a list of headers for the Html table
  $header = array(
	  array('data' => 'Theme', 'field' => 'title'),
	  array('data' => 'Lang', 'field' => 'language'),
	  array('data' => 'Date Given', 'field' => 'last_given'),
	);

  //Create the Sql query. This uses various parts of Drupal 7's new DBTNG database abstraction layer.
  $query = db_select('talk', 't')
			->condition('talk_type', 'do_theme', '=')
			->extend('PagerDefault')
				->limit(variable_get('talk_list_limit', 25))
			->extend('TableSort')
				->orderByHeader($header)
			->fields('t', array('tid', 'outline_number', 'talk_type', 'language', 'title', 'last_given', 'prev_given'));

  $results = $query->execute();

  $rows = array();	
  foreach ($results as $talk) {
	  $rows[] = array(
			'data' => array(
				l($talk->title, 'talk/'. $talk->tid .'/edit'),
				$talk->language,
				ptc_epoch2date($talk->last_given),
			)
		);
  }

	//Theme the html table
	$html = theme('table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No District Overseer themes created...',
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

function talk_circuit_assemblies() {
  //Create a list of headers for the Html table
  $header = array(
	  array('data' => 'Theme', 'field' => 'title'),
	  array('data' => 'Lang', 'field' => 'language'),
	  array('data' => 'Date', 'field' => 'last_given'),
	);

  //Create the Sql query. This uses various parts of Drupal 7's new DBTNG database abstraction layer.
  $query = db_select('talk', 't')
			->condition('talk_type', 'circuit_assembly', '=')
			->extend('PagerDefault')
				->limit(variable_get('talk_list_limit', 25))
			->extend('TableSort')
				->orderByHeader($header)
			->fields('t', array('tid', 'outline_number', 'talk_type', 'language', 'title', 'last_given', 'prev_given'));

  $results = $query->execute();

  $rows = array();	
  foreach ($results as $talk) {
	  $rows[] = array(
			'data' => array(
				l($talk->title, 'talk/'. $talk->tid .'/edit'),
				$talk->language,
				ptc_epoch2date($talk->last_given),
			)
		);
  }

	//Theme the html table
	$html = theme('table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No Circuit Assembly themes created...',
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

function talk_special_assembly_days() {
  //Create a list of headers for the Html table
  $header = array(
	  array('data' => 'Theme', 'field' => 'title'),
	  array('data' => 'Lang', 'field' => 'language'),
	  array('data' => 'Date', 'field' => 'last_given'),
	);

  //Create the Sql query. This uses various parts of Drupal 7's new DBTNG database abstraction layer.
  $query = db_select('talk', 't')
			->condition('talk_type', 'special_assembly_day', '=')
			->extend('PagerDefault')
				->limit(variable_get('talk_list_limit', 25))
			->extend('TableSort')
				->orderByHeader($header)
			->fields('t', array('tid', 'outline_number', 'talk_type', 'language', 'title', 'last_given', 'prev_given'));

  $results = $query->execute();

  $rows = array();	
  foreach ($results as $talk) {
	  $rows[] = array(
			'data' => array(
				l($talk->title, 'talk/'. $talk->tid .'/edit'),
				$talk->language,
				ptc_epoch2date($talk->last_given),
			)
		);
  }

	//Theme the html table
	$html = theme('table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No Special Assembly Day themes created...',
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

function talk_district_conventions() {
  //Create a list of headers for the Html table
  $header = array(
	  array('data' => 'Theme', 'field' => 'title'),
	  array('data' => 'Lang', 'field' => 'language'),
	  array('data' => 'Date', 'field' => 'last_given'),
	);

  //Create the Sql query. This uses various parts of Drupal 7's new DBTNG database abstraction layer.
  $query = db_select('talk', 't')
			->condition('talk_type', 'district_convention', '=')
			->extend('PagerDefault')
				->limit(variable_get('talk_list_limit', 25))
			->extend('TableSort')
				->orderByHeader($header)
			->fields('t', array('tid', 'outline_number', 'talk_type', 'language', 'title', 'last_given', 'prev_given'));

  $results = $query->execute();

  $rows = array();	
  foreach ($results as $talk) {
	  $rows[] = array(
			'data' => array(
				l($talk->title, 'talk/'. $talk->tid .'/edit'),
				$talk->language,
				ptc_epoch2date($talk->last_given),
			)
		);
  }

	//Theme the html table
	$html = theme('table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No District Convention themes created...',
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

function talk_page_view($talk, $view_mode = 'full') {
	$talk->content = array();
	
	$talk_title = $talk->talk_type . " #" . $talk->outline_number . $talk->outline_version . " in " . $talk->language;

	$talk->content['title']=array(
		'#prefix' => '<div>',
		'#markup' => $talk_title,
		'#suffix' => '</div>',
		'#weight' => -8,
	);
	$talk->content['outline']=array(
		'#prefix' => '<div>',
		'#markup' => $talk->title,
		'#suffix' => '</div>',
		'#weight' => -7,
	);
	$talk->content['last_given']=array(
		'#prefix' => '<div>',
		'#markup' => ptc_epoch2date($talk->last_given),
		'#suffix' => '</div>',
		'#weight' => -6,
	);
	$talk->content['prev_given']=array(
		'#prefix' => '<div>',
		'#markup' => ptc_epoch2date($talk->prev_given),
		'#suffix' => '</div>',
		'#weight' => -5,
	);
	
	entity_prepare_view('talk', array($talk->tid => $talk));
	
	return $talk->content;
}

/*
this is the edit page
*/
function talk_page_edit($talk) {
	$types = talk_types();
	drupal_set_title(t('<em>Edit @type:<em>  @title', array('@type'=>$types[$talk->talk_type]->name, '@title'=>$talk->title)), PASS_THROUGH);
	return drupal_get_form($talk->talk_type.'_talk_form', $talk);
}

/*
this is the add page
*/
function talk_add_page() {
	$item = menu_get_item();
	$items = array();
	$links = system_admin_menu_block($item);

	foreach ($links as $link) {
		$items[]=l($link['title'], $link['href'], $link['localized_options']) . ':' . filter_xss_admin($link['description']);
	}
	return theme('item_list', array('items' => $items));
}

function talk_add($type) {
	$types = talk_types();
	$type = isset($type) ? str_replace('-', '_', $type) : NULL;
	
	if( empty($types[$type])) {
		return MENU_NOT_FOUND;
	}
	
	$talk = entity_get_controller('talk')->create($type);
	drupal_set_title(t('Create @name', array('@name' => $types[$type]->name)), PASS_THROUGH);
	return drupal_get_form($type . '_talk_form', $talk);
}

function talk_form($form, &$form_state, $talk) {
	$form['#id'] = 'talk-form';
	$form['#talk'] = $talk;
	$form_state['talk'] = $talk;
	
	if ($talk->talk_type == 'public_talk') {
		$form['outline_number']=array(
			'#type' => 'textfield',
			'#title' => t('Talk outline number'),
			'#default_value' => $talk->outline_number,
			'#weight' => 1,
			'#required' => TRUE,
		);
		$form['outline_version']=array(
			'#type'          => 'select',
			'#title'         => t('Talk outline version number'),
			'#options'       => get_outline_version_options(),
			'#default_value' => $talk->outline_version,
			'#weight'        => 2,
		);
	}
	else {		
		if (empty($talk->outline_number)) {
			$talk->outline_number = get_next_outline_number($talk->talk_type);
		}
		
		$form['outline_number']=array(
			'#type' => 'hidden',
			'#default_value' => $talk->outline_number,
		);
		$form['outline_version']=array(
			'#type'  => 'hidden',
			'#default_value' => '',
		);
	}
	
	$form['language']=array(
		'#type'          => 'select',
		'#title'         => t('Talk language'),
    '#options'       => get_talk_language_options(),
		'#default_value' => $talk->language,
		'#weight'        => 3,
	);
	$form['title']=array(
		'#type'          => 'textfield',
		'#title'         => t('Talk theme'),
		'#default_value' => $talk->title,
		'#weight'        => 4,
	);

	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'   => 'submit',
		'#value'  => t('Save'),
		'#weight' => 25,
		'#submit' => array('talk_form_submit'),
	);
	
	if (!empty($talk->tid)) {
		$form['buttons']['delete'] = array(
			'#type'   => 'submit',
			'#value'  => t('Delete'),
			'#access' => talk_access('delete', $talk),
			'#weight' => 35,
			'#submit' => array('talk_form_delete_submit'),
		);
	}
	$form['#validate'][] = 'talk_form_validate';
	return $form;
}

function get_talk_language_options() {
  return array(
    'DA' => t('Danish'),
    'EN' => t('English'),
    'ES' => t('Spanish'),
    'FR' => t('French'),
    'DE' => t('German'),
    'IT' => t('Italian'),
    'PL' => t('Polish'),
    'RO' => t('Romanian'),
    'RU' => t('Russian'),
  );
}

function get_outline_version_options() {
	return array(
	  ''  => t(''),
	  'A'  => t('A'),
	  'B'  => t('B'),
	  'C'  => t('C'),
	);
}

/*
 * Return a list of available public_talks to be displayed in a drop-down.
 */
function get_talk_outlines_options() {

}

function talk_form_validate($form, &$form_state) {
	$talk = $form_state['talk'];
}

function talk_form_submit($form, &$form_state) {
	$talk = $form_state['talk'];
	$talk->outline_number = $form_state['values']['outline_number'];
	$talk->outline_version = $form_state['values']['outline_version'];
	$talk->language = $form_state['values']['language'];
	$talk->title = $form_state['values']['title'];
	
	talk_save($talk);
	drupal_set_message(t('Talk saved'));
	$form_state['redirect'] = 'setup/' . $talk->talk_type;
}

function talk_save($talk) {
	return entity_get_controller('talk')->save($talk);
}

function talk_form_delete_submit($form, &$form_state) {
	$destination = array();
	
	if(isset($_GET['destination'])){
		$destination=drupal_get_destination();
		unset($_GET['destination']);
	}
	
	$talk = $form['#talk'];
	$form_state['redirect'] = array('talk/' . $talk->tid . '/delete', array('query' => $destination));
}
function talk_delete_confirm($form, &$form_state, $talk) {
	$form['#talk'] = $talk;
	$form['tid'] = array(
		'#type' => 'value',
		'#value' => $talk->tid,
	);

	return confirm_form(
		$form,
		t('Are you sure you want to delete %title', array('%title' => $talk->title)),
		'talk/' . $talk->tid,
		t('This action cannot be undone'),
		t('Delete'),
		t('Cancel')
	);
}

function talk_delete_confirm_submit($form, &$form_state) {
	if($form_state['values']['confirm']){
		$talk = talk_load($form_state['values']['tid']);
		talk_delete($form_state['values']['tid']);
		watchdog('talk', '@type: deleted %title', array('@type'=>$talk->talk_type, '%title'=>$talk->title));
		$types = talk_types();
		drupal_set_message(t('@type %title has been deleted', array('@type'=>$types[$talk->talk_type]->name, '%title'=>$talk->title)));
	}
	$form_state['redirect'] = 'setup/' . $talk->talk_type;
}

function talk_delete($tid){
	return talk_delete_multiple(array($tid));
}

function talk_delete_multiple($tids){
	return entity_get_controller('talk')->delete($tids);
}

// !!!!!!!!! Need to add brother who gave talk to report
function talk_last_given_by_date_report() {
  //Create a list of headers for the Html table
  $header = array(
	  array('data' => 'Outline Num', 'field' => 'outline_number'),
	  array('data' => 'Title', 'field' => 'title'),
	  array('data' => 'Last Given', 'field' => 'last_given'),
	);

  //Create the Sql query. This uses various parts of Drupal 7's new DBTNG database abstraction layer.
  $query = db_select('talk', 't')
			->condition('talk_type', 'public_talk', '=')
			->condition('language', variable_get('talk_default_language', 'EN'), '=')
			->extend('PagerDefault')
				->limit(variable_get('last_given_limit', 25))
			->extend('TableSort')
				->orderByHeader($header)
			->fields('t', array('outline_number', 'outline_version', 'title', 'last_given'));

  $results = $query->execute();
  $rows = array();	
	
  foreach ($results as $talk) {
	  $rows[] = array(
			'data' => array(
			  $talk->outline_number . $talk->outline_version,
				$talk->title,
				ptc_epoch2date($talk->last_given),
			)
		);
  }

	//Theme the html table
	$html = theme(
		'table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No public talks history...',
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

function talk_desired_talk_report($weeks = NULL) {
	// 604800 seconds in a week
	$weeks = variable_get('talk_desired_talks_weeks', 52);
	$target_date = time() - ($weeks * 604800);
	
	//Create a list of headers for the Html table
  $header = array(
	  array('data' => 'Outline Num', 'field' => 'outline_number'),
	  array('data' => 'Title', 'field' => 'title'),
	  array('data' => 'Last Given', 'field' => 'last_given'),
	);

  //Create the Sql query. This uses various parts of Drupal 7's new DBTNG database abstraction layer.
  $query = db_select('talk', 't')
			->condition('talk_type', 'public_talk', '=')
			->condition('language', variable_get('talk_default_language', 'EN'), '=')
			->condition('last_given', $target_date, '<=')
			->extend('PagerDefault')
				->limit(variable_get('talk_desired_talks_limit', 25))
			->fields('t', array('outline_number', 'outline_version', 'title', 'last_given'));

  $results = $query->execute();
  $rows = array();	
	
  foreach ($results as $talk) {
	  $rows[] = array(
			'data' => array(
			  $talk->outline_number . $talk->outline_version,
				$talk->title,
				ptc_epoch2date($talk->last_given),
			)
		);
  }

	//Theme the html table
	$html = theme(
		'table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No public talks history...',
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