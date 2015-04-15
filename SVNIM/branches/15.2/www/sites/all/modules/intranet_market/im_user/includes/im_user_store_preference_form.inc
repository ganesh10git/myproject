<?php   
/**
 * @file
 * inc file for im_user.
 */ 
function im_user_store() {
  $build['store_form'] = drupal_get_form('_user_store_preference_form');
  $build['store_result'] = drupal_get_form('_im_user_store_preference_result_form');
  return $build;
}

/**
 * Implements the User preference form. 
 */
function _user_store_preference_form($form, &$form_state) {
	$form['#attributes'] = array('class' => 'user-store-preference-form');
  drupal_add_js(drupal_get_path('module', 'im_user') . '/js/user_preference.js', array('weight' => 20));
  $do_field_default_value = array();
  $form['up_page_header_title'] = array(
    '#type' => 'markup',
    '#markup' =>t('Filtering information presented on the portal'),
 );
 $form['up_page_title'] = array(
    '#type' => 'markup',
    '#markup' =>t('Filtres sur la liste des magasins'),
 );
 $form['do_title'] = array(
    '#type' => 'markup',
    '#markup' =>t('DO et DR/CF correspondants'),
 );
  $form['usp_do']= array(
    '#type' => 'select', 
    '#title' => t('DO'),
    '#options' => get_do_field(),
    '#default_value' => 'Select',   
    '#ajax' => array(
      'callback' => 'ajax_callback_do_field',
      'wrapper' => 'dr-cf',
    ),
  );
  $drcf_field_option = array();
  if (isset($form_state['values']['usp_do'])) {
  $drcf_field_option = get_dr_cf_field($form_state['values']['usp_do']);  
  //$drcf_field_option = array_combine($drcf_field_option['ite_text'],$drcf_field_option['ite_value']);
  }
  //$default_drcf = array_merge(array('All'=> "All"),$drcf_field_option);
  $form['usp_drcf']= array(
    '#type' => 'select', 
    '#title' => t('DR/CF'), 
    '#options' => $drcf_field_option,
    '#multiple' => TRUE,
    '#prefix' => '<div id="dr-cf">',
    '#suffix' => '</div>',
  );
  $form['usp_store_status']= array(
    '#type' => 'checkboxes', 
    '#title' => t('Store Status'), 
    '#options' =>array(                     
                     'INTEGRE' => t('INTEGRE'),
                     'FRANCHISE' => t('FRANCHISE'),                                   
  ),
    '#default_value' =>array(                     
                     'INTEGRE' => t('INTEGRE'),
                     'FRANCHISE' => t('FRANCHISE'),                                   
  ),
  );
  $form['addtional_criteria_set'] = array(
    '#type' => 'fieldset',
    //'#title' => t('Additional Criteria'),
  );
  $form['criteria_title'] = array(
    '#type' => 'markup',
    '#markup' =>t('Critères supplémentaires'),
 );
  $form_state['storage']['addtional_criteria'] = isset($form_state['storage']['addtional_criteria']) ? $form_state['storage']['addtional_criteria'] : 0;
  $form['addtional_criteria_set']['usp_autocomplete_field']= array(
    '#type' => 'textfield',
    '#title' => t('Criteria') . " 1",    
    '#autocomplete_path' => 'uspautocomplete',
    '#ajax' => array(
      'callback' => 'ajax_callback_autocomplete_field',
      'wrapper' => 'autoc',
    ),
  );
  $options = array();
  if (isset($form_state['values']['usp_autocomplete_field'])) {
    $item_type = get_item_type_by_autocomplete($form_state['values']['usp_autocomplete_field']);
    if (isset($item_type['dit_idt_type'])) {
      $options = get_operator_value($item_type['dit_idt_type']);
    }
  }
  $form['addtional_criteria_set']['usp_operator']= array(
    '#type' => 'select',
    '#options' => $options,
    '#prefix' => '<div id="autoc">',
    '#suffix' => '</div>',
  );
  $form['addtional_criteria_set']['usp_autocomplete_value_text']= array(
    '#type' => 'textfield',  
  );
  $form['addtional_criteria_set']['addtional_criteria'] = array(
    '#type' => 'container',
    '#tree' => 1,
    '#prefix' => '<div id="addtional_criteria_div">',
    '#suffix' => '</div>',
  );
  if (empty($form_state['storage']['addtional_criteria'])) {
    $form_state['storage']['addtional_criteria'] = 0;
  }
/*  if (!empty($form_state['storage']['addtional_criteria']))
  if (@$form_state['storage']['addtional_criteria']) {
    for ($i = 1; $i <= $form_state['storage']['addtional_criteria']; $i++) {
      $form['addtional_criteria_set']['addtional_criteria'][$i]['usp_autocomplete_field']= array(
        '#type' => 'textfield',
        '#title' => t('Criteria') . " ". ($i+1),       
        '#autocomplete_path' => 'uspautocomplete',
        '#ajax' => array(
          'callback' => 'ajax_callback_autocomplete_field',
          'wrapper' => 'autoc',
          'method' => 'replace',
          'event' => 'change'
    ),
     );  
      $form['addtional_criteria_set']['addtional_criteria'][$i]['usp_operator']= array(
        '#type' => 'select',
        '#options' => array(                     
          '1' => t('='),
          '2' => t('+'),
          '3' => t('Like'),
          '4' => t('Unlike'),
        ),
      );
      $form['addtional_criteria_set']['addtional_criteria'][$i]['usp_autocomplete_value_text']= array(
        '#type' => 'textfield',  
      );
    }
  }*/

/*  $form['add_addtional_criteria'] = array(
    '#type' => 'button',
    '#value' => t('Add another item'),
    '#href' => '',
    '#ajax' => array(
    'callback' => '_im_user_ajax_add_addtional_criteria',
    'wrapper' => 'addtional_criteria_div',
   ),
  );*/
  
  $form['usp_save'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#submit' => array('_user_store_preference_form_submit_save'),
    '#attributes' => array('name' => 'usp_save'),
  );
  $form['usp_reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#submit' => array('_user_store_preference_form_submit_reset'),
    '#attributes' => array('name' => 'usp_reset'),
  );
  
  @$form_state['storage']['addtional_criteria']++;
  return $form;
}

/*
* Implementation of store result form.
*
*/
function _im_user_store_preference_result_form($form, &$form_state) {
	$form['#attributes'] = array('class' => 'im-user-store-preference-result-form');
  $options = array();
  $store_list =  get_store_result();
    foreach ($store_list as $store_id => $store_name) {
      $options[$store_id] = $store_name;
    }
    
  $form['usp_return_store']= array(
    '#title' => '',
    '#type' => 'multiselect', 
    '#prefix' => '<div class="poll-form">',
    '#options' => $options, 
    //'#default_value' => array('3021080655604'), 
    '#default_value' => '',
    '#suffix' => '</div>',
    '#multiple' => TRUE,
  );    
  if (arg(4) != "user_store_preference_form_ctools") {
    $form['usp_weather']= array(
      '#type' => 'select', 
      '#title' => t('Store choice of reference for the weather'), 
      '#options' => $options,
    	'#attributes' => array('id' => 'store-choice-weather'),
    );
  }
  $form['usp_cancel']=array(
    '#type' => 'link',
    '#title' => 'Cancel',
    '#markup' => '<div id="cancel">' . t('Cancel') . '</div>',
    '#attributes' => array('class' => 'ctools-close-modal'),
  );
  $form['usp_validate']=array(
    '#type' => 'submit',
    '#value' => t('Validate'),
    '#attributes' => array('id' => 'edit-usp-validate'),
  );
  return $form;
}

function _im_user_store_preference_result_form_submit($form, &$form_state) {
	unset($_SESSION['search_store']['usp_store_status']);
  unset($_SESSION['search_store']['usp_drcf']);
  unset($_SESSION['search_store']['usp_autocomplete_value_text']);
if (arg(4) == "user_store_preference_form_ctools") {
    $_SESSION['selected_store'] = implode(',',$form_state['values']['usp_return_store']);
    $_SESSION['popup_status'] = true;
}
else {
	global $user;
	$userProfile = user_load($user->uid);
  $userProfile->field_user_stores[LANGUAGE_NONE][0]['value'] = implode(',',$form_state['values']['usp_return_store']);
  $_SESSION['selected_store'] = implode(',',$form_state['values']['usp_return_store']);
  $userProfile->field_user_forecast[LANGUAGE_NONE][0]['value'] = $form_state['values']['usp_weather'];
  user_save($userProfile); 
  unset($_SESSION['search_store']); 
  if ($form_state['values']['usp_return_store']) {
  $_SESSION['popup_status'] = true;
  }
} 
}

function _user_store_preference_form_submit_reset($form, &$form_state)  {
  unset($_SESSION['search_store']['usp_store_status']);
  unset($_SESSION['search_store']['usp_drcf']);
  unset($_SESSION['search_store']['usp_autocomplete_value_text']);
}

function _im_user_ajax_add_addtional_criteria($form, $form_state) {
  return $form['addtional_criteria_set']['addtional_criteria'];
  $form_state['rebuild'] = TRUE;
}
/*
* Implementation of hook_submit
*/

function _user_store_preference_form_submit_save($form, &$form_state)  {
  $form_state['rebuild'] = TRUE;
  unset($_SESSION['search_store']['usp_store_status']);
  unset($_SESSION['search_store']['usp_drcf']);
  unset($_SESSION['search_store']['usp_autocomplete_value_text']);
  $status = $form_state['values']['usp_store_status'];
  $dr_cf = $form_state['values']['usp_drcf'];
  $status_value = '';
  $dr_cf_value = '';
  foreach ($status as $key =>$value) {
    if ($value != '0'){
      $status_value .= "'" . $key . "',";
    }
  }
  if ($status_value) {
    $status_value = trim($status_value, ",");
    $status_value = trim($status_value, "'");
    $_SESSION['search_store']['usp_store_status'] = $status_value;
  }
  foreach ($dr_cf as $key =>$value){
  	if ($value == "All") {
  		$dr_cf  = array_diff($_SESSION['doArray'], $dr_cf);
  		break;
  	}
  }
 
  foreach ($dr_cf as $key =>$value){
	  if(!empty($value)){
	      $dr_cf_value .= "'" . $key . "',";
	  }
  }
  if ($dr_cf_value) {
    $dr_cf_value = trim($dr_cf_value, ",");
    $dr_cf_value = trim($dr_cf_value, "'");
    $_SESSION['search_store']['usp_drcf'] = $dr_cf_value;
  }
 
  if (!empty($form_state['values']['usp_autocomplete_value_text'])) {
    $_SESSION['search_store']['usp_autocomplete_value_text'] = $form_state['values']['usp_autocomplete_value_text']; 
  }
}


function get_store_result() {
  $dr_cf_db_value = '';
  $status_db_value = '';
  $usp_autocomplete_value = '';
  if (isset($_SESSION['search_store']['usp_drcf'])) {
   $dr_cf_db_value = $_SESSION['search_store']['usp_drcf'];
  }
  if (isset($_SESSION['search_store']['usp_store_status'])) {
  $status_db_value = $_SESSION['search_store']['usp_store_status'];
  }
  if(isset($_SESSION['search_store']['usp_autocomplete_value_text'])) {
  $usp_autocomplete_value = $_SESSION['search_store']['usp_autocomplete_value_text'];
  }
  $value1 = array();
  $value2 = array();
  $value3 = array();
  $query = "SELECT pve_code AS STORE_ID FROM {store_item_fields} WHERE ite_lib_value IN ('".$dr_cf_db_value ."') AND pve_code IN(SELECT pve_code AS STORE_ID FROM store_item_fields WHERE ite_lib_value IN ('".$status_db_value."'))";
  $filter1 = db_query($query);
  foreach($filter1 as $result) {
    $value1['store_id'][] = $result;
  }
  $store_id = '';
  if (isset($value1['store_id'])) {
    foreach ($value1['store_id'] as $key =>$value){
      if ($value != '0'){
        $store_id .= "'" . $value->store_id . "',";
      }
    }
  }
  if ($store_id) {
    $store_id = trim($store_id, ",");
    $store_id = trim($store_id, "'");
  }
  $query = "SELECT a.pve_code AS STORE_CODE FROM store_item_fields_desc b LEFT JOIN {store_item_fields} a ON b.dit_cod_item=a.dit_cod_item WHERE a.ite_lib_value IN ('".$usp_autocomplete_value ."') and a.pve_code IN ('".$store_id."')";
  $filter2 = db_query($query);
  foreach($filter2 as $result) {
    $value2['store_code'][] = $result;   
  }
  $store_code = '';
  if (isset($value2['store_code'])) {
    foreach ($value2['store_code'] as $key =>$value){
      if ($value != '0'){
        $store_code .= "'" . $value->store_code . "',";
      }
    }
  }
  $filter3 = array();
  if ($store_code) {
    $store_code = trim($store_code, ",");
    $store_code = trim($store_code, "'");
    $filter3 = db_query("select pve_code, pve_lib from {store} where pve_code in ('".$store_code."')");
  }
  foreach($filter3 as $result) {
  	$value3[$result->pve_code] = $result->pve_lib;   
  }
 /* unset($_SESSION['search_store']['usp_store_status']);
  unset($_SESSION['search_store']['usp_drcf']);
  unset($_SESSION['search_store']['usp_autocomplete_value_text']);*/
  return $value3;
}

/*
* Implementation funtion for returning DO field.
*/
function get_do_field() {
  $do_field_lib = array();
  $query = db_select('store_item_fields','s')
  ->fields('s',array('ite_lib_value','pve_code'))
  ->distinct()
  ->condition('s.dit_cod_item','do');
  $result = $query->execute();
  $doArray = array('Select'=> "Select", 'All'=> "All");
  while($record = $result->fetchAssoc()) {
  	$doArray[$record['ite_lib_value']] = $record['ite_lib_value'];
  }
  return  $doArray;
}

/*
* Implementation funtion for returning DR/CF field. 
*/
function get_dr_cf_field($pve_code) {
  $doArray = array();
  $_SESSION['doArray'] = array();
  if ($pve_code == "All") {
    $query = db_select('store_item_fields','s')
    ->fields('s',array('ite_lib_value','pve_code'))
    ->distinct()
    ->condition('s.dit_cod_item','dr-cf');    
    $result = $query->execute();
    $doArray = array('All'=> "All");
    while($record = $result->fetchAssoc()) {
    //$drcf_field['ite_text'][] = $record['ite_lib_value'];
    //$drcf_field['ite_value'][] = $record['ite_lib_value'];
     $doArray[$record['ite_lib_value']] = $record['ite_lib_value'];
    }
    $_SESSION['doArray'] = $doArray;  
  }
  else {
   /* $query = db_select('store_item_fields','s')
    ->fields('s',array('ite_lib_value','pve_code'))
    ->distinct()
    ->condition('s.dit_cod_item','dr-cf')
    ->condition('s.pve_code',$pve_code);
    $result = $query->execute();*/
    $query = "select distinct stf2.ite_lib_value from {store_item_fields} stf1,{store_item_fields} stf2 where stf2.dit_cod_item='dr-cf' and stf1.dit_cod_item='do' and stf1.ite_lib_value='" . $pve_code . "' and stf1.pve_code=stf2.pve_code;";  
    $result = db_query($query);
    $doArray["All"] = "All";  
    while($record = $result->fetchAssoc()) {
    //$drcf_field['ite_text'][] = $record['ite_lib_value'];
    //$drcf_field['ite_value'][] = $record['ite_lib_value'];
    $doArray[$record['ite_lib_value']] = $record['ite_lib_value'];
    }
  }
  return $doArray;
}

/*
* Implementation funtion for returning DR/CF field. 
*/
function get_item_type_by_autocomplete($dit_lib) {
  $drcf_field = array();
  $query = db_select('store_item_fields_desc','s')
  ->fields('s',array('dit_idt_type','dit_cod_item'))
  ->distinct()
  ->condition('s.dit_lib',$dit_lib);
  $result = $query->execute();  
  while($record = $result->fetchAssoc()) {
  $drcf_field['dit_idt_type'] = $record['dit_idt_type'];
  $drcf_field['dit_cod_item'] = $record['dit_cod_item'];  
  }
  return  $drcf_field;
}

/*
* Implementation of item autocomplete.
*/
function _usp_item_autocompletes($string) {
  $string = str_replace("'", "", $string);
  $patterns_encode = array();
  $patterns_decode = array();
  $replacements_encode = array(); 
  $replacements_decode = array(); 
  $matches = array();
  $option_type =array();
  $patterns_str = 'â ã ä å ā ă ą à ç è é é ê ë ē ĕ ė ę ě ì í î ï ì ĩ ī ĭ ó ô õ ö ō ŏ ő ù ú û ü ũ ū ŭ ů';
  $patterns_encode = explode(" ", $patterns_str);
  $replacements_str = '/a/ /a/ /a/ /a/ /a/ /a/ /a/ /a/ /c/ /e/ /e/ /e/ /e/ /e/ /e/ /e/ /e/ /e/ /e/ /i/ /i/ /i/ /i/ /i/ /i/ /i/ /i/ /o/ /o/ /o/ /o/ /o/ /o/ /o/ /u/ /u/ /u/ /u/ /u/ /u/ /u/ /u/';
  $replacements_encode = explode(" ", $replacements_str);
  $patterns_str = '/â/ /ã/ /ä/ /å/ /ā/ /ă/ /ą/ /à/ /ç/ /è/ /é/ /é/ /ê/ /ë/ /ē/ /ĕ/ /ė/ /ę/ /ě/ /ì/ /í/ /î/ /ï/ /ì/ /ĩ/ /ī/ /ĭ/ /ó/ /ô/ /õ/ /ö/ /ō/ /ŏ/ /ő/ /ù/ /ú/ /û/ /ü/ /ũ/ /ū/ /ŭ/ /ů/';
  $patterns_decode = explode(" ", $patterns_str);
  $replacements_str = 'a a a a a a a a c e e e e e e e e e e i i i i i i i i o o o o o o o u u u u u u u u';
  $replacements_decode = explode(" ", $replacements_str);
  $string_decode = preg_replace($patterns_decode, $replacements_decode, strtolower($string));
  $string_encode = preg_replace($replacements_encode, $patterns_encode, strtolower($string));
  $sql = "SELECT dit_lib, dit_cod_item, ddo_lib , dsd_lib , dit_idt_type FROM store_item_fields_desc WHERE translate(lower(dit_lib), 'âãäåāăąèééêëēĕėęěìíîïìĩīĭóôõöōŏőùúûüũūŭů', 'aaaaaaaeeeeeeeeeeiiiiiiiiooooooouuuuuuu') like '%".$string_decode."%' OR translate(lower(dit_lib), 'aaaaaaaeeeeeeeeeeiiiiiiiiooooooouuuuuuu', 'âãäåāăąèééêëēĕėęěìíîïìĩīĭóôõöōŏőùúûüũūŭů') LIKE '%".$string_encode."%' ORDER BY dit_lib ASC LIMIT 10";
  $result = db_query($sql);
  foreach ($result as $row) {
    $matches[$row->dit_lib] = check_plain($row->ddo_lib) . '>' . check_plain($row->dsd_lib) . '>'. check_plain($row->dit_lib);
  }
  drupal_json_output($matches);
}

/*
* Implementation ajax callback for do fields.
*/
function ajax_callback_do_field($form, $form_state) {
  return $form['usp_drcf'];
}

/*
* Implementation ajax callback for autocomplete fields.
*/
function ajax_callback_autocomplete_field($form, $form_state) {
  return $form['addtional_criteria_set']['usp_operator'];
}

/*
* Implementation of function which returns the operator value.
*/
function get_operator_value($type) {
  $options = array();
  if ($type == 1) {
      $options = array(                     
                         'Not In' => t('Not In'),
                         'Like' => t('Like'),
                         'In' => t('In'),
      
      );
    }
  else if ($type == 2) {
      $options = array(                     
                         'equals' => '=',
                         'greater' => '>',
                         'lesser' => '<',
                         'lesser_gretaer' => '<>',
      
      );
    }
  else if ($type == 3) {
      $options = array(                     
                        'equals' => t('='),
                         'greater' => t('>'),
                         'lesser' => t('<'),
                         'lesser_gretaer' => t('<>'),                          
                         'Not In' => t('Not In'),
                         'Like' => t('Like'),
                         'In' => t('In'),
      
      );
    }
  else if ($type == 4) {
      $options = array(                     
                         'Starting From' => t('Starting From'),
                         'Ending From' => t('Ending From'),
      
      );
    }
  else if ($type == 5) {
      $options = array(                     
                         'In' => t('Include'),
                         'Not In' => t('Exclude'),
      );
    }
  else if ($type == 20) {
      $options = array(                     
                         'equals' => t('='),
                         'greater' => t('>'),
                         'lesser' => t('<'),
                         'lesser_gretaer' => t('<>')
      );
    }
  else {
      $options = array(                     
                       'none' => t('none')                       
      );
    }
  return $options;
}

function get_criteria_filter_list($item_code){
	$criteria_list = array();
  	$query = db_select('store_item_fields','s')
  	->fields('s',array('ite_lib_value'))
  	->distinct()
  	->condition('s.dit_cod_item',$item_code)
  	->isNotNull('s.ite_lib_value');
  	$result = $query->execute();
  	while($record = $result->fetchAssoc()) {
  	  if (!empty($record['ite_lib_value'])) {
  	  	$criteria_list[$record['ite_lib_value']] = $record['ite_lib_value'];
  	  }
  	}
  return  $criteria_list;
}