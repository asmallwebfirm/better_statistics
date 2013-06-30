<?php

/**
 * @file
 * Definition of better_statistics_handler_field_time_interval_opt.
 */

/**
 * A field handler to provide the option for numeric fields to be displayed as
 * proper time intervals.
 */
class better_statistics_handler_field_time_interval_opt extends views_handler_field_numeric {

  /**
   * Overrides views_handler_field_numeric::option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['as_interval'] = array('default' => FALSE, 'bool' => TRUE);
    $options['granularity'] = array('default' => 2);

    return $options;
  }

  /**
   * Overrides views_handler_field_numeric::options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Checkbox to optionally render as a time interval.
    $form['as_interval'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display as time interval'),
      '#default_value' => $this->options['as_interval'],
    );

    // Dependent textfield to determine time interval granularity.
    $form['granularity'] = array(
      '#type' => 'textfield',
      '#title' => t('Granularity'),
      '#description' => t('How many different units to display in the string.'),
      '#default_value' => $this->options['granularity'],
      '#dependency' => array('edit-options-as-interval' => array(TRUE)),
    );
  }

  /**
   * Overrides views_handler_field_numeric::render().
   */
  function render($values) {
    // Render as a time interval if configured; otherwise, render normally.
    if ($this->options['as_interval']) {
      $value = $values->{$this->field_alias} / 1000;
      return format_interval($value, isset($this->options['granularity']) ? $this->options['granularity'] : 2);
    }
    else {
      return parent::render($values);
    }
  }
}
