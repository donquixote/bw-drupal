<?php
/**
 * @file
 * bw_nodes.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function bw_nodes_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-footer-menu
  $menus['menu-footer-menu'] = array(
    'menu_name' => 'menu-footer-menu',
    'title' => 'footer menu',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('footer menu');


  return $menus;
}
