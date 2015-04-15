<?php
/**
 * @file
 * im_feature_holiday.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function im_feature_holiday_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function im_feature_holiday_node_info() {
  $items = array(
    'holiday' => array(
      'name' => t('Holiday'),
      'base' => 'node_content',
      'description' => t('This content will help in managing the calendar for the various years.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
