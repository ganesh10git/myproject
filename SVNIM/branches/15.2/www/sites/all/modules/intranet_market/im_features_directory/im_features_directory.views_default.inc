<?php
/**
 * @file
 * im_features_directory.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function im_features_directory_views_default_views() {
  $export = array();
  $view = new view();
  $view->name = 'manage_directory';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Manage Directory';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage Directory';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create directory content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Réinitialiser';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« premier';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ précédent';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'suivant ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'dernier »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_dir_category',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
    1 => array(
      'field' => 'field_dir_function',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_dir_category' => 'field_dir_category',
    'field_dir_function' => 'field_dir_function',
    'field_full_name' => 'field_full_name',
    'timestamp' => 'timestamp',
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
    'field_dir_category' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_dir_function' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_full_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Entête: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<a class="create-function-link" href="/node/add/directory">' .t("Create Directory" ) . '</a>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Relationship: Contenu: Auteur */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Contenu: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'directory_category' => 'directory_category',
    'application_category' => 0,
    'agenda_department' => 0,
    'fonctions' => 0,
    'om_domains' => 0,
    'operational_model_location' => 0,
    'om_roles' => 0,
    'regions' => 0,
  );
  /* Champ: Contenu: Titre */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Champ: Contenu: Category */
  $handler->display->display_options['fields']['field_dir_category']['id'] = 'field_dir_category';
  $handler->display->display_options['fields']['field_dir_category']['table'] = 'field_data_field_dir_category';
  $handler->display->display_options['fields']['field_dir_category']['field'] = 'field_dir_category';
  $handler->display->display_options['fields']['field_dir_category']['label'] = 'Categorie';
  $handler->display->display_options['fields']['field_dir_category']['element_label_colon'] = FALSE;
  /* Champ: Contenu: Function */
  $handler->display->display_options['fields']['field_dir_function']['id'] = 'field_dir_function';
  $handler->display->display_options['fields']['field_dir_function']['table'] = 'field_data_field_dir_function';
  $handler->display->display_options['fields']['field_dir_function']['field'] = 'field_dir_function';
  $handler->display->display_options['fields']['field_dir_function']['label'] = 'Fonction';
  $handler->display->display_options['fields']['field_dir_function']['element_label_colon'] = FALSE;
  /* Champ: Utilisateur: Full Name */
  $handler->display->display_options['fields']['field_full_name']['id'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['table'] = 'field_data_field_full_name';
  $handler->display->display_options['fields']['field_full_name']['field'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['field_full_name']['label'] = 'Modifier';
  /* Champ: Content revision: Updated date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'node_revision';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Last Modification Rule';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'im_date_format';
  /* Sort criterion: Terme de taxonomie: Poids */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['relationship'] = 'term_node_tid';
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
    'directory' => 'directory',
  );
  /* Filter criterion: Contenu: Category (field_dir_category) */
  $handler->display->display_options['filters']['field_dir_category_tid']['id'] = 'field_dir_category_tid';
  $handler->display->display_options['filters']['field_dir_category_tid']['table'] = 'field_data_field_dir_category';
  $handler->display->display_options['filters']['field_dir_category_tid']['field'] = 'field_dir_category_tid';
  $handler->display->display_options['filters']['field_dir_category_tid']['value'] = '';
  $handler->display->display_options['filters']['field_dir_category_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_dir_category_tid']['expose']['operator_id'] = 'field_dir_category_tid_op';
  $handler->display->display_options['filters']['field_dir_category_tid']['expose']['label'] = 'Catégorie';
  $handler->display->display_options['filters']['field_dir_category_tid']['expose']['operator'] = 'field_dir_category_tid_op';
  $handler->display->display_options['filters']['field_dir_category_tid']['expose']['identifier'] = 'field_dir_category_tid';
  $handler->display->display_options['filters']['field_dir_category_tid']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_dir_category_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_dir_category_tid']['vocabulary'] = 'directory_category';
  $handler->display->display_options['filters']['field_dir_category_tid']['hierarchy'] = 1;
  /* Filter criterion: Contenu: Function (field_dir_function) */
  $handler->display->display_options['filters']['field_dir_function_tid']['id'] = 'field_dir_function_tid';
  $handler->display->display_options['filters']['field_dir_function_tid']['table'] = 'field_data_field_dir_function';
  $handler->display->display_options['filters']['field_dir_function_tid']['field'] = 'field_dir_function_tid';
  $handler->display->display_options['filters']['field_dir_function_tid']['value'] = '';
  $handler->display->display_options['filters']['field_dir_function_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_dir_function_tid']['expose']['operator_id'] = 'field_dir_function_tid_op';
  $handler->display->display_options['filters']['field_dir_function_tid']['expose']['label'] = 'Fonction';
  $handler->display->display_options['filters']['field_dir_function_tid']['expose']['operator'] = 'field_dir_function_tid_op';
  $handler->display->display_options['filters']['field_dir_function_tid']['expose']['identifier'] = 'field_dir_function_tid';
  $handler->display->display_options['filters']['field_dir_function_tid']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_dir_function_tid']['vocabulary'] = 'fonctions';
  $handler->display->display_options['filters']['field_dir_function_tid']['hierarchy'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/im/manage/directory';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage Directory';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'main-menu';
  $translatables['manage_directory'] = array(
    t('Master'),
    t('Manage Directory'),
    t('plus'),
    t('Apply'),
    t('Réinitialiser'),
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
    t('Create Directory'),
    t('author'),
    t('term'),
    t('Titre'),
    t('Categorie'),
    t('Fonction'),
    t('Modifier'),
    t('Last Modification Rule'),
    t('Catégorie'),
    t('Page'),
  );
  $export['manage_directory'] = $view;

  return $export;
}
