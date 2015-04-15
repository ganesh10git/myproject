<?php
/**
 * @file
 * im_feature_sales_plan.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function im_feature_sales_plan_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create sales_plan content'.
  $permissions['create sales_plan content'] = array(
    'name' => 'create sales_plan content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_sales_plan' => 'contributor_sales_plan',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any sales_plan content'.
  $permissions['delete any sales_plan content'] = array(
    'name' => 'delete any sales_plan content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_sales_plan' => 'contributor_sales_plan',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own sales_plan content'.
  $permissions['delete own sales_plan content'] = array(
    'name' => 'delete own sales_plan content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_sales_plan' => 'contributor_sales_plan',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in regions'.
  $permissions['delete terms in regions'] = array(
    'name' => 'delete terms in regions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any sales_plan content'.
  $permissions['edit any sales_plan content'] = array(
    'name' => 'edit any sales_plan content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_sales_plan' => 'contributor_sales_plan',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own sales_plan content'.
  $permissions['edit own sales_plan content'] = array(
    'name' => 'edit own sales_plan content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_sales_plan' => 'contributor_sales_plan',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in regions'.
  $permissions['edit terms in regions'] = array(
    'name' => 'edit terms in regions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  return $permissions;
}
