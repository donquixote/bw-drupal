<?php
/**
 * @file
 * bw_faq.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function bw_faq_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'bw_faq';
  $context->description = 'BW FAQ context';
  $context->tag = 'bw, faq';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'faq_item' => 'faq_item',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
    'path' => array(
      'values' => array(
        'about/faq' => 'about/faq',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-bw_faq_categories-block' => array(
          'module' => 'views',
          'delta' => 'bw_faq_categories-block',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('BW FAQ context');
  t('bw, faq');
  $export['bw_faq'] = $context;

  return $export;
}
