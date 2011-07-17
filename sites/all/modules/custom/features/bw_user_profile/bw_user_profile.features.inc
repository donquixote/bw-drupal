<?php
/**
 * @file
 * bw_user_profile.features.inc
 */

/**
 * Implementation of hook_default_profile2_type().
 */
function bw_user_profile_default_profile2_type() {
  $items = array();
  $items['main'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "main",
    "label" : "Main profile",
    "weight" : "0",
    "data" : { "registration" : true, "use_page" : true }
  }');
  return $items;
}
