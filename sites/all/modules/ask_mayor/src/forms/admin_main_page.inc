<?php

/**
 * The configuration form for main ask the mayor public page settings.
 * @return mixed
 */
function _admin_main_page() {
  $form['ask_mayor_main_page_title'] = [
    '#title' => t('Page Title'),
    '#type' => 'textfield',
    '#default_value' => t('Ask the Mayor'),
  ];

  $form['ask_mayor_main_page_path'] = [
    '#title' => t('Page Path'),
    '#type' => 'textfield',
    '#default_value' => variable_get('ask_mayor_main_page_path') !== null ? variable_get('ask_mayor_main_page_path') : t('ask-the-mayor'),
  ];

  if (variable_get('ask_mayor_main_page_image') !== null) {
     $fid = variable_get('ask_mayor_main_page_image');
  } else {
     $fid = null;
  }

  $form['ask_mayor_main_page_image'] = [
    '#title' => t('Image'),
    '#description' => 'Allowed file types are jpeg, jpg, and png',
    '#type' => 'managed_file',
    '#upload_validators' => ['file_validate_extensions' => ['jpeg jpg png']],
    '#upload_location' => 'public://',
    '#progress_indicator' => 'throbber',
    '#progress_message' => 'One moment while we save your file...',
    '#default_value' => $fid,
  ];

  if (variable_get('ask_mayor_main_page_body') !== null) {
    $body = variable_get('ask_mayor_main_page_body');
    $body = t($body['value']);
  } else {
    $body = NULL;
  }
  $form['ask_mayor_main_page_body'] = [
    '#prefix' => '<div style="margin: 3em 0; max-width: 680px;">',
    '#suffix' => '</div>',
    '#title' => t('Body'),
    '#module' => 'text',
    '#type'=>'text_format',
    '#rows' => 20,
    '#format'=>'filtered_html',
    '#default_value' => $body,
    '#settings' => array(
      'rows' => 20,
    ),
  ];
  $form['#submit'][] = 'custom_settings_form_submit';
  return system_settings_form($form);
}

function custom_settings_form_submit($form, &$form_state) {
  if ($form_state['values']['ask_mayor_main_page_image']) {
    $file = file_load($form_state['values']['ask_mayor_main_page_image']);
    $file->status = FILE_STATUS_PERMANENT;
//    file_save($file);
    file_usage_add($file, 'ask_mayor', 'mayor_picture',$form_state['values']['ask_mayor_main_page_image'] );
  }

  return $form;
}