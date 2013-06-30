<?php

/**
 * @file
 * Contains the path argument default plugin.
 */


/**
 * Contextual filter for path.
 */
class better_statistics_handler_argument_path extends views_handler_argument_string {

  function option_definition() {
    $options = parent::option_definition();

    $options['prefix'] = array('default' => '');
    $options['suffix'] = array('default' => '');
    $options['operator'] = array('default' => '=');
    $options['and_or'] = array('default' => FALSE, 'bool' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Do not allow multiple values.
    unset($form['break_phrase']);

    // Prefix field.
    $form['prefix'] = array(
      '#type' => 'textfield',
      '#title' => t('Prefix'),
      '#description' => t('Use this to prepend a string to the path you are checking.'),
      '#default_value' => $this->options['prefix'],
      '#fieldset' => 'more',
    );

    // Suffix field.
    $form['suffix'] = array(
      '#type' => 'textfield',
      '#title' => t('Suffix'),
      '#description' => t('Use this to append a string to the path you are checking.'),
      '#default_value' => $this->options['suffix'],
      '#fieldset' => 'more',
    );

    // Operator field.
    $form['operator'] = array(
      '#type' => 'select',
      '#title' => t('Operator'),
      '#description' => t('The operator used when building the condition.'),
      '#default_value' => $this->options['operator'],
      '#options' => array(
        '=' => t('Is equal to'),
        '!=' => t('Is not equal to'),
        'contains' => t('Contains'),
        'starts' => t('Starts with'),
        'not_starts' => t('Does not start with'),
        'ends' => t('Ends with'),
        'not_ends' => t('Does not end with'),
        'not' => t('Does not contain'),
      ),
      '#fieldset' => 'more',
    );

    // Bit of a hacky way to force OR functionality for contextual filters.
    $form['and_or'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use OR instead of AND logic'),
      '#default_value' => $this->options['and_or'],
      '#fieldset' => 'more',
    );
  }

  function query($group_by = FALSE) {
    $this->ensure_my_table();
    $this->value = array($this->argument);

    $placeholder = $this->placeholder();
    $prefix = empty($this->options['prefix']) ? '' : $this->options['prefix'];
    $suffix = empty($this->options['suffix']) ? '' : $this->options['suffix'];
    $where_group = empty($this->options['and_or']) ? 'AND' : 'OR';

    switch ($this->options['operator']) {
      case '=':
        $value = $prefix . $this->argument . $suffix;
        $operator = '=';
        break;

      case '!=':
        $value = $prefix . $this->argument . $suffix;
        $operator = '!=';
        break;

      case 'contains':
        $value = '%' . db_like($value = $prefix . $this->argument . $suffix) . '%';
        $operator = 'LIKE';
        break;

      case 'starts':
        $value = db_like($value = $prefix . $this->argument . $suffix) . '%';
        $operator = 'LIKE';
        break;

      case 'not_starts':
        $value = db_like($value = $prefix . $this->argument . $suffix) . '%';
        $operator = 'NOT LIKE';
        break;

      case 'ends':
        $value = '%' . db_like($value = $prefix . $this->argument . $suffix);
        $operator = 'LIKE';
        break;

      case 'not_ends':
        $value = '%' . db_like($value = $prefix . $this->argument . $suffix);
        $operator = 'NOT LIKE';
        break;

      case 'not':
        $value = '%' . db_like($value = $prefix . $this->argument . $suffix) . '%';
        $opterator = 'NOT LIKE';
        break;
    }

    $this->query->add_where_expression(0, "$this->table_alias.$this->real_field $operator $placeholder", array($placeholder => $value));
    $this->query->set_where_group($where_group, 0);
  }
}
