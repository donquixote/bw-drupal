<?php



class WikiNodeMigration extends BWMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('wiki');


    // pagename as source key doesn't really work yet
    // somehow type varchar is not picked up
    $this->map = new MigrateSQLMap($this->machineName,
				   array('pagename' => array(
						       'type' => 'varchar',
						       // 'not null' => TRUE,
						       // 'description' => 'Wiki pagename.'
						       )
					 ),
				   MigrateDestinationNode::getKeySchema()
				   );

    // Set up our destination - nodes of type migrate_example_beer
    $this->destination = new MigrateDestinationNode('bw_wikipage');
    $query = $this->roxdb_connection
      ->select('ewiki', 'w')
      ->fields('w', array('pagename', 'version', 'flags',
			  'content', 'author', 'created', 'lastmodified',
			  ));
    $this->source = $this->roxMigrateSource($query);

    // Mapped fields
    $this->addFieldMapping('title', 'pagename')
         ->description(t('Mapping something to node title'));

    $this->addFieldMapping('body', 'content');

    // Unmapped destination fields
    //$this->addUnmigratedDestinations(array('name', 'created', 'changed', 'status',
    //  'promote', 'revision', 'language'));
  }

}



