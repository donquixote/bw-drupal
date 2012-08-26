<?php


abstract class bw_migrate_Migration extends Migration {

  protected $_rox_info;
  protected $_roxdb;
  protected $_overridables = array();

  /**
   * Allow alternative machine names.
   *
   * Note:
   *   This needs a patch to migrate module from
   *   http://drupal.org/node/1386458#comment-5404052
   *   (hopefully to become part of the next version)
   */
  static protected function machineFromClass($class_name) {
    // Allow to prefix our class names, so we are safe against nameclashes.
    if (preg_match('#^bw_migrate_Migration_(.*)$#', $class_name, $m)) {
      return $m[1];
    }
  }

  public function __construct() {

    // Always call the parent constructor first for basic setup
    parent::__construct();

    // With migrate_ui enabled, migration pages will indicate people involved in
    // the particular migration, with their role and contact info. We default the
    // list in the shared class; it can be overridden for specific migrations.
    $this->team = array(
      new MigrateTeamMember('Kasper Souren', 'kasper@guaka.org', t('coder')),
      new MigrateTeamMember('Lemonhead', 'lemon.head.bw@gmail.com', t('coder')),
    );

    // Individual mappings in a migration can be linked to a ticket or issue
    // in an external tracking system. Define the URL pattern here in the shared
    // class with ':id:' representing the position of the issue number, then add
    // ->issueNumber(1234) to a mapping.
    $this->issuePattern = 'http://drupal.org/node/:id:';

    $roxdb = $this->_roxdb = Database::getConnection('default', 'bwroxdb');

    if (method_exists($this, '_init')) {
      // Now call the _init() of the child class.
      $info = array(
        'words' => array(),
        'crypted' => array(),
        'dependencies' => array(),
        'trads' => array(),
        'src_ignore' => array(),
        'dest_ignore' => array(),
        'yesno' => array(),
        'enum' => array(),
        'strtotime' => array(),
      );
      $map_api = new bw_migrate_InjectedAPI_map($this, $info);
      $source_api = new bw_migrate_InjectedAPI_src($this, $roxdb, $info);
      $destination_api = new bw_migrate_InjectedAPI_dest($this, $info, $map_api);
      try {
        $this->_init($source_api, $destination_api, $map_api);
      }
      catch (Exception $e) {
        dpm($e);
        ddebug_backtrace();
      }
      $this->source = $source_api->flush();
      $destination_api->flush();

      if (isset($info['dest_schema'])) {
        $dest_schema = $info['dest_schema'];
      }
      else {
        $dest_schema = $this->destination->getKeySchema();
      }

      $src_primary = $info['primary'];
      $this->map = new MigrateSQLMap($this->machineName, $src_primary, $dest_schema);

      if (is_array($this->dependencies)) {
        foreach ($this->dependencies as $migration_name) {
          $info['dependencies'][$migration_name] = $migration_name;
        }
      }

      $this->addUnmigratedDestinations(array_values($info['dest_ignore']));
      $this->addUnmigratedSources(array_values($info['src_ignore']));

      $this->dependencies = array_keys($info['dependencies']);

      $this->_rox_info = $info;
    }
  }

  public function getTranslation($code, $lang = 'en') {
    // Method to get BW Rox translation string
    $result = $this->_roxdb->query(
      'SELECT Sentence FROM {words} WHERE code = :code AND ShortCode = :lang',
      array(':code' => $code, ':lang' => $lang)
    );
    // this shouldn't be a loop but just want working code now
    foreach ($result as $row) {
      $sentence = $row->sentence;
    }
    if (!isset($sentence)) {
      $sentence = $code;
    }
    return $sentence;
  }

  /**
   * Public wrapper for a protected function,
   * so it can be called from within bw_migrate_InjectedAPI_map.
   */
  function p_addFieldMapping($dest_field, $src_column = NULL, $overridable = FALSE) {
    if (!is_null($dest_field) && !empty($this->_overridables[$dest_field])) {
      // Suppress the warning for field override.
      unset($this->fieldMappings[$dest_field]);
      unset($this->_overridables[$dest_field]);
    }
    if (!is_null($dest_field) && $overridable) {
      // Next time, we suppress again the override warning for this field.
      $this->_overridables[$dest_field] = TRUE;
    }
    return $this->addFieldMapping($dest_field, $src_column);
  }

  function p_setDestination(array $dest_args) {
    $dest_suffix = array_shift($dest_args);
    $dest_class = 'MigrateDestination'. ucfirst($dest_suffix);
    $dest_class_reflect = new ReflectionClass($dest_class);
    $this->destination = $dest_class_reflect->newInstanceArgs($dest_args);
    return $this->destination;
  }

  /**
   * Automatically translate fields.
   * We set this as final, so subclasses don't override it unintendedly.
   */
  final function prepareRow($row) {

    if (method_exists($this, '_prepareRow')) {
      $continue = $this->_prepareRow($row);
      if ($continue === FALSE) {
        // Allow subclasses to not run the default prepareRow code.
        return;
      }
    }

    foreach ($this->_rox_info['words'] as $key => $v) {
      list($key, $word_prefix) = $v;
      $row->$key = $this->getTranslation($word_prefix . $row->$key);
    }

    foreach ($this->_rox_info['crypted'] as $key) {

      if (!empty($row->$key)) {
        $crypted = $this->_roxdb->select('cryptedfields', 'c')
          ->condition('id', $row->$key)
          ->fields('c', array('MemberCryptedValue'))
          ->execute()->fetchField()
        ;
        // The test db has a cheap crypting method.
        if (preg_match('#^\<membercrypted\>(.*)\</membercrypted\>$#', $crypted, $m)) {
          $row->$key = $m[1];
        }
      }
    }

    foreach ($this->_rox_info['strtotime'] as $key) {
      $row->$key = strtotime($row->$key);
    }

    foreach ($this->_rox_info['trads'] as $key => $trad_info) {
      list($id_col, $trad_key) = $trad_info;
      if (isset($row->$id_col)) {
        $q = $this->_roxdb->select('memberstrads', 'mt');
        $q->condition('TableColumn', $trad_key);
        $q->condition('IdTrad', $row->$id_col);
        $q->leftJoin('languages', 'l', 'l.id = mt.IdLanguage');
        $q->fields('mt');
        $q->addExpression('l.ShortCode', 'lang');
        $trads = array();
        foreach ($q->execute() as $trad) {
          $trads[$trad->lang] = $trad;
        }
        // dpm($trads);
      }
    }

    foreach ($this->_rox_info['yesno'] as $key) {
      $row->$key = (strtolower($row->$key) === 'yes') ? 1 : 0;
    }

    foreach ($this->_rox_info['enum'] as $key => $enum) {
      if (isset($enum[$row->$key])) {
        $row->$key = $enum[$row->$key];
      }
    }
  }
}


