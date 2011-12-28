<?php


class bw_migrate_Migration_ogMembership {

  protected function _init($src, $dest, $map) {

    $dest->dest('OGMembership');
    $src->primary('id');

    $q = $src->rox_select('members_groups_subscribed', 's');
    $q->fields('s', array(
      'id', 'IdSubscriber', 'IdGroup',
      'ActionToWatch', 'UnSubscribeKey',
      'created',
    ));

    $map->strtotime('created', 'created');

    // Currently the test db has nothing in this table.
  }
}

