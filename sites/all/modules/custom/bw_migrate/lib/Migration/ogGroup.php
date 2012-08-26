<?php


class bw_migrate_Migration_ogGroup extends bw_migrate_Migration {

  protected $systemOfRecord = Migration::DESTINATION;

  function _init($src, $dest, $map) {

    $this->description = 'Create og groups (with gid) from BW-Rox groups.';

    $dest->table('og');
    $src->primary('id');

    $q = $src->rox_select('groups', 'g');
    $q->fields('g', array(
      'id',
      'Name', 'Type', 'created', 'NbChilds', 'Picture', 'MoreInfo',
      'DisplayedOnProfile', 'VisiblePosts', 'IdDescription', 'IdGeoname',
      'IsLocal',
    ));

    $map->foreignKey('gid', 'id', 'node_group')->callbacks(array($this, 'gidForNid'));

    // Unmigrated fields
    $src->ignore(array(
      'type',  // enum('Public','NeedAcceptance','NeedInvitation')
      'nbchilds',  // redundant?
      'picture', 'idgeoname', 'islocal',
      'moreinfo',  // seems to be empty
      'displayedonprofile', 'visibleposts', 'iddescription',
      'name', 'created',
    ));
    $dest->ignore(array(
      'etid', 'entity_type',
      'label', 'state', 'created',
    ));
  }

  function gidForNid($nid) {
    return db_select('og')
      ->condition('etid', $nid)
      ->condition('entity_type', 'node')
      ->fields('og', array('gid'))
      ->execute()
      ->fetchField()
    ;
  }
}





