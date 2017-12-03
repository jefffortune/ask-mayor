<?php

module_load_include('inc', 'ask_mayor', 'src/ask_mayor.sql');
/**
 * callback for the view a question page.
 * @param $param
 * @return string
 */
function _ask_mayor_view_question($param) {

  $content = [];
  if ($param) {
    $content = ask_mayor_load_question($param[0]);
  } else {
    drupal_not_found();
  }

  return theme('ask_mayor_view_page', $content);
}