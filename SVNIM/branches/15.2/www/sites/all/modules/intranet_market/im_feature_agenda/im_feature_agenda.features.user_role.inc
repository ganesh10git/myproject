<?php
/**
 * @file
 * im_feature_agenda.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function im_feature_agenda_user_default_roles() {
  $roles = array();

  // Exported role: content_manager_action.
  $roles['content_manager_action'] = array(
    'name' => 'content_manager_action',
    'weight' => 4,
  );

  // Exported role: contributor_action.
  $roles['contributor_action'] = array(
    'name' => 'contributor_action',
    'weight' => 3,
  );

  // Exported role: contributor_alert.
  $roles['contributor_alert'] = array(
    'name' => 'contributor_alert',
    'weight' => 5,
  );

  // Exported role: contributor_benchmark.
  $roles['contributor_benchmark'] = array(
    'name' => 'contributor_benchmark',
    'weight' => 10,
  );

  // Exported role: contributor_news.
  $roles['contributor_news'] = array(
    'name' => 'contributor_news',
    'weight' => 7,
  );

  return $roles;
}
