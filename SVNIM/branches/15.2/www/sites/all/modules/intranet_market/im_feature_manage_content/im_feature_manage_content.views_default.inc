<?php
/**
 * @file
 * im_feature_manage_content.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function im_feature_manage_content_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'manage_applications';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Manage Applications';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage Applications';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create application content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<a class="create-function-link" href="/node/add/application"></a>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  /* Field: Content: Category */
  $handler->display->display_options['fields']['field_app_category']['id'] = 'field_app_category';
  $handler->display->display_options['fields']['field_app_category']['table'] = 'field_data_field_app_category';
  $handler->display->display_options['fields']['field_app_category']['field'] = 'field_app_category';
  $handler->display->display_options['fields']['field_app_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_app_category']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['nl2br'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '150';
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['html'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: Application Logo */
  $handler->display->display_options['fields']['field_app_icon']['id'] = 'field_app_icon';
  $handler->display->display_options['fields']['field_app_icon']['table'] = 'field_data_field_app_icon';
  $handler->display->display_options['fields']['field_app_icon']['field'] = 'field_app_icon';
  $handler->display->display_options['fields']['field_app_icon']['label'] = 'Logo';
  $handler->display->display_options['fields']['field_app_icon']['alter']['text'] = '<img src = "/sites/all/themes/im/css/images/attachment.png" />';
  $handler->display->display_options['fields']['field_app_icon']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_app_icon']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_app_icon']['settings'] = array(
    'image_style' => 'application_icon',
    'image_link' => 'file',
  );
  /* Field: Content: Link to the documentation */
  $handler->display->display_options['fields']['field_app_document']['id'] = 'field_app_document';
  $handler->display->display_options['fields']['field_app_document']['table'] = 'field_data_field_app_document';
  $handler->display->display_options['fields']['field_app_document']['field'] = 'field_app_document';
  $handler->display->display_options['fields']['field_app_document']['element_label_colon'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '<img src = "/sites/all/themes/im/css/images/edit-Pen.png" />';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'application' => 'application',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Category (field_app_category) */
  $handler->display->display_options['filters']['field_app_category_tid']['id'] = 'field_app_category_tid';
  $handler->display->display_options['filters']['field_app_category_tid']['table'] = 'field_data_field_app_category';
  $handler->display->display_options['filters']['field_app_category_tid']['field'] = 'field_app_category_tid';
  $handler->display->display_options['filters']['field_app_category_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_app_category_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_app_category_tid']['expose']['operator_id'] = 'field_app_category_tid_op';
  $handler->display->display_options['filters']['field_app_category_tid']['expose']['label'] = 'Catégorie';
  $handler->display->display_options['filters']['field_app_category_tid']['expose']['operator'] = 'field_app_category_tid_op';
  $handler->display->display_options['filters']['field_app_category_tid']['expose']['identifier'] = 'field_app_category_tid';
  $handler->display->display_options['filters']['field_app_category_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    12 => 0,
    4 => 0,
    14 => 0,
    15 => 0,
    16 => 0,
    3 => 0,
    10 => 0,
    5 => 0,
    6 => 0,
    13 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['field_app_category_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_app_category_tid']['vocabulary'] = 'application_category';
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    8 => 0,
    10 => 0,
    11 => 0,
    4 => 0,
    13 => 0,
    14 => 0,
    15 => 0,
    3 => 0,
    9 => 0,
    5 => 0,
    7 => 0,
    12 => 0,
    6 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<a class="create-function-link" href="/node/add/application">créer une application</a>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['path'] = 'admin/im/manage/applications';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage Applications';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['manage_applications'] = array(
    t('Master'),
    t('Manage Applications'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('<a class="create-function-link" href="/node/add/application"></a>'),
    t('Category'),
    t('Title'),
    t('Description'),
    t('Logo'),
    t('<img src = "/sites/all/themes/im/css/images/attachment.png" />'),
    t('Link to the documentation'),
    t('<img src = "/sites/all/themes/im/css/images/edit-Pen.png" />'),
    t('Catégorie'),
    t('Page'),
    t('<a class="create-function-link" href="/node/add/application">créer une application</a>'),
  );
  $export['manage_applications'] = $view;

  $view = new view();
  $view->name = 'manage_messages';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Manage Messages';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage Messages';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create message content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<a class="create-function-link" href="/node/add/message">Créer un message</a>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_description']['id'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['table'] = 'field_data_field_description';
  $handler->display->display_options['fields']['field_description']['field'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_description']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['field_description']['alter']['nl2br'] = TRUE;
  $handler->display->display_options['fields']['field_description']['alter']['max_length'] = '150';
  $handler->display->display_options['fields']['field_description']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['field_description']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_description']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_description']['alter']['preserve_tags'] = '<p> <br>';
  $handler->display->display_options['fields']['field_description']['alter']['html'] = TRUE;
  $handler->display->display_options['fields']['field_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_description']['type'] = 'text_plain';
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_description_accueil']['id'] = 'field_description_accueil';
  $handler->display->display_options['fields']['field_description_accueil']['table'] = 'field_data_field_description_accueil';
  $handler->display->display_options['fields']['field_description_accueil']['field'] = 'field_description_accueil';
  $handler->display->display_options['fields']['field_description_accueil']['empty'] = '[field_description]';
  /* Field: Content: Type de message */
  $handler->display->display_options['fields']['field_message_type']['id'] = 'field_message_type';
  $handler->display->display_options['fields']['field_message_type']['table'] = 'field_data_field_message_type';
  $handler->display->display_options['fields']['field_message_type']['field'] = 'field_message_type';
  $handler->display->display_options['fields']['field_message_type']['empty'] = 'not defined';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_message_image']['id'] = 'field_message_image';
  $handler->display->display_options['fields']['field_message_image']['table'] = 'field_data_field_message_image';
  $handler->display->display_options['fields']['field_message_image']['field'] = 'field_message_image';
  $handler->display->display_options['fields']['field_message_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_message_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_message_image']['settings'] = array(
    'image_style' => 'im_message_image',
    'image_link' => 'file',
  );
  /* Field: Content: Publication From Date */
  $handler->display->display_options['fields']['field_publication_from_date']['id'] = 'field_publication_from_date';
  $handler->display->display_options['fields']['field_publication_from_date']['table'] = 'field_data_field_publication_from_date';
  $handler->display->display_options['fields']['field_publication_from_date']['field'] = 'field_publication_from_date';
  $handler->display->display_options['fields']['field_publication_from_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_publication_from_date']['settings'] = array(
    'format_type' => 'im_date_format',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Publication To Date */
  $handler->display->display_options['fields']['field_publication_to_date']['id'] = 'field_publication_to_date';
  $handler->display->display_options['fields']['field_publication_to_date']['table'] = 'field_data_field_publication_to_date';
  $handler->display->display_options['fields']['field_publication_to_date']['field'] = 'field_publication_to_date';
  $handler->display->display_options['fields']['field_publication_to_date']['label'] = 'Published';
  $handler->display->display_options['fields']['field_publication_to_date']['settings'] = array(
    'format_type' => 'im_date_format',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'message' => 'message',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Publication From Date (field_publication_from_date) */
  $handler->display->display_options['filters']['field_publication_from_date_value']['id'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['table'] = 'field_data_field_publication_from_date';
  $handler->display->display_options['filters']['field_publication_from_date_value']['field'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['group'] = 1;
  $handler->display->display_options['filters']['field_publication_from_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_publication_from_date_value']['expose']['operator_id'] = 'field_publication_from_date_value_op';
  $handler->display->display_options['filters']['field_publication_from_date_value']['expose']['label'] = 'Publication From Date';
  $handler->display->display_options['filters']['field_publication_from_date_value']['expose']['operator'] = 'field_publication_from_date_value_op';
  $handler->display->display_options['filters']['field_publication_from_date_value']['expose']['identifier'] = 'field_publication_from_date_value';
  $handler->display->display_options['filters']['field_publication_from_date_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    12 => 0,
    4 => 0,
    14 => 0,
    15 => 0,
    16 => 0,
    3 => 0,
    10 => 0,
    5 => 0,
    6 => 0,
    13 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['field_publication_from_date_value']['form_type'] = 'date_popup';
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
    8 => 0,
    10 => 0,
    11 => 0,
    4 => 0,
    13 => 0,
    14 => 0,
    15 => 0,
    3 => 0,
    9 => 0,
    5 => 0,
    7 => 0,
    12 => 0,
    6 => 0,
  );
  /* Filter criterion: Content: Type de message (field_message_type) */
  $handler->display->display_options['filters']['field_message_type_value']['id'] = 'field_message_type_value';
  $handler->display->display_options['filters']['field_message_type_value']['table'] = 'field_data_field_message_type';
  $handler->display->display_options['filters']['field_message_type_value']['field'] = 'field_message_type_value';
  $handler->display->display_options['filters']['field_message_type_value']['value'] = array(
    'Widget' => 'Widget',
    'Accueil' => 'Accueil',
  );
  $handler->display->display_options['filters']['field_message_type_value']['group'] = 1;
  $handler->display->display_options['filters']['field_message_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_message_type_value']['expose']['operator_id'] = 'field_message_type_value_op';
  $handler->display->display_options['filters']['field_message_type_value']['expose']['label'] = 'type de message';
  $handler->display->display_options['filters']['field_message_type_value']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['field_message_type_value']['expose']['operator'] = 'field_message_type_value_op';
  $handler->display->display_options['filters']['field_message_type_value']['expose']['identifier'] = 'field_message_type_value';
  $handler->display->display_options['filters']['field_message_type_value']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_message_type_value']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_message_type_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_message_type_value']['group_info']['label'] = 'Type de message ';
  $handler->display->display_options['filters']['field_message_type_value']['group_info']['identifier'] = 'field_message_type_value';
  $handler->display->display_options['filters']['field_message_type_value']['group_info']['widget'] = 'radios';
  $handler->display->display_options['filters']['field_message_type_value']['group_info']['default_group'] = '1';
  $handler->display->display_options['filters']['field_message_type_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'All',
      'operator' => 'or',
      'value' => array(
        'Widget' => 'Widget',
        'Accueil' => 'Accueil',
      ),
    ),
    2 => array(
      'title' => 'Widget',
      'operator' => 'or',
      'value' => array(
        'Widget' => 'Widget',
      ),
    ),
    3 => array(
      'title' => 'Accueil',
      'operator' => 'or',
      'value' => array(
        'Accueil' => 'Accueil',
      ),
    ),
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/im/manage/messages';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage Messages';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['manage_messages'] = array(
    t('Master'),
    t('Manage Messages'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('<a class="create-function-link" href="/node/add/message">Créer un message</a>'),
    t('Title'),
    t('Description'),
    t('[field_description]'),
    t('Type de message'),
    t('not defined'),
    t('Image'),
    t('Publication From Date'),
    t('Published'),
    t('Status'),
    t('type de message'),
    t('Type de message '),
    t('Page'),
  );
  $export['manage_messages'] = $view;

  $view = new view();
  $view->name = 'manage_operational_model';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Manage Operational Model';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage Operational Model';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_om_reference_procedure' => 'field_om_reference_procedure',
    'title' => 'title',
    'field_om_experts' => 'field_om_experts',
    'field_om_publication_period' => 'field_om_publication_period',
    'delta' => 'delta',
    'field_om_domain' => 'field_om_domain',
    'field_om_subdomain' => 'field_om_subdomain',
    'field_om_macro_activity' => 'field_om_macro_activity',
    'status' => 'status',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = 'field_om_reference_procedure';
  $handler->display->display_options['style_options']['info'] = array(
    'field_om_reference_procedure' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_om_experts' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_om_publication_period' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delta' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_om_domain' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_om_subdomain' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_om_macro_activity' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No procedure available.';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Content: Reference Procedure */
  $handler->display->display_options['fields']['field_om_reference_procedure']['id'] = 'field_om_reference_procedure';
  $handler->display->display_options['fields']['field_om_reference_procedure']['table'] = 'field_data_field_om_reference_procedure';
  $handler->display->display_options['fields']['field_om_reference_procedure']['field'] = 'field_om_reference_procedure';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Titre';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Expert Validation */
  $handler->display->display_options['fields']['field_om_experts']['id'] = 'field_om_experts';
  $handler->display->display_options['fields']['field_om_experts']['table'] = 'field_data_field_om_experts';
  $handler->display->display_options['fields']['field_om_experts']['field'] = 'field_om_experts';
  $handler->display->display_options['fields']['field_om_experts']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_om_experts']['delta_offset'] = '0';
  /* Field: Content: Validity period of Publication */
  $handler->display->display_options['fields']['field_om_publication_period']['id'] = 'field_om_publication_period';
  $handler->display->display_options['fields']['field_om_publication_period']['table'] = 'field_data_field_om_publication_period';
  $handler->display->display_options['fields']['field_om_publication_period']['field'] = 'field_om_publication_period';
  $handler->display->display_options['fields']['field_om_publication_period']['settings'] = array(
    'format_type' => 'im_date_format',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_om_location']['id'] = 'field_om_location';
  $handler->display->display_options['fields']['field_om_location']['table'] = 'field_data_field_om_location';
  $handler->display->display_options['fields']['field_om_location']['field'] = 'field_om_location';
  $handler->display->display_options['fields']['field_om_location']['label'] = 'Localisations concernées';
  $handler->display->display_options['fields']['field_om_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_om_location']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_om_location']['delta_offset'] = '0';
  /* Field: Content: Domain */
  $handler->display->display_options['fields']['field_om_domain']['id'] = 'field_om_domain';
  $handler->display->display_options['fields']['field_om_domain']['table'] = 'field_data_field_om_domain';
  $handler->display->display_options['fields']['field_om_domain']['field'] = 'field_om_domain';
  $handler->display->display_options['fields']['field_om_domain']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_om_domain']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Subdomain */
  $handler->display->display_options['fields']['field_om_subdomain']['id'] = 'field_om_subdomain';
  $handler->display->display_options['fields']['field_om_subdomain']['table'] = 'field_data_field_om_subdomain';
  $handler->display->display_options['fields']['field_om_subdomain']['field'] = 'field_om_subdomain';
  $handler->display->display_options['fields']['field_om_subdomain']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Macro Activity */
  $handler->display->display_options['fields']['field_om_macro_activity']['id'] = 'field_om_macro_activity';
  $handler->display->display_options['fields']['field_om_macro_activity']['table'] = 'field_data_field_om_macro_activity';
  $handler->display->display_options['fields']['field_om_macro_activity']['field'] = 'field_om_macro_activity';
  $handler->display->display_options['fields']['field_om_macro_activity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_om_macro_activity']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Version# */
  $handler->display->display_options['fields']['field_om_version']['id'] = 'field_om_version';
  $handler->display->display_options['fields']['field_om_version']['table'] = 'field_data_field_om_version';
  $handler->display->display_options['fields']['field_om_version']['field'] = 'field_om_version';
  /* Field: Content: node_archive */
  $handler->display->display_options['fields']['field_node_archive']['id'] = 'field_node_archive';
  $handler->display->display_options['fields']['field_node_archive']['table'] = 'field_data_field_node_archive';
  $handler->display->display_options['fields']['field_node_archive']['field'] = 'field_node_archive';
  $handler->display->display_options['fields']['field_node_archive']['exclude'] = TRUE;
  /* Field: Workbench Moderation: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['label'] = 'Statut';
  $handler->display->display_options['fields']['state']['machine_name'] = 0;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '<img src = "/sites/all/themes/im/css/images/edit-Pen.png" />';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null_1']['id'] = 'null_1';
  $handler->display->display_options['arguments']['null_1']['table'] = 'views';
  $handler->display->display_options['arguments']['null_1']['field'] = 'null';
  $handler->display->display_options['arguments']['null_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null_1']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Location (field_om_location) */
  $handler->display->display_options['arguments']['field_om_location_tid']['id'] = 'field_om_location_tid';
  $handler->display->display_options['arguments']['field_om_location_tid']['table'] = 'field_data_field_om_location';
  $handler->display->display_options['arguments']['field_om_location_tid']['field'] = 'field_om_location_tid';
  $handler->display->display_options['arguments']['field_om_location_tid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_om_location_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_om_location_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_om_location_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_om_location_tid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'operational_model' => 'operational_model',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Location (field_om_location) */
  $handler->display->display_options['filters']['field_om_location_tid']['id'] = 'field_om_location_tid';
  $handler->display->display_options['filters']['field_om_location_tid']['table'] = 'field_data_field_om_location';
  $handler->display->display_options['filters']['field_om_location_tid']['field'] = 'field_om_location_tid';
  $handler->display->display_options['filters']['field_om_location_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_om_location_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_om_location_tid']['expose']['operator_id'] = 'field_om_location_tid_op';
  $handler->display->display_options['filters']['field_om_location_tid']['expose']['label'] = 'Localisations concernées';
  $handler->display->display_options['filters']['field_om_location_tid']['expose']['operator'] = 'field_om_location_tid_op';
  $handler->display->display_options['filters']['field_om_location_tid']['expose']['identifier'] = 'field_om_location_tid';
  $handler->display->display_options['filters']['field_om_location_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    12 => 0,
    4 => 0,
    14 => 0,
    15 => 0,
    16 => 0,
    3 => 0,
    10 => 0,
    5 => 0,
    6 => 0,
    13 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['field_om_location_tid']['group_info']['label'] = 'Location (field_om_location)';
  $handler->display->display_options['filters']['field_om_location_tid']['group_info']['identifier'] = 'field_om_location_tid';
  $handler->display->display_options['filters']['field_om_location_tid']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_om_location_tid']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  $handler->display->display_options['filters']['field_om_location_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_om_location_tid']['vocabulary'] = 'operational_model_location';
  $handler->display->display_options['filters']['field_om_location_tid']['hierarchy'] = 1;
  /* Filter criterion: Content: Domain (field_om_domain) */
  $handler->display->display_options['filters']['field_om_domain_tid']['id'] = 'field_om_domain_tid';
  $handler->display->display_options['filters']['field_om_domain_tid']['table'] = 'field_data_field_om_domain';
  $handler->display->display_options['filters']['field_om_domain_tid']['field'] = 'field_om_domain_tid';
  $handler->display->display_options['filters']['field_om_domain_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_om_domain_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_om_domain_tid']['expose']['operator_id'] = 'field_om_domain_tid_op';
  $handler->display->display_options['filters']['field_om_domain_tid']['expose']['label'] = 'Domain';
  $handler->display->display_options['filters']['field_om_domain_tid']['expose']['operator'] = 'field_om_domain_tid_op';
  $handler->display->display_options['filters']['field_om_domain_tid']['expose']['identifier'] = 'field_om_domain_tid';
  $handler->display->display_options['filters']['field_om_domain_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    12 => 0,
    4 => 0,
    14 => 0,
    15 => 0,
    16 => 0,
    3 => 0,
    10 => 0,
    5 => 0,
    6 => 0,
    13 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['field_om_domain_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_om_domain_tid']['vocabulary'] = 'om_domains';
  /* Filter criterion: Content: Subdomain (field_om_subdomain) */
  $handler->display->display_options['filters']['field_om_subdomain_tid']['id'] = 'field_om_subdomain_tid';
  $handler->display->display_options['filters']['field_om_subdomain_tid']['table'] = 'field_data_field_om_subdomain';
  $handler->display->display_options['filters']['field_om_subdomain_tid']['field'] = 'field_om_subdomain_tid';
  $handler->display->display_options['filters']['field_om_subdomain_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_om_subdomain_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_om_subdomain_tid']['expose']['operator_id'] = 'field_om_subdomain_tid_op';
  $handler->display->display_options['filters']['field_om_subdomain_tid']['expose']['label'] = 'Sous-domaine';
  $handler->display->display_options['filters']['field_om_subdomain_tid']['expose']['operator'] = 'field_om_subdomain_tid_op';
  $handler->display->display_options['filters']['field_om_subdomain_tid']['expose']['identifier'] = 'field_om_subdomain_tid';
  $handler->display->display_options['filters']['field_om_subdomain_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    12 => 0,
    4 => 0,
    14 => 0,
    15 => 0,
    16 => 0,
    3 => 0,
    10 => 0,
    5 => 0,
    6 => 0,
    13 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['field_om_subdomain_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_om_subdomain_tid']['vocabulary'] = 'om_domains';
  $handler->display->display_options['filters']['field_om_subdomain_tid']['hierarchy'] = 1;
  /* Filter criterion: Content: Macro Activity (field_om_macro_activity) */
  $handler->display->display_options['filters']['field_om_macro_activity_tid']['id'] = 'field_om_macro_activity_tid';
  $handler->display->display_options['filters']['field_om_macro_activity_tid']['table'] = 'field_data_field_om_macro_activity';
  $handler->display->display_options['filters']['field_om_macro_activity_tid']['field'] = 'field_om_macro_activity_tid';
  $handler->display->display_options['filters']['field_om_macro_activity_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_om_macro_activity_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_om_macro_activity_tid']['expose']['operator_id'] = 'field_om_macro_activity_tid_op';
  $handler->display->display_options['filters']['field_om_macro_activity_tid']['expose']['label'] = 'Macro-Activite';
  $handler->display->display_options['filters']['field_om_macro_activity_tid']['expose']['operator'] = 'field_om_macro_activity_tid_op';
  $handler->display->display_options['filters']['field_om_macro_activity_tid']['expose']['identifier'] = 'field_om_macro_activity_tid';
  $handler->display->display_options['filters']['field_om_macro_activity_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    12 => 0,
    4 => 0,
    14 => 0,
    15 => 0,
    16 => 0,
    3 => 0,
    10 => 0,
    5 => 0,
    6 => 0,
    13 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['field_om_macro_activity_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_om_macro_activity_tid']['vocabulary'] = 'om_domains';
  $handler->display->display_options['filters']['field_om_macro_activity_tid']['hierarchy'] = 1;
  /* Filter criterion: Content: Acteurs Concernes (field_om_actuers) */
  $handler->display->display_options['filters']['field_om_actuers_tid']['id'] = 'field_om_actuers_tid';
  $handler->display->display_options['filters']['field_om_actuers_tid']['table'] = 'field_data_field_om_actuers';
  $handler->display->display_options['filters']['field_om_actuers_tid']['field'] = 'field_om_actuers_tid';
  $handler->display->display_options['filters']['field_om_actuers_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_om_actuers_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_om_actuers_tid']['expose']['operator_id'] = 'field_om_actuers_tid_op';
  $handler->display->display_options['filters']['field_om_actuers_tid']['expose']['label'] = 'Acteurs Concernes';
  $handler->display->display_options['filters']['field_om_actuers_tid']['expose']['operator'] = 'field_om_actuers_tid_op';
  $handler->display->display_options['filters']['field_om_actuers_tid']['expose']['identifier'] = 'field_om_actuers_tid';
  $handler->display->display_options['filters']['field_om_actuers_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    12 => 0,
    4 => 0,
    14 => 0,
    15 => 0,
    16 => 0,
    3 => 0,
    10 => 0,
    5 => 0,
    6 => 0,
    13 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['field_om_actuers_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_om_actuers_tid']['vocabulary'] = 'om_roles';
  /* Filter criterion: Workbench Moderation: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['value'] = array(
    'draft' => 'draft',
    'published' => 'published',
    'needs_review' => 'needs_review',
  );
  $handler->display->display_options['filters']['state']['group'] = 1;
  $handler->display->display_options['filters']['state']['exposed'] = TRUE;
  $handler->display->display_options['filters']['state']['expose']['operator_id'] = 'state_op';
  $handler->display->display_options['filters']['state']['expose']['label'] = 'Statut';
  $handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
  $handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
  $handler->display->display_options['filters']['state']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    8 => 0,
    10 => 0,
    11 => 0,
    4 => 0,
    13 => 0,
    14 => 0,
    15 => 0,
    3 => 0,
    9 => 0,
    5 => 0,
    7 => 0,
    12 => 0,
    6 => 0,
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    8 => 0,
    10 => 0,
    11 => 0,
    4 => 0,
    13 => 0,
    14 => 0,
    15 => 0,
    3 => 0,
    9 => 0,
    5 => 0,
    7 => 0,
    12 => 0,
    6 => 0,
  );
  /* Filter criterion: Content: node_archive (field_node_archive) */
  $handler->display->display_options['filters']['field_node_archive_value']['id'] = 'field_node_archive_value';
  $handler->display->display_options['filters']['field_node_archive_value']['table'] = 'field_data_field_node_archive';
  $handler->display->display_options['filters']['field_node_archive_value']['field'] = 'field_node_archive_value';
  $handler->display->display_options['filters']['field_node_archive_value']['value'] = array(
    0 => '0',
    1 => '1',
  );
  $handler->display->display_options['filters']['field_node_archive_value']['group'] = 1;
  /* Filter criterion: Content: draft_status (field_draft_status) */
  $handler->display->display_options['filters']['field_draft_status_value']['id'] = 'field_draft_status_value';
  $handler->display->display_options['filters']['field_draft_status_value']['table'] = 'field_data_field_draft_status';
  $handler->display->display_options['filters']['field_draft_status_value']['field'] = 'field_draft_status_value';
  $handler->display->display_options['filters']['field_draft_status_value']['value'] = array(
    0 => '0',
    1 => '1',
  );
  $handler->display->display_options['filters']['field_draft_status_value']['group'] = 1;
  /* Filter criterion: Workbench Moderation: Current */
  $handler->display->display_options['filters']['current']['id'] = 'current';
  $handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['current']['field'] = 'current';
  $handler->display->display_options['filters']['current']['value'] = '1';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'edit own operational_model content';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<a class="create-function-link" href="/node/add/operational-model">Créer une procédure</a>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['path'] = 'admin/im/manage/om';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage Operational Model';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Operational Model List';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '35';
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Node count: Node id */
  $handler->display->display_options['sorts']['nid']['id'] = 'nid';
  $handler->display->display_options['sorts']['nid']['table'] = 'node_view_count';
  $handler->display->display_options['sorts']['nid']['field'] = 'nid';
  $handler->display->display_options['sorts']['nid']['group_type'] = 'count';
  $handler->display->display_options['sorts']['nid']['order'] = 'DESC';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['not'] = TRUE;
  /* Contextual filter: Content: Location (field_om_location) */
  $handler->display->display_options['arguments']['field_om_location_tid']['id'] = 'field_om_location_tid';
  $handler->display->display_options['arguments']['field_om_location_tid']['table'] = 'field_data_field_om_location';
  $handler->display->display_options['arguments']['field_om_location_tid']['field'] = 'field_om_location_tid';
  $handler->display->display_options['arguments']['field_om_location_tid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_om_location_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_om_location_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_om_location_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'operational_model' => 'operational_model',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  /* Filter criterion: Content: Validity period of Publication -  start date (field_om_publication_period) */
  $handler->display->display_options['filters']['field_om_publication_period_value']['id'] = 'field_om_publication_period_value';
  $handler->display->display_options['filters']['field_om_publication_period_value']['table'] = 'field_data_field_om_publication_period';
  $handler->display->display_options['filters']['field_om_publication_period_value']['field'] = 'field_om_publication_period_value';
  $handler->display->display_options['filters']['field_om_publication_period_value']['operator'] = '<=';
  $handler->display->display_options['filters']['field_om_publication_period_value']['group'] = 1;
  $handler->display->display_options['filters']['field_om_publication_period_value']['form_type'] = 'date_text';
  $handler->display->display_options['filters']['field_om_publication_period_value']['default_date'] = 'now';
  /* Filter criterion: Content: Validity period of Publication - end date (field_om_publication_period:value2) */
  $handler->display->display_options['filters']['field_om_publication_period_value2']['id'] = 'field_om_publication_period_value2';
  $handler->display->display_options['filters']['field_om_publication_period_value2']['table'] = 'field_data_field_om_publication_period';
  $handler->display->display_options['filters']['field_om_publication_period_value2']['field'] = 'field_om_publication_period_value2';
  $handler->display->display_options['filters']['field_om_publication_period_value2']['operator'] = '>=';
  $handler->display->display_options['filters']['field_om_publication_period_value2']['group'] = 1;
  $handler->display->display_options['filters']['field_om_publication_period_value2']['form_type'] = 'date_text';
  $handler->display->display_options['filters']['field_om_publication_period_value2']['default_date'] = 'now';
  $translatables['manage_operational_model'] = array(
    t('Master'),
    t('Manage Operational Model'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('No procedure available.'),
    t('author'),
    t('Reference Procedure'),
    t('Titre'),
    t('Expert Validation'),
    t('Validity period of Publication'),
    t('Localisations concernées'),
    t('Domain'),
    t('Subdomain'),
    t('Macro Activity'),
    t('Version#'),
    t('node_archive'),
    t('Statut'),
    t('<img src = "/sites/all/themes/im/css/images/edit-Pen.png" />'),
    t('All'),
    t('Location (field_om_location)'),
    t('Sous-domaine'),
    t('Macro-Activite'),
    t('Acteurs Concernes'),
    t('Title'),
    t('Page'),
    t('<a class="create-function-link" href="/node/add/operational-model">Créer une procédure</a>'),
    t('Block'),
    t('Operational Model List'),
  );
  $export['manage_operational_model'] = $view;

  $view = new view();
  $view->name = 'sales_plan_management';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Manage Sales plan';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage Sales plan';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_sp_type' => 'field_sp_type',
    'field_sp_operation_period' => 'field_sp_operation_period',
    'field_sp_order_period' => 'field_sp_order_period',
    'field_sp_benchmark' => 'field_sp_benchmark',
    'field_sp_catalogue' => 'field_sp_catalogue',
    'field_sp_help_control' => 'field_sp_help_control',
    'field_sp_others' => 'field_sp_others',
    'field_sp_plv' => 'field_sp_plv',
    'field_sp_visual' => 'field_sp_visual',
    'status' => 'status',
    'field_sp_regions' => 'field_sp_regions',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sp_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sp_operation_period' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sp_order_period' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sp_benchmark' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sp_catalogue' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sp_help_control' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sp_others' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sp_plv' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sp_visual' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sp_regions' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::node_assign_owner_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::node_promote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpromote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::workbench_moderation_set_state_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_by_keyword_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_sp_type']['id'] = 'field_sp_type';
  $handler->display->display_options['fields']['field_sp_type']['table'] = 'field_data_field_sp_type';
  $handler->display->display_options['fields']['field_sp_type']['field'] = 'field_sp_type';
  $handler->display->display_options['fields']['field_sp_type']['label'] = 'Region Type';
  $handler->display->display_options['fields']['field_sp_type']['element_label_colon'] = FALSE;
  /* Field: Content: Operation Period */
  $handler->display->display_options['fields']['field_sp_operation_period']['id'] = 'field_sp_operation_period';
  $handler->display->display_options['fields']['field_sp_operation_period']['table'] = 'field_data_field_sp_operation_period';
  $handler->display->display_options['fields']['field_sp_operation_period']['field'] = 'field_sp_operation_period';
  $handler->display->display_options['fields']['field_sp_operation_period']['label'] = 'Operation period date';
  $handler->display->display_options['fields']['field_sp_operation_period']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sp_operation_period']['settings'] = array(
    'format_type' => 'im_date_format',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Order Period */
  $handler->display->display_options['fields']['field_sp_order_period']['id'] = 'field_sp_order_period';
  $handler->display->display_options['fields']['field_sp_order_period']['table'] = 'field_data_field_sp_order_period';
  $handler->display->display_options['fields']['field_sp_order_period']['field'] = 'field_sp_order_period';
  $handler->display->display_options['fields']['field_sp_order_period']['label'] = 'Order period date';
  $handler->display->display_options['fields']['field_sp_order_period']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sp_order_period']['settings'] = array(
    'format_type' => 'im_date_format',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_sp_benchmark']['id'] = 'field_sp_benchmark';
  $handler->display->display_options['fields']['field_sp_benchmark']['table'] = 'field_data_field_sp_benchmark';
  $handler->display->display_options['fields']['field_sp_benchmark']['field'] = 'field_sp_benchmark';
  $handler->display->display_options['fields']['field_sp_benchmark']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_sp_benchmark']['alter']['text'] = '<img src = "/sites/all/themes/im/css/images/attachment.png" />';
  $handler->display->display_options['fields']['field_sp_benchmark']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_sp_benchmark']['alter']['path'] = '[field_sp_benchmark]';
  $handler->display->display_options['fields']['field_sp_benchmark']['element_label_colon'] = FALSE;
  /* Field: Content: Catalogue */
  $handler->display->display_options['fields']['field_sp_catalogue']['id'] = 'field_sp_catalogue';
  $handler->display->display_options['fields']['field_sp_catalogue']['table'] = 'field_data_field_sp_catalogue';
  $handler->display->display_options['fields']['field_sp_catalogue']['field'] = 'field_sp_catalogue';
  $handler->display->display_options['fields']['field_sp_catalogue']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_sp_catalogue']['alter']['text'] = '<img src = "/sites/all/themes/im/css/images/attachment.png" />';
  $handler->display->display_options['fields']['field_sp_catalogue']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_sp_catalogue']['alter']['path'] = '[field_sp_catalogue]';
  $handler->display->display_options['fields']['field_sp_catalogue']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sp_catalogue']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_sp_catalogue']['type'] = 'file_url_plain';
  $handler->display->display_options['fields']['field_sp_catalogue']['delta_offset'] = '0';
  /* Field: Content: Aides à la commande */
  $handler->display->display_options['fields']['field_sp_help_control']['id'] = 'field_sp_help_control';
  $handler->display->display_options['fields']['field_sp_help_control']['table'] = 'field_data_field_sp_help_control';
  $handler->display->display_options['fields']['field_sp_help_control']['field'] = 'field_sp_help_control';
  $handler->display->display_options['fields']['field_sp_help_control']['label'] = 'Help control';
  $handler->display->display_options['fields']['field_sp_help_control']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_sp_help_control']['alter']['text'] = '<img src = "/sites/all/themes/im/css/images/attachment.png" />';
  $handler->display->display_options['fields']['field_sp_help_control']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_sp_help_control']['alter']['path'] = '[field_sp_help_control]';
  $handler->display->display_options['fields']['field_sp_help_control']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sp_help_control']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_sp_help_control']['type'] = 'file_url_plain';
  $handler->display->display_options['fields']['field_sp_help_control']['delta_offset'] = '0';
  /* Field: Content: Autres */
  $handler->display->display_options['fields']['field_sp_others']['id'] = 'field_sp_others';
  $handler->display->display_options['fields']['field_sp_others']['table'] = 'field_data_field_sp_others';
  $handler->display->display_options['fields']['field_sp_others']['field'] = 'field_sp_others';
  $handler->display->display_options['fields']['field_sp_others']['label'] = 'Other';
  $handler->display->display_options['fields']['field_sp_others']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_sp_others']['alter']['text'] = '<img src = "/sites/all/themes/im/css/images/attachment.png" />';
  $handler->display->display_options['fields']['field_sp_others']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_sp_others']['alter']['path'] = '[field_sp_others] ';
  $handler->display->display_options['fields']['field_sp_others']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sp_others']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_sp_others']['type'] = 'file_url_plain';
  $handler->display->display_options['fields']['field_sp_others']['delta_offset'] = '0';
  /* Field: Content: PLV */
  $handler->display->display_options['fields']['field_sp_plv']['id'] = 'field_sp_plv';
  $handler->display->display_options['fields']['field_sp_plv']['table'] = 'field_data_field_sp_plv';
  $handler->display->display_options['fields']['field_sp_plv']['field'] = 'field_sp_plv';
  $handler->display->display_options['fields']['field_sp_plv']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_sp_plv']['alter']['text'] = '<img src = "/sites/all/themes/im/css/images/attachment.png" ';
  $handler->display->display_options['fields']['field_sp_plv']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_sp_plv']['alter']['path'] = '[field_sp_plv] ';
  $handler->display->display_options['fields']['field_sp_plv']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sp_plv']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_sp_plv']['type'] = 'file_url_plain';
  $handler->display->display_options['fields']['field_sp_plv']['delta_offset'] = '0';
  /* Field: Content: Visuels */
  $handler->display->display_options['fields']['field_sp_visual']['id'] = 'field_sp_visual';
  $handler->display->display_options['fields']['field_sp_visual']['table'] = 'field_data_field_sp_visual';
  $handler->display->display_options['fields']['field_sp_visual']['field'] = 'field_sp_visual';
  $handler->display->display_options['fields']['field_sp_visual']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_sp_visual']['alter']['text'] = '<img src = "/sites/all/themes/im/css/images/attachment.png" />';
  $handler->display->display_options['fields']['field_sp_visual']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_sp_visual']['alter']['path'] = '[field_sp_visual]';
  $handler->display->display_options['fields']['field_sp_visual']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sp_visual']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_sp_visual']['type'] = 'file_url_plain';
  $handler->display->display_options['fields']['field_sp_visual']['delta_offset'] = '0';
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Regions */
  $handler->display->display_options['fields']['field_sp_regions']['id'] = 'field_sp_regions';
  $handler->display->display_options['fields']['field_sp_regions']['table'] = 'field_data_field_sp_regions';
  $handler->display->display_options['fields']['field_sp_regions']['field'] = 'field_sp_regions';
  $handler->display->display_options['fields']['field_sp_regions']['label'] = '';
  $handler->display->display_options['fields']['field_sp_regions']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sp_regions']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_sp_regions']['multi_type'] = 'ol';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '<img src = "/sites/all/themes/im/css/images/edit-Pen.png" />';
  $handler->display->display_options['fields']['edit_node']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['required'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    15 => 0,
    9 => 0,
    10 => 0,
    4 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
    3 => 0,
    16 => 0,
    5 => 0,
    6 => 0,
    11 => 0,
    7 => 0,
    8 => 0,
  );
  /* Filter criterion: Content: Type (field_sp_type) */
  $handler->display->display_options['filters']['field_sp_type_value']['id'] = 'field_sp_type_value';
  $handler->display->display_options['filters']['field_sp_type_value']['table'] = 'field_data_field_sp_type';
  $handler->display->display_options['filters']['field_sp_type_value']['field'] = 'field_sp_type_value';
  $handler->display->display_options['filters']['field_sp_type_value']['group'] = 1;
  $handler->display->display_options['filters']['field_sp_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_sp_type_value']['expose']['operator_id'] = 'field_sp_type_value_op';
  $handler->display->display_options['filters']['field_sp_type_value']['expose']['label'] = 'Type (field_sp_type)';
  $handler->display->display_options['filters']['field_sp_type_value']['expose']['operator'] = 'field_sp_type_value_op';
  $handler->display->display_options['filters']['field_sp_type_value']['expose']['identifier'] = 'field_sp_type_value';
  $handler->display->display_options['filters']['field_sp_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    15 => 0,
    9 => 0,
    10 => 0,
    4 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
    3 => 0,
    16 => 0,
    5 => 0,
    6 => 0,
    11 => 0,
    7 => 0,
    8 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create sales_plan content';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<a class="create-function-link"  href="/node/add/sales-plan">Créer une opération commerciale</a>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area_1']['id'] = 'area_1';
  $handler->display->display_options['header']['area_1']['table'] = 'views';
  $handler->display->display_options['header']['area_1']['field'] = 'area';
  $handler->display->display_options['header']['area_1']['empty'] = TRUE;
  $handler->display->display_options['header']['area_1']['content'] = '<a class="create-function-link"  href="/node/add/holiday">Gestion vacances et jours spéciaux</a>';
  $handler->display->display_options['header']['area_1']['format'] = 'full_html';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'sales_plan' => 'sales_plan',
    'holiday' => 'holiday',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type de contenu';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    12 => 0,
    4 => 0,
    14 => 0,
    15 => 0,
    16 => 0,
    3 => 0,
    10 => 0,
    5 => 0,
    6 => 0,
    13 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['type']['group_info']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['group_info']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['type']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Content: Type (field_sp_type) */
  $handler->display->display_options['filters']['field_sp_type_value']['id'] = 'field_sp_type_value';
  $handler->display->display_options['filters']['field_sp_type_value']['table'] = 'field_data_field_sp_type';
  $handler->display->display_options['filters']['field_sp_type_value']['field'] = 'field_sp_type_value';
  $handler->display->display_options['filters']['field_sp_type_value']['group'] = 1;
  $handler->display->display_options['filters']['field_sp_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_sp_type_value']['expose']['operator_id'] = 'field_sp_type_value_op';
  $handler->display->display_options['filters']['field_sp_type_value']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['field_sp_type_value']['expose']['operator'] = 'field_sp_type_value_op';
  $handler->display->display_options['filters']['field_sp_type_value']['expose']['identifier'] = 'field_sp_type_value';
  $handler->display->display_options['filters']['field_sp_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    15 => 0,
    9 => 0,
    10 => 0,
    4 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
    3 => 0,
    16 => 0,
    5 => 0,
    6 => 0,
    11 => 0,
    7 => 0,
    8 => 0,
  );
  /* Filter criterion: Content: Regions (field_sp_regions) */
  $handler->display->display_options['filters']['field_sp_regions_tid']['id'] = 'field_sp_regions_tid';
  $handler->display->display_options['filters']['field_sp_regions_tid']['table'] = 'field_data_field_sp_regions';
  $handler->display->display_options['filters']['field_sp_regions_tid']['field'] = 'field_sp_regions_tid';
  $handler->display->display_options['filters']['field_sp_regions_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_sp_regions_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_sp_regions_tid']['expose']['operator_id'] = 'field_sp_regions_tid_op';
  $handler->display->display_options['filters']['field_sp_regions_tid']['expose']['label'] = 'Regions';
  $handler->display->display_options['filters']['field_sp_regions_tid']['expose']['operator'] = 'field_sp_regions_tid_op';
  $handler->display->display_options['filters']['field_sp_regions_tid']['expose']['identifier'] = 'field_sp_regions_tid';
  $handler->display->display_options['filters']['field_sp_regions_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    15 => 0,
    9 => 0,
    10 => 0,
    4 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
    3 => 0,
    16 => 0,
    5 => 0,
    6 => 0,
    11 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['field_sp_regions_tid']['group_info']['label'] = 'Regions (field_sp_regions)';
  $handler->display->display_options['filters']['field_sp_regions_tid']['group_info']['identifier'] = 'field_sp_regions_tid';
  $handler->display->display_options['filters']['field_sp_regions_tid']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_sp_regions_tid']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  $handler->display->display_options['filters']['field_sp_regions_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_sp_regions_tid']['vocabulary'] = 'regions';
  $handler->display->display_options['filters']['field_sp_regions_tid']['hierarchy'] = 1;
  /* Filter criterion: Content: Operation Period -  start date (field_sp_operation_period) */
  $handler->display->display_options['filters']['field_sp_operation_period_value']['id'] = 'field_sp_operation_period_value';
  $handler->display->display_options['filters']['field_sp_operation_period_value']['table'] = 'field_data_field_sp_operation_period';
  $handler->display->display_options['filters']['field_sp_operation_period_value']['field'] = 'field_sp_operation_period_value';
  $handler->display->display_options['filters']['field_sp_operation_period_value']['operator'] = '<=';
  $handler->display->display_options['filters']['field_sp_operation_period_value']['group'] = 1;
  $handler->display->display_options['filters']['field_sp_operation_period_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_sp_operation_period_value']['expose']['operator_id'] = 'field_sp_operation_period_value_op';
  $handler->display->display_options['filters']['field_sp_operation_period_value']['expose']['label'] = 'Operation Period -  start date';
  $handler->display->display_options['filters']['field_sp_operation_period_value']['expose']['operator'] = 'field_sp_operation_period_value_op';
  $handler->display->display_options['filters']['field_sp_operation_period_value']['expose']['identifier'] = 'field_sp_operation_period_value';
  $handler->display->display_options['filters']['field_sp_operation_period_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    15 => 0,
    9 => 0,
    10 => 0,
    4 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
    3 => 0,
    16 => 0,
    5 => 0,
    6 => 0,
    11 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['field_sp_operation_period_value']['form_type'] = 'date_popup';
  /* Filter criterion: Content: Operation Period - end date (field_sp_operation_period:value2) */
  $handler->display->display_options['filters']['field_sp_operation_period_value2']['id'] = 'field_sp_operation_period_value2';
  $handler->display->display_options['filters']['field_sp_operation_period_value2']['table'] = 'field_data_field_sp_operation_period';
  $handler->display->display_options['filters']['field_sp_operation_period_value2']['field'] = 'field_sp_operation_period_value2';
  $handler->display->display_options['filters']['field_sp_operation_period_value2']['operator'] = '>=';
  $handler->display->display_options['filters']['field_sp_operation_period_value2']['group'] = 1;
  $handler->display->display_options['filters']['field_sp_operation_period_value2']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_sp_operation_period_value2']['expose']['operator_id'] = 'field_sp_operation_period_value2_op';
  $handler->display->display_options['filters']['field_sp_operation_period_value2']['expose']['label'] = 'Operation Period - end date';
  $handler->display->display_options['filters']['field_sp_operation_period_value2']['expose']['operator'] = 'field_sp_operation_period_value2_op';
  $handler->display->display_options['filters']['field_sp_operation_period_value2']['expose']['identifier'] = 'field_sp_operation_period_value2';
  $handler->display->display_options['filters']['field_sp_operation_period_value2']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    15 => 0,
    9 => 0,
    10 => 0,
    4 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
    3 => 0,
    16 => 0,
    5 => 0,
    6 => 0,
    11 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['field_sp_operation_period_value2']['form_type'] = 'date_popup';
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    15 => 0,
    9 => 0,
    10 => 0,
    4 => 0,
    12 => 0,
    13 => 0,
    14 => 0,
    3 => 0,
    16 => 0,
    5 => 0,
    6 => 0,
    11 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['path'] = 'admin/im/manage/sales_plan';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Gestion Plan de ventes';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['sales_plan_management'] = array(
    t('Master'),
    t('Manage Sales plan'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Title'),
    t('Region Type'),
    t('Operation period date'),
    t('Order period date'),
    t('Broken handler field_data_field_sp_benchmark.field_sp_benchmark'),
    t('<img src = "/sites/all/themes/im/css/images/attachment.png" />'),
    t('Catalogue'),
    t('Help control'),
    t('Other'),
    t('PLV'),
    t('<img src = "/sites/all/themes/im/css/images/attachment.png" '),
    t('Visuels'),
    t('Status'),
    t('<img src = "/sites/all/themes/im/css/images/edit-Pen.png" />'),
    t('Published'),
    t('Type (field_sp_type)'),
    t('Page'),
    t('<a class="create-function-link"  href="/node/add/sales-plan">Créer une opération commerciale</a>'),
    t('<a class="create-function-link"  href="/node/add/holiday">Gestion vacances et jours spéciaux</a>'),
    t('Type de contenu'),
    t('Type'),
    t('Regions'),
    t('Regions (field_sp_regions)'),
    t('Operation Period -  start date'),
    t('Operation Period - end date'),
  );
  $export['sales_plan_management'] = $view;

  return $export;
}
