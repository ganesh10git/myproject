<?php
/**
 * @file
 * im_features_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function im_features_permissions_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 3,
  );

  // Exported role: content_manager_action_regional.
  $roles['content_manager_action_regional'] = array(
    'name' => 'content_manager_action_regional',
    'weight' => 11,
  );

  // Exported role: content_manager_om.
  $roles['content_manager_om'] = array(
    'name' => 'content_manager_om',
    'weight' => 3,
  );

  // Exported role: contributor_om.
  $roles['contributor_om'] = array(
    'name' => 'contributor_om',
    'weight' => 2,
  );

  // Exported role: contributor_sales_plan.
  $roles['contributor_sales_plan'] = array(
    'name' => 'contributor_sales_plan',
    'weight' => 8,
  );

  // Exported role: expert.
  $roles['expert'] = array(
    'name' => 'expert',
    'weight' => 4,
  );

  // Exported role: technical_director.
  $roles['technical_director'] = array(
    'name' => 'technical_director',
    'weight' => 3,
  );

  // Exported role: visitor.
  $roles['visitor'] = array(
    'name' => 'visitor',
    'weight' => 3,
  );

  return $roles;
}
