<?php


/**
 * Implements hook_crumbs_plugins()
 */
function menu_position_crumbs_plugins($api) {
  // Just one plugin for the entire module.
  $api->multiPlugin();
  $api->disabledByDefault('*');
}


/**
 * Implementation of class hook class_CrumbsParentFinder
 * on the behalf of path module.
 */
class path_CrumbsMultiPlugin implements crumbs_MultiPlugin {

  function describe($api) {
    $api->addRule('*', t("Use the rule configured with 'Menu position' module."));
    return array();
  }

  function findParent($path, $item) {
    return;
    if ($alias = $item['alias']) {
      return crumbs_reduce_path($alias, 1);
    }
  }
}
