<?php
/**
 * @file
 * im_features_om.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function im_features_om_taxonomy_default_vocabularies() {
  return array(
    'om_domains' => array(
      'name' => t('Operational Model Domains'),
      'machine_name' => 'om_domains',
      'description' => 'Operational Model Domains Subdomains and Macro activity',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'om_roles' => array(
      'name' => t('Operational Model roles'),
      'machine_name' => 'om_roles',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'operational_model_location' => array(
      'name' => t('Operational Model Location'),
      'machine_name' => 'operational_model_location',
      'description' => 'Operational Model Location',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
