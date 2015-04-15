<?php
/**
 * Theme the header of the submissions table.
 *
 * This is done in it's own function so that webform can retrieve the header and
 * use it for sorting the results.
 */
function theme_questionnaire_webform_results_submissions_header($variables) {
  $node = $variables['node'];

  $columns = array(
    array('data' => t('#'), 'field' => 'sid', 'sort' => 'desc'),
    array('data' => t('Submitted'), 'field' => 'submitted'),
  );
  if (webform_results_access($node)) {
    $columns[] = array('data' => t('User'), 'field' => 'name');
    $columns[] = array('data' => t('Profile'), 'field' => 'profile');
    $columns[] = array('data' => t('Store'), 'field' => 'store');
  }
  $columns[] = array('data' => t('Operations'), 'colspan' => module_exists('print') ? 5 : 3);

  return $columns;
}

function questionnaire_webform_results_submissions($node, $user_filter, $pager_count) {
	module_load_include('inc', 'webform', 'includes/webform.submissions');
  global $user;
  if (isset($_GET['results']) && is_numeric($_GET['results'])) {
    $pager_count = $_GET['results'];
  }

  $header = theme('questionnaire_webform_results_submissions_header', array('node' => $node));
  if ($user_filter) {
    if ($user->uid) {
      drupal_set_title(t('Submissions for %user', array('%user' => $user->name)), PASS_THROUGH);
    }
    else {
      drupal_set_title(t('Your submissions'));
      webform_disable_page_cache();
    }
    webform_set_breadcrumb($node);
    $submissions = questionnaire_webform_get_submissions(array('nid' => $node->nid, 'uid' => $user->uid), $header, $pager_count);
    $count = webform_get_submission_count($node->nid, $user->uid);
  }
  else {
    $submissions = questionnaire_webform_get_submissions($node->nid, $header, $pager_count);
    $count = webform_get_submission_count($node->nid);
  }
  $operation_column = end($header);
  $operation_total = $operation_column['colspan'];

  $rows = array();
  foreach ($submissions as $sid => $submission) {
    $row = array(
      $submission->is_draft ? t('@sid (draft)', array('@sid' => $sid)) : $sid,
      format_date($submission->submitted, 'short'),
    );
    if (webform_results_access($node, $user)) {
      $row[] = theme('username', array('account' => $submission));
      $row[] = $submission->profile;
      $row[] = $submission->store;
    }
    $row[] = l(t('View'), "node/$node->nid/submission/$sid");
    $operation_count = 1;
    // No need to call this multiple times, just reference this in a variable.
    $destination = drupal_get_destination();
    if (webform_submission_access($node, $submission, 'edit', $user)) {
      $row[] = l(t('Edit'), "node/$node->nid/submission/$sid/edit", array('query' => $destination));
      $operation_count++;
    }
    if (webform_submission_access($node, $submission, 'delete', $user)) {
      $row[] = l(t('Delete'), "node/$node->nid/submission/$sid/delete", array('query' => $destination));
      $operation_count++;
    }
    if ($operation_count < $operation_total) {
      $row[count($row) - 1] = array('data' => $row[count($row) - 1], 'colspan' => $operation_total - $operation_count + 1);
    }
    $rows[] = $row;
  }

  $element['#theme'] = 'webform_results_submissions';
  $element['#node'] = $node;
  $element['#submissions'] = $submissions;
  $element['#total_count'] = $count;
  $element['#pager_count'] = $pager_count;
  $element['#attached']['library'][] = array('webform', 'admin');

  $element['table']['#theme'] = 'table';
  $element['table']['#header'] = $header;
  $element['table']['#rows'] = $rows;
  $element['table']['#operation_total'] = $operation_total;

  return drupal_render($element);

}

/**
 * Return all the submissions for a particular node.
 *
 * @param $filters
 *   An array of filters to apply to this query. Usually in the format
 *   array('nid' => $nid, 'uid' => $uid). A single integer may also be passed
 *   in, which will be equivalent to specifying a $nid filter.
 * @param $header
 *   If the results of this fetch will be used in a sortable
 *   table, pass the array header of the table.
 * @param $pager_count
 *   Optional. The number of submissions to include in the results.
 */
function questionnaire_webform_get_submissions($filters = array(), $header = NULL, $pager_count = 0) {
  $submissions = array();

  if (!is_array($filters)) {
    $filters = array('nid' => $filters);
  }

  // UID filters need to be against a specific table.
  if (isset($filters['uid'])) {
    $filters['u.uid'] = $filters['uid'];
    unset($filters['uid']);
  }

  // No need to find SIDs if it was given to us.
  if (isset($filters['sid'])) {
    $sids = array($filters['sid']);
  }
  // Build the list of SIDs that need to be retrieved.
  else {
    $pager_query = db_select('webform_submissions', 'ws')->fields('ws', array('sid'));
    foreach ($filters as $column => $value) {
      $pager_query->condition($column, $value);
    }

    if (isset($filters['u.uid']) || !empty($header)) {
      // Join to the users table for sorting by user name.
      $pager_query->leftJoin('users', 'u', 'u.uid = ws.uid');
    }

    if (isset($filters['u.uid']) && $filters['u.uid'] === 0) {
      if (!empty($_SESSION['webform_submission'])) {
        $anonymous_sids = array_keys($_SESSION['webform_submission']);
        $pager_query->condition('sid', $anonymous_sids, 'IN');
      }
      else {
        $pager_query->condition('sid', 0);
      }
    }

    if (is_array($header)) {
      // Extending the query instatiates a new query object.
      $pager_query = $pager_query->extend('TableSort');
      $pager_query->orderByHeader($header);
    }
    else {
      $pager_query->orderBy('sid', 'ASC');
    }

    if ($pager_count) {
      // Extending the query instatiates a new query object.
      $pager_query = $pager_query->extend('PagerDefault');
      $pager_query->limit($pager_count);
    }
    $result = $pager_query->execute();

    $sids = array();
    foreach ($result as $row) {
      $sids[] = $row->sid;
      $submissions[$row->sid] = FALSE;
    }
  }

  // If there are no submissions being retrieved, return an empty array.
  if (empty($sids)) {
    return $submissions;
  }

  // Query the required submission data.
  $query = db_select('webform_submitted_data', 'sd');
  $query->leftJoin('webform_submissions', 's', 's.sid = sd.sid');
  $query->leftJoin('users', 'u', 'u.uid = s.uid');
  $query->leftJoin('webform_custom_data','cd','cd.sid=s.sid');
  $query
    ->fields('s')
    ->fields('sd', array('cid', 'no', 'data'))
    ->fields('u', array('name'))
    ->fields('cd',array('profile','store'))
    ->condition('sd.sid', $sids, 'IN')
    ->orderBy('sd.sid', 'ASC')
    ->orderBy('sd.cid', 'ASC')
    ->orderBy('sd.no', 'ASC');

  // By adding the NID to this query we allow MySQL to use the primary key on
  // in webform_submitted_data for sorting (nid_sid_cid_no).
  if (isset($filters['nid'])) {
    $query->condition('sd.nid', $filters['nid']);
  }

  $result = $query->execute();

  // Convert the queried rows into submissions.
  $previous = 0;
  foreach ($result as $row) {
    if ($row->sid != $previous) {
      $submissions[$row->sid] = new stdClass();
      $submissions[$row->sid]->sid = $row->sid;
      $submissions[$row->sid]->nid = $row->nid;
      $submissions[$row->sid]->submitted = $row->submitted;
      $submissions[$row->sid]->remote_addr = $row->remote_addr;
      $submissions[$row->sid]->uid = $row->uid;
      $submissions[$row->sid]->name = $row->name;
      $submissions[$row->sid]->is_draft = $row->is_draft;
      $submissions[$row->sid]->data = array();
      $submissions[$row->sid]->profile = $row->profile;
      $submissions[$row->sid]->store = $row->store;
    }
    // CID may be NULL if this submission does not actually contain any data.
    if ($row->cid) {
      $submissions[$row->sid]->data[$row->cid]['value'][$row->no] = $row->data;
    }
    $previous = $row->sid;
  }

  foreach (module_implements('webform_submission_load') as $module) {
    $function = $module . '_webform_submission_load';
    $function($submissions);
  }

  return $submissions;
}

/**
 * Fetch a specified submission for a webform node.
 */
function questionnaire_webform_get_submission($nid, $sid, $reset = FALSE) {
  static $submissions = array();

  if ($reset) {
    $submissions = array();
    if (!isset($sid)) {
      return;
    }
  }

  // Load the submission if needed.
  if (!isset($submissions[$sid])) {
    $new_submissions = questionnaire_webform_get_submissions(array('nid' => $nid, 'sid' => $sid));
    $submissions[$sid] = isset($new_submissions[$sid]) ? $new_submissions[$sid] : FALSE;
  }

  return $submissions[$sid];
}

/**
 * Menu callback; Present a Webform submission page for display or editing.
 */
function questionnaire_webform_submission_page($node, $submission, $format) {
	module_load_include('inc', 'webform', 'includes/webform.submissions');
  global $user;

  // Render the admin UI breadcrumb.
  webform_set_breadcrumb($node, $submission);

  // Set the correct page title.
  drupal_set_title(webform_submission_title($node, $submission));

  if ($format == 'form') {
    $output = drupal_get_form('webform_client_form_' . $node->nid, $node, $submission);
  }
  else {
    $output = webform_submission_render($node, $submission, NULL, $format);
  }
  // Determine the mode in which we're displaying this submission.
  $mode = ($format != 'form') ? 'display' : 'form';
  if (strpos(request_uri(), 'print/') !== FALSE) {
    $mode = 'print';
  }
  if (strpos(request_uri(), 'printpdf/') !== FALSE) {
    $mode = 'pdf';
  }

  // Add navigation for administrators.
  if (webform_results_access($node)) {
    $navigation = theme('webform_submission_navigation', array('node' => $node, 'submission' => $submission, 'mode' => $mode));
    $information = theme('webform_submission_information', array('node' => $node, 'submission' => $submission, 'mode' => $mode));
  }
  else {
    $navigation = NULL;
    $information = NULL;
  }

  // Actions may be shown to all users.
  $actions = theme('links', array('links' => module_invoke_all('webform_submission_actions', $node, $submission), 'attributes' => array('class' => array('links', 'inline', 'webform-submission-actions'))));

  // Disable the page cache for anonymous users viewing or editing submissions.
  if (!$user->uid) {
    webform_disable_page_cache();
  }

  $page = array(
    '#theme' => 'webform_submission_page',
    '#node' => $node,
    '#mode' => $mode,
    '#submission' => $submission,
    '#submission_content' => $output,
    '#submission_navigation' => $navigation,
    '#submission_information' => $information,
    '#submission_actions' => $actions,
  );
  $page['#attached']['library'][] = array('webform', 'admin');
  return $page;
}

/**
 * Confirm form to delete a single form submission.
 *
 * @param $form
 *   The new form array.
 * @param $form_state
 *   The current form state.
 * @param $node
 *   The node for which this webform was submitted.
 * @param $submission
 *   The submission to be deleted (from webform_submitted_data).
 */
function questionnaire_webform_submission_delete_form($form, $form_state, $node, $submission) {
	module_load_include('inc', 'webform', 'includes/webform.submissions');
  webform_set_breadcrumb($node, $submission);

  // Set the correct page title.
  drupal_set_title(webform_submission_title($node, $submission));

  // Keep the NID and SID in the same location as the webform_client_form().
  // This helps mollom identify the same fields when deleting a submission.
  $form['#tree'] = TRUE;
  $form['details']['nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );
  $form['details']['sid'] = array(
    '#type' => 'value',
    '#value' => $submission->sid,
  );

  $question = t('Are you sure you want to delete this submission?');

  if (isset($_GET['destination'])) {
    $destination = $_GET['destination'];
  }
  elseif (webform_results_access($node)) {
    $destination = 'node/' . $node->nid . '/webform-results';
  }
  else {
    $destination = 'node/' . $node->nid . '/submissions';
  }

  return confirm_form($form, NULL, $destination, $question, t('Delete'), t('Cancel'));
}

function questionnaire_webform_submission_delete_form_submit($form, &$form_state) {
  $node = node_load($form_state['values']['details']['nid']);
  $submission = questionnaire_webform_get_submission($form_state['values']['details']['nid'], $form_state['values']['details']['sid']);
  questionnaire_webform_submission_delete($node, $submission);
  drupal_set_message(t('Submission deleted.'));

  $form_state['redirect'] = 'node/' . $node->nid . '/webform-results';
}

/**
 * Delete a single submission.
 *
 * @param $node
 *   The node object containing the current webform.
 * @param $submission
 *   The webform submission object to be deleted from the database.
 */
function questionnaire_webform_submission_delete($node, $submission) {
  // Iterate through all components and let each do cleanup if necessary.
  foreach ($node->webform['components'] as $cid => $component) {
    if (isset($submission->data[$cid])) {
      webform_component_invoke($component['type'], 'delete', $component, $submission->data[$cid]['value']);
    }
  }

  // Delete any anonymous session information.
  if (isset($_SESSION['webform_submission'][$submission->sid])) {
    unset($_SESSION['webform_submission'][$submission->sid]);
  }

  db_delete('webform_submitted_data')
    ->condition('nid', $node->nid)
    ->condition('sid', $submission->sid)
    ->execute();
  db_delete('webform_submissions')
    ->condition('nid', $node->nid)
    ->condition('sid', $submission->sid)
    ->execute();
  db_delete('webform_custom_data')
    ->condition('nid', $node->nid)
    ->condition('sid', $submission->sid)
    ->execute();
  module_invoke_all('questionnaire_webform_submission_delete', $node, $submission);
}

/**
 * Create a table containing all submitted values for a webform node.
 */
function questionnaire_webform_results_table($node, $pager_count = 0) {
	module_load_include('inc', 'webform', 'includes/webform.submissions');
  if (isset($_GET['results']) && is_numeric($_GET['results'])) {
    $pager_count = $_GET['results'];
  }

  // Get all the submissions for the node.
  $header = theme('questionnaire_webform_results_table_header', array('node' => $node));
  $submissions = questionnaire_webform_get_submissions($node->nid, $header, $pager_count);
  $total_count = webform_get_submission_count($node->nid);

  $output = theme('questionnaire_webform_results_table', array('node' => $node, 'components' => $node->webform['components'], 'submissions' => $submissions, 'total_count' => $total_count, 'pager_count' => $pager_count));
  if ($pager_count) {
    $output .= theme('pager');
  }
  return $output;
}

function theme_questionnaire_webform_results_table_header($variables) {
  return array(
    array('data' => t('#'), 'field' => 'sid', 'sort' => 'desc'),
    array('data' => t('Submitted'), 'field' => 'submitted'),
    array('data' => t('User'), 'field' => 'name'),
    array('data' => t('Profile'), 'field' => 'profile'),
    array('data' => t('Store'), 'field' => 'store'),
  );
}

/**
 * Theme the results table displaying all the submissions for a particular node.
 *
 * @param $node
 *   The node whose results are being displayed.
 * @param $components
 *   An associative array of the components for this webform.
 * @param $submissions
 *   An array of all submissions for this webform.
 * @param $total_count
 *   The total number of submissions to this webform.
 * @param $pager_count
 *   The number of results to be shown per page.
 */
function theme_questionnaire_webform_results_table($variables) {
	module_load_include('inc', 'webform', 'includes/webform.submissions');
  drupal_add_library('webform', 'admin');

  $node = $variables['node'];
  $components = $variables['components'];
  $submissions = $variables['submissions'];
  $total_count = $variables['total_count'];
  $pager_count = $variables['pager_count'];

  $header = array();
  $rows = array();
  $cell = array();

  // This header has to be generated separately so we can add the SQL necessary.
  // to sort the results.
  $header = theme('questionnaire_webform_results_table_header', array('node' => $node));

  // Generate a row for each submission.
  foreach ($submissions as $sid => $submission) {
    $cell[] = l($sid, 'node/' . $node->nid . '/submission/' . $sid);
    $cell[] = format_date($submission->submitted, 'short');
    $cell[] = theme('username', array('account' => $submission));
    $cell[] = $submission->profile;
    $cell[] = $submission->store;
    $component_headers = array();

    // Generate a cell for each component.
    foreach ($node->webform['components'] as $component) {
      $data = isset($submission->data[$component['cid']]['value']) ? $submission->data[$component['cid']]['value'] : NULL;
      $submission_output = webform_component_invoke($component['type'], 'table', $component, $data);
      if ($submission_output !== NULL) {
        $component_headers[] = check_plain($component['name']);
        $cell[] = $submission_output;
      }
    }

    $rows[] = $cell;
    unset($cell);
  }
  if (!empty($component_headers)) {
    $header = array_merge($header, $component_headers);
  }

  if (count($rows) == 0) {
    $rows[] = array(array('data' => t('There are no submissions for this form. <a href="!url">View this form</a>.', array('!url' => url('node/' . $node->nid))), 'colspan' => 4));
  }


  $output = '';
  $output .= theme('webform_results_per_page', array('total_count' => $total_count, 'pager_count' => $pager_count));
  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  return $output;
}

/**
 * Form to configure the download of CSV files.
 */
function questionnaire_webform_results_download_form($form, &$form_state, $node) {
  module_load_include('inc', 'webform', 'includes/webform.export');
  module_load_include('inc', 'webform', 'includes/webform.components');
  module_load_include('inc', 'webform', 'includes/webform.report');
  
  $form = array();

  $form['node'] = array(
    '#type' => 'value',
    '#value' => $node,
  );

  $form['format'] = array(
    '#type' => 'radios',
    '#title' => t('Export format'),
    '#options' => webform_export_list(),
    '#default_value' => isset($form_state['values']['format']) ? $form_state['values']['format'] : variable_get('webform_export_format', 'delimited'),
  );

  $form['delimiter'] = array(
    '#type' => 'select',
    '#title' => t('Delimited text format'),
    '#description' => t('This is the delimiter used in the CSV/TSV file when downloading Webform results. Using tabs in the export is the most reliable method for preserving non-latin characters. You may want to change this to another character depending on the program with which you anticipate importing results.'),
    '#default_value' => isset($form_state['values']['delimiter']) ? $form_state['values']['delimiter'] : variable_get('webform_csv_delimiter', '\t'),
    '#options' => array(
      ','  => t('Comma (,)'),
      '\t' => t('Tab (\t)'),
      ';'  => t('Semicolon (;)'),
      ':'  => t('Colon (:)'),
      '|'  => t('Pipe (|)'),
      '.'  => t('Period (.)'),
      ' '  => t('Space ( )'),
    ),
  );

  $form['select_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select list options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['select_options']['select_keys'] = array(
    '#type' => 'radios',
    '#title' => t('Select keys'),
    '#options' => array(
      0 => t('Full, human-readable options (values)'),
      1 => t('Short, raw options (keys)'),
    ),
    '#default_value' => isset($form_state['values']['select_options']['select_keys']) ? $form_state['values']['select_options']['select_keys'] : 0,
    '#description' => t('Choose which part of options should be displayed from key|value pairs.'),
  );

  $form['select_options']['select_format'] = array(
    '#type' => 'radios',
    '#title' => t('Select list format'),
    '#options' => array(
      'separate' => t('Separate'),
      'compact' => t('Compact'),
    ),
    '#default_value' => isset($form_state['values']['select_options']['select_format']) ? $form_state['values']['select_options']['select_format'] : 'separate',
    '#attributes' => array('class' => array('webform-select-list-format')),
    '#theme' => 'webform_results_download_select_format',
  );

  $csv_components = array(
    'info' => t('Submission information'),
    'serial' => '-' . t('Submission Number'),
    'sid' => '-' . t('Submission ID'),
    'time' => '-' . t('Time'),
    'draft' => '-' . t('Draft'),
    'ip_address' => '-' . t('IP Address'),
    'uid' => '-' . t('User ID'),
    'username' => '-' . t('Username'),
    'profile' => '-' . t('Profile'),
  	'store' => '-' . t('Store'),
  );
  $csv_components += webform_component_list($node, 'csv', TRUE);

  $form['components'] = array(
    '#type' => 'select',
    '#title' => t('Included export components'),
    '#options' => $csv_components,
    '#default_value' => isset($form_state['values']['components']) ? $form_state['values']['components'] : array_keys($csv_components),
    '#multiple' => TRUE,
    '#size' => 10,
    '#description' => t('The selected components will be included in the export.'),
    '#process' => array('webform_component_select'),
  );

  $form['range'] = array(
    '#type' => 'fieldset',
    '#title' => t('Download range options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
    '#theme' => 'webform_results_download_range',
    '#element_validate' => array('webform_results_download_range_validate'),
    '#after_build' => array('webform_results_download_range_after_build'),
  );

  $form['range']['range_type'] = array(
    '#type' => 'radios',
    '#options' => array(
      'all' => t('All submissions'),
      'new' => t('Only new submissions since your last download'),
      'latest' => t('Only the latest'),
      'range' => t('All submissions starting from'),
    ),
    '#default_value' => 'all',
  );
  $form['range']['latest'] = array(
    '#type' => 'textfield',
    '#size' => 5,
    '#maxlength' => 8,
    '#default_value' => isset($form_state['values']['latest']) ? $form_state['values']['latest'] : '',
  );
  $form['range']['start'] = array(
    '#type' => 'textfield',
    '#size' => 5,
    '#maxlength' => 8,
    '#default_value' => '',
  );
  $form['range']['end'] = array(
    '#type' => 'textfield',
    '#size' => 5,
    '#maxlength' => 8,
    '#default_value' => '',
    '#description' => '',
  );

  // By default results are downloaded. User can override this value if
  // programmatically submitting this form.
  $form['download'] = array(
    '#type' => 'value',
    '#default_value' => TRUE
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Download'),
  );

  return $form;
}

/**
 * Validate handler for webform_results_download_form().
 */
function questionnaire_webform_results_download_form_submit(&$form, &$form_state) {
	module_load_include('inc', 'webform', 'includes/webform.report');
  $options = array(
    'delimiter' => $form_state['values']['delimiter'],
    'components' => array_keys(array_filter($form_state['values']['components'])),
    'select_keys' => $form_state['values']['select_keys'],
    'select_format' => $form_state['values']['select_format'],
    'range_type' => $form_state['values']['range']['range_type'],
    'download' => $form_state['values']['download'],
  );

  // Retrieve the list of required SIDs.
  if ($options['range_type'] != 'all') {
    $options['sids'] = questionnaire_webform_download_sids($form_state['values']['node']->nid, $form_state['values']['range']);
  }

  $export_info = questionnaire_webform_results_export($form_state['values']['node'], $form_state['values']['format'], $options);

  // If webform result file should be downloaded, send the file to the browser,
  // otherwise save information about the created file in $form_state.
  if ($options['download']) {
    webform_results_download($form_state['values']['node'], $export_info);
  }
  else {
    $form_state['export_info'] = $export_info;
  }
}

/**
 * Given a set of range options, retrieve a set of SIDs for a webform node.
 */
function questionnaire_webform_download_sids($nid, $range_options, $uid = NULL) {
  $query = db_select('webform_submissions', 'ws')
    ->fields('ws', array('sid'))
    ->condition('nid', $nid);

  switch ($range_options['range_type']) {
    case 'all':
      // All Submissions.
      $query->orderBy('sid', 'ASC');
      break;
    case 'new':
      // All Since Last Download.
      $download_info = webform_download_last_download_info($nid, $uid);
      $last_sid = $download_info ? $download_info['sid'] : 0;
      $query
        ->condition('sid', $last_sid, '>')
        ->orderBy('sid', 'ASC');
      break;
    case 'latest':
      // Last x Submissions.
      $query
        ->orderBy('sid', 'DESC')
        ->range(0, $range_options['latest']);
      break;
    case 'range':
      // Submissions Start-End.
      $query->condition('sid', $range_options['start'], '>=');
      if ($range_options['end']){
        $query->condition('sid', $range_options['end'], '<=');
      }
      $query->orderBy('sid', 'ASC');
      break;
  }

  $sids = $query->execute()->fetchCol();

  // The last x submissions option has SIDs that are in reverse order.
  if ($range_options['range_type'] == 'latest') {
    $sids = array_reverse($sids);
  }

  return $sids;
}

/**
 * Generate a Excel-readable CSV file containing all submissions for a Webform.
 *
 * The CSV requires that the data be presented in a flat file.  In order
 * to maximize usability to the Excel community and minimize subsequent
 * stats or spreadsheet programming this program extracts data from the
 * various records for a given session and presents them as a single file
 * where each row represents a single record.
 * The structure of the file is:
 *   Heading Line 1: Gives group overviews padded by empty cells to the
 *                   next group.  A group may be a question and corresponds
 *                   to a component in the webform philosophy. Each group
 *                   overview will have a fixed number of columns beneath it.
 *   Heading line 2: gives column headings
 *   Data line 1 .....
 *   Data line 2 .....
 *
 * An example of this format is given below.  Note the columns have had spaces
 * added so the columns line up.  This is not the case with actual file where
 * a column may be null.  Note also, that multiple choice questions as produced
 * by checkboxes or radio buttons have been presented as "yes" or "no" and the
 * actual choice text is retained only in the header line 2.
 * Data from text boxes and input fields are written out in the body of the table.
 *
 *   Submission Details,    ,   ,      ,Question 1,        ,        ,..,        ,Question 2,        ,        ,..,        ,Question n
 *   timestamp         ,time,SID,userid,Choice 1  ,Choice 2,Choice 3,..,Choice n,Choice 1  ,Choice 2,Choice 3,..,Choice n,Comment
 *   21 Feb 2005       ,1835,23 ,34    ,X         ,        ,        ,..,       ,X          ,X       ,X       ,..,X       ,My comment
 *   23 Feb 2005       ,1125,24 ,89    ,X         ,X       ,        ,..,       ,X          ,X       ,X       ,..,X       ,Hello
 *   .................................................................................................................................
 *   27 Feb 2005       ,1035,56 ,212   ,X         ,        ,        ,..,       ,X          ,X       ,X       ,..,X       ,How is this?
 *
 */
function questionnaire_webform_results_export($node, $format = 'delimited', $options = array()) {
  global $user;
  module_load_include('inc', 'webform', 'includes/webform.export');
  module_load_include('inc', 'webform', 'includes/webform.components');

  $submission_information = array(
    'serial' => t('Serial'),
    'sid' => t('SID'),
    'time' => t('Time'),
    'draft' => t('Draft'),
    'ip_address' => t('IP Address'),
    'uid' => t('UID'),
    'username' => t('Username'),
  	'profile' => t('Profile'),
  	'store' => t('Store'),
  );

  if (empty($options)) {
    $options = array(
      'delimiter' => variable_get('webform_csv_delimiter', '\t'),
      'components' => array_merge(array_keys($submission_information), array_keys(webform_component_list($node, 'csv', TRUE))),
      'select_keys' => 0,
      'select_format' => 'separate',
      'range_type' => 'all',
    );
  }
  else {
    foreach ($submission_information as $key => $label) {
      if (!in_array($key, $options['components'])) {
        unset($submission_information[$key]);
      }
    }
  }

  // Open a new Webform exporter object.
  $exporter = webform_export_create_handler($format, $options);

  $file_name = drupal_tempnam('temporary://', 'webform_');
  $handle = @fopen($file_name, 'w'); // The @ suppresses errors.
  $exporter->bof($handle);

  // Fill in the header for the submission information (if any).
  $header[2] = $header[1] = $header[0] = count($submission_information) ? array_fill(0, count($submission_information), '') : array();
  if (count($submission_information)) {
    $header[0][0] = $node->title;
    $header[1][0] = t('Submission Details');
    foreach (array_values($submission_information) as $column => $label) {
      $header[2][$column] = $label;
    }
  }

  // Compile header information for components.
  foreach ($options['components'] as $cid) {
    if (isset($node->webform['components'][$cid])) {
      $component = $node->webform['components'][$cid];

      // Let each component determine its headers.
      if (webform_component_feature($component['type'], 'csv')) {
        $component_header = (array) webform_component_invoke($component['type'], 'csv_headers', $component, $options);
        $header[0] = array_merge($header[0], (array) $component_header[0]);
        $header[1] = array_merge($header[1], (array) $component_header[1]);
        $header[2] = array_merge($header[2], (array) $component_header[2]);

        // Allow modules to modify the CSV header.
        drupal_alter('webform_csv_header', $component_header, $component);
      }
    }
  }

  // Add headers to the file.
  foreach ($header as $row) {
    $exporter->add_row($handle, $row);
  }

  // Get all the required submissions for the download.
  $filters['nid'] = $node->nid;
  if (!empty($options['sids'])){
    $filters['sid'] = $options['sids'];
  }
  $submissions = questionnaire_webform_get_submissions($filters);

  // Generate a row for each submission.
  $row_count = 0;
  $sid = 0;
  foreach ($submissions as $sid => $submission) {
    $row_count++;

    $row = array();
    if (isset($submission_information['serial'])) {
      $row[] = $row_count;
    }
    if (isset($submission_information['sid'])) {
      $row[] = $sid;
    }
    if (isset($submission_information['time'])) {
      $row[] = format_date($submission->submitted, 'short');
    }
    if (isset($submission_information['draft'])) {
      $row[] = $submission->is_draft;
    }
    if (isset($submission_information['ip_address'])) {
      $row[] =  $submission->remote_addr;
    }
    if (isset($submission_information['uid'])) {
      $row[] = $submission->uid;
    }
    if (isset($submission_information['username'])) {
      $row[] = $submission->name;
    }
    if (isset($submission_information['profile'])) {
      $row[] = $submission->profile;
    }
    if (isset($submission_information['store'])) {
      $row[] = $submission->store;
    }

    foreach ($options['components'] as $cid) {
      if (isset($node->webform['components'][$cid])) {
        $component = $node->webform['components'][$cid];
        // Let each component add its data.
        $raw_data = isset($submission->data[$cid]['value']) ? $submission->data[$cid]['value'] : NULL;
        if (webform_component_feature($component['type'], 'csv')) {
          $data = webform_component_invoke($component['type'], 'csv_data', $component, $options, $raw_data);

          // Allow modules to modify the CSV data.
          drupal_alter('webform_csv_data', $data, $component, $submission);

          if (is_array($data)) {
            $row = array_merge($row, array_values($data));
          }
          else {
            $row[] = isset($data) ? $data : '';
          }
        }
      }
    }

    // Write data from submissions.
    $data = $exporter->add_row($handle, $row);
  }

  // Add the closing bytes.
  $exporter->eof($handle);

  // Close the file.
  @fclose($handle);

  $export_info['options'] = $options;
  $export_info['file_name'] = $file_name;
  $export_info['exporter'] = $exporter;
  $export_info['row_count'] = $row_count;
  $export_info['last_sid'] = $sid;

  return $export_info;
}

/**
 * Send a generated webform results file to the user's browser.
 *
 * @param $node
 *   The webform node.
 * @param $export_info
 *   Export information array retrieved from webform_results_export().
 */
function questionnaire_webform_results_download($node, $export_info) {
  global $user;

  // $exporter, $file_name, $row_count
  $export_name = _webform_safe_name($node->title);
  $export_info['exporter']->set_headers($export_name);
  @readfile($export_info['file_name']);  // The @ makes it silent.
  @unlink($export_info['file_name']);  // Clean up, the @ makes it silent.

  // Update user last downloaded sid if required.
  if ($export_info['options']['range_type'] != 'range' && $export_info['row_count'] > 0) {
    // Delete existing record.
    db_delete('webform_last_download')
      ->condition('nid', $node->nid)
      ->condition('uid', $user->uid)
      ->execute();
    // Write new record.
    db_insert('webform_last_download')
      ->fields(array(
        'nid' => $node->nid,
        'uid' => $user->uid,
        'sid' => $export_info['last_sid'],
        'requested' => REQUEST_TIME,
      ))
      ->execute();
  }

  exit();
}

/**
 * Confirmation form to delete all submissions for a node.
 *
 * @param $nid
 *   ID of node for which to clear submissions.
 */
function questionnaire_webform_results_clear_form($form, $form_state, $node) {
  drupal_set_title(t('Clear Form Submissions'));

  $form = array();
  $form['nid'] = array('#type' => 'value', '#value' => $node->nid);
  $question = t('Are you sure you want to delete all submissions for this form?');

  return confirm_form($form, $question, 'node/' . $node->nid . '/webform-results', NULL, t('Clear'), t('Cancel'));
}

function questionnaire_webform_results_clear_form_submit($form, &$form_state) {
  questionnaire_webform_results_clear($form_state['values']['nid']);
  $node = node_load($form_state['values']['nid']);
  $title = $node->title;
  $message = t('Webform %title entries cleared.', array('%title' => $title));
  drupal_set_message($message);
  watchdog('webform', $message);
  $form_state['redirect'] = 'node/' . $form_state['values']['nid'] . '/webform-results';
}

/**
 * Delete all submissions for a node.
 *
 * @param $nid
 *   The node id whose submissions will be deleted.
 */
function questionnaire_webform_results_clear($nid) {
  $node = node_load($nid);
  $submissions = questionnaire_webform_get_submissions($nid);
  foreach ($submissions as $submission) {
    questionnaire_webform_submission_delete($node, $submission);
  }
}