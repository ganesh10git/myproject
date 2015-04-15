<?php
/**
 * @file
 * im_feature_holiday.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function im_feature_holiday_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create holiday content'.
  $permissions['create holiday content'] = array(
    'name' => 'create holiday content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any holiday content'.
  $permissions['delete any holiday content'] = array(
    'name' => 'delete any holiday content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own holiday content'.
  $permissions['delete own holiday content'] = array(
    'name' => 'delete own holiday content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any holiday content'.
  $permissions['edit any holiday content'] = array(
    'name' => 'edit any holiday content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own holiday content'.
  $permissions['edit own holiday content'] = array(
    'name' => 'edit own holiday content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
