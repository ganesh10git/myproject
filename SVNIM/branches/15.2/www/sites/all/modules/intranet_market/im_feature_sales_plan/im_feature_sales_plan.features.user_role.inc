<?php
/**
 * @file
 * im_feature_sales_plan.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function im_feature_sales_plan_user_default_roles() {
  $roles = array();

  // Exported role: contributor_sales_plan.
  $roles['contributor_sales_plan'] = array(
    'name' => 'contributor_sales_plan',
    'weight' => 8,
  );

  return $roles;
}
