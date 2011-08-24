<?php
/**
 * @file
 * bw_faq.features.taxonomy.inc
 */

/**
 * Implementation of hook_taxonomy_default_vocabularies().
 */
function bw_faq_taxonomy_default_vocabularies() {
  return array(
    'faq_categories' => array(
      'name' => 'FAQ categories',
      'machine_name' => 'faq_categories',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
  );
}
