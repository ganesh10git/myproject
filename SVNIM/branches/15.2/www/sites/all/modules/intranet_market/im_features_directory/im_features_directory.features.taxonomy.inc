<?php
/**
 * @file
 * im_features_directory.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function im_features_directory_taxonomy_default_vocabularies() {
  return array(
    'directory_category' => array(
      'name' => t('Annuaire Category'),
      'machine_name' => 'directory_category',
      'description' => 'Taxonomy term for directory',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
