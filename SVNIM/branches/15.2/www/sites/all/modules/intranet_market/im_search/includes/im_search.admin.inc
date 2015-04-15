<?php
/**
 * @file
 * Return a form for IM Search settings.
 */

/**
 * Implement _im_search_settings_admin_form.
 */
function _im_search_settings_admin_form() {
  $form = array();
  $form['Search_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('IM Search Settings')
  );
  $form['Search_settings']['im_autocomplete_activation_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Autocomplete for search'),
    '#default_value' => variable_get('im_autocomplete_activation_status', FALSE),
  );
  return system_settings_form($form);
}