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
    // $this->dependencies = array('BWUser');  // Add when BWUser more stable

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
      ->select('members', 'm')
      ->fields('m', array('id', 'Username', 'FirstName', 'SecondName', 'LastName', 'Occupation',
			  'ProfileSummary', 'Gender', 'BirthDate', 'WebSite', 'Books', 'Music', 'Movies'));
    $this->source = $this->roxMigrateSource($query);

    $this->destination = new MigrateDestinationProfile2('main');

    $this->addFieldMapping('field_firstname', 'firstname');
    $this->addFieldMapping('field_secondname', 'secondname');
    $this->addFieldMapping('field_lastname', 'lastname');
    $this->addFieldMapping('field_occupation', 'occupation');

    $this->addFieldMapping('field_profile_summary', 'profilesummary');
    $this->addFieldMapping('field_gender', 'gender');
    $this->addFieldMapping('field_birth_date', 'birthdate');
    $this->addFieldMapping('field_website', 'website');
    $this->addFieldMapping('field_books', 'books');
    $this->addFieldMapping('field_music', 'music');
    $this->addFieldMapping('field_movies', 'movies');

    // Unmapped destination fields
    $this->addUnmigratedDestinations(array('id'));
  }

  public function prepare(stdClass $account, stdClass $row) {
    // print "\nuser: " . $row->username . "\n";
    $result = db_query('SELECT uid FROM {users} WHERE name = :name',
		       array(':name' => $row->username));
    $uid = NULL;
    foreach ($result as $r) { // this shouldn't be a loop but just want working code now
      $uid = $r->uid;
    }
    $account->uid = (int)$uid;
    // print $uid;
  }
}
