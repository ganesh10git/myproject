<?php 
/**
 * Product guide back office form.
 */
function im_product_guide_bo_form(){
	 drupal_add_js(drupal_get_path('module', 'im_product_guide') . '/js/im_product_guide.js');
  $form = array();
  $form['pg_configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Product Guide Configuration')
  );
  $form['pg_configuration']['pg_url_radio'] = array(
    '#type' => 'radios',
    '#options' => array('url'=>t('URL')),
  );
  $form['pg_configuration']['pg_url_textbox'] = array(
    '#type' =>'textfield',
    '#description' => t('enter with "http",example http://carrefour.fr'),
    '#size' => 60,
    '#default_value' => variable_get('im_product_guide_url'),
  );
  $form['pg_configuration']['pg_ldap_fr_tag_radio'] = array(
    '#type' => 'radios',
    //'#title' => 'Ldap France Tag',
    '#options' => array('ldap_fr_tag'=>t('LDAP France Tag')),
  );
  $form['pg_configuration']['pg_ldap_fr_tag_textbox'] = array(
    '#type' =>'textfield',
    //'#description' => t('enter with "http",example http://carrefour.fr'),
    '#size' => 60,
    '#default_value' => variable_get('im_product_guide_ldap_fr_tag'),
  );
  $form['pg_iframe_configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Product Guide Iframe Settings')
  );
  $form['pg_iframe_configuration']['pg_iframe_width_textbox'] = array(
    '#type' =>'textfield',
    '#title' => t('Iframe Width'),
    '#description' => t('width in % example 100%'),
    '#size' => 60,
    '#default_value' => variable_get('im_product_guide_iframe_width'),
  );
  $form['pg_iframe_configuration']['pg_iframe_height_textbox'] = array(
    '#type' =>'textfield',
    '#title' => t('Iframe Height'),
    '#size' => 60,
    '#description' => t('height in px example 650px'),
    '#default_value' => variable_get('im_product_guide_iframe_height'),
  );
  $form['pg_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

//product guide form validate
function im_product_guide_bo_form_validate($form, &$form_state){
  if(!empty($form_state['values']['pg_url_radio']) && empty($form_state['values']['pg_url_textbox'])){
      form_set_error('pg_url_textbox', t('url textbox is empty'));
  }
  if(!empty($form_state['values']['pg_ldap_fr_tag_radio']) && empty($form_state['values']['pg_ldap_fr_tag_textbox'])){
      form_set_error('pg_ldap_fr_tag_textbox', t('ldap france tag textbox is empty'));
  }
  if(empty($form_state['values']['pg_url_radio']) && empty($form_state['values']['pg_ldap_fr_tag_radio'])){
      form_set_error('pg_url_radio',t('Select any of the radio button'));
 }
} 

//product guide form submit
function im_product_guide_bo_form_submit($form,&$form_state){
  if(!empty($form_state['values']['pg_url_radio'])){
    variable_set('im_product_guide_url', $form_state['values']['pg_url_textbox']);
    variable_set('im_product_guide_ldap_fr_tag', '');
  }
  elseif (!empty($form_state['values']['pg_ldap_fr_tag_radio'])){
    variable_set('im_product_guide_ldap_fr_tag', $form_state['values']['pg_ldap_fr_tag_textbox']);
    variable_set('im_product_guide_url', '');
  }
 if(!empty($form_state['values']['pg_iframe_width_textbox'])){
    variable_set('im_product_guide_iframe_width', $form_state['values']['pg_iframe_width_textbox']);
  }
  if(!empty($form_state['values']['pg_iframe_height_textbox'])){
    variable_set('im_product_guide_iframe_height', $form_state['values']['pg_iframe_height_textbox']);
  }
  drupal_set_message(t('Successfully updated'));
}

