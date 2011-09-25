<?php
/**
 * @file
 * bw_wiki.features.inc
 */

/**
 * Implementation of hook_node_info().
 */
function bw_wiki_node_info() {
  $items = array(
    'bw_wikipage' => array(
      'name' => t('bw_wikipage'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
