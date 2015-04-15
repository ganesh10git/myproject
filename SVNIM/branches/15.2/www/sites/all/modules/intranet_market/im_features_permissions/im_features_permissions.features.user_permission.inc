<?php
/**
 * @file
 * im_features_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function im_features_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access administration menu'.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_benchmark' => 'contributor_benchmark',
      'contributor_news' => 'contributor_news',
      'contributor_om' => 'contributor_om',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_benchmark' => 'contributor_benchmark',
      'contributor_news' => 'contributor_news',
      'contributor_om' => 'contributor_om',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access all views'.
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'views',
  );

  // Exported permission: 'access all webform results'.
  $permissions['access all webform results'] = array(
    'name' => 'access all webform results',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'technical_director' => 'technical_director',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access contextual links'.
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'contextual',
  );

  // Exported permission: 'access dashboard'.
  $permissions['access dashboard'] = array(
    'name' => 'access dashboard',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'dashboard',
  );

  // Exported permission: 'access own webform results'.
  $permissions['access own webform results'] = array(
    'name' => 'access own webform results',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
      'technical_director' => 'technical_director',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access own webform submissions'.
  $permissions['access own webform submissions'] = array(
    'name' => 'access own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
      'technical_director' => 'technical_director',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access site in maintenance mode'.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access site reports'.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'user',
  );

  // Exported permission: 'access workbench'.
  $permissions['access workbench'] = array(
    'name' => 'access workbench',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_benchmark' => 'contributor_benchmark',
      'contributor_news' => 'contributor_news',
      'contributor_om' => 'contributor_om',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'workbench',
  );

  // Exported permission: 'administer actions'.
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer blocks'.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'block',
  );

  // Exported permission: 'administer ckeditor'.
  $permissions['administer ckeditor'] = array(
    'name' => 'administer ckeditor',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'ckeditor',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer features'.
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'features',
  );

  // Exported permission: 'administer field collections'.
  $permissions['administer field collections'] = array(
    'name' => 'administer field collections',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'field_collection',
  );

  // Exported permission: 'administer fieldgroups'.
  $permissions['administer fieldgroups'] = array(
    'name' => 'administer fieldgroups',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'field_group',
  );

  // Exported permission: 'administer filters'.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'administer image styles'.
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'image',
  );

  // Exported permission: 'administer languages'.
  $permissions['administer languages'] = array(
    'name' => 'administer languages',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'locale',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'menu',
  );

  // Exported permission: 'administer modules'.
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer scheduler'.
  $permissions['administer scheduler'] = array(
    'name' => 'administer scheduler',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'scheduler',
  );

  // Exported permission: 'administer search'.
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'search',
  );

  // Exported permission: 'administer site configuration'.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer software updates'.
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer taxonomy'.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'administer themes'.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer url aliases'.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'path',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer views'.
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'views',
  );

  // Exported permission: 'administer workbench'.
  $permissions['administer workbench'] = array(
    'name' => 'administer workbench',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'workbench',
  );

  // Exported permission: 'administer workbench moderation'.
  $permissions['administer workbench moderation'] = array(
    'name' => 'administer workbench moderation',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'archive'.
  $permissions['archive'] = array(
    'name' => 'archive',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'technical_director' => 'technical_director',
    ),
    'module' => 'im_agenda',
  );

  // Exported permission: 'ask for publication'.
  $permissions['ask for publication'] = array(
    'name' => 'ask for publication',
    'roles' => array(
      'contributor_action' => 'contributor_action',
      'contributor_om' => 'contributor_om',
      'expert' => 'expert',
    ),
    'module' => 'im_agenda',
  );

  // Exported permission: 'block IP addresses'.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'system',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'bypass workbench moderation'.
  $permissions['bypass workbench moderation'] = array(
    'name' => 'bypass workbench moderation',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'cancel account'.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'user',
  );

  // Exported permission: 'change own username'.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'user',
  );

  // Exported permission: 'create action content'.
  $permissions['create action content'] = array(
    'name' => 'create action content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create alert content'.
  $permissions['create alert content'] = array(
    'name' => 'create alert content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_alert' => 'contributor_alert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create application content'.
  $permissions['create application content'] = array(
    'name' => 'create application content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create benchmark content'.
  $permissions['create benchmark content'] = array(
    'name' => 'create benchmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_benchmark' => 'contributor_benchmark',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create holiday content'.
  $permissions['create holiday content'] = array(
    'name' => 'create holiday content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create message content'.
  $permissions['create message content'] = array(
    'name' => 'create message content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create new version'.
  $permissions['create new version'] = array(
    'name' => 'create new version',
    'roles' => array(
      'content_manager_om' => 'content_manager_om',
      'expert' => 'expert',
    ),
    'module' => 'im_features_om',
  );

  // Exported permission: 'create news content'.
  $permissions['create news content'] = array(
    'name' => 'create news content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_news' => 'contributor_news',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create operational_model content'.
  $permissions['create operational_model content'] = array(
    'name' => 'create operational_model content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_om' => 'content_manager_om',
      'contributor_om' => 'contributor_om',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create preferred_store content'.
  $permissions['create preferred_store content'] = array(
    'name' => 'create preferred_store content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'contributor_alert' => 'contributor_alert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create questionnaire content'.
  $permissions['create questionnaire content'] = array(
    'name' => 'create questionnaire content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create sales_plan content'.
  $permissions['create sales_plan content'] = array(
    'name' => 'create sales_plan content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create url aliases'.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'path',
  );

  // Exported permission: 'create webform content'.
  $permissions['create webform content'] = array(
    'name' => 'create webform content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
    ),
    'module' => 'node',
  );

  // Exported permission: 'customize ckeditor'.
  $permissions['customize ckeditor'] = array(
    'name' => 'customize ckeditor',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'ckeditor',
  );

  // Exported permission: 'delete all webform submissions'.
  $permissions['delete all webform submissions'] = array(
    'name' => 'delete all webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete any action content'.
  $permissions['delete any action content'] = array(
    'name' => 'delete any action content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any alert content'.
  $permissions['delete any alert content'] = array(
    'name' => 'delete any alert content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any application content'.
  $permissions['delete any application content'] = array(
    'name' => 'delete any application content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any benchmark content'.
  $permissions['delete any benchmark content'] = array(
    'name' => 'delete any benchmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any holiday content'.
  $permissions['delete any holiday content'] = array(
    'name' => 'delete any holiday content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any message content'.
  $permissions['delete any message content'] = array(
    'name' => 'delete any message content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any news content'.
  $permissions['delete any news content'] = array(
    'name' => 'delete any news content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any operational_model content'.
  $permissions['delete any operational_model content'] = array(
    'name' => 'delete any operational_model content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_om' => 'content_manager_om',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any preferred_store content'.
  $permissions['delete any preferred_store content'] = array(
    'name' => 'delete any preferred_store content',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any questionnaire content'.
  $permissions['delete any questionnaire content'] = array(
    'name' => 'delete any questionnaire content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any sales_plan content'.
  $permissions['delete any sales_plan content'] = array(
    'name' => 'delete any sales_plan content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any webform content'.
  $permissions['delete any webform content'] = array(
    'name' => 'delete any webform content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own action content'.
  $permissions['delete own action content'] = array(
    'name' => 'delete own action content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own alert content'.
  $permissions['delete own alert content'] = array(
    'name' => 'delete own alert content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_alert' => 'contributor_alert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own application content'.
  $permissions['delete own application content'] = array(
    'name' => 'delete own application content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own benchmark content'.
  $permissions['delete own benchmark content'] = array(
    'name' => 'delete own benchmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_benchmark' => 'contributor_benchmark',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own holiday content'.
  $permissions['delete own holiday content'] = array(
    'name' => 'delete own holiday content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own message content'.
  $permissions['delete own message content'] = array(
    'name' => 'delete own message content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own news content'.
  $permissions['delete own news content'] = array(
    'name' => 'delete own news content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_news' => 'contributor_news',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own operational_model content'.
  $permissions['delete own operational_model content'] = array(
    'name' => 'delete own operational_model content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_om' => 'content_manager_om',
      'contributor_om' => 'contributor_om',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own preferred_store content'.
  $permissions['delete own preferred_store content'] = array(
    'name' => 'delete own preferred_store content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'contributor_alert' => 'contributor_alert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own questionnaire content'.
  $permissions['delete own questionnaire content'] = array(
    'name' => 'delete own questionnaire content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own sales_plan content'.
  $permissions['delete own sales_plan content'] = array(
    'name' => 'delete own sales_plan content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform content'.
  $permissions['delete own webform content'] = array(
    'name' => 'delete own webform content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform submissions'.
  $permissions['delete own webform submissions'] = array(
    'name' => 'delete own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
      'technical_director' => 'technical_director',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in agenda_department'.
  $permissions['delete terms in agenda_department'] = array(
    'name' => 'delete terms in agenda_department',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in application_category'.
  $permissions['delete terms in application_category'] = array(
    'name' => 'delete terms in application_category',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in fonctions'.
  $permissions['delete terms in fonctions'] = array(
    'name' => 'delete terms in fonctions',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in om_domains'.
  $permissions['delete terms in om_domains'] = array(
    'name' => 'delete terms in om_domains',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in om_roles'.
  $permissions['delete terms in om_roles'] = array(
    'name' => 'delete terms in om_roles',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in operational_model_location'.
  $permissions['delete terms in operational_model_location'] = array(
    'name' => 'delete terms in operational_model_location',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in regions'.
  $permissions['delete terms in regions'] = array(
    'name' => 'delete terms in regions',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'display drupal links'.
  $permissions['display drupal links'] = array(
    'name' => 'display drupal links',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'dropdown_checkboxes_settings'.
  $permissions['dropdown_checkboxes_settings'] = array(
    'name' => 'dropdown_checkboxes_settings',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'dropdown_checkboxes',
  );

  // Exported permission: 'edit all webform submissions'.
  $permissions['edit all webform submissions'] = array(
    'name' => 'edit all webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'technical_director' => 'technical_director',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit any action content'.
  $permissions['edit any action content'] = array(
    'name' => 'edit any action content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any alert content'.
  $permissions['edit any alert content'] = array(
    'name' => 'edit any alert content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any application content'.
  $permissions['edit any application content'] = array(
    'name' => 'edit any application content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any benchmark content'.
  $permissions['edit any benchmark content'] = array(
    'name' => 'edit any benchmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any holiday content'.
  $permissions['edit any holiday content'] = array(
    'name' => 'edit any holiday content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any message content'.
  $permissions['edit any message content'] = array(
    'name' => 'edit any message content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any news content'.
  $permissions['edit any news content'] = array(
    'name' => 'edit any news content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any operational_model content'.
  $permissions['edit any operational_model content'] = array(
    'name' => 'edit any operational_model content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_om' => 'content_manager_om',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any preferred_store content'.
  $permissions['edit any preferred_store content'] = array(
    'name' => 'edit any preferred_store content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'contributor_alert' => 'contributor_alert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any questionnaire content'.
  $permissions['edit any questionnaire content'] = array(
    'name' => 'edit any questionnaire content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any sales_plan content'.
  $permissions['edit any sales_plan content'] = array(
    'name' => 'edit any sales_plan content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any webform content'.
  $permissions['edit any webform content'] = array(
    'name' => 'edit any webform content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own action content'.
  $permissions['edit own action content'] = array(
    'name' => 'edit own action content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own alert content'.
  $permissions['edit own alert content'] = array(
    'name' => 'edit own alert content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_alert' => 'contributor_alert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own application content'.
  $permissions['edit own application content'] = array(
    'name' => 'edit own application content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own benchmark content'.
  $permissions['edit own benchmark content'] = array(
    'name' => 'edit own benchmark content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_benchmark' => 'contributor_benchmark',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own holiday content'.
  $permissions['edit own holiday content'] = array(
    'name' => 'edit own holiday content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own message content'.
  $permissions['edit own message content'] = array(
    'name' => 'edit own message content',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own news content'.
  $permissions['edit own news content'] = array(
    'name' => 'edit own news content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_news' => 'contributor_news',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own operational_model content'.
  $permissions['edit own operational_model content'] = array(
    'name' => 'edit own operational_model content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_om' => 'content_manager_om',
      'contributor_om' => 'contributor_om',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own preferred_store content'.
  $permissions['edit own preferred_store content'] = array(
    'name' => 'edit own preferred_store content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'contributor_alert' => 'contributor_alert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own questionnaire content'.
  $permissions['edit own questionnaire content'] = array(
    'name' => 'edit own questionnaire content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own sales_plan content'.
  $permissions['edit own sales_plan content'] = array(
    'name' => 'edit own sales_plan content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform content'.
  $permissions['edit own webform content'] = array(
    'name' => 'edit own webform content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform submissions'.
  $permissions['edit own webform submissions'] = array(
    'name' => 'edit own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
      'technical_director' => 'technical_director',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit terms in agenda_department'.
  $permissions['edit terms in agenda_department'] = array(
    'name' => 'edit terms in agenda_department',
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

  // Exported permission: 'edit terms in fonctions'.
  $permissions['edit terms in fonctions'] = array(
    'name' => 'edit terms in fonctions',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in om_domains'.
  $permissions['edit terms in om_domains'] = array(
    'name' => 'edit terms in om_domains',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in om_roles'.
  $permissions['edit terms in om_roles'] = array(
    'name' => 'edit terms in om_roles',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in operational_model_location'.
  $permissions['edit terms in operational_model_location'] = array(
    'name' => 'edit terms in operational_model_location',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in regions'.
  $permissions['edit terms in regions'] = array(
    'name' => 'edit terms in regions',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'flush caches'.
  $permissions['flush caches'] = array(
    'name' => 'flush caches',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'generate features'.
  $permissions['generate features'] = array(
    'name' => 'generate features',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'features',
  );

  // Exported permission: 'manage features'.
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'features',
  );

  // Exported permission: 'moderate content from draft to needs_review'.
  $permissions['moderate content from draft to needs_review'] = array(
    'name' => 'moderate content from draft to needs_review',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'contributor_action' => 'contributor_action',
      'contributor_om' => 'contributor_om',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from needs_review to draft'.
  $permissions['moderate content from needs_review to draft'] = array(
    'name' => 'moderate content from needs_review to draft',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'technical_director' => 'technical_director',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from needs_review to published'.
  $permissions['moderate content from needs_review to published'] = array(
    'name' => 'moderate content from needs_review to published',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'technical_director' => 'technical_director',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'publish'.
  $permissions['publish'] = array(
    'name' => 'publish',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'contributor_alert' => 'contributor_alert',
      'contributor_benchmark' => 'contributor_benchmark',
      'contributor_news' => 'contributor_news',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'technical_director' => 'technical_director',
    ),
    'module' => 'im_agenda',
  );

  // Exported permission: 'publish now'.
  $permissions['publish now'] = array(
    'name' => 'publish now',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'technical_director' => 'technical_director',
    ),
    'module' => 'im_agenda',
  );

  // Exported permission: 'return publication'.
  $permissions['return publication'] = array(
    'name' => 'return publication',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'technical_director' => 'technical_director',
    ),
    'module' => 'im_agenda',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'save draft'.
  $permissions['save draft'] = array(
    'name' => 'save draft',
    'roles' => array(
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_benchmark' => 'contributor_benchmark',
      'contributor_news' => 'contributor_news',
      'contributor_om' => 'contributor_om',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'im_agenda',
  );

  // Exported permission: 'schedule (un)publishing of nodes'.
  $permissions['schedule (un)publishing of nodes'] = array(
    'name' => 'schedule (un)publishing of nodes',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'scheduler',
  );

  // Exported permission: 'search content'.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'technical_director' => 'technical_director',
    ),
    'module' => 'search',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'user',
  );

  // Exported permission: 'translate interface'.
  $permissions['translate interface'] = array(
    'name' => 'translate interface',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'locale',
  );

  // Exported permission: 'use PHP for title patterns'.
  $permissions['use PHP for title patterns'] = array(
    'name' => 'use PHP for title patterns',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'auto_nodetitle',
  );

  // Exported permission: 'use advanced search'.
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'search',
  );

  // Exported permission: 'use permission select'.
  $permissions['use permission select'] = array(
    'name' => 'use permission select',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'permission_select',
  );

  // Exported permission: 'use text format basic_html'.
  $permissions['use text format basic_html'] = array(
    'name' => 'use text format basic_html',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format filtered_html'.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_benchmark' => 'contributor_benchmark',
      'contributor_news' => 'contributor_news',
      'contributor_om' => 'contributor_om',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'technical_director' => 'technical_director',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_news' => 'contributor_news',
      'contributor_om' => 'contributor_om',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use workbench_moderation my drafts tab'.
  $permissions['use workbench_moderation my drafts tab'] = array(
    'name' => 'use workbench_moderation my drafts tab',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'contributor_action' => 'contributor_action',
      'contributor_om' => 'contributor_om',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'use workbench_moderation needs review tab'.
  $permissions['use workbench_moderation needs review tab'] = array(
    'name' => 'use workbench_moderation needs review tab',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'contributor_action' => 'contributor_action',
      'contributor_om' => 'contributor_om',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view all unpublished content'.
  $permissions['view all unpublished content'] = array(
    'name' => 'view all unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view moderation history'.
  $permissions['view moderation history'] = array(
    'name' => 'view moderation history',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view moderation messages'.
  $permissions['view moderation messages'] = array(
    'name' => 'view moderation messages',
    'roles' => array(
      'technical_director' => 'technical_director',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_benchmark' => 'contributor_benchmark',
      'contributor_news' => 'contributor_news',
      'contributor_om' => 'contributor_om',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'technical_director' => 'technical_director',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'administrator' => 'administrator',
      'content_manager_action' => 'content_manager_action',
      'content_manager_action_regional' => 'content_manager_action_regional',
      'content_manager_om' => 'content_manager_om',
      'contributor_action' => 'contributor_action',
      'contributor_alert' => 'contributor_alert',
      'contributor_benchmark' => 'contributor_benchmark',
      'contributor_news' => 'contributor_news',
      'contributor_om' => 'contributor_om',
      'contributor_sales_plan' => 'contributor_sales_plan',
      'expert' => 'expert',
      'technical_director' => 'technical_director',
    ),
    'module' => 'system',
  );

  return $permissions;
}
