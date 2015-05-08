<?php 
/**
 * @file
 * inc file for user header block.
 */

/**
* Implements form for the user header block.
*/
function _im_user_userheader_bar() {
	//print $_SESSION['user_selected_store'];
  //drupal_add_js(drupal_get_path('module', 'im_user') . '/js/jquery-ui.js');
  drupal_add_js(drupal_get_path('module', 'im_user') . '/js/im_user_userheader_block.js');
  drupal_add_js(drupal_get_path('module', 'im_user') . '/js/jquery.jclock-2.4.2.js');
  include_once drupal_get_path('module', 'im_user') . '/im_user.profile.inc';
  im_feature_agenda_ctools_popup_settings();
  drupal_add_js('misc/tabledrag.js');
  drupal_add_css(drupal_get_path('module', 'im_agenda') . '/css/im_agenda.css');
  drupal_add_css(drupal_get_path('module', 'im_features_stores') . '/css/im_features_stores.css');
  drupal_add_js(drupal_get_path('module', 'im_features_stores') . '/js/im_features_stores.js');
  drupal_add_js(drupal_get_path('module', 'multiselect') . '/multiselect.js');
  drupal_add_css(drupal_get_path('module', 'multiselect') . '/multiselect.css');    
  global $base_url;
  global $user;
  $role = '';

  $user_fields = user_load($user->uid);
  $logged_user_roles = is_array($user_fields->roles) ? $user_fields->roles : array();  
  $excluded_bo_roles = array_diff($logged_user_roles, array('authenticated user', 'visitor')); 
  $view_settings_link = FALSE; 
  if(sizeof($excluded_bo_roles) > 0) {
    $view_settings_link = TRUE;
  }
  if (isset($_SESSION['ldap_user_role'])) {
    if($_SESSION['ldap_user_role'] == 'store_director') {
      $view_settings_link = TRUE;
    }
  }
  $uid = $user_fields->uid;
 // $titles = t('My custom listing');
  $type = 'ul';
  $attributes = array(
    'id' => 'my-custom-listing',
    'class' => 'user-header-style',
  );

  $timestamp = date("l j F Y ");
  $timestamp =strtotime($timestamp);
  $datedisplay = format_date($timestamp,'custom','l j F Y');
  $timedisplay = array('class'=>'im_user_portal_time');
  $item_display[0] = $datedisplay;
  $item_display[] = $timedisplay;
  $count = 0;
if(!empty ($user_fields->field_user_stores['und'][0]['value'])) {
    $prefered_store = $user_fields->field_user_stores['und'][0]['value'];
    $prefered_store = explode(',', $prefered_store);
    $count = count($prefered_store);
  }
  else{
    $count = 0;
  }
  $nid = isset($user_fields->field_user_store_nid['und'][0]['value']) ? $user_fields->field_user_store_nid['und'][0]['value'] : '';
   
  if (isset($_SESSION['ldap_login_key'])) {
    $role = isset($_SESSION['ldap_user_role']) ? $_SESSION['ldap_user_role'] : '';
    $title = array();
    $ctools_url ='';
    $cn = array();
    $ladp_id = $_SESSION['ldap_login_key'];
    $obj = new imldapSoapService();
    $profile = $obj->soapRequest('getProfil', array('id' => $ladp_id));
    if(isset($profile) && !empty($profile)){
      $profile = simplexml_load_string($profile->data);
      $profile_name = _get_profile_name($profile);
      if(!empty($profile_name['title']) && !empty($profile_name['cn'])) {
        $full_name = t('Welcome') . " " . $profile_name['title'] . " " . $profile_name['cn'];
        if($count > 0 && !empty($nid)){
          if (isset($user_fields->field_user_store_nid['und'][0]['value'])) {
          $ctools_url = 'user_store_preference_form/node/form/nojs/' . $user_fields->field_user_store_nid['und'][0]['value'] . '/edit';
        }
          $item_display[] = ctools_modal_text_button($full_name, $ctools_url, $full_name,  'ctools-modal-ctools-sample-style im_user_full_name full-name-link');
        }
        
        else{
          $item_display[] = $full_name;
        }
      }
    }
  }

  $linklist = array();
  if ($view_settings_link) {
  //Bulid the benu based on Roles
    $fo_links = array();
    foreach($excluded_bo_roles as $current_role){
      if(strpos($current_role, 'action')== true || strpos($current_role, 'news')== true || strpos($current_role, 'benchmark')== true || strpos($current_role, 'alert')== true){
        $links = _im_agenda_fo_menus();
        foreach($links as $key => $link){
        $fo_links[$key] = $link;
        }
      }
      if(strpos($current_role, 'om')== true){
        $links = _im_om_fo_menus();      
        foreach($links as $key => $link){
        $fo_links[$key] = $link;
        }
      }
      if(strpos($current_role, 'sales')== true){
        $links = _im_sales_fo_menus();      
        foreach($links as $key => $link){
          $fo_links[$key] = $link;
         }
      }
      if($current_role == "expert"){
        $links = _im_om_fo_menus(); 
        foreach($links as $key => $link){
          $fo_links[$key] = $link;
         }
      }
      if(($current_role == "administrator") || ($current_role == 'technical_director')){
        $links = _im_admin_fo_menus();      
        foreach($links as $key => $link){
          $fo_links[$key] = $link;
         }
      }
     }
     if (isset($_SESSION['ldap_user_role'])) {
       if($_SESSION['ldap_user_role'] == 'store_director' && in_array( 'authenticated user',$user_fields->roles) && count($user_fields->roles)==1) {
         $fo_links['DMD Assignment'] = array( 'title' => t('DMD Assignment'), 'href' => 'admin/im/user/dmd-assignment'); 
       }
     }
    $linklist = $fo_links;
//    $linklist['item9'] = array('title' => t('Administration'), 'href' => $base_url . '/admin', 'html' => TRUE );
    $logout_img ='';
    $img_path = drupal_get_path('module','im_user').'/images/user-setting.png';
    $setting_path = array('path' => $img_path, 'attributes' => array('class' => 'settings', 'id' => 'settings-img'));
    $settings_img = theme('image', $setting_path);
    $attributes_settings =array('class' => array('menu-categories'), 'id' => 'sub_menu', );
    $item_display[] = array(html_entity_decode(theme('links', array('links' => $linklist, 'attributes' => $attributes_settings, 'heading' => array('text' => $settings_img, 'level' => 'div', 'class' => 'uh-settings-icon')))),'class' => 'im_user_settings_menu');
    }

  if (!empty($user_fields->field_user_stores['und'][0]['value']) &&($count > 1)) {
    //Agenda home page and day page with "All store" link at first.
    if (((arg(0) == 'agenda') && arg(3) == 'all') || ((arg(0) == 'agenda-day') && (arg(2) == 'all'))) {
      $att = array('class' => 'menu-categories', 'id' => 'sub_menu1');
      $store_id = '';
      $stores_result = db_query("SELECT s.pve_code, s.ite_lib_value from {store_item_fields} s WHERE s.pve_code IN (:store_id) AND s.dit_cod_item ='magasin' ORDER BY s.ite_lib_value ASC", array(':store_id' => $prefered_store))->fetchAll();
      $stores = array();
      foreach ($stores_result as $store){
        $stores[$store->pve_code] = $store->ite_lib_value;
      }
      $i = 0;
      foreach ($stores as $key => $value) {
        $url_value = $value;
        $store_id_value = $key;
        if (!empty($url_value) && (!empty($store_id_value))) {
          $item_var = 'item' . $i;
          $current_date = date('Ymd');
        }
        if (((arg(0) == 'agenda') && arg(3) == 'all')) {
          if (arg(4) != '') {
            $homepage_dept_arg = arg(4);
          }
          else {
            $homepage_dept_arg = 'all';
          }
          //UATIM-533 to show the selected store on the top , to differentiate between the Accuile and the Tous les magasin
          $prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'agenda/list/'.arg(2).'/'.$store_id_value.'/'.$homepage_dept_arg);
          if(arg(2) == 'today') {
            $prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'agenda/list/'.$current_date.'/'.$store_id_value.'/'.$homepage_dept_arg);
          }
          else {
            $prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'agenda/list/'.arg(2).'/'.$store_id_value.'/'.$homepage_dept_arg);
          }
        }
        elseif (((arg(0) == 'agenda-day') && (arg(2) == 'all'))) {
          if (arg(3) != '') {
            $daypage_depart_arg = arg(3);
          }
          else {
            $daypage_depart_arg = 'all' ;
          }
          $prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'agenda-day/'.arg(1).'/'.$store_id_value.'/'. $daypage_depart_arg);
        }
        $i++;
      }
      if (((arg(0) == 'agenda') && arg(3) == 'all')) {
      	//UATIM-533 to show the selected store on the top , to differentiate between the Accuile and the Tous les magasin
        if(arg(2) == 'today') {
          $item_display[] = array(html_entity_decode(theme('links', array('links' => $prefered_stores, 'attributes' => $att, 'heading' => array('text' => l(t('Tous les magasins'), 'agenda/list/'.$current_date.'/all/'.$homepage_dept_arg, array('html' => TRUE)), 'level' => 'div', 'class' => '')))),'class' => 'im_stores_list_menu');
        }
        else{
          $item_display[] = array(html_entity_decode(theme('links', array('links' => $prefered_stores, 'attributes' => $att, 'heading' => array('text' => l(t('Tous les magasins'), 'agenda/list/'.arg(2).'/all/'.$homepage_dept_arg, array('html' => TRUE)), 'level' => 'div', 'class' => '')))),'class' => 'im_stores_list_menu');
        }
      }
      elseif (((arg(0) == 'agenda-day') && (arg(2) == 'all'))) {
        $item_display[] = array(html_entity_decode(theme('links', array('links' => $prefered_stores, 'attributes' => $att, 'heading' => array('text' => l(t('Tous les magasins'), 'agenda-day/'.arg(1).'/all/'.$daypage_depart_arg, array('html' => TRUE)), 'level' => 'div', 'class' => '')))),'class' => 'im_stores_list_menu');
      }
    }

    //Agenda home page and day page with All store link in second place.
    elseif (((arg(0) == 'agenda') && is_numeric(arg(3))) || ((arg(0) == 'agenda-day') && is_numeric(arg(2)))) {
      $att = array('class' => 'menu-categories', 'id' => 'sub_menu1');
      $i = 0;
      if (arg(0) ==  'agenda') {
        $first_store = arg(3);
      }
      else{
        $first_store = arg(2);
      }
      $store_id = '';
      $stores_result = db_query("SELECT s.pve_code,s.ite_lib_value from {store_item_fields} s WHERE s.pve_code IN (:store_id) AND s.dit_cod_item ='magasin' ORDER BY s.ite_lib_value ASC", array(':store_id' => $prefered_store))->fetchAll();

      $stores = array();
        foreach ($stores_result as $store){
          $stores[$store->pve_code] = $store->ite_lib_value;
        }
    
      $i = 0;
      foreach ($stores as $key => $value) {
        if ($first_store != $key){
          $url_value = $value;
          $store_id_value = $key;
          if (!empty($url_value) && (!empty($store_id_value))) {
            $item_var = 'item' . $i;
            $current_date = date('Ymd');
            if (((arg(0) == 'agenda') && is_numeric(arg(3)))) {
                if (arg(4) != '') {
                  $homepage_dept_arg = arg(4);
                }
                else {
                  $homepage_dept_arg = 'all' ;
                }
            $prefered_stores[2] = array('title' => t('Tous les magasins'), 'href' => 'agenda/list/'.arg(2).'/all/'.$homepage_dept_arg);
            $prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'agenda/list/'.arg(2).'/'.$store_id_value.'/'.$homepage_dept_arg);
            }
            elseif (((arg(0) == 'agenda-day') && is_numeric(arg(2)))) {
              if(arg(3) != '') {
                $daypage_depart_arg = arg(3);
              }
              else {
                $daypage_depart_arg = 'all' ;
               }
            $prefered_stores[2] = array('title' => t('Tous les magasins'), 'href' => 'agenda-day/'.arg(1).'/all/'.$daypage_depart_arg);
            $prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'agenda-day/'.arg(1).'/'.$store_id_value.'/'.$daypage_depart_arg);
            }
          }
          $i++;
        }
      }
      $url_value = db_select('store_item_fields','s') 
                  ->fields('s',array('ite_lib_value'))
                  ->condition('s.pve_code' ,$first_store, '=')
                  ->condition('s.dit_cod_item', 'magasin', '=')
                  ->execute()->fetchField();
      if (((arg(0) == 'agenda') && is_numeric(arg(3)))) {
        $item_display[] = array(html_entity_decode(theme('links', array('links' => $prefered_stores, 'attributes' => $att, 'heading' => array('text' => l($url_value, 'agenda/list/'.arg(2).'/'.$first_store.'/'.$homepage_dept_arg, array('html' => TRUE)), 'level' => 'div', 'class' => '')))),'class' => 'im_stores_list_menu');
      }
      elseif (((arg(0) == 'agenda-day') && is_numeric(arg(2)))) {
        $item_display[] = array(html_entity_decode(theme('links', array('links' => $prefered_stores, 'attributes' => $att, 'heading' => array('text' => l($url_value, 'agenda-day/'.arg(1).'/'.$first_store.'/'.$daypage_depart_arg, array('html' => TRUE)), 'level' => 'div', 'class' => '')))),'class' => 'im_stores_list_menu');
      }
    
    }
  }
  //User has only one store.
  elseif($count == 1 && arg(0) != 'annuaire' && arg(0) != 'sales-plan'){
    $store_value = $user_fields->field_user_stores['und'][0]['value'];
    $str_value = db_select('store_item_fields','s') 
           ->fields('s',array('ite_lib_value'))
           ->condition('s.pve_code',$store_value,'=')
           ->condition('s.dit_cod_item', 'magasin', '=')
           ->execute()->fetchField();
    $current_date = date('Ymd');
    if (((arg(0) == 'agenda-day'))) {
      if (arg(3) != '') {
        $daypage_depart_arg = arg(3);
      }
      else {
        $daypage_depart_arg = 'all' ;
      }
      $item_display[] = l($str_value, 'agenda-day/'.arg(1).'/'.$store_value.'/'.$daypage_depart_arg, array('attributes' => array('class' => array('single-store'))), array('html' => TRUE));
    }
    else {
      $item_display[] = l($str_value, 'agenda/list/'.arg(2).'/'.$store_value.'/all', array('attributes' => array('class' => array('single-store'))), array('html' => TRUE));
    }
  }
    //for the other pages expect agenda home page, agenda for the day and annuaire.
  if ($count > 1 && arg(0)!='agenda' && arg(0)!= 'agenda-day' && arg(0) != 'annuaire' && arg(0) != 'sales-plan'){
  	$current_date= date('Ymd');
    $att = array('class' => 'menu-categories', 'id' => 'sub_menu1');
    $store_id = '';
    $stores_result = db_query("SELECT s.pve_code,s.ite_lib_value from {store_item_fields} s WHERE s.pve_code IN (:store_id) AND s.dit_cod_item ='magasin' ORDER BY s.ite_lib_value ASC", array(':store_id' => $prefered_store))->fetchAll();
    $stores = array();
    foreach ($stores_result as $store){
      $stores[$store->pve_code] = $store->ite_lib_value;
    }
    $i = 0;
    //UATIM-533 to show the selected store on the top 
    if (is_numeric($_SESSION['user_selected_store']) && isset($_SESSION['user_selected_store'])) { 
      $first_store = $_SESSION['user_selected_store'];
        foreach ($stores as $key => $value) {
          if ($first_store != $key){
            $url_value = $value;
            $store_id_value = $key;
            if (!empty($url_value) && (!empty($store_id_value))) {
              $item_var = 'item' . $i;
              $prefered_stores[2] = array('title' => t('Tous les magasins'), 'href' => 'agenda/list/'.$current_date.'/all/all');
              $prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'agenda/list/'.$current_date.'/'.$store_id_value.'/all');
            }
            $i++;
          }
        }
        $url_value = db_select('store_item_fields','s') 
                    ->fields('s',array('ite_lib_value'))
                    ->condition('s.pve_code' ,$first_store, '=')
                    ->condition('s.dit_cod_item', 'magasin', '=')
                    ->execute()->fetchField();
        $item_display[] = array(html_entity_decode(theme('links', array('links' => $prefered_stores, 'attributes' => $att, 'heading' => array('text' => l($url_value, 'agenda/list/'.$current_date.'/'.$first_store.'/all', array('html' => TRUE)), 'level' => 'div', 'class' => '')))),'class' => 'im_stores_list_menu');
    }
    else{
      foreach ($stores as $key => $value) {
        $url_value = $value;
        $store_id_value = $key;
        if (!empty($url_value) && (!empty($store_id_value))) {
          $item_var = 'item' . $i;
          $current_date = date('Ymd');
          $prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'agenda/list/'.$current_date.'/'.$store_id_value.'/all');
        }
        $i++;
      }
      $item_display[] = array(html_entity_decode(theme('links', array('links' => $prefered_stores, 'attributes' => $att, 'heading' => array('text' => l(t('Tous les magasins'), 'agenda/list/'.$current_date.'/all/all', array('html' => TRUE)), 'level' => 'div', 'class' => '')))),'class' => 'im_stores_list_menu');
    }
  }
  //Annuaire page store link generation - UATIM-454
  if (arg(0) == 'annuaire') {
    //If user has more than one store
    if ($count > 1) {
      //user will multiple store and if user select any one store
      if (is_numeric(arg(1))) {
      	$att = array('class' => 'menu-categories', 'id' => 'sub_menu1');
        $first_store = arg(1);
        $store_id = '';
        $stores_result = db_query("SELECT s.pve_code,s.ite_lib_value from {store_item_fields} s WHERE s.pve_code IN (:store_id) AND s.dit_cod_item ='magasin' ORDER BY s.ite_lib_value ASC", array(':store_id' => $prefered_store))->fetchAll();

        $stores = array();
          foreach ($stores_result as $store){
            $stores[$store->pve_code] = $store->ite_lib_value;
          }

        $i = 0;
        foreach ($stores as $key => $value) {
          if ($first_store != $key){
            $url_value = $value;
            $store_id_value = $key;
            if (!empty($url_value) && (!empty($store_id_value))) {
              $item_var = 'item' . $i;
              $prefered_stores[2] = array('title' => t('Tous les magasins'), 'href' => 'annuaire/all/all');
              $prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'annuaire/'.$store_id_value);
            }
            $i++;
          }
        }
        $url_value = db_select('store_item_fields','s') 
                    ->fields('s',array('ite_lib_value'))
                    ->condition('s.pve_code' ,$first_store, '=')
                    ->condition('s.dit_cod_item', 'magasin', '=')
                    ->execute()->fetchField();
          $item_display[] = array(html_entity_decode(theme('links', array('links' => $prefered_stores, 'attributes' => $att, 'heading' => array('text' => l($url_value, 'annuaire/'.$first_store, array('html' => TRUE)), 'level' => 'div', 'class' => '')))),'class' => 'im_stores_list_menu');
        }
        //user have multiple store and 'all store' at top.
      else if (arg(1) == 'all') {
        $att = array('class' => 'menu-categories', 'id' => 'sub_menu1');
        $store_id = '';
        $stores_result = db_query("SELECT s.pve_code, s.ite_lib_value from {store_item_fields} s WHERE s.pve_code IN (:store_id) AND s.dit_cod_item ='magasin' ORDER BY s.ite_lib_value ASC", array(':store_id' => $prefered_store))->fetchAll();
        $stores = array();
        foreach ($stores_result as $store){
          $stores[$store->pve_code] = $store->ite_lib_value;
        }
        $i = 0;
        foreach ($stores as $key => $value) {
          $url_value = $value;
          $store_id_value = $key;
          if (!empty($url_value) && (!empty($store_id_value))) {
            $item_var = 'item' . $i;
          }
          $prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'annuaire/'.$store_id_value);
          $i++;
        }
          $item_display[] = array(
          html_entity_decode(
          theme('links', 
          array('links' => $prefered_stores, 'attributes' => $att,
          'heading' => array('text' => l(t('Tous les magasins'), 'annuaire/all/all', array('html' => TRUE)), 
          'level' => 'div', 'class' => '')))),'class' => 'im_stores_list_menu');
      }
    }
    //if user has only one store.
    else if ($count == 1) {
    $store_value = $user_fields->field_user_stores['und'][0]['value'];
    $str_value = db_select('store_item_fields','s') 
           ->fields('s',array('ite_lib_value'))
           ->condition('s.pve_code',$store_value,'=')
           ->condition('s.dit_cod_item', 'magasin', '=')
           ->execute()->fetchField();
    $current_date = date('Ymd');

      $item_display[] = l($str_value, 'annuaire/'.$store_value, array('attributes' => array('class' => array('single-store'))), array('html' => TRUE));
    }
  }
  //Sales-plan page store link generation - UATIM-801
  if (arg(0) == 'sales-plan') {
    //If user has more than one store    
    $currentyear = date("Y");
    if ($count > 1) {
      //user will multiple store and if user select any one store
      if (is_numeric(arg(1))) {
      	$att = array('class' => 'menu-categories', 'id' => 'sub_menu1');
        $first_store = $_SESSION['storeid'];
        $store_id = '';
        $stores_result = db_query("SELECT s.pve_code,s.ite_lib_value from {store_item_fields} s WHERE s.pve_code IN (:store_id) AND s.dit_cod_item ='magasin' ORDER BY s.ite_lib_value ASC", array(':store_id' => $prefered_store))->fetchAll();

        $stores = array();
          foreach ($stores_result as $store){
            $stores[$store->pve_code] = $store->ite_lib_value;
          }

        $i = 0;
        foreach ($stores as $key => $value) {
        	$url_value = $value;
          $store_id_value = $key;
          if ($first_store != $key){            
            if (!empty($url_value) && (!empty($store_id_value))) {
              $item_var = 'item' . $i;
			        $storeType = 'region-commerciale';
			        $storeToken = $store_id_value;
			        $fetchRegion = db_select('store_item_fields','s')
			              ->fields('s',array('ite_lib_value'))
			              ->distinct()
			              ->condition('s.dit_cod_item',$storeType, '=')
			              ->condition('s.pve_code',$storeToken, '=')
			              ->execute();
			             
					    $storeRegion = $fetchRegion->fetchfield();		   
					    $regionOptions = _im_sales_plan_get_taxonomy_tid();
					    $regionCode = array_search($storeRegion, $regionOptions);
					     
					    $fetchRegionCode = db_select('field_data_field_taxo_sp_region_code','s')
			              ->fields('s',array('entity_id'))
			              ->condition('s.field_taxo_sp_region_code_value',$regionCode, '=')
			              ->execute();			             
					    $storeRegionId = $fetchRegionCode->fetchfield();	
					    $prefered_stores[2] = array('title' => t('Tous les magasins'), 'href' => 'sales-plan/now/all');
	              if($storeRegionId==''){
						    	$store_regionurl = 'now/all';
						    	$prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'sales-plan/'.$store_regionurl, 'query' => array('storeid' => $store_id_value,'region'=>selected));
						    }
						    else{
						    	$store_regionurl = $currentyear .'/'.$storeRegionId;
						    	$prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'sales-plan/'.$store_regionurl, 'query' => array('storeid' => $store_id_value,'region'=>selected));
						    }              
              //$prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'sales-plan/'.$store_regionurl);
            }
            $i++;
          }else{
            if (!empty($url_value) && (!empty($store_id_value))) {        	
			        $storeType = 'region-commerciale';
			        $first_storeToken = $store_id_value;
			        $fetchRegion = db_select('store_item_fields','s')
			              ->fields('s',array('ite_lib_value'))
			              ->distinct()
			              ->condition('s.dit_cod_item',$storeType, '=')
			              ->condition('s.pve_code',$first_storeToken, '=')
			              ->execute();
			             
					    $storeRegion = $fetchRegion->fetchfield();		   
					    $regionOptions = _im_sales_plan_get_taxonomy_tid();
					    $regionCode = array_search($storeRegion, $regionOptions);
					     
					    $fetchRegionCode = db_select('field_data_field_taxo_sp_region_code','s')
			              ->fields('s',array('entity_id'))
			              ->condition('s.field_taxo_sp_region_code_value',$regionCode, '=')
			              ->execute();			             
					    $storeRegionId = $fetchRegionCode->fetchfield();	
					    if($storeRegionId==''){
						     $first_store_regionurl = 'now/all';
					    }				    
              else{						    	
					    	 $first_store_regionurl = $currentyear .'/'.$storeRegionId;    	
					    }   
            }
          }
        }
         $fetch_sel_store = db_select('store_item_fields','s') 
                    ->fields('s',array('ite_lib_value'))
                    ->condition('s.pve_code' ,$first_store, '=')
                    ->condition('s.dit_cod_item', 'magasin', '=')
                    ->execute();
          $url_value = $fetch_sel_store->fetchfield();	;	

          if($url_value!=''){
             $item_display[] = array(html_entity_decode(theme('links', array('links' => $prefered_stores, 'attributes' => $att, 'heading' => array('text' => l(t($url_value), 'sales-plan/'.$first_store_regionurl, array('query' => array('storeid' => $first_storeToken,'region'=>selected)), array('html' => TRUE)), 'level' => 'div', 'class' => '')))),'class' => 'im_stores_list_menu');
          }else{
          	 unset($prefered_stores[2]);
          	$item_display[] = array(
          html_entity_decode(
          theme('links', 
          array('links' => $prefered_stores, 'attributes' => $att,
          'heading' => array('text' => l(t('Tous les magasins'), 'sales-plan/now/all', array('html' => TRUE)), 
          'level' => 'div', 'class' => '')))),'class' => 'im_stores_list_menu');           
          }
        }
        //user have multiple store and 'all store' at top.
      else if (arg(2) == 'all') {
        $att = array('class' => 'menu-categories', 'id' => 'sub_menu1');
        $store_id = '';
        $stores_result = db_query("SELECT s.pve_code, s.ite_lib_value from {store_item_fields} s WHERE s.pve_code IN (:store_id) AND s.dit_cod_item ='magasin' ORDER BY s.ite_lib_value ASC", array(':store_id' => $prefered_store))->fetchAll();
        $stores = array();
        foreach ($stores_result as $store){
          $stores[$store->pve_code] = $store->ite_lib_value;
        }
        $i = 0;
        foreach ($stores as $key => $value) {
          $url_value = $value;
          $store_id_value = $key;
          if (!empty($url_value) && (!empty($store_id_value))) {
            $item_var = 'item' . $i;
          }
        $storeType = 'region-commerciale';
        $storeToken = $store_id_value;
        $fetchRegion = db_select('store_item_fields','s')
              ->fields('s',array('ite_lib_value'))
              ->distinct()
              ->condition('s.dit_cod_item',$storeType, '=')
              ->condition('s.pve_code',$storeToken, '=')
              ->execute();
             
		    $storeRegion = $fetchRegion->fetchfield();		   
		    $regionOptions = _im_sales_plan_get_taxonomy_tid();
		    $regionCode = array_search($storeRegion, $regionOptions);
		     
		    $fetchRegionCode = db_select('field_data_field_taxo_sp_region_code','s')
              ->fields('s',array('entity_id'))
              ->condition('s.field_taxo_sp_region_code_value',$regionCode, '=')
              ->execute();
             
		    $storeRegionId = $fetchRegionCode->fetchfield();	
		    
		    if($storeRegionId==''){
		    	$store_regionurl = 'now/all';
		    	$prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'sales-plan/'.$store_regionurl, 'query' => array('storeid' => $store_id_value,'region'=>selected));
		    }
		    else{
		    	$store_regionurl = $currentyear .'/'.$storeRegionId;
		      $prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'sales-plan/'.$store_regionurl, 'query' => array('storeid' => $store_id_value,'region'=>selected));
		    } 
          //$prefered_stores[$item_var] = array('title' => t($url_value), 'href' => 'sales-plan/'.$store_regionurl);
          $i++;
        }
          $item_display[] = array(
          html_entity_decode(
          theme('links', 
          array('links' => $prefered_stores, 'attributes' => $att,
          'heading' => array('text' => l(t('Tous les magasins'), 'sales-plan/now/all', array('html' => TRUE)), 
          'level' => 'div', 'class' => '')))),'class' => 'im_stores_list_menu');          
      }
    }
    //if user has only one store.
    else if ($count == 1) {
        $store_id_value = $user_fields->field_user_stores['und'][0]['value'];
        $str_value = db_select('store_item_fields','s') 
           ->fields('s',array('ite_lib_value'))
           ->condition('s.pve_code',$store_id_value,'=')
           ->condition('s.dit_cod_item', 'magasin', '=')
           ->execute()->fetchField();
        $storeType  = 'region-commerciale';
        $storeToken = $store_id_value;
        $fetchRegion = db_select('store_item_fields','s')
              ->fields('s',array('ite_lib_value'))
              ->distinct()
              ->condition('s.dit_cod_item',$storeType, '=')
              ->condition('s.pve_code',$storeToken, '=')
              ->execute();
             
	    $storeRegion = $fetchRegion->fetchfield();		   
	    $regionOptions = _im_sales_plan_get_taxonomy_tid();
	    $regionCode = array_search($storeRegion, $regionOptions);
	     
	    $fetchRegionCode = db_select('field_data_field_taxo_sp_region_code','s')
              ->fields('s',array('entity_id'))
              ->condition('s.field_taxo_sp_region_code_value',$regionCode, '=')
              ->execute();
             
	    $storeRegionId = $fetchRegionCode->fetchfield();	
	    
	    if($storeRegionId==''){
	    	$store_regionurl = 'now/all';		    	
	    	$item_display[] = l($str_value, 'sales-plan/'.$store_regionurl, array('attributes' => array('class' => array('single-store'))), array('html' => TRUE));
	    }
	    else{
	    	$store_regionurl = $currentyear .'/'.$storeRegionId;
	      $item_display[] = l($str_value, 'sales-plan/'.$store_regionurl, array('attributes' => array('class' => array('single-store'))), array('html' => TRUE));
	    }
    }
  }
 
  $img_path = drupal_get_path('module','im_user').'/images/logout.png';
  $logout_img ='';
  $logout_path = array('path' => $img_path, 'attributes' => array('class' => 'logout', 'id' => 'logout-img'));
  //$logout_img = theme('image', $logout_path);
  $logout_img = 'Déconnexion';
  $item_display[] =l($logout_img, 'user/logout', array('html' => TRUE, 'attributes' => array('class' => 'logout', 'id' => 'logout-img')));
  $output = theme_item_list(array('items' => $item_display, 'title' => '', 'type' => $type, 'attributes' => $attributes));
  $output = theme('im_userheader_output', array('output' => $output));
  return $output;
}
/**
 * 
 * Function to get the Menu links for Agenda. 
 */
function _im_agenda_fo_menus(){
  $output = ''; 
  $output = array(
    'My Content' => array( 'title' => t('My Content'), 'href' => 'admin/workbench'),
    'Manage Agenda Content' => array( 'title' => t('Manage Agenda Content'), 'href' => 'admin/im/manage/agenda'),
  );
  if (isset($_SESSION['ldap_user_role'])) {
    if ($_SESSION['ldap_user_role'] == 'store_director') {
      $output['DMD Assignment'] =  array( 'title' => t('DMD Assignment'), 'href' => 'admin/im/user/dmd-assignment');
    }
  }
  return $output;
}
/**
 * 
 * Function to get the Menu links for OM.
 */
function _im_om_fo_menus(){
  $output = ''; 
  $output = array(
    'My Content' => array( 'title' => t('My Content'), 'href' => 'admin/workbench'),
    'Manage OM Content' => array( 'title' => t('Manage OM Content'), 'href' => 'admin/im/manage/om'),
  );
  if (isset($_SESSION['ldap_user_role'])) {
    if ($_SESSION['ldap_user_role'] == 'store_director') {
      $output['DMD Assignment'] =  array( 'title' => t('DMD Assignment'), 'href' => 'admin/im/user/dmd-assignment');
    }
  }
  return $output;
}
/**
 * 
 * Function to get the Menu links for Sales plan 
 */
function _im_sales_fo_menus(){
  $output = ''; 
  $output = array(
    'My Content' => array( 'title' => t('My Content'), 'href' => 'admin/workbench'),
    'Manage Sales Content' => array( 'title' => t('Manage Sales plan Content'), 'href' => 'admin/im/manage/sales_plan'),
  );
  if (isset($_SESSION['ldap_user_role'])) {
    if ($_SESSION['ldap_user_role'] == 'store_director') {
      $output['DMD Assignment'] =  array( 'title' => t('DMD Assignment'), 'href' => 'admin/im/user/dmd-assignment');
    }
  }
  return $output;
}
/**
 * 
 * Function to get the menu links for Administrator and techinical director.
 */  
function _im_admin_fo_menus(){
  $output = ''; 
  $output = array(   
    'My Content' => array( 'title' => t('My Content'), 'href' => 'admin/workbench'),
    'Manage Agenda Content' => array( 'title' => t('Manage Agenda Content'), 'href' => 'admin/im/manage/agenda'),
    'Manage OM Content' => array( 'title' => t('Manage OM Content'), 'href' => 'admin/im/manage/om'),
    'Manage Sales Content' => array( 'title' => t('Manage Sales plan Content'), 'href' => 'admin/im/manage/sales_plan'),
    'Manage Messages' => array( 'title' => t('Manage Messages'), 'href' => 'admin/im/manage/messages' ),
    'Manage Application' => array( 'title' => t('Manage Application'), 'href' => 'admin/im/manage/applications'),
    'Manage Taxonomy' => array( 'title' => t('Manage Taxonomy'), 'href' => 'admin/structure/taxonomy'),
    'Manage DM Foncions' => array( 'title' => t('Manage DM Foncions'), 'href' => 'admin/im/getdynamics'),
  	'Manage DMS' => array( 'title' => t('Manage DMS'), 'href' => 'admin/im/getdms'),
  	'Manage MMS' => array( 'title' => t('Manage MMS'), 'href' => 'admin/im/getmms'),
    'IM Custom Settings' => array( 'title' => t('IM Custom Settings'), 'href' => 'admin/im/settings'),
    'Manage User Dashboard' => array( 'title' => t('Manage User Dashboard'), 'href' => 'admin/im/user/dashboard'),
    'Manage Directory' => array( 'title' => t('Manage Directory'), 'href' => 'admin/im/manage/directory'),
  );
  if (isset($_SESSION['ldap_user_role'])) {
    if ($_SESSION['ldap_user_role'] == 'store_director') {
      $output['DMD Assignment'] =  array( 'title' => t('DMD Assignment'), 'href' => 'admin/im/user/dmd-assignment');
    }
  }
  return $output;
}  
/**
 * 
 * UATIM-533 to show the selected store on the top- (Set the selected store value on all pages except annuaire,homepage and agenda for the day) ...
 */
function _im_user_store_selection() {
  if (!empty($_POST['data'])) {
    $_SESSION['user_selected_store'] = $_POST['data']; 
  }
}