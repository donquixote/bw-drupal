<?php
/**
 * @file
 * bw_frontpage.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function bw_frontpage_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implementation of hook_views_api().
 */
function bw_frontpage_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implementation of hook_node_info().
 */
function bw_frontpage_node_info() {
  $items = array(
    'bw_front_image' => array(
      'name' => t('BW Frontpage Image'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
