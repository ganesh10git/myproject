<?php
/**
 * 
 * Solr search block page
 * 
 */
/**
 * Function to display where can i shop form.
 *
 * @return array
 *   An array of form fields
 */
function im_search_block_form() {
  $form['f1'] = array(
    '#type' => 'select',
    '#title' => t('Categories'),
    '#options' => _im_search_get_entity_type(),
    '#attributes' => array('class' => array('categories')),
	'#default_value' => (!empty($_GET['f1'])) ? $_GET['f1'] : '',
  );
  $form['f2'] = array(
    '#type' => 'select',
    '#title' => t('Types of media'),
    '#options' => array(t('All'), "contents" => t('Contents'), "files" => t('Files')),
    '#attributes' => array('class' => array('type-of-media')),
	'#default_value' => (!empty($_GET['f2'])) ? $_GET['f2'] : '',
  );
  $form['f3'] = array(
    '#type' => 'select',
    '#title' => t('Published'),
    '#options' => array(t('No selection'), "week" => t('One week'), "month" => t('One month'), "quarter" => t('A quarter'), "semester" => t('One semester'), "year" => t('One year')),
    '#attributes' => array('class' => array('published')),
	'#default_value' => (!empty($_GET['f3'])) ? $_GET['f3'] : '',
  );
  $fromdate = "";
  if(!empty($_GET['f4']['date'])){
  	$fromdate = trim($_GET['f4']['date']);
  	$fromdate = explode("/", $fromdate);
  }
  $form['f4'] = array(
    '#type' => 'date_popup',
    '#title' => t('Between'),
    '#date_label_position' => 'within',
    '#date_format' => 'd/m/Y',
    '#default_value' => (!empty($_GET['f4']['date'])) ? date('Y-m-d', strtotime($fromdate[2] . "/" . $fromdate[1] . "/" . $fromdate[0])) : '',
    '#date_year_range' => '-3:+3',
    '#prefix' => '<div id="date_popup_main"> <div class="date-label">' .t('Date Of Publication'). '</div><div id="search-block-start-date">',
    '#suffix' => '</div>',
    '#datepicker_options' => array(
	    'showOn' => 'button',
	    'buttonImage' => base_path() .path_to_theme('im') . '/css/images/calender.png',
	    'buttonImageOnly' => true,
     ),
  );
  if(!empty($_GET['f5']['date'])){
	  $todate = trim($_GET['f5']['date']);
	  $todate = explode("/", $todate);
  }
  $form['f5'] = array(
    '#type' => 'date_popup',
    '#title' => t('And'),
    '#date_label_position' => 'within',
    '#date_format' => 'd/m/Y',
    '#default_value' => (!empty($_GET['f5']['date'])) ? date('Y-m-d', strtotime($todate[2] . "/" . $todate[1] . "/" . $todate[0])) : '',
    '#date_year_range' => '-3:+3',
    '#prefix' => '<div id="search-block-end-date">',
    '#suffix' => '</div></div>',
    '#datepicker_options' => array(
	    'showOn' => 'button',
	    'buttonImage' => base_path() .path_to_theme('im') . '/css/images/calender.png',
	    'buttonImageOnly' => true,
     ),
  );
  $refresh_url = arg(0). "/" . arg(1) . "/" . arg(2);
  $form['f6'] = array(
    '#prefix' => '<div id="search-block-bottom">',
    '#type' => 'link',
    '#title' => t('Search Refresh'),
    '#href' => $refresh_url,    
  );
  $form['f7'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#submit' => array('im_search_block_form_submit'),
    '#attributes' => array('class' => array('search-submit')),
    '#suffix' => '</div>',
  );
  $form['#method'] = 'get';
  return $form;
}

/**
 * Get Solr index content types for the search filter
 */
function _im_search_get_entity_type(){
	$indexable_bundles = apachesolr_get_index_bundles('solr', 'node');
	$bundle_names = array();
    $entityinfo = entity_get_info('node');
	foreach ($indexable_bundles as $machine_name){
	  //array_push($bundle_names, t($entityinfo['bundles'][$machine_name]['label']));
	  $bundle_names[$machine_name] = t($entityinfo['bundles'][$machine_name]['label']);
	}
	array_unshift($bundle_names, t('All portals'));
	return $bundle_names;
}