<?php
/**
 * @file
 * im_features_application.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function im_features_application_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'delete terms in application_category'.
  $permissions['delete terms in application_category'] = array(
    'name' => 'delete terms in application_category',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in application_category'.
  $permissions['edit terms in application_category'] = array(
    'name' => 'edit terms in application_category',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  return $permissions;
}
