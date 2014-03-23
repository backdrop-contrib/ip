<?php

/**
 * @file
 * Contains the ip_views_handler_field_long2ip class.
 */

/**
 * A handler to provide proper displays IP Long values
 */
class ip_views_handler_field_long2ip extends views_handler_field {
  // @TODO option to link or not to address manage page
  function render($values) {
    $value = $this->get_value($values);
    $long2ip = !empty($value) ? long2ip($value) : NULL;
    return !empty($long2ip) ? l($long2ip, 'admin/people/ip', array('query' => array('ip' => array('value' => $long2ip)))) : NULL;
  }
}
