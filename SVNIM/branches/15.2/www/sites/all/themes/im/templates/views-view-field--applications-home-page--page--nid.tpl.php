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
$userProfile = user_load($user->uid);
$app_title = $row->node_title;
if (!empty($userProfile->field_user_apps['und'][0]['value'])) {
  $app_store_value = $userProfile->field_user_apps['und'][0]['value'];
  $explode_value = explode("," , $app_store_value);
  $app_store = (in_array($app_title, $explode_value,TRUE));
  
  if (!empty($app_store)) {
    print l(t("Remove"), 'applications/remove', array('query'=>array('app' => $app_title),'attributes' => array('class' => 'remove-app-button')));
  }
  else{
    //print l(t("Add"),$row->node_title,array('attributes' => array('class' => 'add-app-button', 'onclick' => ' return xt_click(this, \'C\',\'5\',\'add::'.str_replace(" ","_",$row->node_title).'\',\'A\')')));
    print l(t("Add"), 'applications/add', array('query'=>array('app' => $app_title),'attributes' => array('class' => 'add-app-button', )));
  }
 }
else {
  //print l(t("Add"),$row->node_title,array('attributes' => array('class' => 'add-app-button', 'onclick' => 'return xt_click(this, \'C\',\'5\',\'add::'.str_replace(" ","_",$row->node_title).'\',\'A\')')));
  print l(t("Add"), 'applications/add', array('query'=>array('app' => $app_title),'attributes' => array('class' => 'add-app-button', )));
}