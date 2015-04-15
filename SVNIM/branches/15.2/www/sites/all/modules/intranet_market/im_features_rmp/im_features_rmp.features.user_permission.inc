<?php
/**
 * @file
 * im_features_rmp.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function im_features_rmp_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create regional_moderator_profile content'.
  $permissions['create regional_moderator_profile content'] = array(
    'name' => 'create regional_moderator_profile content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create regional_profiles content'.
  $permissions['create regional_profiles content'] = array(
    'name' => 'create regional_profiles content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any regional_moderator_profile content'.
  $permissions['delete any regional_moderator_profile content'] = array(
    'name' => 'delete any regional_moderator_profile content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any regional_profiles content'.
  $permissions['delete any regional_profiles content'] = array(
    'name' => 'delete any regional_profiles content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own regional_moderator_profile content'.
  $permissions['delete own regional_moderator_profile content'] = array(
    'name' => 'delete own regional_moderator_profile content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own regional_profiles content'.
  $permissions['delete own regional_profiles content'] = array(
    'name' => 'delete own regional_profiles content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any regional_moderator_profile content'.
  $permissions['edit any regional_moderator_profile content'] = array(
    'name' => 'edit any regional_moderator_profile content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any regional_profiles content'.
  $permissions['edit any regional_profiles content'] = array(
    'name' => 'edit any regional_profiles content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own regional_moderator_profile content'.
  $permissions['edit own regional_moderator_profile content'] = array(
    'name' => 'edit own regional_moderator_profile content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own regional_profiles content'.
  $permissions['edit own regional_profiles content'] = array(
    'name' => 'edit own regional_profiles content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  return $permissions;
}
