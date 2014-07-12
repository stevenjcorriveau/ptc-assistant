<?php

function brother_brother_talk($bid) {
  //Create a list of headers for the Html table
  $header = array(		
	  array('data' => 'Talk ID', 'field' => 'tid'),
	  array('data' => 'Title', 'field' => 'title'),
	);

  $query = db_select('brother_talk', 'bt')
			->extend('PagerDefault')
				->limit(variable_get('brother_talk_list_limit', 15))
			->extend('TableSort')
				->orderByHeader($header);
  $query->condition('bt.bid', $bid, '=');
      
  $query->join('talk', 't', 'bt.tid = t.tid');
  $query->fields('t', array('tid', 'title'));

  $results = $query->execute();

  $rows = array();	
  foreach ($results as $talk) {
	  $rows[] = array(
			'data' => array(
				$talk->tid,
				$talk->title,
			)
		);
  }

	//Theme the html table
	$html = theme('table', 
		array(
			'header' => $header,
			'rows'=>$rows,
			'sticky' => TRUE,
			'empty' => 'No talks assigned...',
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

function brother_talk_form($form, &$form_state, $brother_talk = NULL) {
	module_load_include('inc', 'ptc', 'ptc.pages');
  // Use path to get the brother's ID
  $path = current_path();
  $parts = explode('/', $path);
  $bid = $parts[1];

	$form['#id'] = 'brother-talk-form';
	$form['#brother_talk'] = $brother_talk;
	$form_state['brother_talk'] = $brother_talk;
  
	$form['brother_talk_table'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('brother-talk-table')),
    '#weight' => 1,
	);
	$form['brother_talk_table']['brother_talk_list'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="brother-talk-list">',
    '#markup' => brother_brother_talk($bid),
    '#suffix' => '</div>',
    '#weight' => 1,
	);
  
	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
  
  $form['buttons']['submit'] = array(
		'#type'   => 'submit',
		'#value'  => t('Add Talk(s)'),
		'#weight' => 103,
		//'#submit' => array('brother_talk_form_add'),
    '#submit' => drupal_get_form('brother_talk_form_add'),
	);
		
  $form['buttons']['delete'] = array(
    '#type'   => 'submit',
    '#value'  => t('Delete talk(s)'),
    '#access' => talk_access('delete', $brother_talk),
    '#weight' => 105,
    '#submit' => array('brother_talk_form_delete'),
  );
  
	$form['#validate'][] = 'brother_talk_form_validate';
	return $form;
}

/*
 * No validation needed for this form.
 */
function brother_talk_form_validate($form, &$form_state) {
}

function brother_talk_form_add($form, &$form_state, $bid) {
  $form['#id'] = 'brother-talk-form-add';
	$form['#brother_talk'] = NULL;
	$form_state['brother_talk'] = NULL;
  
  $form['brother_talk_form'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('brother-talk-form')),
    '#weight' => 1,
  );
  
  
  
  
}

function brother_talk_form_add_submit($form, &$form_state) {
}

function brother_talk_form_add_validate($form, &$form_state) {
}

function brother_talk_form_delete($form, &$form_state) {
}

function brother_talk_form_delete_submit($form, &$form_state) {
}

function brother_talk_form_delete_validate() {
}

/**
 * TODO:  create a dropdown list for a brother's talks
 */