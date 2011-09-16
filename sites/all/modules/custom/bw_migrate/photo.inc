<?php



class PhotoNodeMigration extends BWMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('FAQ');
    $this->dependencies = array('FaqTerm');

    $this->map = new MigrateSQLMap($this->machineName,
				   array('fid' => array(
						       'type' => 'int',
						       'not null' => TRUE,
						       'description' => 'FAQ ID.'
						       )
					 ),
				   MigrateDestinationNode::getKeySchema()
				   );

    // Set up our destination - nodes of type migrate_example_beer
    $this->destination = new MigrateDestinationNode('pr9photo');
    $query = $this->roxdb_connection
      ->select('files', 'f')
      ->fields('f', array('fid', 'filepath', 'filename'));

    $this->source = $this->roxMigrateSource($query);

    // Mapped fields
    $this->addFieldMapping('title', 'title')
         ->description(t('Mapping something to node title'));

    // To maintain node identities between the old and new systems (i.e., have
    // the same unique IDs), map the ID column from the old system to nid and
    // set is_new to TRUE.
    $this->addFieldMapping('nid', 'id')
         ->description(t('Preserve old FAQ ID as nid in Drupal'));
    $this->addFieldMapping('is_new')
         ->defaultValue(TRUE);

    $this->addFieldMapping('body', 'body');


    $this->addFieldMapping('field_faq_category', 'category');

    // Unmapped destination fields
    //$this->addUnmigratedDestinations(array('name', 'created', 'changed', 'status',
    //  'promote', 'revision', 'language'));
  }

  public function prepareRow($current_row) {

  }

}



