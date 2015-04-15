<?php
/**
 * @file
 * im_feature_agenda.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function im_feature_agenda_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function im_feature_agenda_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function im_feature_agenda_node_info() {
  $items = array(
    'action' => array(
      'name' => t('Action'),
      'base' => 'node_content',
      'description' => t('Use this content type for creating Action type content.'),
      'has_title' => '1',
      'title_label' => t('Titre'),
      'help' => '',
    ),
    'alert' => array(
      'name' => t('Alerte'),
      'base' => 'node_content',
      'description' => t('Use this content type for creating Alert type content.'),
      'has_title' => '1',
      'title_label' => t('Titre'),
      'help' => '',
    ),
    'benchmark' => array(
      'name' => t('Benchmark'),
      'base' => 'node_content',
      'description' => t('Use this content type for creating Benchmark type content.'),
      'has_title' => '1',
      'title_label' => t('Titre'),
      'help' => '',
    ),
    'news' => array(
      'name' => t('Actu Market'),
      'base' => 'node_content',
      'description' => t('Use this content type for creating News type content.'),
      'has_title' => '1',
      'title_label' => t('Titre'),
      'help' => '',
    ),
  );
  return $items;
}
