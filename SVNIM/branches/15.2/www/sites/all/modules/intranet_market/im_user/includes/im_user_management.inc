<?php
/**
 * 
 *  Function to bulid the search user and add user.
 */
function im_user_management() {
  drupal_add_js(drupal_get_path('module', 'im_user') . '/js/im_user_validations.js');
  drupal_add_js(drupal_get_path('module', 'im_rmp') . '/js/im_rmp.js');
  drupal_add_css(drupal_get_path('module', 'im_features_stores') . '/css/im_features_stores.css');
  drupal_add_css(drupal_get_path('module', 'multiselect') . '/multiselect.css');
  drupal_add_js(drupal_get_path('module', 'multiselect') . '/multiselect.js');
  drupal_add_js('misc/tabledrag.js'); 
//  drupal_add_css(drupal_get_path('module', 'im_agenda') . '/css/im_agenda.css');    
  $build['user_filter_form'] = drupal_get_form('im_user_management_filter_form');
  $build['user_admin_account'] = drupal_get_form('im_user_mangement_list_form');
  return $build;
}
/**
 * Serach users filter form
 */
function im_user_management_filter_form($form, &$form_state) {
  global $user;
  $uid = $user->uid;
  if(!empty($_SESSION['user_management'][$uid]['user_crfr_market']) && $_SESSION['user_management'][$uid]['user_crfr_market'] == 1){
  	$carrefour_market = 1;
  }
  else {
  	$carrefour_market =0;
  }
  $form['user_management']['user_back_url'] = array(
    '#type' => 'link',
    '#title' => t('Back'),
    '#href' => 'admin/im/user/dashboard', 
    '#attributes' => array('class' => "button-orange"),
  );
  $form['user_management']['user_first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#default_value' => isset($_SESSION['user_management'][$uid]['first_name']) ? $_SESSION['user_management'][$uid]['first_name'] : '',
  );
  $form['user_management']['user_last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#default_value' => isset($_SESSION['user_management'][$uid]['last_name']) ? $_SESSION['user_management'][$uid]['last_name'] : '',
  );
  $form['user_management']['user_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Address'),
    '#default_value' => isset($_SESSION['user_management'][$uid]['email']) ? $_SESSION['user_management'][$uid]['email'] : '',
  );
  $form['user_management']['user_crfr_market'] = array(
    '#type' => 'checkbox',
    '#title' => t('Search for Carrefour Market User Only'),
    '#default_value' => $carrefour_market,
  );
  $form['user_management']['user_serach'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
  );
  $form['user_management']['user_reset'] = array(
    '#type' => 'link',
    '#title' => t('Reset'),
    '#href' => 'admin/im/user/add',
    //'#value' => t('Reset'),
     //'#submit' => array('im_user_reset_submit'),
  );
  regional_profile_popup_settings();
  $rmp = '<div id="rmp_popup" style="display:none">' . ctools_modal_text_button(t('Define regional moderator profiles'), 'rmp/nojs/regional_moderator_profile_form/add-rmp-user', t('Define regional moderator profiles'),  'ctools-modal-ctools-sample-style') . '</div>';
  $form['user_management']['usp_form'] = array(
    '#type' => 'item',
    '#markup' => $rmp,
  );
  return $form;
}
/**
 * 
 * Search user validate form
 */

function im_user_management_filter_form_validate($form, &$form_state) {
  if (empty($form_state['values']['user_first_name']) && empty($form_state['values']['user_last_name']) && empty($form_state['values']['user_email'])) {
      form_set_error(' ', "Please enter the value for any one of the field.");
  }
  if (!empty($form_state['values']['user_first_name']) && (empty($form_state['values']['user_last_name']) && empty($form_state['values']['user_email']))) {
      form_set_error(' ', "Please enter the value for Last name or Email.");
  }
  if(!empty($form_state['values']['user_email'])){
    $reg_exp = "/^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{1,3}$/";
	  if (!preg_match($reg_exp, $form_state['values']['user_email'])) {
	   form_set_error('user_email', t('Please enter the valid email address'));
	  }
  }  
}
/**
 * 
 * Search users submit form -submit handler
 */

function im_user_management_filter_form_submit($form, &$form_state) {
  global $user;
  $uid = $user->uid;
  $form_state['rebuild'] = TRUE;
  unset($_SESSION['user_management'][$uid]['first_name']);
  unset($_SESSION['user_management'][$uid]['last_name']);
  unset($_SESSION['user_management'][$uid]['email']);
  unset($_SESSION['user_management'][$uid]['user_crfr_market']);
  unset($_SESSION['user_management'][$uid]['total_result_count']);	
  if (!empty($form_state['values']['user_first_name'])) {
    $_SESSION['user_management'][$uid]['first_name'] = $form_state['values']['user_first_name'];	
  }
  if (!empty($form_state['values']['user_last_name'])) {
    $_SESSION['user_management'][$uid]['last_name'] = $form_state['values']['user_last_name'];	
  }
  if (!empty($form_state['values']['user_email'])) {
    $_SESSION['user_management'][$uid]['email'] = $form_state['values']['user_email'];	
   }
  if (!empty($form_state['values']['user_crfr_market']) && $form_state['values']['user_crfr_market'] == TRUE) {
    $_SESSION['user_management'][$uid]['user_crfr_market'] = 1;
  }
}
/**
 * 
 * Reset handler for the filter form ...
 */
function im_user_reset_submit($form, &$form_state) {
	$form_state['values']['user_first_name'] = " ";
	$form_state['values']['user_last_name'] = " ";
	$form_state['values']['email'] = " ";
	unset($_SESSION['user_management'][$uid]['first_name']);
    unset($_SESSION['user_management'][$uid]['last_name']);
    unset($_SESSION['user_management'][$uid]['email']);
    unset($_SESSION['user_management'][$uid]['user_crfr_market']);
    unset($_SESSION['user_management'][$uid]['total_result_count']);	
}
/**
 * 
 * Serach User result list form
 */
function im_user_mangement_list_form($form, &$form_state) {	
  global $user;
  $uid = $user->uid;
  $form['user_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#attributes' => array('class' => array('container-inline')),
  );
  include_once drupal_get_path('module', 'im_user'). '/includes/im_user_dashboard.inc';
  $roles = _get_all_roles();
  foreach ($roles as $key => $val) {
  	if ($val != "visitor") {
  	  $user_roles[$val] = $val;	
  	}  	
  }
  $options = array('Select');
  $options['Add back office role to the selected users'] = $user_roles;	
  $options['Add the front office role to the selected users'] = array('visitor' => 'visitor');
  
  $form['user_list']['update_options'] =array(
    '#type' => 'select',
    '#title' => t('Update options'),
    '#title_display' => 'invisible',
    '#options' => $options,    
  );
  $form['user_list']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );
  $header= array(
    'mail' => array('data' => t('Email')),
    'matricule' => array('data' => t('Matricule')),  
    'complete_name' => array('data' => t('Complete Name')),
    'type' => array('data' => t('Type')),   
   );
   $options = array();
  if(!empty($_SESSION['user_management'][$uid]['user_crfr_market']) && $_SESSION['user_management'][$uid]['user_crfr_market'] == 1){
  	$carrefour_market = 1;
  }
  else {
  	$carrefour_market = 0;
  }
  $user_details = _im_user_retrive_details();
  if (isset($user_details) && !empty($user_details)) {
    for ($u = 0; $u < count($user_details); $u++ ) {
      if (!empty($user_details[$u]['mail'])) {
        $options[$user_details[$u]['loginID']] = array('mail' => $user_details[$u]['mail'],'complete_name' => $user_details[$u]['cn'],'type' => $user_details[$u]['type'], 'matricule' => $user_details[$u]['matricule']); //, 'first_name' => $user_details[$u]['givenName']
      } 
    }
  } 
   $form['accounts'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No people available.'),
  );
  $search_result_count = isset($_SESSION['user_management'][$uid]['total_result_count']) ? $_SESSION['user_management'][$uid]['total_result_count'] : ""; 
  pager_default_initialize($search_result_count, 10);
    $args = array('quantity' => 6,'tags' => array('First','<','','>','Last'));
    $form['users_list'] = array(
  	  '#type' => 'markup',
      '#markup' => theme('pager',$args), 
    ); 
//  $form['pager'] = array('#markup' => theme('pager')); 
  return $form;	
}

/**
 * Serach User result list form validate
 * @param $form array
 * @param $form_state array
 */
function im_user_mangement_list_form_validate($form, &$form_state) {
  $user_details = _im_user_retrive_details();
  if (count($form_state['values']['accounts']) == 0) {
    if (count($user_details) > 0) {
      form_set_error('', t("Please select any people"));
    }
    else if (count($user_details) == 0) {
      form_set_error('', t("No people available."));
    } 
  }
  
  if (($form_state['values']['update_options'] == "0" || empty($form_state['values']['update_options'])) && count($user_details) >0 ) {
    form_set_error('update_options', t("Please select the update option"));
  }
}
/**
 * 
 * Search users result list form - submit handler
 *  * 
 */  
function im_user_mangement_list_form_submit($form, &$form_state) {
 // global $user;
  //$user_mail = $user->name;
  $user_list = array();  
  foreach ($form_state['values']['accounts'] as $key => $value) {
    if (strlen($form_state['values']['accounts'][$key]) > 1) {
	  $user_list[$key] = $form_state['values']['accounts'][$key];
	 }
  }
  $selected_options = $form_state['values']['update_options'];
  foreach ($user_list as $user_id) {
    $user_details = _getUserAttributs($user_id);
    $query = db_select('users','users');
    $query->join('users_roles','roles','users.uid=roles.uid');
    $register_id = !empty($user_details['employeeNumber']) ? trim($user_details['employeeNumber']):trim($user_details['uid']);
    $result = $query->fields('users', array('uid'))
    				->condition('name', db_like($register_id), 'LIKE')
    				->range(0, 1)
    				->execute()
    				->fetchField();
    if ((bool)$result){
    	$userProf = user_load($result);
		  $rid = db_query("SELECT rid FROM {role} WHERE name = :role_name", array(':role_name' => $selected_options))->fetchField();
		  $userProf->roles[$rid] = $selected_options;  
		  user_save($userProf);
		  drupal_set_message(t("Updated the selected users"));
		  
      return;
    }else{
    	$rid = db_query("SELECT rid FROM {role} WHERE name = :role_name", array(':role_name' => $selected_options))->fetchField();
	    if ($rid) {
	    	module_load_include('inc', 'im_user', 'includes/im_user_homepage');
	    	_im_user_external_login_register($user_details,$register_id, 'im_user_dashboard');
		    $userProf = user_external_load($register_id); 
		    $userProf->roles[$rid] = $selected_options;  
		    $userProf->field_full_name[LANGUAGE_NONE][0]['value']  = $user_details['cn'];
		    $userProf->mail  = $user_details['mail'];
		    user_save($userProf); 
		   drupal_set_message(t("Added the selected users"));
	    }
    }
  }
  //Revert User.
  //user_external_login_register($user_mail, 'im_user');
  //$account = user_external_load($user_mail);
  drupal_goto("admin/im/user/dashboard");
} 
/**
 * 
 * Function to retrive the users by searchUsers method.
 */
function _im_user_retrive_details() {
  global $user;
  $uid = $user->uid;
  $user_details = array();
  $ladp_id = '';
  $carrefour_market = 0;
  if (isset($_SESSION['ldap_login_key'])) {
    $ladp_id = $_SESSION['ldap_login_key'];
  }
  $j =0;
  if (!empty($_SESSION['user_management'][$uid]['first_name'])) {
    $attribute_type[$j] = 'givenName';
	$attribute_value[$j] = $_SESSION['user_management'][$uid]['first_name'] . '*';
	$j++;
  }
  if (!empty($_SESSION['user_management'][$uid]['last_name'])) {
    $attribute_type[$j] = 'sn';
	$attribute_value[$j] = $_SESSION['user_management'][$uid]['last_name'] . '*';
	$j++;
  }
  if (!empty($_SESSION['user_management'][$uid]['email'])) {
    $attribute_type[$j] = 'mail';
	$attribute_value[$j] = $_SESSION['user_management'][$uid]['email'];
	$j++;	
  } 
  if(!empty($_SESSION['user_management'][$uid]['user_crfr_market']) && $_SESSION['user_management'][$uid]['user_crfr_market'] == 1){
  	$carrefour_market = 1;
  	$attribute_type[$j] = 'eduPersonOrgUnitDn';
	$attribute_value[$j] = 'cn=0002,cn=mng,ou=thales,ou=organizations,dc=fr,dc=carrefour,dc=com';
	$j++;
  }
  /*unset($_SESSION['user_management'][$uid]['first_name']);
  unset($_SESSION['user_management'][$uid]['last_name']);
  unset($_SESSION['user_management'][$uid]['email']);
  unset($_SESSION['user_management'][$uid]['user_crfr_market']);
  unset($_SESSION['user_management'][$uid]['total_result_count']);	*/
  $user_id = array();
  $_SESSION['user_management'][$uid]['total_result_count'] = 0;
  if (isset($attribute_type) && isset($attribute_value)) {
    $attribute_type[$j] = 'inetUserStatus';
    $attribute_value[$j] = 'active';
    $j++;
    $obj = new imldapSoapService();
    $response = $obj->soapRequest('searchUsers', array('id' => $ladp_id, 'login' => '*', 'attributsType' => $attribute_type, 'attributsValue' => $attribute_value ));
    if ($response->status == "success") {
      if (count($response->data) > 1) {
      	$_SESSION['user_management'][$uid]['total_result_count'] = count($response->data);
      	$page_start = isset($_REQUEST['page']) ?  $_REQUEST['page']*10 : 0;      	 
      	$user_id = array_slice($response->data, $page_start, 10);
      }
       else {
      	$_SESSION['user_management'][$uid]['total_result_count'] = 1;
        $user_id[$response->data] = $response->data;	
        }
      } 	
    }    
  $cc =0;
  
  if (!empty($user_id)) {
    foreach ($user_id as $key => $value) {
      $obj = new imldapSoapService();
      $response = $obj->soapRequest('getUserAttributs', array('id' => $ladp_id, 'login' => $value, 'attributsType'=> array('givenName', 'cn', 'mail', 'eduPersonOrgUnitDn', 'employeeNumber'),  'pad' => ' '));
      if ($response->status == "success") {
        $user_details[$cc]['givenName'] = trim($response->data[0]);
        $user_details[$cc]['cn'] = trim($response->data[1]);
        //$user_details[$cc]['mail'] = trim($response->data[2]);
        $user_details[$cc]['mail'] = current(explode(' ', trim($response->data[2])));
        $eduPersonOrgUnitDn = trim($response->data[3]);
        $user_details[$cc]['matricule'] = trim($response->data[4]);
        $user_details[$cc]['eduPersonOrgUnitDn'] = trim($eduPersonOrgUnitDn);
        $is_carrefour_market_user = im_is_carrefour_market(trim($eduPersonOrgUnitDn));
	    if ($is_carrefour_market_user) {
	      $user_details[$cc]['type'] = "Market";		      	
	     } else {
	         $user_details[$cc]['type'] = "";
	       }
        $user_details[$cc]['loginID'] = $value;
     }
     $cc++;      	
    } 		 
  }
  return $user_details;    
}
/**
 * 
 * Function to check the user is carrefour market user or not..
 * @param string $eduPersonOrgUnitDn : input string to find the user role
 * return Boolean : TRUE?FALSE
 */
function im_is_carrefour_market($eduPersonOrgUnitDn) {
  $carrefour_market = 'cn=0002,cn=mng,ou=thales,ou=organizations,dc=fr,dc=carrefour,dc=com';
  $carrefour_market_role = strstr($eduPersonOrgUnitDn, $carrefour_market);
  if(is_string($carrefour_market_role)){
  	return TRUE;
  }
  else {
  	return FALSE;
  }
}
