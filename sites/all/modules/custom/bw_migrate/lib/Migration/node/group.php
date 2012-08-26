<?php


class bw_migrate_Migration_node_group extends bw_migrate_Migration {

  function _init($src, $dest, $map) {

    $this->description = 'Migrate Groups from BW-Rox to BW-Drupal.';

    $dest->node('group');
    $src->primary('id');

    $q = $src->rox_select('groups', 'g');
    $q->fields('g', array(
      'id',
      'Name', 'Type', 'created', 'NbChilds', 'Picture', 'MoreInfo',
      'DisplayedOnProfile', 'VisiblePosts', 'IdDescription', 'IdGeoname',
      'IsLocal',
    ));

    $map->map('title', 'name');
    $map->map('language')->defaultValue('en');
    $map->yesno('promoted', 'displayedonprofile');
    $map->yesno('group_access', 'visibleposts');

    $map->trad('body', 'iddescription', 'groups.IdDescription');

    $map->uidAdmin('uid');
    $map->uidAdmin('revision_uid');

    $map->strtotime('created', 'created');
    $map->defaultValue('group_group', NULL);

    // Unmigrated fields
    $src->ignore(array(
      'type',  // enum('Public','NeedAcceptance','NeedInvitation')
      'nbchilds',  // redundant?
      'picture', 'idgeoname', 'islocal',
      'moreinfo',  // seems to be empty
    ));
    $dest->ignore(array(
      'changed', 'field_group_picture', 'field_wiki_text',
    ));
  }
}



