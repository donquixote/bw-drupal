<?php
/**
 * @file
 */

/**
 * Migration class to test import of various date fields.
 */
class BWMembersMigration extends BWMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Migration of BW Rox members table into profile2 entities');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
        )
      ),
      MigrateDestinationProfile2::getKeySchema()
    );


    $query = $this->roxdb_connection
      ->select('members', 'm')->fields('m', array('FirstName', 'SecondName', 'Occupation'));
    $query_count = array();
    $this->source = new MigrateSourceSQL($query, $query_count, NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationProfile2('main');

    $this->addFieldMapping('uid')
         ->defaultValue(1);

    $this->addFieldMapping('firstname', 'firstname');
    $this->addFieldMapping('secondname', 'secondname');
    $this->addFieldMapping('occupation', 'occupation');


    // Unmapped destination fields
    $this->addUnmigratedDestinations(array('id'));
  }

}
