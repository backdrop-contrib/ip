<?php
/**
 * @file
 * Actions for IP Address entities.
 */

/**
 * Callback for "Remove IP Address(es)" bulk action.
 */
function ip_remove_address_action($ip_address, &$context) {

dpm($ip_address,'$ip_address');

//   db_query('
//     DELETE FROM {ip_demerits}
//     WHERE demerit_id = :demerit_id
//     ', array(':demerit_id' => $demerit->demerit_id));
}
