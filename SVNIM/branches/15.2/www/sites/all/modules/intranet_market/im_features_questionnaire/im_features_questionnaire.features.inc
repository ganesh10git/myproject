<?php
/**
 * @file
 * im_features_questionnaire.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function im_features_questionnaire_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function im_features_questionnaire_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function im_features_questionnaire_node_info() {
  $items = array(
    'questionnaire' => array(
      'name' => t('Questionnaire'),
      'base' => 'node_content',
      'description' => t('Intranet market Questionnaire'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}