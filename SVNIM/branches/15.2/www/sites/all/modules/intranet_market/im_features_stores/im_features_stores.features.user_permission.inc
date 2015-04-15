<?php
/**
 * @file
 * im_features_stores.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function im_features_stores_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create preferred_store content'.
  $permissions['create preferred_store content'] = array(
    'name' => 'create preferred_store content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'contributor_alert' => 'contributor_alert',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any operational_model content'.
  $permissions['delete any operational_model content'] = array(
    'name' => 'delete any operational_model content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any preferred_store content'.
  $permissions['delete any preferred_store content'] = array(
    'name' => 'delete any preferred_store content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own preferred_store content'.
  $permissions['delete own preferred_store content'] = array(
    'name' => 'delete own preferred_store content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'contributor_alert' => 'contributor_alert',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any preferred_store content'.
  $permissions['edit any preferred_store content'] = array(
    'name' => 'edit any preferred_store content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'contributor_alert' => 'contributor_alert',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own preferred_store content'.
  $permissions['edit own preferred_store content'] = array(
    'name' => 'edit own preferred_store content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'contributor_alert' => 'contributor_alert',
    ),
    'module' => 'node',
  );

  return $permissions;
}
