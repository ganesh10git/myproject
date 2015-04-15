<?php
/**
 * 
 * Sales plan complete page
 * @param $year
 */

function im_sales_plan_page() {
  drupal_add_js(drupal_get_path('module', 'im_sales_plan') . '/js/jquery.jcarousel.min.js');
  $jcarousel_start = ''; 
  if (is_numeric(arg(3)) && arg(3) > 0) {
    $jcarousel_start = _im_sales_plan_padzero(arg(3)%52); 
  }
  
  //No ajax
  if (isset($_GET['region']) && isset($_SESSION['date-begun']) && (empty($_GET['date']) || empty($_GET['statevalue']))) {
  	$_SESSION['region_tid'] = arg(2);
    $year_change = date('Y',strtotime($_SESSION['date-begun']));
    $week = date('W',strtotime($_SESSION['date-begun']));
    $node_segment = (arg(4)) ? '/'. arg(4) : '';
    drupal_goto('sales-plan/' . $year_change . '/'.arg(2).'/' . $week . $node_segment );
  }
  
  $jcarousel_start = $jcarousel_start ? _im_sales_plan_padzero($jcarousel_start%52) : date('W');  
  drupal_add_js(array('current_week' => $jcarousel_start), 'setting');
  drupal_add_css(drupal_get_path('module', 'im_sales_plan') . '/css/carousel.css');
  drupal_add_js(drupal_get_path('module', 'im_sales_plan') . '/js/im_sales_plan.js');
  drupal_add_css(drupal_get_path('module', 'im_sales_plan') . '/css/im_sales_plan.css');
  if(is_numeric(arg(1)) && arg(1) != 'now'){
    $year = arg(1);
  }
  else{
    $year = date('Y');
  }
  $calendar   = im_sales_plan_calendar($year);
  //query to get latest created node.
  $today_date =date('Y-m-d')."T00:00:00";
  $sales_plan_content = '';
  //to load required node based on url.
  if(arg(4) && is_numeric(arg(4))){
    $sales_plan_content = im_sales_plan_content(arg(4));
  }
  else{
    $first_promotion_nid = '';
    //$first_promotion_nid = db_query("SELECT op.entity_id FROM {field_data_field_sp_operation_period} op INNER JOIN {node} n on n.nid=op.entity_id and op.field_sp_operation_period_value <= '.$today_date.' and op.field_sp_operation_period_value2 >= '.$today_date.' order by op.field_sp_operation_period_value ASC")->fetchField();
    $first_promotion_nid = db_query("SELECT op.entity_id FROM {field_data_field_sp_operation_period} op INNER JOIN {node} n on n.nid=op.entity_id  order by op.field_sp_operation_period_value ASC")->fetchField();
    $sales_plan_content = ($first_promotion_nid) ? im_sales_plan_content($first_promotion_nid) : '';
  }
 //print_r(arg());
  $sales_plan = '<div class="sales-plan-wrapper"><div id="sales-calendar">' . $calendar . '</div><div id="sales-content">' . $sales_plan_content . '</div></div>';
  if(isset($_GET['type']) &&  $_GET['type']== 'ajax'){
    print $sales_plan;
  }
  else{
    return $sales_plan;
  }
}

/**
 * 
 * Sales plan Calendar Block
 * @param $year
 */
function im_sales_plan_calendar($year) {
  $calendar = array();
  $days = array('Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun');
  $time_stamp = strtotime(date('d').'-'.date('m').'-'.$year);
  
  //Append Previous Year days - which is there in 1st week
  for ($day = 0; $day < 7; $day++) {
    if(date('D', $time_stamp) == $days[0]) {
      break;
    }else{
      $time_stamp = strtotime('-1 day', $time_stamp);
    }
  }
//Fetch all plan de vente(Sales contents)
  $plan_de_vente = array();
  $join       = '';
  $join_and   = '';
  $join_where = '';
  //For ajax request
  if(isset($_GET['date']) && isset($_GET['statevalue'])){
    if(isset($_SESSION['date-begun']) && $_GET['statevalue']== 'next'){
      $next_end_date = strtotime('+7 day', strtotime($_SESSION['date-end']));
      $date_end = date("Y-m-d", $next_end_date).'-T00:00:00';
      $next_begin_date = strtotime('+7 day', strtotime($_SESSION['date-begun']));
      $date_begin = date("Y-m-d", $next_begin_date).'-T00:00:00';
      $_SESSION['date-begun'] = date("Y-m-d", $next_begin_date);
      $_SESSION['date-end'] = date("Y-m-d", $next_end_date);
    }
    if(isset($_SESSION['date-begun']) && $_GET['statevalue']== 'prev'){
      $next_end_date = strtotime('-7 day', strtotime($_SESSION['date-end']));
      $date_end = date("Y-m-d", $next_end_date).'-T00:00:00';
      $next_begin_date = strtotime('-7 day', strtotime($_SESSION['date-begun']));
      $date_begin = date("Y-m-d", $next_begin_date).'-T00:00:00';
      $_SESSION['date-begun'] = date("Y-m-d", $next_begin_date);
      $_SESSION['date-end'] = date("Y-m-d", $next_end_date);
    }
  }
  else {
  	//if year changed arg(3) = Week
    if (is_numeric(arg(3)) && arg(3) > 0) {
      //If region changed
      if(is_numeric(arg(1)) && arg(1) > 0){
      	if(isset($_GET['sp_week']) && isset($_GET['sp_year']) ){
      		$wee = $_GET['sp_week'];
      	  $year = $_GET['sp_year'];
          $sp_week_no_arg = _im_sales_plan_padzero($wee);
      	  $sp_selected_date = $year.'W'.$sp_week_no_arg;
      	} 
      	else{
      	  $wee = date('W',strtotime($_SESSION['date-begun']));
      	  $session_begun_yr = date('Y',strtotime($_SESSION['date-begun']));
      	  $session_end_yr = date('Y',strtotime($_SESSION['date-end']));
      	  $new_year = $session_end_yr - $session_begun_yr;
      	  if($new_year == 1 && _im_sales_plan_padzero($wee) == '01'){
      	    $year = $session_end_yr;
      	  }
          $sp_week_no_arg = _im_sales_plan_padzero($wee);
      	  $sp_selected_date = $year.'W'.$sp_week_no_arg;
      	}
        $_SESSION['date-begun'] = date("Y-m-d", strtotime($sp_selected_date));
        $_SESSION['date-end'] = date("Y-m-d", strtotime('+5 week', strtotime($sp_selected_date)));
        $date_begin = date("Y-m-d", strtotime($_SESSION['date-begun'])).'-T00:00:00';
        $date_end = date("Y-m-d", strtotime($_SESSION['date-end'])).'-T00:00:00';
        $current_date_by_year = date("Y-m-d", strtotime($_SESSION['date-begun']));
        $time_stamp = strtotime($current_date_by_year);
      }
      else {
        if(isset($_GET['sp_week']) && isset($_GET['sp_year']) ){
      	  $wee = $_GET['sp_week'];
      	  $year = $_GET['sp_year'];
          $sp_week_no_arg = _im_sales_plan_padzero($wee);
      	  $sp_selected_date = $year.'W'.$sp_week_no_arg;
      	  $_SESSION['date-begun'] = date("Y-m-d", strtotime($sp_selected_date));
          $_SESSION['date-end'] = date("Y-m-d", strtotime('+5 week', strtotime($sp_selected_date)));
          $date_begin = date("Y-m-d", strtotime($_SESSION['date-begun'])).'-T00:00:00';
          $date_end = date("Y-m-d", strtotime($_SESSION['date-end'])).'-T00:00:00';
          $current_date_by_year = date("Y-m-d", strtotime($_SESSION['date-begun']));
          $time_stamp = strtotime($current_date_by_year);
      	}
      	else{
          $_SESSION['date-begun'] = date("Y-m-d", strtotime($_SESSION['date-begun']));
          $_SESSION['date-end'] = date("Y-m-d", strtotime($_SESSION['date-end']));
          $date_begin = date("Y-m-d", strtotime($_SESSION['date-begun'])).'-T00:00:00';
          $date_end = date("Y-m-d", strtotime($_SESSION['date-end'])).'-T00:00:00';
          $current_date_by_year = date("Y-m-d", strtotime($_SESSION['date-begun']));
          $time_stamp = strtotime($current_date_by_year);
      	}
      }
    }
    else{
      $date_end_timestamp = strtotime('+5 week', $time_stamp);
      $date_begin = date("Y-m-d", $time_stamp).'-T00:00:00';
      $date_end = date("Y-m-d", $date_end_timestamp).'-T00:00:00';
      $_SESSION['date-begun'] = date("Y-m-d", $time_stamp);
      $_SESSION['date-end'] = date("Y-m-d", $date_end_timestamp);
    }
  }
  //Calculate year for holidays
  if(isset($_SESSION['date-begun']) && isset($_SESSION['date-end']) && isset($_GET['statevalue'])){
    $current_year = date('Y', strtotime($_SESSION['date-begun']));
    $next_year = date('Y', strtotime($_SESSION['date-end']));
    if($current_year == $next_year){
      $year = $current_year;
    }
  }
  else {
    $current_year = $year;
    $next_year = $year + 1;
  }
  //Special Holidays
  $nodeArrays[] = node_load_multiple(array(), array('title' => $current_year, 'type' => 'holiday'));
  $nodeArrays[] = node_load_multiple(array(), array('title' => $next_year, 'type' => 'holiday'));
  
  $node;
  $special_holidays = array();
  //Regional Holidays
  $regional_holidays = array();
  $regional_holidays['zone_a'] = array();
  $regional_holidays['zone_b'] = array();
  $regional_holidays['zone_c'] = array();
  $holiday_pos_file = '';
  foreach ($nodeArrays as $key=>$nodeArray){
    $nodeArray = array_values($nodeArray);
	  if(isset($nodeArray[0])){
	  	$node = $nodeArray[0];
	    $items = field_get_items('node', $node, 'field_holiday_jours_sp_ciaux');
	    $pos_download_link = isset($node->field_holiday_pos_file['und'][0]['uri']) ?  file_create_url($node->field_holiday_pos_file['und'][0]['uri']) : '';
      $pos_filename = isset($node->field_holiday_pos_file['und'][0]['filename']) ? $node->field_holiday_pos_file['und'][0]['filename'] : '';
	    $holiday_pos_file[$node->title] = l($pos_filename,$pos_download_link);
	    foreach ($items as $item) {
	      $special_holiday = field_collection_field_get_entity($item);
	      //$special_holidays[] = date('d/m/Y', strtotime($special_holiday->field_holiday_special_day['und'][0]['value']));
	      if(isset($special_holiday->field_holiday_special_day['und'][0]['value'])) {
	        $special_holidays[date('d/m/Y', strtotime($special_holiday->field_holiday_special_day['und'][0]['value']))] = isset($special_holiday->field_holiday_special_name['und'][0]['value']) ? $special_holiday->field_holiday_special_name['und'][0]['value'] : '';
	      }
	    }
	  }
  
	  if(isset($nodeArray[0])){
	    $items = field_get_items('node', $node, 'field_holiday_period_des_vaccanc');
	    foreach ($items as $item) {
	  	  $regional_holiday = field_collection_field_get_entity($item);
	  	  $regional_holidays['zone_a'] = array_merge($regional_holidays['zone_a'],date_range($regional_holiday->field_holiday_zone_a['und'][0]['value'], $regional_holiday->field_holiday_zone_a['und'][0]['value2'], $step = '+1 day', $format = 'd/m/Y' )); 
	  	  $regional_holidays['zone_b'] = array_merge($regional_holidays['zone_b'],date_range($regional_holiday->field_holiday_zone_b['und'][0]['value'], $regional_holiday->field_holiday_zone_b['und'][0]['value2'], $step = '+1 day', $format = 'd/m/Y' ));
	  	  $regional_holidays['zone_c'] = array_merge($regional_holidays['zone_c'],date_range($regional_holiday->field_holiday_zone_c['und'][0]['value'], $regional_holiday->field_holiday_zone_c['und'][0]['value2'], $step = '+1 day', $format = 'd/m/Y' ));
	    }
	  }
  }
  if(isset($_SESSION['date-begun']) && isset($_GET['statevalue'])){
    $time_stamp = strtotime($_SESSION['date-begun']);
  }
  $current_date_range = date_range($_SESSION['date-begun'], $_SESSION['date-end']);
  //Fetch all plan de vente(Sales contents)
  $plan_de_vente = array();
  $join       = '';
  $join_and   = '';
  $join_where = '';
  $tid = isset($_SESSION['region_tid']) ? $_SESSION['region_tid'] : arg(2);
  if($tid != 'all'){
  $results = db_query("SELECT n.nid, n.title, fspr.field_sp_regions_tid, ftype.field_sp_type_value AS type, fop.field_sp_operation_period_value AS begin_date, fop.field_sp_operation_period_value2 AS end_date 
                 FROM node n 
                      INNER JOIN field_data_field_sp_operation_period fop ON fop.entity_id = n.nid
                      INNER JOIN field_data_field_sp_type ftype ON ftype.entity_id = n.nid 
                      LEFT JOIN field_data_field_sp_regions fspr ON fspr.entity_id = n.nid
                      WHERE n.nid = fop.entity_id AND n.status = 1 
                      AND n.nid = ftype.entity_id
                      AND fop.entity_id = ftype.entity_id
                      AND ((field_sp_operation_period_value >= :value1 
                        AND fop.field_sp_operation_period_value2 <= :value2)
                        OR (field_sp_operation_period_value <= :value2 
                        AND fop.field_sp_operation_period_value2 >= :value1))
                      AND n.type = 'sales_plan' 
                      ORDER BY fop.field_sp_operation_period_value ASC, fop.field_sp_operation_period_value2 ASC",
                      array(':value1' => $date_begin, ':value2' => $date_end)
                     )->fetchAll(PDO::FETCH_ASSOC);
  }
  else{                      
    $results = db_query("SELECT DISTINCT n.nid, n.title, ftype.field_sp_type_value AS type, fop.field_sp_operation_period_value AS begin_date, fop.field_sp_operation_period_value2 AS end_date 
                 FROM node n 
                      INNER JOIN field_data_field_sp_operation_period fop ON fop.entity_id = n.nid
                      INNER JOIN field_data_field_sp_type ftype ON ftype.entity_id = n.nid 
                      WHERE n.nid = fop.entity_id AND n.status = 1 
                      AND n.nid = ftype.entity_id
                      AND fop.entity_id = ftype.entity_id
                      AND ((field_sp_operation_period_value >= :value1 
                        AND fop.field_sp_operation_period_value2 <= :value2)
                        OR (field_sp_operation_period_value <= :value2 
                        AND fop.field_sp_operation_period_value2 >= :value1))
                      AND n.type = 'sales_plan' 
                      ORDER BY fop.field_sp_operation_period_value ASC, fop.field_sp_operation_period_value2 ASC",
                      array(':value1' => $date_begin, ':value2' => $date_end)
                     )->fetchAll(PDO::FETCH_ASSOC);
  }
  $nationale_count = 0;
  $regionale_count = 0;
  $non_alimentare_count = 0;
  $i = 0;
  $new_nid = '';
  //asort($results);
  foreach($results as $result) {
	  	$index = $i . ':' .$result['nid']; //Create index like 1:1, 1:2, 2:10, 2:16
	  	if((is_numeric($tid) && $result['type'] == 'regionale' && $result['field_sp_regions_tid'] == $tid) || ($result['type'] == 'nationale' || $result['type'] == 'non_alimentare')) {
		  	$plan_de_vente[$index]['nid'] = $result['nid'];
		  	$plan_de_vente[$index]['title'] = $result['title'];
		  	$plan_de_vente[$index]['type'] = $result['type'];
			$plan_de_vente_dates = date_range($result['begin_date'], $result['end_date']);
			$plan_de_vente[$index]['plan_de_begin_date'] = $result['begin_date'];
	      	$plan_de_vente[$index]['plan_de_end_date'] = $result['end_date'];
		  	$plan_de_vente[$index]['dates'] = array_values(array_intersect($current_date_range, $plan_de_vente_dates));
		  	 
	  	}
	  	else if (!is_numeric($tid)){
	  		if($new_nid != $result['nid']){
	 	  	  $plan_de_vente[$index]['nid'] = $result['nid'];
		      $plan_de_vente[$index]['title'] = $result['title'];
		      $plan_de_vente[$index]['type'] = $result['type'];
			  $plan_de_vente_dates = date_range($result['begin_date'], $result['end_date']);
			  $plan_de_vente[$index]['plan_de_begin_date'] = $result['begin_date'];
		      $plan_de_vente[$index]['plan_de_end_date'] = $result['end_date'];
		      $plan_de_vente[$index]['dates'] = array_values(array_intersect($current_date_range, $plan_de_vente_dates));
		    }
  			$new_nid = $result['nid'];
	 	}
  	
  	if($result['type'] == 'regionale') $regionale_count++;
    if($result['type'] == 'nationale') $nationale_count++;
    if($result['type'] == 'non_alimentare') $non_alimentare_count++;
  	$i++;
  } 
  return theme('im_sales_plan_calendar_template', array('begin_time' => $time_stamp, 'week_duration' => array('week_beg' => 1, 'week_end' => 5),'special_holidays' => $special_holidays, 'regional_holidays' => $regional_holidays, 'plan_de_vente' => $plan_de_vente, 'node_category' => array('national' => $nationale_count, 'regional' => $regionale_count, 'non_alimentare' => $non_alimentare_count), 'holiday_pos_file' => $holiday_pos_file));
}

function date_range($first, $last, $step = '+1 day', $format = 'd-m-Y' ) { 
  $dates   = array();
  $current = strtotime($first);
  $last    = strtotime($last);
  while($current <= $last) { 
      $dates[] = date($format, $current);
      $current = strtotime($step, $current);
  }
  return $dates;
}

/**
 * 
 * Sales plan Content Block
 * @param $year
 */
/*
function im_sales_plan_theme($existing, $type, $theme, $path) {
  return array(
      'sales_plan_content_template' =>  array(
        'template' => 'theme/sales_plan_content_template'
      ),
    );
}
*/
function im_sales_plan_page_replace_content() {
	$node_page = isset($_REQUEST['nid']) ? im_sales_plan_content($_REQUEST['nid']) : ''; 
  print $node_page;
}
function im_sales_plan_content($nid) {
  $node_item = node_load($nid);
  $node_value = array();
  $entity_type ='';
  $bundle_name = '';
  $entity_type = 'node';
  $bundle_name = 'sales_plan';
  $field_name = '';
  //Attachment label is defined.
  $catalogue_label = field_info_instance($entity_type,$field_name ='field_sp_catalogue' , $bundle_name);
  $node_value['field_sp_catalogue_label'] = t($catalogue_label['label']);
  
  $helpcontrol_label = field_info_instance($entity_type,$field_name ='field_sp_help_control' , $bundle_name);
  $node_value['field_sp_help_control_lable'] = t($helpcontrol_label['label']);
  
  $plv_label = field_info_instance($entity_type,$field_name ='field_sp_plv' , $bundle_name);
  $node_value['field_sp_plv_lable'] = t($plv_label['label']);
  
  $visual_label = field_info_instance($entity_type,$field_name ='field_sp_visual' , $bundle_name);
  $node_value['field_sp_visual_label'] = t($visual_label['label']);
  
  $other_label = field_info_instance($entity_type,$field_name ='field_sp_others' , $bundle_name);
  $node_value['field_sp_others_label'] = t($other_label['label']);
  
  $node_value['title'] = $node_item->title;
  if (isset($node_item->field_sp_type[LANGUAGE_NONE][0]['value']) && $node_item->field_sp_type['und'][0]['value']) {
    $node_value['field_sp_type'] = $node_item->field_sp_type['und'][0]['value'];
  } 
    
  if (isset($node_item->body) && $node_item->body) {
    $node_value['body'] = $node_item->body['und'][0]['value'];
  } 
    
  if (isset($node_item->field_sp_operation_period[LANGUAGE_NONE][0]['value']) && $node_item->field_sp_operation_period['und'][0]['value']) {
    $formatted_sp_cop_url = '';
    $node_value['field_sp_operation_period'] = $node_item->field_sp_operation_period['und'][0]['value'];
    $sp_year = date('Y',strtotime($node_item->field_sp_operation_period['und'][0]['value']));
    $sp_week = date('W',strtotime($node_item->field_sp_operation_period['und'][0]['value']));
    $sp_url = $GLOBALS['base_url'] .base_path().'sales-plan/'.$sp_year.'/all/'.$sp_week.'/'.$nid;
    $sp_query = array('query' => array('sp_year'=>$sp_year, 'sp_week'=> $sp_week),'external' => TRUE,'https'=>TRUE); 
    $formatted_sp_cop_url = url($sp_url,$sp_query);
    $node_value['sp_copy'] = $formatted_sp_cop_url;
  } 
    
  if (isset($node_item->field_sp_order_period[LANGUAGE_NONE][0]['value']) && $node_item->field_sp_order_period['und'][0]['value2']) {
    $node_value['field_sp_order_period_startdate'] = date('d-m-Y',strtotime($node_item->field_sp_order_period['und'][0]['value']));
    $node_value['field_sp_order_period_enddate'] = date('d-m-Y',strtotime($node_item->field_sp_order_period['und'][0]['value2']));
  }
    
    //documents
  $documents_catalogue = (isset($node_item->field_sp_catalogue[LANGUAGE_NONE]) && is_array($node_item->field_sp_catalogue[LANGUAGE_NONE])) ? $node_item->field_sp_catalogue[LANGUAGE_NONE] : array();
  $document_links_catalogue = array();
  foreach ($documents_catalogue as $index => $document) {
    $document_links_catalogue[] = array('name' => $document['filename'], 'url' => file_create_url($document['uri']), 'file_id' => $document['fid']);
  }
  $node_value['field_sp_catalogue'] = $document_links_catalogue;
    
  $documents_control = (isset($node_item->field_sp_help_control[LANGUAGE_NONE]) && is_array($node_item->field_sp_help_control[LANGUAGE_NONE])) ? $node_item->field_sp_help_control[LANGUAGE_NONE] : array();
  $document_links_control = array();
  foreach ($documents_control as $index => $document) {
    $document_links_control[] = array('name' => $document['filename'], 'url' => file_create_url($document['uri']), 'file_id' => $document['fid']);
  }
  $node_value['field_sp_help_control'] = $document_links_control;
    
  $documents_plv = (isset($node_item->field_sp_plv[LANGUAGE_NONE]) && is_array($node_item->field_sp_plv[LANGUAGE_NONE])) ? $node_item->field_sp_plv[LANGUAGE_NONE] : array();
  $document_links_plv = array();
  foreach ($documents_plv as $index => $document) {
    $document_links_plv[] = array('name' => $document['filename'], 'url' => file_create_url($document['uri']), 'file_id' => $document['fid']);
  }
  $node_value['field_sp_plv'] = $document_links_plv;
   
  $documents_visual = (isset($node_item->field_sp_visual[LANGUAGE_NONE]) && is_array($node_item->field_sp_visual[LANGUAGE_NONE])) ? $node_item->field_sp_visual[LANGUAGE_NONE] : array();
  $document_links_visual = array();
  foreach ($documents_visual as $index => $document) {
    $document_links_visual[] = array('name' => $document['filename'], 'url' => file_create_url($document['uri']), 'file_id' => $document['fid']);
  }
  $node_value['field_sp_visual'] = $document_links_visual;
  $documents_image_pros = (isset($node_item->field_sp_image_pros[LANGUAGE_NONE]) && is_array($node_item->field_sp_image_pros[LANGUAGE_NONE])) ? $node_item->field_sp_image_pros[LANGUAGE_NONE] : array();
  $document_links_image_pros = array();
  foreach ($documents_image_pros as $index => $document) {
    $document_links_image_pros[] = array('name' => $document['filename'], 'url' => $document['uri']);
  }
  $node_value['field_sp_image_pros'] = $document_links_image_pros;
  $documents_others = (isset($node_item->field_sp_others[LANGUAGE_NONE]) && is_array($node_item->field_sp_others[LANGUAGE_NONE])) ? $node_item->field_sp_others[LANGUAGE_NONE] : array();
  $document_links_others = array();
  foreach ($documents_others as $index => $document) {
    $document_links_others[] = array('name' => $document['filename'], 'url' => file_create_url($document['uri']), 'file_id' => $document['fid']);
  }
  $node_value['field_sp_others'] = $document_links_others;

  return theme('sales_plan_content_template', $node_value); 
}

/** 
 * Get the 'row' postion of the node (In which Row this node can come)
 * @param $node_begin_date
 * @param $nodes_processed_by_date
 */
function check_date_in_proceesed_nodes($node_begin_date = '', $nodes_processed_by_date = array()) {
  asort($nodes_processed_by_date); //Sort the global node array
  $row_count = get_nodes_processed_row_count($nodes_processed_by_date, '#'); //Get the current row count
  $last_row_val = $row_count ? $row_count : 0;  
  
  //Loop the Rows
  for ($row = 1; $row <= $last_row_val; $row++) { 
    $same_row = true;  	
    //Loop the global node array
    foreach ($nodes_processed_by_date as $nodes_processed) { 
      //Row by Row
      if (strstr($nodes_processed, $row.'#')) { 
        //If node begin date is present in global node array means It need to come in a New Row
        //Else this node can come in the same Row
        if (strstr($nodes_processed, $node_begin_date)) { 
          $same_row = false; 
        }
      }  	
    } 
    if ($same_row) {
      return $row;
    }
  }
  
  return $last_row_val+1;
}

/**
 * Get the current row count based on global node array
 * @param $nodes_processed_by_date
 * @param $delimiter
 */
function get_nodes_processed_row_count($nodes_processed_by_date, $delimiter = '#') {
  $row_val = 0;
  foreach ($nodes_processed_by_date as $nodes_processed) {
    $rows = explode($delimiter, $nodes_processed);
    if ($rows[0] > $row_val) {
      $row_val = $rows[0];
    }
  }
  return $row_val;
}
