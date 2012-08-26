<?php


/**
 * Migration class to test import of various date fields.
 */
abstract class bw_migrate_Migration_userRelationships_comment extends bw_migrate_Migration {

  protected function _init($src, $dest, $map) {

    $this->description = t('Migration of BW Rox comments table into User Relationships');

    $dest->dest('UserRelationships', 'comment');
    $src->primary('id');

    $q = $src->rox_select('comments', 'c');
    $q->fields('c', array(
      'IdFromMember', 'IdToMember', 'Lenght', 'Quality', 'TextFree', 'TextWhere',
      'updated', 'id', 'created', 'AdminAction', 'DisplayableInCommentOfTheMonth'
    ));

    $map->uid('requester_id', 'IdFromMember');
    $map->uid('requestee_id', 'IdToMember');
    $map->map('approved')->defaultValue(1);  // 1 => active?
    $map->map('created_at', 'created');
    $map->map('updated_at', 'updated');
  }
}
