<?php
/**
 * @file
 * im_features_application.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function im_features_application_user_default_roles() {
  $roles = array();

  // Exported role: content_manager_om.
  $roles['content_manager_om'] = array(
    'name' => 'content_manager_om',
    'weight' => 11,
  );

  // Exported role: contributor_om.
  $roles['contributor_om'] = array(
    'name' => 'contributor_om',
    'weight' => 10,
  );

  return $roles;
}
