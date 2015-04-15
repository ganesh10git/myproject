<?php
/**
 * @file
 * im_feature_sales_plan.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function im_feature_sales_plan_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function im_feature_sales_plan_node_info() {
  $items = array(
    'sales_plan' => array(
      'name' => t('Sales plan'),
      'base' => 'node_content',
      'description' => t('Use this content type for creating  various sales promotions.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
