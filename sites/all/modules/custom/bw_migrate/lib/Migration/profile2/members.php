<?php


/**
 * Migration class to test import of various date fields.
 */
abstract class bw_migrate_Migration_profile2_members extends bw_migrate_Migration {

  protected function _init($src, $dest, $map) {

    $this->description = t('Migration of BW Rox members table into profile2 entities');

    $src->primary('idmember');
    $dest->dest('Profile2', 'members');

    $q = $src->rox_select('members', 'm');
    $q->innerJoin('membersphotos', 'mp', 'm.id = mp.IdMember');
    $q->innerJoin('user', 'u', 'u.handle = m.Username');
    $q->groupBy('m.id');
    $q->fields('mp', array(
      'id', 'FilePath', 'IdMember', 'SortOrder', 'Comment'
    ));

    $map->map('field_photos', 'filepath');
    $map->uid('uid', 'IdMember');
  }
}
