<?php
/**
 * @file
 * bwf_groups.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bwf_groups_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function bwf_groups_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_node_info().
 */
function bwf_groups_node_info() {
  $items = array(
    'group' => array(
      'name' => t('Group'),
      'base' => 'node_content',
      'description' => t('A group that other members can join.'),
      'has_title' => '1',
      'title_label' => t('Group name'),
      'help' => '',
    ),
    'group_discussion' => array(
      'name' => t('Group discussion'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
