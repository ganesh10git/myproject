<?php

/**
 * @file workbench_moderation.view.inc
 * Default view. Provides two tabs on the Workbench, "My drafts" and "Needs
 * review", which list the moderation state for content relevant to the current
 * user.
 */

$view = new view();
$view->name = 'archives';
$view->description = 'Lists of Archive contents.';
$view->tag = 'Workbench Moderation';
$view->base_table = 'node';
$view->human_name = 'Archives';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['title'] = 'Archived Contents';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'access workbench';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['distinct'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '25';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
$handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 25, 50, 100, 200';
$handler->display->display_options['pager']['options']['tags']['first'] = '« premier';
$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ précédent';
$handler->display->display_options['pager']['options']['tags']['next'] = 'suivant ›';
$handler->display->display_options['pager']['options']['tags']['last'] = 'dernier »';
$handler->display->display_options['style_plugin'] = 'table';
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = 'This list displays content in the "Archives" state. Currently there is no such content.';
$handler->display->display_options['empty']['area']['format'] = 'full_html';
/* Relationship: Content: Author */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'node';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
/* Field: Content: Scope of Content */
$handler->display->display_options['fields']['field_action_scope_of_content']['id'] = 'field_action_scope_of_content';
$handler->display->display_options['fields']['field_action_scope_of_content']['table'] = 'field_data_field_action_scope_of_content';
$handler->display->display_options['fields']['field_action_scope_of_content']['field'] = 'field_action_scope_of_content';
/* Field: Content: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
/* Field: Content: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'uid';
$handler->display->display_options['fields']['name']['label'] = 'Author';
/* Field: Content: Updated date */
$handler->display->display_options['fields']['changed']['id'] = 'changed';
$handler->display->display_options['fields']['changed']['table'] = 'node';
$handler->display->display_options['fields']['changed']['field'] = 'changed';
$handler->display->display_options['fields']['changed']['label'] = 'Last updated';
$handler->display->display_options['fields']['changed']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['changed']['date_format'] = 'time ago';
/* Field: Content: Edit link */
$handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
$handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
$handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
$handler->display->display_options['fields']['edit_node']['label'] = 'Actions';
$handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['edit_node']['text'] = 'Edit';
/* Sort criterion: Content: Post date */
$handler->display->display_options['sorts']['created']['id'] = 'created';
$handler->display->display_options['sorts']['created']['table'] = 'node';
$handler->display->display_options['sorts']['created']['field'] = 'created';
$handler->display->display_options['sorts']['created']['order'] = 'DESC';
/* Filter criterion: Content: node_archive (field_node_archive) */
$handler->display->display_options['filters']['field_node_archive_value']['id'] = 'field_node_archive_value';
$handler->display->display_options['filters']['field_node_archive_value']['table'] = 'field_data_field_node_archive';
$handler->display->display_options['filters']['field_node_archive_value']['field'] = 'field_node_archive_value';
$handler->display->display_options['filters']['field_node_archive_value']['value'] = array(
  1 => '1',
);
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'action' => 'action',
  'news' => 'news',
  'alert' => 'alert',
  'benchmark' => 'benchmark',
  'sales_plan' => 'sales_plan',
  'operational_model' => 'operational_model',
  'questionnaire' => 'questionnaire',
);
$handler->display->display_options['filters']['type']['exposed'] = TRUE;
$handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
$handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
$handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  10 => 0,
  8 => 0,
  9 => 0,
  4 => 0,
  13 => 0,
  14 => 0,
  15 => 0,
  3 => 0,
  12 => 0,
  5 => 0,
  7 => 0,
  11 => 0,
  6 => 0,
);
$handler->display->display_options['filters']['type']['expose']['reduce'] = TRUE;
/* Filter criterion: Content: Title */
$handler->display->display_options['filters']['title']['id'] = 'title';
$handler->display->display_options['filters']['title']['table'] = 'node';
$handler->display->display_options['filters']['title']['field'] = 'title';
$handler->display->display_options['filters']['title']['operator'] = 'contains';
$handler->display->display_options['filters']['title']['exposed'] = TRUE;
$handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
$handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
$handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  10 => 0,
  8 => 0,
  9 => 0,
  4 => 0,
  13 => 0,
  14 => 0,
  15 => 0,
  3 => 0,
  12 => 0,
  5 => 0,
  7 => 0,
  11 => 0,
  6 => 0,
);
/* Filter criterion: Content: Scope of Content (field_action_scope_of_content) */
$handler->display->display_options['filters']['field_action_scope_of_content_value']['id'] = 'field_action_scope_of_content_value';
$handler->display->display_options['filters']['field_action_scope_of_content_value']['table'] = 'field_data_field_action_scope_of_content';
$handler->display->display_options['filters']['field_action_scope_of_content_value']['field'] = 'field_action_scope_of_content_value';
$handler->display->display_options['filters']['field_action_scope_of_content_value']['value'] = array(
  'all' => 'all',
  'national' => 'national',
  'regional' => 'regional',
);
/* Filter criterion: Content: Agenda Store (field_agenda_store) */
$handler->display->display_options['filters']['field_agenda_store_value']['id'] = 'field_agenda_store_value';
$handler->display->display_options['filters']['field_agenda_store_value']['table'] = 'field_data_field_agenda_store';
$handler->display->display_options['filters']['field_agenda_store_value']['field'] = 'field_agenda_store_value';

/* Display: Archive contents */
$handler = $view->new_display('page', 'Archive contents', 'page');
$handler->display->display_options['display_description'] = 'Lists of Archive contents.';
$handler->display->display_options['path'] = 'admin/workbench/archives';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Archives';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$translatables['archives'] = array(
  t('Defaults'),
  t('Archived Contents'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Items per page'),
  t('- All -'),
  t('Offset'),
  t('« premier'),
  t('‹ précédent'),
  t('suivant ›'),
  t('dernier »'),
  t('This list displays content in the "Archives" state. Currently there is no such content.'),
  t('author'),
  t('Title'),
  t('Scope of Content'),
  t('Type'),
  t('Nid'),
  t('Author'),
  t('Last updated'),
  t('Actions'),
  t('Edit'),
  t('Archive contents'),
  t('Lists of Archive contents.'),
);