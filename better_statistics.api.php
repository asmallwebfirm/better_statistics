<?php

/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */


/**
 * @defgroup better_statistics Better Statistics module integrations.
 *
 * Module integrations with the Better Statistics module.
 */

/**
 * @defgroup better_statistics_hooks Better Statistics' hooks
 * @{
 * Hooks that can be implemented by other modules in order to extend the Better
 * Statistics module.
 */

/**
 * Declare additional fields for possible inclusion in {accesslog}.
 *
 * This hook allows your module to expose fields for inclusion in the accesslog.
 * By default, your field will not be enabled, but a user can enable it for data
 * collection by checking its box on the Statistics configuration page.
 *
 * Once checked, Better Statistics adds your field's schema to the {accesslog}
 * with a call to db_add_field() using your declared schema. It will immediately
 * begin collecting data using the callback you define here.
 *
 * When a user unchecks your field, db_drop_field() is called and all data for
 * the field is wiped with it.
 *
 * If and when you make updates in this hook, Better Statistics will register
 * your changes on cache flushes and cron runs. Be extremely cautious when
 * modifying your field's schema; avoid it if at all possible. If detected, the
 * module will perform db_change_field() using your modified schema.
 *
 * Be careful in your use of the t() function on user-facing strings. See the
 * provided examples below.
 *
 * @return
 *   An array of information about the fields for which your module can provide
 *   data (keyed by the field name to use in the database) to be inserted into
 *   the Access Log at the end of each page request. Each field must declare at
 *   least a schema and a callback function, but can also provide more detailed
 *   information regarding Views integration. Attributes for each field are:
 *   - schema: An array representing the schema data structure used by Drupal's
 *     schema API to create your field. Modifications to this should be rare;
 *     schema changes will be registered and executed on cron and cache flushes.
 *   - callback: A function that returns data for the field. This function must
 *     take a single argument (the field name you provide), and must return data
 *     suitable (in type and length) for your field's declared schema. Note that
 *     if you can guarantee a PHP 5.3+ environment, this can be a closure.
 *   - views_field: (optional) An array of Views handlers suitable for use in a
 *     call to hook_views_data() or hook_views_data_alter(). If no information
 *     is provided, Better Statistics will try and make its best guess on how to
 *     expose your field to Views. Note you can set this to FALSE to disable
 *     Views integration for your field.
 *
 * @see _better_statistics_get_custom_fields_by_module()
 * @see schemaapi
 * @see hook_views_data()
 */
function hook_better_statistics_fields() {
  $fields = array();

  // This array key will be used like: {accesslog}.my_module_foo, so take care
  // not to collide with fields provided by other modules, but also be mindful
  // of the limits of database field name lengths. Additionally, if you don't
  // provide Views information, it will be used as the title of the field.
  $fields['my_module_foo'] = array(
    'schema' => array(
      'type' => 'varchar',
      'length' => 255,
      'not null' => FALSE,
      // If you don't provide any additional Views information, this will be
      // used when presenting admins with your field.
      'description' => 'A description about foo.',
    ),
    // This will be called like: my_module_get_values('my_module_foo');
    'callback' => 'my_module_get_values',
  );

  // Another basic example with a few more options.
  $fields['my_module_bar'] = array(
    'schema' => array(
      'type' => 'int',
      'size' => 'normal',
      // If 'not null' is set to TRUE, you must define a default value.
      'not null' => TRUE,
      'default' => 0,
      'description' => 'A description about bar.',
    ),
    'callback' => 'my_module_get_values',
    'views_field' => array(
      // This is user facing and should be passed through t(), but here, it must
      // return in English, or else it may become cached in the wrong language.
      // The string will be passed properly through t() when actually presented.
      'title' => t('Bar', array(), array('langcode' => 'en')),
      'help' => t('A description about bar for site builders.', array(), array('langcode' => 'en')),
      // Default Views handlers will be guessed based on the schema type.
    ),
  );

  // A more advanced example.
  $fields['my_module_baz'] = array(
    'schema' => array(
      'type' => 'varchar',
      'length' => 255,
      'not null' => FALSE,
      'description' => 'A description about baz.',
    ),
    // If you can assume a PHP 5.3 envrionment, you can use a closure:
    'callback' => function($field) {
      $baz = '';
      // Your code here...
      return truncate_utf8($baz, 255);
    },
    'views_field' => array(
      'title' => t('Baz', array(), array('langcode' => 'en')),
      'help' => t('A description about baz for site builders.', array(), array('langcode' => 'en')),
      // Provide specialized Views handlers for your field. Note that you are
      // responsible for ensuring these classes are loaded properly.
      'field' => array(
        'handler' => 'my_special_views_field_handler',
      ),
      'sort' => array(
        'handler' => 'my_special_sort_handler',
      ),
      'filter' => array(
        'handler' => 'my_special_filter_handler',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'my_special_argument_handler',
      ),
    ),
  );

  return $fields;
}

/**
 * @}
 */
