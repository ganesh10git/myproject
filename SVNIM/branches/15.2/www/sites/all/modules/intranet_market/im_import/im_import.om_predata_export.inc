<?php
/**
 * @file
 * Inc file for im_import.om_predata_export.inc export the OM procedures, domain, subdomain and macros predata.
 */

/**
 * This function is used to join the procedure nodes and its corresponding taxonomy exporting functions
 */
function _im_import_export_procedure_predata() {
  ini_set('memory_limit','-1');
  set_time_limit(0);
  // Export Acteur procédure modèle opérationnel (om_roles) vocabulary taxonomy terms
  $om_role = _im_import_export_procedure_roles_taxonomy();
  // Export Emplacement modèle opérationnel (operational_model_location) vocabulary taxonomy terms
  $om_location = _im_import_export_procedure_location_taxonomy();
  // Export Domaines modèle opérationnel (om_domains) vocabulary taxonomy terms
  $om_domain = _im_import_export_procedure_domains_taxonomy();
  // Export procedure nodes
  _im_import_export_procedure_nodes($om_role, $om_location, $om_domain);
  return '';
}

/**
 * This function is used to export the om_roles vocabulary taxonomy terms
 */
function _im_import_export_procedure_roles_taxonomy() {
	ini_set('memory_limit','-1');
  $taxonomy_machine_name = 'om_roles';
  $om_roles_vocabulary = taxonomy_vocabulary_machine_name_load($taxonomy_machine_name);
  $om_roles_term_tree = taxonomy_get_tree($om_roles_vocabulary->vid);
  $om_roles_term_tree_full_set = array();
  foreach ($om_roles_term_tree as $key=>$om_role) {
    $om_roles_term_tree_result[$om_roles_term_tree[$key]->tid] = $om_roles_term_tree[$key]->name;
    $tmp = taxonomy_term_load_multiple(array($om_roles_term_tree[$key]->tid));
    $tmp = $tmp[$om_roles_term_tree[$key]->tid];
    $om_roles_term_tree_full_set[] = $tmp;
    unset($om_roles_term_tree_full_set[$key]->tid);
    unset($om_roles_term_tree_full_set[$key]->vid);
  }
  $om_roles_terms = serialize($om_roles_term_tree_full_set);
  $file_working_uri = drupal_realpath("private://exported_procedure/inc") . '/taxonomy/om_roles.inc';
  $fp = fopen($file_working_uri, "w");
  fwrite($fp, $om_roles_terms, strlen($om_roles_terms));
  fclose($fp);
  drupal_set_message(t("Successfully exported the om_roles vocabulary taxonomy terms in a .inc file format"));
  return $om_roles_term_tree_result;
}

/**
 * This function is used to export the operational_model_location vocabulary taxonomy terms
 */
function _im_import_export_procedure_location_taxonomy() {
	ini_set('memory_limit','-1');
  $taxonomy_machine_name = 'operational_model_location';
  $om_locations_vocabulary = taxonomy_vocabulary_machine_name_load($taxonomy_machine_name);
  $om_locations_term_tree = taxonomy_get_tree($om_locations_vocabulary->vid);
  $om_locations_term_tree_full_set = array();
  foreach ($om_locations_term_tree as $key=>$om_location) {
  	$om_locations_term_tree_result[$om_locations_term_tree[$key]->tid] = $om_locations_term_tree[$key]->name;
  	$tmp = taxonomy_term_load_multiple(array($om_locations_term_tree[$key]->tid));
  	$tmp = $tmp[$om_locations_term_tree[$key]->tid];
    $om_locations_term_tree_full_set[] = $tmp;
    unset($om_locations_term_tree_full_set[$key]->tid);
    unset($om_locations_term_tree_full_set[$key]->vid);
  }
  $om_locations_terms = serialize($om_locations_term_tree_full_set);
  $file_working_uri = drupal_realpath("private://exported_procedure/inc") . '/taxonomy/operational_model_location.inc';
  $fp = fopen($file_working_uri, "w");
  fwrite($fp, $om_locations_terms, strlen($om_locations_terms));
  fclose($fp);
  drupal_set_message(t("Successfully exported the operational_model_location vocabulary taxonomy terms in a .inc file format"));
  return $om_locations_term_tree_result;
}

/**
 * This function is used to export the om_domains vocabulary taxonomy terms
 */
function _im_import_export_procedure_domains_taxonomy() {
	ini_set('memory_limit','-1');
  $taxonomy_machine_name = 'om_domains';
  $om_domains_vocabulary = taxonomy_vocabulary_machine_name_load($taxonomy_machine_name);
  $om_domains_term_tree = taxonomy_get_tree($om_domains_vocabulary->vid);
  foreach ($om_domains_term_tree as $key=>$om_domain) {
    $om_domains_term_tree_reset[$om_domain->tid] = $om_domain;
  }
  $om_domains_term_tree_full_set = array();
  foreach ($om_domains_term_tree as $key=>$om_domain) {
    $om_domains_term_tree_result[$om_domains_term_tree[$key]->tid] = $om_domains_term_tree[$key]->name;
    $tmp = taxonomy_term_load_multiple(array($om_domains_term_tree[$key]->tid));
    $tmp = $tmp[$om_domains_term_tree[$key]->tid];
    if ($om_domains_term_tree[$key]->parents[0] > 0) {
      $tmp->parents[0] = $om_domains_term_tree_reset[$om_domains_term_tree[$key]->parents[0]]->name;
    }
    $om_domains_term_tree_full_set[] = $tmp;
    unset($om_domains_term_tree_full_set[$key]->tid);
    unset($om_domains_term_tree_full_set[$key]->vid); 
  }
  $om_domains_terms = serialize($om_domains_term_tree_full_set);
  $file_working_uri = drupal_realpath("private://exported_procedure/inc") . '/taxonomy/om_domains.inc';
  $fp = fopen($file_working_uri, "w");
  fwrite($fp, $om_domains_terms, strlen($om_domains_terms));
  fclose($fp);
  drupal_set_message(t("Successfully exported the om_domains vocabulary taxonomy terms in a .inc file format"));
  return $om_domains_term_tree_result;
}

/**
 * This function is used to export the operational_model type contents
 */
function _im_import_export_procedure_nodes($om_roles, $om_locations, $om_domains) {
  ini_set('memory_limit','-1');
  $GLOBALS['conf']['cache'] = FALSE;
  $overall_nodes = array();
  // Set the node inc file exporting path
  $working_uri = 'private://exported_procedure/files';
  // Variable declaration for the valid and invalid content separation
  $valid_node_log = "";
  $valid_nodes_id = array();
  $valid_node_count = 0;
  
  $field = 'field_om_attachments';
  
  $query = db_select('node', 'n');
  $query->fields('n',array('nid'));
  $query->condition('type', 'operational_model', '=');
  $query->orderBy('changed', 'DESC');
  $result = $query->execute();
  $node_list = $result->fetchCol(); 
  foreach($node_list as $k=>$node) {
    ini_set('memory_limit','-1');
    $node_invalid = FALSE;
    $node = node_load($node);
    $node_nid = $node->nid;
    /**
     * Start - Replace the om_roles, operational_model_location and om_domains vocabulary taxonomy term tids to term name 
     */
    //Reset the om_roles taxonomy term set
    if (is_array(reset($node->field_om_actuers))) {
	    foreach (reset($node->field_om_actuers) as $key=>$om_role) {
	      if (!empty($om_roles[$om_role['tid']])) {
	        $node->field_om_actuers['und'][$key]['tid'] = $om_roles[$om_role['tid']];
	      }
	    }
    }
    //Reset the operational_model_location taxonomy term set
    if (is_array(reset($node->field_om_location))) {
	    foreach (reset($node->field_om_location) as $key=>$om_location) {
	      if (!empty($om_locations[$om_location['tid']])) {
	        $node->field_om_location['und'][$key]['tid'] = $om_locations[$om_location['tid']];
	      }
	    }
    }
    //Reset the om_domains taxonomy term set - Domain value
    if (is_array(reset($node->field_om_domain))) {
	    foreach (reset($node->field_om_domain) as $key=>$om_domain) {
	      if (!empty($om_domains[$om_domain['tid']])) {
	        $node->field_om_domain['und'][$key]['tid'] = $om_domains[$om_domain['tid']];
	      }
	    }
    }
    //Reset the om_domains taxonomy term set - Subdomain value
    if (is_array(reset($node->field_om_subdomain))) {
	    foreach (reset($node->field_om_subdomain) as $key=>$om_domain) {
	      if (!empty($om_domains[$om_domain['tid']])) {
	        $node->field_om_subdomain['und'][$key]['tid'] = $om_domains[$om_domain['tid']];
	      }
	    }
    }
    //Reset the om_domains taxonomy term set - Macro value
    if (is_array(reset($node->field_om_macro_activity))) {
	    foreach (reset($node->field_om_macro_activity) as $key=>$om_domain) {
	      if (!empty($om_domains[$om_domain['tid']])) {
	        $node->field_om_macro_activity['und'][$key]['tid'] = $om_domains[$om_domain['tid']];
	      }
	    }
    }
    /**
     * End - Replace the om_roles, operational_model_location and om_domains vocabulary taxonomy term tids to term name 
     */
    
    /**
     * Start - Attachment file managing code 
     */
    $content_type_total['operational_model'] = isset($content_type_total['operational_model']) ? $content_type_total['operational_model'] + 1 : 1;
    if (isset($node->$field) && is_array(reset($node->$field))) {
      foreach(reset($node->$field) as $file) {
        if (file_exists(drupal_realpath($file['uri']))) {
          $valid_files[$node_nid][] = drupal_realpath($file['uri']);
          file_copy((object)$file, $working_uri, FILE_EXISTS_REPLACE);
        }
      }
    }
    $valid_node_count++;
    $valid_node_log .= "S.No - " . $valid_node_count . "\tNid - " . $node_nid . "\tType - operational_model \tTitle - " . $node->title . "\n";
    unset($node->nid);
    unset($node->vid);
    $overall_nodes[] = $node;
    /**
     * End - Attachment file managing code 
     */
  }
 
  $content = serialize($overall_nodes);
  $file_working_uri = drupal_realpath("private://exported_procedure/inc") . '/node/operational_model.inc';
  $fp = fopen($file_working_uri, "w");
  fwrite($fp, $content, strlen($content));
  fclose($fp);
  
  $content = $valid_node_log;
  $file_working_uri = drupal_realpath("private://exported_procedure/inc") . '/node/logs/operational_model.log';
  $fp = fopen($file_working_uri, "w");
  fwrite($fp, $content, strlen($content));
  fclose($fp);
  
  drupal_set_message(t("Successfully Exported the Operational Model (Procedure type) contents"));
}