<?php
/**
 * @file
 * bw_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function bw_permissions_user_default_roles() {
  $roles = array();

  // Exported role: accepted
  $roles['accepted'] = array(
    'name' => 'accepted',
    'weight' => '3',
  );

  // Exported role: admin
  $roles['admin'] = array(
    'name' => 'admin',
    'weight' => '3',
  );

  return $roles;
}
