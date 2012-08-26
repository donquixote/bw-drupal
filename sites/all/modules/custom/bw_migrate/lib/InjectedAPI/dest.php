<?php


/**
 * API object, to be injected into the _init() method on migration classes.
 */
class bw_migrate_InjectedAPI_dest {

  protected $_migration;
  protected $_info;
  protected $_map;

  function __construct($migration, array &$info, $map) {
    $this->_migration = $migration;
    $this->_info =& $info;
    $this->_map = $map;
  }

  function dest($suffix) {
    $args = func_get_args();
    return $this->_migration->p_setDestination($args);
  }

  function node($bundle, $options = array()) {
    foreach (array(
      'is_new', 'status', 'promote', 'sticky', 'revision', 'path', 'comment',
    ) as $key) {
      $this->_map->overridable($key)->issueGroup(t('DNM'));
    }
    $this->_map->overridable('pathauto')->defaultValue(FALSE);
    $this->_map->overridable('language')->defaultValue('en');
    $options += array(
      'text_format' => 'filtered_html',
    );
    return $this->dest('node', $bundle, $options);
  }

  function comment($node_bundle, $options = array()) {
    $options += array(
      'text_format' => 'filtered_html',
    );
    return $this->dest('comment', 'comment_node_'. $node_bundle, $options);
  }

  function table($table_name) {
    $this->_info['dest_schema'] = MigrateDestinationTable::getKeySchema($table_name);
    return $this->dest('table', $table_name);
  }

  function ignore(array $names) {
    foreach ($names as $name) {
      $this->_info['dest_ignore'][$name] = $name;
    }
  }

  function flush() {
    
  }
}


