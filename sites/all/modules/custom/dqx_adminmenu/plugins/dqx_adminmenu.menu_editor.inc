<?php


function menu_editor_dqx_adminmenu_items() {
  $items = array();
  $q = db_query("SELECT * FROM {menu_custom} ORDER BY title");
  while ($menu = db_fetch_array($q)) {
    $path = 'admin/build/menu-customize/' . $menu['menu_name'] . '/poweredit';
    $items[$path] = array(
      'title' => $menu['title'],
      'link_path' => $path,
      'weight' => 100,
    );
  }
  return $items;
}


function menu_editor_dqx_adminmenu_items_alter($items) {
  $items->parentMap('admin/build/menu-customize', 'admin/build/menu/list');
  $items->submenuSetInlineChild('admin/build/menu', 'admin/build/menu/list');
}



