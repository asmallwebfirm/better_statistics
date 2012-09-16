<?php

/**
 * @file
 * Views hooks for the Better Statistics module.
 */


/**
 * Implements hook_views_data_alter().
 *
 * Exposes the fields this module's added to the accesslog to views.
 */
function better_statistics_views_data_alter(&$data) {
  // Fetch active statistics fields.
  $current = variable_get('better_statistics_fields', better_statistics_get_default_fields());

  // For each field, if appropriate, expose the field to Views.
  foreach ($current as $field => $field_data) {
    if ($field_data['views_field']) {
      $data['accesslog'][$field] = $field_data['views_field'];
    }
  }
}
