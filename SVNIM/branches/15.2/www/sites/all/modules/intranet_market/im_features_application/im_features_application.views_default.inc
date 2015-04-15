<?php
/**
 * @file
 * im_features_application.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function im_features_application_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'applications_home_page';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Applications Home Page';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Appliquer';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'R�initialiser';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_app_category',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['row_class'] = 'app-teasers';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  /* Relationship: Contenu: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'application_category' => 'application_category',
    'agenda_department' => 0,
    'fonctions' => 0,
    'om_domains' => 0,
    'operational_model_location' => 0,
    'om_roles' => 0,
    'regions' => 0,
  );
  /* Champ: Contenu: Application Logo */
  $handler->display->display_options['fields']['field_app_icon']['id'] = 'field_app_icon';
  $handler->display->display_options['fields']['field_app_icon']['table'] = 'field_data_field_app_icon';
  $handler->display->display_options['fields']['field_app_icon']['field'] = 'field_app_icon';
  $handler->display->display_options['fields']['field_app_icon']['label'] = '';
  $handler->display->display_options['fields']['field_app_icon']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_app_icon']['element_class'] = 'im-app-icon';
  $handler->display->display_options['fields']['field_app_icon']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_app_icon']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_app_icon']['empty'] = '<img src="/sites/all/modules/intranet_market/im_features_application/application_default_logo.png">';
  $handler->display->display_options['fields']['field_app_icon']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_app_icon']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_app_icon']['settings'] = array(
    'image_style' => 'application_icon',
    'image_link' => '',
  );
  /* Champ: Contenu: LDAP France Tag */
  $handler->display->display_options['fields']['field_ldap_sso_redirect']['id'] = 'field_ldap_sso_redirect';
  $handler->display->display_options['fields']['field_ldap_sso_redirect']['table'] = 'field_data_field_ldap_sso_redirect';
  $handler->display->display_options['fields']['field_ldap_sso_redirect']['field'] = 'field_ldap_sso_redirect';
  $handler->display->display_options['fields']['field_ldap_sso_redirect']['label'] = '';
  $handler->display->display_options['fields']['field_ldap_sso_redirect']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ldap_sso_redirect']['element_label_colon'] = FALSE;
  /* Champ: Contenu: URL */
  $handler->display->display_options['fields']['field_app_url']['id'] = 'field_app_url';
  $handler->display->display_options['fields']['field_app_url']['table'] = 'field_data_field_app_url';
  $handler->display->display_options['fields']['field_app_url']['field'] = 'field_app_url';
  $handler->display->display_options['fields']['field_app_url']['exclude'] = TRUE;
  /* Champ: Contenu: Titre */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['target'] = ' _blank';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'div';
  $handler->display->display_options['fields']['title']['element_class'] = 'app-container-title';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Champ: Contenu: Link to the documentation */
  $handler->display->display_options['fields']['field_app_document']['id'] = 'field_app_document';
  $handler->display->display_options['fields']['field_app_document']['table'] = 'field_data_field_app_document';
  $handler->display->display_options['fields']['field_app_document']['field'] = 'field_app_document';
  $handler->display->display_options['fields']['field_app_document']['label'] = '';
  $handler->display->display_options['fields']['field_app_document']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_app_document']['alter']['text'] = 't';
  $handler->display->display_options['fields']['field_app_document']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_app_document']['alter']['path'] = '[field_app_document]';
  $handler->display->display_options['fields']['field_app_document']['alter']['external'] = TRUE;
  $handler->display->display_options['fields']['field_app_document']['alter']['link_class'] = 'im-app-doc-help-link';
  $handler->display->display_options['fields']['field_app_document']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['field_app_document']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_app_document']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_app_document']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_app_document']['type'] = 'text_plain';
  /* Champ: Contenu: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = 'Ajouter';
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['path'] = '[title]';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Champ: Contenu: Category */
  $handler->display->display_options['fields']['field_app_category']['id'] = 'field_app_category';
  $handler->display->display_options['fields']['field_app_category']['table'] = 'field_data_field_app_category';
  $handler->display->display_options['fields']['field_app_category']['field'] = 'field_app_category';
  $handler->display->display_options['fields']['field_app_category']['label'] = '';
  $handler->display->display_options['fields']['field_app_category']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_app_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_app_category']['type'] = 'taxonomy_term_reference_plain';
  /* Champ: Contenu: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['body']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['body']['alter']['more_link_text'] = 'Plus';
  $handler->display->display_options['fields']['body']['element_type'] = 'div';
  $handler->display->display_options['fields']['body']['element_class'] = 'im-app-description';
  $handler->display->display_options['fields']['body']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['body']['type'] = 'text_plain';
  /* Champ: Contenu: Download a file */
  $handler->display->display_options['fields']['field_documentation_file_upload']['id'] = 'field_documentation_file_upload';
  $handler->display->display_options['fields']['field_documentation_file_upload']['table'] = 'field_data_field_documentation_file_upload';
  $handler->display->display_options['fields']['field_documentation_file_upload']['field'] = 'field_documentation_file_upload';
  $handler->display->display_options['fields']['field_documentation_file_upload']['label'] = '';
  $handler->display->display_options['fields']['field_documentation_file_upload']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_documentation_file_upload']['alter']['text'] = 't';
  $handler->display->display_options['fields']['field_documentation_file_upload']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_documentation_file_upload']['alter']['path'] = '[field_documentation_file_upload]';
  $handler->display->display_options['fields']['field_documentation_file_upload']['alter']['link_class'] = 'im-app-doc-help-link';
  $handler->display->display_options['fields']['field_documentation_file_upload']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['field_documentation_file_upload']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_documentation_file_upload']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_documentation_file_upload']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_documentation_file_upload']['type'] = 'file_url_plain';
  /* Sort criterion: Terme de taxonomie: Poids */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['relationship'] = 'term_node_tid';
  /* Sort criterion: Contenu: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
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
    'application' => 'application',
  );
  /* Filter criterion: Contenu: Application Type (field_application_type) */
  $handler->display->display_options['filters']['field_application_type_value']['id'] = 'field_application_type_value';
  $handler->display->display_options['filters']['field_application_type_value']['table'] = 'field_data_field_application_type';
  $handler->display->display_options['filters']['field_application_type_value']['field'] = 'field_application_type_value';
  $handler->display->display_options['filters']['field_application_type_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_application_type_value']['value'] = array(
    1 => '1',
  );

  /* Display: Applications Home page */
  $handler = $view->new_display('page', 'Applications Home page', 'page');
  $handler->display->display_options['path'] = 'applications';
  $translatables['applications_home_page'] = array(
    t('Master'),
    t('plus'),
    t('Appliquer'),
    t('R�initialiser'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('term'),
    t('<img src="/sites/all/modules/intranet_market/im_features_application/application_default_logo.png">'),
    t('URL'),
    t('t'),
    t('Ajouter'),
    t('Description'),
    t('Plus'),
    t('Applications Home page'),
  );
  $export['applications_home_page'] = $view;

  return $export;
}
