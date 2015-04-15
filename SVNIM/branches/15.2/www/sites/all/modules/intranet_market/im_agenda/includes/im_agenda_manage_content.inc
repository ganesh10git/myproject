<?php
function im_agenda_manage_content(){
	drupal_add_css(drupal_get_path('module', 'im_agenda') . '/css/im_agenda_admin.css');
  return drupal_get_form('im_agenda_manage_content_form');
}

function im_agenda_manage_content_form(){
  $form = array();
  $format = 'd-m-Y';
  $agenda_types = array('action' => t('Action'), 
                        'alert' => t('Alert'),
                        'news' => t('News'),
                        'benchmark' => t('Benchmark') 
                        );
  $agenda_types_default = isset($_SESSION['agenda_type_before_shift']) ? $_SESSION['agenda_type_before_shift'] : array();
  
  // Get the Departments list from the taxonomy 'Departments'
  $departments = array(0 => t('Department'));
  $taxonomy_machine_name = 'agenda_department';
  $vocabulary = taxonomy_vocabulary_machine_name_load($taxonomy_machine_name);
  $dept_vid = $vocabulary->vid;
  
  $dept_tree = taxonomy_get_tree($dept_vid, $parent = 0, $max_depth = NULL, $load_entities = FALSE);
  
  foreach($dept_tree as $key => $value) {  	
  	$departments[$value->tid] =  $value->name;
  }
  $departments_default = isset($_SESSION['manage_content_agenda_department']) ? $_SESSION['manage_content_agenda_department'] : array();
  $status = array(0 => t('Status'), 1 => t('Drafts'), 2 => t('Needs Review'), 3 => t('Published'), 4 => t('Archive'));
  $status_default = isset($_SESSION['manage_content_agenda_status']) ? $_SESSION['manage_content_agenda_status'] : array();
  
  $dos = array(0 => t('DO'));
  $do_list = _im_agenda_manage_content_list_dos_dr_cf('do');
  $do_default = isset($_SESSION['manage_content_agenda_do']) ? $_SESSION['manage_content_agenda_do'] : array();
  foreach($do_list as $value) {
  	$dos[$value] = $value;
  }
  
  $agenda_dr_cf = array(0 => t('DR/CF'));
  $drcf_list = _im_agenda_manage_content_list_dos_dr_cf('dr-cf');
  $drcf_default = isset($_SESSION['manage_content_agenda_dr_cf']) ? $_SESSION['manage_content_agenda_dr_cf'] : array();
  foreach($drcf_list as $value) {
  	$agenda_dr_cf[$value] = $value;
  }
  
  $agenda_roles = array('dm' => t('DM'), 'mm' => t('MM'), 'employee' => t('Employee'));  
  $agenda_roles_sess = isset($_SESSION['manage_content_agenda_roles']) ? $_SESSION['manage_content_agenda_roles'] : array();
  $roles_default = array();
  foreach($agenda_roles_sess as $key => $value) {    
    if($value == 'store_director') {
      $roles_default[] = 'dm';
    }
    elseif ($value == 'store_manager') {
      $roles_default[] = 'mm';
    }
    elseif ($value == 'store_employee') {
      $roles_default[] = 'employee';
    }
  }
  
  $action_scope = array(0 => t('Type'), 'national' => t('National'), 'regional' => t('Regional'));
  $scope_default = isset($_SESSION['manage_action_scope']) ? $_SESSION['manage_action_scope'] : array();  
  
  $date_default = (isset($_SESSION['manage_content_agenda_date']) && $_SESSION['manage_content_agenda_date']) ? $_SESSION['manage_content_agenda_date'] : date('Y-m-d');
  $agenda_search_default = isset($_SESSION['manage_content_agenda_search']) ? $_SESSION['manage_content_agenda_search'] : '';
  $form['agenda_date'] = array(
     '#type' => 'date_popup',
     '#date_format' => $format,
     '#default_value' => $date_default,
     '#required' => FALSE,
  	 '#weight' => 1,
    );
  $form['agenda_type'] = array(
     '#type' => 'checkboxes',
     '#options' => $agenda_types,
     '#default_value' => $agenda_types_default,
     '#required' => FALSE,
  	 '#after_build' => array('im_agenda_manage_content_disable_element'),
  	 '#weight' => 2,
  	 
    );
  $form['agenda_department'] = array(
     '#type' => 'select',
     '#options' =>$departments,
  	 '#default_value' => $departments_default,
     '#required' => FALSE,
  	 '#weight' => 3,
    );
  $form['agenda_status'] = array(
     '#type' => 'select',
     '#options' =>$status,
     '#default_value' => $status_default,
     '#required' => FALSE,
  	 '#weight' => 4,
    );
  $form['agenda_do'] = array(
     '#type' => 'select',
     '#options' => $dos,
  	 '#default_value' => $do_default,
     '#required' => FALSE,
  	 '#weight' => 5,
    );
  $form['agenda_dr_cf'] = array(
     '#type' => 'select',
     '#options' => $agenda_dr_cf,
     '#default_value' => $drcf_default,
     '#required' => FALSE,
  	 '#weight' => 6,
    );
  $form['agenda_roles'] = array(
     '#type' => 'checkboxes',
     '#options' => $agenda_roles,
  	 '#default_value' => $roles_default,
     '#required' => FALSE,
  	 '#weight' => 7,     
    );
  $form['action_scope'] = array(
     '#type' => 'select',
     '#options' => $action_scope,
  	 '#default_value' => $scope_default,
     '#required' => FALSE,
  	 '#weight' => 8,  
  	 '#states' => array(
  		'enabled' => array(
  			':input[name="agenda_type[action]"]' => array(array('checked' => TRUE)),  				
  		),
  	 ),
    );
  $form['agenda_search'] = array(
     '#type' => 'textfield',
     '#required' => FALSE,
  	 '#default_value' => $agenda_search_default,
  	 '#weight' => 9,
    ); 
  $form['agenda_submit'] = array(
     '#type' => 'submit',
     '#value' => 'search',
  	 '#weight' => 10,
    );
  return $form;  
}

/**
 * To disable the content types checkboxes based on the roles and permissions
 * Enter description here ...
 * @param unknown_type $element
 */
function im_agenda_manage_content_disable_element($element){
	global $user;
  	if(!in_array('contributor_action',$user->roles) && !in_array('content_manager_action',$user->roles) && !in_array('content_manager_action_regional',$user->roles) && !in_array('administrator',$user->roles) && !in_array('technical_director',$user->roles)){
		foreach (element_children($element) as $key) {
		    if ($key == 'action') {
		      $element[$key]['#attributes'] = array('disabled' => 'disabled');
		    }
		}
  	}
	if(!in_array('contributor_alert',$user->roles) && !in_array('administrator',$user->roles) && !in_array('technical_director',$user->roles) && !in_array('content_manager_action',$user->roles) && !in_array('content_manager_action_regional',$user->roles)){
		foreach (element_children($element) as $key) {
		    if ($key == 'alert') {
		      $element[$key]['#attributes'] = array('disabled' => 'disabled');
		    }
		}
  	}
	if(!in_array('contributor_news',$user->roles) && !in_array('administrator',$user->roles) && !in_array('technical_director',$user->roles) && !in_array('content_manager_action',$user->roles) && !in_array('content_manager_action_regional',$user->roles)){
		foreach (element_children($element) as $key) {
		    if ($key == 'news') {
		      $element[$key]['#attributes'] = array('disabled' => 'disabled');
		    }
		}
  	}
	if(!in_array('contributor_benchmark',$user->roles) && !in_array('administrator',$user->roles) && !in_array('technical_director',$user->roles) && !in_array('content_manager_action',$user->roles) && !in_array('content_manager_action_regional',$user->roles)){
		foreach (element_children($element) as $key) {
		    if ($key == 'benchmark') {
		      $element[$key]['#attributes'] = array('disabled' => 'disabled');
		    }
		}
  	}
	return $element;
}

/**
 * Implementation of im_agenda_manage_content_form_submit
 * 
 */
function im_agenda_manage_content_form_submit($form, &$form_state) {	
	$agenda_roles = array();
	$agenda_roles_arr = array_filter($form_state['values']['agenda_roles']);
	foreach($agenda_roles_arr as $key => $value) {    
		if($value == 'mm') {
	      $agenda_roles[] = 'store_manager';
	    }
	    elseif ($value == 'dm') {
	      $agenda_roles[] = 'store_director';
	    }
	    elseif ($value == 'employee') {
	      $agenda_roles[] = 'store_employee';
	    }
	}
	
	$_SESSION['manage_content_agenda_date'] = (isset($form_state['values']['agenda_date'])) ? $form_state['values']['agenda_date'] : '';
	$_SESSION['agenda_type_before_shift'] = (isset($form_state['values']['agenda_type'])) ? $form_state['values']['agenda_type'] : '';
	if($form_state['values']['agenda_type']['action']!='0'){
		$_SESSION['manage_action_scope'] = (isset($form_state['values']['action_scope'])) ? $form_state['values']['action_scope'] : '';
	}else{
		$_SESSION['manage_action_scope'] = "";
	}
		
	if((isset($form_state['values']['agenda_type']) && $form_state['values']['agenda_type']['action']!='0') && (isset($form_state['values']['action_scope']) && $form_state['values']['action_scope']!='0')){
		array_shift($form_state['values']['agenda_type']);
	}
	
	$_SESSION['manage_content_agenda_type'] = (isset($form_state['values']['agenda_type'])) ? $form_state['values']['agenda_type'] : '';
	$_SESSION['manage_content_agenda_department'] = (isset($form_state['values']['agenda_department'])) ? $form_state['values']['agenda_department'] : '';
	$_SESSION['manage_content_agenda_status'] = (isset($form_state['values']['agenda_status'])) ? $form_state['values']['agenda_status'] : '';
	$_SESSION['manage_content_agenda_do'] = (isset($form_state['values']['agenda_do'])) ? $form_state['values']['agenda_do'] : '';	
	$_SESSION['manage_content_agenda_dr_cf'] = (isset($form_state['values']['agenda_dr_cf'])) ? $form_state['values']['agenda_dr_cf'] : '';	
	$_SESSION['manage_content_agenda_roles'] = (isset($agenda_roles)) ? $agenda_roles : '';
	$_SESSION['manage_content_agenda_search'] = (isset($form_state['values']['agenda_search'])) ? $form_state['values']['agenda_search'] : '';	
}

function im_agenda_manage_content_block(){
	global $user;
	$agenda_date = date('Y-m-d');
	$agenda_date_filter = '';
	$agenda_type_filter = '';
	$agenda_department_filter = '';
	$agenda_status_filter = '';
	$agenda_roles_filter = '';
	
	//Agenda Date filter:
	if(isset($_SESSION['manage_content_agenda_date']) && $_SESSION['manage_content_agenda_date']) {
		$agenda_date = $_SESSION['manage_content_agenda_date'];
		$agenda_date .= 'T00:00:00';
		$agenda_date_filter = " agenda_date.field_agenda_date_value = '$agenda_date' ";
	}else{
		$agenda_date .= 'T00:00:00';
		$agenda_date_filter = " agenda_date.field_agenda_date_value = '$agenda_date' ";
	}
	
	//Agenda Type filter:	
	$agenda_types = '';
	$type_prefix = '';
	if(in_array('contributor_action',$user->roles)){
		$agenda_types.= $type_prefix . "'action'";
    	$type_prefix = ', ';
    	$agenda_type_filter = " AND n.type IN($agenda_types)";
	}
	if(in_array('content_manager_action',$user->roles)){
		$agenda_type_filter = " AND n.type IN('alert', 'action', 'news', 'benchmark')";
	}
	if(in_array('contributor_alert',$user->roles)){
		$agenda_types.= $type_prefix . "'alert'";
    	$type_prefix = ', ';
    	$agenda_type_filter = " AND n.type IN($agenda_types)";
	}
	if(in_array('contributor_news',$user->roles)){
		$agenda_types.= $type_prefix . "'news'";
    	$type_prefix = ', ';
    	$agenda_type_filter = " AND n.type IN($agenda_types)";
	}
	if(in_array('contributor_benchmark',$user->roles)){
		$agenda_types.= $type_prefix . "'benchmark'";
    	$type_prefix = ', ';
    	$agenda_type_filter = " AND n.type IN($agenda_types)";
	}
	if(in_array('administrator',$user->roles) || in_array('technical_director',$user->roles)){
		$agenda_type_filter = " AND n.type IN('alert', 'action', 'news', 'benchmark')";
	}
	if(!isset($_SESSION['manage_content_agenda_type'])){
		$agenda_type_filter = " AND n.type IN('alert', 'action', 'news', 'benchmark')";
	}
	else if(isset($_SESSION['manage_content_agenda_type']) && array_key_exists('action', $_SESSION['manage_content_agenda_type'])){
		if(!in_array('content_manager_action_regional',$user->roles)){
			if(($_SESSION['manage_content_agenda_type']['action']=='0' && $_SESSION['manage_content_agenda_type']['alert']=='0' && $_SESSION['manage_content_agenda_type']['news']=='0' && $_SESSION['manage_content_agenda_type']['benchmark']=='0')){
				$agenda_type_filter = " AND n.type IN('alert', 'action', 'news', 'benchmark')";
			}
			else{
				$in_agenda_type = implode("' , '", array_filter($_SESSION['manage_content_agenda_type']));
				$agenda_type_filter = " AND n.type IN ('$in_agenda_type')";
			}
		}
	}else{
		if(($_SESSION['manage_content_agenda_type']['alert']=='0' && $_SESSION['manage_content_agenda_type']['news']=='0' && $_SESSION['manage_content_agenda_type']['benchmark']=='0') && (isset($_SESSION['manage_action_scope']) && $_SESSION['manage_action_scope']!='0')){
			$agenda_type_filter = "";
		}else{
			$in_agenda_type = implode("' , '", array_filter($_SESSION['manage_content_agenda_type']));
			$agenda_type_filter = " OR n.type IN ('$in_agenda_type')";
		}
			
	}
	
  	//Department Filter
  	if(isset($_SESSION['manage_content_agenda_department']) && $_SESSION['manage_content_agenda_department']) {
  		$agenda_department_filter = " AND deptmnt.field_agenda_department_tid = " . $_SESSION['manage_content_agenda_department'];
  	}
		
  //Status Filter
  $workbench_status = "";
  if(isset($_SESSION['manage_content_agenda_status']) && $_SESSION['manage_content_agenda_status']) {
  	//If status is Draft
  	if($_SESSION['manage_content_agenda_status'] == 1){
  		$agenda_status_filter = ' AND n.status = 0 AND aj_draft_status.field_draft_status_value = 1 AND aj_node_archive.field_node_archive_value = 0';
  	}
  	//If Status is Needs Review
  	if($_SESSION['manage_content_agenda_status'] == 2) {
   		$workbench_status = "needs_review";
  		$agenda_status_filter = " AND n.status = 0 AND aj_draft_status.field_draft_status_value = 0 AND aj_node_archive.field_node_archive_value = 0 AND workbench_status.state='".$workbench_status."'";
  	}
  	//If status is published
  	if($_SESSION['manage_content_agenda_status'] == 3) {
  		$agenda_status_filter = ' AND n.status = 1 AND aj_draft_status.field_draft_status_value = 0 AND aj_node_archive.field_node_archive_value = 0';
  	}
  	//If status is archived
    if($_SESSION['manage_content_agenda_status'] == 4) {
   		$agenda_status_filter = ' AND n.status = 0 AND aj_draft_status.field_draft_status_value = 0 AND aj_node_archive.field_node_archive_value = 1';
  	}
  }
  
  // Roles Filter : $_SESSION['manage_content_agenda_roles']
  //$agenda_roles_filter = " AND aj_conc.field_agenda_concernees_value IN ('store_director', 'store_manager', 'store_employee')";
  if(isset($_SESSION['manage_content_agenda_roles']) && count(array_filter($_SESSION['manage_content_agenda_roles'])) > 0) {
    $in_agenda_roles = implode("' , '", array_filter($_SESSION['manage_content_agenda_roles']));
    $agenda_roles_filter = " AND aj_conc.field_agenda_concernees_value IN ('$in_agenda_roles')";
  }
  
  //Do & DR/CF Filter
  $pve_code_list = "";
  $prefix = '';
  if(isset($_SESSION['manage_content_agenda_dr_cf']) && $_SESSION['manage_content_agenda_dr_cf']) {
  	$dr_cf_stores = db_query("SELECT distinct(apn.entity_id)
  								FROM {store_item_fields} sf
  								INNER JOIN {field_data_field_preferred_store_options} pso ON (sf.pve_code = pso.field_preferred_store_options_value)
  								INNER JOIN {field_data_field_agenda_preference_nid} apn ON (cast(apn.field_agenda_preference_nid_value as bigint) = pso.entity_id)							 
  								WHERE sf.ite_lib_value = '".$_SESSION['manage_content_agenda_dr_cf']."'"
  							 );
  	foreach ($dr_cf_stores as $dr_cf) {
		$pve_code_list.= $prefix . "'" . $dr_cf->entity_id . "'";
    	$prefix = ', ';
	}
  }else{
  	if(isset($_SESSION['manage_content_agenda_do']) && $_SESSION['manage_content_agenda_do']){
  		$dr_cf_stores = db_query("SELECT distinct(apn.entity_id)
  								FROM {store_item_fields} sf
  								INNER JOIN {field_data_field_preferred_store_options} pso ON (sf.pve_code = pso.field_preferred_store_options_value)
  								INNER JOIN {field_data_field_agenda_preference_nid} apn ON (cast(apn.field_agenda_preference_nid_value as bigint) = pso.entity_id)							 
  								WHERE sf.ite_lib_value = '".$_SESSION['manage_content_agenda_do']."'"
  							 );
	  	foreach ($dr_cf_stores as $dr_cf) {
			$pve_code_list.= $prefix . "'" . $dr_cf->entity_id . "'";
	    	$prefix = ', ';
		}
  	}
  }
  
  //Search Text Filter
  $text_search_filter = '';
  if(isset($_SESSION['manage_content_agenda_search']) && $_SESSION['manage_content_agenda_search']){
  	$string = str_replace("%", "", $_SESSION['manage_content_agenda_search']);
    $result = _im_feature_manage_content_views_query_chars_support($string);
    $string_decode = $result['string_decode'];
    $string_encode = $result['string_encode'];
    $special_chars_flag = $result['special_chars_flag'];
    $text_search_filter = " AND (translate(lower(title), 'Ã¢Ã£Ã¤Ã¥Ä�ÄƒÄ…Ã¨Ã©Ã©ÃªÃ«Ä“Ä•Ä—Ä™Ä›Ã¬Ã­Ã®Ã¯Ã¬Ä©Ä«Ä­Ã³Ã´ÃµÃ¶Å�Å�Å‘Ã¹ÃºÃ»Ã¼Å©Å«Å­Å¯', 'aaaaaaaeeeeeeeeeeiiiiiiiiooooooouuuuuuu') LIKE '%" . $string_decode . "%' OR translate(lower(title), 'aaaaaaaeeeeeeeeeeiiiiiiiiooooooouuuuuuu', 'Ã¢Ã£Ã¤Ã¥Ä�ÄƒÄ…Ã¨Ã©Ã©ÃªÃ«Ä“Ä•Ä—Ä™Ä›Ã¬Ã­Ã®Ã¯Ã¬Ä©Ä«Ä­Ã³Ã´ÃµÃ¶Å�Å�Å‘Ã¹ÃºÃ»Ã¼Å©Å«Å­Å¯') LIKE '%" . $string_encode . "%')";
  }
  
  //Action content scope field filter
  if(!in_array('content_manager_action_regional',$user->roles)){
	  $action_scope_filter = '';
	  if(isset($_SESSION['manage_action_scope']) && $_SESSION['manage_action_scope']) {
	  	$action_scope_filter.= "  AND (n.type='action' AND action_scope.field_action_scope_of_content_value = '".$_SESSION['manage_action_scope']."')";
	  }
  }
  
  $agenda_store_join = '';
  $agenda_store_condition = '';
  if(in_array('content_manager_action_regional',$user->roles)){
	  $user_load = user_load($user->uid);
	  if (!empty($user_load->field_user_regional_profile_stor['und'][0]['value'])) {    
	    $userstores[] = $user_load->field_user_regional_profile_stor['und'][0]['value'];
	    if (strstr($user_load->field_user_regional_profile_stor['und'][0]['value'],',')) {
	      $userstoresarray = $user_load->field_user_regional_profile_stor['und'][0]['value'];
	      $userstores = array();
	      $userstores = explode(',',$userstoresarray);
	      $userstoresarray = array();
	    }
	  }
	  $user_selected_store = "";
	  for ($i = 0; $i < count($userstores); $i++) {
	    if ($i == (count($userstores) - 1)) {
	      $user_selected_store .= '[[:<:]]' . $userstores[$i] . '[[:>:]]';
	     }
	     else {
	       $user_selected_store .= '[[:<:]]' . $userstores[$i] . '[[:>:]]' . '|';
	      }       
	  }
 	if(!isset($_SESSION['manage_content_agenda_type'])){
		$agenda_type_filter = " And (n.type IN('action', 'alert', 'news', 'benchmark')";
		$agenda_store = $user_selected_store;
	 	$action_scope = array('national','regional');
  	  	$agenda_store_join = " LEFT JOIN {field_data_field_agenda_store} agenda_store ON agenda_store.entity_id = n.nid ";
  	  	$agenda_store_condition = " AND ((action_scope.field_action_scope_of_content_value <> 'regional') OR (agenda_store.field_agenda_store_value ~ '". $agenda_store ."' AND action_scope.field_action_scope_of_content_value = 'regional')) )";
	}
	else if(isset($_SESSION['manage_content_agenda_type']) && array_key_exists('action', $_SESSION['manage_content_agenda_type'])){
		if(($_SESSION['manage_content_agenda_type']['action']=='0' && $_SESSION['manage_content_agenda_type']['alert']=='0' && $_SESSION['manage_content_agenda_type']['news']=='0' && $_SESSION['manage_content_agenda_type']['benchmark']=='0')){
			$agenda_type_filter = " AND ( n.type IN('alert', 'news', 'benchmark')";
			$agenda_store = $user_selected_store;
		 	$action_scope = array('national','regional');
	  	  	$agenda_store_join = " LEFT JOIN {field_data_field_agenda_store} agenda_store ON agenda_store.entity_id = n.nid ";
	  	  	$agenda_store_condition = " OR ((action_scope.field_action_scope_of_content_value <> 'regional') OR (agenda_store.field_agenda_store_value ~ '". $agenda_store ."' AND action_scope.field_action_scope_of_content_value = 'regional'))) ";
		}
		else{
			$in_agenda_type = array();
			if($_SESSION['manage_content_agenda_type']['alert']!='0'){
				array_push($in_agenda_type,'alert');
			}
			if($_SESSION['manage_content_agenda_type']['news']!='0'){
				array_push($in_agenda_type,'news');
			}
			if($_SESSION['manage_content_agenda_type']['benchmark']!='0'){
				array_push($in_agenda_type,'benchmark');
			}
			$in_agenda_type_filter = implode("','", array_filter($in_agenda_type));
			if($_SESSION['manage_content_agenda_type']['action']=='0'){
				$agenda_type_filter = " AND n.type IN ('$in_agenda_type_filter')";
			}else{
				$agenda_type_filter = " AND ( n.type IN ('$in_agenda_type_filter')";
				$agenda_store = $user_selected_store;
				$agenda_store_join = " LEFT JOIN {field_data_field_agenda_store} agenda_store ON agenda_store.entity_id = n.nid ";
  	  			$agenda_store_condition = " OR ((action_scope.field_action_scope_of_content_value <> 'regional') OR (agenda_store.field_agenda_store_value ~ '". $agenda_store ."' AND action_scope.field_action_scope_of_content_value = 'regional')) )";
			}
		}
	}else{
		if(($_SESSION['manage_content_agenda_type']['alert']=='0' && $_SESSION['manage_content_agenda_type']['news']=='0' && $_SESSION['manage_content_agenda_type']['benchmark']=='0') && (isset($_SESSION['manage_action_scope']) && $_SESSION['manage_action_scope']!='0')){
			if(isset($_SESSION['manage_action_scope']) && $_SESSION['manage_action_scope']) {
				$agenda_store = $user_selected_store;  	
		  		$action_scope_filter.= "  AND (n.type='action' AND action_scope.field_action_scope_of_content_value = '".$_SESSION['manage_action_scope']."')";
		  		$agenda_store_join = " LEFT JOIN {field_data_field_agenda_store} agenda_store ON agenda_store.entity_id = n.nid ";
		  		$agenda_store_condition = " AND ((agenda_store.field_agenda_store_value ~ '". $agenda_store ."'))";//Fixed the query for FATIM-622
		  	}
		}else{
			$in_agenda_type = implode("' , '", array_filter($_SESSION['manage_content_agenda_type']));
			if(isset($_SESSION['manage_action_scope']) && $_SESSION['manage_action_scope']) {  	
		  		$action_scope_filter.= "  AND (n.type='action' AND action_scope.field_action_scope_of_content_value = '".$_SESSION['manage_action_scope']."')";
		  	}
		  	$agenda_type_filter = " OR n.type IN ('$in_agenda_type')";
		}
	}
  }
 
  $search_query = "SELECT DISTINCT ON (tab.nid) nid,
                                      tab.title,
                                      tab.agendadate, 
                                      tab.node_type, 
                                      tab.status,
                                      tab.department,
                                      tab.destin,
                                      tab.source,
                                      tab.content_scope,
                                      tab.pubdate,
                                      tab.draft_status,
                                      tab.node_archive,
                                      tab.workbench_status,
                                      tab.agenda_store
                      FROM 
                      (SELECT n.nid as nid,
                              n.title,
                              agenda_date.field_agenda_date_value agendadate,
	   						  n.type node_type, 
	   						  n.status status,
	   						  term.name department,
	   						  aj_conc.field_agenda_concernees_value destin,
	   						  aj_source.field_agenda_source_value source,
	   						  publ_from.field_publication_from_date_value pubdate,
	   						  action_scope.field_action_scope_of_content_value content_scope,
	   						  aj_draft_status.field_draft_status_value draft_status,
	   						  aj_node_archive.field_node_archive_value node_archive,
	   						  workbench_status.state workbench_status,
	   						  aj_agenda_store.field_agenda_store_value agenda_store
					   FROM {node} n 
                       INNER JOIN {field_data_field_agenda_date agenda_date} ON(n.nid = agenda_date.entity_id) 
                       INNER JOIN {field_data_field_publication_from_date} publ_from ON(n.nid=publ_from.entity_id) 
                       INNER JOIN {field_data_field_publication_to_date} publ_to ON(n.nid=publ_to.entity_id) 
                       LEFT JOIN  {field_data_field_agenda_info} inf ON(n.nid=inf.entity_id)
                       LEFT JOIN {field_data_field_agenda_department} deptmnt ON(n.nid=deptmnt.entity_id) 
                       LEFT JOIN {taxonomy_term_data} term ON(deptmnt.field_agenda_department_tid=term.tid)
                       LEFT JOIN {field_data_field_agenda_concernees} aj_conc ON(n.nid=aj_conc.entity_id)
                       LEFT JOIN {field_data_field_agenda_source} aj_source ON(n.nid=aj_source.entity_id)
                       LEFT JOIN {field_data_field_draft_status} aj_draft_status ON(n.nid=aj_draft_status.entity_id)
                       LEFT JOIN {field_data_field_node_archive} aj_node_archive ON(n.nid=aj_node_archive.entity_id)
                       LEFT JOIN {workbench_moderation_node_history} workbench_status ON n.nid=workbench_status.nid AND workbench_status.current=1
                       LEFT JOIN {field_data_field_action_scope_of_content} action_scope ON(n.nid=action_scope.entity_id)
                       LEFT JOIN {field_data_field_agenda_store} aj_agenda_store ON(n.nid=aj_agenda_store.entity_id)";
  					   if(isset($agenda_store_join)){
  					   	$search_query.= $agenda_store_join;
  					   }
                       $search_query.=" WHERE $agenda_date_filter
  					   $agenda_type_filter                       
                       $agenda_department_filter
                       $agenda_status_filter                    
                       $agenda_roles_filter 
                       $text_search_filter 
                       $action_scope_filter
                       ";
 					   if(!empty($pve_code_list)){
                       		$search_query.="AND n.nid IN ($pve_code_list) ";
                       }
					   if(!in_array('administrator',$user->roles) && !in_array('technical_director',$user->roles) && !in_array('content_manager_action',$user->roles) && !in_array('content_manager_action_regional',$user->roles)){
  					   		$search_query.="AND n.uid='$user->uid' ";
  					   }
  					   if(isset($agenda_store_condition)){
  					   		$search_query.=$agenda_store_condition;
  					   }
                       $search_query.="ORDER BY (case when n.type = 'alert' then 1 
                                      when n.type = 'action' then 2
                                      when n.type = 'news' then 3
                                      when n.type = 'benchmark' then 4
                                      end),
                        inf.field_agenda_info_value,term.weight) as tab ";
  $result = db_query($search_query);
  $node_status = "";                 
  $table_header = array(t('Serial'), 
                     t('Start Date'),
                     t('Type'),
                     t('Status'),
                     t('Department'),
                     t('Destinataires'),
                     t('Publication'),
                     t('Type'),
                     t('No of Stores'),
                     t('Profiles'),
                     t('Author'),
                     t('Title'),
                     t('Edit')
                    );
  $i=1;
  $table_rows = array();  
  $agenda_scope = '';
  foreach ($result as $agenda) {
   $today_date = strtotime(date('Y-m-d'));
   $agenda_pubfromdate = strtotime(date('Y-m-d', strtotime($agenda->pubdate)));
   if($agenda->draft_status == '1' && $agenda->node_archive == '0' && $agenda->status == '0'){
   		$node_status = t('Drafts');
   }
   elseif($agenda->draft_status == '0' && $agenda->node_archive == '0' && $agenda->status == '0' && $agenda->node_type == 'action' && $agenda->workbench_status == 'needs_review'){
    	$node_status = t('Needs Review');
   }
   elseif($agenda->draft_status == '0' && $agenda->node_archive == '1' && $agenda->status == '0'){
    	$node_status = t('Archive');
   }
   elseif(($agenda->draft_status == '0' && $agenda->node_archive == '0' && $agenda->status == '1') && ($agenda_pubfromdate <= $today_date)){
    	$node_status = t('Published');
   }
   elseif(($agenda->draft_status == '0' && $agenda->node_archive == '0' && $agenda->status == '1') && ($agenda_pubfromdate > $today_date)){
	  	$node_status = t("Publication Possible");
   }
   if($agenda->node_type == 'action'){
	   if($agenda->content_scope == 'national'){
	   		$agenda_scope = t('National');
	   }else if($agenda->content_scope == 'regional'){
	   		$agenda_scope = t('Regional');
	   }
   }else{
   		$agenda_scope = '';
   }
   $agenda_stores_array = explode(",", $agenda->agenda_store);
   $agendanos = count($agenda_stores_array);
   $node = node_load($agenda->nid);
   $attached_profiles = $node->field_attached_regional_profiles['und'][0]['value'];
   // Fix for UATIM-624
   $agenda->source = explode('(',$agenda->source);
   $author_name = $agenda->source[0];
  	$table_rows[] = array(
	    array('data' => $i, 'class' => array('serial')),
	    array('data' => date('d/m/Y', strtotime($agenda->agendadate)), 'class' => array('date')),
	    array('data' => $agenda->node_type, 'class' => array('type')),
	    array('data' => $node_status, 'class' => array('status')),
	    array('data' => $agenda->department, 'class' => array('department')),
	    array('data' => $agenda->destin, 'class' => array('destinators')),
	    array('data' => date('d/m/Y', strtotime($agenda->pubdate)), 'class' => array('publication')),
	    array('data' => $agenda_scope),
	    array('data' => $agendanos, 'class' => array('stores')),
	    array('data' => $attached_profiles, 'class' => array('profiles')),
	    array('data' => $author_name, 'class' => array('author')),
	    array('data' => $agenda->title, 'class' => array('title')),
	    array('data' => l(t('edit'),'node/'.$agenda->nid.'/edit'), 'class' => array('edit'))
    );
    $i++;
    $node_status = "";
  }
  $output = theme_table(array(
        'header' =>  $table_header, 
        'rows' => $table_rows,
        'attributes' => array('class' => 'table_manage_agenda', 'width' => '100%'),
        'caption' => '',
        'colgroups' => array(),
        'sticky' => FALSE,
        'empty' => t('No data is available'),
    )); 
    
  return $output;
}

/**
 * To list all the DO(s) or DR/CF items
 */

function _im_agenda_manage_content_list_dos_dr_cf($item_code){
	$list_dos = array();
	$result = db_select('store_item_fields','sf')
		->condition('sf.dit_cod_item',$item_code, '=')
		->fields('sf', array('ite_lib_value'))
		->distinct()
		->orderBy("ite_lib_value", "ASC")		
		->execute();
	foreach ($result as $dos) {
		$list_dos[] = $dos->ite_lib_value;
	}
	return $list_dos;
}