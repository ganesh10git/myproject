<?php
/**
 * @file
 * im_features_application.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function im_features_application_taxonomy_default_vocabularies() {
  return array(
    'application_category' => array(
      'name' => t('Application Category'),
      'machine_name' => 'application_category',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
