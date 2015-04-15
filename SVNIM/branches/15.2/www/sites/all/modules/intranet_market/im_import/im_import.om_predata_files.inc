<?php
/**
 * @file
 * This file is used to import all procedure contents attachment files
 */
/**
 * This function is used to import the Operational model attachment files into the appropriate path.
 */
function _im_import_procedure_files_batch_process() {
  $folder_path = drupal_realpath("private://exported_procedure/files");
  $files = _im_import_read_all_files($folder_path);
  ini_set('memory_limit','-1');
  $num_operations = ceil(count($files['files']) / 100);
  drupal_set_message(t('Importing procedure files @num operations', array('@num' => $num_operations))); 
  $operations = array();
  for ($i = 0; $i<$num_operations; $i++) {
    $operations[] = array('_im_import_procedure_files_batch_operation', array($files['files'], count($files['files']), $i));
  }
  $batch = array(
  'operations' => $operations,
  'finished' => '_im_import_procedure_files_batch_finished',
  );
  return $batch;
}


/**
 * Import the procedure contents attachment files
 * @param $files_folders array
 * @param $operation_details integer
 * @param $context array
 */
function _im_import_procedure_files_batch_operation($files, $total_files, $operation_details, &$context) {
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
  	if ($end > $total_files) {
  		$end = $total_files;
  	}
  }
  
  $context['results'][] = $context;
  $context['message'] = t("Operation - importing the procedure files");
  for($i = $start; $i <= $end; $i++) {
    $file_path = explode("exported_procedure/files", $files[$i]);
    $source = (object) array(
       'uid' => $user->uid,
       'uri' => trim($files[$i]),
       'filemime' => file_get_mimetype(trim($files[$i])),
       'status' => 1,
    );
     
    $dest = 'public://operational_model/' . $file_path[1]; 
    $dest = str_replace('public://operational_model//', 'public://operational_model/', $dest);
    file_copy($source, $dest, FILE_EXISTS_REPLACE);
  }
  _im_import_insert_procedure_files_update_http_requests();
}

/**
 * Batch process completions status function
 * @param $success boolean
 * @param $results array
 * @param $operations array
 */
function _im_import_procedure_files_batch_finished($success, $results, $operations) {
   if ($success) {
    // Here we could do something meaningful with the results.
    // We just display the number of nodes we processed...
    drupal_set_message(t('@count results processed in @requests HTTP requests.', array('@count' => count($results), '@requests' => _im_import_insert_procedure_files_get_http_requests())));
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
function _im_import_insert_procedure_files_update_http_requests() {
  $_SESSION['files_http_request_count']++;
}

/**
* Initialize the HTTP requests in a session variable.
*/
function _im_import_insert_procedure_files_get_http_requests() {
  return !empty($_SESSION['files_http_request_count']) ? $_SESSION['files_http_request_count'] : 0;
}