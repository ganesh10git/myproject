<?php
function _im_import_saint_day_import_page(){
	return drupal_get_form('im_import_saint_data_form');
}

function im_import_saint_data_form($form, &$form_state){
  $form['#attributes'] = array('enctype' => "multipart/form-data");
  $form['saint_of_day'] = array(
    '#type' => 'file',
    '#title' => t('Saint of The day'),
    '#description' => t('Pick a csv file to upload')
  );
  $form['submit'] = array(
    '#type' => 'submit', 
    '#value' => t('Upload'),
    '#suffix' => get_saintoftheday_data(),
  );
  return $form;
}


function im_import_saint_data_form_submit($form, &$form_state){
  $saint_array = array();
  $file = file_save_upload('saint_of_day', array('file_validate_extensions' => array('csv'),FILE_EXISTS_REPLACE));
  if ($file) {
    if ($file = file_move($file, 'public://')) {
      if($handle = fopen(drupal_realpath($file->uri), 'r')){
        while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
		  $saint_array[] = array('saint_date' => trim($data[0]) . '-' . trim($data[1]), 
		                         'saint_of_the_day' => trim($data[2])
		                        );
		}
		try {
		  $truncate = db_truncate('saint_day_data')->execute();
	      $query = db_insert('saint_day_data')->fields(array('saint_date', 'saint_of_the_day'));
		  foreach ($saint_array as $saint) {
		    $query->values($saint);
		  }
		  $query->execute();
		  drupal_set_message("data has been inserted");
		}catch (Exception $e){
		  drupal_set_message($e->getMessage(),'error');
		}
	  }
    }
  }
}

function get_saintoftheday_data(){
  $table_rows = array();
  $saints = db_select("saint_day_data", "s")
  ->fields("s")
  ->execute();
  
  $table_header = array(t('Date'), 
                        t('Saint of the day'),
                       ); 
  
  foreach($saints as $saint){
  	$table_rows[] = array(
  	    array('data' => $saint->saint_date, 'class' => array('saint-date')),
	    array('data' => $saint->saint_of_the_day, 'class' => array('saint-title'))
    );
  }
  $output = theme_table(array(
        'header' =>  $table_header, 
        'rows' => $table_rows,
        'attributes' => array('class' => 'table_saint', 'width' => '100%'),
        'caption' => '',
        'colgroups' => array(),
        'sticky' => FALSE,
        'empty' => 'No data is available',
    ));
  return $output;
}