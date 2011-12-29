<?php


/**
 * API object, to be injected into the _init() method on migration classes.
 */
class bw_migrate_InjectedAPI_map {

  protected $_migration;
  protected $_info;

  function __construct($migration, array &$info) {
    $this->_migration = $migration;
    $this->_info =& $info;
  }

  function map($dest_field, $src_column = NULL) {
    return $this->_migration->p_addFieldMapping($dest_field, $src_column);
  }

  function uid($dest_field, $src_column = NULL) {
    return $this->foreignKey($dest_field, $src_column, 'user');
  }

  function word($dest_field, $src_column, $word_prefix = '') {
    $this->_info['words']["$src_column::$word_prefix"] = array($src_column, $word_prefix);
    return $this->map($dest_field, $src_column);
  }

  function trad($dest_field, $src_column) {
    $this->_info['trads'][$src_column] = $src_column;
    return $this->map($dest_field, $src_column);
  }

  function strtotime($dest_field, $src_column) {
    $this->_info['strtotime'][$src_column] = $src_column;
    return $this->map($dest_field, $src_column);
  }

  function crypted($dest_field, $src_column) {
    $this->_info['crypted'][$src_column] = $src_column;
    return $this->map($dest_field, $src_column);
  }

  function foreignKey($dest_field, $src_column, $mig) {
    $this->_info['dependencies'][$mig] = $mig;
    return $this->map($dest_field, $src_column)->sourceMigration($mig);
  }

  function defaultValue($dest_field, $value) {
    return $this->map($dest_field)->defaultValue($value);
  }

  function uidAdmin($dest_field) {
    return $this->map($dest_field)->defaultValue(1);
  }

  function yesno($dest_field, $src_column) {
    $this->_info['yesno'][$src_column] = $src_column;
    return $this->map($dest_field, $src_column);
  }

  /**
   * This allows to specify a default mapping,
   * without generating a warning when it is overridden.
   */
  function overridable($dest_field, $src_column = NULL) {
    return $this->_migration->p_addFieldMapping($dest_field, $src_column, TRUE);
  }
}


