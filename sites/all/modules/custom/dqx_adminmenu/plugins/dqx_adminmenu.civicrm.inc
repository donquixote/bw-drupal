<?php


function civicrm_dqx_adminmenu_items() {
  $items = _dqx_adminmenu_router_items("title != '' AND path = 'civicrm'");
  return $items;
}


function civicrm_dqx_adminmenu_items_alter($items) {
  $item = $items->getItem('civicrm');
  $items->addItem('admin/civicrm', $item);
  $items->parentMap('civicrm', 'admin/civicrm');
}
