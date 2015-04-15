<?php

/**
 * Override or insert variables into page templates.
 */
function adaptivetheme_admin_preprocess_page(&$vars) {
  // RFC2822 date format
  if ($rfc = date("r" , time())) {
    $vars['datetime_rfc'] = t('@time', array('@time' => $rfc));
  }
  else {
    $rfc = '';
    $vars['datetime_rfc'] = '';
  }
  // ISO 8601 date format
  if ($iso = gmdate('Y-m-d\TH:i:sO')) {
    $vars['datetime_iso'] = $iso;
  }
  else {
    $iso = '';
    $vars['datetime_iso'] = '';
  }
  
  $vars['content_header_attributes_array']['class'][] = 'branding-elements';
  $vars['content_header_attributes_array']['role'][] = 'banner';
}

/**
 * Alter the search block form.
 */
function adaptivetheme_admin_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'search_block_form') {
    $form['search_block_form']['#title'] = t('Search');
    $form['search_block_form']['#title_display'] = 'invisible';
    $form['search_block_form']['#size'] = 20;
    $form['search_block_form']['#attributes']['placeholder'] = t('Search');
    $form['actions']['submit']['#value'] = t('Go');
  }
}

/**
 * Implements template_preprocess_views_view().
 * Change the "Change to Draft" link open in Popup mode.
 * IM-13 : Action: Return the Publication
 * @param $vars
 */
function adaptivetheme_admin_preprocess_views_view(&$vars) {
  $view = $vars['view'];
  if ($view->name == "workbench_moderation") {
    $output = !empty($vars['rows']) ? $vars['rows'] : $vars['empty'];
    $form = drupal_get_form(views_form_id($view), $view, $output);
    $vars['rows'] = $form;
  }
}
/**
 * 
 * Alter Date fields for Holiday.
 * @param object $vars
 */
function adaptivetheme_admin_date_part_label_date($vars) {
  
  if (isset($vars['element']['#field']['field_name']) && in_array($vars['element']['#field']['field_name'], array('field_holiday_zone_a', 'field_holiday_zone_b', 'field_holiday_zone_c'))) {
    return t($vars['element']['#date_title']);
  } else {
    return t('Date');
  }
}

function adaptivetheme_admin_file_link(&$variables) {
  $file = $variables['file'];
  $icon_directory = $variables['icon_directory'];

  $url = file_create_url($file->uri);
  $formatted_url = $url;
  $icon = theme('file_icon', array('file' => $file, 'icon_directory' => $icon_directory));
  // Set options as per anchor format described at
  // http://microformats.org/wiki/file-format-examples
  $options = array(
    'attributes' => array(
      'type' => $file->filemime . '; length=' . $file->filesize,
    ),
  );
  // Use the description as the link text if available.
  if (empty($file->description)) {
    $link_text = $file->filename;
  }
  else {
    $link_text = $file->description;
    $options['attributes']['title'] = check_plain($file->filename);
  }
  
  return '<span class="file">' . $icon . ' ' . '<a href="'.$formatted_url.'">'.$link_text.'</a></span>';
}