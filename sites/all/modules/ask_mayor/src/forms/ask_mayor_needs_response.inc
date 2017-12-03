<?php

module_load_include('inc', 'ask_mayor', 'src/ask_mayor.sql');

/**
 * Needs Response form callback
 * @return mixed
 */
function _ask_mayor_needs_response() {
  $form = drupal_get_form('ask_mayor_needs_response_form');
  $question_form = drupal_render($form);
  $content['question_form'] = [
    '#type' => 'markup',
    '#markup' => $question_form,
  ];

  return $content;
}

/**
 * Needs a response form
 * @param $form
 * @param $form_state
 * @return mixed
 */
function ask_mayor_needs_response_form($form, $form_state) {
  $headers = [t('Date'), t('Subject'), t('Actions')];
  $results = ask_mayor_get_needs_response_rows();
  $intro = '
    <div>
        <h1>Questions</h1>
        <hr>
        <h3>Manage the waiting questions with a response.</h3>
    </div>
  ';

  $form['response']['intro'] = [
    '#markup' => $intro,
  ];

  if($results) {
    $form['response']['table'] = [
      '#prefix' => '<div id="response-table" style="margin-top: 4em">',
      '#suffix' => '</div>',
      '#tree' => TRUE,
      '#theme' => 'table',
      '#header' => $headers,
      '#rows' => [],
    ];

    foreach ($results as $result) {
      $question_date = [
        '#id' => 'date' . $result->qid,
        '#markup' => format_date($result->created,'custom', 'd F Y')
      ];

      $question_subject = [
        '#id' => 'subject' . $result->qid,
        '#markup' => $result->subject,
      ];

      $respond_delete = l(t('Respond'), "admin/ask-the-mayor/manage/$result->qid/respond");
      $respond_delete .= ' | ';
      $respond_delete .= l(t('Delete'), "admin/ask-the-mayor/manage/$result->qid/delete");
      $question_respond_delete = [
        '#id' => 'rnd' . $result->qid,
        '#markup' => $respond_delete,
      ];

      $form['response']['table']['#rows'][] = [
        ['data' => &$question_date],
        ['data' => &$question_subject],
        ['data' => &$respond_delete],
      ];
      // unset variables that had relationships to pointers
      unset($question_date);
      unset($question_subject);
      unset($respond_delete);
      unset($question_respond_delete);
    }

    $form['response']['pager'][] = [
      '#theme' => 'pager'
    ];
  } else {
    $form['response']['body'] = [
      '#markup' => '<h2 style="margin-top: 5em">There are no questions waiting for response.</h2>',
    ];
  }

  return $form;
}