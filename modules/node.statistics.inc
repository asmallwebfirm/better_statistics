<?php

/**
 * @file
 * Statistics API functions and hooks for the Node module.
 */


/**
 * Implements hook_better_statistics_fields().
 */
function node_better_statistics_fields() {
  $fields = array();

  // Pass all user-facing strings through t(), but always use English when first
  // declaring fields. They will be run through t() normally on output.
  $en = array('langcode' => 'en');

  // Declare a Node ID field.
  $fields['node_id'] = array(
    'schema' => array(
      'description' => 'The primary identifier for a node.',
      'type' => 'int',
      'unsigned' => TRUE,
      'not null' => FALSE,
    ),
    'callback' => 'node_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Node ID', array(), $en),
      'help' => t('The node ID on a full node page view.', array(), $en),
      'field' => array(
        'handler' => 'views_handler_field_node',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_node_nid',
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

  // Declare a node revision ID field.
  $fields['node_vid'] = array(
    'schema' => array(
      'description' => 'The node version identifier.',
      'type' => 'int',
      'unsigned' => TRUE,
      'not null' => FALSE,
    ),
    'callback' => 'node_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Revision ID', array(), $en),
      'help' => t('The revision ID of the content revision on a full node page view.', array(), $en),
      'field' => array(
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_node_vid',
        'click sortable' => TRUE,
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
  );

  // Declare a node translation ID field.
  $fields['node_tnid'] = array(
    'schema' => array(
      'description' => 'The translation set id for this node.',
      'type' => 'int',
      'unsigned' => TRUE,
      'not null' => FALSE,
    ),
    'callback' => 'node_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Node translation set ID', array(), $en),
      'help' => t('The node translation set ID on a full node page view.', array(), $en),
      'field' => array(
        'handler' => 'views_handler_field_node',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_node_nid',
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

  // Declare a node type (content type) field.
  $fields['node_type'] = array(
    'schema' => array(
      'description' => 'The content type on a full page view of a node.',
      'type' => 'varchar',
      'length' => 32,
      'not null' => FALSE,
    ),
    'callback' => 'node_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Content type', array(), $en),
      'help' => t('The content type on a full node page view.', array(), $en),
      'field' => array(
        'handler' => 'views_handler_field_node_type',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_node_type',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_node_type',
      ),
    ),
  );

  // Declare a node author field.
  $fields['node_uid'] = array(
    'schema' => array(
      'description' => 'The uid of the node author.',
      'type' => 'int',
      'not null' => TRUE,
      'default' => 0,
    ),
    'callback' => 'node_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Content author UID', array(), $en),
      'help' => t('The user who authored the content on a full node page view.', array(), $en),
      'relationship' => array(
        'title' => t('Author'),
        'help' => t('Relate content to the user who created it.'),
        'handler' => 'views_handler_relationship',
        'base' => 'users',
        'field' => 'uid',
        'label' => t('author'),
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_user_name',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
      'field' => array(
        'handler' => 'views_handler_field_user',
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
 * @see node_better_statistics_fields()
 */
function node_get_statistics_field_value($field) {
  $node = function_exists('menu_get_object') ? menu_get_object('node') : NULL;

  switch ($field) {
    case 'node_id':
      return isset($node->nid) ? $node->nid : NULL;
      break;

    case 'node_vid':
      return isset($node->vid) ? $node->vid : NULL;
      break;

    case 'node_tnid':
      return isset($node->tnid) ? $node->tnid : NULL;
      break;

    case 'node_type':
      return isset($node->type) ? $node->type : NULL;
      break;

    case 'node_uid':
      return isset($node->uid) ? $node->uid : NULL;
      break;
  }

  return NULL;
}
