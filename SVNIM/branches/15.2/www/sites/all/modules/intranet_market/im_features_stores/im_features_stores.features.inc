<?php
/**
 * @file
 * im_features_stores.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function im_features_stores_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function im_features_stores_node_info() {
  $items = array(
    'preferred_store' => array(
      'name' => t('Preferred Store'),
      'base' => 'node_content',
      'description' => t('User store preferred store'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
