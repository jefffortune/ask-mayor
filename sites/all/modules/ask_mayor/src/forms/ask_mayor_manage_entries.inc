<?php

module_load_include('inc', 'ask_mayor', 'src/ask_mayor.sql');
/**
 * This is the management of the question form.
 * Can edit or delete any questions that have had a response.
 * @return mixed
 */
function _ask_mayor_manage_entries() {
  $form = drupal_get_form('ask_mayor_manage_entries_form');
  $question_form = drupal_render($form);
  $content['question_form'] = [
    '#type' => 'markup',
    '#markup' => $question_form,
  ];

  return $content;
}

function ask_mayor_manage_entries_form($form, $form_state) {
  $headers = [t('Date'), t('Subject'), t('Actions')];
  $results = ask_mayor_get_question_rows();
  $intro = '
    <div>
        <h1>Manage Entries</h1>
        <hr>
        <h3>Manage entries that have a response.</h3>
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

      $respond_delete = l(t('Update'), "admin/ask-the-mayor/manage/$result->qid/respond");
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

      unset($question_date);
      unset($question_subject);
      unset($question_respond_delete);
    }

    $form['response']['pager'][] = [
      '#theme' => 'pager'
    ];
  } else {
    $form['response']['body'] = [
      '#markup' => '<h2 style="margin-top: 5em">There are no responses to manage.</h2>',
    ];
  }

  return $form;
}