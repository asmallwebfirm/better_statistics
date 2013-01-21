<?php

/**
 * @file
 * Statistics API functions and hooks for the Better Statistics module.
 */


/**
 * Implements hook_better_statistics_fields().
 */
function better_statistics_better_statistics_fields() {
  $fields = array();

  // Pass all user-facing strings through t(), but always use English when first
  // declaring fields. They will be run through t() normally on output.
  $en = array('langcode' => 'en');

  // Declare a cache status field.
  $fields['cache'] = array(
    'schema' => array(
      'type' => 'varchar',
      'length' => 128,
      'not null' => FALSE,
      'description' => 'Cache hit, miss, or not applicable.',
    ),
    'callback' => 'better_statistics_get_field_value',
    'views_field' => array(
      'title' => t('Cache status', array(), $en),
      'help' => t('The cache status of the page (HIT, MISS, or NULL).', array(), $en),
    ),
  );

  // Declare a user agent field.
  $fields['user_agent'] = array(
    'schema' => array(
      'type' => 'varchar',
      'length' => 255,
      'not null' => FALSE,
      'description' => 'User-agent string used on the request.',
    ),
    'callback' => 'better_statistics_get_field_value',
    'views_field' => array(
      'title' => t('User-agent', array(), $en),
      'help' => t('User-agent string of the user who visited your page.', array(), $en),
    ),
  );

  // Declare a peak memory field.
  $fields['peak_memory'] = array(
    'schema' => array(
      'type' => 'int',
      'size' => 'normal',
      'not null' => TRUE,
      'default' => 0,
      'unsigned' => TRUE,
      'description' => 'Peak memory in bytes allocated for the request.',
    ),
    'callback' => 'memory_get_peak_usage',
    'views_field' => array(
      'title' => t('Peak memory', array(), $en),
      'help' => t('Size in bytes of the peak memory allocated for the request.', array(), $en),
    ),
  );

  return $fields;
}


/**
 * Returns a value to be inserted into the accesslog based on a field name
 * provided. This handles Drupal Core's values as well as our own.
 *
 * @param $field
 *   The name of the field for which to return data.
 *
 * @return
 *   The data to be inserted into the accesslog for the provided field.
 */
function better_statistics_get_field_value($field) {
  switch ($field) {
    case 'title':
      return truncate_utf8(strip_tags(drupal_get_title()), 255);

    case 'path':
      return truncate_utf8($_GET['q'], 255);

    case 'url':
      return isset($_SERVER['HTTP_REFERER']) ? $_SERVER['HTTP_REFERER'] : '';

    case 'hostname':
      return ip_address();

    case 'uid':
      global $user;
      return $user->uid;

    case 'sid':
      return session_id();

    case 'timer':
      return (int) timer_read('page');

    case 'timestamp':
      return REQUEST_TIME;

    case 'cache':
      $cached = NULL;
      $cache_status = better_statistics_served_from_cache();
      if ($cache_status === TRUE) {
        $cached = 'HIT';
      }
      elseif ($cache_status === FALSE) {
        $cached = 'MISS';
      }
      return $cached;

    case 'user_agent':
      return truncate_utf8($_SERVER['HTTP_USER_AGENT'], 255);
  }
}
