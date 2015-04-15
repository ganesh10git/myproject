<?php
/**
 * @file
 * Inc file for im_import OM procedures, domain, subdomain and macros.
 */

/**
 * Callback - Import OM notes and Domain, subdomain, macro path settings form and Start batch process button form
 */
function _im_import_domain_asset_xml() {
  return drupal_get_form('_im_import_domain_asset_form');
}

/**
 * Used to set the file url path
 * @param $filename string
 * @param $fileset_array array
 */
function _im_import_set_file_path($filename, $fileset_array) {
  $url = file_create_url(variable_get('domain_xml_dest_file_path', 'sites/default/files/public/operational_model'));
  $path = '';
  foreach ($fileset_array as $key=>$fileset) {
  	if (strcasecmp($fileset['filename'], $filename) == 0) {
      $path = trim(file_create_url($fileset['uri']));
    }
    else if ($fileset['filename'] == $filename) {
      $path = trim(file_create_url($fileset['uri']));
    }
  }
  if (empty($path)) {
    $path = $url . '/' . $filename;
  }
  return urldecode($path);
}

/**
 * Set the body content attachment link attributes
 * @param $str string
 */
function _im_import_format_link_attributes($str) {
  $tmp_bcontent[0] = $str;
  $attributes_set = substr($tmp_bcontent[0], strpos($tmp_bcontent[0], '||')+2, strlen($tmp_bcontent[0]));
  $attributes_set = explode('"', $attributes_set);
  $attributes = array();
  $attributes_key = array();
  $attributes_value = array();
  for($i=0; $i<count($attributes_set); $i++) {
    if (!empty($attributes_set[$i])) {
      if ($i % 2 == 0) {
        $attributes_key[] = $attributes_set[$i];
      }
      else {
        $attributes_value[] = $attributes_set[$i];
      }
    }
  }
  for ($i=0; $i<count($attributes_key); $i++) {
    $key = trim(str_replace("=", "", $attributes_key[$i]));
    $attributes[$key] = trim($attributes_value[$i]);
  }
  return $attributes;
}

/**
 * Implements of hook_form().
 * Import OM notes and Domain, subdomain, macro path settings form and Start batch process button form
 * @param $form array
 * @param $form_state array
 */
function _im_import_domain_asset_form($form, &$form_state) {
  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  );
  $form['fieldset']['source_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Source path'),
    '#required' => TRUE,
    '#default_value' => variable_get("im_import_domain_xml_source_path", "private://import_domain_subdomain"),
  );
  $form['fieldset']['dist_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Destination path'),
    '#required' => TRUE,
    '#default_value' => variable_get("im_import_domain_xml_dest_path", "private://imported_domain_subdomain"),
  );
  $form['fieldset']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('_im_import_domain_asset_form_variable_submit'),
  );
  $form['fieldset_process'] = array(
    '#type' => 'fieldset',
    '#title' => t('Import Domain, Subdomain, Macro and Procedures'),
  );
  $form['fieldset_process']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Start Process'),
    '#submit' => array('_im_import_domain_asset_form_xml_process'),
  );
  return $form;
}

/**
 * Implements of hook_form_submit().
 * hook_form_submit - Import OM notes and Domain, subdomain, macro path settings form and Start batch process button form
 * @param $form array
 * @param $form_state array
 */
function _im_import_domain_asset_form_variable_submit($form, &$form_state) {
  if (variable_get("im_import_domain_xml_source_path", "private://import_domain_subdomain") != $form_state['values']['source_path']) {
   _im_import_file_system_create_directory_system('im_import', 'domain_xml_source_path', $form_state['values']['source_path']);
  }
  if (variable_get("im_import_domain_xml_dest_path", "private://imported_domain_subdomain") != $form_state['values']['dist_path']) {
   _im_import_file_system_create_directory_system('im_import', 'domain_xml_dest_path', $form_state['values']['dist_path']);
  }
  drupal_set_message(t("Successfully updated"));
}


/**
 * Initialize the Batch process : Import OM node, Domain, Subdomain and Macro
 * @param $form array
 * @param $form_state array
 */
function _im_import_domain_asset_form_xml_process($form, &$form_state) {
  $function = '_im_import_xml_batch_process';
  $_SESSION['http_request_count'] = 0; // reset counter for debug information.
  $batch = $function();
  batch_set($batch); 
}

/**
 * Batch Process operation setup : Import OM node, Domain, Subdomain and Macro
 */
function _im_import_xml_batch_process() {
  ini_set('memory_limit','-1');
  $domain = 1;
  $source_path = drupal_realpath(variable_get("im_import_domain_xml_source_path", "private://import_domain_subdomain"));
  $files = _im_import_read_all_files($source_path);
  $domain_folders = array();
  foreach ($files['dirs'] as $key=>$path) {
    if (strlen(str_replace('/', '', str_replace($source_path, '', $path))) == 3) {
      $domain_folders[] = str_replace('/', '', str_replace($source_path, '', $path));
    }
  }
  $num_operations = count($domain_folders);
  drupal_set_message(t('Creating Domain of @num operations', array('@num' => $num_operations))); 
  $operations = array();
  $files_folders = array("domain" => $domain_folders, "files" => $files['files']);
  for ($i = 0; $i<$num_operations; $i++) {
    // Each operation is an array consisting of
    // - the function to call
    // - An array of arguments to that function
    $operations[] = array('_im_import_xml_batch_process_xml_import_operation', array($files_folders, $i));
  }
  $batch = array(
  'operations' => $operations,
  'finished' => '_im_import_xml_batch_process_finished',
  );
  return $batch; 
}

/**
 * Import the domain and subdomain. Called the procedure and macro creation setup. Called the archive imported files and clear the imported files.
 * @param $files_folders array
 * @param $operation_details integer
 * @param $context array
 */
function _im_import_xml_batch_process_xml_import_operation($files_folders, $operation_details, &$context) {
	ini_set('memory_limit','-1');
	set_time_limit(0);
  $inc = intval($operation_details);
  $context['results'][] = $context;
  $context['message'] = t("Operation - Creating Domain : @domain & its subdomain, macro and procedures", array("@domain" => $files_folders['domain'][$inc])) . " " . ($operation_details +1);
  /**
   * Setup Domain term and create the Domain
   */
  $domain_term_id = '';
  $domainxmlfilename = drupal_realpath(variable_get("im_import_domain_xml_source_path", "private://import_domain_subdomain")) . "/" . $files_folders['domain'][$inc] . "/WebHome.xml";
  $taxonomy_machine_name = 'om_domains';
  $vocabulary = taxonomy_vocabulary_machine_name_load($taxonomy_machine_name);
  $domain_tree = taxonomy_get_tree($vocabulary->vid, 0, 1);
  $domain_xml_obj = new stdClass();
  $domain_xml_obj = simplexml_load_file($domainxmlfilename);
  foreach ($domain_tree as $key=>$domain_term_name) {
    if (strval($domain_term_name->name) == strval($domain_xml_obj->title)) {
      $domain_term_id = $domain_term_name->tid;
      break;
    }
  }
  $domainterms = array();
  if (empty($domain_term_id)) {
    $domainterms['code'] = $files_folders['domain'][$inc];
    $domainterms['name'] = $domain_xml_obj->title;
    if (!empty($domain_xml_obj->title))
      $domain_term_id = _im_import_create_domain_term($domainterms, $vocabulary);
    else
      $domain_term_id = '';
  }
  if ($domain_term_id) {
    $sub_domain_tree = taxonomy_get_tree($vocabulary->vid, $domain_term_id, 1);
  }
  else {
    $sub_domain_tree = taxonomy_get_tree($vocabulary->vid);
  }
  /**
   * Setup and create the Subdomain, Macro and Procedure
   */
  $xmlfilepath = drupal_realpath(variable_get("im_import_domain_xml_source_path", "private://import_domain_subdomain")) . "/" . $files_folders['domain'][$inc] . "/";
  $dest_xmlfilepath = drupal_realpath(variable_get("im_import_domain_xml_dest_path", "private://imported_domain_subdomain")) . "/" . $files_folders['domain'][$inc] . "/";
  $subdomain_name = array();
  $subdomain_code = array();
  foreach ($files_folders['files'] as $key=>$filename) {
    $procedure_file_name_flag = strval(substr($filename, 0, strpos($filename, "-")));
    /**
     * Subdomain Setup
     */
    
    if (strstr($filename, $xmlfilepath) && strlen(str_replace($xmlfilepath, '', $filename)) == 7) { // && str_replace($xmlfilepath, '', $filename) != $files_folders['domain'][$inc] . ".xml"
      $subdomain_xml_obj = new stdClass();
      $subdomain_xml_obj = simplexml_load_file($filename);
      $sub_domain_term_id = '';
      $subdomain_code[] = str_replace(".xml", '', str_replace($xmlfilepath, '', $filename));
      foreach ($sub_domain_tree as $key=>$sub_domain_term_name) {
        if (strval($sub_domain_term_name->name) == strval($subdomain_xml_obj->title) && $domain_term_id == $sub_domain_term_name->parents[0]) {
          $sub_domain_term_id = $sub_domain_term_name->tid;
          break;
        }
      }
      if (empty($sub_domain_term_id)) {
        $sub_domain_terms['code'] = str_replace(".xml", '', str_replace($xmlfilepath, '', $filename));
        $sub_domain_terms['name'] = $subdomain_xml_obj->title;
        $sub_domain_terms['parent_id'] = $domain_term_id;
        if (!empty($subdomain_xml_obj->title))
          $sub_domain_term_id = _im_import_create_sub_domain_term($sub_domain_terms, $vocabulary);
        else 
          $sub_domain_term_id = '';
      }
    }
    
  }
  _im_import_create_macro_all_procedure($files_folders['files'], $xmlfilepath, $files_folders['domain'][$inc], $domain_term_id);
  @mkdir($dest_xmlfilepath);
  _im_import_archive_imported_files($xmlfilepath, $dest_xmlfilepath);
  _im_import_file_system_delete_directory_system($xmlfilepath, TRUE);
  _im_import_update_http_requests(); 
}

/**
 * Create the OM node procedure and its Marco under the proper Domain & subdomain
 * @param $files_folders array
 * @param $xmlfilepath string
 * @param $domain_code string
 * @param $domain_term_id integer
 */
function _im_import_create_macro_all_procedure($files_folders, $xmlfilepath, $domain_code, $domain_term_id) {
	global $user;
	ini_set('memory_limit','-1');
	set_time_limit(0);
  $source_path = drupal_realpath(variable_get("im_import_domain_xml_source_path", "private://import_domain_subdomain"));
  $files = $files_folders;
  $taxonomy_machine_name = 'om_domains';
  $vocabulary = taxonomy_vocabulary_machine_name_load($taxonomy_machine_name);
  $domain_term_tid_value = $domain_term_id;
  $sub_domain_term_tree = taxonomy_get_tree($vocabulary->vid, $domain_term_id, 1);
  $term_ids = array();
  $domain_code_id = array();
  foreach ($sub_domain_term_tree as $key=>$value) {
    $term_obj = taxonomy_term_load_multiple(array($value->tid));
    $sub_domain_code_id[$key]['tid'] = $value->tid;
      if (isset($term_obj[$value->tid]->field_taxo_om_code['und'][0]['value'])) {
       $sub_domain_code_id[$key]['code'] = $term_obj[$value->tid]->field_taxo_om_code['und'][0]['value'];
      }
      else {
        $sub_domain_code_id[$key]['code'] = '';
      }
    $sub_domain_code_id[$key]['parent'] = $value->parents[0];
  }
  $attachment = array();
  $attachment_array_set = array();
  $attachment_asset = array();
  $attachment_array = array();
  $om_node = '';
  unset($om_node);
  foreach ($files as $key=>$filename) {
   	$attachment = array();
  	$attachment_array_set = array();
  	$attachment_asset = array();
  	$attachment_array = array();
    $procedure_file_name_flag = strval(substr($filename, 0, strpos($filename, "-")));
    if(strstr($filename, "-") && is_numeric(substr($filename, strpos($filename, "-")+1, 1)) && strlen(str_replace($xmlfilepath, "", substr($filename, 0, strpos($filename, "-")))) == 3){ // && str_replace($xmlfilepath, "", substr($filename, 0, strpos($filename, "-"))) != "PIL"
    	$procedure_xml_obj = new stdClass();
      $procedure_xml_obj = @simplexml_load_file($filename);
      if (count($procedure_xml_obj) == 0 || empty($procedure_xml_obj) || !is_object($procedure_xml_obj)) {
        $fc = file_get_contents($filename, "r");
        $procedure_xml_obj = @simplexml_load_string($fc);
        if (count($procedure_xml_obj) == 0 || empty($procedure_xml_obj) || !is_object($procedure_xml_obj)) {
        	$ar = 0;
          $attachment_array_set = explode("</attachment>", $fc);
          $attachment = substr($attachment_array_set[0], 0, strpos($attachment_array_set[0], '<attachment>'));
          if ((!strstr($attachment_array[$ar], '<filename>') && !strstr($attachment_array[$ar], '<attachment>'))) {
            $attachment .= $attachment_array_set[count($attachment_array_set)-1];
          } 
          else {
            $attachment .= '</xwikidoc>';
          }
          for($ar=0; $ar<count($attachment_array_set); $ar++) {
            if ($ar == 0) {
              $attachment_array[$ar] = substr($attachment_array_set[$ar], strpos($attachment_array_set[$ar], '<attachment>'), strlen($attachment_array_set[$ar]));
            }
            else if ($ar == count($attachment_array_set)-1 && (!strstr($attachment_array[$ar], '<filename>') && !strstr($attachment_array[$ar], '<attachment>'))) {
              $attachment_array[$ar] = $attachment_array_set[$ar];
            }
            else {
              $attachment_array[$ar] = $attachment_array_set[$ar];
            }
          }
          for($a=0; $a<count($attachment_array); $a++) {
            if (!empty($attachment_array[$a])) {
              $temp = '';
              $tfname = array();
              $tcontent = array();
              $temp = '<?xml version="1.0" encoding="UTF-8"?><xwikidoc>' . $attachment_array[$a] . '</attachment></xwikidoc>';
              $temp = @simplexml_load_string($temp);
              if (empty($temp)) {
                $tfirst = explode("</filename>", $attachment_array[$a]);
                $tsecond = explode("<content>", $attachment_array[$a]);
                $attachment_asset[$a]['attach_filename'] = strip_tags($tfirst[0]);
                $attachment_asset[$a]['attach_content'] =  strip_tags($tsecond[1]);
              }
              else {
                $tfname = (array)$temp->attachment->filename;
                $tcontent = (array)$temp->attachment->content;
                $attachment_asset[$a]['attach_filename'] = implode("", $tfname);//trim(strip_tags(str_replace('</filename>', "", substr($attachment_array[$a], strpos($attachment_array[$a], '<filename>') + strlen('<filename>'), strpos($attachment_array[$a], '</filename>')))));
                $attachment_asset[$a]['attach_content'] = implode("", $tcontent);//strip_tags(str_replace('</content>', "", substr($attachment_array[$a], strpos($attachment_array[$a], '<content>') + strlen('<content>'), strpos($attachment_array[$a], '</content>'))));
              }
            }
          }
          //$fc = str_replace($attachment, "", $fc);
          $procedure_xml_obj = @simplexml_load_string($attachment);
        }
      }
      $sub_domain_code = str_replace($xmlfilepath, "", substr($filename, 0, strpos($filename, "-")));
      $sub_domain_term_tid_value = '';
      foreach ($sub_domain_code_id as $key=>$term_set) {
        if (strval($term_set['code']) === strval($sub_domain_code) && intval($domain_term_tid_value) == intval($term_set['parent'])) {
          $sub_domain_term_tid_value = $term_set['tid'];
          break;
        }
      }
      $macro_flag = $procedure_xml_obj->parent;
      /**
       * Macro Setup and create it
       */
      $macro_term_id = '';
      if (!empty($macro_flag) && $macro_flag != $domain_code . ".WebHome" && $macro_flag != $sub_domain_code . ".WebHome" && $macro_flag != $domain_code . "." . $sub_domain_code && $macro_flag != $sub_domain_code . "." . $domain_code) {
        if (!empty($sub_domain_term_tid_value)) {
          $macro_sub_domain_tree = taxonomy_get_tree($vocabulary->vid, $sub_domain_term_tid_value, 1);
        }
        else {
          $macro_sub_domain_tree = taxonomy_get_tree($vocabulary->vid);
        }
        foreach ($macro_sub_domain_tree as $key=>$macro_sub_domain_term_name) {
          if (strval($macro_sub_domain_term_name->name) == substr($macro_flag, 4, strlen($macro_flag))) { //strval(str_replace(".xml", '', str_replace($xmlfilepath, '', $filename)))) {
            $macro_term_id = $macro_sub_domain_term_name->tid;
            break;
          }
        }
        $macro_name_tmp = substr($macro_flag, 4, strlen($macro_flag));
        if (empty($macro_term_id) && !empty($macro_name_tmp)) {
          $macro_sub_domain_terms['name'] = substr($macro_flag, 4, strlen($macro_flag));
          $macro_sub_domain_terms['parent_id'] = $sub_domain_term_tid_value;
          if (!empty($macro_sub_domain_terms['name']))
            $macro_term_id = _im_import_create_macro_term($macro_sub_domain_terms, $vocabulary);
          else 
            $macro_term_id = '';
        }
      }
      /**
       * Procedure setup and create it (Operational Model content create)
       */
      $om_node = new stdClass();
      $om_node->type = "operational_model";
      $tmp_var = '';
      $tmp_var = (array)$procedure_xml_obj->title;
      node_object_prepare($om_node);
      $om_node->language = LANGUAGE_NONE;
      $node_title = implode("", $tmp_var);
      if (!empty($node_title)) {
	      $om_node->title = $node_title;
	      $om_node->field_om_domain['und'][0]['tid'] = $domain_term_tid_value;
	      if (!empty($sub_domain_term_tid_value)) {
	        $om_node->field_om_subdomain['und'][0]['tid'] = $sub_domain_term_tid_value;
	      }
	      else {
	        $om_node->field_om_subdomain['und'] = array();
	      }
	      if (!empty($macro_term_id)) {
	        $om_node->field_om_macro_activity['und'][0]['tid'] = $macro_term_id;
	      }
	      else {
	        $om_node->field_om_macro_activity['und'] = array();
	      }
	      $om_node->field_om_version['und'][0]['value'] = 1;
	      $om_node->field_om_publication_period['und'][0]['value'] = date("Y-m-d") . "T" . date("H:i:s");//2013-11-05T00:00:00
	      $om_node->field_om_publication_period['und'][0]['value2'] = date('Y-m-d', mktime(0, 0, 0, (date('m')+variable_get('im_admin_n', 0)), date('d'), date('Y'))) . "TO" . date("H:i:s");//2013-11-05T00:00:00
	      $om_node->field_om_publication_period['und'][0]['show_todate'] = 1;
	      $om_node->field_om_publication_period['und'][0]['timezone'] = 'UTC';
	      $om_node->field_om_publication_period['und'][0]['offset'] = 0;
	      $om_node->field_om_publication_period['und'][0]['offset2'] = 0;
	      $om_node->field_om_publication_period['und'][0]['timezone_db'] = 'UTC';
	      $om_node->field_om_publication_period['und'][0]['date_type'] = 'date';
          $om_node->field_om_status['und'][0]['value'] = 'INTEGRE';
          $om_node->field_om_status['und'][1]['value'] = 'FRANCHISE';
          $om_node->field_om_access['und'][0]['value'] = 0;
          $attach_file = array();
	        if (isset($procedure_xml_obj->attachment) && isset($procedure_xml_obj->attachment)) {
	          for ($i=0; $i<count($procedure_xml_obj->attachment); $i++) {
	            $attach_file['filename'] = trim($procedure_xml_obj->attachment[$i]->filename);
	            $attach_file['file_content'] = trim($procedure_xml_obj->attachment[$i]->content);
	            if (!empty($attach_file['filename']) && !empty($attach_file['file_content'])) {
	            	$node_attach_files = _im_import_create_attached_file($attach_file);
	            	$om_node->field_om_attachments['und'][] = (array)$node_attach_files;
	            }
	          }
	        }
	        else if(count($attachment_asset) > 0) {
	          foreach ($attachment_asset as $key=>$attachment_value) {
	            $attach_file['filename'] = trim($attachment_value['attach_filename']);
	            $attach_file['file_content'] = trim($attachment_value['attach_content']);
	            if (!empty($attach_file['filename']) && !empty($attach_file['file_content'])) {
	            	$node_attach_files = _im_import_create_attached_file($attach_file);
	            	$om_node->field_om_attachments['und'][] = (array)$node_attach_files;
	            }
	          }
	        }
	      for ($i=0; $i<count($procedure_xml_obj->object->property); $i++) {
	        if (isset($procedure_xml_obj->object->property[$i]->location)) {
	          for ($j=0; $j<count($procedure_xml_obj->object->property[$i]->location->value);$j++) {
	          	$taxonomy_machine_name = 'operational_model_location';
	            $om_localtion_vocabulary = taxonomy_vocabulary_machine_name_load($taxonomy_machine_name);
	            $om_location_term_tree = taxonomy_get_tree($om_localtion_vocabulary->vid);
	            $value_set = array();
	            $value_set = (array)$procedure_xml_obj->object->property[$i]->location;
	            $value_set = $value_set['value'];
	            if (!is_array($value_set)) {
	            	$value_set = array($value_set);
	            }
	            $om_location_tid = '';
	            foreach ($om_location_term_tree as $key=>$tname) {
	                if (strval($tname->name) === strval($value_set[$j])) {
	                  $om_location_tid = $tname->tid;
	                }
	              }
	            if (empty($om_location_tid)) {
	                $om_location_term = new stdClass();
	                $om_location_term->name = $value_set[$j];
	                $om_location_term->vid = $om_localtion_vocabulary->vid;
	                $om_location_term->field_om_location_code['und'][0]['value'] = str_replace("/", "-", str_replace(" ", "_", $value_set[$j]));
	                if (!empty($value_set[$j])) {
	                  taxonomy_term_save($om_location_term);
	                  $om_location_tid = $om_location_term->tid;
	                }
	                else {
	                  $om_location_tid = '';
	                }
	              }
	            if (!empty($om_location_tid))
	              $om_node->field_om_location['und'][$j]['tid'] = $om_location_tid;
	          }
	        }
	        if (isset($procedure_xml_obj->object->property[$i]->procedureActors)) {
	          for ($k=0; $k<count($procedure_xml_obj->object->property[$i]->procedureActors->value); $k++) {
	            $taxonomy_machine_name = 'om_roles';
			        $om_roles_vocabulary = taxonomy_vocabulary_machine_name_load($taxonomy_machine_name);
				      $om_roles_term_tree = taxonomy_get_tree($om_roles_vocabulary->vid);
	            $value_set = array();
	            $value_set = (array)$procedure_xml_obj->object->property[$i]->procedureActors;
	            $value_set = $value_set['value'];
	            if (!is_array($value_set)) {
	            	$value_set = array($value_set);
	            }
	            $om_role_actuers_tid = '';
	            foreach ($om_roles_term_tree as $key=>$tname) {
	              if (strval($tname->name) === strval($value_set[$k])) {
	                $om_role_actuers_tid = $tname->tid;
	              }
	            }
	            if (empty($om_role_actuers_tid)) {
	              $om_role_term = new stdClass();
	              $om_role_term->name = $value_set[$k];
	              $om_role_term->vid = $om_roles_vocabulary->vid;
	              if (!empty($value_set[$k])) {
	                taxonomy_term_save($om_role_term);
	                $om_role_actuers_tid = $om_role_term->tid;
	              }
	              else {
	                $om_role_actuers_tid = '';
	              }
	            }
	            if (!empty($om_role_actuers_tid))
	              $om_node->field_om_actuers['und'][$k]['tid'] = $om_role_actuers_tid;
	          }
	        }
	         
	        if (isset($procedure_xml_obj->object->property[$i]->procedureMaterial)) {
	        	$tmp_var = '';
	          $tmp_var = (array)$procedure_xml_obj->object->property[$i]->procedureMaterial;
	          $om_node->field_om_material['und'][0]['value'] = implode("", $tmp_var);
	        }
	        if (isset($procedure_xml_obj->object->property[$i]->objectives)) {
	        	$tmp_var = '';
	          $tmp_var = (array)$procedure_xml_obj->object->property[$i]->objectives;
	          $objectives_content = implode("", $tmp_var);
	          $objectives_content = str_replace("}}", ">", str_replace("{{", "<", $objectives_content));
	          $objectives_content_array = array();
	          $objectives_content_array = explode('[[', $objectives_content);
	          foreach ($objectives_content_array as $key=>$bcontent) {
              $tmp_bcontent = explode(']]', $bcontent);
              $tmp_bcontent[0] = html_entity_decode($tmp_bcontent[0]);
              $tmp_bcontent[0] = trim($tmp_bcontent[0]);
	           
              if (!strstr($tmp_bcontent[0], 'attach:') && !strstr($tmp_bcontent[0], 'image:')) {
                $attributes = _im_import_format_link_attributes($tmp_bcontent[0]);
                $tmp = '';
                if (strstr($tmp_bcontent[0], '>>')) {
                  $tmp = substr($tmp_bcontent[0], strpos($tmp_bcontent[0], '>>')+2);
                  $tmp = substr($tmp, 0, strpos($tmp, '||'));
                } 
                if (!empty($tmp)) {
                  $tmp_bcontent[0] = l(substr($tmp_bcontent[0], 0, strpos($tmp_bcontent[0], '>>')), $tmp, array('attributes' => $attributes));
                }
              }
              else if (strstr($tmp_bcontent[0], 'attach:')) {
                $attributes = _im_import_format_link_attributes($tmp_bcontent[0]);
                $tmp = '';
                if (strstr($tmp_bcontent[0], '>>')) {
                  $tmp = substr($tmp_bcontent[0], strpos($tmp_bcontent[0], '>>')+2);
                  $tmp = str_replace("attach:", '', substr($tmp, 0, strpos($tmp, '||')));
                }
                else {
                	$tmp = $tmp_bcontent[0];
                	$tmp = str_replace("attach:", '', substr($tmp, 0, strpos($tmp, '||')));
                  $tmp = str_replace("attach:", '', $tmp);
                }
                $path = _im_import_set_file_path($tmp, $om_node->field_om_attachments['und']);
                $tmp_bcontent[0] = l(substr($tmp_bcontent[0], 0, strpos($tmp_bcontent[0], '>>')), $path, array('attributes' => $attributes));
              }
              else if (strstr($tmp_bcontent[0], 'image:')) {
                $attributes = _im_import_format_link_attributes($tmp_bcontent[0]);
                $tmp = '';
                if (strstr($tmp_bcontent[0], '>>')) {
                  $tmp = substr($tmp_bcontent[0], strpos($tmp_bcontent[0], '>>')+2);
                  $tmp = str_replace("image:", '', substr($tmp, 0, strpos($tmp, '||')));
                }
                else {
                	$tmp = $tmp_bcontent[0];
                	$tmp = str_replace("image:", '', substr($tmp, 0, strpos($tmp, '||')));
                  $tmp = str_replace("image:", '', $tmp);
                }
                $path = _im_import_set_file_path($tmp, $om_node->field_om_attachments['und']);
                $variables = array(
                  'path' => $path,
                  'attributes' => $attributes,
                );
                $img = theme('image', $variables); 
                $tmp_bcontent[0] = $img;
              }
	          
              $objectives_content_array[$key] = implode(' ', $tmp_bcontent);
	          }
	        
	          $objectives_content = implode('', $objectives_content_array);
	          $objectives_content = html_entity_decode($objectives_content);
            $objectives_content = _im_import_change_content_font_format($objectives_content);
	          $om_node->field_om_objective['und'][0]['value'] = $objectives_content;
	          $om_node->field_om_objective['und'][0]['format'] = 'full_html';
	        }
	        if (isset($procedure_xml_obj->object->property[$i]->procedureContent)) {
	        	$tmp_var = '';
	          $tmp_var = (array)$procedure_xml_obj->object->property[$i]->procedureContent;
	          $body_content = implode("", $tmp_var);
	          $body_content = str_replace("}}", ">", str_replace("{{", "<", $body_content));
	          $body_content_array = array();
	          $body_content_array = explode('[[', $body_content);
	          foreach ($body_content_array as $key=>$bcontent) {
              $tmp_bcontent = explode(']]', $bcontent);
              $tmp_bcontent[0] = html_entity_decode($tmp_bcontent[0]);
              $tmp_bcontent[0] = trim($tmp_bcontent[0]);
              if (!strstr($tmp_bcontent[0], 'attach:') && !strstr($tmp_bcontent[0], 'image:')) {
              	$tmp = '';
                $attributes = _im_import_format_link_attributes($tmp_bcontent[0]);
                if (strstr($tmp_bcontent[0], '>>')) {
                  $tmp = substr($tmp_bcontent[0], strpos($tmp_bcontent[0], '>>')+2);
                  $tmp = substr($tmp, 0, strpos($tmp, '||'));
                } 
                if (!empty($tmp)) {
                  $tmp_bcontent[0] = l(substr($tmp_bcontent[0], 0, strpos($tmp_bcontent[0], '>>')), $tmp, array('attributes' => $attributes));
                }
              }
              else if (strstr($tmp_bcontent[0], 'attach:')) {
              	$tmp = '';
                $attributes = _im_import_format_link_attributes($tmp_bcontent[0]);
                if (strstr($tmp_bcontent[0], '>>')) {
                  $tmp = substr($tmp_bcontent[0], strpos($tmp_bcontent[0], '>>')+2);
                  $tmp = str_replace("attach:", '', substr($tmp, 0, strpos($tmp, '||')));
                }
                else {
                	$tmp = $tmp_bcontent[0];
                	$tmp = str_replace("attach:", '', substr($tmp, 0, strpos($tmp, '||')));
                  $tmp = str_replace("attach:", '', $tmp);
                }
                $path = _im_import_set_file_path($tmp, $om_node->field_om_attachments['und']);
                $tmp_bcontent[0] = l(substr($tmp_bcontent[0], 0, strpos($tmp_bcontent[0], '>>')), $path, array('attributes' => $attributes));
              }
              else if (strstr($tmp_bcontent[0], 'image:')) {
              	$tmp = '';
                $attributes = _im_import_format_link_attributes($tmp_bcontent[0]);
                if (strstr($tmp_bcontent[0], '>>')) {
                  $tmp = substr($tmp_bcontent[0], strpos($tmp_bcontent[0], '>>')+2);
                  $tmp = str_replace("image:", '', substr($tmp, 0, strpos($tmp, '||')));
                }
                else {
                	$tmp = $tmp_bcontent[0];
                	$tmp = str_replace("image:", '', substr($tmp, 0, strpos($tmp, '||')));
                  $tmp = str_replace("image:", '', $tmp);
                }
                $path = _im_import_set_file_path($tmp, $om_node->field_om_attachments['und']);
                $variables = array(
                  'path' => $path,
                  'attributes' => $attributes,
                );
                $img = theme('image', $variables); 
                $tmp_bcontent[0] = $img;
              }
              $body_content_array[$key] = implode(' ', $tmp_bcontent);
	          }
	          $body_content = implode('', $body_content_array);
	          $body_content = html_entity_decode($body_content);
            $body_content = _im_import_change_content_font_format($body_content);
	          $om_node->body['und'][0]['value'] = $body_content;
	          $om_node->body['und'][0]['format'] = 'full_html';
	          $om_node->body['und'][0]['summary'] = '';
	        }
	        if (isset($procedure_xml_obj->object->property[$i]->procedureExecutionDuration)) {
	        	$tmp_var = '';
	          $tmp_var = (array)$procedure_xml_obj->object->property[$i]->procedureExecutionDuration;
	          $om_node->field_om_duration['und'][0]['value'] = substr($tmp_var[0], 0, 50);
	        }
	      }
	      $om_node->status = 0;
	      $om_node->field_draft_status['und'][0]['value'] = 1;
	      $om_node->field_node_archive['und'][0]['value'] = 0;
	      unset($_SESSION['field_om_reference_procedure_code']);
	      $_SESSION['field_om_reference_procedure_code'] = $domain_code . '/' . $sub_domain_code . '/';
	      $om_node->uid = $user->uid;
	      node_save($om_node);
      }
      else {
      	// Node title is empty then it will execute
      	watchdog('im_import', 'The procedure (Operational Model node) title is empty on %filename', array('%filename' => $filename), WATCHDOG_NOTICE);
      }
    }
  }
}
function _im_import_change_content_font_format($string) {
  include_once (drupal_get_path("module", "im_import") . "/includes/class.XWIKIParser.php");
  $string = str_replace('"__blank"', '"_blank"', $string);
  $obj = new XWIKIParser();
  $string = $obj->parse($string);
  $string = _im_import_change_table_tag($string);
  $string = _im_import_change_style_tag($string);
  $string = _im_import_add_h2_tag_idvalue($string);
  return $string;
}

function _im_import_add_h2_tag_idvalue($string) {
  $string_flag = explode("<h2", $string);
  if (count($string_flag) > 1) {
    for ($i=1; $i<count($string_flag); $i++) {
      $string_flag[$i] = '<h2 id="h2tag-' . $i . '"' . $string_flag[$i];
    }
  }
  $string = implode("", $string_flag);
  return $string;
}
function _im_import_change_style_tag($string) {
	$string = str_replace('<td>(%', '<td ', $string);
	$string = str_replace('<tr>(%', '<tr ', $string);
  $string = str_replace('<h2>(%', '<h2 ', $string);
  $string = str_replace('<h3>(%', '<h3 ', $string);
  $string = str_replace('<u>(%', '<u ', $string);
  $string = str_replace('<hr>(%', '<hr ', $string);
  $string = str_replace('<strike>(%', '<strike ', $string);
  $string = str_replace('<sup>(%', '<sup ', $string);
  $string = str_replace('<sub>(%', '<sub ', $string);
  $string = str_replace('<strin>(%', '<string ', $string);
  $string = str_replace('<ol>(%', '<ol ', $string);
  $string = str_replace('<li>(%', '<li ', $string);
  $string = str_replace('<ul>(%', '<ul ', $string);
  
  $string = str_replace('<td> (%', '<td ', $string);
  $string = str_replace('<tr> (%', '<tr ', $string);
  $string = str_replace('<h2> (%', '<h2 ', $string);
  $string = str_replace('<h3> (%', '<h3 ', $string);
  $string = str_replace('<u> (%', '<u ', $string);
  $string = str_replace('<hr> (%', '<hr ', $string);
  $string = str_replace('<strike> (%', '<strike ', $string);
  $string = str_replace('<sup> (%', '<sup ', $string);
  $string = str_replace('<sub> (%', '<sub ', $string);
  $string = str_replace('<strin> (%', '<string ', $string);
  $string = str_replace('<ol> (%', '<ol ', $string);
  $string = str_replace('<li> (%', '<li ', $string);
  $string = str_replace('<ul> (%', '<ul ', $string);
  
  $string = str_replace('(%%)', '', $string);
  $string = str_replace('%)', '>', $string);
  
  $string = str_replace('(% style', '<p style', $string);
  $string = str_replace('<p>(%', '<p ', $string);
  $string = str_replace('<p> (%', '<p ', $string);
  $string = str_replace('(%%)', '</p>', $string);
  $string = str_replace('%)', '>', $string);

  $string = str_replace('http:</em><em>', 'http://', $string);
  $string = str_replace('http:<em></em>', 'http://', $string);
  $string = str_replace('http:<em><em>', 'http://', $string);
  $string = str_replace('http:</em></em>', 'http://', $string);
  $string = str_replace('http:<em>', 'http://', $string);
  $string = str_replace('http:</em>', 'http://', $string);
  
  $string = str_replace('https:</em><em>', 'https://', $string);
  $string = str_replace('https:<em></em>', 'https://', $string);
  $string = str_replace('https:<em><em>', 'https://', $string);
  $string = str_replace('https:</em></em>', 'https://', $string);
  $string = str_replace('https:<em>', 'https://', $string);
  $string = str_replace('https:</em>', 'https://', $string);
  $string = str_replace('<li></li>', '', $string);
  
  $string = str_replace('<h2', '<h1', $string);
  $string = str_replace('</h2', '</h1', $string);
  return $string;
}

function _im_import_change_h3_tag($string) {
  $string_flag = explode("===", $string);
  if (count($string_flag) > 1) {
    for ($i=1; $i<count($string_flag)-1; $i++) {
      $string_flag[$i] = trim($string_flag[$i]);
      if (substr($string_flag[$i], 0, 2) == '(%') {
        $string_flag[$i] = '<h3 ' . substr($string_flag[$i], 2, strlen($string_flag[$i])) . '</h3>';
        $string_flag[$i] = str_replace('(%%)', '', $string_flag[$i]);
        $string_flag[$i] = str_replace('%)', '>', $string_flag[$i]);
      }
      else {
        $string_flag[$i] = '<h3>' . $string_flag[$i] . '</h3>';
      }
    }
    $string = implode("", $string_flag);
  }
  return $string;
}

function _im_import_change_h2_tag($string) {
  $string_flag = explode("==", $string);
  if (count($string_flag) > 1) {
    for ($i=1; $i<count($string_flag)-1; $i++) {
      $string_flag[$i] = trim($string_flag[$i]);
      if (substr($string_flag[$i], 0, 2) == '(%') {
        $string_flag[$i] = '<h2 ' . substr($string_flag[$i], 2, strlen($string_flag[$i])) . '</h2>';
        $string_flag[$i] = str_replace('(%%)', '', $string_flag[$i]);
        $string_flag[$i] = str_replace('%)', '>', $string_flag[$i]);
      }
      else {
        $string_flag[$i] = '<h2>' . $string_flag[$i] . '</h2>';
      }
      $string_flag[$i] = str_replace('<h2', '<h2 id="h2tag-' . $i . '"', $string_flag[$i]);
    }
    $string = implode("", $string_flag);
  }
  return $string;
}

function _im_import_change_italic_tag($string) {
  $string_flag = explode('//', $string);
  if (count($string_flag) > 1) {
    for ($i=1; $i<count($string_flag)-1; $i++) {
      $string_flag[$i] = trim($string_flag[$i]);
      if (substr($string_flag[$i], 0, 2) == '(%') {
        $string_flag[$i] = '<i ' . substr($string_flag[$i], 2, strlen($string_flag[$i])) . '</i>';
        $string_flag[$i] = str_replace('(%%)', '', $string_flag[$i]);
        $string_flag[$i] = str_replace('%)', '>', $string_flag[$i]);
      }
      else {
        $string_flag[$i] = '<i>' . $string_flag[$i] . '</i>';
      }
    }
    $string = implode("", $string_flag);
  }
  return $string;
}

function _im_import_change_bold_tag($string) {
  $string_flag = explode('**', $string);
  if (count($string_flag) > 1) {
    for ($i=1; $i<count($string_flag)-1; $i++) {
      $string_flag[$i] = trim($string_flag[$i]);
      if (substr($string_flag[$i], 0, 2) == '(%') {
        $string_flag[$i] = '<b ' . substr($string_flag[$i], 2, strlen($string_flag[$i])) . '</b>';
        $string_flag[$i] = str_replace('(%%)', '', $string_flag[$i]);
        $string_flag[$i] = str_replace('%)', '>', $string_flag[$i]);
      }
      else {
        $string_flag[$i] = '<b>' . $string_flag[$i] . '</b>';
      }
    }
    $string = implode("", $string_flag);
  }
  return $string;
}

function _im_import_change_strike_tag($string) {
  $string_flag = explode('--', $string);
  if (count($string_flag) > 1) {
    for ($i=1; $i<count($string_flag)-1; $i++) {
      $string_flag[$i] = trim($string_flag[$i]);
      if (substr($string_flag[$i], 0, 2) == '(%') {
        $string_flag[$i] = '<strike ' . substr($string_flag[$i], 2, strlen($string_flag[$i])) . '</strike>';
        $string_flag[$i] = str_replace('(%%)', '', $string_flag[$i]);
        $string_flag[$i] = str_replace('%)', '>', $string_flag[$i]);
      }
      else {
        $string_flag[$i] = '<strike>' . $string_flag[$i] . '</strike>';
      }
    }
    $string = implode("", $string_flag);
  }
  return $string;
}

function _im_import_change_underline_tag($string) {
  $string_flag = explode('__', $string);
  if (count($string_flag) > 1) {
    for ($i=1; $i<count($string_flag)-1; $i++) {
      $string_flag[$i] = trim($string_flag[$i]);
      if (substr($string_flag[$i], 0, 2) == '(%') {
        $string_flag[$i] = '<u ' . substr($string_flag[$i], 2, strlen($string_flag[$i])) . '</u>';
        $string_flag[$i] = str_replace('(%%)', '', $string_flag[$i]);
        $string_flag[$i] = str_replace('%)', '>', $string_flag[$i]);
      }
      else {
        $string_flag[$i] = '<u>' . $string_flag[$i] . '</u>';
      }
    }
    $string = implode("", $string_flag);
  }
  return $string;
}

function _im_import_change_superscript_tag($string) {
  $string_flag = explode('^^', $string);
  if (count($string_flag) > 1) {
    for ($i=1; $i<count($string_flag)-1; $i++) {
      $string_flag[$i] = trim($string_flag[$i]);
      if (substr($string_flag[$i], 0, 2) == '(%') {
        $string_flag[$i] = '<sup ' . substr($string_flag[$i], 2, strlen($string_flag[$i])) . '</sup>';
        $string_flag[$i] = str_replace('(%%)', '', $string_flag[$i]);
        $string_flag[$i] = str_replace('%)', '>', $string_flag[$i]);
      }
      else {
        $string_flag[$i] = '<sup>' . $string_flag[$i] . '</sup>';
      }
    }
    $string = implode("", $string_flag);
  }
  return $string;
}

function _im_import_change_horizontalline_tag($string) {
  $string_flag = explode('----', $string);
  if (count($string_flag) > 1) {
    for ($i=1; $i<count($string_flag)-1; $i++) {
      $string_flag[$i] = trim($string_flag[$i]);
      if (substr($string_flag[$i], 0, 2) == '(%') {
        $string_flag[$i] = '<hr ' . substr($string_flag[$i], 2, strlen($string_flag[$i]));
        $string_flag[$i] = str_replace('(%%)', '', $string_flag[$i]);
        $string_flag[$i] = str_replace('%)', '>', $string_flag[$i]);
      }
      else {
        $string_flag[$i] = '<hr>' . $string_flag[$i];
      }
    }
    $string = implode("", $string_flag);
  }
  return $string;
  return $string;
}

function _im_import_change_subscript_tag($string) {
  $string_flag = explode(',,', $string);
  if (count($string_flag) > 1) {
    for ($i=1; $i<count($string_flag)-1; $i++) {
      $string_flag[$i] = trim($string_flag[$i]);
      if (substr($string_flag[$i], 0, 2) == '(%') {
        $string_flag[$i] = '<sub ' . substr($string_flag[$i], 2, strlen($string_flag[$i])) . '</sub>';
        $string_flag[$i] = str_replace('(%%)', '', $string_flag[$i]);
        $string_flag[$i] = str_replace('%)', '>', $string_flag[$i]);
      }
      else {
        $string_flag[$i] = '<sub>' . $string_flag[$i] . '</sub>';
      }
    }
    $string = implode("", $string_flag);
  }
  return $string;
}

function _im_import_change_unorderedlist_tag($string) {
  $string_flag = explode('*', $string);
  if (count($string_flag) > 1) {
    for ($i=1; $i<count($string_flag)-1; $i++) {
      $string_flag[$i] = trim($string_flag[$i]);
      if (!empty($string_flag[$i])) {
	      if (substr($string_flag[$i], 0, 2) == '(%') {
	        $string_flag[$i] = '<li ' . substr($string_flag[$i], 2, strlen($string_flag[$i]));
	        $string_flag[$i] = str_replace('(%%)', '', $string_flag[$i]);
	        $string_flag[$i] = str_replace('%)', '>', $string_flag[$i]);
	      }
	      else {
	        $string_flag[$i] = '<li>' . $string_flag[$i];
	      }
	      $string_flag[$i] = $string_flag[$i] . "</li>";
	      if ($i == 0 ) {
          $string_flag[$i] = '<ul>' . $string_flag[$i];
	      }
      }
    }
    $string_flag[count($string_flag)-1] = '</ul>' . $string_flag[count($string_flag)-1];
    $string = implode("", $string_flag);
  }
  $string = str_replace('<li></li>', '', $string);
  $string_li_flag = explode('</li>', $string);
  for ($j=0; $j<count($string_li_flag); $j++) {
    if (strstr($string_li_flag[$j], '- ')) {
      $string_li_flag[$j] = str_replace('- ', '<li>', $string_li_flag[$j]) . '</li>';
    }
  }
  $string = implode('</li>', $string_li_flag);
  return $string;
}

function _im_import_change_table_tag($string) {
  $table_flag_symbol = substr($string, strlen($string)-1, strlen($string));
  $string_flag = explode('|', $string);
  $table_head_counter = 0;
  $table_row_counter = 0;
  $table_row_first_enter_flag = 1;
  if (count($string_flag) > 1) {
    if ($table_flag_symbol == '|') {
      $total_loop = count($string_flag);
    }
    else {
      $total_loop = count($string_flag)-1;
    }
    for ($i=1; $i<$total_loop; $i++) {
      $string_flag[$i] = trim($string_flag[$i]);
      if (substr($string_flag[$i], 0, 1) == '=') {
        if (substr($string_flag[$i], 1, 2) == '(%') {
          $string_flag[$i] = '<th ' . substr($string_flag[$i], 3, strlen($string_flag[$i])) . '</th>';
          $string_flag[$i] = str_replace('(%%)', '', $string_flag[$i]);
          $string_flag[$i] = str_replace('%)', '>', $string_flag[$i]);
        }
        else {
          $string_flag[$i] = '<th>' . substr($string_flag[$i], 1, strlen($string_flag[$i])) . '</th>';
        }
        if ($i == 1) {
           $string_flag[$i] = '<table><thead><tr>' . $string_flag[$i];
        }
        $table_head_counter++;
      }
      else {
        if ($table_row_counter == $table_head_counter) {
          $table_row_counter = 0;
        }
        if (substr($string_flag[$i], 0, 2) == '(%') {
          $string_flag[$i] = '<td ' . substr($string_flag[$i], 2, strlen($string_flag[$i])) . '</td>';
          $string_flag[$i] = str_replace('(%%)', '', $string_flag[$i]);
          $string_flag[$i] = str_replace('%)', '>', $string_flag[$i]);
        }
        else {
          $string_flag[$i] = '<td>' . $string_flag[$i] . '</td>';
        }
        if ($table_row_counter == 0 && $table_row_first_enter_flag == 0) {
          $string_flag[$i] = '</tr><tr>' . $string_flag[$i];
        }
        else if ($table_row_counter == 0 && $table_row_first_enter_flag == 1) {
        	$string_flag[$i] = '</tr></thead><tr>' . $string_flag[$i];
        }
        $table_row_first_enter_flag = 0;
        $table_row_counter++;
      }
    }
    $table_end = explode("\n", $string_flag[$total_loop]);
    $table_end_content = '';
    foreach ($table_end as $key=>$tevalue) {
      if (!empty($tevalue)) {
        $table_end_content .= $tevalue . "\n";
        unset($table_end[$key]);
      }
      else {
        break;
      }
    }
    $string_flag[$total_loop] = '<td>' . $table_end_content . '</td></tr></table>';
    unset($table_end[0]);
    $string_flag[$total_loop] = $string_flag[$total_loop] . implode("\n", $table_end);
    $string = implode("", $string_flag);
  }
  return $string;
}

/**
 * Used to save the file in file_managed and return the file object.
 * @param $attach_file array
 */
function _im_import_create_attached_file($attach_file) {
  ini_set('memory_limit','-1');
  $public_folder_path = drupal_realpath(variable_get('domain_xml_dest_file_path', 'sites/default/files/public/operational_model'));
  $fname = microtime(TRUE) . $attach_file['filename'];
  $content = base64_decode($attach_file['file_content']);
  $public_folder_path . '/' . $fname;
  $public_folder_path . '/' . $fname;
  $fp = fopen($public_folder_path . '/' . $fname, 'w');
  fwrite($fp, $content);
  fclose($fp);
  $filepath = drupal_realpath($dest_file_name);
  $uri = 'public://operational_model/' . $fname;
	$file = new stdClass;
	$file->filename = $attach_file['filename'];
	$file->uri = $uri; 
	$file->filesize = filesize($filepath);
	$file->status = 1;
	$file->display = 1;
    $file->description = "";
	$file = file_save($file); 
  unlink($source_file_name);
  return $file;
}

/**
 * Create Domain taxonomy
 * @param $terms array
 * @param $vocabulary object
 */
function _im_import_create_domain_term($terms, $vocabulary) {
  $term = new stdClass();
  $term->name = $terms['name'];
  $term->field_taxo_om_code['und'][0]['value'] = $terms['code'];
  $term->vid = $vocabulary->vid;
  taxonomy_term_save($term);
  return $term->tid;
}

/**
 * Create Subdomain taxonomy
 * @param $terms array
 * @param $vocabulary object
 */
function _im_import_create_sub_domain_term($terms, $vocabulary) {
  $term = new stdClass();
  $term->name = $terms['name'];
  $term->field_taxo_om_code['und'][0]['value'] = $terms['code'];
  $term->vid = $vocabulary->vid;
  $term->parent = array($terms['parent_id']);
  taxonomy_term_save($term);
  return $term->tid;
}

/**
 * Create Macro taxonomy
 * @param $terms array
 * @param $vocabulary object
 */
function _im_import_create_macro_term($terms, $vocabulary) {
  $term = new stdClass();
  $term->name = $terms['name'];
  $term->vid = $vocabulary->vid;
  $term->parent = array($terms['parent_id']);
  taxonomy_term_save($term);
  return $term->tid;
}

/**
 * Batch process completions status function
 * @param $success boolean
 * @param $results array
 * @param $operations array
 */
function _im_import_xml_batch_process_finished($success, $results, $operations) {
   if ($success) {
    // Here we could do something meaningful with the results.
    // We just display the number of nodes we processed...
    drupal_set_message(t('@count results processed in @requests HTTP requests.', array('@count' => count($results), '@requests' => _im_import_get_http_requests())));
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
function _im_import_update_http_requests() {
  $_SESSION['http_request_count']++;
}

/**
* Initialize the HTTP requests in a session variable.
*/
function _im_import_get_http_requests() {
  return !empty($_SESSION['http_request_count']) ? $_SESSION['http_request_count'] : 0;
}