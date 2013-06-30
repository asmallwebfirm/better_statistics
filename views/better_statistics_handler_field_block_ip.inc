<?php

/**
 * @file
 * Views field handler to supply a block/unblock IP link.
 */


/**
 * A field handler to provide block/unblock IP operation links.
 */
class better_statistics_handler_field_block_ip extends views_handler_field {

  /**
   * Don't bother showing this link to those without the proper permissions.
   */
  function access() {
    return user_access('block IP addresses');
  }

  /**
   * Ensure the IP and IID of the blocked hostname is available.
   */
  function pre_query() {
    parent::pre_query();

    $this->add_additional_fields(array(
      array(
        'table' => 'blocked_ips',
        'field' => 'iid',
      ),
      array(
        'table' => 'accesslog',
        'field' => 'hostname',
      ),
    ));
  }

  /**
   * Based on the IID, IP, and UID, display a block or unblock operation.
   */
  function render($values) {
    $iid = $values->blocked_ips_iid;
    $ip = $values->accesslog_hostname;
    $uid = isset($values->users_accesslog_uid) ? $values->users_accesslog_uid : 0;

    // We don't block IPs of users.
    if ($uid) {
      return NULL;
    }
    // If an IID exists, offer an unblock link.
    elseif (!empty($iid)) {
      $title = t('unblock IP address');
      $url = 'admin/config/people/ip-blocking/delete/' . $iid;
    }
    // Otherwise, offer a block link.
    else {
      $title = t('block IP address');
      $url = 'admin/config/people/ip-blocking/' . $ip;
    }

    return l($title, $url, array('query' => drupal_get_destination()));
  }
}