<?php 
/**
 * @file
 * Module file for store_data_import.
 */
function _im_import_store_import_page() {
  return drupal_get_form('im_import_store_data_form');
}

/**
 * Display the form to upload the CSV file
 */
function im_import_store_data_form($form, &$form_state){
  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  );
  $form['fieldset']['source_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Source path'),
    '#required' => TRUE,
    '#default_value' => variable_get("im_import_store_data_import_path", "private://import_store_data"),
  );
  $form['fieldset']['dist_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Destination path'),
    '#required' => TRUE,
    '#default_value' => variable_get("im_import_store_data_imported_path", "private://imported_store_data"),
  );
  $form['fieldset']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('_im_import_domain_asset_form_store_data_variable_submit'),
  );
  return $form;
}

/**
 * Implements of hook_form_submit().
 * hook_form_submit - Import OM notes and Domain, subdomain, macro path settings form and Start batch process button form
 * @param $form array
 * @param $form_state array
 */
function _im_import_domain_asset_form_store_data_variable_submit($form, &$form_state) {
  if (variable_get("im_import_domain_xml_source_path", "private://import_store_data") != $form_state['values']['source_path']) {
   _im_import_file_system_create_directory_system('im_import', 'store_data_import_path', $form_state['values']['source_path']);
  }
  if (variable_get("im_import_domain_xml_dest_path", "private://imported_store_data") != $form_state['values']['dist_path']) {
   _im_import_file_system_create_directory_system('im_import', 'store_data_imported_path', $form_state['values']['dist_path']);
  }
  drupal_set_message(t("Successfully updated"));
}

/**
 * Implements of hook_cron
 */
function im_import_cron() {
  im_import_store_data_cron_process(); 
}

/**
 * hoom_form_validate
 * Used to validate the store data import form
 * @param $form array
 * @param $form_state array
 */
function im_import_store_data_cron_process(){
  _im_import_stores_table_backup();
  _im_import_store_data_desc_cron_process();
  _im_import_store_data_cron_process();
} 

/**
 * _im_import_stores_table_backup();
 */
function _im_import_stores_table_backup() {
  /*db_query("COPY (SELECT * FROM store) TO ':path'", array(':path' => drupal_realpath(variable_get("im_import_store_data_backup_path", "private://store_import/backup")) . '/' . date("Ymd") . "_store.sql"));
  db_query("COPY (SELECT * FROM store_item_fields) TO ':path'", array(':path' => drupal_realpath(variable_get("im_import_store_data_backup_path", "private://store_import/backup")) . '/' . date("Ymd") . "_store_item_fields.sql"));
  db_query("COPY (SELECT * FROM store_item_fields_desc) TO ':path'", array(':path' => drupal_realpath(variable_get("im_import_store_data_backup_path", "private://store_import/backup")) . '/' . date("Ymd") . "_store_item_fields_desc.sql"));*/
  $mappingfilename = drupal_realpath(variable_get("im_import_store_data_import_path", "private://store_import/input")) . '/basemagasins_' . date("Ymd") . "_mapping.csv";
  if (file_exists($mappingfilename)) {
    db_query("TRUNCATE TABLE {store_item_fields_desc}");
  }
  $datafilename = drupal_realpath(variable_get("im_import_store_data_import_path", "private://store_import/input")) . '/basemagasins_' . date("Ymd") . "_data.csv";
  if (file_exists($datafilename)) {
    db_query("TRUNCATE TABLE {store}");
    db_query("TRUNCATE TABLE {store_item_fields}");
  }
}

/**
 * Cron Batch Process operation setup : Import Store data Description
 */
function _im_import_store_data_desc_cron_process() {
  ini_set('memory_limit','-1');
  $filename = drupal_realpath(variable_get("im_import_store_data_import_path", "private://store_import/input")) . '/basemagasins_' . date("Ymd") . "_mapping.csv";
  $logfilename = drupal_realpath(variable_get("im_import_store_data_logs_path", "private://store_import/logs")) . '/basemagasins_' . date("Ymd") . ".log";
  if (file_exists($filename)) {
    $fp = fopen($logfilename, 'w');
    $data = file($filename);
    $total_rows = count($data)-1;
    $num_operations = ceil($total_rows / 100);
    $content = "Mapping File Process\n";
    $content .= "---------------------\n";
    $content .= "File name : " . $filename . "\n";
    $content .= "Number of record read : " . count($data) . "\n";
    $content .= "Start time : " . date("Y-m-d H:i:s") . "\n";
    $_SESSION['mapping_error_log_hit'] = '';
    for ($i=0; $i<$num_operations; $i++) {
      _im_import_store_data_desc_import_operation_cron($data, $i, $total_rows);
    }
    $content .= "End time : " . date("Y-m-d H:i:s") . "\n";
    if (!empty($_SESSION['mapping_error_log_hit'])) {
      $content .= "\n\nMapping file Error Log list\n";
      $content .= "---------------------------\n";
      $content .= $_SESSION['mapping_error_log_hit'];
      $src = $filename;
      $dst = drupal_realpath(variable_get("im_import_store_data_rejected_path", "private://store_import/reject")) . '/basemagasins_' . date("Ymd") . "_mapping.csv";
      copy($src, $dst);
      exec('chmod 664 ' . $dst);
      file_unmanaged_delete($src);
    }
    else {
      $src = $filename;
      $dst = drupal_realpath(variable_get("im_import_store_data_imported_path", "private://store_import/archive")) . '/basemagasins_' . date("Ymd") . "_mapping.csv";
      copy($src, $dst); 
      exec('chmod 664 ' . $dst);
      file_unmanaged_delete($src);
    }
    fwrite($fp, $content);
    fclose($fp);
  }
}
/**
 * Cron Batch Process operation setup : Import Store data
 */
function _im_import_store_data_cron_process() {
  ini_set('memory_limit','-1');
  $filename = drupal_realpath(variable_get("im_import_store_data_import_path", "private://store_import/input")) . '/basemagasins_' . date("Ymd") . "_data.csv";
  $logfilename = drupal_realpath(variable_get("im_import_store_data_logs_path", "private://store_import/logs")) . '/basemagasins_' . date("Ymd") . ".log";
  if (file_exists($filename)) {
    $_SESSION['store_data_item_fields_count'] = 0;
    $fp = fopen($logfilename, 'a');
    $data = file($filename);
    $total_rows = count($data)-1;
    $num_operations = ceil($total_rows / 100);
    $content = "\n\n\n\nData File Process\n";
    $content .= "----------------\n";
    $content .= "File name : " . $filename . "\n";
    $content .= "Number of Store data record read : " . $total_rows . "\n";
    $content_time = "Start time : " . date("Y-m-d H:i:s") . "\n";
    $_SESSION['data_error_log_hit'] = '';
    $item_code = str_getcsv($data[0], "|");
    for ($i=0; $i<$num_operations; $i++) {
      _im_import_store_data_item_import_operation_cron($data, $i, $total_rows, $item_code);
    }
    $content .= "Number of Store data item record read : " . intval($_SESSION['store_data_item_fields_count']) . "\n";
    $content .= $content_time;
    $content .= "End time : " . date("Y-m-d H:i:s") . "\n";
    if (!empty($_SESSION['data_error_log_hit'])) {
      $content .= "\n\nData file Error Log list\n";
      $content .= "------------------------\n";
      $content .= $_SESSION['data_error_log_hit'];
      $src = $filename;
      $dst = drupal_realpath(variable_get("im_import_store_data_rejected_path", "private://store_import/reject")) . '/basemagasins_' . date("Ymd") . "_data.csv";
      copy($src, $dst);
      exec('chmod 664 ' . $dst);
      file_unmanaged_delete($src);
    }
    else {
      $src = $filename;
      $dst = drupal_realpath(variable_get("im_import_store_data_imported_path", "private://store_import/archive")) . '/basemagasins_' . date("Ymd") . "_data.csv";
      copy($src, $dst);
      exec('chmod 664 ' . $dst);
      file_unmanaged_delete($src);
    }
    fwrite($fp, $content);
    fclose($fp);
  }
}

/** 
 * To Import the Store data and its Items
 * @param $line
 * @param $context
 */
function _im_import_store_data_item_import_operation_cron($data, $operation_details, $total_rows, $item_code){
  ini_set('memory_limit','-1');
  set_time_limit(0);
  if ($operation_details == 0) {
    $init = 1;
  }
  else {
    $init = ($operation_details * 100) + 1;
  }
  $expression = ($operation_details + 1) * 100;
  if ($expression > $total_rows) {
    $expression = $total_rows;
  }
  for($i=$init; $i<=$expression; $i++) {
    $record_set = array();
    $record = array();
    $record_set = str_getcsv($data[$i], "|");
    // Insert store table data (Store's data)
    if (isset($record_set[0]) && isset($record_set[1])) {
      db_insert('store')
        ->fields(array('pve_code' => utf8_encode($record_set[0]), 'pve_lib' => utf8_encode($record_set[1])))
        ->execute();
    }
    else {
      if (!isset($record_set[0])) {
        $_SESSION['data_error_log_hit'] = "Error : Store code 'pve_code' column is empty\n";
      } 
      else if (!isset($record_set[1])) {
        $_SESSION['data_error_log_hit'] = "Error : '" . $record_set[0] . "' Store's 'pve_lib' column is empty\n";
      }
    }
    // Insert store_item_fields table data (Store's item data)
	$query=db_insert('store_item_fields')->fields(array('pve_code','dit_cod_item' ,'ite_lib_value'));
    for($s=1; $s<count($item_code); $s++) {
      $_SESSION['store_data_item_fields_count']++;
      if (isset($record_set[0]) && isset($item_code[$s]) && isset($record_set[$s])) {
             $query->values(array('pve_code' => utf8_encode($record_set[0]),'dit_cod_item' => utf8_encode($item_code[$s]),'ite_lib_value' => utf8_encode($record_set[$s])));
      }
      else {
        if (!isset($record_set[0])) {
          $_SESSION['data_error_log_hit'] = "Error : Store code 'pve_code' column is empty\n";
        } 
        else if (!isset($item_code[$s])) {
          $_SESSION['data_error_log_hit'] = "Error : '" . $record_set[0] . "' Store's 'dit_cod_item' column is empty\n";
        }
        else if (!isset($record_set[$s])) {
          $_SESSION['data_error_log_hit'] = "Error : '" . $record_set[0] . "' Store's 'ite_lib_value' column is empty\n";
        }
      }
    }
	$query->execute();
  }
}


/** 
 * To Import the Store data and its Items
 * @param $line
 * @param $context
 */
function _im_import_store_data_desc_import_operation_cron($data, $operation_details, $total_rows){
  ini_set('memory_limit','-1');
  set_time_limit(0);
  if ($operation_details == 0) {
    $init = 0;
  }
  else {
    $init = ($operation_details * 100) + 1;
  }
  $expression = ($operation_details + 1) * 100;
  if ($expression > $total_rows) {
    $expression = $total_rows;
  }
  for($i=$init; $i<=$expression; $i++) {
    $record = array();
    $record = str_getcsv($data[$i], "|");
    if (isset($record[2]) && isset($record[3]) && isset($record[1]) && isset($record[0]) && isset($record[5])) {
	    $result = db_insert('store_item_fields_desc')
	    ->fields(array('dit_cod_item' => utf8_encode($record[2]),'dit_lib' => utf8_encode($record[3]),'dsd_lib' => utf8_encode($record[1]),'ddo_lib' => utf8_encode($record[0]),'dit_idt_type' => utf8_encode($record[5])))
	    ->execute();
    }
    else {
      if (!isset($record[2])) {
        $_SESSION['mapping_error_log_hit'] = "Error : 'dit_cod_item' column is empty\n";
      } 
      else if (!isset($record[3])) {
        $_SESSION['mapping_error_log_hit'] = "Error : 'dit_lib' column is empty\n";
      }
      else if (!isset($record[1])) {
        $_SESSION['mapping_error_log_hit'] = "Error : 'dsd_lib' column is empty\n";
      }
      else if (!isset($record[0])) {
        $_SESSION['mapping_error_log_hit'] = "Error : 'ddo_lib' column is empty\n";
      }
      else if (!isset($record[5])) {
        $_SESSION['mapping_error_log_hit'] = "Error : 'dit_idt_type' column is empty\n";
      }
    }
  }
}