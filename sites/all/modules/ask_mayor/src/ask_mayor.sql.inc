<?php

function ask_mayor_save_question(array $data) {
  $return = db_insert('ask_mayor')
    ->fields($data)
    ->execute();
  if (!$return) {
    drupal_set_message('Form Failed to submit, please try again.', 'error');
  }
  return $return;
}

function ask_mayor_update_question(array $data) {
  $return = drupal_write_record('ask_mayor', $data, 'qid');
  if(!$return) {
    drupal_set_message('Form Failed to update record, please try again.', 'error');
  }
  return $return;
}

function ask_mayor_get_question_rows() {
  try {
    $return = db_select('ask_mayor', 'r')
      ->extend('PagerDefault')
      ->fields('r', ['qid','created', 'subject', 'response'])
      ->isNotNull('r.response')
      ->limit(25)
      ->execute()
      ->fetchAll();
    return $return;
  } catch (Exception $e) {
    watchdog('ask-mayor', $e, NULL, WATCHDOG_CRITICAL);
  }
  return FALSE;
}

function ask_mayor_get_needs_response_rows() {
  try {
    $return = db_select('ask_mayor', 'r')
      ->extend('PagerDefault')
      ->fields('r', ['qid','created', 'subject', 'response'])
      ->isNull('r.response')
      ->limit(25)
      ->execute()
      ->fetchAll();
    return $return;
  } catch (Exception $e) {
    watchdog('ask-mayor', $e, NULL, WATCHDOG_CRITICAL);
  }
  return FALSE;
}

function ask_mayor_get_subject($qid) {
  try {
    $return = db_select('ask_mayor', 's')
      ->fields('s', ['subject'])
      ->condition('qid', $qid)
      ->execute()
      ->fetchAssoc();
    if ($return['subject']) {
      return $return['subject'];
    }
  } catch (Exception $e) {
    watchdog('ask-mayor', $e, NULL, WATCHDOG_ALERT);
  }
  return FALSE;
}

function ask_mayor_load_question($qid) {
  try {
    $return = db_select('ask_mayor', 's')
      ->fields('s')
      ->condition('qid', $qid)
      ->execute()
      ->fetchAssoc();
    if($return) {
      return $return;
    }
  } catch (Exception $e) {
    watchdog('ask-mayor', $e, NULL, WATCHDOG_ALERT);
  }
  return FALSE;
}

function ask_mayor_load_all_question($per_page) {
  try {
    $return = db_select('ask_mayor', 's')
      ->extend('PagerDefault')
      ->fields('s')
      ->isNotNull('s.response')
      ->limit($per_page)
      ->orderBy("s.qid", "DESC")
      ->execute()
      ->fetchAll();
    if($return) {
      return $return;
    }
  } catch (Exception $e) {
    watchdog('ask-mayor', $e, NULL, WATCHDOG_ALERT);
  }
  return FALSE;
}

function ask_mayor_delete_record($qid) {
  try {
    db_delete('ask_mayor')
      ->condition('qid', $qid)
      ->execute();
  } catch (Exception $e) {
    watchdog('ask-mayor', $e, NULL, WATCHDOG_ALERT);
  }
}

function ask_mayor_count_year($year) {
  try {
    $return = db_select('ask_mayor', 'y')
      ->fields('y', ['year'])
      ->condition('year', $year)
      ->execute();
    return $return->rowCount();
  } catch (Exception $e) {
    watchdog('ask-mayor', $e, NULL, WATCHDOG_ALERT);
  }
  return FALSE;
}

function ask_mayor_get_all_year($year) {
  try {
    $return = db_select('ask_mayor', 'y')
      ->fields('y', ['qid', 'subject', 'question', 'created'])
      ->condition('year', $year)
      ->execute()
      ->fetchAll();

    return $return;
  } catch (Exception $e) {
    watchdog('ask-mayor', $e, NULL, WATCHDOG_ALERT);
  }
  return FALSE;
}

function ask_mayor_get_distinct_years() {
  try {
    $return = db_select('ask_mayor', 'd')
      ->distinct()
      ->fields('d', ['year'])
      ->groupBy('d.year')
      ->orderBy("d.year", "DESC")
      ->execute()
      ->fetchAll();
    return $return;
  } catch (Exception $e) {
    watchdog('ask-mayor', $e, NULL, WATCHDOG_ALERT);
  }
  return FALSE;
}

