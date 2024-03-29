<?php
/**
 * @file
 * bw_frontpage.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function bw_frontpage_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_bw_front_image';
  $strongarm->value = 0;
  $export['comment_anonymous_bw_front_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_bw_front_image';
  $strongarm->value = '2';
  $export['comment_bw_front_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_bw_front_image';
  $strongarm->value = 1;
  $export['comment_default_mode_bw_front_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_bw_front_image';
  $strongarm->value = '50';
  $export['comment_default_per_page_bw_front_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_bw_front_image';
  $strongarm->value = 1;
  $export['comment_form_location_bw_front_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_bw_front_image';
  $strongarm->value = '1';
  $export['comment_preview_bw_front_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_bw_front_image';
  $strongarm->value = 1;
  $export['comment_subject_field_bw_front_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_bw_front_image';
  $strongarm->value = '0';
  $export['language_content_type_bw_front_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_bw_front_image';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_bw_front_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_bw_front_image';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_bw_front_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_bw_front_image';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_bw_front_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_bw_front_image';
  $strongarm->value = '1';
  $export['node_preview_bw_front_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_bw_front_image';
  $strongarm->value = 1;
  $export['node_submitted_bw_front_image'] = $strongarm;

  return $export;
}
