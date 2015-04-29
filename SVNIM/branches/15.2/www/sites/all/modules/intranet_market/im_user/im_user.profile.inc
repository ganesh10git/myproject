<?php
/**
 * @file
 * im_user.profile.inc
 */

/**
 * This method returns below profile names
 * givenName
 * sn
 * mail
 * inetUserStatus
 * uid
 * cn
 * title
 * @param XML response of WS:getProfil 
 */
function _get_profile_name($profile) {
  $profile_name = array();	
  $counter      = 0;
  if(!isset($profile->attribut)) return $profile_name;
  foreach ($profile->attribut as $value){
  	if(!isset($profile_name[(string)$profile->attribut[$counter]['name']])) {
      $profile_name[(string)$profile->attribut[$counter]['name']] = (string)$profile->attribut[$counter];
  	}
    $counter++;
  }
  return $profile_name;
}

/**
 * This method decides whether user is carrefour market user or not.
 * returns - TRUE/FALSE, as per carrefour market user status. 
 * @param XML response of WS:getProfil 
 */
function _is_carrefour_market($profile) {
  if(!isset($profile->grp)) return FALSE;
  foreach ($profile->grp as $grp){
    $counter = 0;
    $level   = '';
    $cn      = ''; 
    foreach($grp->attr as $attr){
  	  if((string)$grp->attr[$counter]['type'] == 'level' && (string)$grp->attr[$counter] == 'GRPOPE') {
  		$level = 'GRPOPE';
  	  }
      if((string)$grp->attr[$counter]['name'] == 'cn' && (string)$grp->attr[$counter] == '0002') {
  		$cn = '0002';
  	  }
  	  if($level == 'GRPOPE' && $cn == '0002') {
  		return TRUE;
  	  } 
  	  $counter++;
    }
  }
  return FALSE;
}

/**
 * This method retrieves user's store.
 * returns - store name, if the user attached with store.
 * returns - FALSE, if the user not attached with store.
 * @param XML response of WS:getProfil 
 */
function _get_user_store($profile) {
  if(!isset($profile->grp)) return FALSE;
  foreach ($profile->grp as $grp){
    $counter = 0;
    $level   = '';
    $cn      = ''; 
    foreach($grp->attr as $attr){
  	  if((string)$grp->attr[$counter]['type'] == 'level' && (string)$grp->attr[$counter] == 'AL') {
  		$level = 'AL';
  	  }
      if((string)$grp->attr[$counter]['name'] == 'cn') {
  		$cn = (string)$grp->attr[$counter];
  	  }
  	  if($level == 'AL' && $cn) {
  	  	//assign if DATABASE table is present.
	  	$result = db_query("SELECT pve_code
		                        FROM {store_item_fields} sif 
		                        WHERE sif.dit_cod_item = 'thales'
		                        AND sif.ite_lib_value = :lib_value",
		                        array(':lib_value' => $cn)
		                       );
		if($result) {
			$store = $result->fetchObject();
			if(!empty($store)){
			  $_SESSION['profil']['store'] = $store->pve_code;
			}
		}
  	  	return $cn;
  	  } 
  	  $counter++;
    }
  }
  return FALSE;
}

/**
 * This method retrieves user's store status.
 * returns - store statut, if the user attached with store.
 * returns - FALSE, if the user not attached with store statut.
 */
function _get_user_store_status() {
  if(isset($_SESSION['profil']['store']) && $_SESSION['profil']['store']) {
    $result = db_query("SELECT ite_lib_value
	                    FROM {store_item_fields} sif 
	                    WHERE sif.dit_cod_item = 'statut'
	                    AND sif.pve_code = :pve_code",
	                    array(':pve_code' => $_SESSION['profil']['store'])
	                  );
		if($result) {
			$store = $result->fetchObject();
			if(!empty($store)){
			  return $store->ite_lib_value;
			}
		}
  }
  return FALSE;
}

/**
 * This method retrieves user's cadre status.
 * returns - cadre, if the user with cadre status.
 * returns - FALSE, if the user is not with cadre status.
 */
function _get_user_cadre_status() {
  $profile = simplexml_load_string($_SESSION['getProfil']);
  if(!isset($profile->grp)) return FALSE;
  foreach ($profile->grp as $grp){
  	$counter = 0;
  	$description = '';
    $cn = ''; 
    foreach($grp->attr as $attr){
      if((string)$grp->attr[$counter]['name'] == 'description') {
  		$description = (string)$grp->attr[$counter];
  	  }
  	  if((string)$grp->attr[$counter]['name'] == 'cn') {
  		$cn = (string)$grp->attr[$counter];
  	  }
  	  if($cn == 'C' && $description == 'cadre') {
  	  	return 'cadre';
  	  }
  	  $counter++;
    }
  }
  return FALSE;
}

/**
 * This method maps user's store with profile.
 * @param stores of WS:getProfil 
 */
function _get_user_stores($profile) {
  $stores = array();
  if(!isset($profile->grp)) return FALSE;
  foreach ($profile->grp as $grp){
    $counter = 0;
    $level   = '';
    $cn      = ''; 
    foreach($grp->attr as $attr){
  	  if((string)$grp->attr[$counter]['type'] == 'level' && (string)$grp->attr[$counter] == 'AL') {
  		$level = 'AL';
  	  }
      if((string)$grp->attr[$counter]['name'] == 'cn') {
  		$cn = (string)$grp->attr[$counter];
  	  }
  	  if($level == 'AL' && $cn) {
  	  	//assign if DATABASE table is present.
	  	$result = db_query("SELECT pve_code
		                        FROM {store_item_fields} sif 
		                        WHERE sif.dit_cod_item = 'thales'
		                        AND sif.ite_lib_value = :lib_value",
		                        array(':lib_value' => $cn)
		                       );
		if($result) {
			$store = $result->fetchObject();
			if(!empty($store)){
			  $_SESSION['profil']['store'] = $store->pve_code;
			}
		}
		$stores[] = $cn;
		$level   = '';
        $cn      = ''; 
  	  	//return $cn;
  	  } 
  	  $counter++;
    }
  }
  return $stores;
}


function _is_store_director_dynamic($profile) {
  if(!isset($profile->grp)) return FALSE;
  $counter = 0;
  $db_dynamics = _im_user_getdynamics();
  foreach ($profile->grp as $grp){
  foreach ($db_dynamics as $db_dynamic) {
  	//to remove inbetween spaces preg_replace is added
    if(trim(strtoupper($db_dynamic['data']['code'])) == preg_replace('/\s+/', '', trim(strtoupper($profile->grp[$counter]['dn'])))) {
 	    return TRUE;
 	  }
    }
    $counter++;
  }
  return FALSE;
}

function _is_store_manager_category($profile) {
  if(!isset($profile->grp)) return FALSE;
  foreach ($profile->grp as $grp){
    $counter = 0;
    $level   = '';
    $cn      = ''; 
    foreach($grp->attr as $attr){
  	  if((string)$grp->attr[$counter]['type'] == 'level' && (string)$grp->attr[$counter] == 'classification') {
  		$level = 'classification';
  	  }
      if((string)$grp->attr[$counter]['name'] == 'cn') {
  		$cn = (string)$grp->attr[$counter];
  	  }
  	  if($level == 'classification' && $cn == 'C') {
  		return TRUE;
  	  } 
  	  $counter++;
    }
  }
  return FALSE;
}

/**
 * Check Whether current logged in user has Assigned Director Role.
 * @return boolean
 */
function _is_dmd_assigned_now($account = NULL){
  if(!db_table_exists('ldap_role_assignment')) return FALSE; 
  $result = db_query("SELECT asid
		              FROM {ldap_role_assignment} 
		              WHERE employee_number = :username
		              AND assignment_begin_date <= :now
		              AND (assignment_end_date + 60*60*24-1) >= :now
		              LIMIT 1",
		              array(':username' => $account->name,
		                    ':now' => time()
		                   )
		            );
  if($result) {
  	$assigned = $result->fetchObject();
  	  return (isset($assigned->asid) && $assigned->asid) ? TRUE : FALSE;
  }
  return FALSE;
}
/**
 * 
 * Function to validate the store director trainee...
 * @param unknown_type $profile
 */
function _is_store_director_trainee_dynamic($profile) {
  if(!isset($profile->grp)) return FALSE;
  $counter = 0;
  $db_dms = _im_user_getdms();
  foreach ($profile->grp as $grp){
    foreach ($db_dms as $dms) {
  	//to remove inbetween spaces preg_replace is added
    if(trim(strtoupper($dms['data']['code'])) == preg_replace('/\s+/', '', trim(strtoupper($profile->grp[$counter]['dn'])))) {
 	    return TRUE;
 	  }
    }
    $counter++;
  }
  return FALSE;
}
/**
 * 
 * Function to validate the store manager trainee ...
 * @param $profile
 */
function _is_store_manager_trainee_category($profile) {
  if(!isset($profile->grp)) return FALSE;
  $counter = 0;
  $db_dms = _im_user_getmms();
  foreach ($profile->grp as $grp){
    foreach ($db_dms as $dms) {
  	//to remove inbetween spaces preg_replace is added
    if(trim(strtoupper($dms['data']['code'])) == preg_replace('/\s+/', '', trim(strtoupper($profile->grp[$counter]['dn'])))) {
 	    return TRUE;
 	  }
    }
    $counter++;
  }
  return FALSE;
}
/**
 * This method idenify the foreman role in the LDAP
 * returns - TRUE, if the Foreman role is identified.
 * returns - FALSE, if the user is not a Foreman role.
 */
function _is_user_foreman($profile) {
  if(!isset($profile->grp)) return FALSE;
  foreach ($profile->grp as $grp){
    $counter = 0;
    $classification   = '';
    $a      = ''; 
    foreach($grp->attr as $attr){
  	  if((string)$grp->attr[$counter] == 'classification') {
  		$classification = 'classification';
  	  }
      if((string)$grp->attr[$counter] == 'A') {
  		$a = 'A';
  	  }
  	  if($classification == 'classification' && $a == 'A') {
  		return TRUE;
  	  } 
  	  $counter++;
    }
  }
  return FALSE;
}