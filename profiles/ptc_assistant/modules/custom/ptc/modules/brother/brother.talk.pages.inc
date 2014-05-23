<?php

function brother_talks() {
  //Create a list of headers for the Html table
  $header = array(		
	  array('data' => 'Talk ID', 'field' => 'tid'),
	  array('data' => 'Title', 'field' => 'title'),
	);

  $query = db_select('brother_talk', 'bt')
			->extend('PagerDefault')
				->limit(variable_get('brother_talk_list_limit', 15))
			->extend('TableSort')
				->orderByHeader($header)
			->fields('bt', array('tid'));
      
  $query->join('talk', 't', 'bt.tid == t.tid')
      ->fields('t', 'title');

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

/**
 * TODO:  create a dropdown list for a brother's talks
 */