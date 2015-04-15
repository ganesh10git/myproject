<?php

function _im_user_login_validate(){
  global $user, $base_url;
 
  if(isset($_REQUEST['CSIF_SessionId'])) {
    $ldap_login_key = base64_decode($_REQUEST['CSIF_SessionId']);
    //web service Integration
    $obj = new imldapSoapService();
    $response = $obj->soapRequest('isAlive', array('id' => $ldap_login_key));
    if($response->status == 'success'){
      //Remove cached services.
      include drupal_get_path('module', 'im_service') . '/im_service.methods.inc';
      foreach($cachable_methods as $method) {
        if(isset($_SESSION[$method])) $_SESSION[$method] = ''; 
      }
      $_SESSION['ldap_login_key'] = $ldap_login_key;
      if(isset($response->data) && $response->data == 1) {
        $profile = $obj->soapRequest('getProfil', array('id' => $ldap_login_key));        
        if($profile->status == 'success') {
          $profile = simplexml_load_string($profile->data);
          include_once drupal_get_path('module', 'im_user') . '/im_user.profile.inc';
          //Fetch User Info:
          $profile_name = _get_profile_name($profile);          
          //is Carrefour Market User?
          $is_carrefour_market_user = _is_carrefour_market($profile);
          
          //Get User Store
          $user_store = _get_user_store($profile);          
          watchdog('im_user', 'User store  %user_stores', array('%user_stores' => var_export($user_store, TRUE)), WATCHDOG_NOTICE, $link = NULL);
          //Add condition to check isset employeenumber or isset UID
          $register_id = !empty($profile_name['employeeNumber']) ? trim($profile_name['employeeNumber']):trim($profile_name['uid']);
          watchdog('im_user', 'Profile details  %profile_name', array('%profile_name' => var_export($profile_name, TRUE)), WATCHDOG_NOTICE, $link = NULL);
          watchdog('im_user', 'Register ID  %register_id', array('%register_id' => $register_id), WATCHDOG_NOTICE, $link = NULL);
          //Redirect Users to respective Home Page(VISITOR/ADMINISTRATOR/SALARIE SIEGE/STORE DIRECTOR-DM/STORE MANAGER-MM/STORE EMPLOYEE).
         if(!$is_carrefour_market_user){
          //Non carrefour - whether user exist in the database
           _im_user_external_login_register($profile_name,$register_id, $module='im_user');
           $account_validate = user_external_load($register_id);
           watchdog('im_user', 'Non carrefour  %account_validate', array('%account_validate' => var_export($account_validate, TRUE)), WATCHDOG_NOTICE, $link = NULL);
           if(!is_object($account_validate) || !isset($account_validate->uid) || !isset($account_validate->status) || !$account_validate->uid || !$account_validate->status) {
             if(!isset($account_validate->roles) || (count($account_validate->roles) < 2)){
               _im_access_denied();
               return;
              }
             } else if(!isset($account_validate->roles) || (count($account_validate->roles) < 2)){
               /*
                * UAT IM - 717:Security issue -Access deined for non Carrefour market usesr.
                */
                $_SESSION['NON_CARREFOUR_USER_ACCESS_DENIED'] = 'DENIED';
             	_im_access_denied();
              return;
            }
          } 
          //Check with Logged in user's EmployeeNumber or UID.
          _im_user_external_login_register($profile_name,$register_id, $module='im_user');
          //user_external_login_register($register_id, 'im_user');      
          $account = user_external_load($register_id);
          //Maps stores with - User Profile.
          $user_stores = _get_user_stores($profile);
          watchdog('im_user', 'user_stores %user_stores', array('%user_stores'=>var_export($user_stores, TRUE)), WATCHDOG_NOTICE, $link = NULL);
          if(sizeof($user_stores) > 0) {
            map_stores_profile($user_stores, $account);
          }
           //Assign Users email to profile.
          if(isset($profile_name['mail']) && $profile_name['mail']) {
            $account->mail = trim($profile_name['mail']);
            user_save($account);
           }
          //Assign Users full name to profile.
          if(isset($profile_name['givenName']) && $profile_name['sn']) {
            $account->field_full_name[LANGUAGE_NONE][0]['value'] = trim($profile_name['givenName']) . ' ' . trim($profile_name['sn']);
            user_save($account);
          }
          //Assign DMD role to User Object.
          // Assign DMD role - if already mapped.
          if(_is_dmd_assigned_now($account)) {
            $_SESSION['ldap_user_role_assigned'] = 'store_director';
          }else {
            $_SESSION['ldap_user_role_assigned'] = '';
          }
         //Mapping User ID to Session
            $_SESSION['ldap_user_id'] = $profile_name['uid'];
         //VISITOR 
          if(!$is_carrefour_market_user && in_array('visitor', $account->roles)) {
            $_SESSION['ldap_user_role'] = 'visitor';
           }
          //ADMINISTRATOR
          if ($is_carrefour_market_user && in_array('administrator', $account->roles)) {
            $_SESSION['ldap_user_role'] = 'administrator';
           }
            //STORE DIRECTOR TRAINEEE
          if ($is_carrefour_market_user && !im_stores_is_store_exist($user_store) && _is_store_director_trainee_dynamic($profile)) {
            $_SESSION['ldap_user_role'] = 'store_director_trainee';
           }
           //STORE Manager TRAINEEE
           elseif ($is_carrefour_market_user && !im_stores_is_store_exist($user_store) && _is_store_manager_trainee_category($profile)) {
            $_SESSION['ldap_user_role'] = 'store_manager_trainee';
           } 
          //SALARIE SIEGE
          elseif ($is_carrefour_market_user && !im_stores_is_store_exist($user_store)) {
            $_SESSION['ldap_user_role'] = 'salarie_siege';
             //Removing salarie_siege role according to UATIM-343.
            //_im_user_create_user_salarie_siege_role($account, $profile_name);
          }               
          //STORE DIRECTOR-DM
          //work on 4 -DM Identifiers: Creating LDAP Functions list
          if ($is_carrefour_market_user && im_stores_is_store_exist($user_store) && _is_store_director_dynamic($profile)) {
            $_SESSION['ldap_user_role'] = 'store_director';
           }
          //STORE MANAGER-MM
          elseif ($is_carrefour_market_user && im_stores_is_store_exist($user_store) && _is_store_manager_category($profile)) {
            $_SESSION['ldap_user_role'] = 'store_manager';
           }
         //STORE EMPLOYEE
          elseif ($is_carrefour_market_user && im_stores_is_store_exist($user_store) && !_is_store_manager_category($profile) && !in_array('administrator', $account->roles)) {
            $_SESSION['ldap_user_role'] = 'store_employee';
          }
          /*
           * Implemented to resolve the Login Redirection to the previously accessed page.
           */ 
          if(isset($_SESSION['enter_menu_destination'])) {
          	$errorurl = '';$stringquery = ''; 
            if(preg_match('/MSIE/i',$_SERVER['HTTP_USER_AGENT']) && (strpos($_SESSION['enter_menu_destination'], "all/") == TRUE) && (strpos($_SESSION['enter_menu_destination'], "list") == TRUE)) {
               $_SESSION['enter_menu_destination'] = trim($_SESSION['enter_menu_destination']).'all';
             }
             $stringquery = strpos($_SESSION['enter_menu_destination'], '?'); 
             $appendalterambersonstring = '';
             if(is_numeric($stringquery) == TRUE) {
              $alterquerystringurl  = explode('?', $_SESSION['enter_menu_destination']);
              $arguurl = explode('=', $alterquerystringurl[1]);
              $firstargument = urldecode($arguurl[0]); 
              $firstargumentvalue = urldecode($arguurl[1]);
              $stringamber = strpos($arguurl[1], '&');
              if(is_numeric($stringamber) == TRUE) {
               $alterambersonurl  = explode('&', $arguurl[1]);  
               $firstargumentvalue = urldecode($alterambersonurl[0]);
               drupal_goto($alterquerystringurl[0], array('query' => array($firstargument => $firstargumentvalue, $alterambersonurl[1] => $arguurl[2])));
              }
              drupal_goto($alterquerystringurl[0], array('query' => array($firstargument => $firstargumentvalue)));
             } else {
              drupal_goto($_SESSION['enter_menu_destination']);
             }
             unset($_SESSION['enter_menu_destination']);
           }
          //Allow All LDAP Users
          if(isset($_SESSION['ldap_user_role']) && ($_SESSION['ldap_user_role'])) {
            drupal_goto('agenda/list/today/all/all');
          }
           //Allow All Portal Roles
          else if(count($account->roles) > 1) {
            drupal_goto('agenda/list/today/all/all');
          }
          else{
            _im_access_denied();
          }
        } else {
          drupal_goto(im_user_get_login_url());
        }
      } else {
        drupal_goto(im_user_get_login_url());
      }
    }else {
      drupal_goto(im_user_get_login_url());  
    }
  }
  return '';
}
function _im_access_denied($message = 'please contact admin for the portal access', $status = 'warning') {
  drupal_set_message(t($message), $status);
  drupal_access_denied();
  return;
}

function _im_user_external_login_register($profile_name,$register_id, $module='im_user') {
  $account = user_external_load($register_id);
  if (!$account) {
  	watchdog('im_user', 'Not Registered with EID or UID', array(), WATCHDOG_NOTICE, $link = NULL);
    $existing_account = user_external_load($profile_name['mail']);
    if(!$existing_account){
    	
      // Register this new user.
      $userinfo = array(
        'name' => $register_id,
        'pass' => user_password(),
        'mail'=> $profile_name['mail'],
        'init' => $register_id,
        'status' => 1,
        'access' => REQUEST_TIME,
      );
      $new_account = user_save(drupal_anonymous_user(), $userinfo);
      //  Terminate if an error occurred during user_save().
      if (!$new_account) {
        drupal_set_message(t("Error saving user account."), 'error');
        return;
      }
      user_set_authmaps($new_account, array("authname_$module" => $register_id));
      $account = $new_account; 
      watchdog('im_user', 'New Registration with Register id ', array(), WATCHDOG_NOTICE, $link = NULL);
    }else{
    	watchdog('im_user', 'Already Registered with Email  %registered_mail So Process this user with workflow', array('%registered_mail' => $profile_name['mail']), WATCHDOG_NOTICE, $link = NULL);
      $account =  _im_user_modify_email_registration($profile_name,$register_id,$existing_account);
    }
     // Log user in.
   //  $form_state['uid'] = $account->uid;
 //    user_login_submit(array(), $form_state);
   if($module != 'im_user_dashboard'){
		// Log user in.
    $form_state['uid'] = $account->uid;
    user_login_submit(array(), $form_state);
   }
  }
  if($module != 'im_user_dashboard'){
		// Log user in.
    $form_state['uid'] = $account->uid;
    user_login_submit(array(), $form_state);
  }
}

function _im_user_modify_email_registration($profile_name,$register_id,$existing_account){
  //Search users and count and count>1 -> disable and delete authmap table and register as new users with EID or UID. 
  $obj = new imldapSoapService();
  $ldap_id = '';
  if (isset($_SESSION['ldap_login_key'])) {
    $ldap_id = $_SESSION['ldap_login_key'];
  }
  //Search users 
  $attribute_type = array('0' => 'mail','1' => 'inetUserStatus' );
  $attribute_value = array('0' => $profile_name['mail'],'1' => 'active' );
  $response = $obj->soapRequest('searchUsers', array('id' => $ldap_id, 'login' => '*', 'attributsType' => $attribute_type, 'attributsValue' => $attribute_value ));
  if ($response->status == "success") {
    //Search users and count>1 -> disable and delete authmap table and register as new users with EID or UID. 
    if (count($response->data) > 1) {
      watchdog('im_user', 'for count > 1 Registered with Email %registered_mail and  %search_user_count users with same email found in LDAP', array('%registered_mail' => $profile_name['mail'],'%search_user_count' => count($response->data)), WATCHDOG_NOTICE, $link = NULL);
      //Delete User data from authmap.
      $authname = $profile_name['mail'];
      $num_deleted = db_delete('authmap')
         ->condition('authname', $authname)
         ->execute();
     watchdog('im_user', 'for count > 1 Deleted authname in authmap :authname= %registered_mail, uid is %existing_account_uid', array('%existing_account_uid'=>$existing_account->uid,'%registered_mail' => $profile_name['mail']), WATCHDOG_NOTICE, $link = NULL);
      //Disable User
      $disable_user = user_load($existing_account->uid, TRUE);
      $disable_user->status = 0;
      user_save($disable_user);
      watchdog('im_user', 'for count > 1 Disabled user uid is %disable_user_uid, status is %disable_user_status', array('%disable_user_uid'=>$disable_user->uid,'%disable_user_status'=>$disable_user->status), WATCHDOG_NOTICE, $link = NULL);
     //Register as new user.
     user_external_login_register($register_id, 'im_user');
     $account = user_external_load($register_id);
     watchdog('im_user', 'for count > 1 Register as new user : UserID= %account_uid and Username= %account_name ', array('%account_uid'=>$account->uid,'%account_name'=>$account->name), WATCHDOG_NOTICE, $link = NULL);
    return $account;
  }
  else {
    watchdog('im_user', ' for count == 1 Existing user_id= %account_uid and  Username= %account_name', array('%account_uid'=>$existing_account->uid,'%account_name'=>$existing_account->name), WATCHDOG_NOTICE, $link = NULL);
    // In case count==1 
    //Update authmap table with exisitng user's EID or UID field.
    db_merge('authmap')->key(array(
      'uid' => $existing_account->uid,
      'module' => 'im_user',
      ))->fields(array('authname' => $register_id))->execute();
    watchdog('im_user', ' for count == 1 Updated authname with register_id for user_id= %account_uid and  Username= %account_name', array('%account_uid'=>$existing_account->uid,'%account_name'=>$existing_account->name), WATCHDOG_NOTICE, $link = NULL);
    //Update User table with exisitng user's EID or UID field.
    $update_user = user_load($existing_account->uid);
    $update_user->name = $register_id;
    $update_user->mail = $profile_name['mail'];
    $account = user_save($update_user); 
    watchdog('im_user', 'Updated existing user table data uid %account_uid and name is %account_name for count == 1', array('%account_uid'=>$account->uid,'%account_name'=>$account->name), WATCHDOG_NOTICE, $link = NULL);
    $account = user_external_load($register_id);
    return $account;
   }
  } 
}