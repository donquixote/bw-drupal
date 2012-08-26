<?php


class bw_migrate_Migration_comment_group extends bw_migrate_Migration {

  function _init($src, $dest, $map) {

    $this->description = 'Migrate Group discussion comments';

    $dest->comment('group');
    $src->primary('id');

    $q = $src->rox_select('shouts', 's');
    $q->fields('s', array(
      'id', 'member_id_foreign',
      'table_id',
      'created', 'title', 'text',
    ));
    $q->where("`table` = 'groups'");

    $map->map('subject', 'title');
    $map->map('comment_body', 'text');
    $map->defaultValue('comment_format', 'filtered_html');

    $map->uid('uid', 'member_id_foreign');
    $map->foreignKey('nid', 'table_id', 'node_group');

    $map->strtotime('created', 'created');

    $src->ignore(array(
      'table',  // for us, this is always 'groups'.
    ));
    $dest->ignore(array(
      'pid',  // "parent" comment, for threaded view. Does not exist in rox.
      'status',
      'thread',  // what is this?
      'changed',

      'language',
      'path',

      // These fields are meant for blog commenting from ppl w/o account.
      'name', 'hostname', 'mail', 'homepage',
    ));
  }
}


