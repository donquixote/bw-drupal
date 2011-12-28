<?php


/**
 * This is disabled (using abstract keyword),
 * until we have a convincing solution for importing revisions.
 */
abstract class bw_migrate_Migration_node_bw_wikipage extends bw_migrate_Migration {

  /**
   * TODO:
   *   What about a destination plugin for node revision?
   */
  protected function _init($src, $dest, $map) {

    $this->description = 'Migrate wiki pages.';

    $dest->node('bw_wikipage');

    // Composite primary key
    $src->primary('pagename', 'varchar', 'Unique page name');
    $src->primary('version', 'int', 'Wiki page version');

    $q = $src->rox_select('ewiki', 'w');
    $q->fields('w', array(
      'pagename', 'version',
      'flags', 'content', 'author', 'created', 'lastmodified',
    ));

    // Mapped fields
    $map->map('title', 'pagename');
    $map->map('body', 'content');
    $map->uid('uid')->defaultValue(1);

    $dest->ignore(array());
  }

  protected function _prepareRow($row) {
    $row->pagename = implode(' ', explode('_', $row->pagename));
  }
}



