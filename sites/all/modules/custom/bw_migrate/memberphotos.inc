<?php
/**
 * @file
 */

/**
 * Migration class to test import of various date fields.
 */
class BWMembersPhotosMigration extends BWMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Migration of BW Rox members table into profile2 entities');
    // $this->dependencies = array('BWUser');  // Add when BWUser more stable

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'idmember' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
        )
      ),
      MigrateDestinationProfile2::getKeySchema()
    );

    $query = $this->roxdb_connection
      ->select('membersphotos', 'mp')
      ->fields('mp', array('id', 'FilePath', 'IdMember', 'SortOrder', 'Comment'));
    $this->source = $this->roxMigrateSource($query);

    $this->destination = new MigrateDestinationProfile2('members');

    $this->addFieldMapping('field_photos', 'filepath');
    $this->addFieldMapping('uid', 'idmember');

    // Unmapped destination fields
    // $this->addUnmigratedDestinations(array('id'));
  }

  public function prepare(stdClass $account, stdClass $row) {
    var_dump($row);
  }


}
