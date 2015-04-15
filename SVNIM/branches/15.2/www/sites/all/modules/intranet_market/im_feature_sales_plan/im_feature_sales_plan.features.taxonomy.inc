<?php
/**
 * @file
 * im_feature_sales_plan.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function im_feature_sales_plan_taxonomy_default_vocabularies() {
  return array(
    'regions' => array(
      'name' => t('Regions'),
      'machine_name' => 'regions',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
