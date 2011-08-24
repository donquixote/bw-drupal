<?php


class FaqTermMigration extends BWMigration {
  public function __construct() {
    parent::__construct();
    // Human-friendly description of your migration process. Be as detailed as you
    // like.
    $this->description = t('Migrate FAQ categories from the source database to taxonomy terms');

    // Create a map object for tracking the relationships between source rows
    // and their resulting Drupal objects. Usually, you'll use the MigrateSQLMap
    // class, which uses database tables for tracking. Pass the machine name
    // (FaqTerm) of this migration to use in generating map and message tables.
    // And, pass schema definitions for the primary keys of the source and
    // destination - we need to be explicit for our source, but the destination
    // class knows its schema already.
    $this->map = new MigrateSQLMap($this->machineName,
				   array(
					 'id' => array('type' => 'varchar',
						       'length' => 255,
						       'not null' => TRUE,
						       'description' => 'Topic ID',
						       )
					 ),
				   MigrateDestinationTerm::getKeySchema()
				   );

    $query = $this->roxdb_connection
      ->select('faqcategories', 'faqcategories')
      ->fields('faqcategories', array('id', 'Description', 'SortOrder'));
    $this->source = $this->roxMigrateSource($query);
    $this->destination = new MigrateDestinationTerm('faq_categories');

    $this->addFieldMapping('name', 'name_en');
    $this->addFieldMapping('description', 'name_en');
  }

  public function prepareRow($current_row) {
    $current_row->name_en = $this->getTranslation($current_row->description);
  }
}


class FaqNodeMigration extends BWMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('FAQ');
    $this->dependencies = array('FaqTerm');

    $this->map = new MigrateSQLMap($this->machineName,
        array('id' => array(
                'type' => 'int',
                'not null' => TRUE,
                'description' => 'FAQ ID.'
                )
             ),
        MigrateDestinationNode::getKeySchema()
    );

    // Set up our destination - nodes of type migrate_example_beer
    $this->destination = new MigrateDestinationNode('faq_item');
    $query = $this->roxdb_connection
      ->select('faq', 'faq')
      ->fields('faq', array('id', 'QandA', 'updated', 'created',
			    'Active', 'SortOrder', 'IdCategory', 'PageTitle'));
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

    // Unmapped destination fields
    //$this->addUnmigratedDestinations(array('name', 'created', 'changed', 'status',
    //  'promote', 'revision', 'language'));
  }

  public function prepareRow($current_row) {
    $current_row->title = $this->getTranslation('FaqQ_' . $current_row->qanda);
    $current_row->body = $this->getTranslation('FaqA_' . $current_row->qanda);
  }

}



