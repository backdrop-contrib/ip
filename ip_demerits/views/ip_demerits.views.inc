<?php
/**
 * @file
 * Provides ip_demerits view fields and filters.
 */

/**
 * Implements hook_views_data().
 */
function ip_demerits_views_data() {
  $data = array();

  //
  // Table: Individual demerits
  //
  $data['ip_demerits']['table']['group'] = t('IP demerits');
  $data['ip_demerits']['table']['base'] = array(
    'field' => 'ip',
    'title' => t('IP demerits'),
    'help' => t('IP demerits'),
  );

  // IP field
  $data['ip_demerits']['ip'] = array(
    'title' => t('IP Address'),
    'help' => t('IP address of user.'),
    'relationship' => array(
      'base' => 'ip_tracker',
      'field' => 'ip',
      'handler' => 'views_handler_relationship',
      'label' => t('IP address'),
    ),
    'field' => array(
      'handler' => 'Long2IpField',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'Ip2LongFilter',
    ),
    'argument' => array(
      'handler' => 'Ip2LongArgument',
    ),
  );

  // Uid field
  $data['ip_demerits']['uid'] = array(
    'title' => t('User id'),
    'help' => t('Unique id of user'),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('User uid'),
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Points
  $data['ip_demerits']['points'] = array(
    'title' => t('Points'),
    'help' => t('Points for this demerit'),
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

  // Date
  $data['ip_demerits']['date'] = array(
    'title' => t('Date'),
    'help' => t('Date that demerits were assigned'),
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

  // Reason
  $data['ip_demerits']['reason'] = array(
    'title' => t('Reason'),
    'help' => t('Reason for assignment of demerits'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // User relationship: users -> ip_demerits.
  $data['users']['ip_demerits'] = array(
    'title' => t('IP demerits'),
    'help' => t('IP demerits (users)'),
    'relationship' => array(
      'base' => 'ip_demerits',
      'base field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('IP demerits'),
      'title' => t('Referenced demerit'),
      'help' => t('Demerit reference by this user'),
    ),
  );

  //
  // Table: Total points by IP
  //
  $data['ip_demerits_ip_totals']['table']['group'] = t('IP demerits IP totals');
  $data['ip_demerits_ip_totals']['table']['base'] = array(
    'field' => 'ip',
    'title' => t('IP demerits IP totals'),
    'help' => t('IP demerits IP totals contains total demerit points by IP'),
  );

  // Join to ip_tracker table
  $data['ip_demerits_ip_totals']['table']['join'] = array(
    'ip_tracker' => array(
      'left_field' => 'ip',
      'field' => 'ip',
    ),
  );

  // IP field
  $data['ip_demerits_ip_totals']['ip'] = array(
    'title' => t('IP Address'),
    'help' => t('IP address of user.'),
    'relationship' => array(
      'base' => 'ip_tracker',
      'field' => 'ip',
      'handler' => 'views_handler_relationship',
      'label' => t('IP address'),
    ),
    'field' => array(
      'handler' => 'Long2IpField',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'Ip2LongFilter',
    ),
    'argument' => array(
      'handler' => 'Ip2LongArgument',
    ),
  );

  // Points
  $data['ip_demerits_ip_totals']['points'] = array(
    'title' => t('Points'),
    'help' => t('Points for this demerit'),
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

  // IP relationship: ip_tracker -> ip_demerits_ip_totals
  $data['ip_tracker']['ip_demerits_ip_totals'] = array(
    'title' => t('IP demerits totals'),
    'help' => t('IP demerits totals (IP)'),
    'relationship' => array(
      'base' => 'ip_demerits_ip_totals',
      'base field' => 'ip',
      'handler' => 'views_handler_relationship',
      'label' => t('IP demerits point totals'),
      'title' => t('Referenced IP'),
      'help' => t('Demerit reference by this IP'),
    ),
  );

  //
  // Table: Total points by user ID
  //
  $data['ip_demerits_uid_totals']['table']['group'] = t('IP demerits user totals');
  $data['ip_demerits_uid_totals']['table']['base'] = array(
    'field' => 'uid',
    'title' => t('IP demerits user totals'),
    'help' => t('IP demerits user totals contains total demerit points by user'),
  );

  // Join to users table
  $data['ip_demerits_uid_totals']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  // Join to ip_tracker table
  $data['ip_demerits_uid_totals']['table']['join'] = array(
    'ip_tracker' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  // Uid field
  $data['ip_demerits_uid_totals']['uid'] = array(
    'title' => t('User id'),
    'help' => t('Unique id of user'),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('User uid'),
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Points
  $data['ip_demerits_uid_totals']['points'] = array(
    'title' => t('Points'),
    'help' => t('Points for this demerit'),
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

  // User relationship: users -> ip_demerits_uid_totals
  $data['users']['ip_demerits_ip_totals'] = array(
    'title' => t('IP demerits'),
    'help' => t('IP demerits (users)'),
    'relationship' => array(
      'base' => 'ip_demerits_uid_totals',
      'base field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('IP demerits point totals'),
      'title' => t('Referenced user'),
      'help' => t('Demerit reference by this user'),
    ),
  );

  // Alternative username field for users table
//   $data['users']['name_alt'] = array(
//     'title' => t('Username (alt)'),
//     'help' => t('The username for the user account or author distinguishing anonymous and deleted.'),
//     'real field' => 'name',
//     'field' => array(
//       'handler' => 'views_handler_field_user_name',
//       'click sortable' => TRUE,
//     ),
//     'sort' => array(
//       'handler' => 'views_handler_sort',
//     ),
//     'argument' => array(
//       'handler' => 'views_handler_argument_string',
//     ),
//     'filter' => array(
//       'handler' => 'views_handler_filter_string',
//       'title' => t('Name (raw)'),
//       'help' => t('The username for the user account or author. This filter does not check if the user account exists and allows partial matching. Does not utilize autocomplete.')
//     ),
//   );

  return $data;
}
