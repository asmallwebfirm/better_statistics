<?php

/**
 * @file
 * Drupal hooks and functions for the Better Statistics module's AJAX features.
 */


/**
 * Handles Better Statistics AJAX POST requests.
 *
 * @param $type
 *   The type of statistics data that is being handled; this is used to call a
 *   hook where the payload will actually be processed.
 */
function better_statistics_ajax_handler($type) {
  if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // Extract the payload from the request.
    $payload = drupal_json_decode(file_get_contents('php://input'));

    // Load all Statistics API includes to ensure implementations are loaded.
    better_statistics_load_active_incs();

    // Invoke hooks of the form hook_better_statistics_ajax and the more verbose
    // hook_better_statistics_ajax_TYPE, so Statistics API implementors can
    // implement their own functionality.
    module_invoke_all('better_statistics_ajax', $type, $payload);
    module_invoke_all('better_statistics_ajax_' . $type, $payload);

    // Prevent this callback from creating an additional log entry.
    global $conf;
    $conf['statistics_enable_access_log'] = BETTER_STATISTICS_ACCESSLOG_DISABLED;
  }
}
