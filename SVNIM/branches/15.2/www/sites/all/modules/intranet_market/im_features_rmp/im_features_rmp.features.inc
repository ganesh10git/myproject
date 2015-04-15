<?php
/**
 * @file
 * im_features_rmp.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function im_features_rmp_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function im_features_rmp_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function im_features_rmp_node_info() {
  $items = array(
    'regional_moderator_profile' => array(
      'name' => t('Regional Moderator Profile'),
      'base' => 'node_content',
      'description' => t('Use this content type for creating Regional Moderator Profile type content.'),
      'has_title' => '1',
      'title_label' => t('Titre'),
      'help' => '',
    ),
    'regional_profiles' => array(
      'name' => t('Regional Profiles'),
      'base' => 'node_content',
      'description' => t('content type for regional moderator profiles'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
