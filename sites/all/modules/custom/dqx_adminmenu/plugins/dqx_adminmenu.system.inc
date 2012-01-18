<?php


function system_dqx_adminmenu_items() {
  $items = _dqx_adminmenu_router_items("path LIKE 'admin/%%'  OR  path = 'admin'");

  unset($items['admin/by-module']);
  unset($items['admin/by-task']);
  unset($items['admin/compact']);

  return $items;
}


function system_dqx_adminmenu_structure_alter($structure) {
  $structure->submenuSetInlineChild('admin/build/themes', 'admin/build/themes/settings');
}

