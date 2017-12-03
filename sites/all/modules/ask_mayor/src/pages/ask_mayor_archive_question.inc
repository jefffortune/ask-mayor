<?php

function _ask_mayor_archive_question($param) {
  $content = [];
  if ($param) {
    drupal_set_title(t($param . ' Questions'));
    $rows = [];
    $rows_query = ask_mayor_get_all_year($param);
    foreach ($rows_query as $row) {
      $item = "<h2>$row->subject</h2>";
      $item .= "<p>$row->question</p>";
      $item .= '<span>Asked: ' . format_date($row->created, 'custom', 'd/M/y') . '</span>';
      $rows[] = l($item, 'ask-the-mayor/view-question/' . $row->qid, ['query' => drupal_get_destination(), 'html' => TRUE]);
    }
    $content = [
      'rows' => $rows,
    ];
  } else {
    drupal_not_found();
  }

  return theme('ask_mayor_archive', $content);
}