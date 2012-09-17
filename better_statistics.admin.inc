<?php

/**
 * @file
 * Admin and config code for the Better Statistics module.
 */


/**
 * Makes alterations to the core Statistics configuration form.
 */
function _better_statistics_form_statistics_settings_form_alter(&$form, &$form_state, $form_id) {
  // Alter the access log settings to indicate a requirement.
  $log_description = &$form['access']['statistics_enable_access_log']['#description'];
  $log_description .= ' ' . t('Also required by the Better Statistics module.');

  // Create a fieldset for our settings.
  $form['better_statistics'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Better statistics settings'),
    '#description' => t('Select the data you would like to collect on each page load. Note that unchecking a field below will permanently delete all data collected for that field.'),
    '#weight' => 0,
    // Only show this fieldset if the accesslog is enabled.
    '#states' => array(
      'visible' => array(
        ':input[name="statistics_enable_access_log"]' => array('checked' => TRUE),
      ),
    ),
  );

  // Get all fields provided by core.
  $fields_modules = array();
  $fields_modules['statistics'] = better_statistics_get_default_fields();

  // Get a list of all modules implementing our hook and their fields.
  $fields_modules += _better_statistics_get_custom_fields_by_module();

  // Get currently active fields from the active store.
  $current = variable_get('better_statistics_fields', better_statistics_get_default_fields());

  // Create a series of checkboxes with all declared fields.
  foreach ($fields_modules as $module => $fields) {
    // Get the module name for display.
    $module_info = system_get_info('module', $module);

    // Get the fields and current defaults for this module.
    $field_set = array();
    $defaults = array();
    foreach ($fields as $field => $data) {
      // If a title is explicitly declared, use it.
      if (isset($data['views_field']['title'])) {
        $title = '<strong>' . t($data['views_field']['title']) . '</strong>';
        $field_set[$field] = $title;
      }
      else {
        $field_set[$field] = '<strong>' . $field . '</strong>';
      }

      // If help text is explicitly declared, use it.
      if (isset($data['views_field']['help'])) {
        $field_set[$field] .= ': ' . t($data['views_field']['help']);
      }
      // If not, but if a schema description is declared, use it.
      elseif (isset($data['schema']['description'])) {
        $field_set[$field] .= ': ' . t($data['schema']['description']);
      }

      // Check whether this field is currently active.
      if (isset($current[$field])) {
        $defaults[$field] = $field;
      }
    }

    // Special case: for now, don't allow disabling core accesslog fields.
    $disabled = $module == 'statistics' ? TRUE : FALSE;

    // Special case: Better Statistics started by simply adding its own fields
    // via the regular schema API. We should maintain those defaults if they're
    // actually reflected in the database.
    // @todo This should be removed once we hit a 1.2 or 1.3 release.
    if ($module == 'better_statistics' && empty($defaults)) {
      if (db_field_exists('accesslog', 'cache')) {
        $defaults['cache'] = 'cache';
      }
      if (db_field_exists('accesslog', 'user_agent')) {
        $defaults['user_agent'] = 'user_agent';
      }
    }

    // Create checkboxes for all fields declared by this module.
    $form['better_statistics'][$module] = array(
      '#type' => 'checkboxes',
      '#title' => $module_info['name'],
      '#options' => $field_set,
      '#disabled' => $disabled,
      '#default_value' => $defaults,
    );
  }

  // Add a submit handler to handle schema changes as a result of changes here.
  $form['#submit'][] = 'better_statistics_settings_form_submit';
}


/**
 * Submit handler for Better Statistics configuration settings.
 */
function _better_statistics_settings_form_submit($form, &$form_state) {
  // Get all declared fields.
  $declared = _better_statistics_get_custom_fields_by_module();

  // Compare the declared fields to what was submitted in the form.
  $customizations = array();
  foreach ($declared as $module => $fields) {
    foreach ($fields as $name => $field) {
      if ($form_state['input'][$module][$name]) {
        $customizations[$name] = $field;
      }
    }
  }

  // Get various combinations of fields for schema comparisons.
  $defaults = better_statistics_get_default_fields();
  $default_and_custom = $defaults + $customizations;
  $active = variable_get('better_statistics_fields', $defaults);

  // Compare the fields we turned up above to what currently exists.
  $fields_added = array_diff_key($default_and_custom, $active);
  $fields_removed = array_diff_key($active, $default_and_custom);

  // If fields were added, add them to the DB and the active store.
  if (!empty($fields_added)) {
    // Loop through each field.
    foreach ($fields_added as $field => $data) {
      // Verify the field is valid.
      $schema_set = isset($data['schema']) ? is_array($data['schema']) : FALSE;
      $callable = isset($data['callback']) ? is_callable($data['callback']) : FALSE;
      $field_exists = db_field_exists('accesslog', $field);

      if ($schema_set && $callable && !$field_exists) {
        // Add the field to the database.
        db_add_field('accesslog', $field, $data['schema']);

        // Add the field to the active store.
        $active += array($field => $data);

        // Log the field addition in watchdog.
        watchdog('better statistics', 'Successfully added field %field to accesslog.', array(
          '%field' => $field,
        ), WATCHDOG_NOTICE);
      }
      // Special case: support for legacy default field additions by Better
      // Statistics module. If this is detected to be a field addition but the
      // field already exists, we just need to add it to the active store.
      elseif ($field_exists) {
        // Add the field to the active store.
        $active += array($field => $data);
      }
      else {
        // Alert the failure.
        watchdog('better statistics', 'Unable to add field %field to accesslog.', array(
          '%field' => $field,
        ), WATCHDOG_WARNING);
      }
    }
  }

  // If fields were removed, remove them from the DB and the active store.
  if (!empty($fields_removed)) {
    // Loop through each missing field.
    foreach ($fields_removed as $field => $data) {
      // Verify the field exists.
      if (db_field_exists('accesslog', $field)) {
        // Drop the field from the database.
        db_drop_field('accesslog', $field);

        // Remove the field from the active store.
        unset($active[$field]);

        // Log the field removal in watchdog.
        watchdog('better statistics', 'Successfully dropped field %field from accesslog.', array(
          '%field' => $field,
        ), WATCHDOG_NOTICE);
      }
    }
  }

  // Save the active store with any changes.
  variable_set('better_statistics_fields', $active);
}


/**
 * Determines whether or not accesslog fields should be altered, and if so,
 * performs any necessary database alterations and re-saves the declared
 * fields to the active store variable.
 *
 * It is absolutely necessary that this function does all sanity checks because
 * if not, it's possible for our hook_exit() call to insert data into
 * non-existent fields.
 *
 * This function is also necessary to ensure that our schema alter is always in
 * line with what's actually declared in the database.
 */
function _better_statistics_update_fields() {
  // Attempt to get all fields, including customizations from other modules.
  $active = variable_get('better_statistics_fields', better_statistics_get_default_fields());
  $customizations = _better_statistics_get_custom_fields_by_module();
  $available_fields = array_keys(better_statistics_get_default_fields());

  // Write through updates to the non-schema portions of custom fields; also
  // check for, perform, and write through schema updates.
  foreach ($customizations as $module => $data) {
    foreach ($data as $field => $field_data) {
      // Only check for differences in pre-existing fields in the active store.
      if (isset($active[$field])) {
        // Check that the new callback is callable and write through.
        if (is_callable($field_data['callback'])) {
          $active[$field]['callback'] = $field_data['callback'];
        }

        // Write through Views API changes.
        $active[$field]['views_field'] = $field_data['views_field'];

        // Check for updates to the schema.
        if ($active[$field]['schema'] != $field_data['schema']) {
          try {
            // Change the schema.
            db_change_field('accesslog', $field, $field, $field_data['schema']);
  
            // Write through the change to the active store.
            $active[$field]['schema'] = $field_data['schema'];
  
            // Log the field change in watchdog.
            watchdog('better statistics', 'Successfully changed field %field in the accesslog.', array(
              '%field' => $field,
            ), WATCHDOG_NOTICE);
          }
          catch(Exception $e) {
            $module_info = system_get_info('module', $module);
            $message = '<em>Error</em>: Failed to update the %field field in the access log. Please make sure you are using the latest version of the @module module.';
            $options = array(
              '%field' => $field,
              '@module' => $module_info['name'],
            );

            // Set a message notifying the user.
            drupal_set_message(t($message, $options), 'error');

            // Log the failed attempt in watchdog and add more details.
            $message .= '<br /><br /><strong>Error message:</strong><br />!error';
            $options['!error'] = $e->getMessage();
            watchdog('better statistics', $message, $options, WATCHDOG_ERROR);
          }
        }
      }

      // Save this field as an available field.
      $available_fields[] = $field;
    }
  }

  // Check for fields in the active store that no longer exist.
  foreach ($active as $field => $data) {
    if (!in_array($field, $available_fields)) {
      $message = 'A recent module update has invalidated the %field field in the access log. No data has been removed at this time, but all data in the field will be lost next time Better Statistics settings are updated.';
      $options = array('%field' => $field);
      drupal_set_message(t($message, $options), 'warning');
      watchdog('better statistics', $message, $options, WATCHDOG_WARNING);
    }
  }

  // Save the active store with any changes.
  variable_set('better_statistics_fields', $active);
}


/**
 * Returns arrays of fields keyed by the module that declares them. In addition,
 * this function will attempt to apply sensible views handlers.
 *
 * @return
 *   Arrays of declared statistics fields keyed by their declaring module.
 */
function _better_statistics_get_custom_fields_by_module() {
  $declared = array();

  foreach (module_implements('better_statistics_fields') as $module) {
    $fields = module_invoke($module, 'better_statistics_fields');

    foreach ($fields as $field => &$data) {
      // Try to provide default title and help description.
      if (!isset($data['views_field']['title'])) {
        $data['views_field']['title'] = $field;
      }
      if (!isset($data['views_field']['help'])) {
        $data['views_field']['help'] = isset($data['schema']['description']) ? $data['schema']['description'] : '';
      }

      // Unless explicitly told not to, make our best guesses on Views handlers.
      if ($data['views_field']) {
        $guesses = _better_statistics_get_views_handlers($data['schema']);
        if ($guesses) {
          $data['views_field'] += $guesses;
        }
        else {
          $data['views_field'] = FALSE;
        }
      }
    }

    // Return the fields, now with Views API defaults, keyed by the module.
    $declared[$module] = $fields;
  }

  return $declared;
}


/**
 * Returns a best guess on which Views handlers should be used based on a
 * provided field schema.
 *
 * @param $schema
 *   An array representing the field's schema.
 *
 * @return
 *   An array of views handlers.
 */
function _better_statistics_get_views_handlers($schema) {
  $handlers = array();

  // Define some straightforward string handlers.
  $string_handlers = array(
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Define some straightforward numeric handlers.
  $numeric_handlers = array(
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  switch ($schema['type']) {
    case 'serial':
    case 'int':
    case 'float':
    case 'numeric':
      $handlers = $numeric_handlers;
      break;

    case 'varchar':
    case 'text':
      $handlers = $string_handlers;
      break;

    case 'blob':
      $handlers = FALSE;
      break;
  }

  return $handlers;
}
