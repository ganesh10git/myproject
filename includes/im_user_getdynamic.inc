<?php
/**
 * @file
 * form For identifying the DM role during login
 */
function im_user_getdynamics_form() { 
  drupal_add_js(drupal_get_path('module', 'im_user') . '/js/jquery-ui.js');
  drupal_add_js(drupal_get_path('module', 'im_user') . '/js/im_user_getdynamic.js');
  $form = array();
  $form['getdynamics_textbox'] = array(
    '#type' => 'textfield',
    '#title' => t('search function'),
    '#size' => '25',
  );
  $form['getdynamics_button'] = array(
    '#type' => 'submit',
    '#value' => t('getDynamic'),
    '#submit' => array('getresult_submit'),
  );
  if (arg(3)) {
    $form['dynamic_result'] = array( 
      '#type' => 'item',
      '#markup' => im_user_getdynamics_result_callback(),
      '#prefix' => '<div class="table_global">',
      '#suffix' => '</div>',
    );
  }
  $form['dynamic_drupaltable_data'] = array(
    '#type' => 'item',
    '#markup' => _im_user_getdynamics_format(),
    '#prefix' => '<div class="table_global">',
    '#suffix' => '</div>',
  );
     $form['textbox']= array(
      '#type' => 'textarea',
    );
  $form['textbox']['#attributes']['style'] = 'display:none';
  return $form;
}
/**
*function to pass the textbox value
*/
function getresult_submit($form, &$form_state) {
  $searched_keyword = '';
  $searched_keyword = $form_state['values']['getdynamics_textbox'];
  $_SESSION['searched_keyword'] = $searched_keyword;
  drupal_goto("admin/im/getdynamics/".$searched_keyword);
  unset($_SESSION['searched_keyword']);
  exit;
}
/**
*function to call webservice on click of getdynamics button
*/
function im_user_getdynamics_result_callback() {
	$search_word = '';
  $search_word = $_SESSION['searched_keyword'];
  $application_name = 'Portail_Market';
  $request = 'getFonctions';
  $response ='';
  $obj = new imldapSoapService();
  $response = $obj->soapRequest('getDynamics', array('id' => $_SESSION['ldap_login_key'], 'applicationName' => 'Portail_Market', 'request' => 'getFonctions', 'params' => $search_word));
  if ($response->status == 'success') {
    return $member_desc = _get_dynamic_member_description($response);
  }
  else {
    drupal_set_message('Unable to fetch the response.','warning');
  }
}
/**
*function to display response from web service in table format
*/
function _get_dynamic_member_description($response) {
	if(!empty($response->data)){
		$results = array();
		$search_query = db_select('user_getdynamic', 'u')
      ->fields('u', array('code', 'description'))
      ->execute()->fetchall();
      foreach($search_query as $result){
      	$results[$result->code] = $result->description;
      }
    
		$rows = array();
  for ($n=0; $n <count($response->data); $n=$n+2) {
    $code = array();
    $m =$n+1;
    $code = $response->data[$n];
    $desc = $response->data[$m];
    $codecolumn = '';
    $codeexplode = explode("eduPersonOrgUnitDN=", $response->data[$n]);
    $codecolumn =str_replace(')', '', $codeexplode[1]);
    $descex = explode("=", $desc);
    $desccolumn = $descex[1];
    $ws_result[preg_replace('/\s+/', '', $codecolumn)]= $desccolumn;
    } 
    $final_diff_value = array_diff_assoc($ws_result,$results);

  if(!empty($final_diff_value)) {
    foreach($final_diff_value as $key=>$value) {
      $rows[] = array('data' => array('code' => $key, 'description' => $value));
    }
  }
   
  $header= array(
    'code' => array('data' => t('Code')),
    'description' => array('data' => t('Description')),
  );
  $tree = array();
  if(isset($rows)){
  foreach ($rows as $key => $value) {
    $tree[] =(object) $value;
  }
  }
  //Fix to pass the current page url to the pager
  //$_GET['q'] = "admin/im/getdynamics/magasin";
  //Prepare Pager items for the table
  if(!empty($tree)){
    $tree = pager_array_splice($tree, 4);
    //Limit the no.of rows to 15
    $rows = pager_array_splice($rows, 10);
  }
    
  $rows = array_map("unserialize", array_unique(array_map("serialize", $rows)));
  
  $output = '<div class ="table-trans-replace">';
  $output .= theme('table', array('header' => $header, 'rows' => $rows, ));
  $output .= theme('pager', array('quantity' => 4));
  $output .= '</div>';
  return $output;
	}
}
/**
*function to display data from portal database.
*/
function _im_user_getdynamics_format() { 
	$rows = _im_user_getdynamics(); 
  $header = array("Code", "Description");
  $output = '<div class ="table-trans-replace">';
  $output .= '<div id ="table-second-save">';
  $output .= theme('table', array('header' => $header, 'rows' => $rows, ));
  $output .= '</div></div>';
  return $output;
}
/**
*function called for ajax callback while drag and drop does save and delete.
*/

function  _im_user_getdynamics_saveresult_callback() {
	if(!empty($_POST['data'])){
  $str = $_POST['data'];
  $table_string = str_replace('<TD>', '<td>', $str);
  $table_string = str_replace('</TD>','<td>',$table_string);
  $table_string = str_replace('<td><td>','<td>',$table_string);
  $table_string = str_replace('</td>', '<td>', $table_string);
  
  $result = explode("<td>", $table_string);
 // print "<pre>";print_r($result);exit;
  foreach ($result as $key => $value) {  
    $value =trim($value);
    if (is_null($value) || $value == '')
      unset($result[$key]);
  }
  $result_count = count($result);
  $result = array_values($result);
  $final_array =array();
  $new_array =array();
  for ($i =1; $i < $result_count; $i = $i+2) {
    $code = '';
    $description = '';
    $code = (string)$result[$i];
    $i = $i+1;
    $description =(string)$result[$i];
    //print($code);echo '<br>';print($description);exit;
    $search_query = db_select('user_getdynamic', 'u')
      ->fields('u', array('code', 'description'))
      ->condition('u.code', $code, '=')
      ->condition('u.description', $description, '=')
      ->execute()->fetchField();
    if (!empty($code) && !empty($description) && empty($search_query)) {
    $insert_query = db_insert('user_getdynamic')
      ->fields(array('code', 'description'))
      ->values(array(
        'code' => $code,
        'description' => $description, ))
      ->execute();
    }
    $new_array = array($code => $description);
    $final_array = array_merge($new_array, $final_array);
    }
  $select_query =db_select('user_getdynamic', 'u')
    ->fields('u', array('code', 'description'))
    ->execute();
  while ($record =$select_query->fetchAllKeyed()) {
      $search_result= $record;
  }
  $diffs = array();
  $diffs = array_diff_key($search_result, $final_array);
  foreach ($diffs as $key => $value ) {
    $delete_query = db_delete('user_getdynamic')
      ->condition('code', $key)
      ->execute();
  }
	}
}