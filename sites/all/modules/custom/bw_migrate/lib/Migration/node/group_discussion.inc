<?php


class bw_migrate_Migration_node_group_discussion extends bw_migrate_Migration {

  function _init($src, $dest, $map) {

    $this->description = 'Migrate Group discussions from BW-Rox to BW-Drupal';

    $dest->node('group_discussion');
    $src->primary('id');

    $q = $src->rox_select('forums_threads', 't');
    $q->fields('t', array(
      'id',
      'expiredate', 'IdTitle', 'threadid', 'title', 'first_postid',
      'last_postid', 'replies', 'views', 'geonameid', 'admincode',
      'countrycode', 'continent', 'tag1', 'tag2', 'tag3', 'tag4', 'tag5',
      'stickyvalue', 'IdFirstLanguageUsed', 'IdGroup', 'WhoCanReply',
      'ThreadDeleted', 'ThreadVisibility',
    ));
    $q->innerJoin('forums_posts', 'p', 't.id = p.threadid AND t.first_postid = p.postid');
    $q->fields('p', array(
      'message', 'IdWriter', 'create_time', 'last_edittime', 'last_editorid',
      'edit_count',
    ));
    $q->condition('p.PostDeleted', 'NotDeleted');
    $q->condition('t.ThreadDeleted', 'NotDeleted');
    // Require threads to be in a group.
    // Otherwise, we make them a different content type. Do we?
    $q->innerJoin('groups', 'g', 't.IdGroup = g.id');
    $q->groupBy('t.id');

    $map->map('title', 'title');
    $map->map('body', 'message');
    $map->defaultValue('format', 'filtered_html');
    $map->map('sticky', 'stickyvalue');

    $map->uid('uid', 'idwriter');
    $map->uid('revision_uid', 'idwriter');

    $map->strtotime('created', 'create_time');
    $map->strtotime('changed', 'last_edittime');

    $map->foreignKey('group_audience', 'idgroup', 'node_group');

    // Unmigrated fields
    $src->ignore(array(
      'expiredate', 'idtitle', 'threadid', 'first_postid', 'last_postid',
      'replies', 'views', 'geonameid', 'admincode', 'continent',
      'tag1', 'tag2', 'tag3', 'tag4', 'tag5',
      'stickyvalue',
      'idfirstlanguageused', 'idgroup', 'whocanreply', 'threaddeleted',
      'threadvisibility', 'last_editorid', 'edit_count',
      'countrycode',
    ));
    $dest->ignore(array(
      'group_content_access',
    ));
  }

  protected function _prepareRow($row) {
    $row->stickyvalue = ($row->stickyvalue > 0) ? 1 : 0;
  }
}




