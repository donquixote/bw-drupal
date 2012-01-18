<?php


/**
 * Implements hook_dqx_adminmenu_items_alter()
 *
 * This one is only called if both help and advanced_help are enabled.
 */
function advanced_help_dqx_adminmenu_items_alter($items) {
  $help_item = $items->getItem('admin/help');
  $help_item['title'] = '?';
  $items->addItem('admin/dqx-adminmenu-help', $help_item);
}


/**
 * Implements hook_dqx_adminmenu_structure_alter()
 *
 * This one is only called if both help and advanced_help are enabled.
 */
function advanced_help_dqx_adminmenu_structure_alter($structure) {
  $structure->submenuRemoveChild('admin', 'admin/help');
  $structure->submenuRemoveChild('admin', 'admin/advanced_help');
  $structure->submenuAddChild('admin/dqx-adminmenu-help', 'admin/help');
  $structure->submenuAddChild('admin/dqx-adminmenu-help', 'admin/advanced_help');
}



