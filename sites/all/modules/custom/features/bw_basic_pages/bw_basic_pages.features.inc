<?php
/**
 * @file
 * bw_basic_pages.features.inc
 */

/**
 * Implementation of hook_node_info().
 */
function bw_basic_pages_node_info() {
  $items = array(
    'page' => array(
      'name' => t('Page'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
