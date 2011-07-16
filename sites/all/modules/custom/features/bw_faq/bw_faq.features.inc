<?php

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

/**
 * Implementation of hook_views_api().
 */
function bw_faq_views_api() {
  return array(
    'api' => '3.0-alpha1',
  );
}
