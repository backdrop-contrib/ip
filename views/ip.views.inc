<?php

/**
 * @file
 * Provides ip_tracker view fields and filters.
 */

/**
 * Implements hook_views_data().
 */
function ip_views_data() {
  // Table: IP tracker:
  $data['ip_tracker']['table']['group'] = t('User IP');
  $data['ip_tracker']['table']['base'] = array(
    'field' => 'uid',
    'title' => t('User IP table'),
    'help' => t('Maps to uid in user table.'),
    'weight' => -10,
  );
  $data['ip_tracker']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  // uid field
  $data['ip_tracker']['uid'] = array(
    'title' => t('User id'),
    'help' => t('Unique id of user'),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('User uid'),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  // IP field
  $data['ip_tracker']['ip'] = array(
    'title' => t('IP Address'),
    'help' => t('IP address of user.'),
    'field' => array(
      'handler' => 'ip_views_handler_field_long2ip',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'ip_views_handler_filter_ip2long',
    ),
    'argument' => array(
      'handler' => 'ip_views_handler_argument_ip2long',
    ),
  );

  // Visit
  $data['ip_tracker']['visits'] = array(
    'title' => t('Visits'),
    'help' => t('Total visits'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  // First visit
  $data['ip_tracker']['first_visit'] = array(
    'title' => t('First visit'),
    'help' => t('First visit: registration/login.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  // Last visit
  $data['ip_tracker']['last_visit'] = array(
    'title' => t('Last visit'),
    'help' => t('Last visit: registration/login.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  // Last visit
  $data['ip_tracker']['user_count'] = array(
    'title' => t('User count'),
    'help' => t('User count.'),
    'field' => array(
      'handler' => 'ip_views_handler_field_user_count',
      'click sortable' => FALSE,
    ),
  );
  
  return $data;
}
