<?php


function _nodeaspect_info_build() {
  $pages = array();
  $view_modes = array();
  $api = new nodeaspect_API($pages, $view_modes);
  module_invoke_all('nodeaspect', $api);
  return new nodeaspect_InfoWrapper($pages, $view_modes);
}


class nodeaspect_InfoWrapper {

  protected $_pages;
  protected $_view_modes;

  function __construct(array $pages, array $view_modes) {
    $this->_pages = $pages;
    $this->_view_modes = $view_modes;
  }

  function hook_perm() {
    $perm = array();
    foreach ($this->_view_modes as $key => $info) {
      $perm[] = 'nodeaspect view ' . $key;
    }
    return $perm;
  }

  function hook_menu() {
    $items = array();
    foreach ($this->_pages as $suffix => $true) {
      if ($suffix === '' || $suffix === 'view') {
        // This is dealt with in hook_menu_alter().
        continue;
      }
      $path = 'node/%node/' . $suffix;
      $items[$path] = array(
        'title callback' => 'nodeaspect_page_title',
        'title arguments' => array(1, $suffix),
        'page callback' => 'nodeaspect_page',
        'page arguments' => array(1, $suffix),
        'access callback' => 'nodeaspect_page_access',
        'access arguments' => array(1, $suffix),
        'type' => MENU_LOCAL_TASK,
      );
    }
    return $items;
  }

  function hook_menu_alter(&$items) {
    if (isset($this->_pages[''])) {
      // Something wants to hijack the main node/% route.
      $items['node/%node'] = array(
        'title callback' => 'nodeaspect_page_title',
        'title arguments' => array(1),
        'page callback' => 'nodeaspect_page',
        'page arguments' => array(1),
        // We do not override the access check,
        // to allow the bulk access checking for node/% menu items.
        'access callback' => 'node_access',
        'access arguments' => array('view', 1),
        'type' => MENU_CALLBACK,
        // 'module' => 'node',  // TODO: Why is this?
      );
    }
    if (isset($this->_pages['view'])) {
      // We assume that node/%node/view is still the "default local task".
      $items['node/%node/view'] = array(
        'title callback' => 'nodeaspect_page_title',
        'title arguments' => array(1, 'view'),
        // We do not override the access check,
        // to allow the bulk access checking for node/% menu items.
        // 'access callback' => 'node_access',
        // 'access arguments' => array('view', 1),
        'type' => MENU_DEFAULT_LOCAL_TASK,
        'weight' => -10,
        // 'module' => 'node',  // TODO: Why is this?
      );
    }
  }

  function hook_entity_info_alter(&$entity_info) {
    $entity_info['node']['view modes'] += $this->_view_modes;
  }
}


/**
 * API object, to be injected in hook_nodeaspect().
 */
class nodeaspect_API {

  protected $_pages;
  protected $_view_modes;

  function __construct(array &$pages, array &$view_modes) {
    $this->_pages =& $pages;
    $this->_view_modes =& $view_modes;
  }

  function page($node_subpath) {
    $this->_pages[$node_subpath] = TRUE;
  }

  function viewMode($view_mode, $title) {
    $this->_view_modes[$view_mode] = array(
      'label' => t($title),
      'custom settings' => FALSE,
    );
  }
}




