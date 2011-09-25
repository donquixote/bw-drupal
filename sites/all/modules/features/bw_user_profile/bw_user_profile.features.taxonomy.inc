<?php
/**
 * @file
 * bw_user_profile.features.taxonomy.inc
 */

/**
 * Implementation of hook_taxonomy_default_vocabularies().
 */
function bw_user_profile_taxonomy_default_vocabularies() {
  return array(
    'accommodation' => array(
      'name' => 'Accommodation',
      'machine_name' => 'accommodation',
      'description' => 'yes/maybe/no',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
    'gender' => array(
      'name' => 'Gender',
      'machine_name' => 'gender',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
  );
}
