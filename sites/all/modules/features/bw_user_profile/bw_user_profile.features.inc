<?php
/**
 * @file
 * bw_user_profile.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bw_user_profile_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_profile2_type().
 */
function bw_user_profile_default_profile2_type() {
  $items = array();
  $items['main'] = entity_import('profile2_type', '{
    "userCategory" : false,
    "userView" : false,
    "type" : "main",
    "label" : "Main profile",
    "weight" : "0",
    "data" : { "registration" : true, "use_page" : true },
    "entity_type" : "profile2_type"
  }');
  return $items;
}
