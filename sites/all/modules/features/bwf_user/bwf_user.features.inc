<?php
/**
 * @file
 * bwf_user.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bwf_user_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}
