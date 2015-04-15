<?php
/**
 * @file
 * im_feature_agenda.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function im_feature_agenda_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'agenda_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Agenda list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'agenda day';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'input_required';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Appliquer';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Réinitialiser';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'full_html';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Champ: Contenu: Titre */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Contenu: Type */
  $handler->display->display_options['sorts']['type']['id'] = 'type';
  $handler->display->display_options['sorts']['type']['table'] = 'node';
  $handler->display->display_options['sorts']['type']['field'] = 'type';
  $handler->display->display_options['sorts']['type']['order'] = 'DESC';
  $handler->display->display_options['sorts']['type']['expose']['label'] = 'Type';
  /* Sort criterion: Contenu: Info (field_agenda_info) */
  $handler->display->display_options['sorts']['field_agenda_info_value']['id'] = 'field_agenda_info_value';
  $handler->display->display_options['sorts']['field_agenda_info_value']['table'] = 'field_data_field_agenda_info';
  $handler->display->display_options['sorts']['field_agenda_info_value']['field'] = 'field_agenda_info_value';
  $handler->display->display_options['sorts']['field_agenda_info_value']['order'] = 'DESC';
  /* Sort criterion: Contenu: Department (field_agenda_department) */
  $handler->display->display_options['sorts']['field_agenda_department_tid']['id'] = 'field_agenda_department_tid';
  $handler->display->display_options['sorts']['field_agenda_department_tid']['table'] = 'field_data_field_agenda_department';
  $handler->display->display_options['sorts']['field_agenda_department_tid']['field'] = 'field_agenda_department_tid';
  /* Contextual filter: Contenu: Agenda date (field_agenda_date) */
  $handler->display->display_options['arguments']['field_agenda_date_value']['id'] = 'field_agenda_date_value';
  $handler->display->display_options['arguments']['field_agenda_date_value']['table'] = 'field_data_field_agenda_date';
  $handler->display->display_options['arguments']['field_agenda_date_value']['field'] = 'field_agenda_date_value';
  $handler->display->display_options['arguments']['field_agenda_date_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_agenda_date_value']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['field_agenda_date_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_agenda_date_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_agenda_date_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_agenda_date_value']['granularity'] = 'week';
  /* Contextual filter: Contenu: Agenda Store (field_agenda_store) */
  $handler->display->display_options['arguments']['field_agenda_store_value']['id'] = 'field_agenda_store_value';
  $handler->display->display_options['arguments']['field_agenda_store_value']['table'] = 'field_data_field_agenda_store';
  $handler->display->display_options['arguments']['field_agenda_store_value']['field'] = 'field_agenda_store_value';
  $handler->display->display_options['arguments']['field_agenda_store_value']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['field_agenda_store_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_agenda_store_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_agenda_store_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_agenda_store_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_agenda_store_value']['limit'] = '0';
  /* Contextual filter: Contenu: Department (field_agenda_department) */
  $handler->display->display_options['arguments']['field_agenda_department_tid']['id'] = 'field_agenda_department_tid';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['table'] = 'field_data_field_agenda_department';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['field'] = 'field_agenda_department_tid';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['summary']['format'] = 'default_summary';
  /* Filter criterion: Contenu: Publié  */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Contenu: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'action' => 'action',
    'alert' => 'alert',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Contenu: Publication From Date (field_publication_from_date) */
  $handler->display->display_options['filters']['field_publication_from_date_value']['id'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['table'] = 'field_data_field_publication_from_date';
  $handler->display->display_options['filters']['field_publication_from_date_value']['field'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['operator'] = '<=';
  $handler->display->display_options['filters']['field_publication_from_date_value']['default_date'] = 'now';
  /* Filter criterion: Contenu: Publication To Date (field_publication_to_date) */
  $handler->display->display_options['filters']['field_publication_to_date_value']['id'] = 'field_publication_to_date_value';
  $handler->display->display_options['filters']['field_publication_to_date_value']['table'] = 'field_data_field_publication_to_date';
  $handler->display->display_options['filters']['field_publication_to_date_value']['field'] = 'field_publication_to_date_value';
  $handler->display->display_options['filters']['field_publication_to_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_publication_to_date_value']['default_date'] = 'now';

  /* Display: Agenda Home page */
  $handler = $view->new_display('block', 'Agenda Home page', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Agenda list';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Champ: Contenu: Agenda date */
  $handler->display->display_options['fields']['field_agenda_date']['id'] = 'field_agenda_date';
  $handler->display->display_options['fields']['field_agenda_date']['table'] = 'field_data_field_agenda_date';
  $handler->display->display_options['fields']['field_agenda_date']['field'] = 'field_agenda_date';
  $handler->display->display_options['fields']['field_agenda_date']['label'] = 'Date agenda ';
  $handler->display->display_options['fields']['field_agenda_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_agenda_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Champ: Contenu: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Champ: Contenu: Titre */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Contenu: Agenda date (field_agenda_date) */
  $handler->display->display_options['arguments']['field_agenda_date_value']['id'] = 'field_agenda_date_value';
  $handler->display->display_options['arguments']['field_agenda_date_value']['table'] = 'field_data_field_agenda_date';
  $handler->display->display_options['arguments']['field_agenda_date_value']['field'] = 'field_agenda_date_value';
  $handler->display->display_options['arguments']['field_agenda_date_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_agenda_date_value']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['field_agenda_date_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_agenda_date_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_agenda_date_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_agenda_date_value']['granularity'] = 'week';
  /* Contextual filter: Contenu: Agenda Store (field_agenda_store) */
  $handler->display->display_options['arguments']['field_agenda_store_value']['id'] = 'field_agenda_store_value';
  $handler->display->display_options['arguments']['field_agenda_store_value']['table'] = 'field_data_field_agenda_store';
  $handler->display->display_options['arguments']['field_agenda_store_value']['field'] = 'field_agenda_store_value';
  $handler->display->display_options['arguments']['field_agenda_store_value']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['field_agenda_store_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_agenda_store_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_agenda_store_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_agenda_store_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_agenda_store_value']['limit'] = '0';
  $handler->display->display_options['arguments']['field_agenda_store_value']['transform_dash'] = TRUE;
  /* Contextual filter: Contenu: Department (field_agenda_department) */
  $handler->display->display_options['arguments']['field_agenda_department_tid']['id'] = 'field_agenda_department_tid';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['table'] = 'field_data_field_agenda_department';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['field'] = 'field_agenda_department_tid';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Contenu: Publié  */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Contenu: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'action' => 'action',
    'alert' => 'alert',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Contenu: Publication From Date (field_publication_from_date) */
  $handler->display->display_options['filters']['field_publication_from_date_value']['id'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['table'] = 'field_data_field_publication_from_date';
  $handler->display->display_options['filters']['field_publication_from_date_value']['field'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['operator'] = '<=';
  $handler->display->display_options['filters']['field_publication_from_date_value']['default_date'] = 'now';
  /* Filter criterion: Contenu: Publication To Date (field_publication_to_date) */
  $handler->display->display_options['filters']['field_publication_to_date_value']['id'] = 'field_publication_to_date_value';
  $handler->display->display_options['filters']['field_publication_to_date_value']['table'] = 'field_data_field_publication_to_date';
  $handler->display->display_options['filters']['field_publication_to_date_value']['field'] = 'field_publication_to_date_value';
  $handler->display->display_options['filters']['field_publication_to_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_publication_to_date_value']['default_date'] = 'now';

  /* Display: Agenda For day */
  $handler = $view->new_display('block', 'Agenda For day', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Agenda list';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_agenda_info',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
    1 => array(
      'field' => 'type',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
    2 => array(
      'field' => 'field_agenda_department',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
    3 => array(
      'field' => 'nid',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Champ: Contenu: Agenda date */
  $handler->display->display_options['fields']['field_agenda_date']['id'] = 'field_agenda_date';
  $handler->display->display_options['fields']['field_agenda_date']['table'] = 'field_data_field_agenda_date';
  $handler->display->display_options['fields']['field_agenda_date']['field'] = 'field_agenda_date';
  $handler->display->display_options['fields']['field_agenda_date']['label'] = '';
  $handler->display->display_options['fields']['field_agenda_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_agenda_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_agenda_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Champ: Contenu: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Champ: Contenu: Titre */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Champ: Contenu: Rendered Nœud */
  $handler->display->display_options['fields']['rendered_entity']['id'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['rendered_entity']['field'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['label'] = '';
  $handler->display->display_options['fields']['rendered_entity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rendered_entity']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['display'] = 'view';
  $handler->display->display_options['fields']['rendered_entity']['view_mode'] = 'im_agenda_day';
  $handler->display->display_options['fields']['rendered_entity']['bypass_access'] = 0;
  /* Champ: Contenu: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  /* Champ: Contenu: Info */
  $handler->display->display_options['fields']['field_agenda_info']['id'] = 'field_agenda_info';
  $handler->display->display_options['fields']['field_agenda_info']['table'] = 'field_data_field_agenda_info';
  $handler->display->display_options['fields']['field_agenda_info']['field'] = 'field_agenda_info';
  $handler->display->display_options['fields']['field_agenda_info']['label'] = '';
  $handler->display->display_options['fields']['field_agenda_info']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_agenda_info']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_agenda_info']['delta_offset'] = '0';
  /* Champ: Contenu: Department */
  $handler->display->display_options['fields']['field_agenda_department']['id'] = 'field_agenda_department';
  $handler->display->display_options['fields']['field_agenda_department']['table'] = 'field_data_field_agenda_department';
  $handler->display->display_options['fields']['field_agenda_department']['field'] = 'field_agenda_department';
  $handler->display->display_options['fields']['field_agenda_department']['label'] = '';
  $handler->display->display_options['fields']['field_agenda_department']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_agenda_department']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_agenda_department']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_agenda_department']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_agenda_department']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_agenda_department']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Contenu: Department (field_agenda_department) */
  $handler->display->display_options['sorts']['field_agenda_department_tid']['id'] = 'field_agenda_department_tid';
  $handler->display->display_options['sorts']['field_agenda_department_tid']['table'] = 'field_data_field_agenda_department';
  $handler->display->display_options['sorts']['field_agenda_department_tid']['field'] = 'field_agenda_department_tid';
  /* Sort criterion: Contenu: Type */
  $handler->display->display_options['sorts']['type']['id'] = 'type';
  $handler->display->display_options['sorts']['type']['table'] = 'node';
  $handler->display->display_options['sorts']['type']['field'] = 'type';
  $handler->display->display_options['sorts']['type']['order'] = 'DESC';
  $handler->display->display_options['sorts']['type']['expose']['label'] = 'Type';
  /* Sort criterion: Contenu: Info (field_agenda_info) */
  $handler->display->display_options['sorts']['field_agenda_info_value']['id'] = 'field_agenda_info_value';
  $handler->display->display_options['sorts']['field_agenda_info_value']['table'] = 'field_data_field_agenda_info';
  $handler->display->display_options['sorts']['field_agenda_info_value']['field'] = 'field_agenda_info_value';
  $handler->display->display_options['sorts']['field_agenda_info_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Contenu: Agenda date (field_agenda_date) */
  $handler->display->display_options['arguments']['field_agenda_date_value']['id'] = 'field_agenda_date_value';
  $handler->display->display_options['arguments']['field_agenda_date_value']['table'] = 'field_data_field_agenda_date';
  $handler->display->display_options['arguments']['field_agenda_date_value']['field'] = 'field_agenda_date_value';
  $handler->display->display_options['arguments']['field_agenda_date_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_agenda_date_value']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['field_agenda_date_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_agenda_date_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_agenda_date_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_agenda_date_value']['granularity'] = 'week';
  /* Contextual filter: Contenu: Agenda Store (field_agenda_store) */
  $handler->display->display_options['arguments']['field_agenda_store_value']['id'] = 'field_agenda_store_value';
  $handler->display->display_options['arguments']['field_agenda_store_value']['table'] = 'field_data_field_agenda_store';
  $handler->display->display_options['arguments']['field_agenda_store_value']['field'] = 'field_agenda_store_value';
  $handler->display->display_options['arguments']['field_agenda_store_value']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['field_agenda_store_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_agenda_store_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_agenda_store_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_agenda_store_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_agenda_store_value']['limit'] = '0';
  $handler->display->display_options['arguments']['field_agenda_store_value']['transform_dash'] = TRUE;
  /* Contextual filter: Contenu: Department (field_agenda_department) */
  $handler->display->display_options['arguments']['field_agenda_department_tid']['id'] = 'field_agenda_department_tid';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['table'] = 'field_data_field_agenda_department';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['field'] = 'field_agenda_department_tid';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_agenda_department_tid']['break_phrase'] = TRUE;
  $handler->display->display_options['block_description'] = 'Agenda for the day';
  $translatables['agenda_list'] = array(
    t('Master'),
    t('agenda day'),
    t('plus'),
    t('Appliquer'),
    t('Réinitialiser'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Select any filter and click on Apply to see results'),
    t('Type'),
    t('Tout'),
    t('Agenda Home page'),
    t('Agenda list'),
    t('Date agenda '),
    t('Nid'),
    t('Agenda For day'),
    t('Agenda for the day'),
  );
  $export['agenda_list'] = $view;

  $view = new view();
  $view->name = 'news_benchmark';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'News Benchmark';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'input_required';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Appliquer';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Réinitialiser';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'full_html';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'type',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Champ: Contenu: Titre */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Champ: Contenu: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  /* Champ: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Actu Market';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'agenda/news/!1/!2/!3';
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Contextual filter: Contenu: Agenda date (field_agenda_date) */
  $handler->display->display_options['arguments']['field_agenda_date_value']['id'] = 'field_agenda_date_value';
  $handler->display->display_options['arguments']['field_agenda_date_value']['table'] = 'field_data_field_agenda_date';
  $handler->display->display_options['arguments']['field_agenda_date_value']['field'] = 'field_agenda_date_value';
  $handler->display->display_options['arguments']['field_agenda_date_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_agenda_date_value']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['field_agenda_date_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_agenda_date_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_agenda_date_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_agenda_date_value']['granularity'] = 'week';
  /* Contextual filter: Contenu: Agenda Store (field_agenda_store) */
  $handler->display->display_options['arguments']['field_agenda_store_value']['id'] = 'field_agenda_store_value';
  $handler->display->display_options['arguments']['field_agenda_store_value']['table'] = 'field_data_field_agenda_store';
  $handler->display->display_options['arguments']['field_agenda_store_value']['field'] = 'field_agenda_store_value';
  $handler->display->display_options['arguments']['field_agenda_store_value']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['field_agenda_store_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_agenda_store_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_agenda_store_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_agenda_store_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_agenda_store_value']['limit'] = '0';
  /* Filter criterion: Contenu: Publié  */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Contenu: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'news' => 'news',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Contenu: Publication From Date (field_publication_from_date) */
  $handler->display->display_options['filters']['field_publication_from_date_value']['id'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['table'] = 'field_data_field_publication_from_date';
  $handler->display->display_options['filters']['field_publication_from_date_value']['field'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['operator'] = '<=';
  $handler->display->display_options['filters']['field_publication_from_date_value']['default_date'] = 'now';
  /* Filter criterion: Contenu: Publication To Date (field_publication_to_date) */
  $handler->display->display_options['filters']['field_publication_to_date_value']['id'] = 'field_publication_to_date_value';
  $handler->display->display_options['filters']['field_publication_to_date_value']['table'] = 'field_data_field_publication_to_date';
  $handler->display->display_options['filters']['field_publication_to_date_value']['field'] = 'field_publication_to_date_value';
  $handler->display->display_options['filters']['field_publication_to_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_publication_to_date_value']['default_date'] = 'now';

  /* Display: News Page */
  $handler = $view->new_display('page', 'News Page', 'page_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['view_mode'] = 'full';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Champ: Contenu: Titre */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Champ: Contenu: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  /* Champ: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Actu Market';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'agenda/news/!1/!2/!3';
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'agenda/news/%/%/%';

  /* Display: News link */
  $handler = $view->new_display('block', 'News link', 'block_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Champ: Contenu: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Champ: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Actu Market';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'agenda-day/!1/!2/!3';
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['nothing']['element_wrapper_class'] = 'agenda-news-right';
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Contenu: Publié  */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Contenu: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'news' => 'news',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Contenu: Publication From Date (field_publication_from_date) */
  $handler->display->display_options['filters']['field_publication_from_date_value']['id'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['table'] = 'field_data_field_publication_from_date';
  $handler->display->display_options['filters']['field_publication_from_date_value']['field'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['operator'] = '<=';
  $handler->display->display_options['filters']['field_publication_from_date_value']['default_date'] = 'now';
  /* Filter criterion: Contenu: Publication To Date (field_publication_to_date) */
  $handler->display->display_options['filters']['field_publication_to_date_value']['id'] = 'field_publication_to_date_value';
  $handler->display->display_options['filters']['field_publication_to_date_value']['table'] = 'field_data_field_publication_to_date';
  $handler->display->display_options['filters']['field_publication_to_date_value']['field'] = 'field_publication_to_date_value';
  $handler->display->display_options['filters']['field_publication_to_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_publication_to_date_value']['default_date'] = 'now';

  /* Display: News and Benchmark */
  $handler = $view->new_display('block', 'News and Benchmark', 'block_2');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Champ: Contenu: Titre */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Champ: Contenu: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Champ: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Actu Market';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'agenda/news/!1/!2/!3';
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Champ: Contenu: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '100';
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Champ: Contenu: Attachments (field_agenda_attachments:delta) */
  $handler->display->display_options['fields']['delta']['id'] = 'delta';
  $handler->display->display_options['fields']['delta']['table'] = 'field_data_field_agenda_attachments';
  $handler->display->display_options['fields']['delta']['field'] = 'delta';
  $handler->display->display_options['fields']['delta']['label'] = '';
  $handler->display->display_options['fields']['delta']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['delta']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['delta']['hide_alter_empty'] = FALSE;
  /* Champ: Contenu: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Contenu: Type */
  $handler->display->display_options['sorts']['type']['id'] = 'type';
  $handler->display->display_options['sorts']['type']['table'] = 'node';
  $handler->display->display_options['sorts']['type']['field'] = 'type';
  $handler->display->display_options['sorts']['type']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Contenu: Publié  */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Contenu: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'benchmark' => 'benchmark',
    'news' => 'news',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Contenu: Publication From Date (field_publication_from_date) */
  $handler->display->display_options['filters']['field_publication_from_date_value']['id'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['table'] = 'field_data_field_publication_from_date';
  $handler->display->display_options['filters']['field_publication_from_date_value']['field'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['operator'] = '<=';
  $handler->display->display_options['filters']['field_publication_from_date_value']['default_date'] = 'now';
  /* Filter criterion: Contenu: Publication To Date (field_publication_to_date) */
  $handler->display->display_options['filters']['field_publication_to_date_value']['id'] = 'field_publication_to_date_value';
  $handler->display->display_options['filters']['field_publication_to_date_value']['table'] = 'field_data_field_publication_to_date';
  $handler->display->display_options['filters']['field_publication_to_date_value']['field'] = 'field_publication_to_date_value';
  $handler->display->display_options['filters']['field_publication_to_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_publication_to_date_value']['default_date'] = 'now';

  /* Display: Benchmark link */
  $handler = $view->new_display('block', 'Benchmark link', 'block_3');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Champ: Contenu: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Champ: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Benchmark';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'agenda-day/!1/!2/!3';
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['nothing']['element_wrapper_class'] = 'agenda-news-right';
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Contenu: Publié  */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Contenu: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'benchmark' => 'benchmark',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Contenu: Publication From Date (field_publication_from_date) */
  $handler->display->display_options['filters']['field_publication_from_date_value']['id'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['table'] = 'field_data_field_publication_from_date';
  $handler->display->display_options['filters']['field_publication_from_date_value']['field'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['operator'] = '<=';
  $handler->display->display_options['filters']['field_publication_from_date_value']['default_date'] = 'now';
  /* Filter criterion: Contenu: Publication To Date (field_publication_to_date) */
  $handler->display->display_options['filters']['field_publication_to_date_value']['id'] = 'field_publication_to_date_value';
  $handler->display->display_options['filters']['field_publication_to_date_value']['table'] = 'field_data_field_publication_to_date';
  $handler->display->display_options['filters']['field_publication_to_date_value']['field'] = 'field_publication_to_date_value';
  $handler->display->display_options['filters']['field_publication_to_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_publication_to_date_value']['default_date'] = 'now';
  $translatables['news_benchmark'] = array(
    t('Master'),
    t('plus'),
    t('Appliquer'),
    t('Réinitialiser'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Select any filter and click on Apply to see results'),
    t('Nid'),
    t('Actu Market'),
    t('Tout'),
    t('News Page'),
    t('News link'),
    t('News and Benchmark'),
    t('.'),
    t(','),
    t('Benchmark link'),
    t('Benchmark'),
  );
  $export['news_benchmark'] = $view;

  return $export;
}
