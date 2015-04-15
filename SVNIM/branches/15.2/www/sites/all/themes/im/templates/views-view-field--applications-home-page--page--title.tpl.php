<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<?php
$app_full_url = '';
$query_string = '';
if (isset($row->_field_data['nid']['entity']->field_app_send_anabel_code['und']['0']['value'])) {
  if ($row->_field_data['nid']['entity']->field_app_send_anabel_code['und']['0']['value'] == 1) {
    global $user;
    $user_load_result = user_load($user->uid);
    if (isset($user_load_result->field_user_stores['und'][0]['value'])) {
      if (strstr($user_load_result->field_user_stores['und'][0]['value'],',')) {
        $explode_store_field = explode(",", $user_load_result->field_user_stores['und'][0]['value']);
        $first_prefered_store = $explode_store_field[0];
      }
      else {
        $first_prefered_store = $user_load_result->field_user_stores['und'][0]['value'];
      }
      $query = "select ite_lib_value from store_item_fields where pve_code =:store_id and dit_cod_item = 'anabel'";
      if($_SESSION['user_selected_store']=='all'){
      	$result = db_query($query,array(':store_id' => $first_prefered_store))->fetchall();
      }else{
      	$result = db_query($query,array(':store_id' => $_SESSION['user_selected_store']))->fetchall();
      }
      $query_string = '?anabel='.$result[0]->ite_lib_value;
    }
  }
}

if(isset($row->_field_data['nid']['entity']->field_ldap_sso_redirect['und']['0']['value']) && isset($row->_field_data['nid']['entity']->field_app_url['und']['0']['value'])) {
  if ($row->_field_data['nid']['entity']->field_ldap_sso_redirect['und']['0']['value'] ==  '-none-' && !empty($row->_field_data['nid']['entity']->field_app_url['und']['0']['value'])) {
    if (!empty($query_string)) {
      $app_full_url = $row->_field_data['nid']['entity']->field_app_url['und']['0']['value'].$query_string;
    }
    else{
      $app_full_url = $row->_field_data['nid']['entity']->field_app_url['und']['0']['value'];
    }
  }
}
if(isset($row->_field_data['nid']['entity']->field_ldap_sso_redirect['und']['0']['value'])) {
  if(!empty($row->_field_data['nid']['entity']->field_ldap_sso_redirect['und']['0']['value']) && $row->_field_data['nid']['entity']->field_ldap_sso_redirect['und']['0']['value'] != '-none-' ) {
    $app_name = $row->_field_data['nid']['entity']->field_ldap_sso_redirect['und']['0']['value'];
    include_once drupal_get_path('module', 'im_user') . '/im_user.profile.inc';
    if (isset($_SESSION['ldap_login_key'])) {
      $app_names ='';
      //$ladp_id = '8e5a5f10-4420-4517-a2d0-2179356947af';
      $ladp_id = $_SESSION['ldap_login_key'];
      $obj = new imldapSoapService();
      $profile = $obj->soapRequest('getProfil', array('id' => $ladp_id));
      if (isset($profile) && !empty($profile)){
         $profile = simplexml_load_string($profile->data);
         foreach($profile->app as $key => $value){
         	if(strcmp(trim($app_name), trim($value->name)) == 0){
             $ws_app_url= $value->url;
             $app_url = strstr($ws_app_url, "http://");
              $app_url_with_https = strstr($ws_app_url, "https://");
             if (empty($app_url) && empty($app_url_with_https)) { 
               if (!empty($query_string)) {
                 $app_full_url = "http://" . $ws_app_url.str_replace('?', '&', $query_string);
               }
               else {
                 $app_full_url = "http://" . $ws_app_url;
               }
             }
             else{
               if (!empty($query_string)) {
                 $app_full_url = $ws_app_url.str_replace('?', '&', $query_string);
               }
               else{
                 $app_full_url = $ws_app_url;
               }
             }
           }
         }
      }
    }
    else {
      $app_full_url = '';
    }
  }
}
print l($output,$app_full_url,array('attributes'=> array('target' =>'_blank','onclick' => ' return xt_click(this, \'C\',\'5\',\'display::'.str_replace(" ","_", rawurlencode(rawurldecode($output))).'\',\'A\')')));