<?php

/**
 * @file
 */

/**
 * Migration class to test import of various date fields.
 */
class BWCommentsMigration extends BWMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Migration of BW Rox comments table into User Relationships');
    // $this->dependencies = array('BWUser');  // Add when BWUser more stable

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
        )
      ),
      MigrateDestinationUserRelationships::getKeySchema()
    );

    $query = $this->roxdb_connection
      ->select('comments', 'c')
      ->fields('c', array('IdFromMember', 'IdToMember', 'Lenght', 'Quality', 'TextFree', 'TextWhere',
			  'updated', 'id', 'created', 'AdminAction', 'DisplayableInCommentOfTheMonth'));
    $this->source = $this->roxMigrateSource($query);

    $this->destination = new MigrateDestinationUserRelationships('comment');

    $this->addFieldMapping('requester_id', 'idfrommember');
    $this->addFieldMapping('requestee_id', 'idtomember');
    $this->addFieldMapping('approved')
      ->defaultValue(1); // 1 => active?
    $this->addFieldMapping('created_at', 'created');
    $this->addFieldMapping('updated_at', 'updated');
    

    // Unmapped destination fields
    $this->addUnmigratedDestinations(array('id'));
  }

  public function prepareRow(stdClass $row) {
    var_dump($row);
  }

}
