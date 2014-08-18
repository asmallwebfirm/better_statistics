<?php

/**
 * @file
 * Statistics API functions and hooks for the Taxonomy module.
 */


/**
 * Implements hook_better_statistics_fields().
 */
function taxonomy_better_statistics_fields() {
  $fields = array();

  // Pass all user-facing strings through t(), but always use English when first
  // declaring fields. They will be run through t() normally on output.
  $en = array('langcode' => 'en');

  // Declare a taxonomy page term ID field.
  $fields['taxonomy_page_tid'] = array(
    'schema' => array(
      'description' => 'The primary identifier for a taxonomy term (page view).',
      'type' => 'int',
      'unsigned' => TRUE,
      'not null' => FALSE,
    ),
    'callback' => 'taxonomy_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Taxonomy term page term ID', array(), $en),
      'help' => t('The taxonomy term ID on a full term page view.', array(), $en),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_taxonomy',
        'name field' => 'name',
        'zero is null' => TRUE,
      ),
      'filter' => array(
        'title' => t('Term', array(), $en),
        'help' => t('Taxonomy term chosen from autocomplete or select widget.', array(), $en),
        'handler' => 'views_handler_filter_term_node_tid',
        'hierarchy table' => 'taxonomy_term_hierarchy',
        'numeric' => TRUE,
      ),
    ),
  );

  // Declare a taxonomy page term name field.
  $fields['taxonomy_page_term_name'] = array(
    'schema' => array(
      'description' => 'The term name for a taxonomy term page view.',
      'type' => 'varchar',
      'length' => 255,
      'not null' => FALSE,
      'default' => '',
    ),
    'callback' => 'taxonomy_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Taxonomy term page term name', array(), $en),
      'help' => t('The taxonomy term name on a full term page view.', array(), $en),
      'field' => array(
        'handler' => 'views_handler_field_taxonomy',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
        'help' => t('Taxonomy term name.', array(), $en),
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
        'help' => t('Taxonomy term name.', array(), $en),
        'many to one' => TRUE,
        'empty field name' => t('Uncategorized', array(), $en),
      ),
    ),
  );

  // Declare a taxonomy page vocabulary ID field.
  $fields['taxonomy_page_vid'] = array(
    'schema' => array(
      'description' => 'The taxonomy vocabulary ID for a taxonomy term page view.',
      'type' => 'int',
      'unsigned' => TRUE,
      'not null' => FALSE,
      'default' => 0,
    ),
    'callback' => 'taxonomy_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Taxonomy term page term VID', array(), $en),
      'help' => t('The taxonomy term vocabulary ID on a full term page view', array(), $en),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_vocabulary_vid',
        'name field' => 'name',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
  );

  // Declare a taxonomy page vocabulary machine name field.
  $fields['taxonomy_page_vocab_machine_name'] = array(
    'schema' => array(
      'description' => 'The taxonomy vocabulary machine name for a taxonomy term page view.',
      'type' => 'varchar',
      'length' => 255,
      'not null' => FALSE,
      'default' => '',
    ),
    'callback' => 'taxonomy_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Taxonomy term page vocabulary machine name', array(), $en),
      'help' => t('The taxonomy term vocabulary machine name on a full term page view', array(), $en),
      'field' => array(
        'help' => t('Machine-Name of the vocabulary a term is a member of. This will be the vocabulary that whichever term the "Taxonomy: Term" field is; and can similarly cause duplicates.', array(), $en),
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'help' => t('Filter the results of "Taxonomy: Term" to a particular vocabulary.', array(), $en),
        'handler' => 'views_handler_filter_vocabulary_machine_name',
      ),
      'argument' => array(
        'help' => t('Filter the results of "Taxonomy: Term" to a particular vocabulary.', array(), $en),
        'handler' => 'views_handler_argument_vocabulary_machine_name',
      ),
    ),
  );

  // Declare a taxonomy referenced tids field.
  $fields['taxonomy_tids'] = array(
    'schema' => array(
      'description' => 'Comma separated taxonomy term ids referenced by the node being viewed.',
      'type' => 'varchar',
      'length' => 255,
      'not null' => FALSE,
      'default' => '',
    ),
    'callback' => 'taxonomy_get_statistics_field_value',
    'views_field' => array(
      'title' => t('Referenced taxonomy terms', array(), $en),
      'help' => t('Comma separated list of term IDs referenced by the entity being viewed.', array(), $en),
      'field' => array(
        'handler' => 'views_handler_field_string',
        'click sortable' => FALSE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
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
function taxonomy_get_statistics_field_value($field) {
  $term = function_exists('menu_get_object') ? menu_get_object('taxonomy_term', 2) : NULL;

  switch ($field) {
    case 'taxonomy_page_tid':
      return isset($term->tid) ? $term->tid : NULL;
      break;

    case 'taxonomy_page_term_name':
      return isset($term->name) ? $term->name : NULL;
      break;

    case 'taxonomy_page_vid':
      return isset($term->vid) ? $term->vid : NULL;
      break;

    case 'taxonomy_page_vocab_machine_name':
      return isset($term->vocabulary_machine_name) ? $term->vocabulary_machine_name : NULL;
      break;

    case 'taxonomy_tids':
      $node = function_exists('menu_get_object') ? menu_get_object('node') : NULL;
      if (isset($node->type)) {
        return implode(',', better_statistics_get_entity_terms('node', $node->type, $node));
      }
      break;
  }

  return NULL;
}

/**
 * Fetch all taxonomy term IDs from an entity.
 *
 * All fields of field type "taxonomy_term_reference" will be included.
 *
 * @param string $entity_type
 *   The type of entity.
 *
 * @param string $bundle
 *   The entity bundle of the given entity.
 *
 * @param object $entity
 *   Actual entity object to process.
 *
 * @return array
 *   Array of tids.
 */
function better_statistics_get_entity_terms($entity_type, $bundle, $entity) {
  // Ensure all functions are loaded.
  if (!function_exists('field_info_field_map') || !function_exists('field_get_items')) {
    return array();
  }

  // Use very lightweight field info list to find relevant fields.
  $tids = array();
  foreach (field_info_field_map() as $field_name => $field_info) {
    if ($field_info['type'] != 'taxonomy_term_reference') {
      continue;
    }
    if (array_key_exists($entity_type, $field_info['bundles'])) {
      if (in_array($bundle, $field_info['bundles'][$entity_type])) {
        if (isset($entity->{$field_name})) {
          // Collect terms from fields for return.
          $values = field_get_items($entity_type, $entity, $field_name);
          foreach ((array) $values as $term_array) {
            if (!empty($term_array['tid'])) {
              $tids[] = $term_array['tid'];
            }
          }
        }
      }
    }
  }

  return $tids;
}
