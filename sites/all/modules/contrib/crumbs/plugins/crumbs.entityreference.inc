<?php


/**
 * Implements hook_crumbs_plugins()
 */
function entityreference_crumbs_plugins($api) {
  foreach (field_info_fields() as $key => $info) {
    if ($info['type'] === 'entityreference') {
      foreach ($info['bundles'] as $entity_type => $bundles) {
        $class = '_entityreference_CrumbsMultiPlugin_' . $entity_type;
        if (class_exists($class)) {
          $plugin = new $class($key, $bundles);
          $api->multiPlugin("$key.$entity_type", $plugin);
        }
      }
    }
  }
  $api->disabledByDefault('*');
}


abstract class _entityreference_CrumbsMultiPlugin implements crumbs_MultiPlugin {

  protected $fieldKey;
  protected $bundles;

  // To be defined by the child class
  protected $entityType;

  function __construct($field_key, $bundles) {
    $this->fieldKey = $field_key;
    $this->bundles = $bundles;
  }

  function describe($api) {
    foreach ($this->bundles as $bundle) {
      $api->addRule($bundle, $bundle);
    }
  }

  protected function _findParentPath($entity) {
    if (isset($entity->{$this->fieldKey}['und'][0])) {
      $target_id = $entity->{$this->fieldKey}['und'][0]['target_id'];
      $target_type = $entity->{$this->fieldKey}['und'][0]['target_type'];
      $method = '_getPath_' . $target_type;
      if (method_exists($this, $method)) {
        return $this->$method($target_id);
      }
    }
  }

  protected function _getPath_node($nid) {
    return 'node/' . $nid;
  }

  protected function _getPath_user($uid) {
    return 'user/' . $uid;
  }
}


class _entityreference_CrumbsMultiPlugin_node extends _entityreference_CrumbsMultiPlugin {

  protected $entityType = 'node';

  /**
   * Match "node/%" router path
   */
  function findParent__node_x($path, $item) {
    $node = $item['map'][1];
    $parent_path = $this->_findParentPath($node);
    if ($parent_path) {
      return array($node->type => $parent_path);
    }
  }
}


class _entityreference_CrumbsMultiPlugin_user extends _entityreference_CrumbsMultiPlugin {

  protected $entityType = 'user';

  /**
   * Match "user/%" router path
   */
  function findParent__user_x($path, $item) {
    $user = $item['map'][1];
    $parent_path = $this->_findParentCandidates($user);
    if ($parent_path) {
      // TODO: Is 'user' the correct bundle name?
      return array('user' => $user);
    }
  }
}







