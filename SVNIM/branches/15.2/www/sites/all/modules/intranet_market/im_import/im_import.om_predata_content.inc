<?php
/**
 * @file
 * This file is used to import all procedure node contents
 */
/**
 * This function is used to import the Operational model node contents.
 */
function _im_import_procedure_contents_batch_process() {
  $file_working_uri = drupal_realpath("private://exported_procedure") . '/inc/node/operational_model.inc';
  $fp = fopen($file_working_uri, "r");
  $file_content = fread($fp, filesize($file_working_uri));
  fclose($fp);
  $file_content = unserialize($file_content);
  /**
   * Start - om_roles, operational_model_location and om_domains Vocabulary taxonomy term object creation
   */
  $vocabulary_machine_name_set = array("om_roles" => "om_roles", "operational_model_location" => "operational_model_location", "om_domains" => "om_domains");
  $om_taxonomy_set = array();
  foreach ($vocabulary_machine_name_set as $key=>$vocabulary) {
    $vocabulary_object = taxonomy_vocabulary_machine_name_load($vocabulary);
    $om_term_tree = taxonomy_get_tree($vocabulary_object->vid);
    foreach ($om_term_tree as $termkey=>$value) {
      $om_taxonomy_set[$key][$value->name] = $value->tid;
    }
  }
  /**
   * End - om_roles, operational_model_location and om_domains Vocabulary taxonomy term object creation
   */
  ini_set('memory_limit','-1');
  $num_operations = ceil(count($file_content) / 100);
  drupal_set_message(t('Importing procedure node contents @num operations', array('@num' => $num_operations))); 
  $operations = array();
  for ($i = 0; $i<$num_operations; $i++) {
    $operations[] = array('_im_import_procedure_content_batch_operation', array($file_content, count($file_content), $om_taxonomy_set, $i));
  }
  $batch = array(
  'operations' => $operations,
  'finished' => '_im_import_procedure_content_batch_finished',
  );
  return $batch;
}

/**
 * Import the procedure contents attachment files
 * @param $files_folders array
 * @param $operation_details integer
 * @param $context array
 */
function _im_import_procedure_content_batch_operation($file_content, $total_noof_contents, $om_taxonomy_set, $operation_details, &$context) {
  global $user;
  ini_set('memory_limit','-1');
  set_time_limit(0);
  $inc = intval($operation_details) + 1;
  if ($operation_details == 0) {
    $start = 0;
    $end = 99;
  }
  else {
    $start = $operation_details * 100;
    $end = $start + 99;
    if ($end > $total_noof_contents) {
      $end = $total_noof_contents;
    }
  }
  
  $context['results'][] = $context;
  $context['message'] = t("Operation - importing the procedure node contents");
  for($i = $start; $i <= $end; $i++) {
    $node = new stdClass();
    $node->type = 'operational_model';
    node_object_prepare($node);
  
    // Replace the taxonomy terms tid to the appropriate node content taxonomy reference field.
    // om_roles vocabulary
    foreach (reset($file_content[$i]->field_om_actuers) as $key=>$term) {
      if (!empty($term['tid']) && !empty($om_taxonomy_set['om_roles'][$term['tid']])) {
        $file_content[$i]->field_om_actuers['und'][$key]['tid'] = $om_taxonomy_set['om_roles'][$term['tid']];
        $node->field_om_actuers['und'][$key]['tid'] = $om_taxonomy_set['om_roles'][$term['tid']];
      }
    }
    // operational_model_location
    foreach (reset($file_content[$i]->field_om_location) as $key=>$term) {
      if (!empty($term['tid']) && !empty($om_taxonomy_set['operational_model_location'][$term['tid']])) {
        $file_content[$i]->field_om_location['und'][$key]['tid'] = $om_taxonomy_set['operational_model_location'][$term['tid']];
        $node->field_om_location['und'][$key]['tid'] = $om_taxonomy_set['operational_model_location'][$term['tid']];
      }
    }
    // om_domains : Main domain
    foreach (reset($file_content[$i]->field_om_domain) as $key=>$term) {
      if (!empty($term['tid']) && !empty($om_taxonomy_set['om_domains'][$term['tid']])) {
        $file_content[$i]->field_om_domain['und'][$key]['tid'] = $om_taxonomy_set['om_domains'][$term['tid']];
        $node->field_om_domain['und'][$key]['tid'] = $om_taxonomy_set['om_domains'][$term['tid']];
      }
    }
   // om_domains : Sub domain
    foreach (reset($file_content[$i]->field_om_subdomain) as $key=>$term) {
      if (!empty($term['tid']) && !empty($om_taxonomy_set['om_domains'][$term['tid']])) {
        $file_content[$i]->field_om_subdomain['und'][$key]['tid'] = $om_taxonomy_set['om_domains'][$term['tid']];
        $node->field_om_subdomain['und'][$key]['tid'] = $om_taxonomy_set['om_domains'][$term['tid']];
      }
    }
    // om_domains : Macro domain
    foreach (reset($file_content[$i]->field_om_macro_activity) as $key=>$term) {
      if (!empty($term['tid']) && !empty($om_taxonomy_set['om_domains'][$term['tid']])) {
        $file_content[$i]->field_om_macro_activity['und'][$key]['tid'] = $om_taxonomy_set['om_domains'][$term['tid']];
        $node->field_om_macro_activity['und'][$key]['tid'] = $om_taxonomy_set['om_domains'][$term['tid']];
      }
    }
    $reference_code = $file_content[$i]->field_om_reference_procedure['und'][0]['value'];
    $reference_code = explode("/", $reference_code);
    unset($_SESSION['field_om_reference_procedure_code']);
    //$_SESSION['field_om_reference_procedure_code'] = $reference_code[0] . '/' . $reference_code[1] . '/';
    
    $node->log = $file_content[$i]->log;
    $node->status = $file_content[$i]->status;
    $node->language = $file_content[$i]->language;
    $node->field_om_publication_period = $file_content[$i]->field_om_publication_period;
    $node->field_om_access = $file_content[$i]->field_om_access;
    $node->field_om_experts = $file_content[$i]->field_om_experts;
    $node->field_om_macro_activity = $file_content[$i]->field_om_macro_activity;
    $node->field_om_actuers = $file_content[$i]->field_om_actuers;
    $node->field_parent_nid = $file_content[$i]->field_parent_nid;
    $node->field_om_location = $file_content[$i]->field_om_location;
    $node->field_om_version = $file_content[$i]->field_om_version;
    $node->field_om_subdomain = $file_content[$i]->field_om_subdomain;
    $node->field_om_status = $file_content[$i]->field_om_status;
    $node->field_draft_status = $file_content[$i]->field_draft_status;
    
    $node->field_node_archive = $file_content[$i]->field_node_archive;
    $node->field_om_domain = $file_content[$i]->field_om_domain;
    $node->field_om_material = $file_content[$i]->field_om_material;
    $node->field_om_objective = $file_content[$i]->field_om_objective;
    $node->body = $file_content[$i]->body;
    $node->field_om_duration = $file_content[$i]->field_om_duration;  
    $node->title = $file_content[$i]->title;
    $node->uid = $user->uid;
    if ($file_content[$i]->status == 0 && $file_content[$i]->workbench_moderation['published']->published == 0) {
      $node->status = 0;
      $node->field_draft_status['und'][0]['value'] = 1;
      $node->field_node_archive['und'][0]['value'] = 0;
    }
    else if($file_content[$i]->status == 0 && $file_content[$i]->workbench_moderation['published']->published == 1) {
      $node->status = 0;
      $node->field_draft_status['und'][0]['value'] = 0;
      $node->field_node_archive['und'][0]['value'] = 1;
    }
    else if($file_content[$i]->status == 1){
      $node->status = 1;
      $node->field_draft_status['und'][0]['value'] = 0;
      $node->field_node_archive['und'][0]['value'] = 0;
    }
    
    
    if ($file_content[$i]->status == 0) {
      $node->status = 0;
      $node->field_draft_status['und'][0]['value'] = 1;
      $node->field_node_archive['und'][0]['value'] = 0;
    }
    foreach (reset($file_content[$i]->field_om_attachments) as $key=>$value) {
      if (!empty($value['uri'])) {
        $aquery = db_query("SELECT fid FROM {file_managed} WHERE uri = :uri", array(':uri' => $value['uri']))->fetchCol();
        $file = '';
        if (!empty($aquery[0])) {
          $file = file_load($aquery[0]);
          $file->filename = $value['filename'];
          $file = file_save($file);
          $file = (array)$file;
          $file['display'] = $value['display'];
          $file['description'] = '';
          $node->field_om_attachments['und'][$key] = $file;
        }
      }
    }
    $_SESSION['procedure_valid_content_count']++;
    if (is_object($file_content[$i]) && !empty($file_content[$i]->title)) {
      node_save($node);
      if ($file_content[$i]->status == 0){
        workbench_moderation_moderate($node,'draft');
      }
      else{
        workbench_moderation_moderate($node,'published');
      }
      $valid_node_log = "S.No - " . $_SESSION['procedure_valid_content_count'] . "\tTitle - " . $file_content[$i]->title . "\n";
      $file_working_uri = drupal_realpath("private://exported_procedure/inc") . '/node/logs/operational_model_imported.log';
      file_put_contents($file_working_uri, $valid_node_log, FILE_APPEND);
    }
  }
  _im_import_insert_procedure_content_update_http_requests();
}

/**
 * Batch process completions status function
 * @param $success boolean
 * @param $results array
 * @param $operations array
 */
function _im_import_procedure_content_batch_finished($success, $results, $operations) {
   if ($success) {
    // Here we could do something meaningful with the results.
    // We just display the number of nodes we processed...
     drupal_set_message(t('@count results processed in @requests HTTP requests.', array('@count' => count($results), '@requests' => _im_import_insert_procedure_content_get_http_requests())));
    //drupal_set_message(t('The final result was "%final"', array('%final' => end($results))));
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
  } 
}

/**
* Utility function to count the HTTP requests in a session variable.
*/
function _im_import_insert_procedure_content_update_http_requests() {
  $_SESSION['content_http_request_count']++;
}

/**
* Initialize the HTTP requests in a session variable.
*/
function _im_import_insert_procedure_content_get_http_requests() {
  return !empty($_SESSION['content_http_request_count']) ? $_SESSION['content_http_request_count'] : 0;
}