<?php

/**
 * @file
 * Views hooks for the Better Statistics module.
 */


/**
 * Implements hook_views_data_alter().
 *
 * Exposes selected fields in the accesslog to Views.
 */
function better_statistics_views_data_alter(&$data) {
  // Fetch active statistics fields.
  $current = variable_get('better_statistics_fields', better_statistics_get_default_fields());

  // For each field, if appropriate, expose the field to Views.
  foreach ($current as $field => $field_data) {
    if ($field_data['views_field']) {
      // Properly translate the title.
      if (isset($field_data['views_field']['title'])) {
        $field_data['views_field']['title'] = t($field_data['views_field']['title']);
      }

      // Properly translate the help/description.
      if (isset($field_data['views_field']['help'])) {
        $field_data['views_field']['help'] = t($field_data['views_field']['help']);
      }

      // Properly translate any labels.
      foreach ($field_data['views_field'] as &$handler) {
        if (is_array($handler) && isset($handler['label'])) {
          $handler['label'] = t($handler['label']);
        }
      }

      // Make views aware of the field in the accesslog.
      $data['accesslog'][$field] = $field_data['views_field'];
    }
  }

  // Add a contextual filter handler for the path.
  $data['accesslog']['path']['argument']['handler'] = 'better_statistics_handler_argument_path';

  // Add float to timer to expose rounding options; alter the field handler to
  // our custom handler to allow the timer to be displayed as a time interval.
  $data['accesslog']['timer']['field']['float'] = TRUE;
  $data['accesslog']['timer']['field']['handler'] = 'better_statistics_handler_field_time_interval_opt';
}


/**
 * Implements hook_views_data().
 */
function better_statistics_views_data() {
  $data['blocked_ips']['table']['group'] = t('Blocked IPs');

  // For other base tables, explain how we join.
  $data['blocked_ips']['table']['join'] = array(
    'accesslog' => array(
      'field' => 'ip',
      'left_field' => 'hostname',
    ),
  );

  // blocked_ips.iid
  $data['blocked_ips']['iid'] = array(
    'title' => t('Blocked IP ID'),
    'help' => t('The unique ID of the IP block.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'iid',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // blocked_ips.ip
  $data['blocked_ips']['ip'] = array(
    'title' => t('Block IP'),
    'help' => t('A link to block or unblock the IP from the site.'),
    'field' => array(
      'handler' => 'better_statistics_handler_field_block_ip',
      'click sortable' => FALSE,
    ),
  );

  return $data;
}


/**
 * Implements hook_views_pre_render().
 */
function better_statistics_views_pre_render(&$view) {
  // Replace %accesslog_interval with a properly formatted interval in titles.
  $title = $view->get_title();
  $interval = format_interval(variable_get('statistics_flush_accesslog_timer', 259200));
  $view->set_title(format_string($title, array('%accesslog_interval' => $interval)));
}
