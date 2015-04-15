<?php

/**
 * Return a form for managing IM custom settings.
 */
function im_custom_settings_admin_form() {
  $form = array();
  $form['om_settings'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Om settings')
  );
  $form['om_settings']['om_Publication_to_date_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Om Publication To date Settings')
  );
  $form['om_settings']['om_Publication_to_date_settings']['n_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the N value'),
    '#description' => t('Enter the value of N in months'),
    '#required' => TRUE,
    '#default_value' => variable_get('im_admin_n'),
  );
  $form['om_settings']['om_mail_trigger_settings']= array(
    '#type' => 'fieldset',
    '#title' => t('Om Mail Trigger Setting'),
  );
  $form['om_settings']['om_mail_trigger_settings']['mail_n_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the number of days'),
    '#description' => t('Enter the value of N in days to trigger mail'),
    '#required' => TRUE,
    '#default_value' => variable_get('om_mail_trigger_nvalue'),
  );
  //Agenda settings...
  $form['agenda_settings'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Agenda settings')
  );
  $form['agenda_settings']['agenda_future_action_days'] = array(
    '#type' => 'fieldset',
    '#title' => t('Agenda Future Action Link Settings')
  );
  $form['agenda_settings']['agenda_future_action_days']['nvalue_agenda_home_page'] =  array(
    '#title' => t('N  days for future action link home page'),
    '#type' => 'textfield',
    '#description' => t('Enter the N value in days'),
    '#required' => TRUE,
    '#default_value' => variable_get('im_future_action_ndays'),
  );
  $form['agenda_settings']['agenda_publication_to_date_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Agenda Publication To date Settings')
  );
  $form['agenda_settings']['agenda_publication_to_date_settings']['action_publication_todate_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the value of N in months for Action content'),
    '#description' => t('Enter the value of N in months for Action content'),
    '#required' => TRUE,
    '#default_value' => (variable_get('action_publication_todate_nvalue')!='')? variable_get('action_publication_todate_nvalue') : '18',
  );
  $form['agenda_settings']['agenda_publication_to_date_settings']['alert_publication_todate_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the value of N in months in Alert content'),
    '#description' => t('Enter the value of N in months in Alert content'),
    '#required' => TRUE,
    '#default_value' => (variable_get('alert_publication_todate_nvalue')!='')? variable_get('alert_publication_todate_nvalue') : '18',
  );
  $form['agenda_settings']['agenda_publication_to_date_settings']['news_publication_todate_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the value of N in months in News content'),
    '#description' => t('Enter the value of N in months in News content'),
    '#required' => TRUE,
    '#default_value' => (variable_get('news_publication_todate_nvalue')!='')? variable_get('news_publication_todate_nvalue') : '18',
  );
  $form['agenda_settings']['agenda_publication_to_date_settings']['benchmark_publication_todate_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the value of N in months in Benchmark content'),
    '#description' => t('Enter the value of N in months in Benchmark content'),
    '#required' => TRUE,
    '#default_value' => (variable_get('benchmark_publication_todate_nvalue')!='')? variable_get('benchmark_publication_todate_nvalue') : '18',
  );
  //cuwa settings
  $form['cuwa'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cuwa Settings'),
    //'#access' => module_exists('fr_cuwa'),
  );
  $form['cuwa']['im_cuwa_mode'] = array(
    '#type' => 'select',
    '#title' => t('Cuwa mode'),
    '#options' => array(
      'test' => 'Test',
      'default' => 'Default'
    ),
    '#default_value' => variable_get('core_custom_im_cuwa_mode', 'test'),
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
function im_custom_settings_admin_form_submit($form, &$form_state) {
  //saving n_value in a variable. 
  variable_set('core_custom_im_cuwa_mode',$form_state['values']['im_cuwa_mode']);
	variable_set('im_admin_n', $form_state['values']['n_value']);
  variable_set('om_mail_trigger_nvalue', $form_state['values']['mail_n_value']);
  variable_set('im_future_action_ndays', $form_state['values']['nvalue_agenda_home_page']);
  variable_set('action_publication_todate_nvalue', $form_state['values']['action_publication_todate_value']);
  variable_set('alert_publication_todate_nvalue', $form_state['values']['alert_publication_todate_value']);
  variable_set('news_publication_todate_nvalue', $form_state['values']['news_publication_todate_value']);
  variable_set('benchmark_publication_todate_nvalue', $form_state['values']['benchmark_publication_todate_value']);
	drupal_set_message(t('The configuration options have been saved.'));
}
