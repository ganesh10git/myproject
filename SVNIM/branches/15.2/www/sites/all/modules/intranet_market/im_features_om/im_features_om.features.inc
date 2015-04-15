<?php
/**
 * @file
 * im_features_om.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function im_features_om_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function im_features_om_node_info() {
  $items = array(
    'operational_model' => array(
      'name' => t('Operational Model'),
      'base' => 'node_content',
      'description' => t('Use this content type for creating Operational Model type content.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
