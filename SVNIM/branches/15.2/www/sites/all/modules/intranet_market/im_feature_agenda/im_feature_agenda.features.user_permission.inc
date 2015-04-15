<?php
/**
 * @file
 * im_feature_agenda.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function im_feature_agenda_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'content_manager_action' => 'content_manager_action',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_news' => 'contributor_news',
      'contributor_benchmark' => 'contributor_benchmark',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access workbench'.
  $permissions['access workbench'] = array(
    'name' => 'access workbench',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_news' => 'contributor_news',
      'contributor_benchmark' => 'contributor_benchmark',
    ),
    'module' => 'workbench',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
    ),
    'module' => 'menu',
  );

  // Exported permission: 'archive'.
  $permissions['archive'] = array(
    'name' => 'archive',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
    ),
    'module' => 'im_agenda',
  );

  // Exported permission: 'ask for publication'.
  $permissions['ask for publication'] = array(
    'name' => 'ask for publication',
    'roles' => array(
      'contributor_action' => 'contributor_action',
    ),
    'module' => 'im_agenda',
  );

  // Exported permission: 'create action content'.
  $permissions['create action content'] = array(
    'name' => 'create action content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'contributor_action' => 'contributor_action',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create alert content'.
  $permissions['create alert content'] = array(
    'name' => 'create alert content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_alert' => 'contributor_alert',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create benchmark content'.
  $permissions['create benchmark content'] = array(
    'name' => 'create benchmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_benchmark' => 'contributor_benchmark',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create news content'.
  $permissions['create news content'] = array(
    'name' => 'create news content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_news' => 'contributor_news',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any action content'.
  $permissions['delete any action content'] = array(
    'name' => 'delete any action content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any alert content'.
  $permissions['delete any alert content'] = array(
    'name' => 'delete any alert content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any benchmark content'.
  $permissions['delete any benchmark content'] = array(
    'name' => 'delete any benchmark content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any news content'.
  $permissions['delete any news content'] = array(
    'name' => 'delete any news content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own action content'.
  $permissions['delete own action content'] = array(
    'name' => 'delete own action content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'contributor_action' => 'contributor_action',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own alert content'.
  $permissions['delete own alert content'] = array(
    'name' => 'delete own alert content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_alert' => 'contributor_alert',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own benchmark content'.
  $permissions['delete own benchmark content'] = array(
    'name' => 'delete own benchmark content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own news content'.
  $permissions['delete own news content'] = array(
    'name' => 'delete own news content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_news' => 'contributor_news',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any action content'.
  $permissions['edit any action content'] = array(
    'name' => 'edit any action content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any alert content'.
  $permissions['edit any alert content'] = array(
    'name' => 'edit any alert content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any benchmark content'.
  $permissions['edit any benchmark content'] = array(
    'name' => 'edit any benchmark content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any news content'.
  $permissions['edit any news content'] = array(
    'name' => 'edit any news content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own action content'.
  $permissions['edit own action content'] = array(
    'name' => 'edit own action content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'contributor_action' => 'contributor_action',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own alert content'.
  $permissions['edit own alert content'] = array(
    'name' => 'edit own alert content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_alert' => 'contributor_alert',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own benchmark content'.
  $permissions['edit own benchmark content'] = array(
    'name' => 'edit own benchmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_benchmark' => 'contributor_benchmark',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own news content'.
  $permissions['edit own news content'] = array(
    'name' => 'edit own news content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_news' => 'contributor_news',
    ),
    'module' => 'node',
  );

  // Exported permission: 'moderate content from draft to needs_review'.
  $permissions['moderate content from draft to needs_review'] = array(
    'name' => 'moderate content from draft to needs_review',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'contributor_action' => 'contributor_action',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from needs_review to draft'.
  $permissions['moderate content from needs_review to draft'] = array(
    'name' => 'moderate content from needs_review to draft',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from needs_review to published'.
  $permissions['moderate content from needs_review to published'] = array(
    'name' => 'moderate content from needs_review to published',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'publish'.
  $permissions['publish'] = array(
    'name' => 'publish',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_news' => 'contributor_news',
    ),
    'module' => 'im_agenda',
  );

  // Exported permission: 'publish now'.
  $permissions['publish now'] = array(
    'name' => 'publish now',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
    ),
    'module' => 'im_agenda',
  );

  // Exported permission: 'return publication'.
  $permissions['return publication'] = array(
    'name' => 'return publication',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
    ),
    'module' => 'im_agenda',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
    ),
    'module' => 'node',
  );

  // Exported permission: 'save draft'.
  $permissions['save draft'] = array(
    'name' => 'save draft',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_news' => 'contributor_news',
    ),
    'module' => 'im_agenda',
  );

  // Exported permission: 'use workbench_moderation my drafts tab'.
  $permissions['use workbench_moderation my drafts tab'] = array(
    'name' => 'use workbench_moderation my drafts tab',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_news' => 'contributor_news',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'use workbench_moderation needs review tab'.
  $permissions['use workbench_moderation needs review tab'] = array(
    'name' => 'use workbench_moderation needs review tab',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view all unpublished content'.
  $permissions['view all unpublished content'] = array(
    'name' => 'view all unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view moderation history'.
  $permissions['view moderation history'] = array(
    'name' => 'view moderation history',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view moderation messages'.
  $permissions['view moderation messages'] = array(
    'name' => 'view moderation messages',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_news' => 'contributor_news',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_news' => 'contributor_news',
    ),
    'module' => 'node',
  );

  return $permissions;
}
