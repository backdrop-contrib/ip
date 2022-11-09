<?php
/**
 * @file
 * IP Demerits administrative functions.
 */

/**
 * Return settings form for IP Demerits module.
 */
function ip_demerits_settings_form($form, &$form_state) {
  $form['#config'] = 'ip_demerits.settings';
  $config = config('ip_demerits.settings');

  $form[] = array(
    '#type' => 'help',
    '#markup' => t('Configure demerits for user actions and actions based on user demerits.'),
  );

  $form['points'] = array(
    '#type' => 'fieldset',
    '#title' => t('Points'),
    '#description' => t('Enter the demerit points to award automatically for each user action.'),
  );
  $form['points']['points_manual_default'] = array(
    '#type' => 'number',
    '#title' => t('Manual default'),
    '#description' => t('Default points for a manual demerit'),
    '#min' => 0,
    '#step' => 1,
    '#default_value' => (int) $config->get('points_manual_default'),
  );
  $form['points']['points_user_blocked'] = array(
    '#type' => 'number',
    '#title' => t('User blocked'),
    '#description' => t('Points for demerit when a user account has been blocked'),
    '#min' => 0,
    '#step' => 1,
    '#default_value' => (int) $config->get('points_user_blocked'),
  );
  $form['points']['points_user_deleted'] = array(
    '#type' => 'number',
    '#title' => t('User deleted'),
    '#description' => t('Points for demerit when a user account has been deleted'),
    '#min' => 0,
    '#step' => 1,
    '#default_value' => (int) $config->get('points_user_deleted'),
  );

/*
  $form['take_actions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Actions'),
    '#description' => t('Enter the threshold points for demerit-based actions.'),
  );
  $form['take_actions']['threshold_block_ip'] = array(
    '#type' => 'number',
    '#title' => t('Block IP threshold'),
    '#description' => t('Enter the threshold demerits to block an IP address.'),
    '#min' => 0,
    '#step' => 1,
    '#default_value' => (int) $config->get('threshold_block_ip'),
  );
 */

  return system_settings_form($form);
}

/**
 * Assign a demerit to a user or IP address.
 */
function ip_demerits_demerits_form($form, &$form_state) {

  $form['assign'] = array(
    '#type' => 'fieldset',
    '#title' => t('Assign a demerit'),
    '#description' => t('Assign a demerit to a user/IP combination.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['assign']['uid'] = array(
    '#type' => 'number',
    '#title' => t('User ID'),
    '#description' => t('Enter the UID. TODO: replace with a user autocomplete.'),
    '#min' => 0,
    '#step' => 1,
  );
  $form['assign']['ip'] = array(
    '#type' => 'textfield',
    '#title' => t('IP address'),
    '#description' => t('Enter the IP address. TODO: replace with autocomplete based on IP addresses from the user.'),
  );
  $form['assign']['points'] = array(
    '#type' => 'number',
    '#title' => t('Points'),
    '#description' => t('Enter the number of points to assign to the demerit.'),
    '#min' => 1,
    '#step' => 1,
    '#default_value' => config_get('ip_demerits.settings', 'points_manual_default'),
  );
  $form['assign']['reason'] = array(
    '#type' => 'textfield',
    '#title' => t('Reason'),
    '#description' => t('Enter a short reason for the demerit.'),
  );
  $form['assign']['actions'] = array('#type' => 'actions');
  $form['assign']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Assign demerit'),
  );

  $form[] = array(
    '#markup' => views_embed_view('ip_demerits', 'default'),
  );

  return $form;
}

/**
 * Validation function for assigning a demerit to a user or IP address.
 */
function ip_demerits_demerits_form_validate($form, &$form_state) {
  $ip = $form_state['values']['ip'];
  $ip_parts = explode('.', $ip);
  $bad_ip = count($ip_parts) != 4;
  foreach ($ip_parts as $part) {
    if (empty($part) || !is_numeric($part) || $part < 0 || $part > 255 || $part != round($part)) {
      $bad_ip = TRUE;
      break;
    }
  }
  if ($bad_ip) {
    form_set_error('ip', t('%ip is not a valid IP address.', array('%ip' => $ip)));
  }
}

/**
 * Submission function for assigning a demerit to a user or IP address.
 */
function ip_demerits_demerits_form_submit($form, &$form_state) {
  $uid = (int) $form_state['values']['uid'];
  $ip = $form_state['values']['ip'];
  $points = $form_state['values']['points'];
  $reason = $form_state['values']['reason'];
  ip_demerits_assign(ip2long($ip), $uid, $points, $reason);
  $account = user_load($uid);
  if ($uid && $account) {
    backdrop_set_message(format_plural($points, 'A demerit of @points point has been assigned to user %name and IP address %ip for the reason %reason.', 'A demerit of @points points has been assigned to user %name and IP address %ip for the reason %reason.', array(
      '@points' => $points,
      '%name' => $name,
      '%ip' => $ip,
      '%reason' => $reason)));
  }
  else {
    backdrop_set_message(format_plural($points, 'A demerit of @points point has been assigned to IP address %ip for the reason %reason.', 'A demerit of @points points has been assigned to IP address %ip for the reason %reason.', array(
      '@points' => $points,
      '%ip' => $ip,
      '%reason' => $reason)));
  }
}

/**
 * Display form for demerits and details for an individual IP address
 */
function ip_demerits_ip_details_form($form, &$form_state, $ip) {
  backdrop_set_title(t('IP address details for @ip', array('@ip' => $ip)));

  // Users
  $form[] = array(
    '#markup' => t('Users'),
    '#prefix' => '<h2>',
    '#suffix' => '</h2>',
  );
  $total_users = (int) db_query('
    SELECT COUNT(uid)
    FROM {ip_tracker}
    WHERE ip = :ip
    ', array(':ip' => ip2long($ip)))
    ->fetchField();
  $form[] = array(
    '#type' => 'help',
    '#markup' => $total_users ? format_plural($total_users, 'This address has been used by 1 user.', 'This address has been used by @num users.', array('@num' => $total_users)) : t('This address has been used by no users.'),
  );
  $form[] = array(
    '#markup' => views_embed_view('ip_address_users_by_ip', 'default', $ip),
  );

  // Demerits
  $form[] = array(
    '#markup' => t('Demerits'),
    '#prefix' => '<h2>',
    '#suffix' => '</h2>',
  );
  $total_points = (int) db_query('
    SELECT points
    FROM {ip_demerits_ip_totals}
    WHERE ip = :ip
    ', array(':ip' => ip2long($ip)))
    ->fetchField();
  $form[] = array(
    '#type' => 'help',
    '#markup' => $total_points ? format_plural($total_points, 'This address has received 1 demerit point.', 'This address has received @points demerit points.', array('@points' => $total_points)) : t('This address has received no demerits.'),
  );
  $form[] = array(
    '#markup' => views_embed_view('ip_demerits', 'by_ip', $ip),
  );

  return $form;
}
