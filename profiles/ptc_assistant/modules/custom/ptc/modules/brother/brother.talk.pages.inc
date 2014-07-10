<?php

function brother_brother_talk() {
  // Use path to get the brother's ID
  $path = current_path();
  $parts = explode('/', $path);
  $bid = $parts[1];

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
    '#markup' => brother_brother_talk(),
    '#suffix' => '</div>',
    '#weight' => 1,
	);
  
	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'   => 'submit',
		'#value'  => t('Add Talk'),
		'#weight' => 101,
		'#submit' => array('brother_talk_form_submit'),
	);
	
	if (!empty($brother->bid)) {  // move this to a button on each line
		$form['buttons']['delete'] = array(
			'#type'   => 'submit',
			'#value'  => t('Delete'),
			'#access' => talk_access('delete', $brother),
			'#weight' => 105,
			'#submit' => array('brother_talk_form_delete_submit'),
		);
	}
  
	$form['#validate'][] = 'brother_talk_form_validate';
	return $form;
}

/**
 * TODO:  create a dropdown list for a brother's talks
 */