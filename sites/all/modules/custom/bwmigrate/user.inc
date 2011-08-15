<?php

class BWUserMigration extends BWMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('BW users');
    $this->map = new MigrateSQLMap($this->machineName,
        array('id' => array(
                'type' => 'int',
                'not null' => TRUE,
                'description' => 'User ID.'
                )
             ),
        MigrateDestinationUser::getKeySchema()
    );

    $query = $this->roxdb_connection
      ->select('user', 'user')->fields('user', array('id', 'email', 'handle', 'active', 'lastlogin', 'pw'));
    $query_count = array();
    $this->source = new MigrateSourceSQL($query, $query_count, NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationUser();

    // TODO: fix
    //$this->addFieldMapping('active', 'status'); 

    // Dedupe assures that value is unique. Use it when source data is non-unique.
    // Pass the Drupal table and column for determining uniqueness.
    $this->addFieldMapping('name', 'handle')
         ->dedupe('users', 'name');

    // Here we have a special case - we want to transform a date/time string
    // into a UNIX timestamp, and also apply a specific timezone. The
    // mapping of posted to created here is primarily for the sake of
    // documentation - the prepare method below actually populates the field.
    $this->addFieldMapping('created', 'lastlogin')
         ->description('See prepare method');

    $this->addFieldMapping('mail', 'email');
    $this->addFieldMapping('pass', 'pw');

    // Instead of mapping a source field to a destination field, you can
    // hardcode a default value. You can also use both together - if a default
    // value is provided in addition to a source field, the default value will
    // be applied to any rows where the source field is empty or NULL.
    $this->addFieldMapping('roles')
         ->defaultValue(drupal_map_assoc(array(2)));
    $this->addFieldMapping('field_migrate_example_gender', 'sex');

    // Unmapped source fields
    $this->addFieldMapping(NULL, 'nickname')
         ->issueGroup(t('DNM'));

    // Unmapped destination fields
    $this->addFieldMapping('theme')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('signature')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('access')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('login')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('timezone')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('language')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('picture')
         ->issueGroup(t('DNM'));
  }

  // If you define a prepare() method in your migration, it will be called
  // after the mappings have been applied and before the destination object is
  // saved. The first argument is the destination object as built up using
  // the mappings; the second argument is the raw source data.
  public function prepare(stdClass $account, stdClass $row) {
    // Source dates are in ISO format.
    // Because the mappings above have been applied, $account->created contains
    // the date/time string now - we could also pass $row->posted here.
    $account->created = strtotime($account->created);
  }
}
