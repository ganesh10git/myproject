<?php
function im_user_dmd_assignment(){
  return drupal_get_form('im_user_dmd_assignment_form');	
}

function im_user_dmd_assignment_form(){
  global $user;
  $form =array();
  $format = 'd-m-Y';
  $search_result = '';
  $store_name = get_dmd_store_name();
  dmd_validate_edit();
  
	drupal_add_css(drupal_get_path('module', 'im_user') . '/css/im_user_dmd_assignment.css');
  drupal_add_js(drupal_get_path('module', 'im_user') . '/js/im_user_dmd_assignment.js');
  //Removed as per UATIM-492
/*  if($store_name) {
    $form['dmd_store'] = array(
      '#type' => 'markup',
      '#markup' => t('DMD assignment for ') . $store_name, 
      );
  }*/
  $form['dmd_first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'), 
    '#default_value' => isset($_SESSION['dmd_search']['first_name']) ? $_SESSION['dmd_search']['first_name'] : '',
    '#required' => FALSE,
    );
  $form['dmd_last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Family Name'), 
    '#default_value' => isset($_SESSION['dmd_search']['last_name']) ? $_SESSION['dmd_search']['last_name'] : '',
    '#required' => FALSE,
    );
  $form['dmd_employee_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Employee Id'), 
    '#default_value' => isset($_SESSION['dmd_search']['employee_number']) ? $_SESSION['dmd_search']['employee_number'] : '',
    '#required' => FALSE,
    );
  $form['dmd_search'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#submit' => array('_dmd_search_user_submit'),
	'#validate' => array('_dmd_search_user_validate'),
    );
  $form['dmd_cancel'] = array(
    '#type' => 'markup',
    '#markup' => l(t('Cancel'), 'admin/im/user/dmd-assignment'), 
    );
  $dmd_search_result = empty($_SESSION['messages']['error']) ? get_dmd_search_result() : array();
  $search_result_count = isset($dmd_search_result['count']) ? $dmd_search_result['count'] : 0;
  $dmd_search_result_mails = array();
  $dmd_search_result_names = array();
  array_shift($dmd_search_result);
  if($search_result_count){
  	foreach ($dmd_search_result as $result) {
  	  $dmd_search_result_mails[$result['uid']] = isset($result['mail']) ? $result['mail'] : '';
  	  $dmd_search_result_names[$result['uid']] = isset($result['name']) ? $result['name'] : '';
  	  $dmd_search_result_uid[$result['uid']] = isset($result['uid']) ? $result['uid'] : '';
  	}
  }
  
  $dmd_search_result_default = (sizeof($dmd_search_result_mails) == 1) ? key($dmd_search_result_mails) : '';
  if($search_result_count) {
  	$form['dmd_result_title'] = array(
  	  '#type' => 'markup',
      '#markup' => t('Name'), 
    );
  }
  $page = isset($_REQUEST['page']) ? $_REQUEST['page'] * 10 : 0;
  $form['dmd_search_result'] = array(
    '#type' => 'radios',
    '#options' => $dmd_search_result_names,
    '#default_value' => $dmd_search_result_default,
    );
  if($search_result_count) {
  	$output_email = '<div class="email-ids"><div class="mail-title assignment-search-result-title">'.t('Email').'</div>';
  	foreach($dmd_search_result_mails as $mail){
  		$output_email .= '<div class="mail">'.$mail.'</div>';
  	}
  	$output_email .= '</div>';
  	$form['dmd_search_result_mail'] = array(
      '#type' => 'markup',
      '#markup' => $output_email, 
    );
    $output_uid = '<div class="email-ids"><div class="mail-title assignment-search-result-title">'.t('Employee ID').'</div>';
    foreach($dmd_search_result_uid as $uid){
      $output_uid .= '<div class="mail">'.$uid.'</div>';
    }
    $output_uid .= '</div>';
    $form['dmd_search_result_uid'] = array(
      '#type' => 'markup',
      '#markup' => $output_uid, 
    );
    $form['dmd_begin_date'] = array(
      '#type' => 'date_popup',
      '#title' => t('Start Date'),
      '#date_format' => $format,
      '#default_value' => (isset($_SESSION['dmd_search'][$user->uid]['begin_date']) && $_SESSION['dmd_search'][$user->uid]['begin_date']) ? date('Y-m-d', $_SESSION['dmd_search'][$user->uid]['begin_date']) : date('Y-m-d', time()),
      '#required' => FALSE,
      );
    $form['dmd_end_date'] = array(
      '#type' => 'date_popup',
      '#title' => t('End Date'),
      '#date_format' => $format,
      '#default_value' => (isset($_SESSION['dmd_search'][$user->uid]['end_date']) && $_SESSION['dmd_search'][$user->uid]['end_date']) ? date('Y-m-d', $_SESSION['dmd_search'][$user->uid]['end_date']) : date('Y-m-d', time()),
      '#required' => FALSE,
      );
    
	pager_default_initialize($search_result_count, 10);
    $args = array('quantity' => 6,'tags' => array('First','<','','>','Last'));
    $form['dmd_result_pager'] = array(
  	  '#type' => 'markup',
      '#markup' => theme('pager',$args), 
    ); 
    $assign_modify = (arg(4)) ? 'Update' : 'Add';
    $form['dmd_assign'] = array(
      '#type' => 'submit',
      '#value' => t($assign_modify),
      '#submit' => array('_dmd_add_user_submit'),
	  '#validate' => array('_dmd_add_user_validate'),
      );
  }
  return $form;
}
function _dmd_search_user_validate(&$form, &$form_state){
	$first_name 	= trim($form_state['values']['dmd_first_name']);
    $last_name  	= trim($form_state['values']['dmd_last_name']);
    $employee_id    = trim($form_state['values']['dmd_employee_id']);
    /*
    if(!$first_name) form_set_error(' ', t('Provide First Name'));
    if(!$last_name) form_set_error(' ', t('Provide Family name'));
    if(!$employee_id) form_set_error(' ', t('Provide Employee Number'));
  	*/
    $_SESSION['dmd_search']['first_name'] = $first_name;
    $_SESSION['dmd_search']['last_name'] = $last_name;
    $_SESSION['dmd_search']['employee_number'] = $employee_id;
    //$_SESSION['dmd_search'][$user->uid]['begin_date'] = '';
    //$_SESSION['dmd_search'][$user->uid]['end_date'] = '';
	//$form_state['redirect'] = false;
	drupal_goto('admin/im/user/dmd-assignment');
}
function _dmd_search_user_submit(&$form, &$form_state){
	$form_state['redirect'] = false;
}
function _dmd_add_user_validate(&$form, &$form_state){
	global $user;
    if(!$form_state['values']['dmd_search_result']) {
  	  form_set_error('dmd_search_result', t('Select user'));
  	}
    if(!$form_state['values']['dmd_begin_date']) {
  	  form_set_error('dmd_begin_date', t('Provide Begin Date'));
  	}
    if(!$form_state['values']['dmd_end_date']) {
  	  form_set_error('dmd_end_date', t('Provide End Date'));
  	}
  	if($form_state['values']['dmd_search_result'] && $form_state['values']['dmd_begin_date'] && $form_state['values']['dmd_end_date']) {
  	  //Get Firstname, Last Name
  	  $obj = new imldapSoapService();
  	  $ldap_login_key = isset($_SESSION['ldap_login_key']) ? $_SESSION['ldap_login_key'] : '';
      
      $obj = new imldapSoapService();
      
        //Search users 
  $attribute_type = array('0' => 'employeeNumber','1' => 'inetUserStatus' );
  $attribute_value = array('0' => $form_state['values']['dmd_search_result'],'1' => 'active' );
  $searchObj = $obj->soapRequest('searchUsers', array('id' => $ldap_login_key, 'login' => '*', 'attributsType' => $attribute_type, 'attributsValue' => $attribute_value ));
      
     // $searchObj = $obj->soapRequest('searchUsers', array('id' => $ldap_login_key, 'login' => '*', 'attributsType' => 'employeeNumber', 'attributsValue' => $form_state['values']['dmd_search_result']));
      
      $loginFound = (isset($searchObj->data) && is_array($searchObj->data)) ? current($searchObj->data) : $searchObj->data;
      $attrObj = $obj->soapRequest('getUserAttributs', array('id' => $ldap_login_key, 'login' => $loginFound, 'attributsType' => array('givenName', 'sn', 'employeeNumber', 'mail'), 'pad' => ''));
  	  $first_name = isset($attrObj->data[0]) ? $attrObj->data[0] : '';
  	  $last_name  = isset($attrObj->data[1]) ? $attrObj->data[1] : '';
  	  $employee_number = isset($attrObj->data[2]) ? $attrObj->data[2] : '';
  	  $email_id = isset($attrObj->data[3]) ? $attrObj->data[3] : '';
  	  if($form_state['clicked_button']['#value'] == t('Add')) {
  	  	
  	  	$result = db_query("SELECT asid 
  	                       FROM {ldap_role_assignment} 
  	                       WHERE email_assigned_by = :assigned_by
  	                       AND ((assignment_begin_date <= :begindate AND assignment_end_date >= :enddate) 
						     OR (assignment_end_date >= :begindate AND assignment_begin_date <= :enddate )
						       )
						   LIMIT 1", 
  	                       array(
  	                       ':assigned_by' => $user->name,
  	                             ':begindate' => strtotime($form_state['values']['dmd_begin_date']),
  	                       		 ':enddate' => strtotime($form_state['values']['dmd_end_date']),
  	                             )
  	                     );
        if($result) {
       	  $dmdObj = $result->fetchObject();
       	  if(isset($dmdObj->asid) && $dmdObj->asid){
	        form_set_error('dmd_begin_date', t('Delegation exists for this period or part of this period'));
	        form_set_error('dmd_end_date', '');
	        return;
       	  }
	    }
	   
	    $result = db_insert('ldap_role_assignment')
	      ->fields(array('employee_number', 'email', 'first_name', 'last_name', 'email_assigned_by', 'assigned_store', 'assignment_begin_date', 'assignment_end_date'))
	      ->values(array(
	       'employee_number' => $employee_number,
	       'email' => $email_id,
	       'first_name' => $first_name,
	       'last_name' => $last_name,
	       'email_assigned_by' => $user->name,
	       'assigned_store' => '',
	       'assignment_begin_date' => strtotime($form_state['values']['dmd_begin_date']),
	       'assignment_end_date' => strtotime($form_state['values']['dmd_end_date'])))
	     ->execute();
	    if($result) {
	      $_SESSION['dmd_search']['first_name'] = '';
    	  $_SESSION['dmd_search']['last_name'] = '';
          $_SESSION['dmd_search']['employee_number'] = '';
  	  	  drupal_set_message('Selected user is given DM Role');
  	  	} else {
  	  	  drupal_set_message('unable to insert data', 'warning');
  	  	} 
  	  }else if($form_state['clicked_button']['#value'] == t('Update')) {
  	  	//IS User USER EXIST IN THE SAME PERIOD
  	  	
  	   $result = db_query("SELECT asid 
  	                       FROM {ldap_role_assignment} 
  	                       WHERE email_assigned_by = :assigned_by
  	                       AND asid != :asid
  	                       AND ((assignment_begin_date <= :begindate AND assignment_end_date >= :enddate) 
						     OR (assignment_end_date >= :begindate AND assignment_begin_date <= :enddate )
						       )
						   LIMIT 1", 
  	                       array(':assigned_by' => $user->name,
  	                             ':begindate' => strtotime($form_state['values']['dmd_begin_date']),
  	                       		 ':enddate' => strtotime($form_state['values']['dmd_end_date']),
  	                             ':asid' => arg(4)
  	                             )
  	                     );
       if($result) {
       	 $dmdObj = $result->fetchObject();
       	 if(isset($dmdObj->asid) && $dmdObj->asid){
	       form_set_error('dmd_begin_date', t('Record exist for the same period'));
	       form_set_error('dmd_end_date', '');
	       return;
       	 }
	   }
  	   $result = db_query("UPDATE {ldap_role_assignment} 
  	  	                    SET employee_number = :employee_number,
  	  	                        first_name = :first_name,
  	  	                        last_name = :last_name,
  	  	                        assignment_begin_date = :begin_date, 
  	  	                        assignment_end_date = :end_date 
  	  	                    WHERE asid = :asid", 
  	  	                        array(':employee_number' => $employee_number,
  	  	                              ':first_name' => $first_name,
  	  	                              ':last_name' => $last_name,
  	  	                              ':begin_date' => strtotime($form_state['values']['dmd_begin_date']), 
  	  	                              ':end_date' => strtotime($form_state['values']['dmd_end_date']), 
  	  	                              ':asid' => arg(4)
  	  	                             )
  	  	                  );
  	  	if($result) {
  	  	  $_SESSION['dmd_search']['first_name'] = '';
    	  $_SESSION['dmd_search']['last_name'] = '';
          $_SESSION['dmd_search']['employee_number'] = '';
  	  	  drupal_set_message('data has been modified');
  	  	} else {
  	  	  drupal_set_message('unable to update data', 'warning');
  	  	}
  	  	drupal_goto('admin/im/user/dmd-assignment');
  	  }
	}
	$form_state['redirect'] = false;
}
function _dmd_add_user_submit(&$form, &$form_state){
	$form_state['redirect'] = false;
}

function get_dmd_search_result(){	
	global $user;
	$user_attributes = array();
    $first_name = isset($_SESSION['dmd_search']['first_name']) ? $_SESSION['dmd_search']['first_name'] : '';
    $last_name = isset($_SESSION['dmd_search']['last_name']) ? $_SESSION['dmd_search']['last_name'] : '';
    $employee_id = isset($_SESSION['dmd_search']['employee_number']) ? $_SESSION['dmd_search']['employee_number'] : '';
    
    if(!empty($last_name) || !empty($employee_id)){
    	$attribute_type = array();
	    $attribute_value= array();
	    $index = 0;
	    if ($first_name) {
	      $attribute_type[$index] = 'givenName';
		  $attribute_value[$index] = trim($first_name) . '*';
		  $index++;
	    }
		if($last_name) {
		  $attribute_type[$index] = 'sn';
		  $attribute_value[$index] = trim($last_name) . '*';
		  $index++;
		}
		if($employee_id) {
		  $attribute_type[$index] = 'employeeNumber';
		  $attribute_value[$index] = trim($employee_id) . '*';
		  $index++;
		}
		$attribute_type[$index] = 'inetUserStatus';
		$attribute_value[$index] = 'active';
		
		$ldap_login_key = isset($_SESSION['ldap_login_key']) ? $_SESSION['ldap_login_key'] : '';
	    $obj = new imldapSoapService();
	    $searchObj = $obj->soapRequest('searchUsers', array('id' => $ldap_login_key, 'login' => '*', 'attributsType' => $attribute_type, 'attributsValue' => $attribute_value));
	    if(isset($searchObj->data)) {
	      $uids = array();
	      if(isset($searchObj->data)) {
	      	$uids = is_array($searchObj->data) ? $searchObj->data : array($searchObj->data);
	      }
	      $uids = array_filter($uids);
	      $user_attributes['count']   = sizeof($uids);
	      $page = isset($_REQUEST['page']) ? $_REQUEST['page'] * 10 : 0;
	      $uids = array_slice($uids, $page,10);
	      
	      foreach ($uids as $uid){
	      	$attrObj = $obj->soapRequest('getUserAttributs', array('id' => $ldap_login_key, 'login' => $uid, 'attributsType' => array('mail', 'cn'), 'pad' => ' '));
	      	if(isset($attrObj->data)) {
	      	  $email = current(explode(' ', trim($attrObj->data[0])));
	      	  $user_attributes[] = array('mail' => $email, 'name' => trim($attrObj->data[1]), 'uid' => $uid);
	      	}
	      }
	    }
    }
  return $user_attributes;
}

function im_user_dmd_assigned_block() {
	global $user;
	$table_rows = array();
	$table_header = array(
	                   /*t('Full Name'),*/
	                   t('First Name'),t('Last Name'),
                     t('Employee Id'),
                     t('Status'),
                     t('Start Date'),
                     t('End Date'),
                     t(''),
                    );
  $result = db_query("(SELECT * 
                      FROM {ldap_role_assignment} 
                      WHERE email_assigned_by = :assigned_email
                      AND assignment_end_date >= :today)
                      UNION
                      (SELECT * 
                      FROM ldap_role_assignment 
                      WHERE email_assigned_by = :assigned_email
                      AND assignment_end_date < :today
                      ORDER BY assignment_end_date DESC
                      LIMIT 1)
                      ORDER BY assignment_end_date DESC
                      ", 
                      array(':assigned_email' => $user->name,
                            ':today' => strtotime(date('Y-m-d',time()))   
                            )
                     );
  foreach ($result as $assigned) {
  	$time = time();
    $status = '';
  	if(date('Y-m-d', $assigned->assignment_begin_date) > date('Y-m-d', $time)) {
  	  $status = 'Future';
  	}else if(date('Y-m-d', $assigned->assignment_end_date) < date('Y-m-d', $time)) {
  	  $status = 'Past';
  	}else if(date('Y-m-d', $assigned->assignment_begin_date) <= date('Y-m-d', $time) &&  date('Y-m-d', $time) <= date('Y-m-d', $assigned->assignment_end_date)) {
  	  $status = 'Active';
  	}
  	$edit = ($status != 'Past') ? l(t('Edit'), 'admin/im/user/dmd-assignment/' . $assigned->asid) : '';
  	$table_rows[] = array(
  	  //array('data' => $assigned->first_name . ' ' . $assigned->last_name, 'class' => array('fullname')),
  	  array('data' => $assigned->first_name, 'class' => array('fname')),
  	  array('data' => $assigned->last_name, 'class' => array('lname')),
	    array('data' => $assigned->employee_number, 'class' => array('mail')),
	    array('data' => $status, 'class' => array('status')),
	    array('data' => date('d/m/Y', $assigned->assignment_begin_date), 'class' => array('begin-date')),
	    array('data' => date('d/m/Y', $assigned->assignment_end_date), 'class' => array('end-date')),
	    array('data' => $edit, 'class' => array('edit')),
    );
  }
  $output = theme_table(array(
        'header' =>  $table_header, 
        'rows' => $table_rows,
        'attributes' => array('class' => 'table_dmd', 'width' => '100%'),
        'caption' => '',
        'colgroups' => array(),
        'sticky' => FALSE,
        'empty' => 'No data is available',
    )); 
    
  return $output;
}

function dmd_validate_edit() {
  global $user;
  $asid = arg(4);
  if($asid) {
  	$result = db_query("SELECT * FROM {ldap_role_assignment} WHERE asid = :asid", array(':asid' => $asid));
    if($result) {
	  $dmdObj = $result->fetchObject();
	  $_SESSION['dmd_search']['first_name'] = $dmdObj->first_name;
      $_SESSION['dmd_search']['last_name'] = $dmdObj->last_name;
      $_SESSION['dmd_search']['employee_number'] = $dmdObj->employee_number;
      $_SESSION['dmd_search'][$user->uid]['begin_date'] = $dmdObj->assignment_begin_date;
      $_SESSION['dmd_search'][$user->uid]['end_date'] = $dmdObj->assignment_end_date;
	}
  }
}

function get_dmd_store_name() {
  global $user;
  $storeId = '';
  $store_name = '';
  $user_profile = user_load($user->uid);
  if(isset($user_profile->field_user_stores['und'][0]['value'])) {
  	$storeId = current(explode(',', $user_profile->field_user_stores['und'][0]['value']));
  }	
  if($storeId) {
  	$result = db_query("SELECT sif.ite_lib_value AS name
                        FROM {store_item_fields} sif 
                        WHERE sif.dit_cod_item = 'thales'
                        AND  sif.pve_code= :storeId",
                        array(':storeId' => $storeId)
                       );
	if($result) {
	  $store = $result->fetchObject();
	  $store_name = $store->name;
	}
  }
  return $store_name;
}