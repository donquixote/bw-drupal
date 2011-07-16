<?php

/**
 * Implementation of hook_node_info().
 */
function bw_wiki_node_info() {
  $items = array(
    'wiki' => array(
      'name' => t('wiki'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function bw_wiki_views_api() {
  return array(
    'api' => '3.0-alpha1',
  );
}
