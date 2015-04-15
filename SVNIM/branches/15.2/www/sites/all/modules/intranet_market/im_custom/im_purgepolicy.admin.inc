<?php
/**
 * Return a form for managing IM Purge policy settings.
 */
function im_purgepolicy_settings_admin_form() {
  $form = array();
  $form['purgepolicy_settings'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Purge Policy Settings')
  );
  $form['purgepolicy_settings']['agenda_contents_no_of_months_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Agenda contents Settings')
  );
  $form['purgepolicy_settings']['agenda_contents_no_of_months_settings']['agenda_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the agenda contents no of months value'),
    '#description' => t('Enter the value of No of months'),
    '#required' => TRUE,
    '#default_value' => (variable_get('im_agenda_no_of_months_value')!='')? variable_get('im_agenda_no_of_months_value') : '18',
  );
  $form['purgepolicy_settings']['wiki_market_no_of_months_settings']= array(
    '#type' => 'fieldset',
    '#title' => t('Wiki market no of months Setting'),
  );
  $form['purgepolicy_settings']['wiki_market_no_of_months_settings']['wiki_market_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the number of months'),
    '#description' => t('Enter the wiki market no of months value'),
    '#required' => TRUE,
    '#default_value' => (variable_get('im_wiki_market_no_of_months_value')!='')? variable_get('im_wiki_market_no_of_months_value') : '18',
  );
  $form['purgepolicy_settings']['sales_plan_no_of_months_settings']= array(
    '#type' => 'fieldset',
    '#title' => t('Sales plan no of months Setting'),
  );
  $form['purgepolicy_settings']['sales_plan_no_of_months_settings']['sales_plan_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the number of months'),
    '#description' => t('Enter the Sales plan no of months value'),
    '#required' => TRUE,
    '#default_value' => (variable_get('im_sales_plan_no_of_months_value')!='')? variable_get('im_sales_plan_no_of_months_value') : '18',
  );
  $form['purgepolicy_settings']['users_no_of_months_settings']= array(
    '#type' => 'fieldset',
    '#title' => t('Users no of months Setting'),
  );
  $form['purgepolicy_settings']['users_no_of_months_settings']['users_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the number of months'),
    '#description' => t('Enter the Users no of months value'),
    '#required' => TRUE,
    '#default_value' => (variable_get('im_users_no_of_months_value')!='')? variable_get('im_users_no_of_months_value') : '18',
  );  
  //Form Submit
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );
  return $form;
}
/**
 * Hook_submit.
 * Save settings after form submit.
 */
function im_purgepolicy_settings_admin_form_submit($form, &$form_state) {
  //saving n_value in a variable. 
  variable_set('im_agenda_no_of_months_value',$form_state['values']['agenda_value']);
	variable_set('im_wiki_market_no_of_months_value', $form_state['values']['wiki_market_value']);
  variable_set('im_sales_plan_no_of_months_value', $form_state['values']['sales_plan_value']);
  variable_set('im_users_no_of_months_value', $form_state['values']['users_value']);
 
	drupal_set_message(t('The configuration options has been saved.'));
}
