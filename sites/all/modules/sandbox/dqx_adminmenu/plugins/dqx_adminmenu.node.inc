<?php


function node_dqx_adminmenu_items() {

  // create content links
  $sql_filter = "path LIKE 'node/add/%%'  OR  path = 'node/add'";
  $items = _dqx_adminmenu_router_items($sql_filter);

  return $items;
}


function node_dqx_adminmenu_items_alter($items) {

  // create content links
  $items->parentMap('node', 'admin/content');
  $items->itemSetWeight('node/add', 0);

  // node type submenus
  $items->parentMap('admin/content/node-type', 'admin/content/types/list');
  $items->itemSetTitle('admin/content/types/list', t('List of types'));
}


function node_dqx_adminmenu_structure_alter($structure) {
  // node type submenus
  $structure->submenuSetInlineChild('admin/content/types', 'admin/content/types/list');
}



