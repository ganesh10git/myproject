<?php 

/**
 * Return a form for managing IM custom settings.
 */
function im_sales_plan_admin_form() {
  $form = array();
  $form['im_sales_plan_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('IM Sales plan settings')
  ); 
   $form['im_sales_plan_settings']['im_admin_sales_plan_catalogue'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the value for Catalogue'),
    '#description' => t('Enter the value for Catalogue category'),
    '#required' => TRUE,
    '#default_value' => variable_get('im_admin_sales_plan_catalogue', 'Catalogue'),
  );
  $form['im_sales_plan_settings']['im_admin_sales_plan_help_control'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the value for Help Control'),
    '#description' => t('Enter the value for Help Control category'),
    '#required' => TRUE,
    '#default_value' => variable_get('im_admin_sales_plan_help_control', 'Help Control'),
  );
  $form['im_sales_plan_settings']['im_admin_sales_plan_plv'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the value for PLV'),
    '#description' => t('Enter the value for PLV category'),
    '#required' => TRUE,
    '#default_value' => variable_get('im_admin_sales_plan_plv', 'PLV'),
  );
   $form['im_sales_plan_settings']['im_admin_sales_plan_visual'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the value for Visual'),
    '#description' => t('Enter the value for visual'),
    '#required' => TRUE,
    '#default_value' => variable_get('im_admin_sales_plan_visual', 'Visual'),
  );
  $form['im_sales_plan_settings']['im_admin_sales_plan_others'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the value for Others'),
    '#description' => t('Enter the value for others category'),
    '#required' => TRUE,
    '#default_value' => variable_get('im_admin_sales_plan_others', 'Others'),
  ); 
  
  return system_settings_form($form);
}