<?php


class bw_migrate_Migration_user extends bw_migrate_Migration {

  protected function _init($src, $dest, $map) {

    $this->description = 'Create drupal users from rox members';

    $dest->dest('User');
    $src->primary('id');

    $q = $src->rox_select_members('m', 'u');
    $q->fields('m', array('id', 'Username'));
    $q->fields('u', array('email', 'pw', 'active', 'lastlogin'));
    $q->leftJoin('membersphotos', 'p', 'm.id = p.IdMember');
    $q->fields('p', array('FilePath', 'id'));

    // Dedupe assures that value is unique. Use it when source data is non-unique.
    // Pass the Drupal table and column for determining uniqueness.
    //
    // Attention:
    //   Dedupe overdedupes on udpate, see http://drupal.org/node/1358318
    // 
    $map->map('name', 'username')->dedupe('users', 'name');

    $map->strtotime('login', 'lastlogin');
    $map->strtotime('access', 'lastlogin');

    $map->map('mail', 'email');
    $map->map('pass', 'pw');  // TODO: like D6->7 migration

    // Instead of mapping a source field to a destination field, you can
    // hardcode a default value. You can also use both together - if a default
    // value is provided in addition to a source field, the default value will
    // be applied to any rows where the source field is empty or NULL.
    $map->map('roles')->defaultValue(drupal_map_assoc(array(2)));

    // TODO: fix
    //    $map->map('active', 'status');
    $map->map('status')->defaultValue(1);  // 1 => active

    $map->map('picture', 'p_id')->sourceMigration('file_membersphotos');

    // Unmapped fields
    $src->ignore(array('active'));
    $dest->ignore(array(
      'theme', 'signature', 'timezone', 'language',
      'is_new', 'signature_format', 'created', 'init', 'group_audience',
      'path', 'pathauto',
    ));
  }
}


