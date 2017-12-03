<?php

/**
 * Form for the the global setting of ask mayor module.
 * @return mixed
 */
function _admin_settings() {
  $form['ask_mayor_response_email'] = [
    '#title' => t('Ask the Mayor Notification Email'),
    '#type' => 'textfield',
    '#default_value' => variable_get('ask_mayor_response_email') !== NULL ?
      variable_get('ask_mayor_response_email')
      : variable_get('site_mail'),
  ];

  $form['ask_mayor_email_response_body'] = [
    '#title' => t('Ask the Mayor Notification Body for Email Notification'),
    '#type' => 'textarea',
    '#default_value' => variable_get('ask_mayor_email_response_body') !== NULL ?
      variable_get('ask_mayor_email_response_body')
      : "Your question has an answer waiting to be viewed.",
  ];

  $form['ask_mayor_pager_block'] = [
    '#title' => 'Pager Maximum Amount for Teaser Block',
    '#type' => 'textfield',
    '#element_validate' => array('element_validate_number'),
    '#default_value' => variable_get('ask_mayor_pager_block') !== NULL ?
      variable_get('ask_mayor_pager_block')
      : 5,
  ];

  return system_settings_form($form);
}

