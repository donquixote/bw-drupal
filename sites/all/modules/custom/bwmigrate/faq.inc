<?php


class FaqNodeMigration extends BWMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('FAQ');

    // You may optionally declare dependencies for your migration - other migrations
    // which should run first. In this case, terms assigned to our nodes and
    // the authors of the nodes should be migrated before the nodes themselves.
    // $this->dependencies = array('BeerTerm', 'BeerUser');

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
      ->select('faq', 'faq')->fields('faq', array('id', 'QandA', 'updated', 'created', 'Active', 'SortOrder', 'IdCategory', 'PageTitle'));
    $query_count = array();
    $this->source = new MigrateSourceSQL($query, $query_count, NULL, array('map_joinable' => FALSE));
    $this->destination = new MigrateDestinationNode('faq_item');

    // Mapped fields
    $this->addFieldMapping('title', 'PageTitle')
         ->description(t('Mapping FAQ title to node title'));

    // To maintain node identities between the old and new systems (i.e., have
    // the same unique IDs), map the ID column from the old system to nid and
    // set is_new to TRUE.
    $this->addFieldMapping('nid', 'id')
         ->description(t('Preserve old beer ID as nid in Drupal'));
    $this->addFieldMapping('is_new')
         ->defaultValue(TRUE);

    $this->addFieldMapping('body', 'QandA');

    // Unmapped destination fields
    //$this->addUnmigratedDestinations(array('name', 'created', 'changed', 'status',
    //  'promote', 'revision', 'language'));
  }
}

