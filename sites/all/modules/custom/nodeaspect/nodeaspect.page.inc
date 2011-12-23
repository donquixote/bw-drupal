<?php


function _nodeaspect_page_info_build($node, $suffix) {
  $info = array();
  $info_tmp = array();
  $api = new nodeaspect_API_PageInfo($info_tmp);
  if (preg_match('#[a-zA-Z0-9_]*#', $suffix)) {
    // $suffix is a valid function suffix.
    // Try the very specific hook.
    foreach (module_implements('nodeaspect_page__' . $suffix) as $module) {
      $f = $module . '_nodeaspect_page__' . $suffix;
      $info_tmp = array('override' => 0, 'module' => $module);
      $f($node, $api);
      if (!isset($info['override']) || $info_tmp['override'] > $info['override']) {
        if (!empty($info_tmp['access']) || strlen($info_tmp['title'])) {
          $info = $info_tmp;
        }
      }
    }
  }
  foreach (module_implements('nodeaspect_page') as $module) {
    $f = $module . '_nodeaspect_page';
    $info_tmp = array('override' => 0, 'module' => $module);
    $f($node, $suffix, $api);
    if (!isset($info['override']) || $info_tmp['override'] > $info['override']) {
      if (!empty($info_tmp['access']) || @strlen($info_tmp['title'])) {
        $info = $info_tmp;
      }
    }
  }
  $info['access'] = @$info['access'] && node_access('view', $node);
  $info += array(
    // Use the defaults from node_show().
    'render as teaser' => FALSE,
    'render as page' => TRUE,
    'render links' => TRUE,
    'tab' => TRUE,
  );
  return new nodeaspect_PageInfo($info);
}


class nodeaspect_PageInfo {

  protected $_info;

  function __construct(array $info) {
    $this->_info = $info;
  }

  function localTaskWeight() {
    return $this->_info['tab'] ? $this->_info['weight'] : FALSE;
  }

  /**
   * Access callback.
   * This only returns an internal variable.
   */
  function access() {
    return !empty($this->_info['access']);
  }

  /**
   * Title callback.
   * This only returns an internal variable.
   */
  function title() {
    return $this->_info['title'];
  }

  /**
   * Page callback.
   */
  function page($node) {

    if (!empty($this->_info['page_title'])) {
      drupal_set_title($this->_info['page_title']);
    }

    if (isset($this->_info['view_mode'])) {
      return $this->_nodeShow($node);
    }
    elseif (isset($this->_info['page callback'])) {
      if (!empty($this->_info['file'])) {
        require_once $this->_info['file'];
      }
      return call_user_func_array($this->_info['page callback'], $this->_info['page arguments']);
    }
    elseif (isset($this->_info['redirect'])) {
      // TODO: drupal_goto().
    }
  }

  function hook_pageapi($api, $node, $suffix) {
    if (!empty($this->_info['pageapi_callback'])) {
      $f = $this->_info['pageapi_callback'];
      $api->setModule($this->_info['module']);
      if (empty($this->_info['pageapi_arguments'])) {
        $f($api, $node, $suffix);
      }
      else {
        $args = array_merge(array($api, $node, $suffix), $this->_info['pageapi_arguments']);
        call_user_func_array($f, $args);
      }
    }
  }

  /**
   * Adapted from function node_show()
   */
  protected function _nodeShow($node) {

    $info = $this->_info;

    // For markup consistency with other pages, use node_view_multiple() rather than node_view().
    $render_array = node_view_multiple(array($node->nid => $node), $info['view_mode']);

    // Update the history table, stating that this user viewed this node.
    node_tag_new($node);

    return $render_array;
  }
}


class nodeaspect_API_PageInfo {

  protected $_info;

  function __construct(array &$info) {
    $this->_info =& $info;
  }

  /**
   * Set title and weight of a local task.
   * Combination of ->title() and ->weight().
   */
  function tab($title, $weight = NULL) {
    $this->_info['title'] = $title;
    if (isset($weight)) {
      $this->_info['weight'] = $weight;
    }
    return $this;
  }

  function title($title) {
    $this->_info['title'] = $title;
    return $this;
  }

  /**
   * As an alternative to the view_mode, this method allows to set a page
   * callback, to be called when the page is to be rendered.
   */
  function pageCallback($callback, array $args) {
    $this->_info['page callback'] = $callback;
    $this->_info['page arguments'] = $callback;
    $this->_info['access'] = TRUE;
    unset($this->_info['view_mode']);
    unset($this->_info['redirect']);
    return $this;
  }

  /**
   * File to include for the page callback.
   */
  function file($path, $module = NULL) {
    if (!isset($module)) {
      $module = $this->_info['module'];
    }
    if ($module !== FALSE) {
      $path = drupal_get_path('module', $module) . '/' . $path;
    }
    $this->_info['file'] = $path;
    return $this;
  }

  function viewMode($view_mode) {
    $this->_info['view_mode'] = $view_mode;
    $this->_info['access'] = ($view_mode === 'full') || user_access('nodeaspect view ' . $view_mode);
    unset($this->_info['page callback']);
    unset($this->_info['redirect']);
    return $this;
  }

  function redirect($path) {
    $this->_info['redirect'] = $path;
    $this->_info['access'] = TRUE;
    unset($this->_info['page callback']);
    unset($this->_info['view_mode']);
  }

  function pageTitle($title) {
    $this->_info['page_title'] = $title;
    return $this;
  }

  /**
   * Weight of the tab linking to this page.
   */
  function weight($weight) {
    $this->_info['weight'] = $weight;
    return $this;
  }

  function renderAsPage($bool) {
    $this->_info['render as page'] = $bool;
    return $this;
  }

  function renderLinks($bool) {
    $this->_info['render links'] = $bool;
    return $this;
  }

  function renderAsTeaser($bool) {
    $this->_info['render as teaser'] = $bool;
    return $this;
  }

  function renderComments($bool) {
    $this->_info['render comments'] = $bool;
    return $this;
  }

  function noTab() {
    $this->_info['tab'] = FALSE;
    return $this;
  }

  function pageapiCallback($callback, array $extra_args = array()) {
    $this->_info['pageapi_callback'] = $callback;
    $this->_info['pageapi_arguments'] = $extra_args;
    return $this;
  }

  function override($weight) {
    $this->_info['override'] = $weight;
    return $this;
  }
}




