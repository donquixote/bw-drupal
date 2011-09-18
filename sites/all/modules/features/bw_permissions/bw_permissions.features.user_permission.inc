<?php
/**
 * @file
 * bw_permissions.features.user_permission.inc
 */

/**
 * Implementation of hook_user_default_permissions().
 */
function bw_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: access content
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: reply only privatemsg
  $permissions['reply only privatemsg'] = array(
    'name' => 'reply only privatemsg',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: search content
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: use advanced search
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: view own unpublished content
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: write privatemsg
  $permissions['write privatemsg'] = array(
    'name' => 'write privatemsg',
    'roles' => array(
      0 => 'accepted',
      1 => 'authenticated user',
    ),
    'module' => 'privatemsg',
  );

  return $permissions;
}
