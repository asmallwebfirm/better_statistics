<?php

/**
 * @file
 * Statistics API functions and hooks for the User module.
 */

/**
 * Implements hook_better_statistics_fields().
 */
function user_better_statistics_fields() {
  $fields = array();

  // Pass all user-facing strings through t(), but always use English when first
  // declaring fields. They will be run through t() normally on output.
  $en = array('langcode' => 'en');

  // Declare a current user ID Field.
  $fields['current_user_id'] = array(
    'schema' => array(
      'description' => 'The user ID associated with the currently authenticated user.',
      'type' => 'int',
      'unsigned' => TRUE,
      'not null' => FALSE,
      'default' => 0,
    ),
    'callback' => 'user_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Current user ID', array(), $en),
      'help' => t('The UID of the currently authenticated user.', array(), $en),
      'field' => array(
        'handler' => 'views_handler_field_user',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_user_uid',
        'name field' => 'title',
        'numeric' => TRUE,
        'validate type' => 'nid',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
  );

  // Declare a current user name field.
  $fields['current_user_name'] = array(
    'schema' => array(
      'description' => 'The user name associated with the currently authenticated user.',
      'type' => 'varchar',
      'length' => 60,
      'not null' => FALSE,
      'default' => '',
    ),
    'callback' => 'user_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Current user name', array(), $en),
      'help' => t('The user name of the currently authenticated user.', array(), $en),
      'field' => array(
        'handler' => 'views_handler_field_user_name',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
        'title' => t('Name (raw)', array(), $en),
        'help' => t('The user or author name. This filter does not check if the user exists and allows partial matching. Does not utilize autocomplete.', array(), $en),
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
  );

  // Declare a user page mail field.
  $fields['current_user_mail'] = array(
    'schema' => array(
      'description' => 'The e-mail address associated with the currently authenticated user.',
      'type' => 'varchar',
      'length' => 254,
      'not null' => FALSE,
      'default' => '',
    ),
    'callback' => 'user_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Current user e-mail', array(), $en),
      'help' => t('The e-mail address of the currently authenticated user.', array(), $en),
      'field' => array(
        'handler' => 'views_handler_field_user_mail',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
  );

  // Declare a user page ID field.
  $fields['page_user_id'] = array(
    'schema' => array(
      'description' => 'The ID associated with a full user page view.',
      'type' => 'int',
      'unsigned' => TRUE,
      'not null' => FALSE,
      'default' => 0,
    ),
    'callback' => 'user_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Page user ID', array(), $en),
      'help' => t('The UID on a full user page view.', array(), $en),
      'field' => array(
        'handler' => 'views_handler_field_user',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_user_uid',
        'name field' => 'title',
        'numeric' => TRUE,
        'validate type' => 'nid',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
  );

  // Declare a user page name field.
  $fields['page_user_name'] = array(
    'schema' => array(
      'description' => 'The user name associated with full user page view.',
      'type' => 'varchar',
      'length' => 60,
      'not null' => FALSE,
      'default' => '',
    ),
    'callback' => 'user_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Page user name', array(), $en),
      'help' => t('The user name on a full user page view.', array(), $en),
      'field' => array(
        'handler' => 'views_handler_field_user_name',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
        'title' => t('Name (raw)', array(), $en),
        'help' => t('The user or author name. This filter does not check if the user exists and allows partial matching. Does not utilize autocomplete.', array(), $en),
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
  );

  // Declare a user page mail field.
  $fields['page_user_mail'] = array(
    'schema' => array(
      'description' => 'The user e-mail address associated with a full user page view.',
      'type' => 'varchar',
      'length' => 254,
      'not null' => FALSE,
      'default' => '',
    ),
    'callback' => 'user_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Page user e-mail', array(), $en),
      'help' => t('The user e-mail address on a full user page view.', array(), $en),
      'field' => array(
        'handler' => 'views_handler_field_user_mail',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
  );

  return $fields;
}

/**
 * Returns the stats field value for a given field.
 *
 * @param string $field
 *   The name of the field for which a value should be returned.
 *
 * @return mixed
 *   The value of the stats field specified, or NULL if none could be found.
 *
 * @see user_better_statistics_fields()
 */
function user_get_statistics_field_value($field) {
  $user = function_exists('menu_get_object') ? menu_get_object('user') : NULL;

  switch ($field) {
    case 'current_user_id':
      return isset($GLOBALS['user']->uid) ? $GLOBALS['user']->uid : NULL;
      break;

    case 'current_user_name':
      return isset($GLOBALS['user']->name) ? $GLOBALS['user']->name : NULL;
      break;

    case 'current_user_mail':
      return isset($GLOBALS['user']->mail) ? $GLOBALS['user']->mail : NULL;
      break;

    case 'page_user_id':
      return isset($user->uid) ? $user->uid : NULL;
      break;

    case 'page_user_name':
      return isset($user->name) ? $user->name : NULL;
      break;

    case 'page_user_mail':
      return isset($user->mail) ? $user->mail : NULL;
      break;
  }

  return NULL;
}
