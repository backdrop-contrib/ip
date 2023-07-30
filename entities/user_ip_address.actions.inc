<?php
/**
 * @file
 * Actions for User IP Address entities.
 */

/**
 * Callback for "Remove User IP Address(es)" bulk action.
 */
function user_ip_address_remove_action($user_ip_address, &$context) {
  db_query('
    DELETE FROM {ip_tracker}
    WHERE ip_tracker_id = :ip_tracker_id
    ', array(':ip_tracker_id' => $user_ip_address->ip_tracker_id));
}
