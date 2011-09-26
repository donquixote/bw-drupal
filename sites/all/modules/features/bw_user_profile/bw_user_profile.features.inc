<?php
/**
 * @file
 * bw_user_profile.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function bw_user_profile_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implementation of hook_default_profile2_type().
 */
function bw_user_profile_default_profile2_type() {
  $items = array();
  $items['main'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "main",
    "label" : "User Profile",
    "weight" : "0",
    "data" : { "registration" : 1 }
  }');
  return $items;
}
