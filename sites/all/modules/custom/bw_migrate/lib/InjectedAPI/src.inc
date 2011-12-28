<?php


/**
 * API object, to be injected into the _init() method on migration classes.
 */
class bw_migrate_InjectedAPI_src {

  protected $_migration;
  protected $_roxdb;
  protected $_info;
  protected $_query;

  function __construct($migration, $roxdb, array &$info) {
    $this->_migration = $migration;
    $this->_roxdb = $roxdb;
    $this->_info =& $info;
  }

  function rox_select($table, $alias = NULL) {
    $alias = isset($alias) ? $alias : $table;
    $this->_query = $q = $this->_roxdb->select($table, $alias);
    return $q;
  }

  function primary($primary, $options = array(), $description = NULL) {
    if (!is_array($primary)) {
      if (!is_array($options)) {
        $options = array('type' => $options);
        if (isset($description)) {
          $options['description'] = $description;
        }
      }
      $primary = array($primary => $options);
    }
    foreach ($primary as $k => $options) {
      $options += array('type' => 'int');
      switch ($options['type']) {
        case 'varchar':
          $options += array('length' => 255);
          break;
        case 'int':
          $options += array('unsigned' => TRUE);
          break;
      }
      $this->_info['primary'][$k] = $options;
    }
  }

  function ignore(array $names) {
    foreach ($names as $name) {
      $this->_info['src_ignore'][$name] = $name;
    }
  }

  function flush() {
    $query_count = array();
    // Create a MigrateSource object, which manages retrieving the input data.
    // The map_joinable should be false because we're using another database
    // (and we don't want silly SQL errors because of unjoinable cross database JOINs)
    $source = new MigrateSourceSQL(
      $this->_query,
      $query_count,
      NULL,
      array('map_joinable' => FALSE)
    );
    return $source;
  }
}


