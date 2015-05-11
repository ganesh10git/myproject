<?php

/**
 * 
 *  Function to bulid the search user and add/remove user Form.
 */
function im_user_dashboard() {
  drupal_add_js(drupal_get_path('module', 'im_user') . '/js/im_user_dashboard.js');
  drupal_add_js(drupal_get_path('module', 'im_rmp') . '/js/im_rmp.js');
  drupal_add_css(drupal_get_path('module', 'im_features_stores') . '/css/im_features_stores.css');
  drupal_add_css(drupal_get_path('module', 'im_user') . '/css/im_user_dashboard.css');
  drupal_add_css(drupal_get_path('module', 'multiselect') . '/multiselect.css');
  drupal_add_js(drupal_get_path('module', 'multiselect') . '/multiselect.js'); 
  drupal_add_js('misc/tabledrag.js');
  $build['users_search'] = drupal_get_form('im_user_search_users_by_role');
  $build['users_add_remove'] = drupal_get_form('im_user_modify_user_role');  
  return $build;
}
/**
 * 
 * Function to search the users by role
 */
function im_user_search_users_by_role($form, &$form_state) { 
  $role_names = _get_all_roles();
  $form['user_head_title'] = array(
    '#type' => 'item',
    '#markup' => t('The Dashboard allows the administrator to manage the users in back office'),
    '#prefix' => '<div id ="dashboard-title">',
    '#suffix' => '</div>',
  );
  $form['user_search'] = array(
    '#type' => 'fieldset',
    '#title' => t('Show users only where'),
    '#prefix' => '<div id ="field-set-search">',
    '#suffix' => '</div>',
  );
  $form['user_search']['user_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($_SESSION['user_dashboard']['name']) ? $_SESSION['user_dashboard']['name'] : '',
  );
 $form['user_search']['user_role'] = array(
    '#type' => 'select',
    '#options' => $role_names,
    '#title' => t('Role'),
    '#default_value' => isset($_SESSION['user_dashboard']['rid']) ? $_SESSION['user_dashboard']['rid'] : '0',
  );
  $form['user_search']['user_search_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
  );
  $form['user_search']['user_reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#submit' => array('im_user_search_users_by_role_reset'),
  );
  $form['user_back_url'] = array(
    '#type' => 'link',
    '#title' => t('Add user'),
    '#href' => 'admin/im/user/add', 
    '#attributes' => array('class' => "button-orange"),
  );
  return $form;
}
/**
 * 
 * Submit handler ti handle the serach submit
 */
function im_user_search_users_by_role_submit($form, $form_state) {
  unset($_SESSION['user_dashboard']['rid']);
  unset($_SESSION['user_dashboard']['name']);
  $rid = isset($form_state['values']['user_role']) ? $form_state['values']['user_role'] : '';
  $name = isset($form_state['values']['user_name']) ? $form_state['values']['user_name'] : '';
  $_SESSION['user_dashboard']['rid'] = $rid;
  $_SESSION['user_dashboard']['name'] = $name;
}
/**
 * 
 * Submit handler ti handle the serach reset
 */
function im_user_search_users_by_role_reset($form, $form_state) {
  $form_state['values'] = '';
  $form_state['rebuild'] = TRUE;	
}
/**
 * 
 * Function to assgin/remove the roles to the a user users
 */
function im_user_modify_user_role($form, $form_state) {
//  unset($_SESSION["dashboard_regional_users"]);
  if (!empty($_SESSION['user_dashboard']['rid']) || !empty($_SESSION['user_dashboard']['name'])) {
  	$rid = $_SESSION['user_dashboard']['rid'];
  	$name = $_SESSION['user_dashboard']['name'];
  	$user_names = _get_search_users($rid, $name); 
  	unset($_SESSION['user_dashboard']['rid']);	
  	unset($_SESSION['user_dashboard']['name']);
  }
  else {
  	$user_names = _get_search_users();
  }
  $role_names = _get_all_roles();
  $options = array();
  $form['role_names'] = array(
    '#type' => 'value',
    '#value' => $role_names,
  );  
  $status = array();
  $header = array();
  $table_select = array();
  $header_data['users'] = array('data' => t("Users"));
  $js_user = array();
  foreach($user_names as $uid => $name) {
  	  $js_user[$uid] = $name['full_name'];
    foreach ($role_names As $rid => $value) {
      if (isset($name['rn_name'][$rid])){
        $status[$uid][$rid] = 1;        
      }
      $header_data[$rid] = array('data' => $value);
      if($value == 'content_manager_action_regional'){
        $regional_rid = $rid;
      }
    }    
    $header = $header_data;
  }
  regional_profile_popup_settings();
  //Create the checkbox and assign the default values.
  foreach ($user_names as $uid => $value) {
  	$table_select[$uid] = array('users' => $value['full_name']);
     foreach ($role_names as $rid => $name) {
       if ($rid == $regional_rid) {       	
       	$regional_user_nid = isset($value['regional_nid']) ?  $value['regional_nid'] : '';        
       	if (!empty($regional_user_nid)) {       		
          $ctools_url = '<div class="usp_regional_user_ctools"><span class="dashboard_regional_link_active dashbaord_active_id_' . $uid . '">' . ctools_modal_text_button(t('Profils Régionaux<span class="plus">+</span>'), 'rmp/nojs/regional_moderator_profile_form/add-rmp/' . $uid . '/edit/' . $regional_user_nid, t('Profils Régionaux<span class="plus">+</span>'),  'ctools-modal-ctools-sample-style') . '</span></span><span class="dashboard_regional_link_deactive dashbaord_deactive_id_' . $uid . '">' . t('Profils Régionaux') . '<span class="plus">+</span></span></div>';
       	} 
       	else {
       	  $ctools_url = '<div class="usp_regional_user_ctools"><span class="dashboard_regional_link_active dashbaord_active_id_' . $uid . '">' . ctools_modal_text_button(t('Profils Régionaux<span class="plus">+</span>'), 'rmp/nojs/regional_moderator_profile_form/add-rmp/' . $uid, t('Profils Régionaux<span class="plus">+</span>'),  'ctools-modal-ctools-sample-style') . '</span></span><span class="dashboard_regional_link_deactive dashbaord_deactive_id_' . $uid . '">' . t('Profils Régionaux') . '<span class="plus">+</span></span></div>';	
       	}   	
       	       	
       	$table_select[$uid][$rid] = array(
        'data' => array(
          '#type' => 'checkbox',
       	  '#title' => $ctools_url,
          '#attributes' => array('class' => array('role-name content_manager_action_regional'), 'name' => 'selected_role[' . $uid . '][' . $rid . '-' . $name . ']', 'id' => $uid),
          '#prefix' => '<div id ="' . $uid . '">',
          '#suffix' => '</div>',
          ),
        );       	
       }
       else {
       	$table_select[$uid][$rid] = array(
        'data' => array(
          '#type' => 'checkbox',
          '#attributes' => array('class' => array('role-name'), 'name' => 'selected_role[' . $uid . '][' . $rid . '-' . $name . ']', 'id' => $uid),
          '#prefix' => '<div id ="' . $uid . '">',
          '#suffix' => '</div>',
          ),
        );
       }       
     if (isset($status[$uid][$rid]) && $status[$uid][$rid] == 1) {
       $table_select[$uid][$rid]['data']['#attributes']['checked'] ='checked';
      }
    }
  }
  drupal_add_js(array('im_user_dashboard' => array('variables' => drupal_json_encode($js_user))), 'setting');
  $form['users_roles_details'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $table_select,
    '#attributes' => array('class' => array('users-checkbox')),
    '#empty' => t('No people available.'),
  ); 
  $form['pager'] = array('#markup' => theme('pager'));  
  $form['actions'] = array('#type' => 'actions');
  // UATIM-705 Do not show the Remove user button It is temporary change.
  $form['actions']['remove'] = array('#type' => 'submit', '#value' => t('Remove Users'), '#submit' => array('im_user_dashboard_remove_users_submit'));
  //Uncommented the above line since the issue UATIM - 670 is fixed.
  $form['actions']['save'] = array('#type' => 'submit', '#value' => t('Save details'));
    
  return $form;
}
/**
 * 
 * Submit  handler to the add user roles.
 */
function im_user_modify_user_role_submit($form, &$form_state) {
//	echo "<pre>"; print_r($form_state['input']);
	im_user_dashboard_process_action($form_state, "add");
}
/**
 * 
 * Submit  handler to Remove the users roles
 */
function im_user_dashboard_remove_users_submit($form, &$form_state) {
  im_user_dashboard_process_action($form_state, "remove");
}
/**
 * 
 * Function to handle the add and remove users roles
 * @param array $form_state: Form state of values
 * @param string $action: the action to be performed; Add/Remove roles
 */
function im_user_dashboard_process_action($form_state, $action) {
  $user_selected_roles = array();
  $user_names = _get_search_users();
  foreach ($form_state['input']['selected_role'] as $uid => $value) {
  	 foreach ($value as $role => $id) {
  	   $rid_role = explode('-', $role);
  	   $roles_selected[$uid][$rid_role[0]] = $rid_role[1]; 
  	 }  	 	
  }
  foreach ($form_state['values']['users_roles_details'] as $key => $value) {
    if ($key == $value) {
  	  $user_selected_roles[$key] = isset($roles_selected[$key]) ? $roles_selected[$key] : '';
  	}
  }
  foreach ($user_selected_roles as $uid => $roles) {
    $user = user_load($uid);
    $user_roles = $user->roles;
    $present_role = $user_roles;
    $updated_user_roles = array();
    if (is_array($roles)) { 	
	  foreach ($roles as $rid => $role) {
	    if ($action == "add") {
	      /*Add the Regional user and save the Regional nid and regional stores to the user profile*/
 	      if ($role == "content_manager_action_regional") {
 	      	if (!empty($_SESSION["dashboard_regional_moderator_users"][$uid]['profile_nids'])) {
		      $rmp_nodes = explode(',',$_SESSION["dashboard_regional_moderator_users"][$uid]['profile_nids']);
 	  	    	$rmp_node_stores = '';
 	  	    	foreach($rmp_nodes as $rmp_node_ids) {
 	  	    		$rmp_store_details = node_load($rmp_node_ids);
 	  	    		if(!empty($rmp_store_details->field_rmp_store['und'][0]['value'])) {
 	  	    			$rmp_node_stores.= $rmp_store_details->field_rmp_store['und'][0]['value'].',';
 	  	    		}
 	  	    	} 	  	    	
 	  	    	$rmp_node_stores = rtrim($rmp_node_stores,',');
 	  	    	$user->field_user_regional_profile_stor['und'][0]['value'] = $rmp_node_stores;
 	  	    	$user->field_user_regional_profile_stor['und'][0]['safe_value'] = $rmp_node_stores;
 	  	    	$user->field_user_regional_profile_nids['und'][0]['value'] = $_SESSION["dashboard_regional_moderator_users"][$uid]['profile_user_nid'];
 	  	    	$user->field_user_regional_profile_nids['und'][0]['safe_value'] = $_SESSION["dashboard_regional_moderator_users"][$uid]['profile_user_nid'];  	    	
		      $updated_user_roles[$rid] = $role;
		      unset($_SESSION["dashboard_regional_moderator_users"][$uid]);
 	  	    }
 	  	    else {
 	  	      if(isset($user->field_user_regional_profile_stor[LANGUAGE_NONE][0]['value']) && ($user->field_user_regional_profile_stor[LANGUAGE_NONE][0]['value'])) {
 	  	   	    $updated_user_roles[$rid] = $role;
 	  	   	  }
 	  	   	  else {
 	  	   	  	$updated_user_roles[$rid] = $role;
 	  	   	  	form_set_error("", t("Please attach the profile to the user."));
 	  	   	  } 
 	  	    }
 	      }
 	      else {
 	        $updated_user_roles[$rid] = $role;
 	      }
	  	 }
	  	  else if (isset($user_roles[$rid]) && $action == "remove") {
	  	  	if (in_array("content_manager_action_regional", $user_roles)) {
	  	  	  //Delete the Regional stores if the user role is removed.
	  	  	  $user->field_user_regional_profile_stor[LANGUAGE_NONE][0]['value'] = '';
	  	  	  $user->field_user_regional_profile_nids[LANGUAGE_NONE][0]['value'] = '';
	  	  	} 
	  	  	unset($user_roles[$rid]);
	  	  }
	  	}
    }    
  	unset($user->roles);  	
    if ($action == "add") {
      $user->roles = $updated_user_roles;
    $content_regional_manager_is_present = array_diff($present_role, $updated_user_roles);
    //Remove the Regional store form the user, if content_manager_action_regional role is removed
      if(in_array("content_manager_action_regional", $content_regional_manager_is_present)) {
        $user->field_user_regional_profile_stor = '';
        $user->field_user_regional_profile_nids = '';
      }
      if (empty($updated_user_roles)) {
        _im_user_dashboard_delete($user->uid);
        unset($user->uid);
      }
    }
    else if ($action == "remove") {
      $user->roles = $user_roles;      
      if ((count($user->roles)==1) && in_array('authenticated user', $user->roles)) {
        _im_user_dashboard_delete($user->uid);
        unset($user->uid);
      }
    }
    if(!empty($user->uid) && isset($user->uid)) {
      user_save($user);
    }
  }

  //unset($_SESSION['selected_store_preference_nid']);
  drupal_set_message(t('The changes have been saved.'));

  // Clear the cached pages and blocks.
  cache_clear_all();
}
/**
 * 
 * Function to get all the users roles in IM
 */
function _get_all_roles() {
  $role_names = array();
  $options = array();
  //Query to select all the roles in the DB.
  $query = db_select('role', 'r');
  $query->fields('r', array('name', 'rid'));
  $query->condition('r.name', 'anonymous user', '<>');
  $query->condition('r.name', 'authenticated user', '<>');
  $query->orderBy("(case WHEN r.name = 'administrator' then 1 
                         WHEN r.name = 'expert' then 2
                         WHEN r.name = 'content_manager_action' then 3
                         WHEN r.name = 'content_manager_action_regional' then 4
                         WHEN r.name = 'content_manager_om' then 5
                         WHEN r.name = 'contributor_action' then 6                         
                         WHEN r.name = 'contributor_alert' then 7
                         WHEN r.name = 'contributor_news' then 8
                         WHEN r.name = 'contributor_benchmark' then 9
                         WHEN r.name = 'contributor_om' then 10
                         WHEN r.name = 'contributor_sales_plan' then 11
                         WHEN r.name = 'visitor' then 12
                         WHEN r.name = 'technical_director' then 13
                          end)", "");
  $result = $query->execute();
  $role_names['0'] = t("any");
  while($record = $result->fetchAssoc()) {
    $role_names[$record['rid']] = $record['name'];    
  }
  return $role_names;	
}
/**
 * 
 * Function to get the users based on search.
 * @param number $rid : Role selected
 * @param string $name: Name entered to search
 */
function _get_search_users($rid = NULL, $name = NULL) {
  $user_names = array();
  //Query to get all the Users who have already roles.
  $query = db_select('users', 'u');
  $query->join('users_roles','r','r.uid = u.uid');
  $query->join('role','rn','r.rid = rn.rid');
  $query->join('field_data_field_full_name','ud','ud.entity_id = u.uid');
  $query->leftJoin('field_data_field_user_regional_profile_nids','r_nid','r_nid.entity_id = u.uid');
  $query->fields('u', array('name', 'uid'));
  $query->fields('rn', array('name'));
  $query->fields('r', array('rid'));
  $query->fields('ud', array('field_full_name_value'));
  $query->fields('r_nid', array('field_user_regional_profile_nids_value'));
  $query->orderBy('ud.field_full_name_value', 'ASC');   
  if (!empty($name)) {  	
    $query->condition('ud.field_full_name_value', "%" . $name . "%", 'LIKE');
  }
  $query->condition('u.status', '1', '=');  
  if(!empty($rid)){
    //sub query to get UID based on rid and filter users based resulting uid.
    $subquery = db_select('users_roles', 'urs')
                ->fields('urs', array('uid'))
                ->condition('urs.rid', $rid, '=');
    $query->condition('u.uid', $subquery, 'IN');
    //$query->condition('r.rid', $rid, '=');
  }
  $result = $query->execute(); 
  while($record = $result->fetchAssoc()) {
    $user_names[$record['uid']]['name'] = $record['name'];
    $user_names[$record['uid']]['full_name'] = $record['field_full_name_value'];
    $user_names[$record['uid']]['rn_name'][$record['rid']] = $record['rn_name'];
    $user_names[$record['uid']]['rid'][$record['rid']] = $record['rid'];
    $user_names[$record['uid']]['regional_nid'] = $record['field_user_regional_profile_nids_value'];
  }  
  //To sort the users list.
//  uasort($user_names, 'comp_sort_criteria');
  return $user_names;
}

/**
 * Custom function to sort the users list
 */
function comp_sort_criteria($a, $b) {
  if ($a['full_name'] == $b['full_name']) {
    return 0;
  }
  //return ($a['full_name'] < $b['full_name']) ? -1 : 1;
  elseif(strcasecmp($a['full_name'], $b['full_name']) < 0){
    return -1;
  }
  elseif(strcasecmp($a['full_name'], $b['full_name']) > 0){
    return 1;
  }
}

/**
 * Function to delete the user having no roles from dashboard.
 */
function _im_user_dashboard_delete($user_id){
	//Fix for UATIM-670
	user_cancel(array(), $user_id, 'user_cancel_reassign');
	$batch =& batch_get();
	$batch['progressive'] = FALSE;
	batch_process();
	user_delete($user_id);
	//@to-do Uncomment the below code for 14.2.10. Fix for UATIM - 670 
	/*
  // Anonymize nodes (current revisions).
  module_load_include('inc', 'node', 'node.admin');
  $nodes = db_select('node', 'n')->fields('n', array('nid'))->condition('uid', $user_id)->execute()->fetchCol();
  node_mass_update($nodes, array('uid' => 0));
  // Anonymize old revisions.
  db_update('node_revision')->fields(array('uid' => 0))->condition('uid', $user_id)->execute();
  // Clean history.
  db_delete('history')->condition('uid', $user_id)->execute();
  db_delete('users')->condition('uid', $user_id, '=')->execute();
  db_delete('users_roles')->condition('uid', $user_id, '=')->execute();
  db_delete('authmap')->condition('uid', $user_id, '=')->execute();
  watchdog('user', 'Deleted user ID: %id.', array('%id' => $user_id), WATCHDOG_NOTICE);*/
}