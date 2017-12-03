<?php
module_load_include('inc', 'ask_mayor', 'src/ask_mayor.sql');

/**
 * Callback fir the response form
 * @param $param
 * @return mixed
 */
function _ask_mayor_respond($param) {
  $form = drupal_get_form('ask_mayor_respond_form', [$param]);
  $question_form = drupal_render($form);
  $content['question_form'] = [
    '#type' => 'markup',
    '#markup' => $question_form,
  ];

  return $content;
}

/**
 * The response form
 * @param $form
 * @param $form_state
 * @param $param
 * @return mixed
 */
function ask_mayor_respond_form($form, $form_state, $param) {
  $question = ask_mayor_load_question($param[0]);
  $name = $question['submitter_name'];
  $date = format_date($question['created'], 'custom', 'd F Y');
  $question_asked = $question['question'];
  $form['#qid'] = $param[0];

  $form['respond']['submitter_name'] = [
    '#markup' => "<h2>$name on $date asked:</h2><hr/>",
  ];
  $form['respond']['subject'] = [
    '#prefix' => '<div style="margin-top: 3em; max-width: 640px; border: 1px solid black; padding: 20px;"><label>Subject</label> <hr />',
    '#suffix' => '</div>',
    '#markup' => $question['subject']
  ];

  $form['respond']['question'] = [
    '#prefix' => '<div style="margin-top: 3em; max-width: 640px; border: 1px solid black; padding: 20px;"><label>Question</label><hr/>',
    '#suffix' => '</div>',
    '#markup' => "$question_asked"
  ];

  $form['respond']['response'] = [
    '#prefix' => '<div style="margin: 3em 0; max-width: 680px;">',
    '#suffix' => '</div>',
    '#title' => t('Response'),
    '#module' => 'text',
    '#type'=>'text_format',
    '#rows' => 20,
    '#default_value' => isset($question['response']) ? $question['response'] : NULL,
    '#format'=>'filtered_html',
    '#settings' => array(
      'rows' => 20,
    ),
  ];

  $form['respond']['notify'] = [
    '#title' => t('Send Email Notification'),
    '#type' => 'checkboxes',
    '#description' => t(''),
    '#options' => ['1' => "Notify $name?"],
    '#default_value' =>  [1]
  ];

  $form['respond']['submit'] = [
    '#value' => !empty($question['response']) ? t('Update') : t('Respond'),
    '#type' => 'submit',
    '#validate' => ['_respond_validate'],
    '#submit' => ['_respond_submit'],
    '#weight' => 10,
  ];

  return $form;
}

function _respond_validate($form, &$form_state) {
  if (empty($form_state['values']['response']['value'])) {
    form_set_error('Response', "Response can not be empty");
  }
}

function _respond_submit($form, &$form_state) {
  global $user;

  $data = [
    'qid' => $form['#qid'],
    'response' => $form_state['values']['response']['value'],
    'updated' => REQUEST_TIME,
    'uid' => $user->uid,
  ];

  ask_mayor_update_question($data);

  if($form_state['values']['notify'][1] == 1) {
    drupal_mail(
      'ask_mayor',
      'response_notice',
      NULL,
      LANGUAGE_NONE,
      $params = ['qid' => $form['#qid']],
      $from = NULL,
      $send = TRUE
    );
  } else {
    drupal_set_message("The question has successfully been updated.");
  }
  drupal_goto('admin/ask-the-mayor');
}