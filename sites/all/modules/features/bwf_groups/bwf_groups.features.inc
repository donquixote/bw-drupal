<?php
/**
 * @file
 * bwf_groups.features.inc
 */

/**
 * Implements hook_views_api().
 */
function bwf_groups_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}
