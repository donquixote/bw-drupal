<?php
/**
 * @file
 * bw_faq.features.inc
 */

/**
 * Implementation of hook_views_api().
 */
function bw_faq_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implementation of hook_node_info().
 */
function bw_faq_node_info() {
  $items = array(
    'faq_item' => array(
      'name' => t('FAQ item'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
