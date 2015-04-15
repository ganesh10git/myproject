<?php 
/**
 * @file
 * Inc file for Sales Plan Right side bar content
 */

/**
 * Function to get this week sales plan data.
 */
function get_sales_plan_details() {
	include_once drupal_get_path('module', 'im_sales_plan') . '/includes/im_sales_plan_page.inc';
	
  $sales_plan = array();
  $days = array('Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun');
  $time_now = strtotime('now');
  //to display according the future date if searched.
  $curr_path = '';
  $curr_path = isset($_GET['q']) ? $_GET['q'] : '';
  if(!empty($curr_path)) {
    $path_args = explode('/', $curr_path);
    if($path_args[2] != 'today' && is_numeric($path_args[2])) {
      $time_now = strtotime($path_args[2]);
    }
  }
  $year = date('Y');

  //Find this week begin day
  for ($day = 0; $day < 7; $day++) {
    if(date('D', $time_now) == $days[0]) {
      break;
    } else{
      $time_now = $time_now - (60*60*24);
    }
  }
  
  $date_time = date('m/d/Y', $time_now);
  $this_week = array();
  //Get days in the current week
  $this_week = date_range($date_time, date('m/d/Y', strtotime('+6 days', $time_now)));

	$sales_plan['this_week_begin'] = $time_now; //Add This week begin time	
  $sales_plan['this_week_no'] = date('W', $time_now); //Add This week number
  $sales_plan['this_week'] = $this_week; //Add This week begin time  
	
  $nodeArray = node_load_multiple(array(), array('title' => $year, 'type' => 'holiday'));
  $nodeArray = array_values($nodeArray);
  
  //Special Holidays
  $special_holidays = array();
  if(isset($nodeArray[0])){
    $node = $nodeArray[0];
    $items = field_get_items('node', $node, 'field_holiday_jours_sp_ciaux');
    foreach ($items as $item) {
      $special_holiday = field_collection_field_get_entity($item);
      $special_holidays[] = date('d/m/Y', strtotime($special_holiday->field_holiday_special_day['und'][0]['value']));
    }
  }
  $sales_plan['special_holidays'] = $special_holidays;
  
  //Regional Holidays
  $regional_holidays = array();
  $regional_holidays['zone_a'] = array();
  $regional_holidays['zone_b'] = array();
  $regional_holidays['zone_c'] = array();
  if(isset($nodeArray[0])){
  	$node = $nodeArray[0];
    $items = field_get_items('node', $node, 'field_holiday_period_des_vaccanc');

    foreach ($items as $item) {
      $regional_holiday = field_collection_field_get_entity($item);
      $regional_holidays['zone_a'] = array_merge($regional_holidays['zone_a'],date_range($regional_holiday->field_holiday_zone_a['und'][0]['value'], $regional_holiday->field_holiday_zone_a['und'][0]['value2'], $step = '+1 day', $format = 'd/m/Y' )); 
      $regional_holidays['zone_b'] = array_merge($regional_holidays['zone_b'],date_range($regional_holiday->field_holiday_zone_b['und'][0]['value'], $regional_holiday->field_holiday_zone_b['und'][0]['value2'], $step = '+1 day', $format = 'd/m/Y' ));
      $regional_holidays['zone_c'] = array_merge($regional_holidays['zone_c'],date_range($regional_holiday->field_holiday_zone_c['und'][0]['value'], $regional_holiday->field_holiday_zone_c['und'][0]['value2'], $step = '+1 day', $format = 'd/m/Y' ));
    }
  }
  
	$sales_plan['regional_holidays'] = $regional_holidays; //Add Regional Holidays
	
	//Fetch all plan de vente(Sales contents)
	$sales_plan_data = array();
	$join       = '';
	$join_and   = '';
	$join_where = '';
	$tid = arg(2);
  $week_begin = date('Y-m-d', strtotime($this_week[0])).'T00:00:00';
  $week_end = date('Y-m-d', strtotime(end($this_week))).'T24:00:00';
  
	if(is_numeric($tid) && arg(0) == 'sales-plan') {
		$join = ', field_data_field_sp_regions AS fspr';
		$join_and = 'AND n.nid = fspr.entity_id';
		$join_where = 'AND fspr.field_sp_regions_tid = ' . $tid;
	}
	
	//Get Sale plan nodes which are occuring this Week
	$results = db_query("SELECT n.nid,
                        n.title,
                        ftype.field_sp_type_value AS type,  
                        fop.field_sp_operation_period_value AS begin_date,
                        fop.field_sp_operation_period_value2 AS end_date
                        FROM {node} n, 
                        {field_data_field_sp_operation_period} fop,
                        {field_data_field_sp_type} ftype
                        $join
                        WHERE n.nid = fop.entity_id AND n.status = 1 
                        AND n.nid = ftype.entity_id
                        AND fop.entity_id = ftype.entity_id
                        $join_and
                        AND ((field_sp_operation_period_value >= :value1 
                        AND fop.field_sp_operation_period_value2 <= :value2)
                        OR (field_sp_operation_period_value <= :value2 
                        AND fop.field_sp_operation_period_value2 >= :value1))
                        AND n.type = 'sales_plan' 
                        $join_where ORDER BY fop.field_sp_operation_period_value ASC, fop.field_sp_operation_period_value2 ASC",
                        array(':value1' => $week_begin, ':value2' => $week_end)
             );

	$i = 0;
	foreach($results as $result) {
		$index = $i . ':' .$result->nid; //Create index like 1:1, 1:2, 2:10, 2:16   
		$sales_plan_data[$index]['nid'] = $result->nid;
		$sales_plan_data[$index]['title'] = $result->title;
		$sales_plan_data[$index]['type'] = $result->type;
		$sales_plan_data[$index]['dates'] = date_range($result->begin_date, $result->end_date);   
		$i++;
	}
	
	$sales_plan['sales_plan_data'] = $sales_plan_data; //Sale plan Nodes

  return array($sales_plan);
}
