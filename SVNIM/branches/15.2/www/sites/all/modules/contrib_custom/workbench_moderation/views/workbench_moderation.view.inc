<?php

/**
 * @file workbench_moderation.view.inc
 * Default view. Provides two tabs on the Workbench, "My drafts" and "Needs
 * review", which list the moderation state for content relevant to the current
 * user.
 */

$view = new view();
$view->name = 'workbench_moderation';
$view->description = 'Lists content by moderation state.';
$view->tag = 'Workbench Moderation';
$view->base_table = 'node_revision';
$view->human_name = 'Workbench Moderate: Content';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['title'] = 'Content I\'ve edited';
$handler->display->display_options['use_more_always'] = TRUE;
$handler->display->display_options['use_more_text'] = 'view all';
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'use workbench_moderation my drafts tab';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['distinct'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['submit_button'] = 'Appliquer';
$handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Réinitialiser';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '25';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
$handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 25, 50, 100, 200';
$handler->display->display_options['pager']['options']['tags']['first'] = '« premier';
$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ précédent';
$handler->display->display_options['pager']['options']['tags']['next'] = 'suivant ›';
$handler->display->display_options['pager']['options']['tags']['last'] = 'dernier »';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'nid' => 'nid',
  'log' => 'log',
  'nothing' => 'nothing',
  'state' => 'state',
  'moderation_actions' => 'moderation_actions',
  'title' => 'title',
  'type' => 'type',
  'name' => 'name',
  'changed' => 'changed',
);
$handler->display->display_options['style_options']['default'] = 'changed';
$handler->display->display_options['style_options']['info'] = array(
  'nid' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'log' => array(
    'align' => '',
    'separator' => '',
  ),
  'nothing' => array(
    'align' => '',
    'separator' => '',
  ),
  'state' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'moderation_actions' => array(
    'align' => '',
    'separator' => '',
  ),
  'title' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'type' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'name' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'changed' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
  ),
);
$handler->display->display_options['style_options']['order'] = 'desc';
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['content'] = 'You haven\'t created or edited any content.';
$handler->display->display_options['empty']['area']['format'] = '1';
/* Relationship: Workbench Moderation: Nœud */
$handler->display->display_options['relationships']['nid']['id'] = 'nid';
$handler->display->display_options['relationships']['nid']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['relationships']['nid']['field'] = 'nid';
$handler->display->display_options['relationships']['nid']['required'] = TRUE;
/* Relationship: Content revision: Utilisateur */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'node_revision';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
/* Relationship: Contenu: Auteur */
$handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
$handler->display->display_options['relationships']['uid_1']['table'] = 'node';
$handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
$handler->display->display_options['relationships']['uid_1']['relationship'] = 'nid';
$handler->display->display_options['relationships']['uid_1']['required'] = TRUE;
/* Relationship: Utilisateur: Content authored */
$handler->display->display_options['relationships']['uid_2']['id'] = 'uid_2';
$handler->display->display_options['relationships']['uid_2']['table'] = 'users';
$handler->display->display_options['relationships']['uid_2']['field'] = 'uid';
$handler->display->display_options['relationships']['uid_2']['relationship'] = 'uid_1';
/* Champ: Contenu: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['relationship'] = 'nid';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid']['link_to_node'] = TRUE;
/* Champ: Content revision: Log message */
$handler->display->display_options['fields']['log']['id'] = 'log';
$handler->display->display_options['fields']['log']['table'] = 'node_revision';
$handler->display->display_options['fields']['log']['field'] = 'log';
$handler->display->display_options['fields']['log']['exclude'] = TRUE;
/* Champ: Workbench Moderation: Moderation history link */
$handler->display->display_options['fields']['workbench_moderation_history_link']['id'] = 'workbench_moderation_history_link';
$handler->display->display_options['fields']['workbench_moderation_history_link']['table'] = 'node';
$handler->display->display_options['fields']['workbench_moderation_history_link']['field'] = 'workbench_moderation_history_link';
$handler->display->display_options['fields']['workbench_moderation_history_link']['exclude'] = TRUE;
$handler->display->display_options['fields']['workbench_moderation_history_link']['hide_alter_empty'] = FALSE;
/* Champ: Moderation state */
$handler->display->display_options['fields']['state']['id'] = 'state';
$handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['fields']['state']['field'] = 'state';
$handler->display->display_options['fields']['state']['ui_name'] = 'Moderation state';
$handler->display->display_options['fields']['state']['label'] = 'Moderation state';
$handler->display->display_options['fields']['state']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['state']['alter']['text'] = '<div>[state]</div><div>[workbench_moderation_history_link]</div>';
$handler->display->display_options['fields']['state']['hide_alter_empty'] = FALSE;
$handler->display->display_options['fields']['state']['machine_name'] = 0;
/* Champ: Workbench Moderation: Moderation links */
$handler->display->display_options['fields']['moderation_actions']['id'] = 'moderation_actions';
$handler->display->display_options['fields']['moderation_actions']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['fields']['moderation_actions']['field'] = 'moderation_actions';
$handler->display->display_options['fields']['moderation_actions']['label'] = 'Set moderation state';
/* Champ: Contenu: Titre */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['relationship'] = 'nid';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
/* Champ: Contenu: Scope of Content */
$handler->display->display_options['fields']['field_action_scope_of_content']['id'] = 'field_action_scope_of_content';
$handler->display->display_options['fields']['field_action_scope_of_content']['table'] = 'field_data_field_action_scope_of_content';
$handler->display->display_options['fields']['field_action_scope_of_content']['field'] = 'field_action_scope_of_content';
$handler->display->display_options['fields']['field_action_scope_of_content']['relationship'] = 'nid';
$handler->display->display_options['fields']['field_action_scope_of_content']['label'] = 'Périmètre de diffusion';
/* Champ: Contenu: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['relationship'] = 'nid';
$handler->display->display_options['fields']['type']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['type']['alter']['ellipsis'] = FALSE;
/* Champ: Utilisateur: Nom */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'uid';
$handler->display->display_options['fields']['name']['label'] = 'Revised by';
/* Champ: Contenu: Updated date */
$handler->display->display_options['fields']['changed']['id'] = 'changed';
$handler->display->display_options['fields']['changed']['table'] = 'node';
$handler->display->display_options['fields']['changed']['field'] = 'changed';
$handler->display->display_options['fields']['changed']['relationship'] = 'nid';
$handler->display->display_options['fields']['changed']['label'] = 'Last updated';
$handler->display->display_options['fields']['changed']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['changed']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['changed']['date_format'] = 'time ago';
/* Champ: Contenu: Edit link */
$handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
$handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
$handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
$handler->display->display_options['fields']['edit_node']['relationship'] = 'nid';
/* Sort criterion: Contenu: Updated date */
$handler->display->display_options['sorts']['changed']['id'] = 'changed';
$handler->display->display_options['sorts']['changed']['table'] = 'node';
$handler->display->display_options['sorts']['changed']['field'] = 'changed';
$handler->display->display_options['sorts']['changed']['relationship'] = 'nid';
/* Filter criterion: Utilisateur: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
/* Filter criterion: Contenu: Titre */
$handler->display->display_options['filters']['title']['id'] = 'title';
$handler->display->display_options['filters']['title']['table'] = 'node';
$handler->display->display_options['filters']['title']['field'] = 'title';
$handler->display->display_options['filters']['title']['relationship'] = 'nid';
$handler->display->display_options['filters']['title']['operator'] = 'contains';
$handler->display->display_options['filters']['title']['exposed'] = TRUE;
$handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
$handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
$handler->display->display_options['filters']['title']['expose']['remember'] = TRUE;
/* Filter criterion: Contenu: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['relationship'] = 'nid';
$handler->display->display_options['filters']['type']['exposed'] = TRUE;
$handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
$handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
$handler->display->display_options['filters']['type']['expose']['remember'] = TRUE;
/* Filter criterion: Workbench Moderation: State */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['value'] = array(
  'all' => 'all',
  'draft' => 'draft',
  'needs_review' => 'needs_review',
  'published' => 'published',
);
$handler->display->display_options['filters']['state']['exposed'] = TRUE;
$handler->display->display_options['filters']['state']['expose']['operator_id'] = 'state_op';
$handler->display->display_options['filters']['state']['expose']['label'] = 'State';
$handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
$handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
$handler->display->display_options['filters']['state']['expose']['remember'] = TRUE;
$handler->display->display_options['filters']['state']['expose']['reduce'] = TRUE;
/* Filter criterion: Workbench Moderation: Current */
$handler->display->display_options['filters']['current']['id'] = 'current';
$handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['current']['field'] = 'current';

/* Display: Needs review page */
$handler = $view->new_display('page', 'Needs review page', 'needs_review_page');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Needs review';
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'use workbench_moderation needs review tab';
$handler->display->display_options['defaults']['empty'] = FALSE;
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['content'] = 'This list displays content in the "Needs review" state that you can moderate. Currently there is no such content.';
$handler->display->display_options['empty']['area']['format'] = 'plain_text';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Champ: Contenu: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['relationship'] = 'nid';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid']['link_to_node'] = TRUE;
/* Champ: Content revision: Log message */
$handler->display->display_options['fields']['log']['id'] = 'log';
$handler->display->display_options['fields']['log']['table'] = 'node_revision';
$handler->display->display_options['fields']['log']['field'] = 'log';
$handler->display->display_options['fields']['log']['exclude'] = TRUE;
/* Champ: Workbench Moderation: Moderation history link */
$handler->display->display_options['fields']['workbench_moderation_history_link']['id'] = 'workbench_moderation_history_link';
$handler->display->display_options['fields']['workbench_moderation_history_link']['table'] = 'node';
$handler->display->display_options['fields']['workbench_moderation_history_link']['field'] = 'workbench_moderation_history_link';
$handler->display->display_options['fields']['workbench_moderation_history_link']['exclude'] = TRUE;
$handler->display->display_options['fields']['workbench_moderation_history_link']['hide_alter_empty'] = FALSE;
/* Champ: Moderation state */
$handler->display->display_options['fields']['state']['id'] = 'state';
$handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['fields']['state']['field'] = 'state';
$handler->display->display_options['fields']['state']['ui_name'] = 'Moderation state';
$handler->display->display_options['fields']['state']['label'] = 'Moderation state';
$handler->display->display_options['fields']['state']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['state']['alter']['text'] = '<div>[state]</div><div>[workbench_moderation_history_link]</div>';
$handler->display->display_options['fields']['state']['hide_alter_empty'] = FALSE;
$handler->display->display_options['fields']['state']['machine_name'] = 0;
/* Champ: Workbench Moderation: Moderation links */
$handler->display->display_options['fields']['moderation_actions']['id'] = 'moderation_actions';
$handler->display->display_options['fields']['moderation_actions']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['fields']['moderation_actions']['field'] = 'moderation_actions';
$handler->display->display_options['fields']['moderation_actions']['label'] = 'Set moderation state';
/* Champ: Contenu: Titre */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['relationship'] = 'nid';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
/* Champ: Contenu: Scope of Content */
$handler->display->display_options['fields']['field_action_scope_of_content']['id'] = 'field_action_scope_of_content';
$handler->display->display_options['fields']['field_action_scope_of_content']['table'] = 'field_data_field_action_scope_of_content';
$handler->display->display_options['fields']['field_action_scope_of_content']['field'] = 'field_action_scope_of_content';
$handler->display->display_options['fields']['field_action_scope_of_content']['relationship'] = 'nid';
$handler->display->display_options['fields']['field_action_scope_of_content']['label'] = 'Périmètre de diffusion';
/* Champ: Contenu: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['relationship'] = 'nid';
$handler->display->display_options['fields']['type']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['type']['alter']['ellipsis'] = FALSE;
/* Champ: Contenu: Attached Regional Profiles */
$handler->display->display_options['fields']['field_attached_regional_profiles']['id'] = 'field_attached_regional_profiles';
$handler->display->display_options['fields']['field_attached_regional_profiles']['table'] = 'field_data_field_attached_regional_profiles';
$handler->display->display_options['fields']['field_attached_regional_profiles']['field'] = 'field_attached_regional_profiles';
$handler->display->display_options['fields']['field_attached_regional_profiles']['relationship'] = 'nid';
$handler->display->display_options['fields']['field_attached_regional_profiles']['label'] = 'Profils régionaux attachés';
$handler->display->display_options['fields']['field_attached_regional_profiles']['delta_offset'] = '0';
/* Champ: Utilisateur: Full Name */
$handler->display->display_options['fields']['field_full_name']['id'] = 'field_full_name';
$handler->display->display_options['fields']['field_full_name']['table'] = 'field_data_field_full_name';
$handler->display->display_options['fields']['field_full_name']['field'] = 'field_full_name';
$handler->display->display_options['fields']['field_full_name']['relationship'] = 'uid';
$handler->display->display_options['fields']['field_full_name']['label'] = 'Revised by';
/* Champ: Contenu: Updated date */
$handler->display->display_options['fields']['changed']['id'] = 'changed';
$handler->display->display_options['fields']['changed']['table'] = 'node';
$handler->display->display_options['fields']['changed']['field'] = 'changed';
$handler->display->display_options['fields']['changed']['relationship'] = 'nid';
$handler->display->display_options['fields']['changed']['label'] = 'Last updated';
$handler->display->display_options['fields']['changed']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['changed']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['changed']['date_format'] = 'time ago';
/* Champ: Contenu: Edit link */
$handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
$handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
$handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
$handler->display->display_options['fields']['edit_node']['relationship'] = 'nid';
$handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
$handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['edit_node']['alter']['text'] = '<img src = "/sites/all/themes/im/css/images/edit-Pen.png" />';
/* Champ: Utilisateur: Nom */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'uid';
$handler->display->display_options['fields']['name']['label'] = 'Revised by';
$handler->display->display_options['fields']['name']['exclude'] = TRUE;
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: Workbench Moderation: Current */
$handler->display->display_options['filters']['current']['id'] = 'current';
$handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['current']['field'] = 'current';
$handler->display->display_options['filters']['current']['value'] = '1';
$handler->display->display_options['filters']['current']['group'] = 1;
/* Filter criterion: Workbench Moderation: State */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['value'] = array(
  'needs_review' => 'needs_review',
);
$handler->display->display_options['filters']['state']['group'] = 1;
$handler->display->display_options['filters']['state']['expose']['label'] = 'Workbench Moderation: State';
$handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
$handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
/* Filter criterion: Contenu: Titre */
$handler->display->display_options['filters']['title']['id'] = 'title';
$handler->display->display_options['filters']['title']['table'] = 'node';
$handler->display->display_options['filters']['title']['field'] = 'title';
$handler->display->display_options['filters']['title']['relationship'] = 'nid';
$handler->display->display_options['filters']['title']['operator'] = 'contains';
$handler->display->display_options['filters']['title']['group'] = 1;
$handler->display->display_options['filters']['title']['exposed'] = TRUE;
$handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
$handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
$handler->display->display_options['filters']['title']['expose']['remember'] = TRUE;
/* Filter criterion: Contenu: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['relationship'] = 'nid';
$handler->display->display_options['filters']['type']['group'] = 1;
$handler->display->display_options['filters']['type']['exposed'] = TRUE;
$handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
$handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
$handler->display->display_options['filters']['type']['expose']['remember'] = TRUE;
/* Filter criterion: Contenu: Scope of Content (field_action_scope_of_content) */
$handler->display->display_options['filters']['field_action_scope_of_content_value']['id'] = 'field_action_scope_of_content_value';
$handler->display->display_options['filters']['field_action_scope_of_content_value']['table'] = 'field_data_field_action_scope_of_content';
$handler->display->display_options['filters']['field_action_scope_of_content_value']['field'] = 'field_action_scope_of_content_value';
$handler->display->display_options['filters']['field_action_scope_of_content_value']['relationship'] = 'nid';
$handler->display->display_options['filters']['field_action_scope_of_content_value']['group'] = 1;
$handler->display->display_options['filters']['field_action_scope_of_content_value']['exposed'] = TRUE;
$handler->display->display_options['filters']['field_action_scope_of_content_value']['expose']['operator_id'] = 'field_action_scope_of_content_value_op';
$handler->display->display_options['filters']['field_action_scope_of_content_value']['expose']['label'] = 'Scope of Content';
$handler->display->display_options['filters']['field_action_scope_of_content_value']['expose']['operator'] = 'field_action_scope_of_content_value_op';
$handler->display->display_options['filters']['field_action_scope_of_content_value']['expose']['identifier'] = 'field_action_scope_of_content_value';
$handler->display->display_options['filters']['field_action_scope_of_content_value']['expose']['remember'] = TRUE;
$handler->display->display_options['filters']['field_action_scope_of_content_value']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  8 => 0,
  10 => 0,
  11 => 0,
  4 => 0,
  14 => 0,
  15 => 0,
  3 => 0,
  9 => 0,
  5 => 0,
  7 => 0,
  12 => 0,
  6 => 0,
  17 => 0,
);
/* Filter criterion: Contenu: Attached Regional Profiles (field_attached_regional_profiles) */
$handler->display->display_options['filters']['field_attached_regional_profiles_value']['id'] = 'field_attached_regional_profiles_value';
$handler->display->display_options['filters']['field_attached_regional_profiles_value']['table'] = 'field_data_field_attached_regional_profiles';
$handler->display->display_options['filters']['field_attached_regional_profiles_value']['field'] = 'field_attached_regional_profiles_value';
$handler->display->display_options['filters']['field_attached_regional_profiles_value']['relationship'] = 'nid';
$handler->display->display_options['filters']['field_attached_regional_profiles_value']['exposed'] = TRUE;
$handler->display->display_options['filters']['field_attached_regional_profiles_value']['expose']['operator_id'] = 'field_attached_regional_profiles_value_op';
$handler->display->display_options['filters']['field_attached_regional_profiles_value']['expose']['label'] = 'Profils régionaux attachés';
$handler->display->display_options['filters']['field_attached_regional_profiles_value']['expose']['operator'] = 'field_attached_regional_profiles_value_op';
$handler->display->display_options['filters']['field_attached_regional_profiles_value']['expose']['identifier'] = 'field_attached_regional_profiles_value';
$handler->display->display_options['filters']['field_attached_regional_profiles_value']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  8 => 0,
  10 => 0,
  11 => 0,
  4 => 0,
  14 => 0,
  15 => 0,
  3 => 0,
  9 => 0,
  5 => 0,
  7 => 0,
  12 => 0,
  6 => 0,
  17 => 0,
);
$handler->display->display_options['path'] = 'admin/workbench/needs-review';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Needs review';
$handler->display->display_options['menu']['weight'] = '99';
$translatables['workbench_moderation'] = array(
  t('Defaults'),
  t('Content I\'ve edited'),
  t('view all'),
  t('Appliquer'),
  t('Réinitialiser'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Items per page'),
  t('- All -'),
  t('Offset'),
  t('« premier'),
  t('‹ précédent'),
  t('suivant ›'),
  t('dernier »'),
  t('You haven\'t created or edited any content.'),
  t('Nœud'),
  t('revision user'),
  t('author'),
  t('nodes'),
  t('Nid'),
  t('Log message'),
  t('Moderation history link'),
  t('Moderation state'),
  t('<div>[state]</div><div>[workbench_moderation_history_link]</div>'),
  t('Set moderation state'),
  t('Titre'),
  t('Périmètre de diffusion'),
  t('Type'),
  t('Revised by'),
  t('Last updated'),
  t('Edit link'),
  t('Title'),
  t('State'),
  t('Needs review page'),
  t('Needs review'),
  t('plus'),
  t('This list displays content in the "Needs review" state that you can moderate. Currently there is no such content.'),
  t('Profils régionaux attachés'),
  t('Edit'),
  t('<img src = "/sites/all/themes/im/css/images/edit-Pen.png" />'),
  t('Workbench Moderation: State'),
  t('Scope of Content'),
);

