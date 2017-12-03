<?php

module_load_include('inc', 'ask_mayor', 'src/ask_mayor.sql');
/**
 * Public page with ask the mayor form and block
 * @return string
 */
function _ask_mayor_page_callback() {
  $form = drupal_get_form('ask_mayor_question_form');
  $question_form = drupal_render($form);

  $response_teaser_block = module_invoke('ask_mayor', 'block_view', 'response_teaser');
  $archive_block_block = module_invoke('ask_mayor', 'block_view', 'ask_mayor_archive');
  $response_teaser = render($response_teaser_block['content']);
  if (!empty($archive_block_block['content']) && !empty($response_teaser_block['content'])) {
    $archive_block = render($archive_block_block['content']);
  } else {
    $archive_block = FALSE;
  }

  if (!empty(variable_get('ask_mayor_main_page_image'))) {
    $img_url = file_create_url(file_load(variable_get('ask_mayor_main_page_image'))->uri);
    $img_path = str_replace($_SERVER['DOCUMENT_ROOT'].'/','',$img_url);
  } else {
    $img_path = FALSE;
  }
  $content = [
    'ask_mayor_title' => variable_get('ask_mayor_main_page_title',t("Ask the Mayor")),
    'ask_mayor_image' => $img_path,
    'ask_mayor_body' => variable_get('ask_mayor_main_page_body', NULL),
    'question_form' => $question_form,
    'teaser_block' => $response_teaser,
    'archive_block' => $archive_block,
  ];

  return theme('ask_mayor_page', $content);
}

/**
 * The form for ask the mayor
 * @param $form
 * @param $form_state
 * @return mixed
 */
function ask_mayor_question_form($form, $form_state) {
  $form['name'] = [
    '#type' => 'textfield',
    '#title' => t('Your Name'),
    '#required' => TRUE,
  ];

  $form['email'] = [
    '#type' => 'textfield',
    '#title' => t('Your Email'),
    '#required' => TRUE,
    '#default_value' => "",
  ];

  $form['subject'] = [
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#required' => TRUE,
  ];

  $form['question'] = [
    '#type' => 'textarea',
    '#title' => t('Your Question'),
    '#required' => TRUE,
  ];

  $form['submit'] = [
    '#type' => 'submit',
    '#value' => 'Send',
    '#submit' => ['ask_mayor_question_submit'],
    '#validate' => ['ask_mayor_question_validate'],
  ];

  return $form;
}

/**
 * Validate email
 * @param $form
 * @param $form_state
 */
function ask_mayor_question_validate($form, &$form_state) {
  $valid_email = $form_state['values']['email'];
  if (!valid_email_address($valid_email)) {
    form_set_error('email', 'Sorry. Your email address,' . $valid_email . ', is not valid. Please submit a valid E-mail address.');
  }
}

/**
 * Submit handler for ask the mayor form
 * @param $form
 * @param $form_state
 */
function ask_mayor_question_submit($form, &$form_state) {
  // Data array for saving the form data to the ask_mayor table
  $data = [
    'mail' => $form_state['values']['email'],
    'submitter_name' => $form_state['values']['name'],
    'question' => $form_state['values']['question'],
    'subject' => $form_state['values']['subject'],
    'created' => REQUEST_TIME,
    'updated' => REQUEST_TIME,
    'year' => format_date(REQUEST_TIME, 'custom', 'Y'),
  ];
  // Save the data variable to the ask_mayor table.
  $save_data = ask_mayor_save_question($data);
  // Check to see if the data saved. If it didn't the set error variable.
  if (!$save_data) {
    $form_state['error'] = true;
  }
  drupal_mail(
    'ask_mayor',
    'question_notice',
    variable_get('ask_mayor_response_email', variable_get('site_email')),
    LANGUAGE_NONE,
    $params = ['qid' => $save_data],
    $from = NULL,
    $send = TRUE
  );

  drupal_mail(
    'ask_mayor',
    'question_verification',
    $form_state['values']['email'],
    LANGUAGE_NONE,
    $params = ['qid' => $save_data],
    $from = NULL,
    $send = TRUE
  );
}