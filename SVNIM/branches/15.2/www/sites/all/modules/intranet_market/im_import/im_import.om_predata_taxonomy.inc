<?php
/**
 * @file
 * Inc file for im_import.om_predata_taxonomy.inc import the om_roles, operational_model_location and om_domains taxonomy terms
 */

/**
 * This function is used to initiage the batch process to import the om_roles, operational_model_location and om_domains taxonomy terms
 */
function _im_import_taxonomy_batch_process() {
  ini_set('memory_limit','-1');
  $num_operations = 3; // om_roles, operational_model_location and om_domains - 3 processes
  drupal_set_message(t('Creating vocabulary taxonomy term of @num operations', array('@num' => $num_operations))); 

  $vocabulary_machine_name_set = array("om_roles", "operational_model_location", "om_domains");
  $operations = array();
  for ($i = 0; $i<$num_operations; $i++) {
    $operations[] = array('_im_import_taxonomy_batch_operation', array($vocabulary_machine_name_set, $i));
  }
  $batch = array(
  'operations' => $operations,
  'finished' => '_im_import_insert_tt_batch_finished',
  );
  return $batch;
}

/**
 * Import the om_roles, operational_model_location and om_domains vocabulary taxonomy terms
 * @param $files_folders array
 * @param $operation_details integer
 * @param $context array
 */
function _im_import_taxonomy_batch_operation($vocabulary_machine_name_set, $operation_details, &$context) {
  ini_set('memory_limit','-1');
  set_time_limit(0);
  $vocabulary_name = array("Acteur procédure modèle opérationnel", "Emplacement modèle opérationnel", "Domaines modèle opérationnel");
  
  $inc = intval($operation_details);
  $context['results'][] = $context;
  $context['message'] = t("Operation - importing the @vocabulary terms", array("@vocabulary" => $vocabulary_name[$operation_details]));
  /**
   * Start the vocabulary taxonomy term importing process
   */
  $vocabulary_machine_name = $vocabulary_machine_name_set[$operation_details];
  $taxonomy_term_set = $taxonomy_term_sets[$operation_details];
  $vocabulary_object = taxonomy_vocabulary_machine_name_load($vocabulary_machine_name);
  // Extracting the om_roles vocabulary taxonomy terms from the appropriate exported .inc file
  $file_working_uri = drupal_realpath("private://exported_procedure/inc/taxonomy") . "/" . $vocabulary_machine_name_set[$operation_details] . ".inc";
  $fp = fopen($file_working_uri, "r");
  $om_terms = fread($fp, filesize($file_working_uri));
  fclose($fp);
  $om_terms = unserialize($om_terms);
  if ($vocabulary_machine_name == "om_domains") {
	  foreach ($om_terms as $key=>$term) {
	  	if (!isset($term->parents)) {
	      $term->vid = $vocabulary_object->vid;
	      unset($term->parents);
	      taxonomy_term_save($term);
	      unset($om_terms[$key]);
	  	}
	  }
    foreach ($om_terms as $key=>$term) {
	    $taxonomy_machine_name = 'om_domains';
	    $om_domains_vocabulary = taxonomy_vocabulary_machine_name_load($taxonomy_machine_name);
	    $om_domains_term_tree = taxonomy_get_tree($om_domains_vocabulary->vid);
	    $om_domains_term_tree_result = array();
	    foreach ($om_domains_term_tree as $key=>$om_domain_term) {
	      $om_domains_term_tree_result[$om_domain_term->name] = $om_domain_term->tid;
	    }
      $term->vid = $vocabulary_object->vid;
      $om_term_tid = 0;
      $om_term_tid = trim($om_domains_term_tree_result[$term->parents[0]]);
      $term->parent = array($om_term_tid => $om_term_tid);
      taxonomy_term_save($term);
    }
  }
  else {
	  foreach ($om_terms as $key=>$term) {
	  	$term->vid = $vocabulary_object->vid;
	    taxonomy_term_save($term);
	  }
  }
  _im_import_insert_t_update_http_requests();
}

/**
 * Batch process completions status function
 * @param $success boolean
 * @param $results array
 * @param $operations array
 */
function _im_import_insert_tt_batch_finished($success, $results, $operations) {
   if ($success) {
    // Here we could do something meaningful with the results.
    // We just display the number of nodes we processed...
    drupal_set_message(t('@count results processed in @requests HTTP requests.', array('@count' => count($results), '@requests' => _im_import_insert_t_get_http_requests())));
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
function _im_import_insert_t_update_http_requests() {
  $_SESSION['http_request_count']++;
}

/**
* Initialize the HTTP requests in a session variable.
*/
function _im_import_insert_t_get_http_requests() {
  return !empty($_SESSION['http_request_count']) ? $_SESSION['http_request_count'] : 0;
}