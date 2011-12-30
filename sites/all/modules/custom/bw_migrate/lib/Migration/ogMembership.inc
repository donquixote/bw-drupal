<?php


class bw_migrate_Migration_ogMembership extends bw_migrate_Migration {

  protected function _init($src, $dest, $map) {

    $dest->dest('OGMembership');
    $src->primary('id');

    $q = $src->rox_select('membersgroups', 'mg');
    $q->innerJoin('groups', 'g', 'g.id = mg.IdGroup');
    $q->innerJoin('members', 'm', 'm.id = mg.IdMember');
    $q->innerJoin('user', 'u', 'u.handle = m.Username');
    $q->groupBy('mg.id');
    $q->fields('mg', array(
      'id', 'IdMember', 'IdGroup',
      'updated', 'created',
      'Comment',
      'Status',  // enum('In','WantToBeIn','Kicked','Invited')
      'IacceptMassMailFromThisGroup',  // enum('yes','no')
      'CanSendGroupMessage',  // enum('yes','no')
      'IsLocal',
    ));

    $map->strtotime('created', 'created');
    $map->foreignKey('gid', 'idgroup', 'ogGroup');
    $map->uid('uid', 'idmember');
    // $map->foreignKey('

    $src->ignore(array(
      'updated', 'comment', 'status',
      'iacceptmassmailfromthisgroup',
      'cansendgroupmessage',
      'islocal',
    ));
    $dest->ignore(array(
      'state', 'is_admin',
    ));
  }
}

