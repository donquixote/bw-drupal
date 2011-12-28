<?php


/**
 * API object, to be injected into the _init() method on migration classes.
 */
class bw_migrate_InjectedAPI_dest {

  protected $_migration;
  protected $_info;

  function __construct($migration, array &$info) {
    $this->_migration = $migration;
    $this->_info =& $info;
  }

  function dest($suffix) {
    $args = func_get_args();
    $this->_info['dest'] = $args;
  }

  function node($bundle, $options = array()) {
    $options += array(
      'text_format' => 'filtered_html',
    );
    $this->dest('node', $bundle, $options);
    $this->ignore(array(
      'is_new', 'status', 'promote', 'sticky', 'revision', 'path', 'comment',
    ));
    $this->_migration->p_addFieldMapping('pathauto')->defaultValue(FALSE);
    $this->_migration->p_addFieldMapping('language')->defaultValue('en');
  }

  function comment($node_bundle, $options = array()) {
    $options += array(
      'text_format' => 'filtered_html',
    );
    $this->dest('comment', 'comment_node_'. $node_bundle, $options);
  }

  function ignore(array $names) {
    foreach ($names as $name) {
      $this->_info['dest_ignore'][$name] = $name;
    }
  }

  function flush() {
    
  }
}


