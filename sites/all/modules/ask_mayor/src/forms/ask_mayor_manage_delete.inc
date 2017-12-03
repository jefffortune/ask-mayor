<?php
module_load_include('inc', 'ask_mayor', 'src/ask_mayor.sql');

/**
 * Callback for deleting a question from the system.
 * @param null $param
 */
function _ask_mayor_manage_delete($param = NULL) {
  if ($param) {
    $subject = ask_mayor_get_subject($param);
    ask_mayor_delete_record($param);
    if ($subject) {
      drupal_set_message("Subject: $subject | was deleted from ask mayor record.");
    } else {
      drupal_set_message('Error occurred while deleting', 'error');
    }
  } else {
    drupal_set_message("Error occurred while trying to delete a message", 'error');
  }
  drupal_goto('admin/ask-the-mayor');
}