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
    $this->addFieldMapping('title', 'title')
         ->description(t('Mapping something to node title'));

    //Actual title: SELECT Sentence FROM words WHERE code = 'FaqA_' . QandA   ShortCode = 'en'

    // To maintain node identities between the old and new systems (i.e., have
    // the same unique IDs), map the ID column from the old system to nid and
    // set is_new to TRUE.
    $this->addFieldMapping('nid', 'id')
         ->description(t('Preserve old beer ID as nid in Drupal'));
    $this->addFieldMapping('is_new')
         ->defaultValue(TRUE);

    //Actual title: SELECT Sentence FROM words WHERE code = 'FaqA_' . QandA

    $this->addFieldMapping('body', 'body');

    // Unmapped destination fields
    //$this->addUnmigratedDestinations(array('name', 'created', 'changed', 'status',
    //  'promote', 'revision', 'language'));
  }

  public function prepareRow($current_row) {
    var_dump($current_row);
    $current_row->title = $this->getTranslation('FaqQ_' . $current_row->qanda);
    $current_row->body = $this->getTranslation('FaqA_' . $current_row->qanda);
  }

  public function getTranslation($code) {
    $result = $this->roxdb_connection
      ->query('SELECT Sentence FROM {words} WHERE code = :code AND ShortCode = :lang',
	      array(':code' => $code, ':lang' => 'en'));
    foreach ($result as $row) { // this shouldn't be a loop but just want working code now
      $sentence = $row->sentence ;
    }
    if (!$sentence) {
      $sentence = $code;
    }
    return $sentence;
  }

}



