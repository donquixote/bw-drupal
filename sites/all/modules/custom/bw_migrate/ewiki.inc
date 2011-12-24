<?php



class WikiNodeMigration extends BWMigration {

  /**
   * TODO:
   *   What about a destination plugin for node revision?
   */
  public function _init($src, $dest, $map) {

    $this->description = 'Migrate wiki pages.';

    $dest->node('bw_wikipage');

    // pagename as source key doesn't really work yet
    // somehow type varchar is not picked up
    $src->primary('version', 'Wiki page version', array('type' => 'int'));

    $q = $src->rox_select('ewiki', 'w');
    $q->fields('w', array(
      'pagename', 'version', 'flags', 'content', 'author', 'created',
      'lastmodified',
    ));

    // Mapped fields
    $map->map('title', 'pagename')->description(t('Mapping something to node title'));
    $map->map('body', 'content');

    // Unmapped destination fields
    //$this->addUnmigratedDestinations(array('name', 'created', 'changed', 'status',
    //  'promote', 'revision', 'language'));
  }
}



